//
//  Composition.cpp
//  GBlockModeling
//
//  Created by Micheli  Knechtel on 24/05/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#include "Composition.hpp"

Composition::Composition(int o, int d, double alfa)
{
    this->origin_airport = o;
    this->destination_airport = d;
    this->alfa = alfa;
}

int Composition::getOriginAirport()
{
    return origin_airport;
}

int Composition::getDestinationAiport()
{
    return  destination_airport;
}

double Composition::getAlfa()
{
    return alfa;
}
