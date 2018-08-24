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
    unsigned generations = 100;
    // TODO: consider what are sensible parameters
    GeneticAlgorithm algorithm(scorer, generations, 150, 50, 10, 4);
    Chromosome bestChromosome = algorithm.run();
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
