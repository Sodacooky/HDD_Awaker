cmake_minimum_required(VERSION 3.0.0)
set(VCPKG_TARGET_TRIPLET x64-windows)
set(CMAKE_TOOLCHAIN_FILE $ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
project(main VERSION 0.1.0)

aux_source_directory(./src/ SRC)
add_executable(main WIN32 ${SRC})

find_package(unofficial-nana CONFIG REQUIRED)
target_link_libraries(main PRIVATE unofficial::nana::nana)