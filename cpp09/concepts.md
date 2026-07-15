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

// Se it == db.begin(), o primeiro registro do DB é a data mais próxima
// Senão, a data anterior é --it
if (it != db.begin())
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

Para datas anteriores ao primeiro registro do DB (ex: 2008-01-01),
`lower_bound` retorna `begin()` — nesse caso, usamos a taxa do
primeiro registro mesmo que ela não seja estritamente "inferior".
Isso evita erros artificiais para datas fora do range histórico
do DB.

### 2.4 Validação de data

Uma data válida tem formato `Ano-Mês-Dia`:

```cpp
bool isValidDate(const std::string& date) {
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        return false;

    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (!std::isdigit(date[i]))
            return false;
    }

    int m, d;
    std::istringstream(date.substr(5, 2)) >> m;
    std::istringstream(date.substr(8, 2)) >> d;

    if (m < 1 || m > 12 || d < 1 || d > 31)
        return false;

    if (m == 2 && d > 29) return false;
    if ((m == 4 || m == 6 || m == 9 || m == 11) && d > 30) return false;

    return true;
}
```

### 2.5 Validação de valor

O valor deve ser um float ou int positivo entre 0 e 1000:

```cpp
float value;
std::istringstream(valueStr) >> value;
if (value < 0)       // "Error: not a positive number."
    erro;
if (value > 1000)    // "Error: too large a number."
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
            if (s.size() < 2) throw std::runtime_error("insuficient operands");
            int b = s.top(); s.pop();
            int a = s.top(); s.pop();

            if (token == "+") s.push(a + b);
            if (token == "-") s.push(a - b);
            if (token == "*") s.push(a * b);
            if (token == "/") {
                if (b == 0) throw std::runtime_error("division by zero");
                s.push(a / b);
            }
        } else {
            // Número: deve ser um dígito (0-9)
            int num;
            std::istringstream tokstream(token);
            if (!(tokstream >> num) || num < 0 || num > 9 || token.length() != 1)
                throw std::runtime_error("invalid token");
            s.push(num);
        }
    }

    if (s.size() != 1) throw std::runtime_error("invalid expression");
    return s.top();
}
```

**Sobre a sentinela de erro:** Cuidado para não usar `-1` como valor de retorno
para erros — `-1` é um resultado válido em RPN (ex: `2 3 -` = `-1`). A
abordagem correta é lançar exceções (`std::runtime_error`) para todos os erros
e capturá-las no `main()`, imprimindo `"Error"` no stderr.

**Precaução importante:** O pop é em ordem INVERSA. Quando você faz `8 9 -`,
o stack tem `[8][9]` (8 no fundo, 9 no topo). O primeiro pop tira 9 (b),
o segundo pop tira 8 (a). Então `a - b` = `8 - 9` = `-1`. É assim que RPN
funciona — o primeiro operando está embaixo no stack.

---

## 4. Exercício 02 — PmergeMe

### 4.1 O que é Merge-Insert (Ford-Johnson)?

O algoritmo de Ford-Johnson é um algoritmo de ordenação que minimiza o número
de comparações no pior caso. Foi descrito por Lester Ford Jr. e Selmer Johnson
em 1959, e depois documentado por Knuth em *The Art of Computer Programming*,
Vol. 3, página 184.

**Ideia principal:**
1. **Pair**: Divide em ⌊n/2⌋ pares e ordena cada par (garantir que o maior venha
   primeiro dentro de cada par)
2. **Sort larger**: Ordena recursivamente os elementos maiores de cada par
   (main chain) usando o próprio Ford-Johnson
3. **Insert smaller**: Insere os elementos menores (pend chain) na main chain
   usando busca binária, na ordem determinada pela **sequência de Jacobsthal**

O truque está na **ordem de inserção**: em vez de inserir os elementos menores
sequencialmente (que poderia exigir muitas comparações), a sequência de Jacobsthal
determina uma ordem que minimiza o número máximo de comparações no pior caso.

### 4.2 Passo a passo visual

