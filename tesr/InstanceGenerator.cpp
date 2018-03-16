//
//  InstanceGenerator.cpp
//  Amadeus
//
//  Created by Micheli Knechtel on 09/10/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#include "InstanceGenerator.hpp"
#include "DataManager.hpp"

InstanceGenerator::InstanceGenerator()
{
    numberAirports =  Parameters::getParameters()->getNumberAirports();
    hub = Parameters::getParameters()->getHub();
    noise = Parameters::getParameters()->getNoise();
    loop = Parameters::getParameters()->getLoop();
  
    distress = Parameters::getParameters()->getDistress();
    arrival = new double [numberAirports];
    departure = new double [numberAirports];
    x = new int *[numberAirports];
}

void InstanceGenerator::buildingData()
{
    if(hub)
        creatingHubs();
    
    creatingItineraries();
    adjustingLegPhat();
    adjustingLegsUpperAndLowerBound();
}

void InstanceGenerator::writeFiles()
{
    cout<<"**********************************************"<<endl<<endl;
    cout<<"Generated File's"<<endl<<endl;
    cout<<"**********************************************"<<endl<<endl;
    
   for (int noiseIndex = 0; noiseIndex<noise.size(); noiseIndex++)
       writeAirports(noiseIndex);
    
    for (int noiseIndex = 0; noiseIndex<noise.size(); noiseIndex++)
        writeLegs(noiseIndex);
    
    for (int noiseIndex = 0; noiseIndex<noise.size(); noiseIndex++)
        writeItinerariesWithNoise(noiseIndex);
    
    writeSolution();
    cout<<"**********************************************"<<endl<<endl;
}

void InstanceGenerator::adjustingLegsUpperAndLowerBound()
{
    for (int i =0 ; i<numberAirports; i++)
    {
        arrival[i]=0;
        departure[i]=0;
    }

    for (map<pair<int, int>, Leg>::iterator it = legs.begin(); it!= legs.end(); it++)
    {
        arrival[it->second.getDestinationAirport()]+=it->second.getPhat();
        departure[it->second.getOrigimAirport()]+=it->second.getPhat();
        
        it->second.setPlb(it->second.getPhat() * 0.25);
        
        if (distress!=0)
        {
            double random = (double)rand() / (RAND_MAX + 1.0);
            
            if (distress<random)
            {
                it->second.setPub(it->second.getPhat());
                continue;
            }
        }
        it->second.setPub(it->second.getPhat() * 1.25);
    }
}

