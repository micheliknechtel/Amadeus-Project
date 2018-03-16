//
//  Airports.hpp
//  GBlockModeling
//
//  Created by Micheli  Knechtel on 24/05/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#ifndef Airports_hpp
#define Airports_hpp

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;
class Airport {
    string airport_code;
    int total_departure_pax;
    int total_arrival_pax;
public:
    Airport(string airport_code, int total_departure_pax, int total_arrival_pax);
    void to_string();
    int getTotalDeparturePax();
    int getTotalArrivalPax();
    string getAirportCode();
  };
#endif /* Airports_hpp */
