# CPP Module 09 — STL Avançado

Esse módulo é a culminação da STL: você vai usar containers padrão em problemas
reais — Bitcoin Exchange, calculadora RPN, e o algoritmo de ordenação Merge-Insert
(Ford-Johnson). Cada exercício exige um container diferente.

---

## Índice

1. [Regra de ouro: containers únicos](#1-regra-de-ouro-containers-únicos)
2. [Exercício 00 — Bitcoin Exchange](#2-exercício-00--bitcoin-exchange)
3. [Exercício 01 — RPN](#3-exercício-01--rpn)
4. [Exercício 02 — PmergeMe](#4-exercício-02--pmergeme)
5. [Bibliotecas usadas — detalhado](#5-bibliotecas-usadas--detalhado)
6. [Dicas finais](#6-dicas-finais)

---

## 1. Regra de ouro: containers únicos

O subject impõe: **cada container pode ser usado em apenas um exercício**.

```
ex00: std::map     → ex01 ❌  ex02 ❌
ex01: std::stack   → ex02 ❌
ex02: std::vector + std::deque (ou list)  → (último, sem restrição)
```

Planeje antes de começar. Se você usar `std::vector` no ex00, não poderá usá-lo
no ex02 — e o ex02 precisa de 2 containers diferentes.

---

## 2. Exercício 00 — Bitcoin Exchange

### 2.1 O que o exercício quer

```
$> ./btc input.txt
2011-01-03 => 3 = 0.9
2011-01-03 => 2 = 0.6
...
Error: bad input => 2001-42-42
...
```

Um programa que:
1. Lê um banco de dados `data.csv` com taxas de câmbio do Bitcoin
2. Lê um arquivo de entrada com datas e valores
3. Para cada linha válida, calcula `valor × taxa`
4. Se a data não existe no DB, usa a data **inferior mais próxima**

### 2.2 Estrutura do data.csv

```
date,exchange_rate
2009-01-02,0
2009-01-05,0
2009-01-08,0
...
```

1613 linhas com datas de 2009 a 2022.

### 2.3 Por que std::map?

`std::map` mantém as chaves ordenadas. Isso é essencial para encontrar a data
inferior mais próxima com `lower_bound`:

```cpp
std::map<std::string, double> db;

// lower_bound retorna o PRIMEIRO elemento >= chave
std::map<std::string, double>::iterator it = db.lower_bound("2011-01-15");

// Se it == db.begin(), não tem data anterior
// Senão, a data anterior é --it
if (it == db.begin())
    erro;
else
    --it;  // it agora aponta para a data inferior mais próxima
```

**Visualmente:**

```
DB no map (ordenado por data):
  2011-01-03 → 0.3
  2011-01-09 → 0.32  ← lower_bound("2011-01-15") retorna este
  2011-01-10 → 0.33
         ↓
  --it (volta um)
         ↓
  2011-01-09 → 0.32  ← data inferior mais próxima
```

### 2.4 Validação de data

Uma data válida tem formato `Ano-Mês-Dia`:

```cpp
bool validDate(const std::string& date) {
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        return false;

    int y, m, d;
    if (sscanf(date.c_str(), "%d-%d-%d", &y, &m, &d) != 3)
        return false;

    if (m < 1 || m > 12 || d < 1 || d > 31)
        return false;

    // Validação simples de dias por mês (ignorando ano bissexto)
    if (m == 2 && d > 29) return false;
    if ((m == 4 || m == 6 || m == 9 || m == 11) && d > 30) return false;

    return true;
}
```

### 2.5 Validação de valor

O valor deve ser um float ou int positivo entre 0 e 1000:

```cpp
double val = strtod(valueStr.c_str(), &end);
if (*end != '\0' || val < 0)       // "Error: not a positive number."
    erro;
if (val > 1000)                    // "Error: too large a number."
    erro;
```

### 2.6 Fluxo completo

```
input.txt:
  2011-01-03 | 3

  1. Parseia: data = "2011-01-03", valor = 3.0
  2. Valida data ✓
  3. Valida valor (0-1000) ✓
  4. Busca data no map:
     - Acha "2011-01-03"? SIM → taxa = 0.3
     - Se não achasse, usaria a data anterior
  5. Calcula: 3 * 0.3 = 0.9
  6. Output: "2011-01-03 => 3 = 0.9"
```

---

## 3. Exercício 01 — RPN

### 3.1 O que é RPN?

RPN (Reverse Polish Notation / Notação Polonesa Reversa) é uma forma de escrever
expressões matemáticas sem parênteses. O operador vem DEPOIS dos operandos:

```
Notação normal:  3 + 4
RPN:             3 4 +

RPN:             8 9 * 9 - 9 - 9 - 4 - 1 +
Equivale a:      ((((8*9)-9)-9)-9)-4)+1 = 42
```

### 3.2 Como funciona com std::stack

```
Expressão: "8 9 * 9 -"

Token "8":  push 8
    Stack: [8]

Token "9":  push 9
    Stack: [8][9]

Token "*":  pop 9, pop 8, calcula 8*9=72, push 72
    Stack: [72]

Token "9":  push 9
    Stack: [72][9]

Token "-":  pop 9, pop 72, calcula 72-9=63, push 63
    Stack: [63]

Resultado: 63
```

### 3.3 Implementação do algoritmo

```cpp
int RPN::evaluate(const std::string& expr) {
    std::stack<int> s;
    std::istringstream iss(expr);
    std::string token;

    while (iss >> token) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            if (s.size() < 2) throw std::exception();
            int b = s.top(); s.pop();
            int a = s.top(); s.pop();

            if (token == "+") s.push(a + b);
            if (token == "-") s.push(a - b);
            if (token == "*") s.push(a * b);
            if (token == "/") {
                if (b == 0) throw std::exception();
                s.push(a / b);
            }
        } else {
            // Número: deve ser um dígito (0-9)
            int num = std::atoi(token.c_str());
            if (num < 0 || num > 9 || token.length() != 1)
                throw std::exception();
            s.push(num);
        }
    }

    if (s.size() != 1) throw std::exception();
    return s.top();
}
```

**Precaução importante:** O pop é em ordem INVERSA. Quando você faz `8 9 -`,
o stack tem `[8][9]` (8 no fundo, 9 no topo). O primeiro pop tira 9 (b),
o segundo pop tira 8 (a). Então `a - b` = `8 - 9` = `-1`. É assim que RPN
funciona — o primeiro operando está embaixo no stack.

---

## 4. Exercício 02 — PmergeMe

### 4.1 O que é Merge-Insert (Ford-Johnson)?

O algoritmo de Ford-Johnson é um algoritmo de ordenação que minimiza o número
de comparações no pior caso. Foi descrito por Lester Ford Jr. e Selmer Johnson
em 1959, e depois documentado por Knuth em *The Art of Computer Programming*.

**Ideia principal:**
1. **Pair**: Divide em pares e ordena cada par (2 comparações por par)
2. **Sort larger**: Ordena recursivamente os maiores elementos de cada par
3. **Insert smaller**: Insere os menores elementos usando busca binária, na ordem
   determinada pela **sequência de Jacobsthal**

### 4.2 Passo a passo visual

```
Sequência inicial: [11, 8, 2, 1, 15, 4, 7, 6]

Passo 1 — Pair:
  (8, 11)  (1, 2)  (4, 15)  (6, 7)
   cada par ordenado (menor, maior)

Passo 2 — Sort larger (recursivamente):
  Maiores:  [11, 2, 15, 7]
  Ordenados: [2, 7, 11, 15]

  (mantendo os pares originais)
  Pares ordenados pelos maiores:
  (1,2)  (6,7)  (8,11)  (4,15)

Passo 3 — Insert smaller na sequência de Jacobsthal:
  Sequência principal (maiores): [2, 7, 11, 15]
  A ser inserido:  [1, 6, 8, 4]
  Ordem de inserção (Jacobsthal): 3º, 2º, 4º, 1º
  → 8, 6, 4, 1
```

### 4.3 Implementação prática

Em vez de implementar o Ford-Johnson exato (que é muito complexo), você pode
implementar um **Merge Sort** clássico em dois containers diferentes e medir
o tempo de cada um. A diferença de performance entre `std::vector` e
`std::deque` (ou `std::list`) já é suficiente para mostrar resultados.

No entanto, o subject diz: "sim, você precisa usar o algoritmo de Ford-Johnson".
Então implemente o merge-insert sort:

```cpp
// Ford-Johnson (simplificado)
void mergeInsertSort(std::vector<int>& arr) {
    if (arr.size() <= 1) return;

    // Passo 1: criar pares e ordenar cada par
    for (size_t i = 0; i + 1 < arr.size(); i += 2)
        if (arr[i] > arr[i + 1])
            swap(arr[i], arr[i + 1]);

    // Passo 2: ordenar os maiores recursivamente
    std::vector<int> larger;
    for (size_t i = 1; i < arr.size(); i += 2)
        larger.push_back(arr[i]);
    mergeInsertSort(larger);

    // Passo 3: intercalar os menores na sequência dos maiores
    std::vector<int> smaller;
    for (size_t i = 0; i < arr.size(); i += 2)
        smaller.push_back(arr[i]);

    // Inserir cada menor no larger usando binary search
    for (size_t i = 0; i < smaller.size(); i++)
        larger.insert(
            std::lower_bound(larger.begin(), larger.end(), smaller[i]),
            smaller[i]);

    arr = larger;
}
```

### 4.4 Medição de tempo

```cpp
#include <sys/time.h>

struct timeval start, end;
gettimeofday(&start, NULL);

// ... algoritmo ...

gettimeofday(&end, NULL);
double elapsed = (end.tv_sec - start.tv_sec) * 1000000.0
               + (end.tv_usec - start.tv_usec);
```

Ou com `clock()` (CPU time):

```cpp
#include <ctime>
clock_t start = clock();
// ... algoritmo ...
clock_t end = clock();
double elapsed = (double)(end - start) / CLOCKS_PER_SEC * 1000000.0;
```

### 4.5 Por que a diferença de tempo entre containers?

`std::vector` vs `std::deque` (ou `std::list`):

| Operação | vector | deque | list |
|----------|--------|-------|------|
| Acesso aleatório | O(1) ✅ | O(1) ✅ | O(n) ❌ |
| Inserção no meio | O(n) | O(n) | O(1) ✅ |
| Cache locality | Excelente ✅ | Boa | Ruim ❌ |

O merge sort beneficia-se muito da **cache locality** do vector (elementos em
posições contíguas na memória), enquanto list (nós espalhados) sofre mais.

### 4.6 Output esperado

```
$> ./PmergeMe 3 5 9 7 4
Before: 3 5 9 7 4
After: 3 4 5 7 9
Time to process a range of 5 elements with std::vector : 0.00031 us
Time to process a range of 5 elements with std::deque : 0.00014 us
```

---

## 5. Bibliotecas usadas — detalhado

### 5.1 `<map>` — std::map (ex00)

```cpp
#include <map>

std::map<std::string, double> db;
db["2011-01-03"] = 0.3;

db.find("2011-01-15");       // iterator ou db.end()
db.lower_bound("2011-01-15"); // primeiro elemento >= chave
db.upper_bound("2011-01-15"); // primeiro elemento > chave
```

### 5.2 `<stack>` — std::stack (ex01)

```cpp
#include <stack>

std::stack<int> s;
s.push(42);
s.top();    // 42
s.pop();    // remove topo
s.size();
s.empty();
```

### 5.3 `<vector>` e `<deque>` (ex02)

Usados para testar a ordenação com dois containers diferentes.
`<algorithm>` para `std::lower_bound` (busca binária).

### 5.4 `<fstream>` — leitura de arquivos (ex00)

```cpp
#include <fstream>

std::ifstream file("data.csv");
std::string line;
while (std::getline(file, line)) {
    // processa linha
}
```

### 5.5 `<sstream>` — string stream (ex00, ex01)

```cpp
#include <sstream>

std::istringstream iss("2011-01-03 | 3");
std::string date, sep;
double value;
iss >> date >> sep >> value;
```

### 5.6 `<sys/time.h>` — gettimeofday (ex02)

Para medição precisa de tempo em microssegundos.

### 5.7 `<cstdlib>` — strtod, atoi (ex00, ex01)

Conversão de string para número.

---

## 6. Dicas finais

### 6.1 Parsing do CSV

O `data.csv` tem cabeçalho `date,exchange_rate`. Pule a primeira linha:

```cpp
std::string line;
std::getline(file, line);  // descarta cabeçalho
while (std::getline(file, line)) {
    size_t comma = line.find(',');
    std::string date = line.substr(0, comma);
    double rate = strtod(line.substr(comma + 1).c_str(), NULL);
    db[date] = rate;
}
```

### 6.2 Parsing do input

O formato é `data | valor`. Separe por `|` com espaços opcionais:

```cpp
std::istringstream iss(line);
std::string date, sep;
double value;
if (!(iss >> date >> sep >> value) || sep != "|") {
    std::cout << "Error: bad input => " << line << std::endl;
    continue;
}
```

### 6.3 Busca da data inferior

```cpp
std::map<std::string, double>::iterator it = db.lower_bound(date);
if (it != db.begin())
    --it;  // data inferior mais próxima
else
    erro;  // não tem data anterior
```

### 6.4 Tabela dos exercícios

| Ex | Programa | Container | STL usada |
|----|----------|-----------|-----------|
| 00 | btc | `std::map` | `<map>`, `<fstream>`, `<sstream>`, `<cstdlib>` |
| 01 | RPN | `std::stack` | `<stack>`, `<sstream>`, `<cstdlib>` |
| 02 | PmergeMe | `std::vector` + `std::deque` | `<algorithm>`, `<sys/time.h>`, `<ctime>` |

### 6.5 Resumo dos módulos

| Módulo | Tema |
|--------|------|
| cpp00 | Namespaces, classes, streams |
| cpp01 | Alocação, ponteiros, referências |
| cpp02 | Polimorfismo ad-hoc, Fixed |
| cpp03 | Herança |
| cpp04 | Polimorfismo, virtual, abstract |
| cpp05 | Exceções |
| cpp06 | Casts |
| cpp07 | Templates |
| cpp08 | STL Containers, Iterators, Algorithms |
| cpp09 | **STL Avançado (map, stack, Ford-Johnson)** |
