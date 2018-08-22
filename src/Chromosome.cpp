#include <Chromosome.h>
#include <random>

Chromosome::Chromosome(unsigned numberOfGenes, unsigned numberOfGeneValues, bool randomlyInitialise) :
    numberOfGenes(numberOfGenes),
    numberOfGeneValues(numberOfGeneValues),
    data(numberOfGenes, 0),
    randomNumberEngine(std::random_device{}()),
    geneDistribution(0, numberOfGeneValues - 1),
    coinFlipDistribution(0,1)
{
    if(randomlyInitialise)
        for(unsigned i = 0; i < numberOfGenes; ++i)
            data.push_back(generateGene());
}

unsigned Chromosome::generateGene()
{
    return geneDistribution(randomNumberEngine);
}

unsigned Chromosome::pickGene(unsigned motherGene, unsigned fatherGene)
{
    return coinFlipDistribution(randomNumberEngine) == 0 ? motherGene : fatherGene;
}

unsigned Chromosome::getGene(unsigned position)
{
    return data[position];
}

Chromosome Chromosome::operator*(const chromosome &mother, const chromosome &father)
{
    Chromosome child(numberOfGenes, numberOfGeneValues, false);
    for(unsigned i = 0; i < numberOfGenes; i++)]
    {
        unsigned gene = pickGene(mother.getGene(i), father.getGene(i));
        child.setGene(gene);
    }
    return child;
}
