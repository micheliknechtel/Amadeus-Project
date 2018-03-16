//
//  Airports.cpp
//  GBlockModeling
//
//  Created by Micheli  Knechtel on 24/05/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#include "Airports.hpp"

using namespace std;


Airport::Airport(string airport_code, int total_departure_pax, int total_arrival_pax)
{
    this->airport_code = airport_code;
    this->total_departure_pax = total_departure_pax;
    this->total_arrival_pax = total_arrival_pax;
}

void Airport::to_string()
{
    cout<<airport_code<<" "<<total_departure_pax<<" "<<total_arrival_pax<<endl;
}

int Airport::getTotalDeparturePax()
{
    return total_departure_pax;
}

int Airport::getTotalArrivalPax()
{
    return total_arrival_pax;
}

string Airport::getAirportCode()
{
    return airport_code;
}
