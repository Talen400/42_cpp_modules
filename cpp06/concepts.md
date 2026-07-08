# CPP Module 06 — Casts em C++

Esse módulo inteiro é sobre **cast** (conversão de tipos). Você vai aprender os 4 tipos
de cast do C++, quando usar cada um, e por que eles existem.

---

## Índice

1. [Por que C++ criou casts diferentes?](#1-por-que-c-criou-casts-diferentes)
2. [Exercício 00 — static_cast (ScalarConverter)](#2-exercício-00--static_cast-scalarconverter)
3. [Exercício 01 — reinterpret_cast (Serializer)](#3-exercício-01--reinterpret_cast-serializer)
4. [Exercício 02 — dynamic_cast (Identify)](#4-exercício-02--dynamic_cast-identify)
5. [Bibliotecas usadas — detalhado](#5-bibliotecas-usadas--detalhado)
6. [Dicas finais](#6-dicas-finais)

---

## 1. Por que C++ criou casts diferentes?

### Como era em C

Em C, você escrevia `(int)variavel` e pronto. Um único parêntese com o tipo dentro.
O problema é que essa sintaxe **faz tudo**:

```c
(int)3.14                 // double → int (trunca)
(int*)0x1234              // número → ponteiro
(char)'A'                 // já é char, não faz nada
(void(*)(void))0x1234     // número → ponteiro de função
```

Todos usam **a mesma sintaxe**. Você não sabe se quem escreveu queria:
- Converter um número pra outro número?
- Reinterpretar bits como ponteiro?
- Silenciar um warning do compilador?

O compilador também não sabe. Ele só obedece.

### O que C++ fez

C++ criou **4 casts diferentes**, cada um com nome que diz exatamente o que faz:

| Cast | Tradução | O que significa |
|------|----------|-----------------|
| `static_cast` | "cast estático" | Conversão **segura** entre tipos relacionados, em **tempo de compilação** |
| `dynamic_cast` | "cast dinâmico" | Checagem de tipo em **tempo de execução** (pergunta pro objeto: qual seu tipo?) |
| `reinterpret_cast` | "reinterpretar" | Pega os bits de uma variável e **finge** que são de outro tipo |
| `const_cast` | "cast de const" | Remove ou adiciona `const` de uma variável |

A regra do módulo é clara: **sempre use C++ casts**. Tanto que o Makefile tem a flag
`-Wold-style-cast` que **transforma C-style casts em erro de compilação**:

```cpp
int x = (int)3.14;  // Wold-style-cast → WARNING (que vira ERRO com -Werror)
int y = static_cast<int>(3.14);  // OK ✅
```

---

## 2. Exercício 00 — static_cast (ScalarConverter)

### 2.1 O que o exercício quer

Execute o programa passando uma string no terminal:

```
$> ./convert 42.0f
```

O programa deve exibir esse valor convertido para **char, int, float e double**:

```
char: '*'
int: 42
float: 42.0f
double: 42.0
```

### 2.2 Por que isso é difícil?

Porque a entrada é uma **string** — uma sequência de caracteres. O C++ não sabe
que `"42.0f"` é um número. Pra ele, é só `'4', '2', '.', '0', 'f'`.

**Desafio 1**: Descobrir qual tipo a string representa
**Desafio 2**: Converter a string pro valor numérico real
**Desafio 3**: Tratar casos especiais (NaN, infinito, char não imprimível)

### 2.3 A estratégia: "tipo universal"

A sacada é: em vez de detectar o tipo e converter separadamente, usamos `double`
como tipo universal. Por quê?

```
char   (1 byte)  → cabe em double (8 bytes)? SIM
int    (4 bytes) → cabe em double (8 bytes)? SIM  
float  (4 bytes) → cabe em double (8 bytes)? SIM
double (8 bytes) → é double                 SIM
```

Ou seja: qualquer valor que caiba em char, int ou float **também** cabe em double.
Então o fluxo fica:

```
String → double (guarda o valor universal) 
       → depois converte esse double para char, int, float, double separadamente
```

**Visualmente**:

```
                 ┌──────────┐
"42.0f" ───────→ │  double  │ ──→ static_cast<char>(42.0)   → '*'
    │            │  value   │ ──→ static_cast<int>(42.0)    → 42
    │            │  = 42.0  │ ──→ static_cast<float>(42.0)  → 42.0f
    │            └──────────┘ ──→ (double já é double)      → 42.0
    │
    └── strtod() converte string → double
```

### 2.4 Detectando o tipo da string (passo a passo)

#### Pseudo-literais (checar PRIMEIRO)

Existem valores especiais que não são números normais:

| String | Significado | Tipo |
|--------|-------------|------|
| `"nan"` | Not a Number (ex: 0.0/0.0) | double |
| `"+inf"` | Infinito positivo | double |
| `"-inf"` | Infinito negativo | double |
| `"nanf"` | Not a Number | float |
| `"+inff"` | Infinito positivo | float |
| `"-inff"` | Infinito negativo | float |

**Por que checar primeiro?** Porque `strtod("nan")` funcionaria (retorna NaN),
mas `strtod("+inf")` também funciona (retorna infinito). Se deixássemos
`strtod` tratar tudo, não teríamos como distinguir o **tipo original** — se veio
como `nan` (double) ou `nanf` (float). Mas na prática isso não importa (o valor
é o mesmo), então muitos colocam também no `strtod`.

No código do seu colega, ele trata TUDO com `strtod` — simplifica bastante.

#### Char com aspas simples

```cpp
" '*'"       → 3 caracteres: aspas, caractere, aspas
if (str.length() == 3 && str[0] == '\'' && str[2] == '\'')
    value = static_cast<double>(str[1]);  // pega o caractere do meio
```

`str[0]` = `'` (abre aspas)
`str[1]` = `*` (o caractere)
`str[2]` = `'` (fecha aspas)

#### Char solitário (sem aspas)

```cpp
if (str.length() == 1 && !std::isdigit(str[0]))
    value = static_cast<double>(str[0]);
```

Exemplo: `"a"` → value = 97.0 (código ASCII de 'a')

**Por que checar que não é dígito?** Porque `"5"` (um único dígito) deve ser
interpretado como **int** (o número 5), não como char (ASCII 53 = '5').

#### Tentativa com strtod (int, float, double)

Para tudo que sobrou (int, float, double), usamos `strtod`:

```cpp
char* end;
double value = strtod(str.c_str(), &end);
```

**O que `strtod` faz por dentro?**

Ela percorre a string caractere por caractere:

```
"42.5abc" 
  ↓
strtod começa: '4' é dígito, começa a montar o número
              '2' é dígito, continua
              '.' é ponto decimal, continua
              '5' é dígito, continua
              'a' NÃO é dígito → PARA!
              → value = 42.5
              → *end = 'a' (ponteiro aponta pra onde parou)
```

**Como interpretar o resultado:**

| Caso | `*end` | Significado | Exemplo |
|------|--------|-------------|---------|
| Leu tudo | `'\0'` (fim da string) | Era um double | `"42.5"` |
| Sobrou 'f' | `'f'` | Era um float | `"42.5f"` |
| Sobrou outra coisa | qualquer outro char | Entrada inválida | `"42.5abc"` |
| Não leu nada | `*end == str[0]` | Não é número | `"abc"` |

No código:
```cpp
if (*end != '\0' && !(*end == 'f' && *(end + 1) == '\0'))
    // ERRO: não é double nem float → imprime "impossible" pra tudo
```

A condição diz: "se sobrou algo E esse algo não é 'f' no final da string, é inválido".

### 2.5 As 4 funções de conversão

Depois de ter o valor em `double`, chamamos 4 funções que convertem e exibem:

```cpp
convert_char(value);
convert_int(value);
convert_float(value);
convert_double(value);
```

Cada uma faz:
1. Verifica se a conversão é **possível** (não é NaN, não é infinito, cabe no tipo)
2. Converte com `static_cast`
3. Exibe com formatação

#### convert_char

```cpp
static void convert_char(double val) {
    // PASSO 1: Verificar se é possível
    if (std::isnan(val) || std::isinf(val)) {
        cout << "char: impossible\n";
        return;
    }
    
    // PASSO 2: Verificar se cabe em char (-128 a 127)
    if (val > std::numeric_limits<char>::max() || 
        val < std::numeric_limits<char>::min()) {
        cout << "char: impossible\n";
        return;
    }
    
    // PASSO 3: Converter
    char c = static_cast<char>(val);
    
    // PASSO 4: Exibir
    cout << "char: ";
    if (std::isprint(c))
        cout << "'" << c << "'\n";   // 'a', '*', etc.
    else
        cout << "Non displayable\n";  // caracteres de controle (0-31, 127)
}
```

**O que é "non displayable"?**

A tabela ASCII:
```
0-31   → caracteres de controle (nulo, tab, enter, etc.) — NÃO são exibíveis
32     → espaço (é exibível com isprint)
33-126 → caracteres visíveis ('!', 'A', 'z', etc.) — são exibíveis
127    → DEL (não exibível)
128-255 → estendido (depende da codificação)
```

`std::isprint(c)` retorna `true` para caracteres que aparecem na tela (32-126).

**Por que `std::isnan` e `std::isinf`?** Porque se o valor for NaN (0.0/0.0) ou
infinito (1.0/0.0), **não faz sentido** converter pra char — não existe caractere
que represente "não é um número".

#### convert_int

```cpp
static void convert_int(double val) {
    // Mesmos checks: NaN e infinito não viram int
    if (std::isnan(val) || std::isinf(val)) {
        cout << "int: impossible\n";
        return;
    }
    
    // Verifica se cabe em int
    if (val > std::numeric_limits<int>::max() || 
        val < std::numeric_limits<int>::min()) {
        cout << "int: impossible\n";
        return;
    }
    
    int i = static_cast<int>(val);
    cout << "int: " << i << "\n";
}
```

**O que é `std::numeric_limits<int>::max()`?** É 2147483647. O maior inteiro que
cabe em 32 bits com sinal.

**Por que checar?** Se `val = 1e20` (100000000000000000000), ao converter pra int,
o resultado seria **imprevisível** (undefined behavior). Melhor avisar o usuário.

#### convert_float

```cpp
static void convert_float(double val) {
    cout << "float: ";
    
    if (std::isnan(val))
        cout << "nanf";
    else if (std::isinf(val))
        cout << (val > 0 ? "+inff" : "-inff");
    else
        cout << std::fixed << std::setprecision(1) 
             << static_cast<float>(val) << "f";
    
    cout << "\n";
}
```

**Por que tratar NaN e infinito separadamente?** Porque `std::cout` não sabe
exibir NaN direito. Se você fizer `cout << static_cast<float>(nan)`, pode sair
qualquer coisa. Melhor exibir `"nanf"` explicitamente.

**O que `std::fixed` faz?** Força notação decimal (em vez de notação científica):

```cpp
cout << 1000000.0;                        // "1e+06" (notação científica)
cout << std::fixed << 1000000.0;          // "1000000.0" (notação decimal)
```

**O que `std::setprecision(1)` faz?** Define 1 casa decimal:

```cpp
cout << std::fixed << std::setprecision(1) << 42.0;   // "42.0"
cout << std::fixed << std::setprecision(1) << 3.1415;  // "3.1"
cout << std::fixed << std::setprecision(1) << 0.0;     // "0.0"
```

**E se o número tiver mais casas decimais?** Com `setprecision(1)`, elas são
arredondadas:

```cpp
cout << std::fixed << std::setprecision(1) << 3.14159;  // "3.1"
cout << std::fixed << std::setprecision(1) << 2.9999;   // "3.0"
```

Pra esse exercício, isso é aceitável. O subject só mostra exemplos com `.0`.

#### convert_double

Exatamente igual ao `convert_float`, mas sem o `"f"` no final:

```cpp
static void convert_double(double val) {
    cout << "double: ";
    
    if (std::isnan(val))
        cout << "nan";
    else if (std::isinf(val))
        cout << (val > 0 ? "+inf" : "-inf");
    else
        cout << std::fixed << std::setprecision(1) << val;
    
    cout << "\n";
}
```

### 2.6 Exemplo completo com tracing

```
Entrada: "42.0f"

1. Detecção:
   - É pseudo-literal? "nan"? "inf"? NÃO → continua
   - É char com aspas? (3 chars, começa e termina com ')? NÃO → continua
   - É char solitário? (len=1 e não dígito)? NÃO → continua
   - Tenta strtod:
     value = strtod("42.0f", &end)
     → lê "42.0", para no 'f'
     → value = 42.0
     → *end = 'f'
     → *end != '\0'? SIM → verifica: *end == 'f' e *(end+1) == '\0'? SIM → OK, aceita

2. convert_char(42.0):
   - isnan(42.0)? NÃO
   - isinf(42.0)? NÃO
   - 42.0 > 127? NÃO
   - 42.0 < -128? NÃO
   - c = static_cast<char>(42.0) = 42 (trunca, mas já é inteiro)
   - isprint(42)? SIM (42 = '*' na ASCII)
   → "char: '*'"

3. convert_int(42.0):
   - isnan(42.0)? NÃO
   - isinf(42.0)? NÃO
   - 42.0 > INT_MAX? NÃO
   - 42.0 < INT_MIN? NÃO
   - i = static_cast<int>(42.0) = 42
   → "int: 42"

4. convert_float(42.0):
   - isnan? NÃO
   - isinf? NÃO
   - fixed << setprecision(1) << static_cast<float>(42.0) << "f"
   → "float: 42.0f"

5. convert_double(42.0):
   - isnan? NÃO
   - isinf? NÃO
   - fixed << setprecision(1) << 42.0
   → "double: 42.0"

Resultado final:
char: '*'
int: 42
float: 42.0f
double: 42.0
```

### 2.7 Exemplo com NaN

```
Entrada: "nan"

1. Detecção:
   - str == "nan"? SIM → pseudo-literal double
   - value = strtod("nan", &end) → value = NaN

2. convert_char(NaN):
   - isnan(NaN)? SIM → "char: impossible"

3. convert_int(NaN):
   - isnan(NaN)? SIM → "int: impossible"

4. convert_float(NaN):
   - isnan(NaN)? SIM → "float: nanf"

5. convert_double(NaN):
   - isnan(NaN)? SIM → "double: nan"

Resultado:
char: impossible
int: impossible
float: nanf
double: nan
```

### 2.8 Por que a classe não pode ser instanciada?

O subject diz: "Como esta classe não precisa armazenar nada, ela não deve ser
instanciável por usuários."

Uma classe com **só métodos estáticos** não precisa de objeto pra funcionar.
Faz sentido proibir a criação de instâncias:

```cpp
ScalarConverter::convert("42");  // OK: método estático, sem instância

ScalarConverter obj;              // deveria ser proibido
obj.convert("42");                // não faz sentido ter um objeto
```

Para proibir, colocamos **todos os construtores no `private`**:

```cpp
class ScalarConverter {
private:
    ScalarConverter();                           // ninguém pode chamar
    ScalarConverter(const ScalarConverter&);     // ninguém pode copiar
    ScalarConverter& operator=(const ScalarConverter&);  // ninguém pode atribuir
    ~ScalarConverter();                          // ninguém pode destruir
public:
    static void convert(const std::string& in);
};
```

Tentativas de criar um objeto viram erro de compilação:
```cpp
ScalarConverter x;           // ERRO: construtor privado
ScalarConverter y(x);        // ERRO: cópia privada
ScalarConverter* p = new ScalarConverter();  // ERRO: construtor privado
```

---

## 3. Exercício 01 — reinterpret_cast (Serializer)

### 3.1 O que o exercício quer

Criar uma classe `Serializer` com dois métodos estáticos:

```cpp
uintptr_t serialize(Data* ptr);    // Data* → inteiro
Data* deserialize(uintptr_t raw);  // inteiro → Data*
```

E testar:
```cpp
Data original;
uintptr_t raw = serialize(&original);
Data* restored = deserialize(raw);
// restored == &original? SIM!
```

### 3.2 O que é um ponteiro? (visão baixo nível)

Quando você declara uma variável:

```cpp
int x = 42;
```

O computador guarda esse valor **em algum lugar da memória**. Esse lugar tem um
**endereço**. O endereço é um número.

```
         MEMÓRIA
    ┌─────────────────┐
    │                 │
    │    ...          │
    │                 │
    │   ┌──────────┐  │  ← endereço 0x7ffc83699d30
    │   │    42    │  │    (aqui está o int x)
    │   └──────────┘  │
    │                 │
    │    ...          │
    │                 │
    └─────────────────┘
```

Um ponteiro `int* ptr = &x` guarda esse **endereço** (um número):

```
ptr = 0x7ffc83699d30  (que é 140722513222960 em decimal)
```

Então um ponteiro é **literalmente um número inteiro**. A diferença é que o
compilador sabe que esse número é um endereço de memória e que lá dentro tem um
`int`.

### 3.3 Serializar = transformar em número

Se um ponteiro já é um número... por que não podemos simplesmente fazer?

```cpp
uintptr_t n = ptr;  // ERRO: não pode converter implicitamente
```

O C++ **proíbe** conversão implícita de ponteiro pra inteiro porque é muito
perigoso — se você fizer isso, o compilador quer ter certeza de que você sabe
o que está fazendo. Por isso você precisa de `reinterpret_cast`:

```cpp
uintptr_t n = reinterpret_cast<uintptr_t>(ptr);
```

É como dizer: "Compilador, **eu sei** que isso é perigoso. Confia em mim."

### 3.4 O que acontece na memória

```
ANTES da serialização:

    &original = 0x7ffc83699d30
    
    ┌──────────────────┐
    │ original.id = 42 │  ← endereço 0x7ffc83699d30
    │ original.name    │
    └──────────────────┘
    
serialize(&original):
    → reinterpret_cast<uintptr_t>(0x7ffc83699d30)
    → Pega o número 0x7ffc83699d30 e "finge" que é um uintptr_t
    → raw = 140722513222960

Depois da serialização:

    raw = 140722513222960  ← é o mesmo endereço, só que como número

deserialize(raw):
    → reinterpret_cast<Data*>(140722513222960)
    → Pega o número 140722513222960 e "finge" que é um Data*
    → restored = 0x7ffc83699d30

restored aponta pro MESMO lugar que &original
    → restored->id = 42 ✓
    → restored == &original ✓
```

### 3.5 Por que `reinterpret_cast` e não `static_cast`?

```cpp
int* p = &x;

// static_cast: "converte o VALOR"
uintptr_t a = static_cast<uintptr_t>(p);  // ERRO de compilação!

// reinterpret_cast: "reinterpreta os BITS"
uintptr_t b = reinterpret_cast<uintptr_t>(p);  // OK
```

`static_cast` quer **converter o valor** (ex: 3.14 → 3). Mas ponteiro pra inteiro
não é uma conversão de valor — é uma **reinterpretação**: "esses bytes que eram
um endereço agora são um número inteiro".

A diferença conceitual:

```
static_cast:    double 42.5 → int 42  (MUDOU o valor)
reinterpret_cast:  ponteiro 0x7ffc... → uintptr_t 140722513222960 (MESMO valor, interpretação diferente)
```

### 3.6 O que é `uintptr_t`?

`uintptr_t` = **unsigned int**eger capable of holding a **p**oin**t**e**r**'s add**r**ess.

É um alias (apelido) definido em `<stdint.h>`:

```cpp
// Em sistemas 64 bits:
typedef unsigned long uintptr_t;

// Em sistemas 32 bits:
typedef unsigned int uintptr_t;
```

Ele sempre tem o **mesmo tamanho** de um ponteiro na plataforma atual.

**Tabela comparativa:**

| Tipo | 32 bits | 64 bits |
|------|---------|---------|
| `char` | 1 byte | 1 byte |
| `int` | 4 bytes | 4 bytes |
| `long` | 4 bytes | 8 bytes |
| `uintptr_t` | 4 bytes | 8 bytes |
| Ponteiro | 4 bytes | 8 bytes |

### 3.7 Por que `unsigned` e não `signed`?

Endereços de memória são sempre números **positivos** (não existe endereço negativo).
Por isso `uintptr_t` é `unsigned`.

Comparação:

```cpp
intptr_t n = reinterpret_cast<intptr_t>(ptr);    // signed (raro)
uintptr_t n = reinterpret_cast<uintptr_t>(ptr);  // unsigned (padrão)
```

O subject pede `uintptr_t` especificamente.

### 3.8 A ordem dos includes em `<stdint.h>` vs `<cstdint>`

Em C++98, a única forma portável de obter `uintptr_t` é:

```cpp
#include <stdint.h>  // C++98: uintptr_t no namespace global
```

Em C++11+, você pode usar:

```cpp
#include <cstdint>   // C++11+: uintptr_t no namespace std
```

Se você tentar `<cstdint>` com `-std=c++98`, o compilador dá erro:
```
#error This file requires compiler and library support for the ISO C++ 2011 standard
```

Então no módulo 06 (C++98), use sempre `<stdint.h>`.

### 3.9 Implementação completa

```cpp
// Serializer.hpp
#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <stdint.h>
#include "Data.hpp"

class Serializer {
private:
    Serializer();
    Serializer(const Serializer& other);
    Serializer& operator=(const Serializer& other);
    ~Serializer();

public:
    static uintptr_t serialize(Data* ptr);
    static Data* deserialize(uintptr_t raw);
};

#endif
```

```cpp
// Serializer.cpp
#include "Serializer.hpp"

uintptr_t Serializer::serialize(Data* ptr) {
    return reinterpret_cast<uintptr_t>(ptr);
}

Data* Serializer::deserialize(uintptr_t raw) {
    return reinterpret_cast<Data*>(raw);
}
```

Cada método tem **exatamente uma linha**. O `reinterpret_cast` faz todo o trabalho.

```cpp
// Data.hpp
#ifndef DATA_HPP
#define DATA_HPP

#include <string>

struct Data {
    int id;
    std::string name;
};

#endif
```

A struct precisa ser **não vazia** — por isso tem `id` e `name`.

### 3.10 Teste

```cpp
int main() {
    Data original;
    original.id = 42;
    original.name = "Hello";
    
    uintptr_t raw = Serializer::serialize(&original);
    Data* restored = Serializer::deserialize(raw);
    
    // Verificação
    if (restored == &original)
        cout << "OK: pointers match!\n";
    
    // Ainda podemos acessar os dados
    cout << restored->id << "\n";       // 42
    cout << restored->name << "\n";     // Hello
}
```

### 3.11 Por que isso não é perigoso AQUI?

Neste exercício, serializamos e desserializamos **na mesma execução**, com o
objeto **ainda vivo**. O endereço continua válido.

Situações PERIGOSAS onde isso quebraria:

```cpp
Data* p = new Data;
uintptr_t raw = Serializer::serialize(p);
delete p;                          // objeto destruído!
// ...
Data* p2 = Serializer::deserialize(raw);  // raw agora é um endereço INVÁLIDO
p2->id = 10;  // CRASH! O objeto não existe mais (dangling pointer)
```

Ou:

```cpp
Data* p = new Data;
uintptr_t raw = Serializer::serialize(p);
// Salva raw em arquivo, fecha o programa...
// ...abre de novo, lê raw do arquivo...
Data* p2 = Serializer::deserialize(raw);  // endereço de outra execução!
p2->id = 10;  // CRASH! Endereço inválido
```

**Endereços de memória mudam a cada execução** por causa da ASLR (Address Space
Layout Randomization) — um recurso de segurança do sistema operacional.

### 3.12 Exercício 01 em uma frase

> "Um ponteiro é um número. `reinterpret_cast` deixa você tratar esse número como
> inteiro e depois transformar de volta em ponteiro."

---

## 4. Exercício 02 — dynamic_cast (Identify)

### 4.1 O que o exercício quer

```cpp
class Base { public: virtual ~Base(); };
class A : public Base {};
class B : public Base {};
class C : public Base {};

Base* generate(void);    // cria A, B ou C aleatoriamente
void identify(Base* p);  // descobre o tipo via ponteiro
void identify(Base& p);  // descobre o tipo via referência (sem usar ponteiros!)
```

### 4.2 O problema: você perdeu o tipo

Quando você cria um objeto e o guarda como `Base*`, o compilador não sabe mais
qual é o tipo real:

```cpp
Base* p = new A;  // O objeto É um A, mas o compilador "esqueceu"
```

**Por que isso acontece?** Porque C++ é **estaticamente tipado**. O tipo da
variável `p` é `Base*`, e é isso que o compilador sabe em tempo de compilação.

**Mas em tempo de execução**, o objeto REALMENTE é um `A`. Se você chamar uma
função virtual, a chamada vai pra função correta (polimorfismo). Mas e se você
quiser **saber** qual é o tipo?

### 4.3 Como `dynamic_cast` resolve

`dynamic_cast` pergunta ao objeto: **"você é um X?"** em tempo de execução.

A classe precisa ter **RTTI** (Run-Time Type Information). O compilador guarda
uma "etiqueta" escondida dentro de cada objeto identificando seu tipo real.

```
Objeto A na memória:
┌──────────────────────────┐
│  vtable pointer ──────── │──→ Tabela de funções virtuais
│                          │    (inclui informações de tipo)
│  dados de A              │
│  ...                     │
└──────────────────────────┘

Essa "vtable" contém informações que o dynamic_cast usa.
```

**Condição**: a classe BASE precisa ter pelo menos uma função `virtual`. Sem
virtual, não há vtable → não há RTTI → `dynamic_cast` não funciona (erro de
compilação).

### 4.4 identify(Base* p) — com ponteiro

```cpp
void identify(Base* p) {
    if (dynamic_cast<A*>(p))          // Tenta: "p é um A?"
        cout << "A\n";
    else if (dynamic_cast<B*>(p))     // Tenta: "p é um B?"
        cout << "B\n";
    else if (dynamic_cast<C*>(p))     // Tenta: "p é um C?"
        cout << "C\n";
}
```

**Como funciona internamente?**

```
p = endereço de um objeto B

1. dynamic_cast<A*>(p):
   - Olha a vtable de p
   - "Você é um A?" → "Não, sou um B"
   - Retorna NULL

2. dynamic_cast<B*>(p):
   - Olha a vtable de p  
   - "Você é um B?" → "Sim!"
   - Retorna o ponteiro B* válido

3. Entra no if (ponteiro não é NULL)
   → Imprime "B"
```

**Por que testar na ordem A, B, C?** Qualquer ordem funciona, desde que você
teste os 3. Se nenhum casar, algo está errado.

**Detalhe importante**: `dynamic_cast<A*>(p)` retorna `NULL` se não for A.
NULL em C++ é `0`, que em contexto booleano é `false`. Então `if (dynamic_cast...)`
funciona direto — nem precisa comparar com NULL.

### 4.5 identify(Base& p) — com referência (sem ponteiros!)

O subject proíbe usar ponteiros dentro desta função. Nem `&p` pra pegar endereço.

Com referência, `dynamic_cast` funciona **diferente**:

```cpp
// Com ponteiro: retorna NULL se falhar
A* a = dynamic_cast<A*>(p);

// Com referência: LANÇA EXCEÇÃO se falhar!
A& a = dynamic_cast<A&>(p);  // Se p não for A → std::bad_cast
```

**Por que essa diferença?** Porque em C++, **referências não podem ser nulas**.
Não existe "referência nula". Então `dynamic_cast` não pode retornar "referência
nula" pra indicar falha — ele precisa de outro mecanismo: a **exceção**.

Solução: `try/catch`

```cpp
void identify(Base& p) {
    try {
        A& a = dynamic_cast<A&>(p);
        (void)a;          // silencia warning "variável não usada"
        cout << "A\n";
        return;           // se chegou aqui, achou → sai
    } catch (...) {}       // se lançou exceção → não é A

    try {
        B& b = dynamic_cast<B&>(p);
        (void)b;
        cout << "B\n";
        return;
    } catch (...) {}

    // Se não é A nem B, só pode ser C
    cout << "C\n";
}
```

**O que `catch (...)` pega?** Tudo. Qualquer exceção. Neste caso, é
especificamente `std::bad_cast`, mas `...` serve.

**Por que `(void)a`?** Porque a variável `a` é declarada mas nunca usada. O
compilador avisa: "warning: unused variable 'a'". O `(void)` silencia isso.
Poderíamos usar o nome da variável só:

```cpp
// Alternativa: não nomear a variável (mas não dá pra fazer em C++98)
```

Ou simplesmente ignorar o warning (mas com `-Werror`, warning = erro).

**Por que o `return` dentro de cada try?** Sem o `return`, mesmo depois de
identificar como A, o código continuaria testando B e C. O `return` garante
que paramos assim que descobrimos o tipo.

### 4.6 generate() — aleatoriedade

```cpp
Base* generate(void) {
    int r = rand() % 3;  // 0, 1, ou 2
    
    if (r == 0) return new A;
    if (r == 1) return new B;
    return new C;         // r == 2
}
```

**Como `rand()` funciona?**

```cpp
#include <cstdlib>

int rand();  // retorna número pseudo-aleatório entre 0 e RAND_MAX
```

**O que é RAND_MAX?** Geralmente 2147483647 (2³¹-1).

**O que é `% 3`?** O resto da divisão por 3. Distribui uniformemente:

```
rand() = 0      → 0 % 3 = 0 → new A
rand() = 1      → 1 % 3 = 1 → new B
rand() = 2      → 2 % 3 = 2 → new C
rand() = 3      → 3 % 3 = 0 → new A
rand() = 4      → 4 % 3 = 1 → new B
...
```

**Por que `srand(time(NULL))` no main?**

Sem `srand`, `rand()` sempre produz a **mesma sequência** toda execução:

```cpp
// Sem srand:
rand() → 1804289383, 846930886, 1681692777... (sempre esses números)

// Com srand(time(NULL)):
// time(NULL) = segundos desde 1970
// Cada execução em segundos diferentes → sequência diferente
```

Chame `srand` **uma única vez** no começo do `main()`:

```cpp
int main() {
    srand(static_cast<unsigned int>(time(NULL)));
    // ... testar generate várias vezes
}
```

### 4.7 Por que o destrutor virtual é obrigatório?

**Razão 1: `dynamic_cast` precisa de RTTI**

RTTI só é gerado para classes com **pelo menos uma função virtual**. O destrutor
virtual conta como função virtual.

```cpp
class Base {
public:
    virtual ~Base();  // ativa RTTI → dynamic_cast funciona
};

// Sem virtual:
class Base {
public:
    ~Base();  // sem virtual → sem RTTI → dynamic_cast NÃO funciona
};

Base* p = new A;
dynamic_cast<A*>(p);  // ERRO de compilação!
```

**Razão 2: Destruição polimórfica correta**

```cpp
Base* p = new A;   // A herda de Base
delete p;           // O que acontece?
```

Se `~Base()` é **virtual**:
```
delete p:
  → chamado ~A()   (destrutor de A)
  → chamado ~Base() (destrutor de Base)
  → memória liberada ✅
```

Se `~Base()` NÃO é virtual:
```
delete p:
  → chamado ~Base() (destrutor de Base, NÃO de A!)
  → recursos de A vazaram! ❌
```

**Regra**: Se uma classe tem funções virtuais ou vai ser usada polimorficamente,
o destrutor DEVE ser virtual.

### 4.8 Fluxo completo de execução

```
main():
  srand(time(NULL))
  
  for (i = 0; i < 3; i++) {
    p = generate()
      → rand() % 3 = 0 → return new A
    
    identify(p):                  // identifica por ponteiro
      dynamic_cast<A*>(p)? → ✅ "A"
    
    identify(*p):                 // identifica por referência
      try dynamic_cast<A&>(*p) → ✅ "A"
      (catch não executado)
    
    delete p
  }
```

### 4.9 Exercício 02 em uma frase

> "Um objeto esconde seu tipo verdadeiro atrás de um ponteiro da classe base.
> `dynamic_cast` descobre a verdade: tenta converter pra cada tipo possível até
> um funcionar."

---

## 5. Bibliotecas usadas — detalhado

### 5.1 `<limits>` — `std::numeric_limits<T>`

**O que é?** Um template que fornece os valores extremos de tipos numéricos.

**Por que existe?** Em C, você usava macros como `INT_MAX`, `CHAR_MIN`. Em C++,
`std::numeric_limits` é a versão **tipada** e **extensível** (funciona pra seus
próprios tipos também).

```cpp
#include <limits>

std::numeric_limits<char>::max()   // 127
std::numeric_limits<char>::min()   // -128
std::numeric_limits<int>::max()    // 2147483647
std::numeric_limits<int>::min()    // -2147483648
std::numeric_limits<float>::max()  // 3.40282e+38
std::numeric_limits<double>::max() // 1.79769e+308
```

**Outros métodos úteis:**

```cpp
std::numeric_limits<double>::epsilon();      // menor diferença entre 2 doubles
std::numeric_limits<double>::infinity();     // infinito
std::numeric_limits<double>::quiet_NaN();    // NaN
std::numeric_limits<int>::digits;            // número de bits (excluindo sinal)
std::numeric_limits<float>::digits10;        // número de dígitos decimais precisos
```

### 5.2 `<cmath>` — `std::isnan()` e `std::isinf()`

**O que é?** Funções que verificam se um número é NaN (Not a Number) ou infinito.

**O que é NaN?**

```cpp
double nan = 0.0 / 0.0;     // zero dividido por zero = NaN
double inf = 1.0 / 0.0;     // número dividido por zero = infinito
double neg = -1.0 / 0.0;    // -infinito
```

**Por que não posso comparar com `==`?**

```cpp
double x = 0.0 / 0.0;
if (x == 0.0 / 0.0)  // FALSO! NaN nunca é igual a nada, nem a si mesmo!
if (x == x)           // FALSO! (propriedade curiosa do NaN)

// Por isso existe isnan():
if (std::isnan(x))    // VERDADEIRO ✅
```

**`std::isinf`:**

```cpp
double y = 1.0 / 0.0;
std::isinf(y);        // true ✅
std::isinf(-y);       // true ✅
```

### 5.3 `<iomanip>` — `std::fixed` e `std::setprecision()`

**O que são?** "Manipuladores" de stream que controlam como números são exibidos.

**`std::fixed`**: Força notação decimal (sem notação científica).

```cpp
cout << 1000000.0;           // "1e+06"
cout << fixed << 1000000.0; // "1000000.0"
```

**`std::setprecision(n)`**: Define o número de casas decimais.

```cpp
cout << fixed << setprecision(2) << 3.14159;  // "3.14"
cout << fixed << setprecision(0) << 3.14159;  // "3"
```

**Comportamento combinado:**

```cpp
cout << fixed << setprecision(1);
cout << 0.0;      // "0.0"
cout << 42.0;     // "42.0"
cout << 3.14;     // "3.1"  (arredondou)
```

**Importante**: `std::fixed` e `std::setprecision` são "pegajosos" (sticky) —
uma vez setados, afetam todos os outputs seguintes até serem alterados.

### 5.4 `<cstdlib>` — `strtod()`

**Nome:** **str**ing **to** **d**ouble.

```cpp
double strtod(const char* str, char** endptr);
```

**Parâmetros:**
- `str`: string de entrada
- `endptr`: ponteiro que será atualizado pra posição onde a leitura parou

**Retorno:** o valor numérico lido (ou 0 se não conseguiu ler nada)

**Como usar passo a passo:**

```cpp
const char* str = "  42.5abc  ";
char* end;

double value = strtod(str, &end);

// Antes:
// str → "  42.5abc  "
//       ↑
//       str

// strtod começa:
// - Pula espaços em branco
// - Lê sinais opcionais (+/-)
// - Lê dígitos e ponto decimal
// - Para no primeiro caractere não numérico

// Depois:
// value = 42.5
// end → "abc  "
//        ↑
//        end
```

**Casos especiais:**

```cpp
strtod("nan", &end);    // value = NaN
strtod("inf", &end);    // value = +infinito
strtod("-inf", &end);   // value = -infinito
strtod("", &end);       // value = 0.0, end = "" (não avançou)
strtod("abc", &end);    // value = 0.0, end = "abc" (não avançou)
```

**Detectando erros:**

```cpp
if (end == str) {
    // strtod não conseguiu ler NADA
    // A string não começa com um número
}

if (*end != '\0') {
    // strtod parou antes do fim da string
    // Sobraram caracteres não lidos
}
```

### 5.5 `<stdint.h>` — `uintptr_t`

**O que é?** Um header que define tipos inteiros de **tamanho fixo**.

```cpp
int8_t    // signed 8 bits   (-128 a 127)
int16_t   // signed 16 bits  (-32768 a 32767)
int32_t   // signed 32 bits  (-2147483648 a 2147483647)
int64_t   // signed 64 bits  (-2^63 a 2^63-1)

uint8_t   // unsigned 8 bits  (0 a 255)
uint16_t  // unsigned 16 bits (0 a 65535)
uint32_t  // unsigned 32 bits (0 a 4294967295)
uint64_t  // unsigned 64 bits (0 a 2^64-1)

uintptr_t // unsigned, tamanho = tamanho de um ponteiro
intptr_t  // signed, tamanho = tamanho de um ponteiro
```

**Por que usar `uintptr_t` em vez de `unsigned long`?**

| Arquitetura | Tamanho do ponteiro | `unsigned long` | `uintptr_t` |
|-------------|---------------------|-----------------|-------------|
| x86 (32 bits) | 4 bytes | 4 bytes ✅ | 4 bytes ✅ |
| x64 (64 bits) | 8 bytes | 8 bytes ✅ | 8 bytes ✅ |
| IA64 (Itanium) | 8 bytes | 8 bytes ✅ | 8 bytes ✅ |
| Arduino (AVR) | 2 bytes | 4 bytes ❌ | 2 bytes ✅ |

`uintptr_t` é **portável** entre arquiteturas. `unsigned long` não é.

### 5.6 `<climits>` — macros C

```cpp
#include <climits>

CHAR_BIT    // 8 (bits por byte)
SCHAR_MIN   // -128
SCHAR_MAX   // 127
UCHAR_MAX   // 255
CHAR_MIN    // -128 (ou 0 se char é unsigned)
CHAR_MAX    // 127 (ou 255)
SHRT_MIN    // -32768
SHRT_MAX    // 32767
INT_MIN     // -2147483648
INT_MAX     // 2147483647
LONG_MIN    // -9223372036854775808 (em 64 bits)
LONG_MAX    // 9223372036854775807
```

Equivalente C de `<limits>`. As macros vieram do `<limits.h>` do C.

### 5.7 `<cctype>` — `std::isprint()` e `std::isdigit()`

```cpp
#include <cctype>

std::isprint(c)  // true se c for imprimível (32-126)
std::isdigit(c)  // true se c for dígito ('0'-'9')
std::isalpha(c)  // true se c for letra ('A'-'Z', 'a'-'z')
std::isalnum(c)  // true se c for letra ou dígito
std::isspace(c)  // true se c for espaço, tab, newline...
```

Usado no ex00 para:
- `std::isprint(c)`: decidir se exibe `'c'` ou "Non displayable"
- `std::isdigit(str[0])`: diferenciar `"5"` (int 5) de `"a"` (char 'a')

---

## 6. Dicas finais

### 6.1 Tabela comparativa dos 3 casts

| Cast | Tempo | Segurança | O que faz | Erro se falhar |
|------|-------|-----------|-----------|----------------|
| `static_cast` | Compilação | Média | Converte valor entre tipos relacionados | Erro de compilação |
| `dynamic_cast` | Execução | Alta | Pergunta ao objeto seu tipo real | NULL (ptr) ou exceção (ref) |
| `reinterpret_cast` | Compilação | **Nenhuma** | Reinterpreta bits | **Comportamento indefinido** |

### 6.2 Ordem dos includes (boa prática)

```cpp
// 1. Header próprio (sempre primeiro — testa se inclui tudo que precisa)
#include "ScalarConverter.hpp"

// 2. Biblioteca padrão
#include <iostream>
#include <string>

// 3. Outros headers do projeto
#include "Data.hpp"
```

**Por que essa ordem?** Se o seu header `ScalarConverter.hpp` esqueceu de incluir
`<string>`, você descobre na hora em vez de descobrir em outro arquivo.

### 6.3 `std::endl` vs `'\n'`

```cpp
cout << "linha 1" << endl;    // escreve + flush (força saída pro terminal)
cout << "linha 2" << '\n';    // escreve só (mais rápido)
```

**`endl`** = `'\n'` + flush. O flush força o buffer a ser escrito imediatamente.

**Quando usar cada um?**

- `'\n'`: 99% dos casos. Mais rápido.
- `endl`: logs em tempo real, crash imminent, depuração.

O subject pede apenas "terminar com nova linha". `'\n'` é suficiente.

### 6.4 Flag `-Wconversion` no Makefile

```makefile
CFLAGS := -Wall -Werror -Wextra -std=c++98 -Wconversion
```

Essa flag ativa warnings para conversões que podem perder dados:

```cpp
double d = 3.14;
int i = d;  // Warning: conversão pode perder dados! (3.14 → 3)
```

Pra silenciar, use `static_cast`:

```cpp
int i = static_cast<int>(d);  // Sem warning: você explicitamente disse que quer
```

### 6.5 Flag `-Wold-style-cast` no Makefile

```makefile
CFLAGS := ... -Wold-style-cast
```

Essa flag avisa sobre C-style casts `(int)x`. Com `-Werror`, vira erro:

```cpp
int i = (int)3.14;  // ERRO!
int i = static_cast<int>(3.14);  // OK ✅
```

### 6.6 Flag `-Wstrict-aliasing=3` no Makefile

Essa flag evita uma otimização perigosa do compilador. Exemplo do que ELA
previne:

```cpp
int x = 42;
float* p = (float*)&x;  // reinterpretar int como float
*p = 3.14f;             // comportamento indefinido!
```

Com `static_cast`/`reinterpret_cast` explícitos, isso não acontece.

### 6.7 Resumo dos exercícios

| Ex | Nome | Cast principal | O que você aprendeu |
|----|------|----------------|---------------------|
| 00 | ScalarConverter | `static_cast` | Converter string → 4 tipos escalares; detectar tipo de um literal; usar `strtod`; `std::numeric_limits` |
| 01 | Serializer | `reinterpret_cast` | Ponteiro é um número; `uintptr_t`; serialização de ponteiros |
| 02 | Identify | `dynamic_cast` | Identificar tipo real em hierarquia de classes; RTTI; destrutor virtual; `try/catch` com referências |
