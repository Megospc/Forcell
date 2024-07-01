// Random functions

#pragma once

#include "Definitions.h"

namespace Rand {
    #define RMAX 4294967295

    uint seed;

    uint next() {
        seed = seed*1664525+1013904223; // Getting new seed

        return seed;
    }

    void Seed(uint s) {
        seed = s;
    }

    double Double() {
        return (double)next()/RMAX;
    }

    float Float() {
        return (float)next()/RMAX;
    }

    float Range(float min, float max) { // Random float in range
        return Float()*(max-min)+min;
    }

    float Chance(float chance) {
        return (float)next()/(RMAX+1) < chance;
    }

    float Sign() {
        return Chance(0.5) ? 1:-1;
    }
}