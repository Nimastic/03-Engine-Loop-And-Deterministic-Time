// ============================================================================
// Application.cpp - Implementation
// ============================================================================

#include "Application.hpp"
#include <imgui.h>

// ============================================================================
// Constructor
// ============================================================================

Application::Application() {
    // Register all available commands for the command palette
    registerCommands();
}

// ============================================================================
// Register Commands
// ============================================================================

void Application::registerCommands() {
    // Each command has: name, shortcut hint, and action (lambda function)
    
    commandPalette_.registerCommand({
        "Toggle Demo Window",
        "",  // No shortcut
        [this]() { showDemoWindow_ = !showDemoWindow_; }
        // [this] captures 'this' pointer so lambda can access class members
    });
    
    commandPalette_.registerCommand({
        "Toggle Settings",
        "",
        [this]() { showSettingsWindow_ = !showSettingsWindow_; }
    });
    
    commandPalette_.registerCommand({
        "Exit Application",
        "Cmd+Q",
        [this]() { requestQuit(); }
    });
}

// ============================================================================
// Render - Called Every Frame
// ============================================================================

void Application::render() {
    // Step 1: Render the dockspace (full-window docking area)
    // This MUST come first so other windows can dock into it
    dockSpace_.render();
    
    // Step 2: Render the menu bar
    // Pass references so menu bar can toggle our state
    menuBar_.render(showDemoWindow_, showSettingsWindow_, shouldQuit_);
    
    // Step 3: Render the command palette (if open)
    commandPalette_.render();
    
    // Step 4: Render optional windows based on state
    if (showDemoWindow_) {
        // ImGui's built-in demo window - great for learning!
        // Pass pointer to bool so the X button can close it
        ImGui::ShowDemoWindow(&showDemoWindow_);
    }
    
    if (showSettingsWindow_) {
        renderSettingsWindow();
    }
}

// ============================================================================
// Settings Window
// ============================================================================

void Application::renderSettingsWindow() {
    // Begin a new window called "Settings"
    // The bool pointer allows the X button to set it to false
    if (ImGui::Begin("Settings", &showSettingsWindow_)) {
        // Get reference to current settings
        Settings& settings = settingsManager_.get();
        
        // Font size slider
        // ##fontSize hides the label (## = hidden ID)
        ImGui::Text("Font Size");
        ImGui::SameLine();  // Put next widget on same line
        ImGui::SliderFloat("##fontSize", &settings.fontSize, 10.0f, 24.0f);
        
        // Theme selection
        ImGui::Text("Theme");
        ImGui::SameLine();
        if (ImGui::BeginCombo("##theme", settings.theme.c_str())) {
            if (ImGui::Selectable("dark", settings.theme == "dark")) {
                settings.theme = "dark";
                ImGui::StyleColorsDark();
            }
            if (ImGui::Selectable("light", settings.theme == "light")) {
                settings.theme = "light";
                ImGui::StyleColorsLight();
            }
            if (ImGui::Selectable("classic", settings.theme == "classic")) {
                settings.theme = "classic";
                ImGui::StyleColorsClassic();
            }
            ImGui::EndCombo();
        }
        
        // Show demo window toggle
        ImGui::Checkbox("Show Demo Window on startup", &settings.showDemoWindow);
    }
    ImGui::End();  // MUST match every Begin()
}

// ============================================================================
// Settings Persistence
// ============================================================================

void Application::loadSettings(const std::string& path) {
    settingsManager_.load(path);
    
    // Apply loaded settings
    Settings& settings = settingsManager_.get();
    showDemoWindow_ = settings.showDemoWindow;
    
    // Apply theme
    if (settings.theme == "light") {
        ImGui::StyleColorsLight();
    } else if (settings.theme == "classic") {
        ImGui::StyleColorsClassic();
    } else {
        ImGui::StyleColorsDark();
    }
}

void Application::saveSettings(const std::string& path) {
    // Update settings with current state before saving
    Settings& settings = settingsManager_.get();
    settings.showDemoWindow = showDemoWindow_;
    
    settingsManager_.save(path);
}

// ============================================================================
// Command Palette Control
// ============================================================================

void Application::toggleCommandPalette() {
    commandPalette_.toggle();
}

