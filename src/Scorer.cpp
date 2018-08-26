#include <Scorer.h>
#include <Chromosome.h>
#include <Vehicle.h>
#include <numeric>
#include <algorithm>

Scorer::Scorer(unsigned R, unsigned C, unsigned F, unsigned N, unsigned B, unsigned T, std::vector<Ride> allRides) :
    R(R),
    C(C),
    F(F),
    N(N),
    B(B),
    T(T),
    allRides(allRides)
{

}
unsigned Scorer::getFitness(const Chromosome &chromosome) const
{
    std::vector<std::vector<Ride>> vehicleAllocationTable(assignmentToSetOfRideLists(chromosome.getData()));

    unsigned fitness = 0;
    for(const auto &ridesAllottedToVehicle : vehicleAllocationTable)
    {
        Vehicle vehicle(ridesAllottedToVehicle, T);
        vehicle.runSimulation();
        fitness += getScore(vehicle.getLateCompletedRides(), vehicle.getTimelyRides());
    }
    return fitness;
}

unsigned Scorer::getScore(const std::vector<Ride> &lateCompletedRides, const std::vector<Ride> &timelyRides) const
{
    std::vector<unsigned> lateScores;
    std::vector<unsigned> timelyScores;
    const auto getDistance = [](const Ride &ride){return ride.distance();};
    std::transform(lateCompletedRides.begin(), lateCompletedRides.end(), std::back_inserter(lateScores), getDistance);
    std::transform(timelyRides.begin(), timelyRides.end(), std::back_inserter(timelyScores), getDistance);
    
    // TODO: something that works
    // return (std::reduce(lateScores.begin(), lateScores.end()) +
            // std::reduce(timelyScores.begin(), timelyScores.end()) +
            // timelyScores.size()*B);
    return (std::accumulate(lateScores.begin(), lateScores.end(), 0) +
            std::accumulate(timelyScores.begin(), timelyScores.end(), 0) +
            timelyScores.size()*B);
}

std::vector<std::vector<Ride>> Scorer::assignmentToSetOfRideLists(const std::vector<unsigned> assignment) const
{
    std::vector<std::vector<Ride>> partitionOfRides(F);
    for(unsigned rideNumber = 0; rideNumber < assignment.size(); ++rideNumber)
    {
        partitionOfRides[assignment[rideNumber]].push_back(allRides[rideNumber]);
    }
    return partitionOfRides;
}    
