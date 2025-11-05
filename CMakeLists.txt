cmake_minimum_required(VERSION 3.10)
project(family-tree)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configurações para suporte a UTF-8
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -finput-charset=UTF-8 -fexec-charset=UTF-8 -fwide-exec-charset=UTF-8")
elseif(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8 /source-charset:utf-8 /execution-charset:utf-8")
    add_compile_definitions(_UNICODE UNICODE _CRT_SECURE_NO_WARNINGS)
endif()

# Garantir consistência em versões mais novas do CMake
if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.20)
    set(CMAKE_CXX_STANDARD_REQUIRED YES)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

set(SOURCES
    src/main.cpp
    src/core/arvore.cpp
    src/io/csv_handler.cpp
    src/io/utf8_config.cpp
    src/ui/menu.cpp
    src/ui/impressao.cpp
    src/utils/validacao.cpp
    src/utils/busca.cpp
)

add_executable(family-tree ${SOURCES})
target_include_directories(family-tree PRIVATE include)

# Forçar codificação UTF-8 no GCC / Clang
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(family-tree PRIVATE "-finput-charset=UTF-8")
    target_compile_options(family-tree PRIVATE "-fexec-charset=UTF-8")
    target_compile_options(family-tree PRIVATE "-fwide-exec-charset=UTF-8")
endif()

message(STATUS "Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "CXX Flags: ${CMAKE_CXX_FLAGS}")