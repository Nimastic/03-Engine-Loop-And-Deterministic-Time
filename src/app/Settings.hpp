// ============================================================================
// Settings.hpp - Application Settings & Persistence
// ============================================================================

#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <nlohmann/json.hpp>
#include <fstream>
#include <string>
#include <filesystem>  // For creating directories

// ============================================================================
// Settings Structure
// Holds all user preferences. Can be converted to/from JSON.
// ============================================================================

struct Settings {
    // Window state
    int windowWidth = 1280;
    int windowHeight = 720;
    bool maximized = false;
    
    // UI preferences
    bool showDemoWindow = false;
    float fontSize = 16.0f;
    std::string theme = "dark";
    
    // This macro generates JSON serialization code automatically
    // It creates to_json() and from_json() functions for this struct
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Settings, 
        windowWidth, windowHeight, maximized,
        showDemoWindow, fontSize, theme)
};

// ============================================================================
// Settings Manager
// Handles loading and saving settings to a JSON file.
// ============================================================================

class SettingsManager {
public:
    // Load settings from a JSON file
    // If file doesn't exist, keeps default settings
    void load(const std::string& path) {
        std::ifstream file(path);
        if (file.is_open()) {
            try {
                nlohmann::json j;
                file >> j;                          // Parse JSON from file
                settings_ = j.get<Settings>();      // Convert JSON to Settings struct
            } catch (const nlohmann::json::exception& e) {
                // JSON parsing failed - keep defaults
                // Could log error here: fmt::print(stderr, "Settings load error: {}\n", e.what());
            }
        }
        // If file doesn't exist or fails to parse, settings_ keeps its defaults
    }
    
    // Save settings to a JSON file
    void save(const std::string& path) {
        // Create parent directories if they don't exist
        std::filesystem::path filePath(path);
        std::filesystem::create_directories(filePath.parent_path());
        
        std::ofstream file(path);
        if (file.is_open()) {
            nlohmann::json j = settings_;       // Convert Settings struct to JSON
            file << j.dump(2);                  // Write with 2-space indentation
        }
    }
    
    // Get reference to settings (allows modification)
    Settings& get() { return settings_; }
    
    // Get const reference (read-only access)
    const Settings& get() const { return settings_; }
    
private:
    Settings settings_;  // Holds the current settings
};

#endif // SETTINGS_HPP