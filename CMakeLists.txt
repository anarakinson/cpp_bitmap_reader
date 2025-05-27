

cmake_minimum_required(VERSION 3.21)


# название проекта
project(bitmap_reader)

# определение конечной директории для испольняемого файла
if(MSVC)
    set(OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/Debug)
else()
    set(OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/)
endif()


# executables
add_executable(
    bitmap_reader
    src/main.cpp
    src/bitmap.cpp
)

# стандарт
set_target_properties( 
    bitmap_reader PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/include
)


# копирование папки с изображениями в конечную директорию сборки
file(
    COPY 
    ${CMAKE_CURRENT_SOURCE_DIR}/bitmaps 
    DESTINATION 
    ${OUTPUT_DIR}
)


# compile options
if (MSVC)
    target_compile_options(bitmap_reader PRIVATE
        /W4
    )
else ()
    target_compile_options(bitmap_reader PRIVATE
        # -Wall 
        -Wextra 
        -pedantic 
        -Werror
    )
endif()

