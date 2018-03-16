//
//  InstanceGenerator.hpp
//  Amadeus
//
//  Created by Micheli Knechtel on 09/10/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#ifndef InstanceGenerator_hpp
#define InstanceGenerator_hpp

#include <stdio.h>
#include "Parameters.hpp"
#include "Itinerary.hpp"
#include "Leg.hpp"
#include <map>
#include <stdlib.h>
#include <iostream>
#include <fstream>

class InstanceGenerator {
    double sumAlfa;
    map<pair<int, int>, Leg> legs;
    double *arrival;
    double *radomInteger;
    double *interval;
    double *hubNormalized;
    double *departure;
    int ** x;
    vector<Itinerary> itineraries;
    int numberAirports;
    bool hub = false;
    bool loop = false;
    vector<double> noise;
    double distress = 0;
public:
    InstanceGenerator();
    Itinerary makeConections(int index,int numberOfConections, int o, int d);
    int searchRange(double value);
    void insertLeg(int o, int d);
    void creatingItineraries();
    void adjustingLegPhat();
    void adjustingLegsUpperAndLowerBound();
    void writeItineraries();
    void writeItinerariesWithNoise(int noiseIndex);
    void writeLegs(int noiseIndex);
    void writeSolution();
    void writeAirports(int noiseIndex);
    void creatingHubs();
    void normalizingHubs(double sum, int aeroport, bool renormalizing);
    void buildingData();
    void writeFiles();
};

#endif /* InstanceGenerator_hpp */
