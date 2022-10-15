---
title: In-depth research
layout: single
permalink: /lo1/in-depth
---

This document is a follow-up on the trends research, precisely on the topic of cross-platform malware. Since virtually everybody in the western world owns a smartphone
or a personal computer, the amount of different platforms that are running on our hardware is bigger than it ever was. This forces malware developers to spend much more
time on creating malware for each of these systems.

Nowadays, with the rise of new systems programming languages such as Rust or Go, developing malicious software for different platforms has become more accessible
and much quicker than it ever was.

## Research questions

Because portable software is a broad subject, I have decided to only focus on some key parts of the domain. My research will try to answer the following question,
along with the sub-questions:

**Is Rust a good choice for creating a cross-platform malware?**

- Does Rust have native support on Windows/Linux?
- How long does it takes to develop a malware in Rust?
- How does Rust handle binary portability/cross-platform compiling?

I will try to answer the main research question by working on each of the sub-questions and producing a multiplatform keylogger written in Rust.

### Research strategies

In order to answer the sub-questions and produce the conclusion of the research I will combine different research strategies. This approach is going to allow me
to structurize my work and validate the quality of my research.

- Does Rust have native support on Windows/Linux? 

    In order to answer this question I need to look into the history of the language, supported platforms and current frameworks (if any). Moreover, I need to develop software
    which works close with the system internals to be able to produce a meaningful answer. To research supported platforms I will use the Library strategy. With the Library
    research results I am going to continue to the Lab strategy to test if the Library research was indeed correct.

- How long does it takes to develop a malware in Rust?

    This research questions will require the combination of Library, Workshop and Lab strategies. I will use Library to find how to develop malware on Linux and Windows.
    Then, I am going to use that knowledge in the Workshop, to develop the software and validate it in the Lab. The results from the Workshop are going to have the biggest
    impact on the answer of this research question.

- How does Rust handle binary portability/cross-platform compiling?
    
    After having developed the malware, I need to prepare it to work on both Windows and Linux systems. This will require combining knowledge gained from previous research
    and some additional Library activities which might lead me to new frameworks or techniques for cross-compiling. I am going to test the results in the Lab research strategy.

Having researched all the sub-questions I would be ready to produce the answer to the final question. To do that, I need to use the product of the research in the Lab
to see if and how does it work and then present it to my peers in the Workshop strategy.

## Does Rust have native support on Windows/Linux?

Since Rust was created with portability in mind, one would expect the language to be have good support for interacting with the kernel/api of the OS. And indeed,
this is the case with the language. Development with Rust is great on both Linux and Windows, but it requires a slightly different approach on each of the platforms.

### Linux

Unix-like systems follow the well known philosophy: 'Everything is a file'. Essentially, this means that almost all system internals are exposed as a stream of bytes
accessible through the OS' filesystem. Since GNU/Linux was written mainly in C, the files representing system internals are usually C structures.

For example, the file which exposes keystroke events at `/dev/input/eventX` is in fact a stream of bytes which make up the the `input_event` struct. This is the original,
C version of the struct:

```c
struct input_event {
    struct timeval time;
    unsigned short type;
    unsigned short code;
    unsigned int value;
};
```

If a programming language would want to work with an input event, it would need to cast the bytes making up the struct into it's own binding of the C library. In Rust,
the official `libc` implementation defines this version of `input_event` struct:

```rust
pub struct input_event {
    pub time: ::timeval,
    pub type_: ::__u16,
    pub code: ::__u16,
    pub value: ::__s32,
}
```

As depicted, the Rust's version takes the same amount of memory as the C struct - 24 bytes on my computer. So in order to be able to use the `input_event` struct
in Rust, it needs to be transmuted from an _unsafe_ byte array to a _managed_ one, like that:

```rust
use libc::input_event;

// Get the size of the Rust's input_event struct
const EV_SIZE: usize = mem::size_of::<input_event>();
let mut buf: [u8; EV_SIZE] = unsafe { mem::zeroed() };

// Cast the C struct to empty array
let ev = unsafe { mem::transmute::<[u8; EV_SIZE], input_event>(buf) };
```

This approach requires a bit more knowledge from the programmer, but if somebody is going down into system internals they need to understand it in-depth. Moreover,
in case of some custom or not-yet-implemented C data types, the programmer has freedom to create their own bindings for the said structures.

### Windows

## How long does it takes to develop a Linux/Windows keylogger in Rust?

## How does Rust handle binary portability/cross-platform compiling?
