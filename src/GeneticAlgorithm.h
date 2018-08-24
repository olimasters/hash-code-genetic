#include <Chromosome.h>
#include <Scorer.h>
#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H
class GeneticAlgorithm
{
    public:
        GeneticAlgorithm(const Scorer &scorer, unsigned generations, unsigned populationSize, unsigned matingPopulationSize, unsigned chromosomeSize, unsigned chromosomeValues);
        Chromosome run();
    private:
        const Scorer &scorer;
        unsigned generationsRemaining;
        unsigned populationSize;
        unsigned chromosomeSize;
        unsigned chromosomeValues;
        unsigned matingPopulationSize;
        std::vector<Chromosome> currentPopulation;

        void initialisePopulation();
        bool terminationConditionMet();
};
#endif
