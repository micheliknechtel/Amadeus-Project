//
//  DataManager.cpp
//  tesr
//
//  Created by Micheli  Knechtel on 18/04/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//


#include "DataManager.hpp"


DataManager* DataManager::dataManager = NULL;

DataManager* DataManager::getDataManager()
{
    if(!dataManager)
    {
        dataManager = new DataManager;
    }
    return dataManager;
}

void DataManager::readAirportsFile(bool containsHeader)
{
    cout << Parameters::getParameters()->extractingFileName(Parameters::getParameters()->getAirportFileName())<<" ...";
    FILE * fp;
    fp = fopen (Parameters::getParameters()->getAirportFileName().c_str(), "r");
    char bufferContent[sizeBufferAirport];
    char *bufferPointer;
    int a,d;
    
    if(containsHeader)
        fgets(bufferContent, sizeBufferAirport, fp);
    
    if(fp==NULL)
    {
        cout<<"Not able to open the file "<<endl;
        return;
    }
    
    while(1)
    {
        fgets(bufferContent, sizeBufferAirport, fp);
        bufferPointer = bufferContent;
        
        if(feof(fp))
        {
            break;
        }
        
        char *tokenA = strsep(&bufferPointer, ",");
        char *tokenB = strsep(&bufferPointer, ",");
        char *tokenC = strsep(&bufferPointer, ",");
        
        d = strcmp(tokenB,"")!=0 ? atoi(tokenB): -1;
        a = strcmp(tokenC,"")!=0 ? atoi(tokenC): -1;
        
        
        if(apCodeMap.find(string(tokenA) ) !=  apCodeMap.end() )
        {
            cout<<"Duplicate airport "<<string(tokenA)<<endl;
            exit(1);
        }
        
        airports.push_back(Airport(string(tokenA), d, a));
        apCodeMap.insert(pair<string,int>(string(tokenA), (int) airports.size()-1));
        codeApMap.insert(pair<int,string>((int) airports.size()-1, string(tokenA)));
    }
    fclose(fp);
    cout << " (" << airports.size() <<  " airports read)" << endl;
};


/* Read leg datafile in which each line is in the following format:
 * airport1 airport2 airline upper_bound lower_bound estimation confidence
 */
void DataManager::readLegsFileM(bool containsHeader)
{
    cout<<Parameters::getParameters()->extractingFileName(Parameters::getParameters()->getLegsFileName())<<" ...";

    FILE * fp;
    fp = fopen (Parameters::getParameters()->getLegsFileName().c_str(), "r");
    char bufferContent[sizeBufferLeg];
    char *bufferPointer;
    int o,d;
    double p_ub, p_lb, p_hat,beta;
    
    if(containsHeader)
        fgets(bufferContent, sizeBufferLeg, fp);
    
    while(1)
    {
        fgets(bufferContent, sizeBufferLeg, fp);
        bufferPointer = bufferContent;
        
        if(feof(fp))
        {
            break;
        }
        
        char *tokenA = strsep(&bufferPointer, ",");
        char *tokenB = strsep(&bufferPointer, ",");
        char *tokenC = strsep(&bufferPointer, ",");
        char *tokenD = strsep(&bufferPointer, ",");
        char *tokenE = strsep(&bufferPointer, ",");
        char *tokenF = strsep(&bufferPointer, ",");
        
        if (apCodeMap.find(string(tokenA) ) ==  apCodeMap.end())
        {
            apCodeMap.insert(pair<string,int>(string(tokenA), (int) airports.size()-1));
        }
        
        if (apCodeMap.find(string(tokenB) ) ==  apCodeMap.end())
        {
            apCodeMap.insert(pair<string,int>(string(tokenB), (int) airports.size()-1));
        }
        
        o = apCodeMap.at(string(tokenA));
        d = apCodeMap.at(string(tokenB));
        
        
        // This part of the code merges and update equals legs from airlines...
        if(legs.find(make_pair(o, d))!=legs.end())
        {
            Leg legAux = legs.at(make_pair(o,d));
            (legs.at(make_pair(o,d))).setPub((legs.at(make_pair(o,d))).getPub() + (double) atof(tokenD));
            (legs.at(make_pair(o,d))).setPlb((legs.at(make_pair(o,d))).getPlb() + (double) atof(tokenE));
            (legs.at(make_pair(o,d))).setPhat((legs.at(make_pair(o,d))).getPhat() + (double) atof(tokenF));
            
            // We are keeping the maximum beta from all airlines while merging ...
            if (atof(tokenF)>(legs.at(make_pair(o,d))).getBeta())
            {
                (legs.at(make_pair(o,d))).setBeta(atof(tokenF));
            }
            
            continue;
        }
        p_lb = strcmp(tokenE,"")!=0 ? (double)atof(tokenC):  -1;
        p_hat = strcmp(tokenF,"")!=0 ? (double)atof(tokenD): -1;
        p_ub = strcmp(tokenD,"")!=0 ? (double) atof(tokenE):  -1;
        beta = strcmp(tokenF,"")!=0 ? (double)atof(tokenF):  -1;

        legs.insert(pair<pair<int,int>, Leg>(pair<int,int>(o,d), Leg(o, d, p_ub, p_lb, p_hat, beta)));
    }
    fclose(fp);
    cout << " (" <<legs.size() <<  " legs read)" << endl;
};

