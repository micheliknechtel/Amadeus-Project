//
//  MultidimensionaIloArray.hpp
//  Amadeus
//
//  Created by Micheli  Knechtel on 30/05/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#ifndef MultidimensionaIloArray_hpp
#define MultidimensionaIloArray_hpp

#include <stdio.h>
#include "Definitions.h"

class MultidimensionaIloArray
{
public:
    static IloDoubleVarMatrix IloDoubleVarMatrix2D(const IloEnv env, int n, int ub, string varName);
    static IloNumVarArray IloNumVarArray1D(const IloEnv env, int n);
};

#endif /* MultidimensionaIloArray_hpp */
