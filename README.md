# Trabalho 1 - Geometria Computacional

Este repositório contém a implementação do primeiro trabalho da disciplina **Geometria Computacional (CI1338)** da **Universidade Federal do Paraná (UFPR)**, com foco na **classificação de polígonos** e na **verificação de pontos interiores** utilizando algoritmos geométricos clássicos.

## Problema

Dado:
- Um conjunto `S` de **polígonos fechados** (descritos por seus vértices).
- Um conjunto `P` de **pontos no plano**.

O objetivo é:
1. **Classificar** cada polígono de `S` como:
   - `nao simples`
   - `simples e convexo`
   - `simples e nao convexo`
2. Para cada ponto `p ∈ P`, listar quais polígonos **simples** o contêm.

## Solução

A solução foi dividida em três partes:

- **Verificação de simplicidade:**  
  Implementada por força bruta, verificando interseção entre todas as arestas (complexidade O(n²)).

- **Teste de convexidade:**  
  Baseado na consistência do sinal dos produtos vetoriais entre arestas consecutivas.

- **Verificação de ponto dentro do polígono:**  
  Utiliza o algoritmo de **Ray Casting**, com tratamento completo de casos degenerados (como pontos sobre vértices ou arestas).

## Execução

A entrada deve ser feita via `stdin` e a saída via `stdout`. Exemplo de uso:

```bash
$ ./poligonos < entrada.txt > saida.txt
