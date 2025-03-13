cmake_minimum_required(VERSION 3.14...3.22)

project(Visual VERSION 1.0 LANGUAGES CXX C)

# Incluir CPM
include(cmake/CPM.cmake)

# Adicionar GLFW
CPMAddPackage(
        NAME glfw
        GITHUB_REPOSITORY glfw/glfw
        GIT_TAG 3.3.8
        OPTIONS
        "GLFW_BUILD_DOCS OFF"
        "GLFW_BUILD_TESTS OFF"
        "GLFW_BUILD_EXAMPLES OFF"
)

# Adicionar oneTBB
CPMAddPackage(
        NAME oneTBB
        GITHUB_REPOSITORY oneapi-src/oneTBB
        GIT_TAG v2021.9.0
        OPTIONS
        "TBB_TEST OFF"
        "TBB_EXAMPLES OFF"
        "TBB_USE_ITT_NOTIFY OFF"
)

# Adicionar ImGui
CPMAddPackage(
        NAME imgui
        GITHUB_REPOSITORY ocornut/imgui
        GIT_TAG v1.89.9
)

# Configuração do ImGui
if(imgui_ADDED)
  add_library(imgui STATIC
          ${imgui_SOURCE_DIR}/imgui.cpp
          ${imgui_SOURCE_DIR}/imgui_demo.cpp
          ${imgui_SOURCE_DIR}/imgui_draw.cpp
          ${imgui_SOURCE_DIR}/imgui_tables.cpp
          ${imgui_SOURCE_DIR}/imgui_widgets.cpp
          ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
          ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
  )

  target_include_directories(imgui PUBLIC
          $<BUILD_INTERFACE:${imgui_SOURCE_DIR}>
          $<BUILD_INTERFACE:${imgui_SOURCE_DIR}/backends>
  )

  target_link_libraries(imgui PRIVATE glfw)
endif()

# Adicionar cpm-glew
CPMAddPackage(
        NAME cpm-glew
        GITHUB_REPOSITORY iauns/cpm-glew
        GIT_TAG master
)

# Configuração do executável principal
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")
add_executable(Visual ${sources})
set_target_properties(Visual PROPERTIES CXX_STANDARD 23)

# Vinculação de bibliotecas
target_link_libraries(Visual PRIVATE
        glfw
        imgui
        ${GLEW_LIBRARIES}
        TBB::tbb
)

# Adicionar OpenGL
if(WIN32)
  target_link_libraries(Visual PRIVATE opengl32)
elseif(APPLE)
  target_link_libraries(Visual PRIVATE "-framework OpenGL")
elseif(UNIX AND NOT APPLE)
  find_package(OpenGL REQUIRED)
  target_link_libraries(Visual PRIVATE ${OPENGL_LIBRARIES})
endif()

# Inclusão de diretórios
target_include_directories(Visual PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${GLEW_INCLUDE_DIR}
)
