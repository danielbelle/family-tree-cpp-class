#pragma once

// C++ Standard Library
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include <algorithm>
#include <cstdlib>
#include <queue>
#include <cctype>
#include <map>
#include <set>

// Windows API
#ifdef _WIN32
#include <windows.h>
#endif

// Using declarations
using namespace std;

// Headers do projeto - ORDEM IMPORTANTE!
#include "./estruturas.hpp"  // Primeiro - define as estruturas
#include "./main.hpp"        // Depois - usa as estruturas
#include "./processo.hpp"    // Por último - usa tudo
#include "./menu_criar.hpp"
#include "./menu_exibir.hpp"
#include "./menu_import_export.hpp"
#include "./menu_funcoes.hpp"
#include "./menu_principal.hpp"