```
Sequência inicial: [11, 8, 2, 1, 15, 4, 7, 6]
                          8 elementos

Passo 1 — Pair:
  Elementos:    11  8  |  2  1  |  15  4  |  7  6
                a1 b1    a2 b2    a3 b3    a4 b4

  Ordenar cada par (a = menor, b = maior):
  (8, 11)  (1, 2)  (4, 15)  (6, 7)
   a1  b1    a2 b2    a3 b3   a4  b4

Passo 2 — Extrair main chain (todos os b's) e pend chain (todos os a's):
  main chain (b's): [11, 2, 15, 7]
  pend chain (a's): [8, 1, 4, 6]

  Ordenar main chain recursivamente (pelo b):
  main chain: [2, 7, 11, 15]   ← ordenada por Ford-Johnson

  Reorganizar pend chain na mesma ordem:
  pend chain: [1, 6, 8, 4]     ← cada a acompanha seu b

  Visualmente (pares ordenados pelos b's):
  (1, 2)  (6, 7)  (8, 11)  (4, 15)
   a1 b1   a4 b4   a2 b2    a3 b3

Passo 3 — Gerar sequência de Jacobsthal:
  Jacobsthal: J(k) = J(k-1) + 2*J(k-2)
  J(0)=1, J(1)=1, J(2)=3, J(3)=5, J(4)=11, J(5)=21...

  Para 4 pend items, Jacobsthal: [1, 1, 3, 5]
  Intervalos de inserção: [J(1), J(2)-1], [J(2), J(3)-1], ...
  → 1..2, 3..4, ...

Passo 4 — Inserir pend na main usando lower_bound:
  main chain: [2, 7, 11, 15]

  1. Inserir pend[0]=1 no início:  [1, 2, 7, 11, 15]

  2. Inserir pend[2]=8 (Jacobsthal):
     lower_bound(8) → 11 → insere antes:  [1, 2, 7, 8, 11, 15]

  3. Inserir pend[1]=6:
     lower_bound(6) → 7 → insere antes:  [1, 2, 6, 7, 8, 11, 15]

  4. Inserir pend[3]=4:
     lower_bound(4) → 6 → insere antes:  [1, 2, 4, 6, 7, 8, 11, 15]

Resultado final ordenado: [1, 2, 4, 6, 7, 8, 11, 15]
```

### 4.3 A sequência de Jacobsthal

A sequência de Jacobsthal determina a **ordem ideal de inserção** dos elementos
pendentes na main chain. A definição:

```
J(0) = 1
J(1) = 1
J(k) = J(k-1) + 2 * J(k-2), para k >= 2
```

Os primeiros valores: 1, 1, 3, 5, 11, 21, 43, 85, 171, 341, ...

No Ford-Johnson, os intervalos de inserção são:

```
[J(k-1), J(k)-1] para k = 2, 3, 4, ...

k=2: [1, 2]  → insere índices 2, 1 (do pend)
k=3: [3, 4]  → insere índices 4, 3
k=4: [5, 10] → insere índices 10, 9, 8, 7, 6, 5
...
```

Cada intervalo é percorrido **de trás para frente** (decrescente), porque os
elementos com índices maiores na main chain já estão em posições avançadas,
e inseri-los primeiro reduz o custo de realocação.

Implementação em C++98:

```cpp
std::vector<int> jacob;
jacob.push_back(1);  // J(0)
jacob.push_back(1);  // J(1)

// Gera Jacobsthal até cobrir todos os pend items
while (jacob.back() < pairCount) {
    int sz = jacob.size();
    jacob.push_back(jacob[sz - 1] + 2 * jacob[sz - 2]);
}

// Para cada intervalo [J(k-1), J(k)-1]
for (size_t k = 2; k < jacob.size(); k++) {
    int end = jacob[k - 1];
    int start = jacob[k] - 1;
    if (start >= pairCount) start = pairCount - 1;
    if (end < 1) end = 1;
    if (start < end) continue;

    // Insere de trás para frente no intervalo
    for (int i = start; i >= end; i--) {
        if (inserted[i]) continue;
        // binary search + insert
        std::lower_bound(main.begin(), main.end(), pend[i]);
        main.insert(pos, pend[i]);
        inserted[i] = true;
    }
}

// Fallback: insere qualquer pend não inserido
for (int i = 1; i < pairCount; i++) {
    if (!inserted[i]) {
        // binary search + insert
    }
}
```

