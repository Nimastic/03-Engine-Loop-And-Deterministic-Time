# ImGui App Shell

A desktop application shell with docking layout, menu bar, command palette, and settings persistence.

**Week 02 of 52 Weeks of C++ Projects**

---

## What is This For?

This **ImGui App Shell** is your **reusable desktop UI framework** for the 52 Weeks of C++ journey. Instead of building UI from scratch each week, you clone this shell and add your project-specific features.

Think of it as your **Swiss Army Knife** — a ready-made application window with menus, docking, settings, and commands that you can extend for any visualization, debugging, or tool-building project.

---

## Features

| Feature | Description |
|---------|-------------|
| **Docking Layout** | Drag and dock windows anywhere in the viewport |
| **Menu Bar** | File, View, Help menus with keyboard shortcuts |
| **Command Palette** | VS Code-style searchable command list (`Cmd+Shift+P`) |
| **Settings Persistence** | Preferences saved to JSON automatically |
| **Theme Switching** | Dark, Light, and Classic themes |
| **ImGui Demo** | Built-in UI component reference for learning |

---

## Projects That Can Use This Shell

This shell becomes the **UI foundation** for many future projects. Here's how your 52-week roadmap maps to this shell:

### Direct Use (Clone this shell, add panels)

| Week | Project | How to Use Shell |
|------|---------|------------------|
| 03 | Engine Loop + Deterministic Time | Add a timing debug panel showing delta time, FPS |
| 04 | Input System + Rebind UI | Add input config panel, keybind editor |
| 05 | 2D Renderer v1 | Add viewport panel, sprite inspector |
| 06 | Asset Pipeline | Add asset browser, hot reload status panel |
| 07 | Tilemap + Collision | Add tilemap editor, collision debug overlay |
| 08 | Entity System + Inspector | Add entity hierarchy, component inspector |
| 09 | ECS Upgrade | Add performance metrics panel, entity count |
| 10 | Scene Serialization | Add scene browser, save/load dialogs |
| 11-12 | Particle Systems | Add particle editor, emitter controls |
| 13 | 2D Physics Lite | Add physics debug panel, constraint viewer |
| 14 | Pathfinding Visualizer | Add grid view, algorithm controls, step debugger |
| 15 | Navmesh-lite | Add navmesh viewer, path testing panel |
| 16-19 | 2.5D Raycaster | Add viewport, level editor, lighting controls |
| 20 | Replay System | Add timeline scrubber, playback controls |
| 21 | Audio + Mixer | Add mixer panel, waveform visualizer |
| 22 | UI System | Build UI components that integrate with shell |
| 32 | Latency Histogram | Add histogram visualization panel |
| 35 | Market Data Playback | Add timeline, data inspector, playback controls |
| 36 | Limit Order Book | Add order book visualization, depth chart |
| 39 | Live Market Dashboard | Add real-time charts, WebSocket status |
| 40 | Telemetry + Profiling | Add flame graph, metric panels |
| 41-42 | ONNX/CNN Demo | Add image drop zone, prediction results panel |
| 45 | llama.cpp Chat UI | Add chat interface, model selector, settings |
| 46 | RAG-lite Pipeline | Add document browser, search interface |
| 49-52 | Chess Engine | Add board view, move history, UCI console |

### Library/Server Projects (No UI needed)

These projects are **backends/libraries** that don't need a GUI, but you could optionally build debug tools using this shell:

| Week | Project | Optional Shell Use |
|------|---------|-------------------|
| 27-28 | HTTP Client/Server | Debug panel for request/response inspection |
| 29-31 | Thread Pool, Ring Buffer | Performance monitoring dashboard |
| 33-34 | Reactor Server, Load Tester | Real-time metrics visualization |
| 37-38 | Matching Engine, Paper Trading | Order flow visualization |
| 43-44 | Tensor Library, Transformer | Tensor shape inspector |
| 47 | Quantized Model Benchmarking | Benchmark results dashboard |
| 48 | Fuzz/Hardening | Crash report viewer, coverage display |

### Standalone Games (Full integration)

| Week | Project | Shell Becomes |
|------|---------|---------------|
| 23 | Mini-Game Vertical Slice | In-game debug console + dev tools |
| 25 | Packaging Week | The game launcher/settings UI |
| 26 | Showcase Week | Demo player with level select |

---

## How to Use for Future Projects

```bash
# 1. Copy the shell for your new project
cp -r 02-ImGUI-App-Shell 08-Entity-Inspector
cd 08-Entity-Inspector

# 2. Update project name in CMakeLists.txt
# Change: project(ImGuiAppShell ...) → project(EntityInspector ...)

# 3. Add your new panels in src/ui/
# Example: src/ui/EntityHierarchy.hpp, src/ui/ComponentInspector.hpp

# 4. Include and render them in Application.cpp
```

