# Create the executable from source files
add_executable(${PROJECT_NAME} 
    main.cpp
    app/Application.cpp
)

# Link required libraries
target_link_libraries(${PROJECT_NAME} PRIVATE 
    fmt::fmt
    imgui::imgui
    glfw
    OpenGL::GL
    nlohmann_json::nlohmann_json
)

# Allow includes relative to src/ directory
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Apply strict compiler warnings
set_project_warnings(${PROJECT_NAME})