void InstanceGenerator::adjustingLegPhat()
{
    LOG("\n--------------------------------------------------------------------------------------------------\n", DEBUG_02);
    LOG("\nAdjusting Leg.Phat\n",DEBUG_02);
    
    for (int i = 0; i<itineraries.size(); i++)
    {
        int o = itineraries[i].getOriginAirport();
        int d = itineraries[i].getDestinationAiport();
        
        double Phat = 0;
        
        LOG("\n--------------------------------------------------------------------------------------------------\n", DEBUG_02);
        LOG("\nitinerary["+SSTRR(i)+"] ->{"+SSTRR(o)+","+SSTRR(d)+"}\n",DEBUG_02);
        
        if( itineraries[i].getConnections().size()==0)
        {
            Phat = itineraries[i].getAlfa() * x[o][d];
            Phat += legs.find(make_pair(o,d))->second.getPhat();
            
            LOG("\nPhat["<<o<<"," <<d<<"] = legs["+SSTRR(o)+","+SSTRR(d)+"].getPhat() + x["+SSTRR(o)+","+SSTRR(d)+"] * itineraries["+SSTRR(i)+"].getAlfa() = "
                +SSTRR(legs.find(make_pair(o, d))->second.getPhat())
                +" + "+ SSTRR(x[o][d])
                +" * "+ SSTRR(itineraries[i].getAlfa())
                +"  = "+ SSTRR(Phat)+"\n",DEBUG_02);
            
            legs.find(make_pair(o,d))->second.setPhat(Phat);
            
        }
        if( itineraries[i].getConnections().size()==1)
        {
            int c1 = itineraries[i].getConnections()[0];
            Phat = itineraries[i].getAlfa()* x[o][d];
            Phat += legs.find(make_pair(o, c1))->second.getPhat();
            
           LOG("Phat["<<o<<"," <<c1<<"] = legs["+SSTRR(o)+","+SSTRR(c1)+"].getPhat() + x["+SSTRR(o)+","+SSTRR(d)+"] * itineraries["+SSTRR(i)+"].getAlfa() = "
                +SSTRR(legs.find(make_pair(o, c1))->second.getPhat())
                +" + "+ SSTRR(x[o][d])
                +" * " + SSTRR(itineraries[i].getAlfa())+"  = "
                + SSTRR(Phat)+"\n",DEBUG_02);
            
            legs.find(make_pair(o, c1))->second.setPhat(Phat);
            
            Phat = (itineraries[i].getAlfa())* x[o][d] ;
            Phat += legs.find(make_pair(c1, d))->second.getPhat();
            
           LOG("Phat["<<c1<<"," <<d<<"] = legs["+SSTRR(c1)+","+SSTRR(d)+"].getPhat() + x["+SSTRR(o)+","+SSTRR(d)+"] * itineraries["+SSTRR(i)+"].getAlfa() = "
                +SSTRR(legs.find(make_pair(c1, d))->second.getPhat())
                +" + "+ SSTRR(x[o][d])
                +" * "+ SSTRR(itineraries[i].getAlfa())
                +"  = "+ SSTRR(Phat)+"\n",DEBUG_02);
            
            legs.find(make_pair(c1, d))->second.setPhat(Phat);
        }
        if( itineraries[i].getConnections().size()==2)
        {
            int c1 = itineraries[i].getConnections()[0];
            int c2 = itineraries[i].getConnections()[1];
            
            Phat = (itineraries[i].getAlfa()) * x[o][d];
            Phat += legs.find(make_pair(o, c1))->second.getPhat();
            
          LOG("Phat["<<o<<"," <<c1<<"] = legs["+SSTRR(o)+","+SSTRR(c1)+"].getPhat() + x["+SSTRR(o)+","+SSTRR(d)+"] * itineraries["+SSTRR(i)+"].getAlfa() = "
                +SSTRR(legs.find(make_pair(o, c1))->second.getPhat())
                +" + "+ SSTRR(x[o][d])
                +" * "+ SSTRR((itineraries[i].getAlfa()))
                +"  = "+ SSTRR(Phat)+"\n",DEBUG_02);
            
            legs.find(make_pair(o, c1))->second.setPhat(Phat);
            
            Phat = (itineraries[i].getAlfa()) * x[o][d];
            Phat += legs.find(make_pair(c1, c2))->second.getPhat();
            
             LOG("Phat["<<c1<<"," <<c2<<"] = legs["+SSTRR(c1)+","+SSTRR(c2)+"].getPhat() + x["+SSTRR(o)+","+SSTRR(d)+"] * itineraries["+SSTRR(i)+"].getAlfa() = "
                +SSTRR(legs.find(make_pair(c1, c2))->second.getPhat())
                +" + "+ SSTRR(x[o][d])
                +" * "+ SSTRR((itineraries[i].getAlfa()))
                +"  = "+ SSTRR(Phat)+"\n",DEBUG_02);
            
            legs.find(make_pair(c1, c2))->second.setPhat(Phat);
            
            Phat = (itineraries[i].getAlfa())* x[o][d];
            Phat += legs.find(make_pair(c2, d))->second.getPhat();
            
             LOG("Phat["<<c2<<"," <<d<<"] = legs["+SSTRR(c2)+","+SSTRR(d)+"].getPhat() + x["+SSTRR(o)+","+SSTRR(d)+"] * itineraries["+SSTRR(i)+"].getAlfa() = "
                +SSTRR(legs.find(make_pair(c2, d))->second.getPhat())
                +" + " + SSTRR(x[o][d]) +" * "
                + SSTRR((itineraries[i].getAlfa()))
                +"  = "+ SSTRR(Phat)+"\n",DEBUG_02);
            
            legs.find(make_pair(c2, d))->second.setPhat(Phat);
        }
    }
    LOG("\n", DEBUG_02);
}

