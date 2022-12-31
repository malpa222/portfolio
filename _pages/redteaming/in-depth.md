---
title: In-depth research
layout: single
permalink: /redt/in-depth
---

This document is a follow-up on the trends research, precisely on the topic of cross-platform malware. Since virtually everybody owns a smartphone or a personal
computer, the amount of different platforms that are running on our hardware is bigger than it ever was. This forces malware developers to spend much more
time on creating malware for each of these systems.

Nowadays, with the rise of new systems programming languages such as Rust or Go, developing malicious software for different platforms has become more accessible
and much quicker than before. I want to investigate why developers would choose cross-platform toolchains and how the technologies could be leveraged for malware
development purposes.

## Research questions

Because portable software is a broad subject, I have decided to only focus on some key parts of the domain. My research will try to answer the following question,
along with the sub-questions:

**How can LLVM compiler infrastructure be used to aid malware development?**

- Why would a malware developer choose an LLVM based language?
- What contributes to the flexibility and modularity of LLVM?
- How to develop a plugin for LLVM's optimization pipeline?
- How to use control flow flattening obfuscation technique with LLVM?

### Research strategies

In order to answer the sub-questions and produce the conclusion of the research I will combine different research strategies. This approach is going to allow me
to organize my work and validate the quality of my research.

- **Why would a malware developer choose an LLVM based language?**

    I need to find out what are the most commonly used languages for malware development and what are the most important characteristics of such language.
    Then, I will try to research whether an LLVM-based language might be a good choice. Therefore, the first research question will mainly require using the
    Library strategy.

- **What contributes to the flexibility and modularity of LLVM?**

    The LLVM toolchain is a set of compiler technologies that allow developers to create compiler front-ends in a platform-agnostic way. It is used by more
    and more languages because it removes a lot of effort needed for compiler development. I want to research why Rust is using it and how to develop custom
    plugins for the framework. To do that, I need to use the Library research to find out how to develop plugins and then Workshop to create initial prototypes.

- **How to develop a plugin for LLVM's optimization pipeline?**

    Using the input from the previous research question, I want to build on it to find out how LLVM can be used for malware development purposes.

    Rust is a very recent case of a programming language built on the LLVM toolchain. However, this is not the only one. Many programming languages are built
    on it. The framework allows for a lot of flexibility and is very modular. Therefore, I want to investigate how it works and how it can be used by the malware
    developers.

- **How effective is the flow flattening obfuscation technique?**

    After investigating the compilation process of the LLVM based compilers, I will create a proof of concept software that will put the LLVM's possibilities to
    the test. The goal is to try and implement the control flow flattening algorithm in the LLVM optimization pipeline to make reverse engineering harder. This
    will require Library research for learning about the algorithm and then Lab and Workshop for implementing and testing the results.

Having researched all the sub-questions I would be ready to produce the answer to the final question. To do that, I need to use the product of the research in the Lab
to see if and how does it work and then present it to my peers in the Workshop strategy.

## Why would a malware developer choose an LLVM based language?

