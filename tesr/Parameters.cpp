//
//  Parameters.cpp
//  Amadeus
//
//  Created by Micheli Knechtel on 14/10/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#include "Parameters.hpp"

Parameters* Parameters::parameters = NULL;

Parameters* Parameters::getParameters()
{
    if(!parameters)
    {
        parameters = new Parameters;
    }
    return parameters;
}


vector<double> Parameters::getNoise()
{
    return noise;
}

void Parameters::setNoise(vector<double> noise)
{
    this->noise = noise;
}

double Parameters::getDistress()
{
    return distress;
}

void Parameters::setDistress(double distress)
{
    this->distress = distress;
}

bool Parameters::getHub()
{
    return hub;
}

void Parameters::setHub(bool hub)
{
    this->hub = hub;
}

bool Parameters::getLoop()
{
    return loop;
}

void Parameters::setLoop(bool loop)
{
    this->loop = loop;
}

int Parameters::getNumberAirports()
{
    return numberAirports;
}

void Parameters::setNumberAirports(int numberAirports)
{
    this->numberAirports = numberAirports;
}

int Parameters::getMaxNumberItineraries()
{
    return maxNumberItineraries;
}

void Parameters::setMaxNumberItineraries(int maxNumberItineraries)
{
    this->maxNumberItineraries = maxNumberItineraries;
}

int Parameters::getMaxNumberConections()
{
    return maxNumberConections;
}

void Parameters::setMaxNumberConections(int maxNumberConections)
{
    this->maxNumberConections = maxNumberConections;
}

string Parameters::getfilePath()
{
    return filePath;
}

void Parameters::setFilePath(string filePath)
{
    this->filePath = filePath;
}

string Parameters::getdataFolder()
{
    return dataFolder;
}

void Parameters::setDataFolder(string dataFolder)
{
    this->dataFolder = dataFolder;
}


string Parameters::getAirportFileName()
{
    if (hub)
        return  fileAirports;
    else
        return  fileAirports ;
    
}


string Parameters::getAirportFileNameWithNoise(double noise)
{
    if (hub)
        return  filePath + dataFolder  + fileAirports + "_noise_"+ SSTRR(noise) + "_hub.csv";
    else
        return  filePath + dataFolder  + fileAirports + "_noise_"+ SSTRR(noise) + ".csv";
    
}

void Parameters::setAirportFileName(string fileAirports)
{
    this->fileAirports =  fileAirports ;
}

string Parameters::getItineraryFileName()
{
    if (hub)
        return filePath + dataFolder + fileItinerary + "_noise_" + SSTRR(0) + "_hub.csv";
    else
        return  filePath + dataFolder +fileItinerary + "_noise_" + SSTRR(0);
}

void Parameters::setItineraryFileName(string fileItinerary)
{
    this->fileItinerary = fileItinerary;
}

string Parameters::getItineraryFileNameWithNoise(double noise)
{
    if (hub)
        return  filePath + dataFolder   + fileItinerary + "_noise_"+ SSTRR(noise) + "_hub.csv";
    else
        return  filePath + dataFolder  + fileItinerary + "_noise_"+ SSTRR(noise) + ".csv";
}

string Parameters::getLegsFileName()
{
    return fileLegs;
}


string Parameters::getLegsFileNameWithNoise(double noise)
{
    if (hub)
        return filePath + dataFolder + fileLegs + "_noise_"+ SSTRR(noise)  + "_hub.csv";
    else
        return filePath + dataFolder + fileLegs;
}

void Parameters::setLegsFileName(string fileLegs)
{
    
    this->fileLegs =  fileLegs;
}

string Parameters::getSolutionFileName()
{
    return fileSolution;
}

void Parameters::setSolutionFileName(string fileSolution)
{
    if (hub)
        this->fileSolution =  filePath + dataFolder + fileSolution + "_hub.csv";
    else
        this->fileSolution =  filePath + dataFolder + fileSolution;
    
}

string Parameters::extractingFileName(string str)
{
    string strFileName = str;
    string strPath = filePath + dataFolder;
    string::size_type i = str.find(strPath);
    
    if (i != std::string::npos)
        strFileName.erase(i, strPath.length());
    
    return strFileName;
}
