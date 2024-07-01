#pragma once

#include <iostream>
#include <chrono>

namespace Logger {
    #define Error(log) std::cerr << log << "\n"
    #define Log(log) std::cout << log << "\n"

    namespace Bench { // Benchmarking
        using namespace std::chrono;

        high_resolution_clock::time_point started;
        
        void Start() {
            started = high_resolution_clock::now();
        }

        double End() {
            high_resolution_clock::time_point ended = high_resolution_clock::now();

            duration<double, std::milli> result = ended-started;

            return result.count();
        }

        double Time() {
            high_resolution_clock::time_point v = high_resolution_clock::now();

            duration<double, std::milli> result = v-high_resolution_clock::from_time_t(0);

            return result.count();
        }
    }
}