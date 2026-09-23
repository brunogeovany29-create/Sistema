#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <cctype>
#include <exception>
#include "Menu.hpp"
#include "Conta.hpp"


/*Função responsável pelas mensagens padronizadas na tela*/
void tela (){
  
  std::cout << "*******************" << std::endl;
  std::cout << "** BANCO INF101  **" << std::endl;
  std::cout << "*******************" << std::endl;
  
  /*std::cout << std::endl;*/
  return;
}
/*Função responsável pela limpeza da tela*/
int limpartela(){
  return std::system("cls");
}
/*Protótipo do futuro meno de login*/
/*void menuLogin (string cpfL){
     
  tela();

  login(cpfL);
  
}*/
/*Realiza a primeira consulta do status da conta Ativa ou Desativa*/
/*void menuConsultar(){
  Banco geral;
  string cpfC;
  
  tela();

  cout << "Digite o CPF: " << endl;
  getline(cin, cpfC);
  geral.consultarConta(cpfC);
    
  return;
}Interação Cliente->Banco*/
enum menuCliente {CONSULTAR = 1, SALDO = 2, SACAR = 3, DEPOSITAR = 4, CLISAIR = 5};
void Cliente(){
  Banco cliente;
  int menu1;
  std::string opcao;
  
  limpartela();
  tela();
  
  std::string cpf;
  std::cout << "Digite o seu cpf: ";
  std::getline(std::cin,cpf);
  login(cpf);
  
  
  do {
  
    
  std::cout << "(1) Verifica dados da conta" << std::endl;
  std::cout << "(2) Verifica saldo da conta" << std::endl;
  std::cout << "(3) Sacar" << std::endl;
  std::cout << "(4) Depositar" << std::endl;
  std::cout << "(5) Sair" << std::endl;
  std::cout << "Digite o numero: ";
  std::getline(std::cin,opcao);
  
  try {
  int Iopcao = std::stoi(opcao);
  switch(Iopcao){
    
    case CONSULTAR:{
    limpartela();
    cliente.consultarConta(cpf);
    std::cin.ignore();
    limpartela();
    menu1 = 1;
    break;
    }
    
    case SALDO:{
    limpartela();
    cliente.verSaldo(cpf);
    std::cin.ignore();
    limpartela();
    menu1 = 1;
    break;
    }

    case SACAR:{
    limpartela();
    double saque;
    cliente.verSaldo(cpf);
    std::cout << "Quanto deseja sacar?";
    std::cin >> saque;
    std::cin.ignore();
    if (saque > 0){
    cliente.Sacar(cpf,saque);
    }
    else {
      limpartela();
      std::cout << "Nao foi possivel completar sua operacao" << std::endl;
    }
    menu1 = 1;
    break;
    }

    case DEPOSITAR:{
    limpartela();
    double depositar;
    cliente.verSaldo(cpf);
    std::cout << "Quanto deseja depositar?";
    std::cin >> depositar;
    std::cin.ignore();
    if (depositar > 0){
    cliente.Depositar(cpf,depositar);
    }
    else {
      limpartela();
      std::cout << "Nao foi possivel completar sua operacao" << std::endl;
    }
    menu1 = 1;
    break;
    }
    
    case CLISAIR:{
      limpartela();
      std::cout << "Saindo do sistema.";
      std::exit(EXIT_SUCCESS);
      break;
    }

    default:{
      limpartela();
      tela();
      std::cerr << "ERRO Numero inserido esta fora da faixa de opcoes" << std::endl;
      menu1 = 1;
   }
  }
}
  catch (const std::exception& erroCliente){
    limpartela();
    tela();
    std::cerr << "ERRO valor inserido nao e um numero, digite apenas numeros" << std::endl;
    menu1 = 1;  
  }

} while (menu1 != 0);
  return;

}
/*Interação Cliente<-Gerente->Banco*/
enum menuGerente {BUSCAR = 1,CADASTRAR = 2,ATIVAR = 3,ALTERAR = 4 ,GESAIR = 5};
void Gerente(){
  Banco gerente;
  int menu1;
  std::string opcao;
  std::string cpf;

  limpartela();
  tela();

  std::cout << "Digite o seu cpf: ";
  std::getline(std::cin, cpf);
  login(cpf);
  
 do {
  
  std::cout << "(1) Buscar conta" << std::endl;
  std::cout << "(2) Cadastrar conta" << std::endl;
  std::cout << "(3) Ativar Conta" << std::endl;
  std::cout << "(4) Alterar o tipo de conta" << std::endl;
  std::cout << "(5) Sair" << std::endl;
  std::cout << "Digite o numero: ";
  std::getline(std::cin,opcao);
  
  try {
  int Iopcao = std::stoi(opcao);
  switch(Iopcao){
    
    case BUSCAR:{
    limpartela();
    std::string cpfCliente;
    std::cout << "Buscar cliente digite o cpf: " << std::endl;
    std::getline(std::cin,cpfCliente);
    gerente.consultarConta(cpfCliente);
    std::cin.get();
    menu1 = 1;
    break;
    }
    case CADASTRAR:{
    gerente.Cadastrar();
    menu1 = 1;
    break;
    }
    case ATIVAR:{
    limpartela();
    std::string cpf;
    std::cout << "Ativar conta, digite o CPF: " << std::endl;
    std::cin >> cpf;
    gerente.ativarConta(cpf);
    menu1 = 1;
    break;  
    }
    case ALTERAR:{
      std::string cpf;
      limpartela();
      std::cout << "Digite o cpf da conta: " << std::endl;
      std::getline(std::cin, cpf);
      gerente.altTipoconta(cpf);
      std::cin.ignore();
      std::cin.get();
      menu1 = 1;
      break;
    }
    case GESAIR:{
      limpartela();
      std::cout << "Saindo do sistema.";
      std::exit(EXIT_SUCCESS);
      break;
    }
    default:{
      limpartela();
      tela();
      std::cerr << "ERRO Numero inserido esta fora da faixa de opcoes" << std::endl;
      menu1 = 1;
    }
  }
  }
  catch (const std::exception& erroGE){
    limpartela();
    tela();
    std::cerr << "ERRO valor inserido nao e um numero, digite apenas numeros" << std::endl;
    menu1 = 1;
  }
  }  while(menu1 != 0);
   return;
}

