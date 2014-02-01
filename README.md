libcr
=====

simple coroutine C library for *nix.

#How to build
```bash
make
```

makes a shared library named "cr.so".

example.c is a example for use this library.  
To build this example,

```bash
make example
```

And You can exec by entering the command below. 

```bash
LD_LIBRARY_PATH=. ./example
```
