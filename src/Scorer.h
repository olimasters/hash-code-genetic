#include <vector>
#include <Ride.h>

#ifndef SCORER_H
#define SCORER_H
class Scorer
{
    public:
        Scorer(unsigned R, unsigned C, unsigned F, unsigned N, unsigned B, unsigned T, std::vector<Ride> rides);
        double getFitness(const Chromosome &chromosome);
    private:
        std::vector<Vehicle> assignmentToVehicles(std::vector<unsigned> assignment);
        unsigned R;
        unsigned C;
        unsigned F;
        unsigned N;
        unsigned B;
        unsigned T;
        std::vector<Ride> rides;
};
#endif
