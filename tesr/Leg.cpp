//
//  Leg.cpp
//  GBlockModeling
//
//  Created by Micheli  Knechtel on 24/05/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#include "Leg.hpp"

Leg::Leg(int origim_airport,
         int destination_airport,
         double p_ub,
         double p_lb,
         double p_hat,
         double beta)
{
    this->origim_airport = origim_airport;
    this->destination_airport = destination_airport;
    this->p_ub = p_ub;
    this->p_lb = p_lb;
    this->p_hat = p_hat;
    this->beta = beta;
}

double Leg::getPub()
{
    return p_ub;
}

double Leg::getPlb()
{
    return p_lb;
}

double Leg::getPhat()
{
    return p_hat;
}

double Leg::getBeta()
{
    return beta;
}

int Leg::getDestinationAirport()
{
    return destination_airport;
}

int Leg::getOrigimAirport()
{
    return origim_airport;
}

vector<Composition>  Leg::getComposition()
{
    return composition;
}

void Leg::AddComposition(Composition comp)
{
    composition.push_back(comp);
}

void Leg::setPub(double p_ub)
{
    this->p_ub = p_ub;
}

void Leg::setPlb(double p_lb)
{
    this->p_lb = p_lb;
}

void Leg::setPhat(double p_hat)
{
    this->p_hat = p_hat;
}
void Leg::setBeta(double beta)
{
    this->beta = beta;
}

string Leg::toString(double noise)
{
    double p_hatNoise = p_hat;
    if(noise!=0)
    {
        double random = (double)rand() / (RAND_MAX + 1.0);
        if (random > 0.5)
            p_hatNoise = (1 + noise) * p_hat;
        else
            p_hatNoise = (1 - noise) * p_hat;
    }
    string str =  SSTRR(origim_airport) + " " + SSTRR(destination_airport)+ " " + SSTRR(p_lb)+ " " + SSTRR(p_hatNoise)+" " + SSTRR(p_ub)+" " + SSTRR(beta);
    return str;
}
