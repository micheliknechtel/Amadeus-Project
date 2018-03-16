//
//  QuadraticConstraints.cpp
//  Amadeus
//
//  Created by Micheli  Knechtel on 30/05/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#include "QuadraticConstraints.hpp"
#include "DataManager.hpp"
#include "MultidimensionaIloArray.hpp"
#include <cmath>

QuadraticConstraints::QuadraticConstraints(IloEnv env, IloModel model)
{
    this->env = env;
    this->model = model;
    
    // Data coming from file ...
    nbAirports = (int) DataManager::getDataManager()->getAirports().size();
    nbLegs = (int) DataManager::getDataManager()->getLegs().size();
    
    // The main decision variables: number of passengers traveling from i to j
    OD = MultidimensionaIloArray::IloDoubleVarMatrix2D(env, nbAirports, 0, "OD");
    
    this->passengers = passangersPerLeg();
}

IloNumVarArray QuadraticConstraints::passangersPerLeg()
{
    int i = 0;
    
    IloNumVarArray passengers(env, nbLegs);
    map<pair<int, int>, Leg>::iterator it;
    map<pair<int, int>, Leg> mapAux = DataManager::getDataManager()->getLegs();
    
    for (it = mapAux.begin();it!= mapAux.end(); it++)
    {
        passengers[i] = IloNumVar(env,it->second.getPlb(),it->second.getPub());
        string name = "passengers" + SSTR(i);
        passengers[i].setName(name.c_str());
        i++;
    }
    return passengers;
}

void QuadraticConstraints::passagengerInOut()
{
 
    // i = {1..n = nbAirports} and l = {1..n = nbLegs}
    // out[i] = passangers[1] + passangers[2] + ...+ passangers[l] = departures[i]
    // out -> sum of all passangers departing from airport i should be equals to total departure

    out = IloRangeArray(env,nbAirports);
    in = IloRangeArray(env,nbAirports);
    
    IloExpr expr_in(env);
    IloExpr expr_out(env);

    string name;
    
    for (int i=0; i < nbAirports; i++)
    {
        IloNum departures = DataManager::getDataManager()->getAirports()[i].getTotalDeparturePax();
        IloNum arrivals = DataManager::getDataManager()->getAirports()[i].getTotalArrivalPax();
        
        in[i] = IloRange(env,arrivals,expr_in,arrivals);
        name = "in" + SSTR(i);
            
        in[i].setName(name.c_str());
        
        out[i] = IloRange(env,departures,expr_out,departures);
        name = "out" + SSTR(i);
        out[i].setName(name.c_str());
    }
    
    
    int l = 0;
    map<pair<int, int>, Leg> mapAux = DataManager::getDataManager()->getLegs();
    
    for (map<pair<int, int>, Leg>::iterator it = mapAux.begin();it!= mapAux.end(); it++)
    {
        out[it->second.getOrigimAirport()].setLinearCoef(passengers[l],1);
         in[it->second.getDestinationAirport()].setLinearCoef(passengers[l],1);

        l++;
    }
    
    model.add(out);
    model.add(in);
    
    in.end();
    out.end();
}

void QuadraticConstraints::passagengerInOut2()
{
    //Constraints
    IloRangeArray out(env,nbAirports);
    IloRangeArray in(env,nbAirports);
    
    // constraints on the number of passengers leaving and arriving in the airports
    for (int i=0; i < nbAirports; i++)
    {
        IloNum departures = DataManager::getDataManager()->getAirports()[i].getTotalDeparturePax();
        
        // Constraints on the number of passengers leaving i
        out[i] = IloRange(env,departures,IloSum(OD[i]),departures);
        
        string name = "out" + SSTR(i);
        out[i].setName(name.c_str());
        
        IloExpr ex(env);
        IloNum arrivals = DataManager::getDataManager()->getAirports()[i].getTotalArrivalPax();
        
        for (int j=0; j <nbAirports; j++)
            ex+= OD[j][i];
        
        // Constraints on the number of passengers arriving in
        in[i]=IloRange(env,arrivals,ex,arrivals);
        name = "in" + SSTR(i);
        in[i].setName(name.c_str());
        ex.end();
    }
    model.add(out);
    model.add(in);
    in.end();
    out.end();
}

