#pragma once

// C++ Standard Library
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include <algorithm>
#include <cstdlib>
#include <queue>
#include <fstream>
#include <filesystem>

// Windows API
#ifdef _WIN32
#include <windows.h>
#endif

// JSON library (single header)
#include "../json/json.hpp"

// Headers do projeto
#include "../core/estruturas.hpp"
#include "../core/main.hpp"
#include "../core/operacoes.hpp"
#include "../core/execucao.hpp"
#include "../core/persistencia.hpp"