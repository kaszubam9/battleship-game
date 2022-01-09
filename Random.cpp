#include "Random.h"

int RandN(const int kFrom, const int kTo)
{

    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution dist(kFrom, kTo);
    int random_number = dist(engine);

    return random_number;
}