void QuadraticConstraints::legsAndConnections()
{
    
    //Links beetween Origines-Destinations and legs; link between the legs and the objective function
    map<pair<int, int>, Leg>::iterator it;
    IloRangeArray ODPassengers(env,nbLegs);
    IloExpr expObj(env);
    
    int i = 0;
    
    map<pair<int, int>, Leg> mapAux = DataManager::getDataManager()->getLegs();
    
    
    // For each leg
    for (it = mapAux.begin();it!= mapAux.end(); it++)
    {
        IloInt nbPaths = it->second.getComposition().size();
        IloExpr expr(env);
        
        // For each origin-destination which uses this leg
        for(int j=0; j < nbPaths; j++)
        {
            IloInt k1 = it->second.getComposition().at(j).getOriginAirport();
            IloInt k2 = it->second.getComposition().at(j).getDestinationAiport();
            expr += it->second.getComposition()[j].getAlfa() * OD[k1][k2];
            
//            cout<<k1<<","<<k2<<" = "<<it->second.getComposition()[j].getAlfa() <<endl;

        }
        
        ODPassengers[i]=IloRange(env,0,passengers[i]-expr,0);
        string name = "ODPassengers" + SSTR(i);
        ODPassengers[i].setName(name.c_str());
        
        expr.end();
//        expObj +=it->second.getBeta()*(passengers[i] * passengers[i] - 2 * it->second.getPhat() * passengers[i]);// Objective function
        expObj +=/*it->second.getBeta()**/(passengers[i] - it->second.getPhat())*(passengers[i]-it->second.getPhat());// Objective function
//        cout<<it->first.first<<","<<it->first.second<<" = "<<it->second.getPhat()<<endl;
        i++;
    }
    
    
    model.add(ODPassengers);
    IloObjective obj = IloMinimize(env, expObj);                            //Objective function
    model.add(obj);
    expObj.end();
    ODPassengers.end();
}

void QuadraticConstraints::legsAndConnections2()
{
    
   
        //Links beetween Origines-Destinations and legs; link between the legs and the objective function
        map<pair<int, int>, Leg>::iterator it;
        IloRangeArray ODPassengers(env,nbLegs);
        IloExpr expObj(env);
        
        int i = 0;
        
        map<pair<int, int>, Leg> mapAux = DataManager::getDataManager()->getLegs();
        
        for (it = mapAux.begin();it!= mapAux.end(); it++)
        {
            IloInt nbPaths = it->second.getComposition().size();
            IloExpr exp(env);
            
            for(int j=0; j < nbPaths; j++)
            {
                IloInt k1 = it->second.getComposition().at(j).getOriginAirport();
                IloInt k2 = it->second.getComposition().at(j).getDestinationAiport();
                exp += it->second.getComposition()[j].getAlfa() * OD[k1][k2];
            }
            
            // Links between OD variables and Passenger variables
            ODPassengers[i]=IloRange(env,0,passengers[i]-exp,0);
            string name = "ODPassengers" + SSTR(i);
            ODPassengers[i].setName(name.c_str());
            exp.end();
            expObj +=it->second.getBeta()*(passengers[i]-it->second.getPhat())*(passengers[i]-it->second.getPhat());// Objective function
            i++;
        }
        model.add(ODPassengers);
        IloObjective obj = IloMinimize(env, expObj);                            //Objective function
        model.add(obj);
        expObj.end();
        ODPassengers.end();
    
}

IloDoubleVarMatrix QuadraticConstraints::getOD()
{
    return OD;
}

IloNumVarArray QuadraticConstraints::getPassengers()
{
    return passengers;
}