void InstanceGenerator::creatingItineraries()
{
    LOG("\n--------------------------------------------------------------------------------------------------\n", DEBUG_02);
    LOG("\nBuilding Itineraries\n", DEBUG_02);
    
    srand(unsigned(time(0)+DataManager::getDataManager()->fileNumber));
    
    for (int o = 0; o<numberAirports; o++)
    {
        x[o] = new int [numberAirports];
        for (int d = 0; d<numberAirports; d++)
        {
            if (!loop)
                if(o==d)
                {
                    x[o][d] = 0;
                    continue;
                }
            x[o][d] = rand() % 2000 + 1001;
            int numberItineraries = rand() % Parameters::getParameters()->getMaxNumberItineraries() + 1;
            sumAlfa = 0;
            
            LOG("\nitinerary[" + SSTRR(o) + ","+ SSTRR(d)+"].passangersTraveling\t= "+SSTRR(x[o][d])+"\n", DEBUG_02);
            LOG("itinerary[" + SSTRR(o) + ","+ SSTRR(d)+"].numberItineraries\t= "+SSTRR(numberItineraries)+"\n", DEBUG_02);
            
            for (int i =0; i<numberItineraries; i++)
            {
                int numberOfConections = rand() % (int)(Parameters::getParameters()->getMaxNumberConections() - 0 + 1);
                LOG("itinerary[" + SSTRR(o) + ","+ SSTRR(d)+"]["+SSTRR(i)+"].numberOfConection = "+SSTRR(numberOfConections)+"\n", DEBUG_02);
                itineraries.push_back(makeConections(i,numberOfConections, o, d));
            }
            
            LOG("itinerary[" + SSTRR(o) + ","+ SSTRR(d)+"].sumAlfa\t\t\t\t= "+SSTRR(sumAlfa)+ "\n", DEBUG_02);
            
            for (int i = (int) itineraries.size()-numberItineraries; i<itineraries.size(); i++)
            {
                double alfa = itineraries[i].getAlfa()/sumAlfa;
                
//                if (noise!=0)
//                {
//                    double random = (double)rand() / (RAND_MAX + 1.0);
//
//                    if (random > 0.5)
//                        alfaNoise = (1 + noise) * alfaNoise;
//                    else
//                        alfaNoise = (1 - noise) * alfaNoise;
//                }
                
                LOG("itinerary[" + SSTRR(o) + ","+ SSTRR(d)+"]["+SSTRR(numberItineraries-(itineraries.size()-i))+"].alfa\t\t\t\t= "+SSTRR(itineraries[i].getAlfa())+ "\n", DEBUG_02);
                
                itineraries[i].setAlfa(alfa);
                
                LOG("itinerary[" + SSTRR(o) + ","+ SSTRR(d)+"]["+SSTRR(numberItineraries-(itineraries.size()-i))+"].alfaNormalized\t= "+SSTRR(itineraries[i].getAlfa())+ "\n", DEBUG_02);
            }
        }
    }
}

void InstanceGenerator::creatingHubs()
{
    double sum = 0;
    
    radomInteger = new double [numberAirports];
    interval = new double [numberAirports];
  
    LOG("Generating integers ...\n\n[1,100]  = { ", DEBUG_01);
    
    for (int i =0 ; i<numberAirports; i++)
    {
        radomInteger[i] =  rand() % 100 + 1;
        sum += radomInteger[i];
        LOG(SSTRR(radomInteger[i]) + " ", DEBUG_01);
    }

    LOG("}\n\n", DEBUG_01);
    normalizingHubs(sum, -1, false);
}