/*Opções ao entrar no programa*/
enum Entrada {CLIENTE = 1,GERENTE = 2 ,SAIR = 3};
void menuEntrada(){
  std::string perfil;
  int opcao;
  limpartela();
  tela();

  do {
  
  std::cout << "(1) Cliente " << std::endl;
  std::cout << "(2) Gerente " << std::endl;
  std::cout << "(3) Sair " << std::endl;
  std::cout << "Digite a sua opcao: ";
  std::getline(std::cin, perfil);
  std::cout << std::endl;
  
  try {
    int Iperfil = std::stoi(perfil);
      switch (Iperfil)
  {
  case CLIENTE:{
    Cliente();
    opcao = 0;
    break;           
  }
  case GERENTE:{
    Gerente();
    opcao = 0;
    break;
  }
  case SAIR:{
    limpartela();
    std::cout << "Saindo do sistema";
    std::exit(EXIT_SUCCESS);
    break;
  }
  default:{
    limpartela();
    tela();
    std::cerr << "ERRO Numero inserido esta fora da faixa de opcoes" << std::endl;
    std::cin.clear();
    opcao = 1;
  }
  }
  }
  catch (const std::exception& erro) {
    limpartela();
    tela();
    std::cerr << "ERRO valor inserido nao e um numero, digite apenas numeros" << std::endl;
    std::cin.clear();
    opcao = 1;
    }
  
  }while (opcao != 0);
 return;
}
