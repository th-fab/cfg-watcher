cmake_minimum_required(VERSION 3.31)
project(cfg-watcher)


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_PREFIX_PATH "C:/Program Files/Slint")



#set(SLINT_STYLE fluent-dark)
#set(SLINT_STYLE material-dark)
set(SLINT_STYLE cupertino-dark)

# Find the Slint Package for the UI
find_package(Slint REQUIRED)
find_package(Boost REQUIRED COMPONENTS property_tree)
find_package(libconfig REQUIRED)

# Define the Executeable
add_executable(cfg-watcher
        src/main.cpp
        src/Settings_old.cpp
        src/Registry.cpp
        src/AppSettings.cpp
        src/Serialization.cpp
        src/SettingsModel.cpp
)

set(CMAKE_VERBOSE_MAKEFILE ON)
#set_property(TARGET cfg-watcher PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

#set_property(TARGET cfg-watcher APPEND PROPERTY WIN32_EXECUTABLE TRUE)
#set_property(TARGET cfg-watcher PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)

# Invoke the Slint Compiler to generate the UI Files
slint_target_sources(
        cfg-watcher
        ui/slint-main.slint)


#target_link_directories(
#	cfg-watcher PUBLIC ./slint
#)

target_link_libraries(
        cfg-watcher PRIVATE
        Slint::Slint
        Boost::property_tree
        libconfig::libconfig++
)

#if (WIN32)
#    add_custom_command(TARGET cfg-watcher POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:cfg-watcher> $<TARGET_FILE_DIR:cfg-watcher> COMMAND_EXPAND_LISTS)
#endif ()

if (WIN32)
    add_custom_command(TARGET cfg-watcher POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different
            "$<TARGET_RUNTIME_DLLS:cfg-watcher>"
            "$<TARGET_FILE_DIR:cfg-watcher>"
            COMMAND_EXPAND_LISTS
    )
endif()