#include <ctime>
#pragma once

/**
 * @class Stopwatch
 * @brief A simple stopwatch utility for measuring elapsed time.
 *
 * This class provides functionality to measure the elapsed time in milliseconds
 * since the stopwatch was started. It uses the standard C++ <ctime> library.
 *
 * Usage:
 *   Stopwatch sw;
 *   // ... code to time ...
 *   int ms = sw.elapsed_milliseconds();
 */
class Stopwatch
{
private:
    /// Stores the processor time at which the stopwatch was started.
    /// This value is obtained from std::clock() and is used to measure elapsed CPU time.
    std::clock_t start_;

public:
    /**
     * @brief Constructs a new Stopwatch object.
     *
     * Initializes the stopwatch and prepares it for timing operations.
     */
    Stopwatch();
    /// @brief Returns the elapsed time in milliseconds since the stopwatch was started or last reset.
    /// @return The number of milliseconds elapsed as an integer.
    int elapsed_milliseconds() const;
};