/* Read leg datafile in which each line is in the following format:
 * airport1 airport2 airline upper_bound lower_bound estimation confidence
 */
void DataManager::readLegsFileT(bool containsHeader)
{
    cout<<Parameters::getParameters()->extractingFileName(Parameters::getParameters()->getLegsFileName())<<endl;
    
    FILE * fp;
    fp = fopen (Parameters::getParameters()->getLegsFileName().c_str(), "r");
    char bufferContent[sizeBufferLeg];
    char *bufferPointer;
    int o,d;
    double p_ub, p_lb, p_hat,beta;
    
    if(containsHeader)
        fgets(bufferContent, sizeBufferLeg, fp);
    
    while(1)
    {
        fgets(bufferContent, sizeBufferLeg, fp);
        bufferPointer = bufferContent;
        
        if(feof(fp))
        {
            break;
        }
        
        char *tokenA = strsep(&bufferPointer, ",");
        char *tokenB = strsep(&bufferPointer, ",");
        char *tokenC = strsep(&bufferPointer, ","); tokenC = NULL; // ignoring Airline Field;
        char *tokenD = strsep(&bufferPointer, ",");
        char *tokenE = strsep(&bufferPointer, ",");
        char *tokenF = strsep(&bufferPointer, ",");
        char *tokenG = strsep(&bufferPointer, ",");
        
        if (apCodeMap.find(string(tokenA) ) ==  apCodeMap.end())
        {
            apCodeMap.insert(pair<string,int>(string(tokenA), (int) airports.size()-1));
        }
        
        if (apCodeMap.find(string(tokenB) ) ==  apCodeMap.end())
        {
            apCodeMap.insert(pair<string,int>(string(tokenB), (int) airports.size()-1));
        }
        
        o = apCodeMap.at(string(tokenA));
        d = apCodeMap.at(string(tokenB));
        
        
        // This part of the code merges and update equals legs from airlines...
        if(legs.find(make_pair(o, d))!=legs.end())
        {
            Leg legAux = legs.at(make_pair(o,d));
            (legs.at(make_pair(o,d))).setPub((legs.at(make_pair(o,d))).getPub() + (double) atof(tokenD));
            (legs.at(make_pair(o,d))).setPlb((legs.at(make_pair(o,d))).getPlb() + (double) atof(tokenE));
            (legs.at(make_pair(o,d))).setPhat((legs.at(make_pair(o,d))).getPhat() + (double) atof(tokenF));
            
            // We are keeping the maximum beta from all airlines while merging ...
            if (atof(tokenG)>(legs.at(make_pair(o,d))).getBeta())
            {
                (legs.at(make_pair(o,d))).setBeta(atof(tokenG));
            }
            
            continue;
        }
        
        p_ub = strcmp(tokenD,"")!=0 ? (double) atof(tokenD):  -1;
        p_lb = strcmp(tokenE,"")!=0 ? (double)atof(tokenE):  -1;
        p_hat = strcmp(tokenF,"")!=0 ? (double)atof(tokenF): -1;
        beta = strcmp(tokenG,"")!=0 ? (double)atof(tokenG):  -1;
        
        legs.insert(pair<pair<int,int>, Leg>(pair<int,int>(o,d), Leg(o, d, p_ub, p_lb, p_hat, beta)));
    }
    fclose(fp);
    cout << " (" << airports.size() <<  " airports read)" << endl;
};

/* Read leg datafile in which each line is in the following format:
 * airport1 airport2 lower_bound estimation upper_bound
 */
