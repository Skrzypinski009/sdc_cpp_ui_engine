cmake_minimum_required(VERSION 3.10)

project(SDL_ENGINE)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h")

add_subdirectory(external/SDL)  # Zakładając, że katalog SDL ma własny plik CMakeLists.txt
add_subdirectory(external/SDL_ttf)  # Zakładając, że katalog SDL_ttf ma własny plik CMakeLists.txt

add_executable(SDL_ENGINE ${SOURCES} ${HEADERS})

target_include_directories(SDL_ENGINE 
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/external/SDL_ttf/SDL_ttf.h
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/external/SDL/include
)

target_link_libraries(SDL_ENGINE SDL2 SDL2_ttf)

