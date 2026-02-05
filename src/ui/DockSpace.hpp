// ============================================================================
// DockSpace.hpp - Full-Window Docking Area
// Creates an invisible window that fills the entire viewport,
// allowing other ImGui windows to dock into it.
// ============================================================================

#ifndef DOCKSPACE_HPP
#define DOCKSPACE_HPP

#include <imgui.h>

class DockSpace {
public:
    void render() {
        // Get the main viewport (the entire application window)
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        
        // Position our dockspace window to fill the viewport
        // WorkPos/WorkSize exclude the OS menu bar on Mac
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        
        // Style: remove padding and rounding for seamless look
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        
        // Window flags - make it invisible and non-interactive
        ImGuiWindowFlags windowFlags = 
            ImGuiWindowFlags_NoDocking |           // This window itself can't be docked
            ImGuiWindowFlags_NoTitleBar |          // No title bar
            ImGuiWindowFlags_NoCollapse |          // Can't collapse
            ImGuiWindowFlags_NoResize |            // Can't resize (fills viewport)
            ImGuiWindowFlags_NoMove |              // Can't move
            ImGuiWindowFlags_NoBringToFrontOnFocus |  // Don't cover other windows
            ImGuiWindowFlags_NoNavFocus |          // Don't receive navigation focus
            ImGuiWindowFlags_NoBackground;         // Transparent background
        
        // Begin the dockspace window
        ImGui::Begin("DockSpace", nullptr, windowFlags);
        
        // Restore style
        ImGui::PopStyleVar(3);  // Pop the 3 style vars we pushed
        
        // Create the actual dockspace inside this window
        // DockSpace() returns the ID, which we don't need to store
        ImGuiID dockspaceId = ImGui::GetID("MainDockSpace");
        ImGui::DockSpace(dockspaceId, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);
        
        ImGui::End();
    }
};

#endif // DOCKSPACE_HPP