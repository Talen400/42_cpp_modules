# CPP Module 08 — STL: Containers, Iterators, Algorithms

Esse módulo é sobre a **STL (Standard Template Library)** — a biblioteca de containers,
iterators e algoritmos genéricos do C++. Finalmente você pode usar `std::vector`,
`std::list`, `<algorithm>` e tudo mais.

---

## Índice

1. [O que é a STL?](#1-o-que-é-a-stl)
2. [Exercício 00 — easyfind](#2-exercício-00--easyfind)
3. [Exercício 01 — Span](#3-exercício-01--span)
4. [Exercício 02 — MutantStack](#4-exercício-02--mutantstack)
5. [Bibliotecas usadas — detalhado](#5-bibliotecas-usadas--detalhado)
6. [Dicas finais](#6-dicas-finais)

---

## 1. O que é a STL?

### 1.1 A trindade da STL

A STL é baseada em três componentes que trabalham juntos:

```
Container:   Onde os dados ficam (vector, list, deque, map, set...)
    │
    ▼
Iterator:    Ponteiro genérico que percorre o container (begin, end, ++, *)
    │
    ▼
Algorithm:   Função que opera sobre os dados via iterators (find, sort, for_each...)
```

### 1.2 Containers mais comuns

| Container | Inclusão | Característica |
|-----------|----------|----------------|
| `std::vector` | `<vector>` | Array dinâmico, acesso O(1), inserção no final O(1) |
| `std::list` | `<list>` | Lista duplamente ligada, inserção O(1), sem acesso aleatório |
| `std::deque` | `<deque>` | Fila dupla, acesso O(1), inserção nas pontas O(1) |
| `std::stack` | `<stack>` | LIFO (pilha), **adapter** — não tem iterators |
| `std::queue` | `<queue>` | FIFO (fila), **adapter** — não tem iterators |
| `std::map` | `<map>` | Árvore binária chave-valor, O(log n) |
| `std::set` | `<set>` | Conjunto ordenado, O(log n) |

### 1.3 Container Adapters

`std::stack` e `std::queue` não são containers de verdade — são **adapters** que
encapsulam outro container (por padrão `std::deque`) e só expõem uma interface
restrita.

```
std::stack<int>   (interface: push, pop, top, empty, size)
       │
       └── usa std::deque por baixo (mas você não vê)
```

É por isso que `std::stack` não tem iterators — o adapter propositalmente esconde
o container subjacente.

### 1.4 Algoritmos do `<algorithm>`

| Algoritmo | O que faz |
|-----------|-----------|
| `std::find(first, last, value)` | Encontra primeira ocorrência |
| `std::sort(first, last)` | Ordena o range |
| `std::min_element(first, last)` | Menor elemento |
| `std::max_element(first, last)` | Maior elemento |
| `std::minmax_element(first, last)` | Menor e maior (junto) |
| `std::adjacent_difference(first, last, result)` | Diferenças entre adjacentes |
| `std::for_each(first, last, func)` | Aplica função a cada elemento |
| `std::distance(first, last)` | Distância entre iterators |

### 1.5 Iterators — a cola entre containers e algoritmos

Um iterator é um objeto que se comporta como um ponteiro:

```cpp
std::vector<int> v;
v.push_back(10);
v.push_back(20);
v.push_back(30);

std::vector<int>::iterator it = v.begin();
// it aponta para o primeiro elemento

*it;       // 10 (acessa o elemento)
++it;      // avança para o próximo
*it;       // 20
--it;      // volta
it != v.end();  // compara com o "fim" (end = após o último)
```

**Visualmente:**

```
v.begin()                                          v.end()
    ↓                                                ↓
  [ 10 ] [ 20 ] [ 30 ]
    ↑
    it

Após ++it:
  [ 10 ] [ 20 ] [ 30 ]
            ↑
            it
```

**Tipos de iterator:**

| Iterator | Operações | Containers |
|----------|-----------|------------|
| Input | `++`, `*` (leitura) | istream, qualquer entrada |
| Output | `++`, `*` (escrita) | ostream, qualquer saída |
| Forward | `++`, `*` (leitura/escrita) | forward_list (C++11) |
| Bidirectional | `++`, `--`, `*` | list, map, set |
| Random Access | `++`, `--`, `+`, `-`, `[]` | vector, deque, array |

### 1.6 Funcionamento típico de um algoritmo STL

```
std::find(v.begin(), v.end(), 42);

    begin                                          end
      ↓                                            ↓
    [ 5 ] [ 12 ] [ 42 ] [ 7 ] [ 99 ]
                  ↑
                  find retorna iterator para o 42

Se não achar:
    [ 5 ] [ 12 ] [ 7 ]
                       ↑
                       find retorna end()
```

---

## 2. Exercício 00 — easyfind

### 2.1 O que o exercício quer

```cpp
template <typename T>
/* ??? */ easyfind(T& container, int value);
```

Uma função template que:
1. Recebe um container de inteiros
2. Recebe um valor inteiro para procurar
3. Retorna a primeira ocorrência ou lança exceção

### 2.2 Implementação

```cpp
template <typename T>
typename T::iterator easyfind(T& container, int value) {
    typename T::iterator it = std::find(container.begin(), container.end(), value);
    if (it == container.end())
        throw std::exception();
    return it;
}
```

**Explicação passo a passo:**

1. `std::find(container.begin(), container.end(), value)` percorre do início ao fim
   procurando o valor
2. Se achar, retorna iterator apontando pro elemento
3. Se não achar, retorna `container.end()` (fim do container)
4. Se retornou `end()`, lançamos exceção

**Por que `typename T::iterator`?** Porque `T::iterator` é um **tipo dependente**
(dependent type) — depende do template T. O compilador precisa do `typename` pra
saber que `T::iterator` é um tipo e não um membro estático.

### 2.3 Versão const

Para containers const:

```cpp
template <typename T>
typename T::const_iterator easyfind(const T& container, int value) {
    typename T::const_iterator it = std::find(container.begin(), container.end(), value);
    if (it == container.end())
        throw std::exception();
    return it;
}
```

Ou você pode usar um único template com `T&` e `const T&` como overloads.

### 2.4 Funcionamento com diferentes containers

```cpp
// Com vector
std::vector<int> v;
v.push_back(10);
v.push_back(20);
v.push_back(30);
std::vector<int>::iterator it = easyfind(v, 20);  // it aponta para 20

// Com list
std::list<int> l;
l.push_back(5);
l.push_back(10);
std::list<int>::iterator it2 = easyfind(l, 5);    // it2 aponta para 5

// Com deque
std::deque<int> d;
d.push_back(1);
d.push_back(2);
std::deque<int>::iterator it3 = easyfind(d, 99);  // lança exceção!
```

### 2.5 Por que "não associativos"?

O subject diz: "Você não precisa lidar com containers associativos."

Containers associativos (`map`, `set`, `multimap`, `multiset`) têm uma interface
diferente. `std::map::iterator` aponta pra `std::pair<const Key, Value>`, não
diretamente pra um inteiro. O exercício simplifica focando só em containers
sequenciais (`vector`, `list`, `deque`).

---

## 3. Exercício 01 — Span

### 3.1 O que o exercício quer

Classe que armazena até N inteiros e calcula distâncias entre eles:

```cpp
Span sp(5);
sp.addNumber(6);
sp.addNumber(3);
sp.addNumber(17);
sp.addNumber(9);
sp.addNumber(11);

sp.shortestSpan();  // 2 (diferença entre 6 e 9 = 3? Não: |17-11| = 6? Não: ordenar!)
sp.longestSpan();   // 14 (17 - 3)
```

**span = distância entre dois números (diferença absoluta).**

### 3.2 Algoritmo do shortestSpan

```cpp
int Span::shortestSpan() const {
    if (_numbers.size() < 2)
        throw std::exception();

    std::vector<int> sorted = _numbers;
    std::sort(sorted.begin(), sorted.end());

    int min = sorted[1] - sorted[0];
    for (size_t i = 2; i < sorted.size(); i++) {
        int diff = sorted[i] - sorted[i - 1];
        if (diff < min)
            min = diff;
    }
    return min;
}
```

**Visualmente:**

```
Antes do sort:  [6, 3, 17, 9, 11]

Depois do sort: [3, 6, 9, 11, 17]

Diferenças:
   3 → 6  = 3
   6 → 9  = 3
   9 → 11 = 2  ← menor!
  11 → 17 = 6

shortestSpan = 2
```

### 3.3 Algoritmo do longestSpan

```cpp
int Span::longestSpan() const {
    if (_numbers.size() < 2)
        throw std::exception();

    int min = *std::min_element(_numbers.begin(), _numbers.end());
    int max = *std::max_element(_numbers.begin(), _numbers.end());
    return max - min;
}
```

Ou, mais eficiente (uma passada só):

```cpp
std::pair<std::vector<int>::const_iterator,
          std::vector<int>::const_iterator> minmax = std::minmax_element(_numbers.begin(), _numbers.end());
return *minmax.second - *minmax.first;
```

### 3.4 Range de iteradores

O subject pede: "Implemente uma função membro para adicionar vários números ao
seu Span em uma única chamada."

```cpp
template <typename InputIterator>
void Span::addNumber(InputIterator begin, InputIterator end) {
    while (begin != end) {
        addNumber(*begin);
        ++begin;
    }
}
```

Uso:

```cpp
std::vector<int> many;
for (int i = 0; i < 10000; i++)
    many.push_back(rand() % 100000);

Span sp(10000);
sp.addNumber(many.begin(), many.end());  // adiciona de uma vez!
```

**Mas cuidado:** se o Span tem capacidade N e você tenta adicionar mais que N,
a exceção é lançada no meio e alguns números já foram adicionados. Você pode
querer verificar `std::distance(begin, end) <= capacidade restante` antes.

### 3.5 Teste com 10.000+ números

```cpp
srand(time(NULL));

Span sp(20000);
for (int i = 0; i < 20000; i++)
    sp.addNumber(rand());

std::cout << sp.shortestSpan() << std::endl;
std::cout << sp.longestSpan() << std::endl;
```

---

## 4. Exercício 02 — MutantStack

### 4.1 O problema

`std::stack` é um container adapter. Ele esconde o container interno e só
expõe `push`, `pop`, `top`, `empty`, `size`. Não tem `begin()` nem `end()`.

```cpp
std::stack<int> s;
s.push(1);
s.push(2);
s.push(3);

// Queremos iterar, mas não dá:
for (/* ??? */)  // não existe begin/end!
```

### 4.2 Dentro do std::stack

Por baixo dos panos, `std::stack<T>` usa um container (padrão: `std::deque<T>`) e
guarda ele como um membro **protected** chamado `c`:

```cpp
// Aproximação do que tem dentro de <stack>:
template <typename T, typename Container = std::deque<T> >
class stack {
protected:
    Container c;  // o container REAL está aqui
public:
    void push(const T& x) { c.push_back(x); }
    void pop()            { c.pop_back(); }
    T& top()              { return c.back(); }
    bool empty()          { return c.empty(); }
    size_t size()         { return c.size(); }
};
```

O `c` é `protected`, então só pode ser acessado por **herança**.

### 4.3 A solução: MutantStack

```cpp
template <typename T>
class MutantStack : public std::stack<T> {
public:
    typedef typename std::stack<T>::container_type::iterator iterator;
    typedef typename std::stack<T>::container_type::const_iterator const_iterator;
    typedef typename std::stack<T>::container_type::reverse_iterator reverse_iterator;
    typedef typename std::stack<T>::container_type::const_reverse_iterator const_reverse_iterator;

    iterator begin() { return this->c.begin(); }
    iterator end()   { return this->c.end(); }
    const_iterator begin() const { return this->c.begin(); }
    const_iterator end() const   { return this->c.end(); }

    reverse_iterator rbegin() { return this->c.rbegin(); }
    reverse_iterator rend()   { return this->c.rend(); }
    const_reverse_iterator rbegin() const { return this->c.rbegin(); }
    const_reverse_iterator rend() const   { return this->c.rend(); }
};
```

**O que acontece aqui:**

1. `MutantStack` herda de `std::stack<T>` — ganha `push`, `pop`, `top`, `size`, `empty`
2. O membro `c` (do tipo `container_type`) está acessível via `this->c`
3. `std::stack<T>::container_type` é `std::deque<T>` (por padrão), que TEM iterators
4. Expomos `begin()` e `end()` que chamam `c.begin()` e `c.end()`

**Visualmente:**

```
MutantStack<int>:

  ┌─ std::stack<int> ──────────────────┐
  │  protected:                         │
  │    std::deque<int> c;               │
  │      ┌────┬────┬────┬────┬────┐    │
  │      │ 5  │ 17 │ 3  │ 737│ 0  │    │
  │      └────┴────┴────┴────┴────┘    │
  │      ↑                             │
  │      c.begin()                     │
  │                         c.end()    │
  │                                    │
  │  public:                           │
  │    push(), pop(), top(), size()...  │
  │    begin() → c.begin()             │
  │    end()   → c.end()               │
  └────────────────────────────────────┘
```

### 4.4 Teste de compatibilidade

O subject diz que a saída deve ser a mesma se você substituir `MutantStack` por
`std::list`:

```cpp
// Com MutantStack:
MutantStack<int> mstack;
mstack.push(5);
mstack.push(17);
std::cout << mstack.top() << std::endl;  // 17
mstack.pop();
std::cout << mstack.size() << std::endl; // 1
mstack.push(3);
mstack.push(5);
mstack.push(737);
mstack.push(0);

MutantStack<int>::iterator it = mstack.begin();
MutantStack<int>::iterator ite = mstack.end();
++it;
--it;
while (it != ite) {
    std::cout << *it << std::endl;  // 5, 3, 5, 737, 0
    ++it;
}

// Com std::list:
std::list<int> lst;
lst.push_back(5);
lst.push_back(17);
std::cout << lst.back() << std::endl;  // 17 (equivalente a top)
lst.pop_back();
std::cout << lst.size() << std::endl;  // 1
lst.push_back(3);
lst.push_back(5);
lst.push_back(737);
lst.push_back(0);

for (std::list<int>::iterator it = lst.begin(); it != lst.end(); ++it)
    std::cout << *it << std::endl;  // mesma saída!
```

### 4.5 Por que `this->c` e não `c`?

Em templates, o nome `c` é um **nome dependente** (está na classe base que depende
do parâmetro template). Sem `this->`, o compilador não procura em classes base
dependentes.

```cpp
// ERRADO (não compila em alguns compiladores):
iterator begin() { return c.begin(); }

// CERTO:
iterator begin() { return this->c.begin(); }
```

---

## 5. Bibliotecas usadas — detalhado

### 5.1 `<algorithm>` — find, sort, min_element, max_element

Finalmente liberado! O módulo 08 é o primeiro onde você pode usar `<algorithm>`.

```cpp
#include <algorithm>

std::find(first, last, value);           // busca linear
std::sort(first, last);                  // ordenação O(n log n)
std::min_element(first, last);           // menor elemento
std::max_element(first, last);           // maior elemento
std::minmax_element(first, last);        // ambos juntos
```

### 5.2 `<vector>` — vector dinâmico

```cpp
#include <vector>

std::vector<int> v;         // vazio
v.push_back(42);            // adiciona no final
v.size();                   // número de elementos
v[0];                       // acesso aleatório O(1)
v.begin(); v.end();         // iterators
```

### 5.3 `<list>` — lista duplamente ligada

```cpp
#include <list>

std::list<int> l;
l.push_back(1);
l.push_front(2);            // list tem push_front (vector não)
l.pop_back();               // remove do final
l.pop_front();              // remove do início
```

### 5.4 `<stack>` — pilha (adapter)

```cpp
#include <stack>

std::stack<int> s;
s.push(42);                 // empilha
s.top();                    // topo (sem remover)
s.pop();                    // remove o topo
s.size();                   // tamanho
s.empty();                  // vazia?
```

### 5.5 `<deque>` — fila dupla

Container padrão usado por `stack` e `queue`. Tem acesso aleatório como vector
e inserção eficiente nas duas pontas como list.

```cpp
#include <deque>

std::deque<int> d;
d.push_back(1);
d.push_front(2);
d[0];                       // acesso aleatório
```

### 5.6 `<cstdlib>` — rand(), srand()

Para testar Span com 10.000+ números aleatórios.

### 5.7 `<exception>` — std::exception

Para lançar exceções quando necessário.

### 5.8 `<ctime>` — time(NULL)

Para seed do `srand()`.

---

## 6. Dicas finais

### 6.1 Type aliases com templates

Para containers que usam `value_type`:

```cpp
// Dentro de uma classe template:
typedef typename Container::value_type value_type;
typedef typename Container::size_type size_type;
```

### 6.2 `typename` é obrigatório em contextos dependentes

```cpp
template <typename T>
void func() {
    T::iterator it;  // ERRO: compilador não sabe se iterator é tipo ou membro
    typename T::iterator it;  // OK: "confia, é um tipo"
}
```

### 6.3 Diferença entre vector::push_back e list::push_back

`std::vector::push_back` pode realocar (se a capacidade acabar):
```
vector antes: [1][2][3]  capacidade=3
push_back(4):
  - aloca novo bloco maior: [1][2][3][4]  capacidade=6
  - copia tudo
  - deleta o bloco antigo
```

`std::list::push_back` nunca realoca (cada elemento é um nó individual):
```
list antes: [1]↔[2]↔[3]
push_back(4):
  - cria novo nó [4]
  - liga no final: [1]↔[2]↔[3]↔[4]
```

### 6.4 Tabela dos exercícios

| Ex | Nome | STL usada | Conceito |
|----|------|-----------|----------|
| 00 | easyfind | `std::find`, qualquer container sequencial | Templates + iterators + `typename` dependente |
| 01 | Span | `std::vector`, `std::sort`, `std::minmax_element` | Algoritmos STL, range de iterators |
| 02 | MutantStack | `std::stack`, iterators do container interno | Container adapters, herança, expor `c` |

### 6.5 Resumo dos módulos até agora

| Módulo | Tema principal |
|--------|----------------|
| cpp00 | Namespaces, classes, streams |
| cpp01 | Alocação, ponteiros, referências |
| cpp02 | Polimorfismo ad-hoc (overloading), Fixed |
| cpp03 | Herança |
| cpp04 | Polimorfismo de subtipo, virtual, abstract |
| cpp05 | Exceções |
| cpp06 | Casts |
| cpp07 | Templates |
| cpp08 | **STL Containers, Iterators, Algorithms** |
