// ============================================================================
// MenuBar.hpp - Main Application Menu Bar
// Renders the menu bar at the top of the window.
// ============================================================================

#ifndef MENUBAR_HPP
#define MENUBAR_HPP

#include <imgui.h>

class MenuBar {
public:
    // Render the menu bar
    // Takes references to bools so menu items can toggle application state
    void render(bool& showDemo, bool& showSettings, bool& shouldQuit) {
        // BeginMainMenuBar creates a menu bar at the top of the viewport
        if (ImGui::BeginMainMenuBar()) {
            
            // ================================================================
            // FILE MENU
            // ================================================================
            if (ImGui::BeginMenu("File")) {
                // MenuItem returns true when clicked
                if (ImGui::MenuItem("New", "Cmd+N")) {
                    // TODO: Implement new file action
                }
                
                if (ImGui::MenuItem("Open", "Cmd+O")) {
                    // TODO: Implement open action
                }
                
                if (ImGui::MenuItem("Save", "Cmd+S")) {
                    // TODO: Implement save action
                }
                
                // Separator draws a horizontal line
                ImGui::Separator();
                
                if (ImGui::MenuItem("Exit", "Cmd+Q")) {
                    shouldQuit = true;  // Signal main loop to exit
                }
                
                ImGui::EndMenu();  // MUST match BeginMenu
            }
            
            // ================================================================
            // VIEW MENU
            // ================================================================
            if (ImGui::BeginMenu("View")) {
                // MenuItem with bool pointer: toggles the bool, shows checkmark when true
                ImGui::MenuItem("Demo Window", nullptr, &showDemo);
                ImGui::MenuItem("Settings", nullptr, &showSettings);
                
                ImGui::EndMenu();
            }
            
            // ================================================================
            // HELP MENU
            // ================================================================
            if (ImGui::BeginMenu("Help")) {
                if (ImGui::MenuItem("Command Palette", "Cmd+Shift+P")) {
                    // This is handled via keyboard shortcut in main.cpp
                    // But having it in menu makes it discoverable
                }
                
                ImGui::Separator();
                
                if (ImGui::MenuItem("About")) {
                    // TODO: Show about dialog
                }
                
                ImGui::EndMenu();
            }
            
            ImGui::EndMainMenuBar();  // MUST match BeginMainMenuBar
        }
    }
};

#endif // MENUBAR_HPP