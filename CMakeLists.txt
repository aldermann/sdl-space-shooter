# Define the project name
set(CXX g++-9)
project(sdl-ball CXX)

# Set the cmake minimum version to 3.5.1
cmake_minimum_required(VERSION 3.5.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
# Add SDL2 CMake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)
include_directories(${PROJECT_SOURCE_DIR}/src)
set(SOURCE_FILES src/game/main.cpp
        src/engine/manager/game.hpp
        src/engine/geometry/geometry.hpp
        src/engine/object/object.hpp
        src/engine/object/bounding_box/bounding_box.hpp
        src/engine/render/renderer.hpp
        src/engine/render/color.hpp
        src/utils/number.hpp src/utils/timer.hpp src/utils/error/error.hpp src/utils/error/sdl_error.hpp src/utils/utils.hpp
        src/engine/physics/dynamic.hpp src/engine/physics/motion.hpp
        src/engine/physics/physics.hpp
        src/engine/manager/timeline.hpp

        src/engine/manager/game.cpp src/engine/manager/manage_objects.cpp src/engine/manager/handle.cpp
        src/engine/manager/timeline.cpp
        src/engine/geometry/point.cpp src/engine/geometry/point.cpp src/engine/geometry/shape.cpp src/engine/geometry/vector.cpp
        src/engine/object/object.cpp
        src/engine/object/bounding_box/bounding_box.cpp src/engine/object/bounding_box/circle_box.cpp src/engine/object/bounding_box/rectangle_box.cpp
        src/engine/render/renderer.cpp src/engine/render/color.cpp
        src/utils/number.cpp src/utils/timer.cpp src/utils/error/error.cpp src/utils/error/sdl_error.cpp src/utils/utils.cpp
        src/engine/physics/dynamic.cpp src/engine/physics/motion.cpp
        src/engine/physics/physics.cpp

        src/game/objects/character/const.hpp
        src/game/objects/character/player.cpp src/game/objects/character/player.hpp
        src/game/objects/env/wall.hpp src/game/objects/env/wall.cpp
        src/game/objects/character/enemy.cpp src/game/objects/character/enemy.hpp
        src/game/objects/character/bullet.cpp src/game/objects/character/bullet.hpp
        src/game/objects/env/background.cpp src/game/objects/env/background.hpp
        src/engine/render/texture.cpp src/engine/render/texture.hpp

        src/game/timeline/spawn_enemy.cpp src/game/timeline/spawn_enemy.hpp
        src/game/timeline/game_setup.cpp src/game/timeline/game_setup.hpp src/game/objects/character/healthbar.cpp src/game/objects/character/healthbar.hpp src/utils/random.cpp src/utils/random.hpp)

set(BINARY_NAME ${PROJECT_NAME})
add_executable(${BINARY_NAME} ${SOURCE_FILES})
set_target_properties(${BINARY_NAME} PROPERTIES LINKER_LANGUAGE CXX)
# Add compiler errors/warnings flags
target_compile_options(${BINARY_NAME} PRIVATE $<$<C_COMPILER_ID:MSVC>:/W4 /WX>)
target_compile_options(${BINARY_NAME} PRIVATE $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -Werror -Wno-unused-parameter>)

find_package(Boost REQUIRED COMPONENTS system filesystem)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(${BINARY_NAME} ${Boost_LIBRARIES})
endif ()

if (APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_GNU_SOURCE")
endif ()
# Add SDL2 library
find_package(SDL2 REQUIRED)
target_link_libraries(${BINARY_NAME} SDL2::Main)

# Add SDL2_image library
find_package(SDL2_image REQUIRED)
target_link_libraries(${BINARY_NAME} SDL2::Image)

# Add SDL2_ttf library
find_package(SDL2_ttf REQUIRED)
target_link_libraries(${BINARY_NAME} SDL2::TTF)

# Add SDL2_net library
#find_package(SDL2_net REQUIRED)
#target_link_libraries(${BINARY_NAME} SDL2::Net)

# Add SDL2_mixer library
#find_package(SDL2_mixer REQUIRED)
#target_link_libraries(${BINARY_NAME} SDL2::Mixer)

# Add SDL2_gfx library
find_package(SDL2_gfx REQUIRED)
target_link_libraries(${BINARY_NAME} SDL2::GFX)

