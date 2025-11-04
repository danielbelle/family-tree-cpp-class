cmake_minimum_required(VERSION 3.10)
project(family-tree)

# Forçar MinGW no Windows
if(WIN32)
    # Definir o compilador MinGW explicitamente
    set(CMAKE_C_COMPILER "gcc")
    set(CMAKE_CXX_COMPILER "g++")
    set(CMAKE_MAKE_PROGRAM "mingw32-make")
    
    # Usar generator MinGW
    set(CMAKE_GENERATOR "MinGW Makefiles")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configurações específicas por compilador
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    # Flags para GCC/MinGW
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
elseif(MSVC)
    # Flags para Visual Studio
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")
endif()

# Arquivos fonte
set(SOURCES
    src/main.cpp
    src/pessoa.cpp
    src/csv_reader.cpp
    src/familia.cpp
)

add_executable(family-tree ${SOURCES})
target_include_directories(family-tree PRIVATE src)

# Mensagem de status
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "Generator: ${CMAKE_GENERATOR}")