---

## Screenshots

Run the app and try:
- **View > Demo Window** — Opens ImGui's comprehensive demo
- **View > Settings** — Opens the settings panel
- **Cmd+Shift+P** — Opens the command palette
- Drag window title bars to dock them to edges

---

## Tech Stack

| Component | Library | Purpose |
|-----------|---------|---------|
| Windowing | GLFW 3.4 | Cross-platform window/input handling |
| Graphics | OpenGL 3.3 | GPU-accelerated rendering |
| GUI | Dear ImGui (docking) | Immediate mode UI framework |
| JSON | nlohmann/json | Settings serialization |
| Formatting | fmt | Modern string formatting |
| Build | CMake 3.21+ | Build system |
| Packages | vcpkg | Dependency management |

---

## Prerequisites

1. **CMake 3.21+**
   ```bash
   # macOS
   brew install cmake
   ```

2. **vcpkg**
   ```bash
   git clone https://github.com/microsoft/vcpkg.git ~/vcpkg
   cd ~/vcpkg && ./bootstrap-vcpkg.sh
   
   # Add to ~/.zshrc
   export VCPKG_ROOT="$HOME/vcpkg"
   export PATH="$VCPKG_ROOT:$PATH"
   ```

3. **Xcode Command Line Tools** (macOS)
   ```bash
   xcode-select --install
   ```

---

## Building

```bash
# Configure (downloads dependencies via vcpkg)
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake

# Build
cmake --build build

# Run
./build/ImGuiAppShell
```

---

## Project Structure

```
02-ImGUI-App-Shell/
├── CMakeLists.txt              # Root build configuration
├── vcpkg.json                  # Dependencies manifest
├── src/
│   ├── main.cpp                # Entry point: GLFW/OpenGL/ImGui setup
│   ├── CMakeLists.txt          # Source build rules
│   ├── app/
│   │   ├── Application.hpp     # Main application class (declaration)
│   │   ├── Application.cpp     # Main application class (implementation)
│   │   └── Settings.hpp        # Settings struct + JSON serialization
│   └── ui/
│       ├── DockSpace.hpp       # Full-window docking container
│       ├── MenuBar.hpp         # File/View/Help menu bar
│       └── CommandPalette.hpp  # Searchable command popup
├── tests/
│   ├── CMakeLists.txt          # Test build rules
│   └── test_main.cpp           # Unit tests
├── cmake/
│   └── CompilerWarnings.cmake  # Strict compiler warning flags
├── .github/
│   └── workflows/
│       └── ci.yml              # GitHub Actions CI
├── .clang-format               # Code formatting rules
├── .clang-tidy                 # Static analysis rules
└── .gitignore                  # Git ignore rules
```

---

## Architecture

```
┌─────────────────────────────────────────────────────────────────┐
│                         main.cpp                                │
│  - Initialize GLFW (window + OpenGL context)                    │
│  - Initialize ImGui                                             │
│  - Run main loop (60 FPS)                                       │
│  - Handle keyboard shortcuts                                    │
│  - Cleanup on exit                                              │
└─────────────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────────────┐
│                      Application                                │
│  - Owns all UI components                                       │
│  - Manages application state                                    │
│  - Handles settings load/save                                   │
│  - Registers commands for palette                               │
└─────────────────────────────────────────────────────────────────┘
                              │
            ┌─────────────────┼─────────────────┐
            ▼                 ▼                 ▼
     ┌─────────────┐  ┌─────────────┐  ┌─────────────────┐
     │  DockSpace  │  │   MenuBar   │  │ CommandPalette  │
     │             │  │             │  │                 │
     │ Full-window │  │ File/View/  │  │ Searchable      │
     │ docking     │  │ Help menus  │  │ command list    │
     └─────────────┘  └─────────────┘  └─────────────────┘
```

---

## Keyboard Shortcuts

| Shortcut | Action |
|----------|--------|
| `Cmd+Shift+P` | Open command palette |
| `Cmd+Q` | Quit application |
| `Escape` | Close command palette |
| `↑` / `↓` | Navigate command palette |
| `Enter` | Execute selected command |

---

## C++ Concepts Practiced

| Concept | Where Used |
|---------|------------|
| **Event Loop** | GLFW event polling in main.cpp |
| **Immediate Mode GUI** | ImGui rendering every frame |
| **Header/Source Split** | Application.hpp/.cpp separation |
| **JSON Serialization** | nlohmann/json for settings |
| **Lambdas** | Command palette actions |
| **RAII** | Resource cleanup in destructors |
| **Include Guards** | `#ifndef`/`#define`/`#endif` in headers |
| **CMake** | Multi-directory project structure |
| **vcpkg** | Package management with features |

