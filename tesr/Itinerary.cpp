//
//  Itinerary.cpp
//  GBlockModeling
//
//  Created by Micheli  Knechtel on 24/05/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#include "Itinerary.hpp"


Itinerary::Itinerary(int origin_airport, int destination_airport, double alfa)
{
    this->origin_airport = origin_airport;
    this->destination_airport = destination_airport;
    this->alfa = alfa;
}

int Itinerary::getOriginAirport()
{
    return origin_airport;
}

int Itinerary::getDestinationAiport()
{
    return  destination_airport;
}

double Itinerary::getAlfa()
{
    return alfa;
}

void Itinerary::setAlfa(double alfa)
{
    this->alfa = alfa;
}


vector<int> Itinerary::getConnections()
{
    return connections;
}

void Itinerary::AddConnection(int c)
{
     connections.push_back(c);
}

string Itinerary::toString() 
{
    
   
    string str = SSTRR(origin_airport) + " " ;
    
    for (int i =0 ; i<connections.size(); i++)
        str  += SSTRR(connections[i])+ " " ;
   
    if (connections.size()==1)
         str  += " ";
    
    if (connections.size()==0)
        str  += "  ";

    str  += SSTRR(destination_airport) + " " + SSTRR(alfa)+" -1";

    
    return str;
}

string Itinerary::toStringWithNoise(double noise)
{
    string str = SSTRR(origin_airport) + " " ;
    
    for (int i =0 ; i<connections.size(); i++)
        str  += SSTRR(connections[i])+ " " ;
    
    if (connections.size()==1)
        str  += " ";
    
    if (connections.size()==0)
        str  += "  ";
    
    if (noise!=0)
    {
        double random = (double)rand() / (RAND_MAX + 1.0);
        double alfaNoise;
        
        if (random > 0.5)
            alfaNoise = (1 + noise) * alfa;
        else
            alfaNoise = (1 - noise) * alfa;
        
        str  += SSTRR(destination_airport) + " " + SSTRR(alfaNoise)+" -1";
    }
    else
        str  += SSTRR(destination_airport) + " " + SSTRR(alfa)+" -1";
    
    
    return str;
}
