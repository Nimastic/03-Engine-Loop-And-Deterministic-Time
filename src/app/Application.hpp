// ============================================================================
// Application.hpp - Main Application Class
// This class owns all UI components and manages application state.
// ============================================================================

#ifndef APPLICATION_HPP  // Include guard - prevents double inclusion
#define APPLICATION_HPP  // If not defined, define it and include the file

// Our UI components
#include "../ui/DockSpace.hpp"
#include "../ui/MenuBar.hpp"
#include "../ui/CommandPalette.hpp"

// Settings management
#include "Settings.hpp"

// Standard library
#include <string>

// ============================================================================
// Application Class
// ============================================================================

class Application {
public:
    // Constructor - initializes all components
    Application();
    
    // Destructor - cleans up resources
    ~Application() = default;  // Default is fine, no manual cleanup needed
    
    // Called every frame to render all UI
    void render();
    
    // Settings persistence
    void loadSettings(const std::string& path);
    void saveSettings(const std::string& path);
    
    // Application control
    bool shouldQuit() const { return shouldQuit_; }
    void requestQuit() { shouldQuit_ = true; }
    
    // Command palette control (called from main.cpp on keyboard shortcut)
    void toggleCommandPalette();
    
private:
    // Setup commands that can be invoked via command palette
    void registerCommands();

    // Render the settings window
    void renderSettingsWindow();
    
    // UI Components (each is a separate class)
    DockSpace dockSpace_;
    MenuBar menuBar_;
    CommandPalette commandPalette_;
    
    // Settings
    SettingsManager settingsManager_;
    
    // Application state
    bool shouldQuit_ = false;
    bool showDemoWindow_ = false;    // Toggle ImGui demo window
    bool showSettingsWindow_ = false; // Toggle settings window
};

#endif // APPLICATION_HPP