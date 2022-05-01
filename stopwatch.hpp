#include <chrono>
#include <algorithm>
#include <vector>
#include <numeric>
class stopwatch
{
private:
    std::chrono::high_resolution_clock::time_point begin;
    std::chrono::duration<double> diff;

public:
    std::vector<double> times;

    //on declaring the class saves current time

    stopwatch()
    {
        begin = std::chrono::high_resolution_clock::now();
    }

// compiler optimizations off for next function, supposed to be more precise results i think??
#pragma optimize("", off)
    // gets current time and subracts it from
    // *begin, returns a double which represent the seconds
    // it took between the two times (begin and time of calling the function)
    // also adds the time to a vector(times), for future use
    double elapsed()
    {
        diff = std::chrono::high_resolution_clock::now() - begin;
        times.push_back(diff.count());
        begin = std::chrono::high_resolution_clock::now();
        return diff.count();
    }
#pragma optimize("", on)

// resets begin variable, incase of idle time between intervals, pause or something, same compiler stuff
#pragma optimize("", off)
    void reset()
    {
        begin = std::chrono::high_resolution_clock::now();
    }
#pragma optimize("", on)
    // returns sum of times

    double sum()
    {
        return std::accumulate(times.begin(), times.end(), 0.0);
    }

    // useless i think, prints out all elements of times vector

    //void out()
    //{
    //    std::cout << "Times:\n";
    //    for (auto i : times)
    //    {
    //        std::cout << i << " ";
    //    }
    //    std::cout << std::endl;
    //}
};