//
//  Composition.hpp
//  GBlockModeling
//
//  Created by Micheli  Knechtel on 24/05/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#ifndef Composition_hpp
#define Composition_hpp

#include <stdio.h>

class Composition {
    int origin_airport;
    int destination_airport;
    double alfa;
public:
    Composition(int origin_airport, int destination_airport, double alfa);
    int getOriginAirport();
    int getDestinationAiport();
    double getAlfa();
};

#endif /* Composition_hpp */
