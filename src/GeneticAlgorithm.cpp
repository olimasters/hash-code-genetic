#include <GeneticAlgorithm.h>
#include <iostream>
#include <algorithm>

GeneticAlgorithm::GeneticAlgorithm(const Scorer &scorer, double mutationRate, unsigned generations, unsigned populationSize, unsigned matingPopulationSize, unsigned numberOfGenes, unsigned numberOfGeneBuckets) :
    scorer(scorer),
    generationsRemaining(generations),
    populationSize(populationSize),
    numberOfGenes(numberOfGenes),
    numberOfGeneBuckets(numberOfGeneBuckets),
    matingPopulationSize(matingPopulationSize),
    mutationRate(mutationRate)
{
    initialisePopulation();
};

void GeneticAlgorithm::initialisePopulation()
{
    // Make sure we call the constructor for each one to get a population of randomly-initialised chromosomes
    std::generate_n(std::back_inserter(currentPopulation), populationSize, [&](){return Chromosome(numberOfGenes, numberOfGeneBuckets);});
}

Chromosome GeneticAlgorithm::run()
{
    while(generationsRemaining--)
    {
        
        std::vector<Chromosome> matingPopulation{selectMatingPopulation()};
        breedNewPopulation(matingPopulation);
    }
    auto bestChromosome = std::max_element(currentPopulation.begin(), currentPopulation.end(), [&](const Chromosome &a, const Chromosome &b){return scorer.getFitness(a) < scorer.getFitness(b);});
    return *bestChromosome;
};

std::vector<Chromosome> GeneticAlgorithm::selectMatingPopulation()
{
    std::vector<Chromosome> matingPopulation;
    // Uses dumb cut-off logic
    // TODO: replace with stochastic universal sampling or tournament
    std::vector<std::pair<Chromosome, unsigned>> populationWithFitness;
    populationWithFitness.reserve(populationSize);

    // TODO: use C++17 and std::execution::par, this will speed up hugely
    std::transform(currentPopulation.begin(),
            currentPopulation.end(),
            std::back_inserter(populationWithFitness),
            [&](Chromosome chromosome){return std::pair<Chromosome, unsigned>{chromosome, scorer.getFitness(chromosome)};});

    std::sort(populationWithFitness.begin(), populationWithFitness.end(), [](const std::pair<Chromosome, unsigned> &a, const std::pair<Chromosome, unsigned> &b){return a.second > b.second;});
    
    // std::cout << "Current maximal fitness: " << populationWithFitness[0].second << std::endl;

    matingPopulation.reserve(matingPopulationSize);
    for(auto it = populationWithFitness.begin(); it < populationWithFitness.begin() + matingPopulationSize; ++it)
        matingPopulation.push_back((*it).first);
    return matingPopulation;
}

void GeneticAlgorithm::breedNewPopulation(std::vector<Chromosome> &matingPopulation)
{
    currentPopulation.clear();
    while(1)
        for(unsigned i = 0; i < matingPopulationSize; i++)
            for(unsigned j = 0; j < matingPopulationSize; j++)
                if(i == j)
                        continue;
                else if(currentPopulation.size() < populationSize)
                {
                    Chromosome mutant{matingPopulation[i] * matingPopulation[j]};
                    mutant.mutate(mutationRate);
                    currentPopulation.push_back(mutant);
                }
                else
                    return;
}

