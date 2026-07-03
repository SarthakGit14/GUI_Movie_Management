cmake_minimum_required(VERSION 3.10)

project(MovieGUI)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(MovieGUI
    src/main.cpp

    backend/Movie.cpp
    backend/MovieManager.cpp
    backend/User.cpp

    database/Database.cpp
    screens/LoginScreen.cpp
    screens/SignupScreen.cpp
    screens/DashboardScreen.cpp
    screens/AdminScreen.cpp

    imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui_demo.cpp

    imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(MovieGUI PRIVATE
    imgui
    imgui/backends
    database
    backend
    screens
    include
)

target_link_libraries(MovieGUI
    glfw
    OpenGL::GL
    sqlite3
)
