cmake_minimum_required(VERSION 3.16)
project(trabalho_cpp)

# Configurar para MinGW
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Desabilitar PCH por enquanto (pode causar problemas)
set(CMAKE_DISABLE_PRECOMPILE_HEADERS ON)

# Configurar diretórios de include
include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

# Encontrar arquivos fonte (apenas .cpp)
file(GLOB SOURCE_FILES 
    "src/*.cpp"
    "include/pch/*.cpp"
)

# Criar executável apenas com arquivos fonte
add_executable(${PROJECT_NAME} 
    ${SOURCE_FILES}
)

# Configurações de compilação
target_compile_options(${PROJECT_NAME} PRIVATE 
    -Wall 
    -Wextra 
    -std=c++17
)

if(WIN32)
    target_compile_options(${PROJECT_NAME} PRIVATE -municode)
endif()

message(STATUS "Arquivos fonte: ${SOURCE_FILES}")