---
title: Control flow flattening
layout: single
permalink: /redt/publication
---

However, before I will explain how obfuscation process can be streamlined with LLVM. I need to make a detour to talk about an interesting way of making the compiled code more
incomprehensible for the reverse engineers. Control flow flattening breaks up a programs structure into basic blocks - sets of instructions with only one entry and exit point. Then these instructions are taken
from different nesting levels and placed next to each other. Take this basic program as an example:

```c
int i = 0;

while (i < 100) 
{
    important_function();
    i++;
}
```

And this is how it might look like when control flow flattening was applied

```c
int i = 0;
int swFlag = 1; // create a switch flag

while (swFlag != 0) 
{
    switch (swFlag)
    {
        case 1:
            i = 1;

            swFlag = 2;
            break;
        case 2:
            if (i <= 100)
                swFlag = 3;
            else
                swFlag = 0;

            break;
        case 3:
            important_function();
            i++;

            swVar = 2;
            break;
    }
}
```

These two pieces of code accomplish the same task! They are however much more different in how they perform it. Therefore the program's structure is going to differ.

// TODO: CHANGE PIC

| ![Control flow flattening](../../assets/img/indepth/control_flow_graph.png) |
| Control flow flattening |

[This paper](https://www.inf.u-szeged.hu/~akiss/pub/fulltext/laszlo2007obfuscating.pdf) explains control flow flattenning in depth, dealing with  more complex concepts like the
`try ... catch` and `switch` clauses, as well as proposes an algorithm which  could obfuscate  the binary during the compile time. Since this is a task which can be performed 
during the compile time, the algorithm needs to be implemented in a compiler. This means that control flow flattening can be well applied to LLVM as a plugin.

### Obfuscating LLVM

After lexing and desugaring the code, the compiler enters the next stage - semantic analysis. This is one of the Rust’s biggest strengths. The code is validated and the borrow 
checker tracks lifetime of each variable to catch any possible memory leaks. Then the compiler enters the optimisation and code generation stages. Because LLVM is language
agnostic, it requires the compiler to translate the code into an intermediate representation (IR). This IR is going to be processed by the LLVM, optimised and compiled on
the selected platform. And the IR is where the obfuscation takes place.

`obfuscation/src/main.rs`

```rust
fn main() {
    let arr = vec!["1", "2", "3"];

    for num in arr {
        println!("{}", num);
    }
}
```

Compiling the program with `cargo build --release` and running the program is going to give us the following output.

```
$ cargo run --quiet
1
2
3
```

And the binary from the release build can be found at `obfuscation/target/release/`.

| ![Disassembled binary](../../assets/img/indepth/disas_1.png) |
| Disassembled binary |

The graph and generated code is very straightforward. Even though the macros expanded to much more code, IR was optimised by LLVM and created a neat executable with very simple 
code flow.

[LLVM obfuscator]() is a plugin that can be used by `cargo`, the Rust compiler to obfuscate the code flow of the program in the compilation. That way, it is much easier to create
a unique binary every time it is compiled. Moreover, it makes static analysis much harder since some of the functions are there just to waste time of the researchers.

_TODO: Add pictures of building and disassembly_

To use the plugin I had to build LLVM and the plugin itself, and then create a custom Rust toolchain with the toolchain manager `rustc`. However, as depicted on the picture below
the effort paid off and a very crude and simple program became something much more complex.

| ![Obfuscated program](../../assets/img/indepth/disas_2.png) |
| Obfuscated program |
