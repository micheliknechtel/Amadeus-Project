#include "Parameters.hpp"
#include "InstanceGenerator.hpp"
#include "DataManager.hpp"

int main (int argc, char **argv)
{
    DATA_TYPE dataType = INSTANCE_GENERATOR_V02;
    
    Parameters::getParameters()->setFilePath("/Users/micheliknechtel/Documents/xCode/amadeus__17_oct/");
    
    if (dataType == INSTANCE_GENERATOR_V01)
    {
        Parameters::getParameters()->setDataFolder("instanceGenerator_V01/5");
        Parameters::getParameters()->setAirportFileName("airports.csv");
        Parameters::getParameters()->setLegsFileName("legs.csv");
        Parameters::getParameters()->setItineraryFileName("itineraries.csv");
        Parameters::getParameters()->setSolutionFileName("solution.csv");
        DataManager::getDataManager()->loadData(INSTANCE_GENERATOR_V01);
    }
    
    if (dataType == INSTANCE_GENERATOR_V02)
    {
        int lb = 0, ub = 10;
        vector<double> noise;
        noise.push_back(0);
        noise.push_back(0.03);
        noise.push_back(0.05);
        noise.push_back(0.1);
        noise.push_back(0.2);
        
        for (int size = 20;size<= 100; size+=10)
            for (int i = lb; i<ub; i++)
            {
                DataManager::getDataManager()->fileNumber = i+size;
                Parameters::getParameters()->setNumberAirports(size);
                Parameters::getParameters()->setMaxNumberItineraries(3);
                Parameters::getParameters()->setMaxNumberConections(2);
                Parameters::getParameters()->setHub(true);
                Parameters::getParameters()->setLoop(false);
                Parameters::getParameters()->setNoise(noise);
                Parameters::getParameters()->setDistress(0);
                Parameters::getParameters()->setDataFolder("instanceGenerator_V02/" + SSTRR(Parameters::getParameters()->getNumberAirports())+"/");
                Parameters::getParameters()->setAirportFileName("airports_" + SSTRR(i));
                Parameters::getParameters()->setLegsFileName("legs_" + SSTRR(i));
                Parameters::getParameters()->setItineraryFileName("itineraries_" + SSTRR(i));
                Parameters::getParameters()->setSolutionFileName("solution_" + SSTRR(i));
                
                InstanceGenerator *instanceGenerator =  new InstanceGenerator();
                instanceGenerator->buildingData();
                instanceGenerator->writeFiles();
                DataManager::getDataManager()->resetData();
            }
    }
    
    if (dataType == AMADEUS_TYPE)
    {
        Parameters::getParameters()->setDataFolder("AmadeusData_20_sept/");
        Parameters::getParameters()->setAirportFileName("continent_io_traffic.csv");
        Parameters::getParameters()->setLegsFileName("continent_route_traffic.csv");
        Parameters::getParameters()->setItineraryFileName("continent_routing_share.csv");
        DataManager::getDataManager()->loadData(AMADEUS_TYPE);
        
    }
    
    //        DataManager::getDataManager()->parseRoutesToAlfa();
    //        DataManager::getDataManager()->alfaVerification();
    //        DataManager::getDataManager()->isTotalDepartureSmallerSumUpperBounds();
    //        DataManager::getDataManager()->legsVerification();
    //
    //        cout <<endl;
    //        time_t startTime, endTime;
    //        startTime = time(&startTime);
    //
    //        QuadraticModel *quadraticModel = new QuadraticModel();
    //        quadraticModel->setExportFile(Parameters::getParameters()->getfilePath() + Parameters::getParameters()->getdataFolder() + "quadraticModel.lp");
    //        quadraticModel->resolution();
    //
    //        endTime = time(&endTime);
    //        cout<<endl<<setprecision(20)<<"Resolution process done in "<<difftime(endTime, startTime)<<" seconds!"<<endl<<endl;
    
    return 0;
}
