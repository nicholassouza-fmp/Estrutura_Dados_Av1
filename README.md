# 📚 Sistema de Gerenciamento de Notas — C e Python

Sistema desenvolvido como parte da **A1 - Avaliação Prática em Equipe**, da disciplina de **Estruturas de Dados**, no curso de **Análise e Desenvolvimento de Sistemas**.

O projeto tem como objetivo desenvolver um sistema para cadastro e gerenciamento de alunos e suas respectivas notas, utilizando conceitos de **estruturas de dados, estruturas de repetição e funções recursivas**.

---

## 🎯 Objetivo do Projeto

Desenvolver um sistema capaz de:

- Cadastrar alunos e suas notas;
- Listar os alunos cadastrados;
- Calcular a média geral da turma;
- Identificar a maior nota;
- Identificar a menor nota;
- Listar e contar alunos aprovados;
- Gerar estatísticas utilizando funções recursivas;
- Trabalhar os mesmos conceitos nas linguagens **C e Python**.

---

## 💻 Tecnologias Utilizadas

- **C**
- **Python**
- Estruturas de Dados
- Vetores e listas
- Estruturas de repetição
- Funções
- Recursividade
- Condicionais

---

## 📋 Funcionalidades

O sistema possui um menu principal com diferentes opções:

### 1. Cadastro de alunos

Permite cadastrar os alunos e suas respectivas notas.

Os dados são armazenados utilizando:

- Vetores em C;
- Listas em Python.

### 2. Listagem geral de alunos

Exibe todos os alunos cadastrados juntamente com suas notas.

### 3. Média geral da turma

Calcula a média de todas as notas cadastradas.

### 4. Maior e menor nota

Identifica a maior e a menor nota entre os alunos cadastrados.

### 5. Alunos aprovados

Lista os alunos que possuem nota maior ou igual a **7.0** e realiza a contagem dos aprovados.

### 6. Estatísticas com recursividade

Utiliza funções recursivas para realizar:

- Somatório das notas;
- Contagem de alunos aprovados.

### 7. Funcionalidades Extras

Novas funcionalidades que deixam o código mais dinâmico, mas mantendo o mesmo escopo do projeto.

As funcionalidades extras incluem:

- Busca sequencial: permite procurar um aluno pelo nome e verificar sua nota;
- Estatísticas complementares: apresenta informações adicionais sobre os alunos e suas notas;
- Soma recursiva de dígitos: recebe um número inteiro e calcula a soma de seus dígitos utilizando recursividade;
- Listagem inversa: exibe os alunos na ordem inversa em que foram cadastrados, utilizando recursividade;
- As funcionalidades extras são acessadas através de um submenu, mantendo a organização do menu principal.

---

## 🔄 Recursividade

Uma das principais características do projeto é a utilização de **funções recursivas** na opção de estatísticas.

Foram desenvolvidas duas funções principais:

```text
somaRecursiva(notas, totalAlunos)
```
---
## ✅ Validação de Dados

O sistema possui validações para evitar entradas incorretas.

Nome

São aceitos somente letras e espaços.

Nota

A nota deve estar no intervalo:

0.0 até 10.0

Entradas inválidas são rejeitadas e o sistema solicita uma nova informação ao usuário.

---
## ⚠️ Tratamento de Entradas

Os menus também possuem tratamento para opções inválidas.

Quando uma opção inexistente é informada, o sistema apresenta uma mensagem de erro e solicita uma nova opção.

O programa somente é encerrado quando o usuário escolhe a opção 0 - Encerrar

---
## 🔚 Conclusão

O projeto possibilitou aplicar na prática conceitos importantes da disciplina de Estruturas de Dados, principalmente o uso de vetores, listas, funções, busca sequencial e recursividade.

A implementação em C e Python também permitiu comparar diferentes formas de trabalhar com estruturas de dados e gerenciamento de informações.
