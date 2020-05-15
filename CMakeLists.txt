# Define the project name
set (CXX g++-9)
project(sdl-ball CXX)

# Set the cmake minimum version to 3.5.1
cmake_minimum_required(VERSION 3.5.1)
set(CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
# Add SDL2 CMake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)
include_directories(${PROJECT_SOURCE_DIR}/src)
set(SOURCE_FILES src/main.cpp
        src/game/game.cpp
        src/geometry/geometry.cpp src/geometry/point.cpp src/geometry/point.cpp src/geometry/shape.cpp src/geometry/vector.cpp
        src/number/number.cpp
        src/object/object.cpp
        src/object/bounding_box/bounding_box.cpp src/object/bounding_box/circle_box.cpp src/object/bounding_box/rectangle_box.cpp
        src/object/display_box/display_box.cpp
        src/physics/motion.cpp
        src/render/renderer.cpp
        src/render/color.cpp
        src/utils/timer.cpp
        src/utils/error/error.cpp src/utils/error/sdl_error.cpp
        src/game/game.hpp
        src/geometry/geometry.hpp
        src/number/number.hpp
        src/object/object.hpp
        src/object/bounding_box/bounding_box.hpp
        src/object/display_box/display_box.hpp
        src/physics/motion.hpp
        src/render/renderer.hpp
        src/render/color.hpp
        src/utils/timer.hpp
        src/utils/error/error.hpp src/utils/error/sdl_error.hpp
        src/utils/utils.cpp src/utils/utils.hpp)
message("What ${SOURCES}")
set(BINARY_NAME ${PROJECT_NAME})
add_executable(${BINARY_NAME} ${SOURCE_FILES})
set_target_properties(${BINARY_NAME} PROPERTIES LINKER_LANGUAGE CXX)
# Add compiler errors/warnings flags
target_compile_options(${BINARY_NAME} PRIVATE $<$<C_COMPILER_ID:MSVC>:/W4 /WX>)
target_compile_options(${BINARY_NAME} PRIVATE $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -Werror -Wno-unused-parameter>)


# Add SDL2 library
find_package(SDL2 REQUIRED)
target_link_libraries(${BINARY_NAME} SDL2::Main)

find_package(Boost REQUIRED COMPONENTS system)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(${BINARY_NAME} ${Boost_LIBRARIES})


endif ()

if (APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_GNU_SOURCE")
endif ()
# Add SDL2_image library
#find_package(SDL2_image REQUIRED)
#target_link_libraries(${BINARY_NAME} SDL2::Image)

# Add SDL2_ttf library
#find_package(SDL2_ttf REQUIRED)
#target_link_libraries(${BINARY_NAME} SDL2::TTF)

# Add SDL2_net library
#find_package(SDL2_net REQUIRED)
#target_link_libraries(${BINARY_NAME} SDL2::Net)

# Add SDL2_mixer library
#find_package(SDL2_mixer REQUIRED)
#target_link_libraries(${BINARY_NAME} SDL2::Mixer)

# Add SDL2_gfx library
find_package(SDL2_gfx REQUIRED)
target_link_libraries(${BINARY_NAME} SDL2::GFX)

