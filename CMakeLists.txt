cmake_minimum_required(VERSION 3.12)
project(sdl_bachelorDefender)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter")     # baseclass functions have plenty unused parameters
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unknown-attributes")   # clang does not know [[(un)likely]]
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

#set(CMAKE_CXX_FLAGS_DEBUG   "-Og")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

add_compile_options("$<$<CONFIG:DEBUG>:-D_DEBUG>")

file(GLOB_RECURSE SOURCES src/*)

add_executable(sdl_bachelorDefender ${SOURCES})

set(      VCPKG_BOOTSTRAP_OPTIONS       "-disableMetrics" )
set(      VCPKG_INSTALL_OPTIONS         "--no-print-usage")
set(      VCPKG_INSTALLED_DIR           ${CMAKE_SOURCE_DIR}/build/vcpkg_installed ) # comment this out to have a vcpkg_installed per build target
set(      VCPKG_DISABLE_METRICS         1 )
set( $ENV{VCPKG_DISABLE_METRICS}        1 )
set(      DOTNET_CLI_TELEMETRY_OPTOUT   1 )
set( $ENV{DOTNET_CLI_TELEMETRY_OPTOUT}  1 )

if( NOT MSVC )
    # Might rework MSVC to align with the adjusted CLion paths
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
endif()

# Add path of current cmake(.exe) to PATH
cmake_path( GET CMAKE_COMMAND PARENT_PATH CMAKE_COMMAND_PATH )
if( WIN32 )
    set( ENV{PATH} "${CMAKE_COMMAND_PATH};$ENV{PATH}" )
else()
    set( ENV{PATH} "${CMAKE_COMMAND_PATH}:$ENV{PATH}" )
endif()

get_filename_component( OUTSIDE_VCPKG_DIR "${CMAKE_SOURCE_DIR}/../vcpkg/" ABSOLUTE )
set( OUTSIDE_VCPKG_DIR "${OUTSIDE_VCPKG_DIR}"             CACHE PATH "Location of the outside vcpkg" )
set( INSIDE_VCPKG_DIR  "${CMAKE_SOURCE_DIR}/build/vcpkg/" CACHE PATH "Location of the inside vcpkg" )
if( EXISTS "${OUTSIDE_VCPKG_DIR}" )
    option( OUTSIDE_VCPKG_USE "Use a vcpkg which is outside of this repo, in a parallel folder" ON )
    if( OUTSIDE_VCPKG_USE )
        message( STATUS "Using outside vcpkg in ${OUTSIDE_VCPKG_DIR}" )
        set( VCPKG_DIR ${OUTSIDE_VCPKG_DIR} )
    else()
        set( VCPKG_DIR ${INSIDE_VCPKG_DIR} )
    endif()
else()
    option( OUTSIDE_VCPKG_USE "Use a vcpkg which is outside of this repo, in a parallel folder" OFF )
    set( VCPKG_DIR ${INSIDE_VCPKG_DIR} )
endif()

find_package( Git )

file( LOCK "${VCPKG_DIR}.lock" )

if( GIT_FOUND AND NOT OUTSIDE_VCPKG_USE )
    if( EXISTS "${PROJECT_SOURCE_DIR}/.git" )
        option( GIT_VCPKG "Check vcpkg during build" ON )
        if( GIT_VCPKG )
            if( NOT EXISTS "${VCPKG_DIR}" )
                message( STATUS "Cloning ${VCPKG_DIR}" )
                execute_process(
                        COMMAND             ${GIT_EXECUTABLE} clone https://github.com/Microsoft/vcpkg.git ${VCPKG_DIR}
                        WORKING_DIRECTORY   ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE     GIT_RESULT )
            else()
                message( STATUS "Pulling ${VCPKG_DIR}" )
                execute_process(
                        COMMAND             ${GIT_EXECUTABLE} pull -q
                        WORKING_DIRECTORY   ${VCPKG_DIR}
                        RESULT_VARIABLE     GIT_RESULT )
            endif()

            if( NOT GIT_RESULT EQUAL "0" )
                message( FATAL_ERROR "git command failed with ${GIT_RESULT}" )
            endif()
        endif()

        if( EXISTS "${PROJECT_SOURCE_DIR}/.gitmodules" )
            option( GIT_SUBMODULE "Check submodules during build" OFF )
            if( GIT_SUBMODULE )
                message( STATUS "Update submodules" )
                execute_process(
                        COMMAND             ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY   ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE     GIT_SUBMOD_RESULT )

                if( NOT GIT_SUBMOD_RESULT EQUAL "0" )
                    message( FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules" )
                endif()
            endif()
        endif()
    endif()
endif()

include( ${VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake )

file( LOCK "${VCPKG_DIR}.lock" RELEASE )


find_package( SDL2       CONFIG REQUIRED )
find_package( SDL2_ttf   CONFIG REQUIRED )
find_package( SDL2_mixer CONFIG REQUIRED )
find_package( SDL2_image CONFIG REQUIRED )
find_package( SDL2_net   CONFIG REQUIRED )

target_include_directories( sdl_basegame
        PRIVATE
        src
        ${SDL2_INCLUDE_DIR}
        )

target_link_libraries( sdl_basegame
        PRIVATE
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,               SDL2::SDL2,             SDL2::SDL2-static>
        $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,       SDL2_ttf::SDL2_ttf,     SDL2_ttf::SDL2_ttf-static>
        $<IF:$<TARGET_EXISTS:SDL2_mixer::SDL2_mixer>,   SDL2_mixer::SDL2_mixer, SDL2_mixer::SDL2_mixer-static>
        $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,   SDL2_image::SDL2_image, SDL2_image::SDL2_image-static>
        $<IF:$<TARGET_EXISTS:SDL2_net::SDL2_net>,       SDL2_net::SDL2_net,     SDL2_net::SDL2_net-static>
        $<TARGET_NAME_IF_EXISTS:OpenMP::OpenMP_CXX>
        )