void DataManager::readLegsFileZ(bool containsHeader)
{
    FILE * fp;
    cout<<Parameters::getParameters()->extractingFileName(Parameters::getParameters()->getLegsFileName());
    fp = fopen (Parameters::getParameters()->getLegsFileName().c_str(), "r");
    char bufferContent[sizeBufferLeg];
    char *bufferPointer;
    int o,d;
    double p_ub, p_lb, p_hat,beta;
    
    if(containsHeader)
        fgets(bufferContent, sizeBufferLeg, fp);
    
    while(1)
    {
        fgets(bufferContent, sizeBufferLeg, fp);
        bufferPointer = bufferContent;
        
        if(feof(fp))
        {
            break;
        }
        
        /* These names are used to be coherent with function readLegsFile */
        char *tokenA = strsep(&bufferPointer, ",");
        char *tokenB = strsep(&bufferPointer, ",");
        char *tokenE = strsep(&bufferPointer, ",");
        char *tokenF = strsep(&bufferPointer, ",");
        char *tokenD = strsep(&bufferPointer, ",");
        
        /* If tokenA is not included in the list of airports */
        if (apCodeMap.find(string(tokenA) ) ==  apCodeMap.end())
        {
            apCodeMap.insert(pair<string,int>(string(tokenA), (int) airports.size()-1));
        }
        
        if (apCodeMap.find(string(tokenB) ) ==  apCodeMap.end())
        {
            apCodeMap.insert(pair<string,int>(string(tokenB), (int) airports.size()-1));
        }
        
        o = apCodeMap.at(string(tokenA));
        d = apCodeMap.at(string(tokenB));
        
        
        // This part of the code merges and update equals legs from airlines...
        if(legs.find(make_pair(o, d))!=legs.end())
        {
            Leg legAux = legs.at(make_pair(o,d));
            (legs.at(make_pair(o,d))).setPub((legs.at(make_pair(o,d))).getPub() + (double) atof(tokenD));
            (legs.at(make_pair(o,d))).setPlb((legs.at(make_pair(o,d))).getPlb() + (double) atof(tokenE));
            (legs.at(make_pair(o,d))).setPhat((legs.at(make_pair(o,d))).getPhat() + (double) atof(tokenF));
            
            continue;
        }
        
        p_ub = strcmp(tokenD,"")!=0 ? (double) atof(tokenD):  -1;
        p_lb = strcmp(tokenE,"")!=0 ? (double)atof(tokenE):  -1;
        p_hat = strcmp(tokenF,"")!=0 ? (double)atof(tokenF): -1;
        beta = 1.0;
        
        legs.insert(pair<pair<int,int>, Leg>(pair<int,int>(o,d), Leg(o, d, p_ub, p_lb, p_hat, beta)));
    }
    fclose(fp);
    cout << " (" << DataManager::getDataManager()->getLegs().size() <<  " legs read)" << endl;
};


void DataManager::readItineraryFile(bool containsHeader)
{
    
    FILE * fp;
    cout << Parameters::getParameters()->extractingFileName(Parameters::getParameters()->getItineraryFileName())<<" ...";
    fp = fopen (Parameters::getParameters()->getItineraryFileName().c_str(), "r");
    char bufferContent[sizeBufferItinerary];
    char *bufferPointer;
    int o,d;
    double alfa;
    
    if(containsHeader)
        fgets(bufferContent, 500, fp);
    
    
    while(1)
    {
        fgets(bufferContent, 500, fp);
        bufferPointer = bufferContent;
        
        if(feof(fp))
        {
            break ;
        }
        
        char *tokenA = strsep(&bufferPointer, ",");
        char *tokenB = strsep(&bufferPointer, ",");
        char *tokenC = strsep(&bufferPointer, ",");
        char *tokenD = strsep(&bufferPointer, ",");
        char *tokenE = strsep(&bufferPointer, ",");
        
        if(!(apCodeMap.find(string(tokenA)) !=  apCodeMap.end()) && strcmp(tokenA,""))
        {
            cout<<"readItineraryFile Error: code does not exist for tokenA or itsEmpt!!! "<<string(tokenA)<<endl;
            exit(1);
        }
        
        if(!(apCodeMap.find(string(tokenD))!= apCodeMap.end()) && strcmp(tokenD,""))
        {
            cout<<"readItineraryFile Error: code does not exist for tokenB !!! "<<string(tokenD)<<endl;
            exit(1);
        }
        
        o = apCodeMap[string(tokenA)];
        d = apCodeMap[string(tokenD)];
        
        alfa = strcmp(tokenE,"")!=0 ?(double) atof(tokenE):  -1;
        
        Itinerary itinerary = Itinerary(o, d, alfa);
        
        
        if (strcmp(tokenB,"")!=0)
        {
           itinerary.AddConnection(apCodeMap[string(tokenB)]);
        }
        
        if (strcmp(tokenC,"")!=0)
        {
            itinerary.AddConnection(apCodeMap[string(tokenC)]);
        }
        
        itineraries.push_back(itinerary);
        
        
    }
    fclose(fp);
    cout << " (" << itineraries.size() <<  " itineraries read)" << endl;

};

