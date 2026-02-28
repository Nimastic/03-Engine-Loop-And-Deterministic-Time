// This is the heart of everything — the fixed timestep loop that ties Timer, FrametimeHistory, and TimeController together.
// GameLoop.hpp - Fixed Timestep Game Loop Controller
// ============================================================================
// PURPOSE: Implements the fixed timestep pattern with:
// - Accumulator-based time banking
// - Spiral of death protection
// - Interpolation alpha for smooth rendering
// - Integration with TimeController for pause/step

#ifndef GAME_LOOP
#define GAME_LOOP
#include "Timer.hpp"
#include "TimeController.hpp"
#include "FrameTimeHistory.hpp"

#include <algorithm>

class GameLoop {

public:



private:

}


#endif // GAME_LOOP
