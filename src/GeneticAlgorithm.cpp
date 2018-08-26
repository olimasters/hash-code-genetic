#include <GeneticAlgorithm.h>
#include <iostream>
#include <algorithm>

GeneticAlgorithm::GeneticAlgorithm(const Scorer &scorer, double mutationRate, unsigned generations, unsigned populationSize, unsigned matingPopulationSize, unsigned chromosomeSize, unsigned chromosomeValues) :
    scorer(scorer),
    generationsRemaining(generations),
    populationSize(populationSize),
    chromosomeSize(chromosomeSize),
    chromosomeValues(chromosomeValues),
    matingPopulationSize(matingPopulationSize),
    mutationRate(mutationRate)
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
    while(generationsRemaining--)
    {
        std::vector<Chromosome> matingPopulation{selectMatingPopulation()};
        breedNewPopulation(matingPopulation);
    }
    return currentPopulation[0];
};

std::vector<Chromosome> GeneticAlgorithm::selectMatingPopulation()
{
    std::vector<Chromosome> matingPopulation;
    // Uses dumb cut-off logic
    // TODO: replace with stochastic universal sampling or tournament
    std::vector<std::pair<Chromosome, unsigned>> populationWithFitness;
    populationWithFitness.reserve(populationSize);
    std::transform(currentPopulation.begin(),
            currentPopulation.end(),
            std::back_inserter(populationWithFitness),
            [&](Chromosome chromosome){return std::pair<Chromosome, unsigned>{chromosome, scorer.getFitness(chromosome)};});
    std::sort(populationWithFitness.begin(), populationWithFitness.end(), [](const std::pair<Chromosome, unsigned> a, const std::pair<Chromosome, unsigned> b){return a.second > b.second;});

    matingPopulation.reserve(matingPopulationSize);
    for(auto it = populationWithFitness.begin(); it < populationWithFitness.begin() + matingPopulationSize; ++it)
        matingPopulation.push_back((*it).first);
    return matingPopulation;
}

void GeneticAlgorithm::breedNewPopulation(std::vector<Chromosome> &matingPopulation)
{
    currentPopulation.clear();
    while(1)
        for(unsigned i = 0; i < matingPopulationSize - 1; i++)
            for(unsigned j = i + 1; j < matingPopulationSize; j++)
                if(currentPopulation.size() < populationSize)
                {
                    Chromosome mutant{matingPopulation[i] * matingPopulation[j]};
                    mutant.mutate(mutationRate);
                    currentPopulation.push_back(mutant);
                }
                else
                    return;
}

