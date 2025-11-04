#include "../../include/io/utf8_config.hpp"
#include <iostream>
#include <limits>
#include <locale>

// Inclusão condicional segura para Windows
#if defined(_WIN32) || defined(_WIN64)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

using namespace std;

void configurarUTF8() {
#if defined(_WIN32) || defined(_WIN64)
  // Configurar console Windows para UTF-8
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
  setvbuf(stdout, nullptr, _IOFBF, 1000);
#else
  // Linux/macOS - configurar locale para UTF-8
  try {
    std::locale::global(std::locale("en_US.UTF-8"));
  }
  catch (const std::exception& e) {
    // Fallback para locale padrão
    std::locale::global(std::locale(""));
  }
#endif
}

string lerStringUTF8() {
  string texto;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  getline(cin, texto);
  return texto;
}