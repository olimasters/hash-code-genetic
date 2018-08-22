#ifndef SCORER_H
#define SCORER_H
class Scorer
{
    public:
        Scorer(); // TODO: add parameters
        ~Scorer();
        double getFitness(const Chromosome &chromosome);
};
#endif
