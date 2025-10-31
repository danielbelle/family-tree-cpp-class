#include "pch/pch.hpp"

// Função para configurar o handler de fechamento
void configurarHandlerFechamento() {
#ifdef _WIN32
  // No Windows, podemos usar SetConsoleCtrlHandler
  SetConsoleCtrlHandler([](DWORD dwCtrlType) -> BOOL {
    if (dwCtrlType == CTRL_CLOSE_EVENT) {
      std::cout << "\n\n⚠️  Fechando programa via botão X..." << std::endl;
      std::cout << "📋 Programa finalizado." << std::endl;
      // Dá um tempo para a mensagem ser exibida
      Sleep(1000);
      return TRUE; // Permite o fechamento
    }
    return FALSE;
    }, TRUE);
#endif
}

int main() {
  configurarUTF8();
  configurarHandlerFechamento();

  string opcao;

  while (true) {
    exibirMenu();
    getline(cin, opcao);

    if (!deveContinuar(opcao)) {
      break;
    }

    processarOpcao(opcao);
  }

  cout << "📋 Programa finalizado!!!!!!" << endl;
  return 0;
}