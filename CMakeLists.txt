cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_COMPILER "/usr/bin/g++-11") 

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Nome do projeto
project(MeuJogoSFML)

# Especifica o padrão C++ a ser usado
set(CMAKE_CXX_STANDARD 14)

# Inclui o diretório de cabeçalhos
include_directories(include)

# Adiciona os arquivos-fonte
file(GLOB SOURCES src/*.cpp)

# Adiciona o executável
add_executable(meu_jogo ${SOURCES})

# Define os caminhos para as bibliotecas SFML
set(SFML_DIR "${CMAKE_SOURCE_DIR}/SFML-linux/lib/cmake/SFML")

# Encontra e linka as bibliotecas SFML necessárias
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

target_link_libraries(meu_jogo sfml-graphics sfml-window sfml-system)
