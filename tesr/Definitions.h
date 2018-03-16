//
//  Definitions.h
//  Amadeus
//
//  Created by Micheli  Knechtel on 30/05/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#ifndef Definitions_h
#define Definitions_h

#include <ilcplex/ilocplex.h>
#include <ilconcert/ilomodel.h>
#define SSTR( x ) static_cast< std::ostringstream & >( \
( std::ostringstream() << std::dec << "(" << x << ")" ) ).str()
#define SSTRR( x ) static_cast< std::ostringstream & >( \
( std::ostringstream() << std::dec  << x  ) ).str()
using namespace std;

enum SEVERITY_TYPE {
    DEBUG_01=1,
    DEBUG_02,
    DEBUG_03,
    WARN,
    ERROR
    
};
enum DATA_TYPE {
    AMADEUS_TYPE,
    INSTANCE_GENERATOR_V01,
    INSTANCE_GENERATOR_V02
    
};

#if LOGLEVEL > 0
#define LOG(name, level) if (LOGLEVEL==DEBUG_03)cout<<name; else if(level==LOGLEVEL)cout<<name;
#else
#define LOG(name, level)
#endif

ILOSTLBEGIN

typedef IloArray<IloNumVarArray> IloDoubleVarMatrix;
typedef IloArray<IloNumArray> IloDoubleMatrix;

#define sizeBufferAirport 50
#define sizeBufferItinerary 50
#define sizeBufferLeg 50

#endif /* Definitions_h */
