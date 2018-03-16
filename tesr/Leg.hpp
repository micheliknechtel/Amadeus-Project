//
//  Leg.hpp
//  GBlockModeling
//
//  Created by Micheli  Knechtel on 24/05/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#ifndef Leg_hpp
#define Leg_hpp

#include <stdio.h>
#include "Composition.hpp"
#include <vector>
#include <string>
#include "Definitions.h"

class Leg {
    double p_ub;
    double p_lb;
    double p_hat;
    double beta;
    int destination_airport;
    int origim_airport;
    vector<Composition>composition;
public:
    Leg(int origim_airport,
        int destination_airport,
        double p_ub,
        double p_lb,
        double p_hat,
        double beta);
    double getPub();
    double getPlb();
    double getPhat();
    double getBeta();
    int getDestinationAirport();
    int getOrigimAirport();
    vector<Composition> getComposition();
    void AddComposition(Composition comp);
    void setPub(double p_ub);
    void setPlb(double p_lb);
    void setPhat(double p_hat);
    void setBeta(double beta);
    string toString(double noise);
    
};
#endif /* Leg_hpp */