### 4.4 O algoritmo completo (Ford-Johnson para vector)

```cpp
void fordJohnsonSortVec(std::vector<int>& arr) {
    int n = arr.size();
    if (n <= 1) return;

    // --- Passo 1: Pair ---
    bool hasStraggler = (n % 2 == 1);
    int straggler = hasStraggler ? arr[n - 1] : 0;
    int pairCount = n / 2;

    std::vector<std::pair<int,int> > pairs(pairCount);
    for (int i = 0; i < pairCount; i++) {
        int a = arr[2 * i];
        int b = arr[2 * i + 1];
        if (a > b) std::swap(a, b);
        pairs[i] = std::make_pair(a, b);  // (menor, maior)
    }

    // --- Passo 2: Sort pairs by b (insertion sort simples) ---
    for (int i = 1; i < pairCount; i++) {
        std::pair<int,int> key = pairs[i];
        int j = i - 1;
        while (j >= 0 && pairs[j].second > key.second) {
            pairs[j + 1] = pairs[j];
            j--;
        }
        pairs[j + 1] = key;
    }

    // --- Extrair main chain (b's) e pend chain (a's) ---
    std::vector<int> main, pend;
    for (int i = 0; i < pairCount; i++) {
        main.push_back(pairs[i].second);
        pend.push_back(pairs[i].first);
    }

    // --- Passo 3: Sort main chain recursivamente ---
    fordJohnsonSortVec(main);

    // --- Passo 4: Insert pend chain na main chain ---
    // Primeiro pend[0] sempre vai para o início
    main.insert(main.begin(), pend[0]);

    // Gerar sequência de Jacobsthal
    std::vector<int> jacob;
    jacob.push_back(1);
    jacob.push_back(1);
    while (jacob.back() < pairCount)
        jacob.push_back(jacob[jacob.size()-1] + 2*jacob[jacob.size()-2]);

    std::vector<bool> inserted(pairCount, false);
    inserted[0] = true;

    // Inserir nos intervalos de Jacobsthal
    for (size_t k = 2; k < jacob.size(); k++) {
        int end = jacob[k - 1];
        int start = jacob[k] - 1;
        if (start >= pairCount) start = pairCount - 1;
        if (end < 1) end = 1;
        if (start < end) continue;

        for (int i = start; i >= end; i--) {
            if (inserted[i]) continue;
            std::vector<int>::iterator pos =
                std::lower_bound(main.begin(), main.end(), pend[i]);
            main.insert(pos, pend[i]);
            inserted[i] = true;
        }
    }

    // Fallback para pend's não inseridos
    for (int i = 1; i < pairCount; i++) {
        if (!inserted[i]) {
            std::vector<int>::iterator pos =
                std::lower_bound(main.begin(), main.end(), pend[i]);
            main.insert(pos, pend[i]);
        }
    }

    // Straggler (se n for ímpar)
    if (hasStraggler) {
        std::vector<int>::iterator pos =
            std::lower_bound(main.begin(), main.end(), straggler);
        main.insert(pos, straggler);
    }

    arr = main;
}
```

### 4.5 Versão para deque

A implementação para `std::deque` segue a mesma lógica, mas com diferenças
importantes nos tipos:

```cpp
void fordJohnsonSortDeq(std::deque<int>& arr) {
    int n = arr.size();
    if (n <= 1) return;

    // Pairing: mesmo algoritmo, armazena em vector<pair>
    std::vector<std::pair<int,int> > pairs(pairCount);
    // ... (idêntico à versão vector)

    // Main chain usa deque, pend chain usa vector
    std::deque<int> main;
    std::vector<int> pend(pairCount);

    // Insert pend[0] no início do deque
    main.push_front(pend[0]);

    // Binary search e insert no deque
    std::deque<int>::iterator pos =
        std::lower_bound(main.begin(), main.end(), pend[i]);
    main.insert(pos, pend[i]);

    // Straggler
    if (hasStraggler) {
        std::deque<int>::iterator pos =
            std::lower_bound(main.begin(), main.end(), straggler);
        main.insert(pos, straggler);
    }

    arr = main;
}
```

