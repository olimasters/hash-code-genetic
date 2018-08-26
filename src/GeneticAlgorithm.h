#include <Chromosome.h>
#include <Scorer.h>
#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H
class GeneticAlgorithm
{
    public:
        GeneticAlgorithm(const Scorer &scorer, double mutationRate, unsigned generations, unsigned populationSize, unsigned matingPopulationSize, unsigned chromosomeSize, unsigned chromosomeValues);
        Chromosome run();
    private:
        const Scorer &scorer;
        unsigned generationsRemaining;
        unsigned populationSize;
        unsigned numberOfGenes;
        unsigned numberOfGeneBuckets;
        unsigned matingPopulationSize;
        double mutationRate;
        std::vector<Chromosome> currentPopulation;

        void initialisePopulation();
        void breedNewPopulation(std::vector<Chromosome> &matingPopulation);
        std::vector<Chromosome> selectMatingPopulation();
};
#endif
