# Sistema Bancário — INF101

Projeto desenvolvido em **C++** como parte da disciplina **INF101 – Programação de Computadores I**, do curso de Análise e Desenvolvimento de Sistemas da UNIVIÇOSA.

## Sobre o Projeto

Este repositório contém uma implementação de um sistema bancário simples em C++, desenvolvida com fins acadêmicos. O objetivo é simular operações básicas de um banco — cadastro, consulta, movimentação e gerenciamento de contas — aplicando conceitos fundamentais da linguagem, como estruturas condicionais, laços de repetição, funções, tratamento de exceções, enumerações e organização modular de código em múltiplos arquivos `.cpp`/`.hpp`.

O sistema é executado via terminal, com navegação por menus, e persiste os dados de cada conta em arquivos de texto individuais, identificados pelo CPF do cliente.

Este é o **primeiro projeto completo** que desenvolvi de forma independente, e sua importância vai além do código em si: ele documenta minha curva de aprendizado real, do primeiro protótipo (que sequer compilava) até uma versão funcional com tratamento de exceções e enumerações. Optei por manter esse histórico de evolução como parte do valor do projeto — não é um código "perfeito desde o início", é um código que foi corrigido, revisado e melhorado de forma incremental, com cada decisão sendo compreendida antes de ser aplicada.

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

Todo o fluxo de menus utiliza `enum` para as opções (evitando "números mágicos" no código) e captura entradas não numéricas com `try/catch`, evitando que o programa encerre de forma abrupta diante de uma digitação inválida.

## Estrutura de Dados da Conta

Cada conta é armazenada em um arquivo de texto próprio (`<CPF>.txt`), contendo os seguintes campos, em ordem:

| Campo           | Tipo   | Descrição                               |
| --------------- | ------ | ---------------------------------------- |
| Nome do Cliente | string | Nome completo do titular                 |
| CPF             | string | Identificador único da conta             |
| Número da Conta | int    | Número identificador da conta            |
| Tipo da Conta   | int    | 1 = Conta Corrente / 2 = Conta Poupança |
| Status da Conta | int    | 1 = Ativa / 2 = Desativada                |
| Saldo           | double | Saldo atual em reais                     |

## Estrutura do Projeto

```
├── Main.cpp        # Ponto de entrada do programa
├── Menu.hpp         # Cabeçalho das funções de menu e navegação
├── Menu.cpp         # Telas, menus, enums e fluxo de interação (Cliente/Gerente)
├── Conta.hpp         # Cabeçalho da classe Banco e da função de login
├── Conta.cpp         # Lógica de cadastro, login e operações de conta
└── README.md
```

O projeto é dividido em dois módulos principais:

- **Conta** — responsável pela lógica de negócio: cadastro, login, saldo, saque, depósito, alteração de tipo, ativação/desativação e persistência em arquivo.
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

O projeto foi desenvolvido e testado utilizando o **Visual Studio Code**, com o compilador **GCC/MinGW**, no terminal integrado.

Compilar o projeto:

```bash
g++ Main.cpp Menu.cpp Conta.cpp -o SistemaBancario.exe
```

Executar (Windows):

```bash
./SistemaBancario.exe
```

> **Observação:** o projeto utiliza o comando `system("cls")` para limpeza de tela, um recurso específico do Windows. A execução em outros sistemas operacionais exigirá adaptação desse trecho — este é um ponto de melhoria já identificado e mapeado para versões futuras.

## Tecnologias Utilizadas

- C++
- Visual Studio Code
- GCC / MinGW
- Git e GitHub

## Objetivos de Aprendizagem

Este projeto foi desenvolvido para praticar:

- Lógica de programação e organização de código em múltiplos arquivos
- Estruturas de decisão e repetição
- Manipulação de arquivos para persistência de dados
- Construtores e inicialização de estado em classes
- Enumerações (`enum`) para substituir valores numéricos soltos
- Tratamento de exceções (`try/catch`) para entradas inválidas
- Boas práticas de nomenclatura, qualificação de namespace e separação de responsabilidades
- Documentação de projetos para publicação no GitHub

## Limitações Conhecidas (versão 1.0)

Sendo transparente sobre o estado atual do projeto:

- [ ] O login não permite nova tentativa em caso de CPF inexistente ou conta desativada — atualmente o programa é encerrado (`exit()`) nesses casos. Esta é a próxima melhoria planejada.
- [ ] A lógica de conta ainda está organizada em uma classe `Banco` que concentra várias responsabilidades; uma futura refatoração para uma classe `Conta` dedicada está prevista.
- [ ] `system("cls")` é específico do Windows, limitando a portabilidade.
- [ ] Não há autenticação por senha (login é validado apenas pela existência do CPF/arquivo).
- [ ] `stoi`/`stod` dentro de `Conta.cpp` ainda não estão protegidos por `try/catch` (apenas as entradas de menu em `Menu.cpp` estão).

Nenhum desses pontos compromete o funcionamento das operações principais do sistema — são melhorias de robustez e arquitetura mapeadas conscientemente para as próximas versões.

## Autor

**Bruno Marques**
Estudante de Análise e Desenvolvimento de Sistemas — UNIVIÇOSA (2º período)

## Status do Projeto

✅ **v1.0 — Primeiro projeto completo e funcional.** Operações principais de Cliente e Gerente implementadas, testadas e com tratamento de exceções para entrada inválida. Próximas etapas já mapeadas (ver seção "Limitações Conhecidas").

## Licença

Projeto de uso acadêmico, desenvolvido para fins de aprendizado na disciplina INF101. Sem licença de distribuição definida.
