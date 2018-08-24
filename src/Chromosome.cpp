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
            data[i] = generateGene();
}

unsigned Chromosome::generateGene()
{
    return geneDistribution(randomNumberEngine);
}

unsigned Chromosome::pickGene(unsigned motherGene, unsigned fatherGene)
{
    return coinFlipDistribution(randomNumberEngine) == 0 ? motherGene : fatherGene;
}

unsigned Chromosome::getGene(unsigned position) const
{
    return data[position];
}

void Chromosome::setGene(unsigned gene, unsigned position)
{
    data[position] = gene;
}

std::vector<unsigned> Chromosome::getData() const
{
    return data;
}


Chromosome Chromosome::operator*(const Chromosome &otherParent)
{
    Chromosome child(numberOfGenes, numberOfGeneValues, false);
    for(unsigned position = 0; position < numberOfGenes; position++)
    {
        unsigned gene = pickGene(getGene(position), otherParent.getGene(position));
        child.setGene(gene, position);
    }
    return child;
}
