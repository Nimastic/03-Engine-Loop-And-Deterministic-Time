// This is a state machine for controlling time: pause, resume, single-step, and slow-motion.

// TimeController.hpp - Pause, Step, and Time Scale Controls

// PURPOSE: Control the flow of simulation time for debugging.
// - Pause/Resume: Freeze the simulation
// - Step: Advance exactly one fixed timestep while paused
// - Time Scale: Slow-motion (0.5x) or fast-forward (2.0x)
//

#ifndef TIME_CONTROLLER_HPP
#define TIME_CONTROLLER_HPP
#include <algorithm>  // for std::max, std::clamp
class TimeController {
   public:
    // ========================================================================
    // Pause Controls
    // ========================================================================

    bool isPaused() const { return paused_; }

    void pause() { paused_ = true; }

    void resume() { paused_ = false; }

    void togglePause() { paused_ = !paused_; }

    // ========================================================================
    // Single-Step (frame-by-frame advance while paused)
    // ========================================================================
    //
    // HOW IT WORKS:
    // 1. User clicks "Step" button → step() is called → stepRequested_ = true
    // 2. Game loop calls consumeStep() each frame
    // 3. If stepRequested_ is true, return true and set it to false
    // 4. Game loop then runs exactly ONE fixed update
    //
    // This pattern is called "consume" because you can only use each step once.
    //

    void step() { stepRequested_ = true; }

    bool consumeStep() {
        if (stepRequested_) {
            stepRequested_ = false;
            return true;  // Yes, run one update
        }
        return false;  // No step was requested
    }

    // ========================================================================
    // Time Scale (slow-motion / fast-forward)
    // ========================================================================
    //
    // timeScale_ multiplies the delta time:
    // - 1.0 = normal speed
    // - 0.5 = half speed (slow-motion)
    // - 2.0 = double speed (fast-forward)
    // - 0.0 = effectively paused (but use pause() instead)
    //

    float getTimeScale() const { return timeScale_; }

    void setTimeScale(float scale) {
        // Clamp between 0.1 (10% speed) and 5.0 (500% speed)
        // Prevents negative time or insanely fast speeds
        timeScale_ = std::clamp(scale, 0.1f, 5.0f);
    }

    void resetTimeScale() { timeScale_ = 1.0f; }

    // ========================================================================
    // Convenience Methods
    // ========================================================================

    void reset() {
        paused_ = false;
        stepRequested_ = false;
        timeScale_ = 1.0f;
    }

   private:
    bool paused_ = false;
    bool stepRequested_ = false;
    float timeScale_ = 1.0f;
};
#endif  // TIME_CONTROLLER_HPP