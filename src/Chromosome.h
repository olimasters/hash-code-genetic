#include <random>

#ifndef CHROMOSOME_H
#define CHROMOSOME_H
class Chromosome
{
    public:
        Chromosome(unsigned numberOfGenes, unsigned numberOfGeneValues, bool randomlyInitialise = true);
        ~Chromosome();
        void setGene(unsigned gene, unsigned position);
        unsigned getGene(unsigned position) const;
        std::vector<unsigned> getData() const;
    private:
        unsigned generateGene();

        unsigned numberOfGenes;
        unsigned numberOfGeneValues;
        std::vector<unsigned > data;
        std::mt19937 randomNumberEngine;
        std::uniform_int_distribution<> geneDistribution;
        std::uniform_int_distribution<> coinFlipDistribution;
};
#endif
