#include <Vehicle.h>
#include <Ride.h>
#include <vector>

Vehicle::Vehicle(std::vector<Ride> ridesToPerform, unsigned T) :
    pendingRides(ridesToPerform),
    T(T),
    currentTime(0),
    currentPosition(0,0)
{
}

std::vector<Ride> Vehicle::getLateCompletedRides() const
{
    return lateCompletedRides;
}

std::vector<Ride> Vehicle::getTimelyRides() const
{
    return timelyRides;
}

void Vehicle::waitForDeparture()
{
    unsigned startTime = pendingRides.back().earliestStart;
    if(currentTime < startTime)
        currentTime = startTime;
}

void Vehicle::registerRide(bool startedOnTime)
{
    Ride completedRide = pendingRides.back();
    if(currentTime < completedRide.latestFinish)
    {
        if(startedOnTime)
            timelyRides.push_back(completedRide);
        else
            lateCompletedRides.push_back(completedRide);
    }
    pendingRides.pop_back();
}

void Vehicle::runSimulation()
{
    while(currentTime < T && !pendingRides.empty())
    {
        bool startedOnTime;
        moveToPosition(pendingRides.back().startPosition);
        startedOnTime = currentTime <= pendingRides.back().earliestStart;
        waitForDeparture();
        moveToPosition(pendingRides.back().endPosition);
        registerRide(startedOnTime);
    }
}

void Vehicle::moveToPosition(const Coordinate &position)
{
    currentTime += dist(position, currentPosition);
    currentPosition = position;
}
