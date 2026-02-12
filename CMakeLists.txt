cmake_minimum_required(VERSION 3.31)
project(cfg-watcher)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_PREFIX_PATH "C:/Program Files/Slint")

# Save all the source Files into a variable
file(GLOB SRC_FILES src/*.cpp)

#set(SLINT_STYLE fluent-dark)
#set(SLINT_STYLE material-dark)
set(SLINT_STYLE cupertino-dark)

# Find the Slint Package for the UI
find_package(Slint)

# Define the Executeable
add_executable(cfg-watcher ${SRC_FILES})

set(CMAKE_VERBOSE_MAKEFILE ON)
set_property(TARGET cfg-watcher PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

#set_property(TARGET cfg-watcher APPEND PROPERTY WIN32_EXECUTABLE TRUE)
#set_property(TARGET cfg-watcher PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)

# Invoke the Slint Compiler to generate the UI Files
slint_target_sources(cfg-watcher ui/app-window.slint)


#target_link_directories(
#	cfg-watcher PUBLIC ./slint
#)

target_link_libraries(
	cfg-watcher PUBLIC 
	Ws2_32 
	wsock32 
	opengl32 
	imm32 
	dwmapi 
	UxTheme 
	Uiautomationcore 
	Dwrite 
	Slint::Slint
)

if (WIN32)
    add_custom_command(TARGET cfg-watcher POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:cfg-watcher> $<TARGET_FILE_DIR:cfg-watcher> COMMAND_EXPAND_LISTS)
endif()