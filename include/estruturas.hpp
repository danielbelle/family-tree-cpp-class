#pragma once

#include "./includes.hpp"

// Forward declarations
struct Pessoa;
struct ArvoreGenealogica;

struct Pessoa {
  string id;
  string nome;
  string dataNascimento;
  char genero;
  Pessoa* pai;
  Pessoa* mae;
  vector<Pessoa*> filhos;
  vector<string> papeis;

  Pessoa() : genero(' '), pai(nullptr), mae(nullptr), filhos(), papeis() {}
};

struct ArvoreGenealogica {
  string id;
  string nome;
  Pessoa* ancestralPrincipal;
  vector<Pessoa*> pessoas;

  ArvoreGenealogica() : ancestralPrincipal(nullptr), pessoas() {}
};