// FrametimeHistory.hpp - Circular Buffer for Frametime Samples
// PURPOSE: Store recent frametime samples for ImGui graphs.
// Uses a fixed-size array that wraps around (circular buffer).

#ifndef FRAMETIME_HISTORY_HPP
#define FRAMETIME_HISTORY_HPP
#include <array>
#include <cstddef>  // for size_t
class FrametimeHistory {
public:
    // Constants
    static constexpr size_t SIZE = 120;
    // ^ constexpr = computed at COMPILE TIME, not runtime
    // 120 samples at 60 FPS = 2 seconds of history

    void push(float frametime_ms) {
        samples_[writeIndex_] = frametime_ms;
        writeIndex_ = (writeIndex_ + 1) % SIZE;
                // ^ MODULO TRICK: When writeIndex_ reaches 120, it wraps to 0
        // This is how circular buffers work - oldest data gets overwritten
         if (count_ < SIZE) {
            ++count_;
            // Track how many samples we have (until buffer is full)
         }

         

    }

        // Getters for ImGui::PlotLines
        
    // Pointer to the array (ImGui needs this for plotting)
    const float* data() const { return samples_.data(); }

    // How many samples in the buffer
    size_t size() const { return SIZE; }

    // Current write position (useful for ImGui offset parameter)
    size_t offset() const { return writeIndex_; }




    float average() const {
            if (count_ == 0) return 0.0f;
            
            float sum = 0.0f;
            for (size_t i = 0; i < count_; ++i) {
                sum += samples_[i];
            }
            return sum / static_cast<float>(count_);
        }
        
        float minimum() const {
            if (count_ == 0) return 0.0f;
            
            float min = samples_[0];
            for (size_t i = 1; i < count_; ++i) {
                if (samples_[i] < min) min = samples_[i];
            }
            return min;
        }
        
        float maximum() const {
            if (count_ == 0) return 0.0f;
            
            float max = samples_[0];
            for (size_t i = 1; i < count_; ++i) {
                if (samples_[i] > max) max = samples_[i];
            }
            return max;
        }
        
        void clear() {
            samples_.fill(0.0f);
            writeIndex_ = 0;
            count_ = 0;
        }
    private:
        std::array<float, SIZE> samples_ = {};  // Zero-initialized
        size_t writeIndex_ = 0;                  // Where next sample goes
        size_t count_ = 0;                       // Samples written (caps at SIZE)
};
#endif // FRAMETIME_HISTORY_HPP
