// Timer.hpp - High-Resolution Timer using std::chrono

#ifndef TIMER_HPP
#define TIMER_HPP
#include <chrono>

class Timer {
    public:
    using Clock = std::chrono::high_resolution_clock;
    // most precise clock, in nano secs

    using TimePoint = Clock::time_point;

    using Duration = std::chrono::duration<double>;

    Timer() : start_(Clock::now()) {}
    // Constructor for timer

    void rest() {
        start_ = Clock::now(); // restarts time to now and 0
    }

    [[nodiscard]] double elapsed() const {
        return Duration(Clock::now() - start_).count();
        // .count() extracts the raw number from a duration object
        // [[nodiscard]] = compiler warning if you ignore return value (C++17)
    }

    [[nodiscard]] double lap() {
        TimePoint now = Clock::now();
        double dt = Duration(now - start_).count();
        start_ = now;  // Reset for next lap
        return dt;     // Seconds since last lap
    }

            
    private:
        TimePoint start_;
};

class ScopedTimer {
public:
    explicit ScopedTimer(double& result) : result_(result) {}
    
    ~ScopedTimer() {
        result_ = timer_.elapsed();
    }
    
    // Delete copy operations (prevents weird bugs)
    ScopedTimer(const ScopedTimer&) = delete;
    ScopedTimer& operator=(const ScopedTimer&) = delete;
    
private:
    Timer timer_;
    double& result_;  // Reference to caller's variable
};
#endif // TIMER_HPP


// Key Concepts to Understand:
// Clock::now() → Returns a time_point (current instant)
// time_point - time_point → Returns a duration
// duration.count() → Returns the raw number (double/int)
// Why lap() matters: Every frame you need delta time AND need to reset for next frame. lap() does both atomically.
// RAII in ScopedTimer: The destructor runs automatically when the object goes out of scope, so you can't forget to stop the timer.