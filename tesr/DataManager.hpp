//
//  DataManager.hpp
//  tesr
//
//  Created by Micheli  Knechtel on 18/04/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#ifndef DataManager_hpp
#define DataManager_hpp

#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <string.h>

#include "Airports.hpp"
#include "Itinerary.hpp"
#include "Leg.hpp"
#include "QuadraticModel.hpp"
#include "LinearModel.hpp"
#include "Composition.hpp"
#include "Leg.hpp"
#include "Parameters.hpp"

using namespace std;

class DataManager
{
    static DataManager *dataManager;
    vector<Itinerary> itineraries;
    vector<Airport> airports;
    map<pair<int, int>, Leg> legs;
    map<string,int> apCodeMap;
    
public:
    static DataManager* getDataManager();
    void readAirportsFile(bool containsHeader);
    void readLegsFile(bool containsHeader);
    void readLegsFileM(bool containsHeader);
    void readLegsFileT(bool containsHeader);
    void readLegsFileZ(bool containsHeader);
    int fileNumber;
    void loadData(DATA_TYPE data_type);
    
    map<int, double> outSum;
    map<int, double> inSum;

    string currentDateTime();
    void readItineraryFile(bool containsHeader);
    void parseRoutesToAlfa();
    void printLegs();
    void printAirports();
    void diferrence(LinearModel *linear, QuadraticModel *quadratic);
    void differenceFloor(LinearModel *linear, QuadraticModel *quadratic);
    void alfaVerification();
    void isTotalDepartureSmallerSumUpperBounds();
    void legsVerification();
    void resetData();
    
    vector<Itinerary> getItineraries();
    map<pair<int, int>, Leg> getLegs();
    vector<Airport> getAirports();
    map<int, string> codeApMap;

    
};

#endif /* DataManager_hpp */