---

## Extending the App

### Add a New Panel (Most Common)

**Step 1:** Create `src/ui/MyPanel.hpp`

```cpp
#ifndef MYPANEL_HPP
#define MYPANEL_HPP

#include <imgui.h>

class MyPanel {
public:
    void render(bool& isOpen) {
        if (!isOpen) return;
        
        if (ImGui::Begin("My Panel", &isOpen)) {
            ImGui::Text("Hello from my panel!");
            
            // Add your widgets here
            static float value = 0.5f;
            ImGui::SliderFloat("Value", &value, 0.0f, 1.0f);
            
            if (ImGui::Button("Do Something")) {
                // Handle button click
            }
        }
        ImGui::End();
    }
};

#endif
```

**Step 2:** Add to `Application.hpp`

```cpp
#include "../ui/MyPanel.hpp"

class Application {
    // ...
private:
    MyPanel myPanel_;
    bool showMyPanel_ = false;
};
```

**Step 3:** Render in `Application::render()`

```cpp
void Application::render() {
    dockSpace_.render();
    menuBar_.render(showDemoWindow_, showSettingsWindow_, shouldQuit_);
    commandPalette_.render();
    
    // Add your panel
    myPanel_.render(showMyPanel_);
    
    // ...
}
```

**Step 4:** Add menu item in `MenuBar.hpp`

```cpp
if (ImGui::BeginMenu("View")) {
    ImGui::MenuItem("Demo Window", nullptr, &showDemo);
    ImGui::MenuItem("Settings", nullptr, &showSettings);
    ImGui::MenuItem("My Panel", nullptr, &showMyPanel);  // Add this
    ImGui::EndMenu();
}
```

### Add a New Command

In `Application.cpp`, inside `registerCommands()`:

```cpp
commandPalette_.registerCommand({
    "Toggle My Panel",
    "",
    [this]() { showMyPanel_ = !showMyPanel_; }
});

commandPalette_.registerCommand({
    "Reset Everything",
    "Cmd+R",
    [this]() { 
        // Your reset logic
    }
});
```

### Add a Viewport for Rendering

For graphics projects (renderer, raycaster, etc.):

```cpp
// In your panel's render() function
void render() {
    ImGui::Begin("Viewport");
    
    // Get available size
    ImVec2 size = ImGui::GetContentRegionAvail();
    
    // If you have a texture/framebuffer ID:
    // ImGui::Image((ImTextureID)myTextureID, size);
    
    // Or draw directly using ImDrawList:
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    ImVec2 pos = ImGui::GetCursorScreenPos();
    drawList->AddRectFilled(pos, ImVec2(pos.x + 100, pos.y + 100), IM_COL32(255, 0, 0, 255));
    
    ImGui::End();
}
```

### Common ImGui Widgets Reference

```cpp
// Text
ImGui::Text("Static text");
ImGui::TextColored(ImVec4(1,0,0,1), "Red text");

// Input
static char buf[256] = "";
ImGui::InputText("Name", buf, sizeof(buf));

static int i = 0;
ImGui::InputInt("Count", &i);

static float f = 0.5f;
ImGui::SliderFloat("Slider", &f, 0.0f, 1.0f);
ImGui::DragFloat("Drag", &f, 0.01f);

// Buttons
if (ImGui::Button("Click Me")) { /* action */ }

static bool checked = false;
ImGui::Checkbox("Enable", &checked);

// Combo box
static int current = 0;
const char* items[] = { "Option 1", "Option 2", "Option 3" };
ImGui::Combo("Select", &current, items, IM_ARRAYSIZE(items));

// Trees and collapsing headers
if (ImGui::CollapsingHeader("Section")) {
    ImGui::Text("Content inside section");
}

if (ImGui::TreeNode("Tree Node")) {
    ImGui::Text("Child content");
    ImGui::TreePop();
}

// Tables
if (ImGui::BeginTable("MyTable", 3)) {
    ImGui::TableNextColumn(); ImGui::Text("A");
    ImGui::TableNextColumn(); ImGui::Text("B");
    ImGui::TableNextColumn(); ImGui::Text("C");
    ImGui::EndTable();
}

// Plots (simple)
static float values[100] = {};
ImGui::PlotLines("Graph", values, IM_ARRAYSIZE(values));
ImGui::PlotHistogram("Histogram", values, IM_ARRAYSIZE(values));
```

---

## Settings Location

Settings are saved as JSON:

| Platform | Path |
|----------|------|
| macOS | `~/Library/Application Support/ImGuiAppShell/settings.json` |
| Linux | `~/.config/imgui-app-shell/settings.json` |

---

## License

This project is created for educational purposes as part of 52 Weeks of C++.

---

*Week 02 of 52 Weeks of C++ Projects*
