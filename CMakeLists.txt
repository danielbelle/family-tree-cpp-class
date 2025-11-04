cmake_minimum_required(VERSION 3.16)
project(family_tree)

# Configurar para MinGW
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)

# Configurar diretórios de include
include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

# Encontrar todos os arquivos .cpp recursivamente
file(GLOB_RECURSE SOURCE_FILES 
    "src/*.cpp"
    "src/*/*.cpp"
    "src/*/*/*.cpp"
)

# Criar executável
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

# Mensagem de status
message(STATUS "=== CONFIGURAÇÃO MODULAR ===")
message(STATUS "Projeto: ${PROJECT_NAME}")
message(STATUS "Arquivos fonte encontrados: ${SOURCE_FILES}")
message(STATUS "=============================")