void DataManager::parseRoutesToAlfa()
{
    
    cout<<"**********************************************"<<endl<<endl;
    cout<<"Parsing Routes";
    
    time_t startTime, endTime;
    startTime = time(&startTime);
    
    int o;
    int d;
    
    
    for (int i= 0; i<itineraries.size(); i++)
    {
        o = itineraries[i].getOriginAirport();
        d = itineraries[i].getDestinationAiport();

        double alfa = itineraries[i].getAlfa();
        
        if (itineraries[i].connections.size()==0)
        {
            legs.at(make_pair(o,d)).AddComposition(Composition(o,d, alfa));
        }
        if (itineraries[i].getConnections().size()==1)
        {
            int c1 = itineraries[i].getConnections()[0];
            legs.at(make_pair(o,c1)).AddComposition(Composition(o,d, alfa));
            legs.at(make_pair(c1,d)).AddComposition(Composition(o,d, alfa));
        }
        else if (itineraries[i].getConnections().size()==2)
        {
            int c1 = itineraries[i].getConnections()[0];
            int c2 = itineraries[i].getConnections()[1];
            
            legs.at(make_pair(o,c1)).AddComposition(Composition(o,d, alfa));
            legs.at(make_pair(c1,c2)).AddComposition(Composition(o,d, alfa));
            legs.at(make_pair(c2,d)).AddComposition(Composition(o,d, alfa));
        }
    }
    //    printLegs();

    endTime = time(&endTime);
    cout<<" executed in "<<difftime(endTime, startTime)<<" seconds!"<<endl<<endl;
    cout<<"**********************************************"<<endl<<endl;

};

void DataManager::alfaVerification()
{
    vector<vector<double>>alfaMatrix(airports.size(),vector<double>(airports.size()));
    
    for (int i= 0; i<airports.size(); i++)
        for (int j= 0; j<airports.size(); j++)
            alfaMatrix[i][j]=0;
    
    for (int i= 0; i<itineraries.size(); i++)
    {
        int o = itineraries[i].getOriginAirport();
        int d = itineraries[i].getDestinationAiport();
        alfaMatrix[o][d]+=itineraries[i].getAlfa();
        LOG("itineraries["+SSTRR(o)+","+SSTRR(d)+"].getAlfa() = "+ SSTRR(itineraries[i].getAlfa())+"\t sum = \t"+SSTRR(alfaMatrix[o][d])+" nbConections = "+SSTRR(itineraries[i].getConnections().size())+"\n",DEBUG_02);
    }
    
    cout<<endl<<"Checking Alphas:"<<endl<<endl;
    
    for (int i= 0; i<airports.size()-1; i++)
    {
        double sum = 0;
        for (int j= 0; j<airports.size(); j++)
        {
            sum+=alfaMatrix[i][j];
            cout << setprecision(2)<<fixed<< alfaMatrix[i][j]<< " + ";
        }
        cout << setprecision(2)<<fixed<< alfaMatrix[i][airports.size()-1]<< " = "<<sum<<endl;
    }
    cout<<endl;
}


void DataManager::printLegs()
{
    cout<<endl<<endl;
    cout<<"printLegs"<<endl;
    map<pair<int, int>, Leg>::iterator it;
    
    for (it = legs.begin();it!= legs.end(); it++)
    {
        int nbPaths = (int) it->second.getComposition().size();
        cout<<it->first.first<<" "<<it->first.second<<endl;
        
        for(int j=0; j < nbPaths; j++)
        {
            int k1 = it->second.getComposition().at(j).getOriginAirport();
            int k2 = it->second.getComposition().at(j).getDestinationAiport();
            cout<<" o = "<<k1<<" d = "<< k2<<" alfa = "<<it->second.getComposition().at(j).getAlfa()<<endl;
        }
    }
}

