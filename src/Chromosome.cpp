#include <Chromosome.h>
#include <random>
#include <unordered_set>
#include <algorithm>
#include <vector>
#include <numeric>
#include <sstream>

Chromosome::Chromosome(unsigned numberOfGenes, unsigned numberOfGeneBuckets, bool randomlyInitialise) :
    numberOfGenes(numberOfGenes),
    numberOfGeneBuckets(numberOfGeneBuckets),
    data(numberOfGeneBuckets),
    randomNumberEngine(std::random_device{}()),
    geneDistribution(0, numberOfGenes - 1)
{
    if(randomlyInitialise)
        initialise();
}

void Chromosome::initialise()
{
    std::vector<unsigned> rawRandomData(numberOfGenes);
    std::iota(rawRandomData.begin(), rawRandomData.end(), 0);
    std::shuffle(rawRandomData.begin(), rawRandomData.end(), randomNumberEngine);

    std::vector<unsigned> endpoints{0, numberOfGenes};
    endpoints.reserve(numberOfGeneBuckets + 1);
    std::uniform_int_distribution<> endpointDistribution(0,numberOfGenes);
    std::generate_n(std::back_inserter(endpoints), numberOfGeneBuckets - 1, [&](){return endpointDistribution(randomNumberEngine);});
    std::sort(endpoints.begin(), endpoints.end());

    for(unsigned i = 0; i < endpoints.size() - 1; i++)
        data[i] = std::vector<unsigned>{rawRandomData.begin() + endpoints[i], rawRandomData.begin() + endpoints[i+1]};
}

void Chromosome::setData(const std::vector<std::vector<unsigned>> &newData)
{
    data = newData;
}

std::vector<std::vector<unsigned>> Chromosome::getData() const
{
    return data;
}


Chromosome Chromosome::operator*(const Chromosome &otherParent)
{
    Chromosome child(numberOfGenes, numberOfGeneBuckets, false);
    std::vector<std::vector<unsigned>> childData(numberOfGeneBuckets);
    const std::vector<std::vector<unsigned>> &otherParentData{otherParent.getData()};
    std::unordered_set<unsigned> genesInheritedFromOtherParent;
    for(unsigned i = 0; i < numberOfGeneBuckets; ++i)
    {
        std::uniform_int_distribution<> bucketDistribution(0,otherParentData[i].size());
        unsigned lo = bucketDistribution(randomNumberEngine);
        unsigned hi = bucketDistribution(randomNumberEngine);
        if(hi < lo)
            std::swap(lo, hi);
        childData[i] = std::vector<unsigned>{otherParentData[i].begin() + lo, otherParentData[i].begin() + hi};
        genesInheritedFromOtherParent.insert(childData[i].begin(), childData[i].end());
    }
    std::vector<std::vector<unsigned>> genesNeededFromMe = data;
    for(auto &geneBucket : genesNeededFromMe)
        geneBucket.erase(
                std::remove_if(
                    geneBucket.begin(),
                    geneBucket.end(),
                    [&](const unsigned &gene){return genesInheritedFromOtherParent.find(gene) != genesInheritedFromOtherParent.end();}
                    ),
                geneBucket.end()
                );
    for(unsigned i = 0; i < childData.size(); i++)
        childData[i].insert(childData[i].end(), genesNeededFromMe[i].begin(), genesNeededFromMe[i].end());
    child.setData(childData);
    return child;
}

void Chromosome::mutate(double mutationRate)
{
    std::bernoulli_distribution mutationDistribution(mutationRate);
    if(mutationDistribution(randomNumberEngine))
         swapGenes(1,2);
        // swapGenes(geneDistribution(randomNumberEngine), geneDistribution(randomNumberEngine));
}

void Chromosome::swapGenes(unsigned firstIndex, unsigned secondIndex)
{
    unsigned firstBucketNumber = whichBucketContains(firstIndex);
    unsigned secondBucketNumber = whichBucketContains(secondIndex);
    unsigned firstBucketIndex = firstIndex - bucketSizes(data.begin(), data.begin() + firstBucketNumber);
    unsigned secondBucketIndex = secondIndex - bucketSizes(data.begin(), data.begin() + secondBucketNumber);
    unsigned tmp = data[firstBucketNumber][firstBucketIndex];
    data[secondBucketNumber][secondBucketIndex] = data[firstBucketNumber][firstBucketIndex];
    data[firstBucketNumber][firstBucketIndex] = tmp;
}

unsigned Chromosome::bucketSizes(std::vector<std::vector<unsigned>>::iterator start, std::vector<std::vector<unsigned>>::iterator end) const
{
    std::vector<unsigned> sizes;
    sizes.reserve(end - start);
    std::transform(start, end, std::back_inserter(sizes), [](const std::vector<unsigned> &bucket){return bucket.size();});
    return std::accumulate(sizes.begin(), sizes.end(), 0);
}

unsigned Chromosome::whichBucketContains(unsigned index) const
{
    unsigned elementsBehindUs = 0;
    for(unsigned i = 0; i < data.size(); i++)
    {
        if(elementsBehindUs + data[i].size() > index)
            return i;
        else
            elementsBehindUs += data[i].size();
    }
    // we should never get here
    std::ostringstream errString;
    errString << "Could not find index" << index << " in data:\n";
    for(const auto &vec : data)
    {
        errString << "{";
        for(const auto num : vec)
            errString << num << " ";
        errString << "}\n";
    }
    throw std::logic_error(errString.str());
}
