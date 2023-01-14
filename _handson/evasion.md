---
layout: single
title: Defense evasion
---

Defense evasion is very important for malware developers, since they want to keep their viruses under
the antivirus' (abbreviated to AV) radar as long as possible, so that they can move laterally without
being noticed. Apart from the AV evasion, malware developers might want to hinder reverse engineering
by obfuscating the compiled files. There are a lot of techniques available, but I focused on control
flow obfuscation and PowerShell script obfuscation.

## Obfuscating control flow

A control flow is a way how program executes. When decompiling an executable file in a disassembler like
IDA, we can see blocks that are connected by arrows. The way how program jumps from one block to another
creates the control flow.

| ![Control flow in IDA](../../assets/img/evasion/controlflow.png) |
| Control flow in IDA |

The control flow is made up from the aforementioned **basic blocks**. These are just sets of instructions
that end with some kind of terminator instruction, be it a `ret` or `jmp` instruction in x86 assembly.
Look at the code below, that created the disassembled program:

```c
int main() {
    int a = 5;

    if (a == 5) {
        return 0;
    } else {
        return 1;
    }
}
```

This code consists of four basic blocks: the entry block, one for each of the `if...else` clause and one
for the return statement.

Now while this might be quite obvious for a reverse engineer to analyze, the binary could be obfuscated
during the compilation of the program. A technique called control flow flattening can be applied to
executables during compilation so that the above code would be compiled as something similar to the
following example:

```c
int main() {
    int a = 5;
    int dispatcher;

    while (true) {
        switch (dispatcher) {
            case 0: {
                if (a == 5)
                    dispatcher = 1
                else 
                    dispatcher = 2
            }
            case 1: {
                return 0;
            }
            case 2: {
                return 1;
            }
        }
    }
}
```

The above example might take a second to understand at first, even in plain code, so it will be definitely
harder for the static analyst to decipher what is going on in the decompiled executable.
[This research paper](https://ac.inf.elte.hu/Vol_030_2009/003.pdf) on obfuscating the control flow explains
the algorithm in detail, so I will just summarize it into the following steps:

1. Create a `dispatcher` variable
2. Create a `while` loop with condition `dispatcher < num_blocks`
3. Add a `switch...case` on `dispatcher` and put each basic block into a case
4. Change the `dispatcher` after every iteration

I have explained the implementation of such algorithm in the LLVM's compiler infrastructure in detail in my
[In-depth research](https://malpa222.github.io/portfolio/redt/in-depth), so I wont delve deep into details.
After running the obfuscation algorithm on the binary file, this is the outcome:

| ![Obfuscated binary](../../assets/img/evasion/hello_obfuscated.png) |
| Obfuscated binary |

As you can see, the control flow has become much more complex and harder to understand, even with such a simple
program.

## PowerShell script Obfuscation

While the previous technique works for compiled languages, I chose to take a look at an interpreted language,
such as PowerShell. It is a common choice for malware developers to use PowerShell scripts as downloaders
that will deliver their payload to the infected system. For example the
[Bumblebee dropper](https://malpa222.github.io/portfolio/redt/in-depth#malware-loaders---bumblebee) was an obfuscated
PowerShell script that downloaded the payload to the victims PC.

There is an automated tool that allows us to obfuscate our script in many different ways called
[Invoke-Obfuscation](https://github.com/danielbohannon/Invoke-Obfuscation). I found a script that opens a reverse shell
and connects to a listener.

| ![Invoke-Obfuscation](../../assets/img/evasion/invoke-obfuscation.png) |
| Invoke-Obfuscation |

I downloaded a reverse shell script from [Payload all the things](https://github.com/swisskyrepo/PayloadsAllTheThings/blob/master/Methodology%20and%20Resources/Reverse%20Shell%20Cheatsheet.md#powershell).
Then, in the obfuscator, I have ran the Encoding obfuscation on the script, which encrypted the string with AES cipher

| ![AES Encoding](../../assets/img/evasion/encoding.png) |
| AES Encoding |

The code looked really well obfuscated, so I decided to give it a go. I turned off the Windows Defender cloud protection and
sample submissions so that I will have higher chances of running the script. I set up a listener on my host machine and ran the
script.

| ![Blocked](../../assets/img/evasion/blocked.png) |
| Blocked |

However, the script was blocked by the antivirus. It turns out that the encrypted string was deciphered by the AV software, which
prevented the execution. Therefore, I have decided to try out the AST nodes obfuscation option. It produced a script which you can
see [here](https://github.com/malpa222/portfolio/blob/master/assets/code/obf_shell.ps1). After running it on the Windows VM, I saw
this:

| ![Successful execution](../../assets/img/evasion/works_win.png) |
| Successful execution |

| ![Reverse shell](../../assets/img/evasion/blocked.png) |
| Reverse shell |

As you can see, the AST node obfuscation is the most succesfull technique that allows to avoid Windows Defender when executing
PowerShell scripts.
