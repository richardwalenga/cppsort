#include "stopwatch.h"
#include <cmath>

Stopwatch::Stopwatch()
{
    start_ = clock();
}

int Stopwatch::elapsed_milliseconds() const
{
    double diff = clock() - start_;
    const int MILLISECS_PER_SEC = 1000;
    int elapsed_milliseconds = round(diff / CLOCKS_PER_SEC * MILLISECS_PER_SEC);
    return elapsed_milliseconds;
}