#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include "Conta.hpp"
#include "Menu.hpp"

Banco::Banco(const std::string& nome,
         const std::string& cpf,
         const int nconta,
         int tpconta,
         int ativaconta,
         double saldoconta){
}
/* Esta função é responsável por captura os dados inseridos pelo Usuário
   realizando o cadastro no banco, que nesta versão permanece apenas na 
   memória enquanto o programa estiver rodando*/
int Banco::Cadastrar(){
   
  std::string nome, cpf;
  int numconta, tipoconta;
  double saldo;
  
  std::cout << "Nome " << std::endl;
  std::getline(std::cin, nome);
  std::cout << "Cpf " << std::endl;
  std::getline(std::cin, cpf);
  std::cout << "Numero Conta " << std::endl;
  std::cin >> numconta;
  if (numconta > 0){
    std::cout << "Tipo da conta " << std::endl;
    std::cin >> tipoconta;
    if (tipoconta > 0 && tipoconta < 3){
      std::cout << "Saldo em conta " << std::endl;
      std::cin >> saldo;
      if (saldo > 0){ 
        ativaconta = 1;
        registrarConta(nome,cpf,numconta,tipoconta,ativaconta,saldo);
      }
      else{
      std::cout << "Valor invalido";
      std::exit(EXIT_FAILURE);
      }
    }
    else{
    std::cout << "Valor invalido";
    std::exit(EXIT_FAILURE);
    }
  }
  else{
    std::cout << "Valor invalido";
    std::exit(EXIT_FAILURE);
  }

  return 0;
}
/*Esta função criar o arquivo txt onde ficaram quardados os dados da conta, de a um dos usuários*/
void Banco::registrarConta (std::string nomeA, std::string cpfA, int numcontaA, int tipocontaA, int ativacontaA, double saldoA){
   
  std::ofstream escreverArquivo (cpfA+".txt",std::ios::out | std::ios::trunc);
  escreverArquivo << nomeA << std::endl; 
  escreverArquivo << cpfA << std::endl;
  escreverArquivo << numcontaA << std::endl;
  escreverArquivo << tipocontaA << std::endl;
  escreverArquivo << ativacontaA << std::endl;
  escreverArquivo << saldoA << std::endl;
     
  escreverArquivo.close();
  return;
}
/*Está função é responsável por busca a conta, utilizando com base o cpf,
  poderia ser o numero da conta, ou qualquer outra condição, desde que
  especificada no arquivo Conta.hpp*/

void login(std::string Logar){
  std::ifstream lerArquivo (Logar+".txt",std::ios::in);
  limpartela();

  std::vector <std::string> status;
  std::string str;

       if (!lerArquivo.is_open()){
      }    
  /* Esse estrutura de repetição FOR 
   eu coloquei para ler apenas primeira linha do documento
   e retornar a informação*/
        while(std::getline(lerArquivo,str)){
          status.push_back(str);
      }
      
        Existe(Logar);

        senha(Logar);
        
        int iStatus = std::stoi(status.at(4));
       
        if (iStatus == 2){
        std::cerr<< "Seu acesso encontra-se Limitado" << std::endl;
        std::cerr << "Procure o seu gerente" << std::endl;
        std::cin.ignore();
        menuEntrada();
        }
        else {
          limpartela();
          std::cout << "Seja bem vindo" << std::endl;
        }      
  lerArquivo.close();

}

int senha(std::string senha){
  int repetir = 0;
  int tentativas;
  std::string verificaSenha;
  
  limpartela();

    do {
        limpartela();
        tentativas = 3 - repetir;
        std::cout << "Voce ainda tem mais " << tentativas << " tentativas." << std::endl;
        std::cout << "Digite a sua senha: " << std::endl;
        std::getline(std::cin,verificaSenha);
        
        if (verificaSenha != senha){
          std::cerr<< "Sua senha esta errada" << std::endl;
        repetir++;
        
        }

        else {
         int Isenha = std::stoi(verificaSenha); 
         return Isenha;
        }

      } while (repetir < 3);
      limpartela();
      std::cout << "Acabou o numero de tentativas" << std::endl;
      std::cin.ignore();
      menuEntrada(); 
      return 0;
}


void Existe(std::string existe){
  std::ifstream lerArquivo (existe+".txt",std::ios::in);
  limpartela();

  std::vector <std::string> status;
  std::string str;

        if (!lerArquivo.is_open()){
        std::cout << "Nao existe nenhuma conta registrada com esse CPF" << std::endl;
        std::cin.ignore();
        menuEntrada();
        }                
  
  lerArquivo.close();

}



