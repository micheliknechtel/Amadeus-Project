//
//  Itinerary.hpp
//  GBlockModeling
//
//  Created by Micheli  Knechtel on 24/05/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#ifndef Itinerary_hpp
#define Itinerary_hpp
#include <vector>
#include <stdio.h>
#include <string>
#include "Definitions.h"


using namespace std;

class Itinerary {
    int origin_airport;
    int destination_airport;
    double alfa;
    
public:
    Itinerary(int origin_airport,int destination_airport, double alfa);
    int getOriginAirport();
    int getDestinationAiport();
    double getAlfa();
    vector<int> getConnections();
    void AddConnection(int c);
    vector<int>connections;
    void setAlfa(double alfa);
    string toString();
    string toStringWithNoise(double noise);
    double getAlfaNoise();
    void setAlfaNoise(double alfa);
    
    ~Itinerary(){connections.clear();}
};

#endif /* Itinerary_hpp */