**Principais diferenças:**
- Main chain: `std::deque<int>` em vez de `std::vector<int>`
- Pend chain: `std::vector<int>` (auxiliar, pode ser array ou vector)
- Inserção no início: `push_front()` em vez de `insert(begin())`
- Iteradores: `std::deque<int>::iterator` em vez de `std::vector<int>::iterator`
- O `lower_bound` funciona igual para qualquer container com iterador
  bidirecional (deque e vector têm iteradores de acesso aleatório)

### 4.6 Lidando com straggler (n ímpar)

Se a sequência tem um número ímpar de elementos, um elemento "straggler" sobra
após o pareamento. Ele é tratado como um pend item extra no final:

```cpp
bool hasStraggler = (n % 2 == 1);
int straggler = hasStraggler ? arr[n - 1] : 0;

// ... após inserir todos os pend's ...

if (hasStraggler) {
    std::deque<int>::iterator pos =
        std::lower_bound(main.begin(), main.end(), straggler);
    main.insert(pos, straggler);
}
```

O straggler é inserido por último usando binary search, que custa O(log n)
comparações.

### 4.7 Número de comparações

Ford-Johnson é famoso por minimizar o número de comparações no pior caso:

```
n = 1:    0 comparações
n = 2:    1 comparação
n = 3:    3 comparações
n = 4:    5 comparações
n = 5:    7 comparações
n = 6:   10 comparações
n = 7:   13 comparações
n = 8:   16 comparações
n = 16:  42 comparações
n = 32: 100 comparações
```

Para n = 3000, Ford-Johnson faz aproximadamente n log₂ n - n comparações,
o que é equivalente ao Merge Sort no caso médio, mas com melhor desempenho
no pior caso.

### 4.8 Medição de tempo

```cpp
#include <sys/time.h>

static double getTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000.0 + tv.tv_usec;
}

double start = getTime();
fordJohnsonSortVec(vec);
double end = getTime();
double elapsed = end - start;  // em microssegundos
```

### 4.9 Por que a diferença de tempo entre containers?

`std::vector` vs `std::deque`:

| Operação | vector | deque |
|----------|--------|-------|
| Acesso aleatório | O(1) contíguo | O(1) segmentado |
| Inserção no início | O(n) realoca tudo | O(1) ou O(n) |
| Inserção no meio | O(n) | O(n) |
| Inserção no final | O(1) amortizado | O(1) |
| Cache locality | Excelente ✅ | Boa |

O Ford-Johnson faz muitas inserções no meio da main chain (via `lower_bound`
+ `insert`), que em ambos os containers é O(n). No entanto:
- `std::vector` tem melhor localidade de cache (elementos contíguos)
- `std::deque` é implementado como chunks de memória, então tem mais
  overhead de ponteiros indiretos
- Na prática, vector costuma ser mais rápido para sequências de até
  alguns milhares de elementos

### 4.10 Output esperado (formato exato do subject)

```
$> ./PmergeMe 3 5 9 7 4
Before:
3 5 9 7 4
After:
3 4 5 7 9
Time to process a range of 5 elements with std::vector : 4.00000 us
Time to process a range of 5 elements with std::deque : 5.00000 us
```

**Atenção ao formato:** "Before:" e "After:" saem em linhas separadas dos
números, e os números mantêm um espaço à direita antes da quebra de linha.

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

### 5.7 `<cctype>` — std::isdigit (ex00)

Validação de caracteres na data (`std::isdigit`).

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
    float rate;
    std::istringstream(line.substr(comma + 1)) >> rate;
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
// Se it == begin(), usa a taxa do primeiro registro
```

### 6.4 Tabela dos exercícios

| Ex | Programa | Container | STL usada |
|----|----------|-----------|-----------|
| 00 | btc | `std::map` | `<map>`, `<fstream>`, `<sstream>`, `<cctype>` |
| 01 | RPN | `std::stack` | `<stack>`, `<sstream>`, `<stdexcept>` |
| 02 | PmergeMe | `std::vector` + `std::deque` | `<algorithm>`, `<sys/time.h>`, `<utility>` |

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
