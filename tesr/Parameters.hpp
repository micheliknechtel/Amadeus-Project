//
//  Parameters.hpp
//  Amadeus
//
//  Created by Micheli Knechtel on 14/10/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#ifndef Parameters_hpp
#define Parameters_hpp

#include <stdio.h>
#include <string>
#include "Definitions.h"
#include <vector>

class Parameters
{
    int numberAirports;
    int maxNumberItineraries;
    int maxNumberConections;
    string filePath;
    string dataFolder;
    string fileAirports;
    string fileLegs;
    string fileItinerary;
    string fileSolution;
    static Parameters *parameters;
    bool hub;
    bool loop;
    vector<double> noise;
    double distress;
public:
    static Parameters* getParameters();
    void setParameters(int numberAirports,
                       int maxNumberItineraries,
                       int maxNumberConections,
                       string filePath,
                       string datafolder,
                       string fileAirports,
                       string fileLegs,
                       string fileItinerary,
                       string fileSolution,
                       bool hub,
                       double noise,
                       bool loop,
                       double distress);
    string extractingFileName(string str);
    string getfilePath();
    string getdataFolder();
    string getAirportFileNameWithNoise(double noise);
    string getAirportFileName();
    string getItineraryFileName();
    string getLegsFileName();
    string getLegsFileNameWithNoise(double noise);
    string getSolutionFileName();
    int getNumberAirports();
    int getMaxNumberItineraries();
    int getMaxNumberConections();
    bool getHub();
    bool getLoop();
    vector<double>  getNoise();
    double getDistress();
    void setNoise(vector<double> noise);
    void setDistress(double distress);
    void setHub(bool hub);
    void setLoop(bool loop);
    void setNumberAirports(int numberAirports);
    void setMaxNumberItineraries(int maxNumberItineraries);
    void setMaxNumberConections(int maxNumberConections);
    void setFilePath(string filePath);
    void setDataFolder(string dataFolder);
    void setAirportFileName(string fileAirports);
    void setItineraryFileName(string fileItinerary);
    void setLegsFileName(string fileLegs);
    void setSolutionFileName(string fileSolution);
    string getItineraryFileNameWithNoise(double noise);
};

#endif /* Parameters_hpp */
