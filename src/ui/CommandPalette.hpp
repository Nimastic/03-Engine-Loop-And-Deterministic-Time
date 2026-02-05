// ============================================================================
// CommandPalette.hpp - VS Code-style Command Palette
// A searchable popup that lists all available commands.
// ============================================================================

#ifndef COMMANDPALETTE_HPP
#define COMMANDPALETTE_HPP

#include <imgui.h>
#include <string>
#include <vector>
#include <functional>   // For std::function
#include <algorithm>    // For std::transform
#include <cctype>       // For std::tolower

// ============================================================================
// Command Structure
// Represents a single command that can be invoked.
// ============================================================================

struct Command {
    std::string name;               // Display name: "Toggle Dark Mode"
    std::string shortcut;           // Shortcut hint: "Cmd+D" (just for display)
    std::function<void()> action;   // The function to call when selected
};

// ============================================================================
// Command Palette Class
// ============================================================================

class CommandPalette {
public:
    // Register a new command
    void registerCommand(const Command& cmd) {
        commands_.push_back(cmd);
    }
    
    // Open the palette
    void open() {
        isOpen_ = true;
        searchBuffer_[0] = '\0';  // Clear the search buffer
        selectedIndex_ = 0;        // Reset selection
    }
    
    // Close the palette
    void close() {
        isOpen_ = false;
    }
    
    // Toggle open/closed
    void toggle() {
        if (isOpen_) close();
        else open();
    }
    
    // Render the palette (call every frame)
    void render() {
        if (!isOpen_) return;  // Don't render if closed
        
        // Open the popup modal
        ImGui::OpenPopup("##CommandPalette");
        
        // Position at top-center of viewport (like VS Code)
        ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos(
            ImVec2(center.x, center.y * 0.5f),  // Top third of screen
            ImGuiCond_Appearing,                 // Only set position when first appearing
            ImVec2(0.5f, 0.0f)                   // Anchor: center-top
        );
        ImGui::SetNextWindowSize(ImVec2(500, 0));  // Width 500, height auto
        
        // Begin the popup
        // Using "##" prefix makes the title invisible (ID only)
        if (ImGui::BeginPopupModal("##CommandPalette", &isOpen_,
            ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize)) {
            
            // ================================================================
            // SEARCH INPUT
            // ================================================================
            
            // Focus the input field when popup appears
            if (ImGui::IsWindowAppearing()) {
                ImGui::SetKeyboardFocusHere();
            }
            
            // Search input field
            // -1 width = fill available space
            ImGui::SetNextItemWidth(-1);
            bool inputChanged = ImGui::InputText(
                "##search",          // Hidden label
                searchBuffer_,       // Buffer to store input
                sizeof(searchBuffer_),
                ImGuiInputTextFlags_EnterReturnsTrue  // Return true on Enter
            );
            
            // Handle Enter key on search input
            if (inputChanged) {
                executeSelected();
            }
            
            // Handle Escape key
            if (ImGui::IsKeyPressed(ImGuiKey_Escape)) {
                close();
            }
            
            // Handle Up/Down arrows
            if (ImGui::IsKeyPressed(ImGuiKey_UpArrow)) {
                if (selectedIndex_ > 0) selectedIndex_--;
            }
            if (ImGui::IsKeyPressed(ImGuiKey_DownArrow)) {
                selectedIndex_++;  // Will be clamped below
            }
            
            // ================================================================
            // COMMAND LIST
            // ================================================================
            
            ImGui::Separator();
            
            // Scrollable region for commands
            if (ImGui::BeginChild("CommandList", ImVec2(0, 300))) {
                int visibleIndex = 0;
                
                for (size_t i = 0; i < commands_.size(); i++) {
                    const Command& cmd = commands_[i];
                    
                    // Skip commands that don't match search
                    if (!matchesSearch(cmd.name)) {
                        continue;
                    }
                    
                    // Clamp selected index to visible items
                    if (visibleIndex == 0 && selectedIndex_ < 0) {
                        selectedIndex_ = 0;
                    }
                    
                    // Is this item selected?
                    bool isSelected = (visibleIndex == selectedIndex_);
                    
                    // Draw selectable item
                    if (ImGui::Selectable(cmd.name.c_str(), isSelected)) {
                        executeCommand(cmd);
                    }
                    
                    // Draw shortcut hint on the right
                    if (!cmd.shortcut.empty()) {
                        ImGui::SameLine(ImGui::GetWindowWidth() - 100);
                        ImGui::TextDisabled("%s", cmd.shortcut.c_str());
                    }
                    
                    visibleIndex++;
                }
                
                // Clamp selected index to valid range
                if (selectedIndex_ >= visibleIndex) {
                    selectedIndex_ = visibleIndex - 1;
                }
                if (selectedIndex_ < 0) {
                    selectedIndex_ = 0;
                }
            }
            ImGui::EndChild();
            
            ImGui::EndPopup();
        } else {
            // Popup was closed (clicked outside)
            isOpen_ = false;
        }
    }
    
private:
    bool isOpen_ = false;
    char searchBuffer_[256] = "";
    int selectedIndex_ = 0;
    std::vector<Command> commands_;
    
    // Check if a command name matches the search query
    // Uses case-insensitive substring matching
    bool matchesSearch(const std::string& name) {
        if (searchBuffer_[0] == '\0') {
            return true;  // Empty search matches everything
        }
        
        // Convert both to lowercase for case-insensitive comparison
        std::string lowerName = name;
        std::string lowerQuery = searchBuffer_;
        
        std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(),
            [](unsigned char c) { return std::tolower(c); });
        std::transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(),
            [](unsigned char c) { return std::tolower(c); });
        
        // Check if query is a substring of name
        return lowerName.find(lowerQuery) != std::string::npos;
    }
    
    // Execute the currently selected command
    void executeSelected() {
        int visibleIndex = 0;
        for (const Command& cmd : commands_) {
            if (!matchesSearch(cmd.name)) continue;
            
            if (visibleIndex == selectedIndex_) {
                executeCommand(cmd);
                return;
            }
            visibleIndex++;
        }
    }
    
    // Execute a command and close the palette
    void executeCommand(const Command& cmd) {
        if (cmd.action) {
            cmd.action();  // Call the function
        }
        close();
    }
};

#endif // COMMANDPALETTE_HPP