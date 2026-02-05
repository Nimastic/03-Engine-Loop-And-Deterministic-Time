// ============================================================================
// main.cpp - Application Entry Point (GLFW + OpenGL version)
// ============================================================================
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <fmt/core.h>
#include <cstdlib>

#include "app/Application.hpp"

std::string getSettingsPath() {
    const char* home = std::getenv("HOME");
    if (!home) home = ".";
    #ifdef __APPLE__
        return std::string(home) + "/Library/Application Support/ImGuiAppShell/settings.json";
    #else
        return std::string(home) + "/.config/imgui-app-shell/settings.json";
    #endif
}

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    
    // ========================================================================
    // PHASE 1: INITIALIZE GLFW
    // ========================================================================
    
    if (!glfwInit()) {
        fmt::print(stderr, "Failed to initialize GLFW\n");
        return 1;
    }
    
    // Set OpenGL version (3.3 core profile works everywhere)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // Required on Mac
    #endif
    
    // Create window
    GLFWwindow* window = glfwCreateWindow(1280, 720, "ImGui App Shell", nullptr, nullptr);
    if (!window) {
        fmt::print(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return 1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);  // Enable vsync
    
    // Load OpenGL functions using glad (or your preferred loader)
    // Note: You'll need to add glad to your project or use another loader
    
    // ========================================================================
    // PHASE 2: INITIALIZE DEAR IMGUI
    // ========================================================================
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    
    ImGui::StyleColorsDark();
    
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    
    // ========================================================================
    // PHASE 3: CREATE APPLICATION
    // ========================================================================
    
    Application app;
    app.loadSettings(getSettingsPath());
    
    // ========================================================================
    // PHASE 4: MAIN LOOP
    // ========================================================================
    bool commandPaletteKeyWasPressed = false;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        
        // Handle keyboard shortcuts
        bool commandPaletteKeyIsPressed = 
            glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS &&
            (glfwGetKey(window, GLFW_KEY_LEFT_SUPER) == GLFW_PRESS ||
            glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) &&
            glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS;
    
        // Only toggle on the frame when key BECOMES pressed (not while held)
        if (commandPaletteKeyIsPressed && !commandPaletteKeyWasPressed) {
            app.toggleCommandPalette();
        } 
        commandPaletteKeyWasPressed = commandPaletteKeyIsPressed;

        
        if (app.shouldQuit()) {
            glfwSetWindowShouldClose(window, true);
        }
        
        // Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        // Render UI
        app.render();
        
        // Finalize and present
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        glfwSwapBuffers(window);
    }
    
    // ========================================================================
    // PHASE 5: CLEANUP
    // ========================================================================
    
    app.saveSettings(getSettingsPath());
    
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    
    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}