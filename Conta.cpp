#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <iomanip>
#include <limits>
#include <algorithm> /*Importante para usar o find_if*/
#include <cstdio> /*Importante para usar remove e rename*/
#include "Conta.hpp"
#include "Menu.hpp"

Banco::Banco(const std::string& nome,
         const std::string& cpf,
         int senha,
         const int nconta,
         int tpconta,
         int ativaconta,
         double saldoconta){
}

  /*Set */
void Banco::setnome(const std::string& nome){
  this->nome = nome;
}
void Banco::setcpf(const std::string& cpf){
  this->cpf = cpf;
}
void Banco::setnconta(int nconta){
  this->nconta = nconta;
}
void Banco::settpconta(int tpconta){
  this->tpconta = tpconta;
}
void Banco::setativaconta (int ativaconta){
  this->ativaconta = ativaconta;
}
void Banco::setsaldoconta(double saldoconta){
  this->saldoconta = saldoconta;
}
void Banco::setsenha(const int senhaConta){
  this-> senha = senhaConta;
}

/*Get*/

std::string Banco::getnome() const{
  return nome;
}
std::string Banco::getcpf () const{
  return cpf;
}
int Banco::getnconta() const{
  return nconta;
}
int Banco::gettpconta() const{
  return tpconta;
}
int Banco::getatiaconta() const{
  return ativaconta;
}
double Banco::getsaldoconta () const{
  return saldoconta;
}
int Banco::getsenha () const {
  return senha;
}


/*-------------------------------------------------------*/

std::vector<Banco> carregarDados();
bool senha(const Banco& conta);

// Lê o arquivo uma única vez e devolve todas as contas
std::vector<Banco> carregarDados() {
    std::vector<Banco> dados;
    std::ifstream arquivo("Banco.txt", std::ios::in);

    if (!arquivo.is_open()) {
        std::cout << "Erro ao abrir Banco.txt" << std::endl;
        return dados; // vetor vazio
    }

    std::string nome, cpf;
    int nconta, tpconta, ativaconta, senhaconta;
    double saldoconta;

    while (arquivo >> cpf >> nome >> nconta >> tpconta >> ativaconta >> saldoconta >> senhaconta) {
        Banco d;
        d.setcpf(cpf);
        d.setnome(nome);
        d.setnconta(nconta);
        d.settpconta(tpconta);
        d.setativaconta(ativaconta);
        d.setsaldoconta(saldoconta);
        d.setsenha(senhaconta);
        dados.push_back(d);
    }

    return dados; // o ifstream fecha sozinho ao sair do escopo
}


bool senha(const Banco& conta) {
    const int MAX_TENTATIVAS = 3;

    for (int tentativa = 1; tentativa <= MAX_TENTATIVAS; tentativa++) {
        limpartela();
        
        std::cout << "Tentativa " << tentativa << " de " << MAX_TENTATIVAS << std::endl;
        std::cout << "Digite a sua senha: ";
        int verificaSenha;
        if (!(std::cin >> verificaSenha)) {
            std::cin.ignore();
            // entrada inválida (letras, por exemplo): limpa o erro e conta como tentativa
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada invalida." << std::endl;
            continue;
        }

        if (verificaSenha == conta.getsenha()) {
            std::cout << "Seja bem vindo, " << conta.getnome() << "!" << std::endl;
            return true;
        }

        std::cout << "Senha incorreta." << std::endl;
    }

    std::cout << "Numero de tentativas esgotado." << std::endl;
    return false;
}

void login(const std::string& Logar) {
    std::vector<Banco> dados = carregarDados();

    auto it = std::find_if(dados.begin(), dados.end(),
        [&Logar](const Banco& b) { return b.getcpf() == Logar; });

    if (it == dados.end()) {
        std::cout << "Conta nao encontrada" << std::endl;
        std::cin.get();
        menuEntrada();
        return;
    }

    if (senha(*it)) {
        std::cout << "Login bem sucedido";
    } else {
        menuEntrada();
    }
}

/*--------------------------------------------------------*/


/* Esta função é responsável por captura os dados inseridos pelo Usuário
   realizando o cadastro no banco, que nesta versão permanece apenas na 
   memória enquanto o programa estiver rodando*/