int InstanceGenerator::searchRange(double value)
{
    int aeroport = 1;
    double sum = 0;
    
    LOG("\nSEARCHING RANGE FOR: ["+SSTRR(value)+"]\n\nAeroport's Range:\n\n", DEBUG_01);
    for (int i = 0; i<numberAirports; i++)
    {
        LOG(SSTRR(i)+" -> ["+SSTRR(interval[i])+"]\n", DEBUG_01);
        if (value <  interval[i] || value == interval[i])
        {
            aeroport =  i;
            break;
        }
    }
    
    LOG("\n["+SSTRR(value)+"]"+" -> ["+SSTRR(aeroport)+"]\n", DEBUG_01);
    for (int i = 0; i<numberAirports; i++)
        if (i!=aeroport)
            sum += radomInteger[i];
    
    LOG("\n* Re-Normalizing values !!\n\n1) Removing aeroport["+SSTRR(aeroport)+"]"+" -> SUM = "+SSTRR(sum)+"\n\n", DEBUG_01);
    normalizingHubs(sum, aeroport, true);
    return aeroport;
}

void InstanceGenerator::normalizingHubs(double sum, int aeroport, bool renormalizing)
{
    for (int i = 0; i<numberAirports; i++)
    {
        if (renormalizing)
        {
            if (i!=aeroport)
                interval[i] = radomInteger[i]/sum;
            else
                interval[i] =  0;
        }
        else
            interval[i] = radomInteger[i]/sum;
        LOG("randomInteger["+SSTRR(i)+"] = "+SSTRR(radomInteger[i])+"\t\tinterval = " +SSTRR(interval[i])+"\n", DEBUG_01);
    }
    
    LOG("\nAdjusting intervals\n\n", DEBUG_01);
    
    for (int i =0 ; i<numberAirports-1; i++)
    {
        interval[i+1] += interval[i];
    }
    
    if (renormalizing)
        interval[aeroport] = 0;
  
    for (int i =0 ; i<numberAirports; i++)
        LOG("range: ["+SSTRR(interval[i])+"] -> aeroport  = "+SSTRR(i)+"\n", DEBUG_01);
    
    LOG("\n", DEBUG_01);
}

void InstanceGenerator::writeAirports(int noiseIndex)
{
    ofstream airportFile;
        
    airportFile.open(Parameters::getParameters()->getAirportFileNameWithNoise(noise[noiseIndex]).c_str());
    
    if(!airportFile.is_open())
    {
        cout<<"Not able to open file "<<Parameters::getParameters()->getAirportFileNameWithNoise(noise[noiseIndex])<<endl;
        return;
    }
    cout.precision(3);
    cout.width(10);
    
    for (int i =0 ; i<numberAirports; i++)
    {
        double value = 1;
        if (noise[noiseIndex]!=0)
        {
            double random = (double)rand() / (RAND_MAX + 1.0);
            if (random > 0.5)
                value = (1 + noise[noiseIndex]) ;
            else
                value = (1 - noise[noiseIndex]);
            
        }
        airportFile<<i<<" "<<(departure[i] * value)<<" "<<(arrival[i]* value) <<endl;
    }
    
    cout << Parameters::getParameters()->extractingFileName( Parameters::getParameters()->getAirportFileNameWithNoise(noise[noiseIndex]))<<" has ...";
    cout << " (" <<numberAirports <<  " airports)" <<endl;
    airportFile.close();
}

