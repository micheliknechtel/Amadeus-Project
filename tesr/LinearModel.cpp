//
//  LinearModel.cpp
//  Amadeus
//
//  Created by Micheli  Knechtel on 30/05/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#include "LinearModel.hpp"
#include <map>
#include <ilcplex/ilocplex.h>
#include <stdio.h>
#include "MultidimensionaIloArray.hpp"
#include "DataManager.hpp"
#include "LinearConstraints.hpp"
#include "Leg.hpp"
#include <string>
#include <unistd.h>

#include <time.h> //not sure is the same for linux


LinearModel::LinearModel()
{
}
void LinearModel::resolution()
{
    IloEnv env;
    try
    {
        // Data coming from file ...
        int nbAirports = (int) DataManager::getDataManager()->getAirports().size();
        IloModel model(env);
        
        LinearConstraints *linearConstraint = new LinearConstraints(env, model);
        linearConstraint->passagengerInOut();
        linearConstraint->legsAndConnections();
        
        // Solving
        IloCplex cplex(model);
        if(strcmp(exportFile.c_str(),"")!=0)
            cplex.exportModel(exportFile.c_str());
        
        cplex.setOut(env.getNullStream());
        
        if(cplex.solve())
        {
            
            // A solution has been found
            env.out() << "Obj. value (weigthed mistakes in absolute values): " << cplex.getObjValue()<< endl<< endl << "Found O-D Matrix:"<<endl;
            
            //Retrieving the solution
            IloDoubleMatrix foundOD(env, nbAirports);
            
            vector<vector<double>> matrix(nbAirports);
            
            for(int i=0; i<nbAirports;i++)
            {
                
                matrix[i] =vector<double>(nbAirports);
                
                foundOD[i]=IloNumArray(env,nbAirports);
                cplex.getValues(foundOD[i],linearConstraint->getOD()[i]);
                
                for (int j=0;j<nbAirports;j++)
                {
                    matrix[i][j]=foundOD[i][j];
                }
                env.out() << foundOD[i] << endl;
            }
            this->matrix = matrix;
                      
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

void LinearModel::setExportFile(string exportFile)
{
    this->exportFile = exportFile;
}

vector<vector<double>> LinearModel::getMatrix()
{
    return matrix;
}

