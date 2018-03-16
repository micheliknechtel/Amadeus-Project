//
//  QuadraticConstraints.hpp
//  Amadeus
//
//  Created by Micheli  Knechtel on 30/05/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#ifndef QuadraticConstraints_hpp
#define QuadraticConstraints_hpp

#include <stdio.h>
#include "Definitions.h"

class QuadraticConstraints {
    IloEnv env;
    IloModel model;
    IloNumVarArray passengers;
    IloDoubleVarMatrix OD; // Decision variable
    int nbAirports;
    int nbLegs;
    IloNumVarArray passangersPerLeg();
public:
    QuadraticConstraints(IloEnv env, IloModel model);
    void passagengerInOut();
    void passagengerInOut2();
    void legsAndConnections();
    void legsAndConnections2();
    IloDoubleVarMatrix getOD();
    IloNumVarArray getPassengers();
    
    IloRangeArray out;
    IloRangeArray in;
};
#endif /* QuadraticConstraints_hpp */
