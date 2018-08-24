#include <vector>
#include <unordered_map>
#include <Chromosome.h>
#include <Ride.h>
#include <Vehicle.h>

#ifndef SCORER_H
#define SCORER_H
class Scorer
{
    public:
        Scorer(unsigned R, unsigned C, unsigned F, unsigned N, unsigned B, unsigned T, std::vector<Ride> allRides);
        unsigned getFitness(const Chromosome &chromosome);
    private:
        std::vector<std::vector<Ride>> assignmentToSetOfRideLists(std::vector<unsigned> assignment);
        unsigned getScore (const std::vector<Ride> &lateCompletedRides, const std::vector<Ride> &timelyRides);
        unsigned R;
        unsigned C;
        unsigned F;
        unsigned N;
        unsigned B;
        unsigned T;
        std::vector<Ride> allRides;
};
#endif
