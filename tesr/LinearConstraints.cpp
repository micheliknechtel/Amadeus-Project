//
//  LinearConstraints.cpp
//  Amadeus
//
//  Created by Micheli  Knechtel on 30/05/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#include "LinearConstraints.hpp"
#include "DataManager.hpp"
#include "MultidimensionaIloArray.hpp"

LinearConstraints::LinearConstraints(IloEnv env, IloModel model)
{
    this->env = env;
    this->model = model;
    
    // Data coming from file ...
    nbAirports = (int) DataManager::getDataManager()->getAirports().size();
    nbLegs = (int) DataManager::getDataManager()->getLegs().size();
    
    // The main decision variables: number of passengers traveling from i to j
    OD = MultidimensionaIloArray::IloDoubleVarMatrix2D(env, nbAirports, 0, "OD");
    
    // For simulation of the absolute value difference
    target = MultidimensionaIloArray::IloNumVarArray1D(env, nbLegs);
    
    out = IloRangeArray(env,nbAirports);
    in = IloRangeArray (env,nbAirports);
}


void LinearConstraints::passagengerInOut()
{
    // constraints on the number of passengers leaving and arriving in the airports
    for (int i=0; i < nbAirports; i++)
    {
        IloNum departures = DataManager::getDataManager()->getAirports()[i].getTotalDeparturePax();
        
        // Constraints on the number of passengers leaving i
        out[i] = IloRange(env,departures,IloSum(OD[i]),departures);
        string name = "out" ;//+ SSTR(i);
        out[i].setName(name.c_str());
        
        IloExpr ex(env);
        IloNum arrivals = DataManager::getDataManager()->getAirports()[i].getTotalArrivalPax();
        
        for (int j=0; j <nbAirports; j++)
            ex+= OD[j][i];
        
        // Constraints on the number of passengers arriving in
        in[i] = IloRange(env,arrivals,ex,arrivals);
        name = "in" ;//+ SSTR(i);
        in[i].setName(name.c_str());
        
        ex.end();
    }
    
    model.add(out);
    model.add(in);
    
    out.end();
    in.end();
}

void LinearConstraints::legsAndConnections()
{
    //Links beetween Origines-Destinations and legs; link between the legs and the objective function
    map<pair<int, int>, Leg>::iterator it;
    int i = 0;
    IloExpr expObj(env);
    
    IloRangeArray passengersOnLegs(env,nbLegs);
    IloRangeArray absVal1(env, nbLegs);
    IloRangeArray absVal2(env, nbLegs);
    
    map<pair<int, int>, Leg> mapAux = DataManager::getDataManager()->getLegs();
    
    for (it = mapAux.begin();it!= mapAux.end(); it++)
    {
        IloInt nbPaths = it->second.getComposition().size();
        IloExpr exp(env);
        
        for(int j=0; j<nbPaths; j++)
        {
            IloInt k1 = it->second.getComposition().at(j).getOriginAirport();
            IloInt k2 = it->second.getComposition().at(j).getDestinationAiport();
            
            exp += it->second.getComposition().at(j).getAlfa() * OD[k1][k2];
        }
        
        passengersOnLegs[i] = IloRange(env,it->second.getPlb(),exp,it->second.getPub());          // Satisfying upper and lower bounds for each leg
        absVal1[i] = IloRange(env, -it->second.getPhat(), target[i] - exp);      // Constraints for the absolute value
        absVal2[i] = IloRange(env, it->second.getPhat(), target[i] + exp);       // Constraints for the absolute value
        exp.end();
        expObj += it->second.getBeta() * target[i];                               // Building Objective function
        i++;
    }
    
    model.add(passengersOnLegs);
    model.add(absVal1);
    model.add(absVal2);
    
    IloObjective obj = IloMinimize(env, expObj);                            //Objective function
    model.add(obj);
    
    expObj.end();
    passengersOnLegs.end();
    absVal1.end();
    absVal2.end();
}

IloDoubleVarMatrix LinearConstraints::getOD()
{
    return OD;
}