void DataManager::loadData(DATA_TYPE data_type)
{
    cout<<"Reading files"<<endl<<endl;
    cout<<"**********************************************"<<endl<<endl;
    
    time_t startTime, endTime;
    startTime = time(&startTime);
    
    if (data_type==INSTANCE_GENERATOR_V01)
        DataManager::getDataManager()->readAirportsFile(true);
    else
        DataManager::getDataManager()->readAirportsFile(false);
    
    if (data_type==AMADEUS_TYPE)
        DataManager::getDataManager()->readLegsFileZ(false);
    
    if (data_type==INSTANCE_GENERATOR_V01)
        DataManager::getDataManager()->readLegsFileT(true);

    if (data_type==INSTANCE_GENERATOR_V02)
        DataManager::getDataManager()->readLegsFileM(false);

    DataManager::getDataManager()->readItineraryFile(false);
    
    endTime = time(&endTime);
    cout<<endl<<"Loading process done in "<<difftime(endTime, startTime)<<" seconds!"<<endl<<endl;
}


void DataManager::printAirports()
{
    cout<<endl<<endl;
    
    for (int i=0; i < airports.size(); i++)
    {
        cout<<airports[i].getAirportCode()<<endl;
    }
}

void DataManager::diferrence(LinearModel *linear, QuadraticModel *quadratic)
{
    
    cout<<endl<<endl;
    
    for (int i =0; i<airports.size(); i++)
    {
        for (int j =0; j<airports.size(); j++)
        {
            cout<<setprecision(numeric_limits<double>::digits10 + 1)<<linear->getMatrix()[i][j]- quadratic->getMatrix()[i][j]<<" ";
            
        }
        cout<<endl;
    }
}

void DataManager::differenceFloor(LinearModel *linear, QuadraticModel *quadratic)
{
    
    cout<<endl<<endl;
    bool equal = true;
    
    for (int i =0; i<airports.size(); i++)
    {
        for (int j =0; j<airports.size(); j++)
        {
            if (floor(linear->getMatrix()[i][j])!= floor(quadratic->getMatrix()[i][j]))
            {
                cout<<"linear["<<i<<"]["<<j<<"] = "<<floor(linear->getMatrix()[i][j])<<" != "<<"quadratic["<<i<<"]["<<j<<"] = "<<floor(quadratic->getMatrix()[i][j])<<endl;
                equal = false;
            }
        }
        if (!equal) {
            cout<<endl;
        }
    }
    if (equal) {
        cout<<"Both models has similar solutions, with a difference smaller than one for each entry !!";
    }
}

vector<Airport> DataManager::getAirports()
{
    return airports;
}

vector<Itinerary> DataManager::getItineraries()
{
    return itineraries;
}

map<pair<int, int>, Leg>  DataManager::getLegs()
{
    return legs;
}

string DataManager::currentDateTime()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    return buf;
}

void DataManager::isTotalDepartureSmallerSumUpperBounds()
{
    cout<<"**********************************************"<<endl<<endl;
    cout<<"Verifying limits (totalDeparture <= sumUpperBounds) "<<endl<<endl;
    
    double totalDeparture  = 0;
    double totalArrivel  = 0;
    
    for (int i=0; i < airports.size(); i++)
    {
        totalDeparture += airports[i].getTotalDeparturePax();
        totalArrivel += airports[i].getTotalArrivalPax();
    }
    map<pair<int, int>, Leg>::iterator it;
    map<pair<int, int>, Leg> mapAux = DataManager::getDataManager()->getLegs();
    
    double sumUpperBounds = 0;
    double sumLowerBounds = 0;
    for (it = mapAux.begin();it!= mapAux.end(); it++)
    {
        sumUpperBounds += it->second.getPub();
        sumLowerBounds += it->second.getPlb();
    }
    
    cout<<"totalDeparture = "<<totalDeparture<<endl<<"totalArrivel   = "<<totalArrivel<<endl<<"sumUpperBounds = "<<sumUpperBounds<<endl<<"sumLowerBounds = "<<sumLowerBounds<<endl<<endl;
    
}
void DataManager::legsVerification()
{
    
    cout<<"**********************************************"<<endl<<endl;
    cout<<"Verifying legs "<<endl<<endl;
    map<pair<int, int>, Leg>::iterator it;
    map<pair<int, int>, Leg> mapAux = DataManager::getDataManager()->getLegs();
    
    for (it = mapAux.begin();it!= mapAux.end(); it++)
    {
        cout<<"leg["<<it->first.first<<","<< it->first.second<<"]"<<endl;
    }
    cout<<endl;
}

void DataManager::resetData()
{
    vector<Itinerary> itineraries;
    vector<Airport> airports;
    map<pair<int, int>, Leg> legs;
    map<string,int> apCodeMap;

    this->apCodeMap= apCodeMap;
    this->itineraries = itineraries;
    this->legs = legs;
    this->airports = airports;



}
