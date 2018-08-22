#include <iostream>
#include <fstream>

Scorer(unsigned R, unsigned C, unsigned F, unsigned N, unsigned B, unsigned T, std::vector<Ride> rides) :
    R(R),
    C(C),
    F(F),
    N(N),
    B(B),
    T(T),
    rides(rides)
{

}
unsigned Scorer::getFitness(const Chromosome &chromosome)
{
    std::vector<unsigned> assignment(chromosome.getData());
    std::unordered_map<unsigned, std:::vector<Ride>> assignmentMap(assignmentToMap(assignment));

    unsigned fitness = 0;
    for(const auto &vehicleRequirements : assignmentMap)
    {
        Vehicle vehicle(vehicleRequirements.second, T);
        vehicle.runSimulation();
        fitness += getScore(vehicle.getLateCompletedRides(), vehicle.getTimelyRides());
    }
}

unsigned Scorer::getScore(const std::vector<Ride> &lateCompletedRides, const std::vector<Ride> &timelyRides)
{
    unsigned score = 0;
    std::vector<unsigned> lateScores;
    std::vector<unsigned> timelyScores;
    std::transform(lateCompletedRides.begin(), lateCompletedRides.end(), std::back_inserter(lateScores), [](const Ride &ride){return ride.distance();});
    std::transform(timelyRides.begin(), timelyRides.end(), std::back_inserter(timelyScores), [](const Ride &ride){return ride.distance();});
    
    return (std::reduce(lateScores.begin(), lateScores.end()) +
            std::reduce(timelyScores.begin(), timelyScores.end()) +
            timelyScores.size()*B);
}

std::unordered_map<Vehicle> assignmentToMap(std::vector<unsigned> assignment, const std::vector<Ride> &rides)
{
    std::unordered_map<unsigned, std::vector<Ride>> vehiclesRidesMap;
    for(unsigned rideNumber = 0; rideNumber < assignment.size(); rideNumber++)
    {
        const auto ridesAssignedToVehicle = vehiclesRidesMap.find(assignment[rideNumber]);
        if(ridesAssignedToVehicle == vehiclesRidesMap.end())
            vehiclesRidesMap.emplace(rideNumber, {rides[rideNumber]});
        else
            (*ridesAssignedToVehicle).push_back(rides[rideNumber]);
    }
    return vehiclesRidesMap;
}    
