//
//  MultidimensionaIloArray.cpp
//  Amadeus
//
//  Created by Micheli  Knechtel on 30/05/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#include "MultidimensionaIloArray.hpp"


IloDoubleVarMatrix MultidimensionaIloArray::IloDoubleVarMatrix2D(const IloEnv env, int n, int ub, string varName)
{
    IloDoubleVarMatrix x(env, n);
   
    for(int i=0; i <n; i++)
    {
        x[i] = IloNumVarArray( env, n);
        
        for(int j=0; j <n; j++)
        {
            x[i][j] = IloNumVar(env);
            string name = varName.c_str()+SSTR(i) +SSTR(j);
            x[i][j].setName(name.c_str());
        }
    }
    return x;
}

IloNumVarArray MultidimensionaIloArray::IloNumVarArray1D(const IloEnv env, int n)
{
    IloNumVarArray x(env, n);
    for (int i=0; i < n; i++)
        x[i] = IloNumVar(env);
    return x;
}
