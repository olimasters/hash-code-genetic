#include <fstream>
#include <iostream>
#include <Utils.h>
#include <GeneticAlgorithm.h>

// testing

#include <Chromosome.h>
#include <Scorer.h>
#include <Ride.h>

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        fprintf(stderr, "Usage: %s <input filepath>\n", argv[0]);
        return 1;
    }
    Scorer scorer(createScorerFromFile(argv[1]));
    // TODO: tune parameters
    double mutationRate = 0.03;
    unsigned generations = 200;
    unsigned populationSize = 150;
    unsigned matingPopulationSize = 30;
    // note: it is wrong that F and N are known about by pulling them out of scorer.  Really we should be passing in a Chromosome factory which is created with N and F
    // life's too short
    GeneticAlgorithm algorithm(scorer, mutationRate, generations, populationSize, matingPopulationSize, scorer.getChromosomeSize(), scorer.getChromosomeValues());
    Chromosome bestChromosome = algorithm.run();
    std::cout << "Best chromosome:" << std::endl;
    for(const auto &vec : bestChromosome.getData())
    {
        for(const auto num : vec)
            std::cout << num << " ";
        std::cout << ",";
    }
    std::cout << std::endl;
    std::cout << "Fitness: " << scorer.getFitness(bestChromosome) << std::endl;
    std::cout << scorer.getFitness(bestChromosome) << std::endl;
    return 0;
}

/* Test stuff
    std::vector<Ride> rides{ {0,0,1,3,2,9}, {1,2,1,0,0,9}, {2,0,2,2,0,9} };
    Scorer scorer(3, 4, 2, 3, 2, 10, rides);
    Chromosome chromosome(3, 2);
    // set up the chromosome
    chromosome.setGene(0,0);
    chromosome.setGene(1,1);
    chromosome.setGene(1,2);

    std::cout << scorer.getFitness(chromosome) << std::endl;
    */
