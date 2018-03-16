//
//  LinearConstraints.hpp
//  Amadeus
//
//  Created by Micheli  Knechtel on 30/05/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#ifndef LinearConstraints_hpp
#define LinearConstraints_hpp

#include <stdio.h>
#include "Definitions.h"

class LinearConstraints {
    IloEnv env;
    IloModel model;
    IloNumVarArray target; // Decision variable
    int nbAirports;
    int nbLegs;
    IloDoubleVarMatrix OD; // Decision variable
public:
    LinearConstraints(IloEnv env, IloModel model);
    void passagengerInOut();
    void legsAndConnections();
    IloDoubleVarMatrix getOD();
    
    IloRangeArray out;
    IloRangeArray in;
};
#endif /* LinearConstraints_hpp */
