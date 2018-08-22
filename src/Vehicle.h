#ifndef VEHICLE_H
#define VEHICLE_H

class Vehicle
{
    public:
        Vehicle(std::vector<Ride> ridesToPerform, unsigned T);
        void runSimulation();
        std::vector<Ride> getLateCompletedRides() const;
        std::vector<Ride> getTimelyRides() const;
    private:
        void waitForDeparture();
        void registerRide(bool startedOnTime);
        void moveToPosition();

        std::vector<Ride> pendingRides;
        std::vector<Ride> lateCompletedRides;
        std::vector<Ride> timelyRides;
        unsigned T;
        unsigned currentTime;
        Coordinate currentPosition;
};

#endif
