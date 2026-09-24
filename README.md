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

### 7. Encerramento

Finaliza a execução do sistema.

---

## 🔄 Recursividade

Uma das principais características do projeto é a utilização de **funções recursivas** na opção de estatísticas.

Foram desenvolvidas duas funções principais:

```text
somaRecursiva(notas, totalAlunos)