Malware development has always revolved around writing low-level code that interacts closely with a kernel of an OS. Linux kernel is written in C and Windows kernel in
C++. This means that majority of the malware developed throughout the years has been written in C or C++, since it allows for the best compatibility with native APIs.
According to _[Malpedia](https://malpedia.caad.fkie.fraunhofer.de/stats/linker_info)_, majority of viruses in their database are using MSVC linkers which suggests that
the software was written in languages from the C family, developed directly on Windows.

| ![Linkers used for compiling malware](../../assets/img/indepth/linkers.png) |
| Linkers used for compiling malware |

In November of 2021, first samples of the BlackCat ransomware were noticed by security researchers. BlackCat is a malware family that's written in Rust. The main
benefit of that language is memory safety, ease of development and most importantly cross-platform compilation. Because the language is built using the LLVM compiler
toolchain, it is very ease to compile it to a CPU with a different instruction set. This event showed that Rust and LLVM as a choice for malware development are
starting to gain traction.

| ![LLVM Optimization Pipeline](../../assets/img/publication/llvm_pipeline.jpeg) |
| LLVM Optimization Pipeline |

LLVM facilitates cross-platform compilation by slightly altering the compilation process. In essence, the code is translated to an abstract assembly language,
which is then compiled to the specific CPU architecture. This intermediate language allows developers to create plugins that can 'optimize' the intermediate
representation (IR) to make it run faster for example.

Let's look at an unoptimized piece of the intermediate representation. It was generated by the `clang` compiler, and I just made it a bit more readable. The
code shifts variables around loads them and pops them from the stack, but it could be much simpler. More information on each instruction in
[IR reference](https://llvm.org/docs/LangRef.html).

```llvm
define @add(i32 %a, i32 %b) {
    ; allocate 4 bytes on stack for %c and %d
    %c = alloca i32, align 4

    ; store %a and %b in %c and %d
    store i32 %a, ptr %c, align 4
    store i32 %b, ptr %d, align 4

    ; load %a and %b into %e and %f
    %e = load i32, ptr %3, align 4
    %f = load i32, ptr %4, align 4

    ; add %e and %f, store in %g
    %g = add i32 %e, %f
    ret i32 %g
}
```

So we could write a plugin that would optimize the `add` function into a much simpler and elegant version:

```llvm
define i32 @add(i32 %a, i32 %b) {
  %c = add i32 %a, %b
  ret i32 %c
}
```

This shows that 'optimizations' that are very beneficial for malware development could now be in the reach of developers. The plugins are written in C++ -
a language that majority of malware developers know from inside-out and use very often. One optimization that comes to my mind is automating obfuscation.
Since the dawn of malware, obfuscation was usually done by hand, making the code very hard to read and maintain. However, this is an important part of
malware development, since it allows the software to avoid initial Anti-Virus detection, and can delay the progress of reverse engineers trying to analyze
the executable. Now, with the LLVM plugins, it could be done during the compilation, lifting the burden from the programmer.

## What contributes to the flexibility and modularity of LLVM?

To find out how to use LLVM for malware development purposes, we need to investigate the design of the framework, certain tools and how it all works
in a close-up. I want to take a look at the compilation process on an example of a Rust program, since the language is built on the framework and there
are interesting design choices in the `rustc` compiler.

### Syntax sugar and macros

Because Rust is a modern language, it tries to make low-level development easier for the programmer. It uses a lot of high-level programming concepts
such as anonymous functions, iterators, generics etc. Moreover the language has a big support for macros, which make meta-programming a bit easier for
the developers. Another big feature of the language is the novel approach to memory management. The compiler has a borrow checker - a tool that tracks
the lifetime of each variable to ensure that there will be no memory leakage in the code. Such amount of high-level and complicated concepts requires a
lot of syntax sugar, and hiding the 'guts' of the language away from the programmer.

Let's take a look at a simple program that iterates over an array and prints its contents:

```rust
let arr = vec![1, 2, 3]; // vec! is a macro that creates a vector

for num in arr {
    println!("{}", num); // println! is a macro that prints to stdout
}
```

The macros and the for loop are actually a sugar coating for a more elaborate control flow which is expanded during the compile time.

```rust
// expansion of the vec! macro
let arr = <[_]>::into_vec(#[rustc_box] ::alloc::boxed::Box::new(["1", "2", "3"]));

// for loop is actually a syntax sugar for
// an infinite loop based on iterators
let mut iter = IntoIterator::into_iter(arr);
loop {
    match iter.next() { // match the next iterator
        Some(num) => {
            {
                // expansion of the println! macro
                ::std::io::_print(
                    ::core::fmt::Arguments::new_v1(
                        &["", "\n"],
                        &[::core::fmt::ArgumentV1::new_display(&num)],
                    ),
                );
            };
        },
        None => break, // break if 'empty'
    }
}
```

It's not important to understand what the code does but rather to notice how many statements were expanded by the compiler during the build process. The for loop is an infinite
loop that has a hidden conditional flow, and `vec!` and `println!` macros are handy shortcuts that allow the programmers to delegate some work to the compiler instead of
worrying about the type safety. Macros are not a new concept, but they are used _all of the time_ when writing Rust code.

### Borrow checker and static analysis

The flagship feature of the language is the borrow checker. The borrow checker is embedded in the compiler and it changes the way the developers work with the memory of
the program. Instead of manually allocating and freeing up the memory for variables, the compilers assigns ownership to them. That way, there are no 'dangling pointers' in
which can lead to memory leakage or corruption (usually).

This is a complex process that makes the compiler inject a lot of code into the program, to facilitate memory management. This results in a lot of machine generated code
that makes no sense at first and really inflates even a simple program. Take this implementation of 'FizzBuzz':

```rust
fn main() {
    for i in 0..100 {
        if i % 15 == 0 {
            println!("fizzbuzz");
        } else if i % 3 == 0 {
            println!("fizz");
        } else if i % 5 ==  0 {
            println!("buzz");
        }
    }
}
```

After compiling it with `cargo build --release` and decompiling the resulting binary in IDA, we can see the following graph

| ![Program disassembly](../../assets/img/indepth/disas_main.png) |
| Program disassembly |

The resulting graph is very huge, and seems too big for the amount of instructions we wrote in our program. The reason for that is the aforementioned borrow
checker. While researching how it works, I came to an interesting discovery - the borrow checker does not run _just_ before the code generation

### Compilation process

LLVM is a set of compiler and toolchain technologies that can be used for developing programming languages. The main advantage of using LLVM comes from using it as
a front-end of the programming language. In essence, this means that LLVM performs code analysis and transforms it into an intermediate assembly which can be compiled
by any compiler. This makes the _rustc_ compiler platform agnostic.

Usually, a compilation process consists of these steps:

1. Lexical analysis
2. Parsing
3. Semantic analysis
4. Optimization
5. Code generation

The process is not always linear, but the details are not relevant to this research. The most important part for obfuscation purposes would be the 3rd and the 4th stage.
The lexical analysis creates so called `tokens` which are then processed by the parser to build abstract syntax tree (AST). Then, during parsing, the macros in the AST
are expanded, the code is de-sugared and a High-Level Intermediate representation is produced. This is then semantically analyzed by the compiler to try and make sense
out of what the programmer is trying to do.

After all of this work, the compiler produces a `.ll` file, which contains an abstract assembly language referred to as _Intermediate Representation_ (IR). And this
file is transformed by different plugins in the LLVM toolchain in the optimization stage. That way the compiler can focus on the meaning of the code and then leave
the machine-specific optimizations to the framework.

But how all of this relates to the static analysis?

### Optimization passes

After desugaring and lexing, LLVM produces a `.ll` file, which contains intermediate bitcode referred to as _Intermediate Representation_ (IR). This file can be then
compiled with any LLVM compatible backend. The nature of LLVM allows developers to write passes (optimization plugins) that will process the IR. This can be leveraged by
malware developers to obfuscate the executables. LLVM documentation provides a guide on how to write these passes (and my [publication](/redt/publication)).
Therefore I have decided to create a simple pass that will substitute some arithmetic operations of the IR bitcode.

```cpp
// RandomSeed.cpp

#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
    struct Substitution : public FunctionPass {
        static char ID;
        Substitution() : FunctionPass(ID) {}

        bool runOnFunction(Function &F) override {
            return false;
        }
    };
}

char Substitution::ID = 0;

static RegisterPass<Substitution> X("Substitution", "Instruction substitution");
```

LLVM works with C just as good as with Rust, so the plugin can be applied to both languages. This shows how easy it might be to add an obfuscation step to the
compilation process.

### Conclusions

LLVM can be used for binary obfuscation in a few different ways. One way is to use LLVM's intermediate representation (IR) to transform the program's code in a way
that makes it more difficult to understand. The IR can be used to rename variables and functions, reorder code blocks, or insert additional code that has no effect
on the program's behavior. By using LLVM as a common framework for these techniques, it is possible to create complex and effective binary obfuscation strategies.

And with Rust's native support for LLVM, a team of skilled malware developers can really increase their chances of making their program 'irreversible'

### Something more complex

Because this obfuscation pass is a very small change, the compiler would still optimize the code (unless you have a custom clang build). However, more complex
obfuscation techniques, such as [control flow flattening](http://ac.inf.elte.hu/Vol_030_2009/003.pdf). In essence, this technique breaks down the body of a
program and putting it into a `switch ... case` statement. Then, using a dispatcher variable, the each block decides on the next set of instructions.

## How to develop a plugin for LLVM's optimization pipeline?

## How to use control flow flattening obfuscation technique with LLVM?