int Banco::Cadastrar(){
   
  std::string nome, cpf;
  int numconta, tipoconta,senha;
  double saldo;
  
  std::cout << "Nome " << std::endl;
  std::getline(std::cin, nome);
  setnome(nome);
  std::cout << "Cpf " << std::endl;
  std::getline(std::cin, cpf);
  setcpf(cpf);
  std::cout << "Numero da conta: " << std::endl;
  std::cin >> numconta;
  setnconta(numconta);
  if (numconta > 0){
    std::cout << "Tipo da conta " << std::endl;
    std::cin >> tipoconta;
    settpconta(tipoconta);
    if (tipoconta > 0 && tipoconta < 3){
      std::cout << "Saldo em conta " << std::endl;
      std::cin >> saldo;
      setsaldoconta(saldo);
      if (saldo > 0){ 
        ativaconta = 1;
        setativaconta(ativaconta);
      std::cout << "Crie a sua senha (somente numeros): ";    
      std::cin >> senha;
      setsenha(senha);
        registrarConta();
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

/*--------------Gerente--------------------*/

/* Esta função é responsável por registrar os dados coletados pela cadastrar*/
void Banco::registrarConta(){
   
  std::ofstream escreverArquivo ("Banco.txt",std::ios::app);
  
  escreverArquivo << getcpf() << " " << getnome() << " " << getnconta() << " " << gettpconta() << " "  << getatiaconta() << " " << getsaldoconta() << " " << getsenha() << "\t" << std::endl; 
     
  escreverArquivo.close();
  return;
}

/*Está função é responsável por busca a conta, utilizando com base o cpf,
  poderia ser o numero da conta, ou qualquer outra condição, desde que
  especificada no arquivo Conta.hpp*/
void Banco::buscar (std::string numCpf){

std::vector <Banco> dados;
std::string Tempcpf;
std::ifstream arquivo ("Banco.txt", std::ios::in);

if (!arquivo.is_open()){
  std::cout << "Deu erro";
  
}

std::string nome,cpf;
int nconta, tpconta, ativaconta, senhaconta;
double saldoconta;

/*Banco(): nome(""), cpf(""), nconta(0), tpconta(0), ativaconta(0), saldoconta(0.0*/
while(arquivo >> cpf >> nome >> nconta >> tpconta >> ativaconta >> saldoconta >> senhaconta){
  
  Banco d;    
  d.setcpf(cpf);
  d.setnome(nome);
  d.setnconta(nconta);
  d.settpconta(tpconta);
  d.setativaconta(ativaconta);
  d.setsaldoconta(saldoconta);
  d.setsenha(senhaconta);
  dados.push_back(d);
}

arquivo.close();

std::string indice = numCpf;

auto it = std::find_if (dados.begin(), dados.end(),[indice](const Banco& b){return b.getcpf() == indice;});
if (it != dados.end()){
 
  std::cout << "Dados da conta" << std::endl;
  std::cout << "CPF: " << it->getcpf() << std::endl;
  std::cout << "Nome do cliente: " << it->getnome() << std::endl;
  std::cout << "Numero da conta: " << it->getnconta() << std::endl;
  std::cout << "Tipo de conta: " << it->gettpconta() << std::endl;
  std::cout << "Ativa/Desativa conta: " << it->getatiaconta() << std::endl;
  std::cout << "Saldo em conta: " << std::fixed << std::setprecision(2) << it->getsaldoconta() << std::endl;
  std::cin.get();
}

}

int Banco::Ativaconta(std::string numCpf){
  std::vector <Banco> dados;

  /*Função ler o arquivo permanente Banco.txt*/
  std::ifstream Arqpermanente ("Banco.txt",std::ios::in);
  
  /*Funcão cira um arquivo temporário TEMPBanco.txt*/
  std::ofstream Arqtemporario ("TEMPBanco.txt", std::ios::out);

  limpartela();
  
  if (!Arqpermanente.is_open() || !Arqtemporario.is_open()){
    std::cerr << "Acesso Negado" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  /*Após verifica a condicional de acesso, criasse as variáveis que serão utilizadas no laço*/
  std::string cpf, nome;
  int nconta, tpconta, atconta, senhaconta;
  double saldo;
  bool encontrado = false;

  while (Arqpermanente >> cpf >> nome >> nconta >> tpconta >> atconta >> saldo >> senhaconta){
    Banco d;

    d.setcpf(cpf);
    d.setnome(nome);
    d.setnconta(nconta);
    d.settpconta(tpconta);
    d.setativaconta(atconta);
    d.setsaldoconta(saldo);
    d.setsenha(senhaconta);

    dados.push_back(d);

    if(numCpf == cpf){
      encontrado = true;
      int Ativa;

      std::cout << "Ativa Conta (1) Desativar Conta (2)";
      std::cin >> Ativa;
      
      if (Ativa > 0 && Ativa <= 2){
        d.setativaconta(Ativa);
      }
    }

    Arqtemporario << std::fixed << std::setprecision(2);
    Arqtemporario << d.getcpf() << " " << d.getnome() << " " << d.getnconta() << " " << d.gettpconta() << " "  << d.getatiaconta() << " " << d.getsaldoconta() << " " << d.getsenha() << "\n";
  }
  
  Arqpermanente.close();
  Arqtemporario.close();

  if(encontrado){
    remove("Banco.txt");
    rename("TEMPBanco.txt","Banco.txt");
    limpartela();
  }
  else {
    remove("TEMPBanco.txt");
    std::cout << "Arquivo nao encontrado";
  }
   
  return 0;
}
/*Única função altera o tipo de conta poupanca e corrente.
Atualização futura imagino que seja classifica 
cliente de varejo e private bank*/

int Banco::TipoConta(std::string numCpf){
  std::vector <Banco> dados;
  std::cin.clear();
  /*Função ler o arquivo permanente Banco.txt*/
  std::ifstream Arqpermanente ("Banco.txt",std::ios::in);
  
  /*Funcão cira um arquivo temporário TEMPBanco.txt*/

  std::ofstream Arqtemporario ("TEMPBanco.txt", std::ios::out);


  limpartela();
  
  if (!Arqpermanente.is_open() || !Arqtemporario.is_open()){
    std::cerr << "Acesso Negado" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  /*Após verifica a condicional de acesso, criasse as variáveis que serão utilizadas no laço*/
  std::string cpf, nome;
  int nconta, tpconta, atconta, senhaconta;
  double saldo;
  bool encontrado = false;
 

  while (Arqpermanente >> cpf >> nome >> nconta >> tpconta >> atconta >> saldo >> senhaconta){
     
    Banco d;
    
    d.setcpf(cpf);
    d.setnome(nome);
    d.setnconta(nconta);
    d.settpconta(tpconta);
    d.setativaconta(atconta);
    d.setsaldoconta(saldo);
    d.setsenha(senhaconta);

    dados.push_back(d);
    
    if(numCpf == cpf){
    encontrado = true;

    int Tipo;

    std::cout << "Altere tipo de conta (1)Conta Corrente (2)Poupanca: ";
    std::cin >> Tipo;
    
    if (Tipo >= 1 && Tipo <= 2){
    
      d.settpconta(Tipo);
          
    }
  }
  Arqtemporario << std::fixed << std::setprecision(2);
  /* Arqtemporario << cpf << " " << nome << " " << nconta << " " << tpconta << " "  << atconta << " " << saldo << "\n"; */
  Arqtemporario << d.getcpf() << " " << d.getnome() << " " << d.getnconta() << " " << d.gettpconta() << " " << d.getatiaconta() << " " << d.getsaldoconta() << " " << d.getsenha() << "\n";
}
  
  Arqpermanente.close();
  Arqtemporario.close();

  if(encontrado){
    remove("Banco.txt");
    rename("TEMPBanco.txt","Banco.txt");
    limpartela();
  }
  else {
    remove("TEMPBanco.txt");
    std::cout << "Arquivo nao encontrado";
  }  
  
  return 0;
}

/*--------------Cliente--------------------*/

/*Única função verifica o saldo em conta
Atualização futura distiguir conta poupanca e corrente.*/
void Banco::verSaldo(std::string veSaldo){

std::vector <Banco> dados;
std::string Tempcpf;
std::ifstream arquivo ("Banco.txt", std::ios::in);


if (!arquivo.is_open()){
  std::cout << "Deu erro";
  
}

std::string nome,cpf;
int nconta, tpconta, ativaconta, senhaconta;
double saldoconta;

int Icpf;

/*Banco(): nome(""), cpf(""), nconta(0), tpconta(0), ativaconta(0), saldoconta(0.0*/
while(arquivo >> cpf >> nome >> nconta >> tpconta >> ativaconta >> saldoconta >> senhaconta){
  
  Banco d;    
  d.setnome(nome);
  d.setcpf(cpf);
  d.setnconta(nconta);
  d.settpconta(tpconta);
  d.setativaconta(ativaconta);
  d.setsaldoconta(saldoconta);
  d.setsenha(senhaconta);

  dados.push_back(d);
}

arquivo.close();

std::string indice = veSaldo;

auto it = std::find_if (dados.begin(), dados.end(),[indice](const Banco& b){return b.getcpf() == indice;});
if (it != dados.end()){
  std::cout << "Dados da conta" << std::endl;
  std::cout << "Saldo em conta: " << it->getsaldoconta() << std::endl;
}

}

/*Única função realizar o saque em conta
Atualização futura distiguir conta poupanca e corrente.*/
int Banco::Sacar(std::string cpfConta, double Atsaldo){

  /*Função ler o arquivo permanente Banco.txt*/
  std::ifstream Arqpermanente ("Banco.txt",std::ios::in);
  
  /*Funcão cira um arquivo temporário TEMPBanco.txt*/

  std::ofstream Arqtemporario ("TEMPBanco.txt", std::ios::out);


  limpartela();
  
  if (!Arqpermanente.is_open() || !Arqtemporario.is_open()){
    std::cerr << "Acesso Negado" << std::endl;
    std::cin.get();
    std::exit(EXIT_FAILURE);
  }

  /*Após verifica a condicional de acesso, criasse as variáveis que serão utilizadas no laço*/
  std::string cpf, nome;
  int nconta, tpconta, atconta, senhaconta;
  double saldo;
  bool encontrado = false;

  while (Arqpermanente >> cpf >> nome >> nconta >> tpconta >> atconta >> saldo >> senhaconta){
    if(cpfConta == cpf){
    if(saldo >= Atsaldo){
    
    encontrado = true;

    saldo = saldo - Atsaldo;
    }
    else {
    
      std::cout << "Saldo insuficiente";
    
      std::cin.ignore();
    }
  }
    Arqtemporario << cpf << " " << nome << " " << nconta << " " << tpconta << " "  << atconta << " " << saldo <<  " " << senhaconta << "\n";
  }

  Arqpermanente.close();
  Arqtemporario.close();

  if(encontrado){
    remove("Banco.txt");
    rename("TEMPBanco.txt","Banco.txt");
    limpartela();
    
  }
  else {
    remove("TEMPBanco.txt");
  }
  
  
  return encontrado ? 1 : 0;
}

/*Única função realizar deposito em sem conta
Atualização futura distiguir conta poupanca e corrente.*/
int Banco::Depositar(std::string cpfConta, double Depsaldo){
  /*Função ler o arquivo permanente Banco.txt*/
  std::ifstream Arqpermanente ("Banco.txt",std::ios::in);
  
  /*Funcão cira um arquivo temporário TEMPBanco.txt*/

  std::ofstream Arqtemporario ("TEMPBanco.txt", std::ios::out);


  limpartela();
  
  if (!Arqpermanente.is_open() || !Arqtemporario.is_open()){
    std::cerr << "Acesso Negado" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  /*Após verifica a condicional de acesso, criasse as variáveis que serão utilizadas no laço*/
  std::string cpf, nome;
  int nconta, tpconta, atconta, senhaconta;
  double saldo;
  bool encontrado = false;

  while (Arqpermanente >> cpf >> nome >> nconta >> tpconta >> atconta >> saldo >> senhaconta){
    if(cpfConta == cpf){
    
    encontrado = true;
    if (Depsaldo > 0){  
    saldo = saldo + Depsaldo;
    }
  }
    Arqtemporario << cpf << " " << nome << " " << nconta << " " << tpconta << " "  << atconta << " " << saldo << " " << senhaconta << "\n";
  }

  Arqpermanente.close();
  Arqtemporario.close();

  if(encontrado){
    remove("Banco.txt");
    rename("TEMPBanco.txt","Banco.txt");
    limpartela();
  }
  else {
    remove("TEMPBanco.txt");
    std::cout << "Arquivo nao encontrado";
  }
 
  return 0;
}