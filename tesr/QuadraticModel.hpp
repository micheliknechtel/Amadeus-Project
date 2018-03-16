//
//  QuadraticModel.hpp
//  Amadeus
//
//  Created by Micheli  Knechtel on 25/05/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#ifndef QuadraticModel_hpp
#define QuadraticModel_hpp

#include <stdio.h>
#include <vector>
#include "Definitions.h"
#include "QuadraticConstraints.hpp"

class QuadraticModel {
    string exportFile = "";
    vector<vector <double> > matrix;
    IloDoubleMatrix foundOD;
    int nbLegs;
    int nbAirports;
    IloEnv env;
    IloCplex cplex;
    QuadraticConstraints *quadraticConstraint;
public:
    QuadraticModel();
    void resolution();
    void setExportFile(string fileName);
    vector<vector <double> > getMatrix();
    void headerFoundSolution();
    void bodyFoundSolution();
    void legDetailList();
};

#endif /* CplexModel_hpp */
