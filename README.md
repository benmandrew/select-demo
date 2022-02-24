# Unix select demo

Demonstration of the `select` Unix call for implementing event-driven programming in C.

Supports the article `[Using the select System Call in Unix](https://www.benmandrew.com/articles/unix-select-syscall)'.

## Building

```
cmake .
make
```

## Usage

Open two terminals:

```
# In one:
./bin/send
# In the other:
./bin/receive
```
