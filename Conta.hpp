#ifndef CONTA_HPP
#define CONTA_HPP

#include <string>

class Banco
{
  private:
  std::string nome, cpf;
  int nconta, tpconta, ativaconta;
  double saldoconta;

  public:
  Banco(): nome(""), cpf(""), nconta(0), tpconta(0), ativaconta(0), saldoconta(0.0){
    /*O construtor tem que ser declarado para poder fazer a linkagem
    independente se vai colocar alguma coisa aqui ou não*/
  }
  Banco (const std::string& nome,
         const std::string& cpf,
         const int nconta,
         int tpconta,
         int ativaconta,
         double saldoconta);
  
  int Cadastrar();
  void verSaldo(std::string veSaldo);
  int Sacar(std::string Retirada, double Saque);
  int Depositar(std::string Aportar, double Deposito);
 
  /*Gerente*/
  
  void registrarConta (std::string nomeA, std::string cpfA, int numcontaA, int tipocontaA, int ativacontaA, double saldoA);
  int consultarConta (std::string Consultar);
  int altTipoconta(std::string Alterar);
  int ativarConta(std::string Status);
  /*int desativarConta(string cpfD);*/
};


void login (std::string Logar);

void Existe(std::string existe);

int senha(std::string senha);

#endif