void InstanceGenerator::writeSolution()
{
    
    ofstream solutionFile;
    solutionFile.open (Parameters::getParameters()->getSolutionFileName().c_str());
    
    if(!solutionFile.is_open())
    {
        cout<<"Not able to open file "<<Parameters::getParameters()->getSolutionFileName()<<endl;
        return;
    }
    
    cout << Parameters::getParameters()->extractingFileName(Parameters::getParameters()->getSolutionFileName())<<" has...";
    cout << " (" << numberAirports << " lines)" << endl<<endl;
    
    for (int o = 0; o<numberAirports; o++)
    {
        for (int d = 0; d<numberAirports; d++)
        {
            solutionFile<<x[o][d]<<" ";
        }
        solutionFile<<endl;
    }
    solutionFile.close();
}

void InstanceGenerator::writeLegs(int noiseIndex)
{
    ofstream legFile;
    legFile.open(Parameters::getParameters()->getLegsFileNameWithNoise(noise[noiseIndex]).c_str());
    
    if(!legFile.is_open())
    {
        cout<<"Not able to open file "<<Parameters::getParameters()->getLegsFileNameWithNoise(noise[noiseIndex])<<endl;
        return;
    }
    cout << Parameters::getParameters()->extractingFileName(Parameters::getParameters()->getLegsFileNameWithNoise(noise[noiseIndex]))<<" has...";
    cout << " (" << legs.size() <<  " lines)" <<endl;
    
    for (map<pair<int, int>, Leg>::iterator it = legs.begin(); it!= legs.end(); it++)
        legFile<<it->second.toString(noise[noiseIndex])<<endl;
    
    legFile.close();
}


void InstanceGenerator::writeItinerariesWithNoise(int noiseIndex)
{
    ofstream itineraryFile;
    itineraryFile.open (Parameters::getParameters()->getItineraryFileNameWithNoise(noise[noiseIndex]).c_str());
    
    
    if(!itineraryFile.is_open())
    {
        cout<<"Not able to open file "<<Parameters::getParameters()->getItineraryFileNameWithNoise(noise[noiseIndex]).c_str()<<endl;
        return;
    }
    
    for (int i = 0; i<itineraries.size(); i++)
        itineraryFile << itineraries[i].toStringWithNoise(noise[noiseIndex])<<endl;
    
    
    cout << Parameters::getParameters()->extractingFileName(Parameters::getParameters()->getItineraryFileNameWithNoise(noise[noiseIndex]))<<" has ...";
    cout << " (" << itineraries.size() <<  " lines)" <<endl;
    
    itineraryFile.close();
}

void InstanceGenerator::insertLeg(int o, int d)
{
    if(legs.find(make_pair(o, d)) == legs.end())
        legs.insert(pair<pair<int,int>, Leg>(pair<int,int>(o,d), Leg(o, d, 0, 0, 0, 1)));
}

Itinerary InstanceGenerator::makeConections(int index,int numberOfConections, int o, int d)
{
    double alfa = 1;
    
    if (numberOfConections !=0)
    {
       //Philippe way alfa = 1.0/(numberOfConections+1);
        alfa = 1.0/numberOfConections+1;

    }
    
    Itinerary * itinerary = new Itinerary(o, d, alfa);
    int conection = o, conectionTemp = o;
    
    for (int i = 0; i<numberOfConections; i++)
    {
        if (hub)
            conection =  searchRange((double)rand() / (RAND_MAX + 1.0));
        else
            conection = rand() % numberAirports;
        
        while(o==conection || d==conection || conection == conectionTemp)
        {
            if (hub)
                conection =  searchRange((double)rand() / (RAND_MAX + 1.0));
            else
                conection = rand() %numberAirports;
        }
        
        insertLeg(conectionTemp,conection);
        LOG("itinerary["+SSTRR(o)+","+SSTRR(d)+"]["+SSTRR(index)+"].conection_"+SSTRR(i)+"\t\t= " + SSTRR(conection)+"\n", DEBUG_02);
        itinerary->AddConnection(conection);
        conectionTemp = conection;
    }
    insertLeg(conection,d);
    sumAlfa +=alfa;
    return *itinerary;
}
