//
//  FirstModel.hpp
//  Amadeus
//
//  Created by Micheli  Knechtel on 30/05/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#ifndef FirstModel_hpp
#define FirstModel_hpp
#include <ilcplex/ilocplex.h>
#include <stdio.h>
#include <vector>

using namespace std;

ILOSTLBEGIN

typedef IloArray<IloNumVarArray> IloDoubleVarMatrix;
typedef IloArray<IloNumArray> IloDoubleMatrix;

class LinearModel {
    string exportFile = "";
    vector<vector <double> > matrix;
public:
    LinearModel();
    void setExportFile(string fileName);
    void resolution();
    vector<vector <double> > getMatrix();
};
#endif /* FirstModel_hpp */
