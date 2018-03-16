//
//  QuadraticModel.cpp
//  Amadeus
//
//  Created by Micheli  Knechtel on 25/05/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//
#include <map>
#include <stdio.h>

#include "QuadraticModel.hpp"
#include "DataManager.hpp"
#include "Leg.hpp"
#include "MultidimensionaIloArray.hpp"


QuadraticModel::QuadraticModel()
{
    cout<<"**********************************************"<<endl<<endl;
    cout<<"Quadratic Model"<<endl<<endl;
    cout<<"**********************************************"<<endl<<endl;
    
}

void QuadraticModel::resolution()
{
    
    try
    {
        IloModel model(env);
        
        nbAirports = (int) DataManager::getDataManager()->getAirports().size();
        nbLegs = (int) DataManager::getDataManager()->getLegs().size();
        foundOD = IloDoubleMatrix(env, nbAirports);
        
        quadraticConstraint = new QuadraticConstraints(env, model);
        quadraticConstraint->passagengerInOut();
        quadraticConstraint->legsAndConnections();
        
        
        cplex = IloCplex (model);
        cplex.setParam(IloCplex::RootAlg, 3);
        
        if(strcmp(exportFile.c_str(),"")!=0)
            cplex.exportModel(exportFile.c_str());
        
        cplex.setOut(env.getNullStream());
        
        if(cplex.solve())
        {
            env.out() << "Obj. value (weigthed mistakes in absolute values): " << cplex.getObjValue()<< endl<< endl;
            headerFoundSolution();
            bodyFoundSolution();
            legDetailList();
        }
        else
            env.out()<< " No solution found !!!!! Please, check the data. " << endl;
        
     
    }
    
    
    catch (IloException& e)
    {
        cerr << "Error: " << e << endl;
    }
    env.end();
}


void QuadraticModel::setExportFile(string exportFile)
{
    this->exportFile = exportFile;
}

vector<vector<double>> QuadraticModel::getMatrix()
{
    return matrix;
}

void QuadraticModel::headerFoundSolution()
{
    int nbAirports = (int) DataManager::getDataManager()->getAirports().size();
    int size = (int) SSTRR(nbAirports).length();
    
    
    cout<<"========================================"<<endl;
    cout<< "PASSENGER FLOW TABLE: "<<endl;
    cout<<"========================================"<<endl;
    
    if(size>1)
    {
        cout<<" ";
        cout.width(size);
    }
    
    for(int i=0; i<nbAirports;i++)
        cout<< (i==0 ? setw(15+(int)(new string("Total|"))->length()+size): setw(15))<<DataManager::getDataManager()->codeApMap.at(i)<<"|";
    
    cout<<endl;
}
void QuadraticModel::bodyFoundSolution()
{
    int size = (int) SSTRR(nbAirports).length();
    
    for(int i=0; i<nbAirports;i++)
    {
        int currentSize = (int) SSTRR(i).length();
        cout<<" ";
        cout.width((int)(new string("Total"))->length());
        if (currentSize<size)
        {
            cout<<"";
            cout.width(size-currentSize);
            cout<< DataManager::getDataManager()->codeApMap.at(i)<<"|";
        }
        else
            cout<< DataManager::getDataManager()->codeApMap.at(i)<<"|";
        
        foundOD[i] = IloNumArray(env,nbAirports);
        foundOD[i][i] = 0;
        
        for (int j=0;j<nbAirports;j++)
            if (i!=j)
            {
                foundOD[i][j] = cplex.getValue(quadraticConstraint->getOD()[i][j]);
            }
        
        for (int j=0;j<nbAirports;j++)
        {
//            cout.precision(3);
            cout<< setprecision(3)<<setw(15) << foundOD[i][j]<<"|";
        }
        cout<<endl;
    }
    
    
    double sumFound =0;
    
    cout<<" ";
    cout.width(size);
    cout<<"Total"<<"|";
    
    for(int i=0; i<nbAirports;i++)
    {
        sumFound = 0;
        cout.precision(3);
        
        for (int j=0;j<nbAirports;j++)
            sumFound+=foundOD[j][i];
        
        cout<<setw(15)<<sumFound<<"|";
    }
    
}

void QuadraticModel::legDetailList()
{
    IloNumArray foundPassengers(env, nbLegs);
    cplex.getValues(foundPassengers,quadraticConstraint->getPassengers());
    
    map<pair<int, int>, Leg> mapAux = DataManager::getDataManager()->getLegs();
    map<pair<int, int>, Leg>::iterator it;
    cout<<endl;
    cout<<endl;
    cout<<"========================================"<<endl;
    cout<<"Legs Details "<<endl;
    cout<<"========================================"<<endl;
    
    int i =0;
   
    cout <<"Airport"<<"|";
    cout.width(15);
    cout <<"lowerBound"<<"|";
    cout.width(15);
    cout << "found"<<"|";
    cout.width(15);
    cout<< "pHat"<<"|";
    cout.width(15);
    cout<< "upperBound"<<"|"<<endl;
   
    double sum = 0;
    for (it = mapAux.begin();it!= mapAux.end(); it++)
    {
        cout.precision(3);
        cout.width((new string("Airport"))->length());
        cout<<SSTRR(DataManager::getDataManager()->codeApMap.at(it->first.first))+ " " +SSTRR( DataManager::getDataManager()->codeApMap.at(it->first.second))<<"|";
        cout.width(15);
        cout<<it->second.getPlb()<<"|";
        cout.width(15);
        cout<< foundPassengers[i]<<"|";;
        cout.width(15);
        cout<< it->second.getPhat()<<"|";
        cout.width(15);
        cout<<it->second.getPub()<<"|"<<endl;
        i++;
    }
    
    int l=0;
    map<pair<int, int>, Leg>::iterator itAux;
    
    
    cplex.getValues(foundPassengers,quadraticConstraint->getPassengers());
//    i=0;
//    cout<<endl;
//    cout<<"========================================"<<endl;
//    cout<<"out[i]+=foundPassengers[i]"<<endl;
//    cout<<"========================================"<<endl;
//    for (it = mapAux.begin();it!= mapAux.end(); it++)
//    {
//        
//        if(l==it->first.first)
//        {
//            sum+=foundPassengers[i];
//            itAux = it;
//            itAux++;
//            if(itAux == mapAux.end())
//                cout<<it->first.first<<" \t= " <<sum<<endl;
//        }
//        else
//        {
//            itAux = it;
//            itAux--;
//            cout<<itAux->first.first<<" \t= " <<sum<<endl;
//            sum = 0;
//            sum+= foundPassengers[i];
//        }
//        
//        l=it->first.first;i++;
//    }
//    
//    cout<<"========================================"<<endl;
//    cout<<"departure [from file] "<<endl;
//    cout<<"========================================"<<endl;
//    
//    for (int i = 0; i<DataManager::getDataManager()->getAirports().size(); i++)
//    {
//        cout<< i<< " =  "<<DataManager::getDataManager()->getAirports()[i].getTotalDeparturePax()<<endl;
//    }
//    cout<<endl;
//    
//    for(int i=0; i<nbAirports;i++)
//    {
//        foundOD[i] = IloNumArray(env,nbAirports);
//        foundOD[i][i] = 0;
//        for (int j=0;j<nbAirports;j++)
//            if (i!=j)
//            {
//                foundOD[i][j] = cplex.getValue(quadraticConstraint->getOD()[i][j]);
//                cout << "OD["<<i<<","<<j<<" ] = "<< cplex.getValue(quadraticConstraint->getOD()[i][j])<<endl;
//            }
//    }
    
    IloNumArray in(env, nbLegs);
}

