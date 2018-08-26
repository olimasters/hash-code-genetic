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
        unsigned getFitness(const Chromosome &chromosome) const;
        unsigned getChromosomeSize() const {return N;};
        unsigned getChromosomeValues() const {return F;};

    private:
        std::vector<std::vector<Ride>> assignmentToSetOfRideLists(std::vector<unsigned> assignment) const;
        unsigned getScore (const std::vector<Ride> &lateCompletedRides, const std::vector<Ride> &timelyRides) const;
        unsigned R;
        unsigned C;
        unsigned F;
        unsigned N;
        unsigned B;
        unsigned T;
        std::vector<Ride> allRides;
};
#endif
