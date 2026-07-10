# CPP Module 07 — Templates em C++

Esse módulo inteiro é sobre **templates** — a ferramenta do C++ para escrever código genérico. Você vai aprender a criar funções e classes que funcionam com **qualquer tipo**.

---

## Índice

1. [Por que templates existem?](#1-por-que-templates-existem)
2. [Exercício 00 — Function Templates (swap, min, max)](#2-exercício-00--function-templates-swap-min-max)
3. [Exercício 01 — Iter](#3-exercício-01--iter)
4. [Exercício 02 — Class Template Array](#4-exercício-02--class-template-array)
5. [Bibliotecas usadas — detalhado](#5-bibliotecas-usadas--detalhado)
6. [Dicas finais](#6-dicas-finais)

---

## 1. Por que templates existem?

### O problema: código repetido pra cada tipo

Se você quer uma função que troque dois valores, em C você precisaria de uma versão para cada tipo:

```c
void swap_int(int* a, int* b) { int t = *a; *a = *b; *b = t; }
void swap_float(float* a, float* b) { float t = *a; *a = *b; *b = t; }
void swap_double(double* a, double* b) { double t = *a; *a = *b; *b = t; }
// E pra char? E pra string? E pra struct?
```

O código é **sempre o mesmo**, só muda o tipo. Isso é:
- **Tedioso** — você copia e coloca 20 vezes
- **Propenso a erro** — um dia você esquece de trocar um tipo
- **Difícil de manter** — se precisar mudar a lógica, muda em 20 lugares

No C++98, você não pode usar auto, macros são perigosas, e `void*` perde a informação de tipo.

### A solução: templates

Template = **"molde"** que o compilador usa para gerar código pra cada tipo:

```cpp
template <typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}
```

Quando você chama `swap(a, b)` com `int`, o compilador **instancia** (cria) uma versão da função para `int`. Quando você chama com `std::string`, ele cria outra para `std::string`.

O template **não é código executável** — é um molde que vira código quando você usa.

### Como o compilador pensa

```
swap(a, b) com a e b sendo int:

1. "Preciso de uma função swap que receba int& e int&"
2. "Tem um template swap que serve"
3. "Gera: void swap(int& a, int& b) { int temp = a; a = b; b = temp; }"
4. "Compila essa versão"
```

### Tipos de template

| Tipo | Palavra-chave | Exemplo |
|------|--------------|---------|
| Function template | `template <typename T>` | `T max(T a, T b)` |
| Class template | `template <typename T>` | `class Array<T>` |

### `typename` vs `class`

Nas versões antigas do C++, só existia `class`:

```cpp
template <class T>  // C++98 original
```

Depois adicionaram `typename` que significa a mesma coisa:

```cpp
template <typename T>  // equivalente, mais claro
```

**Diferença**: `typename` deixa explícito que T é um tipo. `class` funciona igual. O subject não especifica, mas a convenção moderna é `typename`.

### O que NÃO muda com templates

Templates **não** permitem que você faça operações que o tipo não suporta:

```cpp
template <typename T>
T divide(T a, T b) { return a / b; }

// int divide(int, int) → OK (int tem divisão)
// std::string divide(std::string, std::string) → ERRO de compilação!
```

O compilador só gera código se o tipo suportar todas as operações usadas dentro do template.

---

## 2. Exercício 00 — Function Templates (swap, min, max)

### 2.1 O que o exercício quer

Criar 3 templates de função no header:

```cpp
template <typename T>
void swap(T& a, T& b);    // Troca os valores

template <typename T>
T min(T a, T b);          // Retorna o menor (segundo se iguais)

template <typename T>
T max(T a, T b);          // Retorna o maior (segundo se iguais)
```

E testar com `int` e `std::string`.

### 2.2 swap — Passo a passo

```cpp
template <typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}
```

**Por que `T&` e não `T`?** Porque precisamos modificar os originais. Se fosse `T` (cópia), as alterações seriam perdidas.

Visualização na memória:

```
Antes do swap:
  a ──→ 2
  b ──→ 3

swap(a, b):
  temp = a  → temp = 2
  a = b     → a = 3
  b = temp  → b = 2

Depois do swap:
  a ──→ 3
  b ──→ 2
```

### 2.3 min e max — Passo a passo

```cpp
template <typename T>
T min(T a, T b) {
    return (b < a) ? b : a;
}

template <typename T>
T max(T a, T b) {
    return (a < b) ? b : a;
}
```

**Detalhe importante**: Se forem iguais, retorna o **segundo** (`b`). Por quê?

```
min(3, 3):
  b < a? 3 < 3? FALSO → retorna a = 3
  // Errado! Deveria retornar o segundo (3 também, mas conceitualmente b)
```

Na verdade, a expressão `(b < a) ? b : a`:
- Se `b < a` → `b` é menor → retorna `b`
- Se `b >= a` → `b` não é menor → retorna `a`

Quando são iguais, `b < a` é falso → retorna `a`. Mas o subject diz "se forem iguais, retorna o segundo". Repare que se `a == b`, ambos são o mesmo valor, então retornar `a` é funcionalmente igual a retornar `b`. O importante é a consistência.

Versão correta (retorna b se igual):

```cpp
template <typename T>
T min(T a, T b) {
    return (a <= b) ? a : b;
    // a <= b → a é menor ou igual → retorna a
    // senão → b é menor → retorna b
}
```

Espera, se `a == b`, `a <= b` é true → retorna `a`. Mas o subject quer o segundo quando igual.

Vamos ver o código do subject:

```cpp
::swap( a, b );            // a=3, b=2
std::cout << "min( a, b ) = " << ::min( a, b ) << std::endl; // min(3,2) = 2
std::cout << "max( a, b ) = " << ::max( a, b ) << std::endl; // max(3,2) = 3
```

Aqui `a=3, b=2` → `min(3,2) = 2` (correto, retorna b que é menor).
`max(3,2) = 3` (correto, retorna a que é maior).

Teste com string:
```cpp
std::string c = "chaine1";
std::string d = "chaine2";
::swap(c, d);                   // c = "chaine2", d = "chaine1"
std::cout << "min( c, d ) = " << ::min( c, d ) << std::endl; // min("chaine2","chaine1") = "chaine1"
std::cout << "max( c, d ) = " << ::max( c, d ) << std::endl; // max("chaine2","chaine1") = "chaine2"
```

Aqui `c="chaine2", d="chaine1"` (depois do swap). `min` retorna `"chaine1"`, `max` retorna `"chaine2"`.

Comparação de strings em C++: `std::string` compara **lexicograficamente** (ordem alfabética). `"chaine1" < "chaine2"` porque `'1' < '2'`.

### 2.4 Por que `::swap` e não `swap`?

```cpp
::swap(a, b);  // Chama o swap do namespace global (o nosso)
```

O `::` na frente significa **namespace global**. Sem ele, o compilador poderia encontrar `std::swap` (da STL) e causar ambiguidade.

```
Sem :: → o compilador procura em:
  1. Namespace atual
  2. Namespace global
  3. std (por causa de ADL / Argument-Dependent Lookup)

Com :: → força a procurar SÓ no namespace global
```

### 2.5 Por que os templates ficam no .hpp?

Funções normais ficam em `.cpp`:

```cpp
// funcao.hpp
void hello();

// funcao.cpp
void hello() { std::cout << "Hello\n"; }

// main.cpp
#include "funcao.hpp"
hello();  // OK: compilador acha o prototype, depois o linker conecta
```

Com templates, **não funciona assim**:

```cpp
// template.hpp
template <typename T>
void swap(T& a, T& b);  // só o prototype

// template.cpp
template <typename T>
void swap(T& a, T& b) {  // implementação
    T temp = a;
    a = b;
    b = temp;
}

// main.cpp
#include "template.hpp"
int x = 1, y = 2;
swap(x, y);  // ERRO do linker!
```

**Por que?** Porque o compilador de `main.cpp` viu só o prototype. Ele precisa gerar a versão para `int`, mas a implementação está em `template.cpp`. Em `template.cpp`, ninguém chamou `swap<int>`, então o compilador **não gerou** nenhuma versão.

**Solução**: Colocar **definição e implementação** no header:

```cpp
// swap.hpp
#ifndef SWAP_HPP
#define SWAP_HPP

template <typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

#endif
```

**O que acontece agora?**
1. `main.cpp` inclui `swap.hpp`
2. O compilador vê a implementação completa
3. Quando encontra `swap(x, y)` (com `int`), ele gera `swap<int>` na hora
4. Linker feliz

---

## 3. Exercício 01 — Iter

### 3.1 O que o exercício quer

```cpp
template <typename T>
void iter(T* array, size_t length, void (*func)(T&));
```

Um template de função que:
1. Recebe um **array** (não um ponteiro genérico — um array de verdade)
2. Recebe o **comprimento** do array
3. Recebe uma **função** para aplicar em cada elemento

### 3.2 O problema: arrays decaem para ponteiros

Em C/C++, quando você passa um array para uma função, ele **decai** para ponteiro:

```cpp
void func(int arr[]) {
    // arr aqui é int*, não int[5]
    // sizeof(arr) == 8 (tamanho de ponteiro), não 20 (5 * 4)
}

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    func(arr);  // arr decai para int*
    
    // O compilador esqueceu que é um array de 5 elementos!
}
```

**É por isso que você precisa passar o comprimento separadamente.** Não tem como recuperar `sizeof(arr)/sizeof(arr[0])` dentro da função template.

### 3.3 Implementação básica

```cpp
template <typename T>
void iter(T* array, size_t length, void (*func)(T&)) {
    for (size_t i = 0; i < length; i++) {
        func(array[i]);
    }
}
```

### 3.4 Const-correctness — o grande desafio

O subject avisa: **"Pense cuidadosamente sobre como suportar elementos const e non-const."**

Se você tem um array `const int arr[]` e passa para `iter`, a função recebida deve aceitar `const int&`, não `int&`:

```cpp
void print_const(const int& x) {
    std::cout << x << std::endl;
}

void increment(int& x) {
    x++;
}

int main() {
    int arr[] = {1, 2, 3};
    const int carr[] = {1, 2, 3};
    
    iter(arr, 3, increment);     // OK: int& → int&
    iter(arr, 3, print_const);   // OK: int& → const int& (conversão implícita)
    iter(carr, 3, print_const);  // OK: const int& → const int&
    iter(carr, 3, increment);    // ERRO: não pode passar const int& para int&
}
```

Como você suporta os dois casos?

Opção 1: **Dois templates de função** (um para const, um para não-const)

```cpp
template <typename T>
void iter(const T* array, size_t length, void (*func)(const T&));

template <typename T>
void iter(T* array, size_t length, void (*func)(T&));
```

Opção 2: **Template com tipo deduzido para a função** (mais flexível)

```cpp
template <typename T, typename Func>
void iter(T* array, size_t length, Func func) {
    for (size_t i = 0; i < length; i++) {
        func(array[i]);
    }
}
```

A opção 2 é mais flexível porque aceita **qualquer coisa que possa ser chamada** (função, functor, lambda em C++11). O subject mostra que o terceiro parâmetro "pode ser um template de função instanciado".

### 3.5 Como Func é deduzido

```cpp
void print_int(const int& x) { cout << x << endl; }

int arr[] = {1, 2, 3};
iter(arr, 3, print_int);
```

O compilador deduz:
- `T` = `int` (por causa de `arr` ser `int*`)
- `Func` = `void (*)(const int&)` (por causa de `print_int`)

Então instancia:

```cpp
void iter<int, void (*)(const int&)>(int* array, size_t length, void (*func)(const int&)) {
    for (size_t i = 0; i < length; i++)
        func(array[i]);  // int → const int& OK
}
```

### 3.6 Exemplo com função que modifica

```cpp
void triple(int& x) {
    x *= 3;
}

int nums[] = {1, 2, 3, 4, 5};
iter(nums, 5, triple);
// nums agora é {3, 6, 9, 12, 15}
```

Visualmente:

```
Antes:  [1][2][3][4][5]
         ↓  ↓  ↓  ↓  ↓
         triple triple triple triple triple
         ↓  ↓  ↓  ↓  ↓
Depois: [3][6][9][12][15]
```

### 3.7 Exemplo com string

```cpp
void print_string(const std::string& s) {
    std::cout << s << " ";
}

std::string words[] = {"Hello", "World", "Templates"};
iter(words, 3, print_string);
// Saída: "Hello World Templates "
```

---

## 4. Exercício 02 — Class Template Array

### 4.1 O que o exercício quer

Criar um template de classe que se comporta como um array, mas com:
- Tamanho dinâmico (definido na construção)
- Acesso seguro (lança exceção se índice inválido)
- Cópia profunda (duplicata independente)

```cpp
template <typename T>
class Array {
private:
    T* _data;
    unsigned int _size;
public:
    Array();                     // Array vazio
    Array(unsigned int n);       // Array de n elementos
    Array(const Array& other);   // Cópia profunda
    ~Array();                    // Libera memória
    Array& operator=(const Array& other);  // Atribuição profunda
    T& operator[](unsigned int i);         // Acesso com check
    const T& operator[](unsigned int i) const;  // Acesso const
    unsigned int size() const;   // Tamanho
};
```

### 4.2 Construção sem parâmetro — Array vazio

```cpp
template <typename T>
Array<T>::Array() : _data(NULL), _size(0) {}
```

Um array vazio tem `_data = NULL` e `_size = 0`.

### 4.3 Construção com n — alocação dinâmica

```cpp
template <typename T>
Array<T>::Array(unsigned int n) : _data(new T[n]()), _size(n) {}
```

**Por que `new T[n]()` com parênteses no final?**

```cpp
new int[5];    // aloca 5 ints, valores NÃO inicializados (lixo)
new int[5]();  // aloca 5 ints, TUDO ZERADO (value-initialized)
```

Com `()`:
```
int* a = new int[5]();  → {0, 0, 0, 0, 0}
std::string* b = new std::string[5](); → {"", "", "", "", ""}
```

**Por que isso importa?** O subject diz "inicializados por padrão". Cada tipo tem sua inicialização padrão:
- `int` → 0
- `double` → 0.0
- `char` → '\0'
- `std::string` → "" (vazia)
- Qualquer classe com construtor padrão → construtor chamado

### 4.4 Construtor de cópia — cópia profunda

O subject diz: "modificar o array original ou sua cópia após a cópia não deve afetar o outro array."

Isso exige **cópia profunda** (deep copy):

```cpp
template <typename T>
Array<T>::Array(const Array& other) : _data(new T[other._size]()), _size(other._size) {
    for (unsigned int i = 0; i < _size; i++) {
        _data[i] = other._data[i];
    }
}
```

**Visualmente:**

```
ANTES da cópia (cópia rasa — ERRADO):
    arr1            arr2
    _data ──────→ [1][2][3]
                   ↑
    _data ────────┘
    (mesmo ponteiro! modificar um afeta o outro)

DEPOIS da cópia (cópia profunda — CERTO):
    arr1            arr2
    _data ──→ [1][2][3]    _data ──→ [1][2][3]
    (cada um tem seu próprio array)
```

### 4.5 Operador de atribuição

```cpp
template <typename T>
Array<T>& Array<T>::operator=(const Array& other) {
    if (this != &other) {         // auto-atribuição: arr = arr
        delete[] _data;           // libera memória antiga
        _size = other._size;
        _data = new T[_size]();   // aloca nova memória
        for (unsigned int i = 0; i < _size; i++) {
            _data[i] = other._data[i];  // copia elementos
        }
    }
    return *this;
}
```

**Proteção contra auto-atribuição:**

```cpp
Array<int> arr(5);
arr = arr;  // sem o if, daria delete[] em _data e depois tentaria copiar de si mesmo
```

### 4.6 Destrutor

```cpp
template <typename T>
Array<T>::~Array() {
    delete[] _data;
}
```

Sempre `delete[]` (com colchetes) para arrays alocados com `new[]`.

### 4.7 operator[] — com verificação de limites

```cpp
template <typename T>
T& Array<T>::operator[](unsigned int i) {
    if (i >= _size) {
        throw std::exception();  // ou std::out_of_range
    }
    return _data[i];
}

template <typename T>
const T& Array<T>::operator[](unsigned int i) const {
    if (i >= _size) {
        throw std::exception();
    }
    return _data[i];
}
```

**Por que duas versões?** Uma para `Array` não-const (permite modificar) e uma para `Array` const (só leitura):

```cpp
Array<int> arr(3);
arr[0] = 42;            // chama T& operator[]
                          // retorna referência não-const → pode modificar

const Array<int> carr(3);
int x = carr[0];        // chama const T& operator[] const
                          // retorna const → não pode modificar
carr[0] = 42;           // ERRO de compilação!
```

**O que lançar?** O subject diz "uma `std::exception` é lançada". `std::exception` é a classe base de todas as exceções padrão. Você pode lançar `std::exception()` diretamente.

### 4.8 size()

```cpp
template <typename T>
unsigned int Array<T>::size() const {
    return _size;
}
```

- `const` no final: não modifica o objeto
- Retorna `unsigned int` (não recebe parâmetros)

### 4.9 Testando o Array

```cpp
int main() {
    // Array vazio
    Array<int> empty;
    std::cout << empty.size() << std::endl;  // 0
    
    // Array com elementos
    Array<int> arr(5);
    for (unsigned int i = 0; i < arr.size(); i++)
        arr[i] = i * 2;
    
    // Cópia
    Array<int> copy(arr);
    copy[0] = 99;           // arr[0] continua 0 (cópia profunda)
    
    // Atribuição
    Array<int> assigned(3);
    assigned = arr;         // assigned agora tem 5 elementos
    
    // Teste de exceção
    try {
        arr[10] = 42;       // índice inválido → exceção
    } catch (const std::exception& e) {
        std::cout << "Out of bounds!" << std::endl;
    }
    
    // Array de strings
    Array<std::string> strings(3);
    strings[0] = "Hello";
    strings[1] = "World";
    strings[2] = "Templates";
    
    // Array const
    const Array<std::string> const_strings(strings);
    std::cout << const_strings[0] << std::endl;  // leitura OK
    
    return 0;
}
```

---

## 5. Bibliotecas usadas — detalhado

### 5.1 `<iostream>` — `std::cout`

Já usado nos módulos anteriores. Para output padrão.

### 5.2 `<string>` — `std::string`

Usado nos testes com strings. `std::string` suporta `operator<`, `operator>`, `operator==`, então funciona nos templates `min`/`max`.

### 5.3 `<cstdlib>` — `rand()` e `srand()`

Se você quiser testar com valores aleatórios (ex: preencher Array com números aleatórios no main).

### 5.4 `<exception>` — `std::exception`

Classe base para exceções. Usada no `operator[]` para lançar quando índice está fora dos limites.

```cpp
#include <exception>

throw std::exception();
```

### 5.5 `<new>` — alocação

Não precisa incluir explicitamente — `new[]` e `delete[]` são palavras-chave da linguagem.

---

## 6. Dicas finais

### 6.1 Prototype vs implementação no header

Com templates, **tudo vai no header**:

```cpp
// Array.hpp
#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <exception>

template <typename T>
class Array {
private:
    T* _data;
    unsigned int _size;
public:
    Array();
    Array(unsigned int n);
    Array(const Array& other);
    ~Array();
    Array& operator=(const Array& other);
    T& operator[](unsigned int i);
    const T& operator[](unsigned int i) const;
    unsigned int size() const;
};

// Implementações AQUI no header
template <typename T>
Array<T>::Array() : _data(NULL), _size(0) {}

template <typename T>
Array<T>::Array(unsigned int n) : _data(new T[n]()), _size(n) {}

// ... etc

#endif
```

### 6.2 Arquivo .tpp (opcional)

Se você quiser separar implementação do header por organização:

```cpp
// Array.hpp — declarações
#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <exception>

template <typename T>
class Array {
    // ...
};

#include "Array.tpp"  // inclui as implementações no final

#endif
```

```cpp
// Array.tpp — implementações
template <typename T>
Array<T>::Array() : _data(NULL), _size(0) {}
// ...
```

O compilador não se importa com a extensão do arquivo. `.tpp` é só convenção.

### 6.3 Operador de comparação para tipos customizados

Se você quiser testar `min`/`max` com uma classe própria, ela precisa de `operator<`:

```cpp
struct Ponto {
    int x, y;
    bool operator<(const Ponto& other) const {
        return (x < other.x) || (x == other.x && y < other.y);
    }
};
```

### 6.4 Por que não usar `std::vector`?

O subject diz: "Você só pode usar a STL nos Módulos 08 e 09." Isso significa que `std::vector`, `std::list`, `std::map`, `<algorithm>` etc são **proibidos**.

O objetivo é que você implemente seu próprio `Array<T>` para entender como um container genérico funciona por baixo dos panos.

### 6.5 Deep copy vs Shallow copy — resumo visual

```
SHALLOW COPY (ERRADO - cópia do ponteiro):
  
  Original:      _data ──→ [1][2][3]
  Cópia:         _data ──→ [1][2][3] (mesmo endereço!)
  
  Se original[0] = 99, cópia[0] também vira 99!
  Se destrutor de um rodar, o outro fica com dangling pointer!

DEEP COPY (CERTO - cópia dos dados):
  
  Original:      _data ──→ [1][2][3]
  Cópia:         _data ──→ [1][2][3] (endereço diferente)
  
  Cada um tem seu próprio array independente!
```

### 6.6 Forma Canônica Ortodoxa

A classe `Array` deve ter:
- Construtor padrão ✓
- Construtor de cópia ✓
- Operador de atribuição ✓
- Destrutor ✓

### 6.7 Tabela comparativa dos exercícios

| Ex | Nome | Conceito principal | O que você aprendeu |
|----|------|-------------------|---------------------|
| 00 | swap/min/max | Function template | Sintaxe `template<typename T>`, dedução de tipo, instanciação implícita, `::` para namespace global |
| 01 | iter | Function template com array | Decaimento de array para ponteiro, const-correctness, template com parâmetro de função |
| 02 | Array | Class template | `new[]`/`delete[]`, deep copy, operator[] com exceção, inicialização padrão, forma canônica |
