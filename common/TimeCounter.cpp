//
// Created by dvu on 02.11.16.
//

#include "TimeCounter.h"
#include <numeric>

void TimeCounter::start() {
    startTime = std::chrono::high_resolution_clock::now();
}

void TimeCounter::stop() {
    endTime = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    timeValues.push_back(time);
    if (timeValues.size() > maxSampleSize)
        timeValues.pop_front();
}

float TimeCounter::getTime() {
    int size = timeValues.size();
    if (size) {
        auto total = std::accumulate(timeValues.begin(), timeValues.end(), 0);
        float average = static_cast<float>(total) / size;
        return average;
    } else {
        return 0;
    }
}

void TimeCounter::setMaxSampleSize(int size) {
    maxSampleSize = size;
}
