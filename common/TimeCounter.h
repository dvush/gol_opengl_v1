//
// Created by dvu on 02.11.16.
//

#ifndef WGV4_FPSCOUNTER_H
#define WGV4_FPSCOUNTER_H


#include <chrono>
#include <deque>

class TimeCounter {
public:
    void start();

    void stop();

    float getTime();

    void setMaxSampleSize(int size);

private:
    std::chrono::high_resolution_clock::time_point startTime;
    std::chrono::high_resolution_clock::time_point endTime;
    std::deque<long> timeValues;
    int maxSampleSize = 10;
};


#endif //WGV4_FPSCOUNTER_H
