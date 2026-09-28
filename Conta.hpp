#ifndef CONTA_HPP
#define CONTA_HPP

#include <string>

class Banco
{
  private:
  std::string nome, cpf;
  int nconta, tpconta, senha, ativaconta;
  double saldoconta;

  public:
  Banco(): nome(""), cpf(""), senha(0), nconta(0), tpconta(0), ativaconta(0), saldoconta(0.0){
    /*O construtor tem que ser declarado para poder fazer a linkagem
    independente se vai colocar alguma coisa aqui ou não*/
  }
  Banco (const std::string& nome,
         const std::string& cpf,
         int senha,
         const int nconta,
         int tpconta,
         int ativaconta,
         double saldoconta);
  

  /*Set */
void setnome(const std::string& nome);
void setcpf(const std::string& cpf);
void setnconta(int nconta);
void setsenha(int senha);
void settpconta(int tpconta);
void setativaconta (int ativaconta);
void setsaldoconta(double saldoconta);

/*Get*/

std::string getnome() const;
std::string getcpf () const;
int getnconta() const;
int getsenha() const;
int gettpconta() const;
int getatiaconta() const;
double getsaldoconta () const;


  /*Conta*/

  /*Cliente*/

 
  void verSaldo(std::string veSaldo); /*OK*/
  
  int Depositar(std::string cpfConta, double Depsaldo); /*OK*/
 
  /*Gerente*/
  void buscar (std::string numCpf); /*OK*/

  int Sacar(std::string cpfConta, double Atsaldo); /*OK*/
 
  int TipoConta(std::string numCpf);

  int Ativaconta(std::string numCpf);
  /*int desativarConta(string cpfD);*/

  /*Novo*/
  int Cadastrar(); /*OK*/

  void registrarConta(); /*OK*/

  
};


void login(const std::string& Logar);

bool senha(const Banco& conta);

#endif