#include <GeneticAlgorithm.h>
#include <iostream>
#include <algorithm>

GeneticAlgorithm::GeneticAlgorithm(const Scorer &scorer, unsigned generations, unsigned populationSize, unsigned matingPopulationSize, unsigned chromosomeSize, unsigned chromosomeValues) :
    scorer(scorer),
    generationsRemaining(generations),
    populationSize(populationSize),
    chromosomeSize(chromosomeSize),
    chromosomeValues(chromosomeValues),
    matingPopulationSize(matingPopulationSize)
{
    initialisePopulation();
};

void GeneticAlgorithm::initialisePopulation()
{
    // Make sure we call the constructor for each one to get a population of randomly-initialised chromosomes
    std::generate_n(std::back_inserter(currentPopulation), populationSize, [&](){return Chromosome(chromosomeSize, chromosomeValues);});
}

Chromosome GeneticAlgorithm::run()
{
    return Chromosome(chromosomeSize, chromosomeValues); // dummy, TODO: do something reasonable
};

bool GeneticAlgorithm::terminationConditionMet()
{
    return generationsRemaining > 0;
}
