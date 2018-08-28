#include <random>

#ifndef CHROMOSOME_H
#define CHROMOSOME_H
class Chromosome
{
    public:
        Chromosome(unsigned numberOfGenes, unsigned numberOfGeneBuckets, bool randomlyInitialise = true);
        Chromosome operator*(const Chromosome &otherParent);
        std::vector<std::vector<unsigned>> getData() const;
        void mutate(double mutationRate);
        void printData() const;
    private:
        void initialise();
        void setData(const std::vector<std::vector<unsigned>>&);
        unsigned generateGene();
        unsigned bucketSizes(std::vector<std::vector<unsigned>>::iterator start, std::vector<std::vector<unsigned>>::iterator end) const;
        void swapGenes(unsigned firstIndex, unsigned secondIndex);
        unsigned whichBucketContains(unsigned index) const;
        std::pair<unsigned, unsigned> findInData(unsigned geneNumber);

        unsigned numberOfGenes;
        unsigned numberOfGeneBuckets;
        std::vector<std::vector<unsigned>> data;
        std::mt19937 randomNumberEngine;
        std::uniform_int_distribution<> geneDistribution;
};
#endif
