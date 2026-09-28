# Sistema Bancário — INF101

Projeto desenvolvido em **C++** como parte da disciplina **INF101 – Programação de Computadores I**, do curso de Análise e Desenvolvimento de Sistemas da UNIVIÇOSA.

## Sobre o Projeto

Este repositório contém uma implementação de um sistema bancário em C++, desenvolvida com fins acadêmicos. O sistema simula operações básicas de um banco — cadastro, consulta, movimentação e gerenciamento de contas — com autenticação por CPF e senha, persistência de dados em arquivo e menus interativos separados por perfil (Cliente e Gerente).

Este projeto é acompanhado desde sua primeira versão, que sequer compilava, até esta v1.3. O histórico de evolução é parte intencional do repositório: documenta decisões corrigidas, conceitos aplicados de forma incremental (POO, `<algorithm>`, tratamento de exceções) e erros identificados e resolvidos ao longo do tempo — não é um código "pronto desde o início".

## Funcionalidades

O sistema conta com dois perfis de acesso: **Cliente** e **Gerente**, cada um com um conjunto próprio de operações.

**Cliente**

- Consultar dados da conta
- Verificar saldo
- Realizar saque (com validação de saldo suficiente)
- Realizar depósito

**Gerente**

- Buscar informações de qualquer conta
- Cadastrar nova conta
- Ativar / desativar conta
- Alterar tipo de conta (Corrente ↔ Poupança)

Todo o fluxo de menus usa `enum` para as opções e captura entradas não numéricas com `try/catch`, evitando encerramentos abruptos por digitação inválida.

## Autenticação

A partir desta versão, o login exige **CPF e senha**, ambos definidos no momento do cadastro e armazenados como campos separados (a senha não é mais derivada do CPF). O acesso é limitado a **3 tentativas de senha** por sessão de login.

> A senha atualmente é armazenada como número inteiro, em texto puro no arquivo — ver seção "Limitações Conhecidas" para o plano de evolução desse ponto.

## Estrutura de Dados da Conta

Todas as contas são armazenadas em um único arquivo (`Banco.txt`), uma linha por conta, com os seguintes campos, em ordem:

| Campo           | Tipo   | Descrição                                |
| --------------- | ------ | ------------------------------------------ |
| CPF             | string | Identificador único da conta               |
| Nome do Cliente | string | Nome completo do titular                   |
| Número da Conta | int    | Número identificador da conta              |
| Tipo da Conta   | int    | 1 = Conta Corrente / 2 = Conta Poupança   |
| Status da Conta | int    | 1 = Ativa / 2 = Desativada                 |
| Saldo           | double | Saldo atual em reais                       |
| Senha           | int    | Senha de acesso (somente números, ver nota acima) |

## Estrutura do Projeto

```
├── Main.cpp        # Ponto de entrada do programa
├── Menu.hpp         # Cabeçalho das funções de menu e navegação
├── Menu.cpp         # Telas, menus, enums e fluxo de interação (Cliente/Gerente)
├── Conta.hpp         # Cabeçalho da classe Banco, login e senha
├── Conta.cpp         # Lógica de cadastro, autenticação e operações de conta
└── README.md
```

O projeto é dividido em dois módulos principais:

- **Conta** — classe `Banco` com atributos privados e getters/setters, responsável pela lógica de negócio: cadastro, autenticação, saldo, saque, depósito, alteração de tipo, ativação/desativação e persistência em arquivo.
- **Menu** — responsável pela camada de interação com o usuário: exibição de telas, menus, tratamento de exceções de entrada e roteamento entre os perfis Cliente e Gerente.

## Menu do Sistema

```
(1) Cliente
(2) Gerente
(3) Sair
```

**Menu Cliente**

```
(1) Verifica dados da conta
(2) Verifica saldo da conta
(3) Sacar
(4) Depositar
(5) Sair
```

**Menu Gerente**

```
(1) Buscar conta
(2) Cadastrar conta
(3) Ativar Conta
(4) Alterar o tipo de conta
(5) Sair
```

## Como Compilar e Executar

Desenvolvido e testado com **Visual Studio Code** e o compilador **GCC/MinGW**.

Compilar:

```bash
g++ Main.cpp Menu.cpp Conta.cpp -o SistemaBancario.exe
```

Executar (Windows):

```bash
./SistemaBancario.exe
```

> **Observação:** o projeto utiliza `system("cls")` para limpeza de tela, um recurso específico do Windows — ponto de melhoria já mapeado para versões futuras.

## Tecnologias Utilizadas

- C++ (com `<algorithm>`, `<vector>`, `<fstream>`)
- Visual Studio Code
- GCC / MinGW
- Git e GitHub

## Conceitos Aplicados

- Programação Orientada a Objetos: classe `Banco` com atributos privados, getters/setters e métodos que operam sobre o próprio estado do objeto
- `std::find_if` com lambdas para busca de registros em memória
- `enum` para as opções de menu, no lugar de números soltos no código
- Tratamento de exceções (`try/catch`) para entradas não numéricas
- Persistência de dados em arquivo, com leitura, atualização e regravação
- Autenticação por CPF e senha, com limite de tentativas

## Limitações Conhecidas (versão 1.3)

Transparência sobre o estado atual do projeto:

- [ ] A senha é armazenada como número inteiro, em texto puro (sem hash). A próxima etapa planejada é aplicar uma função de hash (`std::hash` ou uma biblioteca como `bcrypt`) antes de gravar e comparar a senha.
- [ ] Uma conta desativada pelo Gerente ainda consegue autenticar normalmente — a checagem de status durante o login precisa ser reintroduzida.
- [ ] `Sacar()` e `Depositar()` ainda não seguem o mesmo padrão de POO das demais operações da classe (ainda usam variáveis soltas em vez do objeto `Banco`) — conversão já planejada.
- [ ] `system("cls")` limita a portabilidade do projeto a sistemas Windows.
- [ ] Há duplicação de código entre as funções que leem `Banco.txt` — uma futura refatoração pode consolidar essa leitura em uma única função reaproveitada por todas.

Nenhum desses pontos compromete o funcionamento das operações principais do sistema — são melhorias de robustez e arquitetura mapeadas conscientemente para as próximas versões.

## Autor

**Bruno Marques**
Estudante de Análise e Desenvolvimento de Sistemas — UNIVIÇOSA (2º período)

## Status do Projeto

✅ **v1.3 — Autenticação por senha implementada, CPF tratado como string em todo o fluxo, POO consolidado na maior parte das operações.** Próximas etapas mapeadas na seção "Limitações Conhecidas".

## Licença

Projeto de uso acadêmico, desenvolvido para fins de aprendizado na disciplina INF101. Sem licença de distribuição definida.