/*Única função verifica o saldo em conta
Atualização futura distiguir conta poupanca e corrente.*/
void Banco::verSaldo(std::string veSaldo){
  std::vector <std::string> vesaldo;
  std::ifstream lerArquivo (veSaldo+".txt",std::ios::in);
  
  limpartela();
  
  if (!lerArquivo.is_open()){
    std::cerr << "Acesso Negado" << std::endl;
    std::exit(EXIT_FAILURE);
  }
  else {
  std::string str;
  while(std::getline(lerArquivo,str)){
    vesaldo.push_back(str);
  }

  std::cout << "Saldo Atual: " << vesaldo.at(5) << "R$" << std::endl;
  /* Esse estrutura de repetição FOR 
   int linhaSaldo = 6;
   eu coloquei para ler apenas ultima linha do documento
   e retornar a informação
  for (int i = 1; i <= linhaSaldo; i++){
        if(getline(lerArquivo,str)){
          if (i == linhaSaldo){
          cout << "Saldo em Conta: " << str << " Reais" << endl;
          }
        }
  } */ 

  lerArquivo.close();
  }
  return;
}
/*Única função realizar o saque em conta
Atualização futura distiguir conta poupanca e corrente.*/
int Banco::Sacar(std::string Retirada, double Saque){
  std::vector<std::string>sacar;

  std::ifstream lerArquivo (Retirada+".txt",std::ios::in);
  
  limpartela();
  
  if (!lerArquivo.is_open()){
    std::cerr << "Acesso Negado" << std::endl;
    std::exit(EXIT_FAILURE);
  }
  else {
  std::string str;
          /*Vetores são bons*/
          while(std::getline(lerArquivo,str)){
          sacar.push_back(str);         
          }
  
  
  lerArquivo.close();
  
  /*Aqui começa a mágica*/
  int Inumconta = std::stoi(sacar.at(2));
  int Itipoconta = std::stoi(sacar.at(3));
  int Iativaconta = std::stoi(sacar.at(4));
  double novosaldo, Dsaldo = std::stod(sacar.at(5));
  novosaldo = Dsaldo - Saque;
  if (novosaldo >= 0){
  registrarConta(sacar.at(0),sacar.at(1),Inumconta,Itipoconta,Iativaconta,novosaldo);
  }
  else {
    std::cout << "Saldo insuficiente para realizar o saque" << std::endl;
    std::cout << "Saldo atual: " << sacar.at(5) << "R$" << std::endl;
  }
  }  
  return 0;
}
/*Única função realizar deposito em sem conta
Atualização futura distiguir conta poupanca e corrente.*/
int Banco::Depositar(std::string Aportar, double Deposito){
  std::vector<std::string>depositar;

  std::ifstream lerArquivo (Aportar+".txt",std::ios::in);
  
  limpartela();
  
  if (!lerArquivo.is_open()){
    std::cerr << "Acesso Negado" << std::endl;
    std::exit(EXIT_FAILURE);
  }
  else{
  std::string str;
          /*Vetores são bons*/
          while(std::getline(lerArquivo,str)){
          depositar.push_back(str);         
          }
  

  lerArquivo.close();
  
  /*Aqui começa a mágica*/
  int Inumconta = std::stoi(depositar.at(2));
  int Itipoconta = std::stoi(depositar.at(3));
  int Iativaconta = std::stoi(depositar.at(4));

  double novosaldoD, Dsaldo = std::stod(depositar.at(5));
  novosaldoD = Deposito + Dsaldo;
  registrarConta(depositar.at(0),depositar.at(1),Inumconta,Itipoconta,Iativaconta,novosaldoD);
  }
  return 0;
}
/*Única função altera o tipo de conta poupanca e corrente.
Atualização futura imagino que seja classifica 
cliente de varejo e private bank*/
int Banco::altTipoconta(std::string Alterar){
  std::vector<std::string>alttipo;
  int alt;

  std::ifstream lerArquivo (Alterar+".txt",std::ios::in);
  
  if (!lerArquivo.is_open()){
    limpartela();
    std::cerr << "Acesso Negado" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  else {
  
  limpartela();
  
  std::cout << "Altere tipo de conta (1)Conta Corrente (2)Poupanca: ";
  std::cin >> alt;

  if (alt > 0 && alt <= 2){
  
  limpartela();
  
  std::string str;
          /*Vetores são bons*/
          while(std::getline(lerArquivo,str)){
          alttipo.push_back(str);         
          }
  
  
  lerArquivo.close();
  
  /*Aqui começa a mágica*/
  int Inumconta = std::stoi(alttipo.at(2));
  int Itipoconta = alt;
  int Iativaconta = std::stoi(alttipo.at(4));

  if (Itipoconta == 1){
    std::cout << "Status atual Conta Corrente" << std::endl;
    double Dsaldo = std::stod(alttipo.at(5));
    registrarConta(alttipo.at(0),alttipo.at(1),Inumconta,Itipoconta,Iativaconta,Dsaldo);
  }
  if (Itipoconta == 2) {
  std::cout << "Status atual Conta Poupanca" << std::endl;
  double Dsaldo = std::stod(alttipo.at(5));
  registrarConta(alttipo.at(0),alttipo.at(1),Inumconta,Itipoconta,Iativaconta,Dsaldo);
  }
  }
}
  return 0;
}
/*Única função devolver todas as informações sobre a conta*/
int Banco::consultarConta(std::string Consultar){
  std::vector<std::string>ler;
  limpartela();

  std::ifstream lerArquivo (Consultar+".txt",std::ios::in);
  
  std::string str;
  
  tela();

   if (!lerArquivo.is_open()){
    std::cerr << "Satus de conta: DESATIVADA" << std::endl;
    std::cerr << "Entre em contato com seu gerente." << std::endl;
    std::exit(EXIT_FAILURE);
  }

  else {

  if (lerArquivo.is_open()){
    std::cout << "Conta do Cliente " << std::endl;
    while(std::getline(lerArquivo, str)){
      ler.push_back(str);
    }
    std::cout << "Nome: " << ler.at(0) << std::endl;
    std::cout << "CPF: " << ler.at(1) << std::endl;
    std::cout << "Numero da conta: " << ler.at(2) << std::endl;
    if (ler.at(3) == "1"){
    std::cout << "Tipo da conta: " << "Conta Corrente" << std::endl;
     if (ler.at(4) == "1"){
      std::cout << "Status da conta: Ativa" << std::endl;}
      else {
      std::cout << "Status da conta: Desativada" << std::endl;
    }
    
    std::cout << "Saldo em conta: " << ler.at(5) << "R$" << std::endl;
    }
    else{
      std::cout << "Tipo da conta: " << " Conta Poupanca" << std::endl;
      if (ler.at(4) == "1"){
      std::cout << "Status da conta: Ativa" << std::endl;}
      else {
      std::cout << "Status da conta: Desativada" << std::endl;
      }
    std::cout << "Saldo em conta: " << ler.at(5) << "R$" << std::endl;
    }

  }

  lerArquivo.close();
}
  return 0;
}
int Banco::ativarConta(std::string Status){
    std::vector<std::string>status;

  std::ifstream lerArquivo (Status+".txt",std::ios::in);
  
  std::string str;
          /*Vetores são bons*/
          while(std::getline(lerArquivo,str)){
          status.push_back(str);         
          }
  
  if (!lerArquivo.is_open()){
    std::cerr << "Acesso Negado" << std::endl;
    std::exit(EXIT_FAILURE);
  }
  lerArquivo.close();
  
  if (status.at(4) == "1"){
      std::cout << "Status da conta: Ativa" << std::endl;}
      else {
      std::cout << "Status da conta: Desativada" << std::endl;
      } 

  std::cout << "Digite (1)Ativar conta (2)Desativar conta: ";
  int Iativaconta;
  std::cin >> Iativaconta;

  if (Iativaconta > 0 && Iativaconta <= 2){
  
  /*Aqui começa a mágica*/
  int Inumconta = std::stoi(status.at(2));
  int Itipoconta = std::stoi(status.at(3));
  double saldo = std::stod(status.at(5));

  registrarConta(status.at(0),status.at(1),Inumconta,Itipoconta,Iativaconta,saldo);
  }
  else {
    std::cerr << "Acesso Negado" << std::endl;
    std::exit(EXIT_FAILURE);
  }
  return 0;
}
/*Única função é desativar a conta adicionando uma letra
D no cpf, tornando a conta desativada*/
/*int Banco::desativarConta(string cpfD){
  string desativar = cpf;
  system(("ren "+cpf+".txt" " D"+cpf+".txt").c_str());
  return 0;
Única função é sativar a conta retirando uma letra
D nome do arquivo, tornando este novamente ativo.*/
/*int Banco::ativarConta(string cpfA){
  string ativar = cpf;
  system(("ren D"+cpf+".txt "+cpf+".txt").c_str());
  return 0;
}*/
