# unrandom

Provides determinism via a LD\_PRELOAD hook, replacing the getrandom(2) syscall with a Mersenne twister.

This was made to produce deterministic UUIDs in gtirb/ddisasm.
Here, the UUIDs are 128-bits and commonly base64 encoded.
For visibility, we tweak the first 6 bits of these
random generations so the first base64 character is fixed.

## usage
To build the .so file for LD\_PRELOAD,
```bash
make
```
To build and run the test binary,
```bash-session
$ make do-test
cc    -c -o test.o test.c
cc   test.o   -o test
g++ -fPIC -ldl   -c -o unrandom.o unrandom.cpp
g++ -fPIC -ldl unrandom.o -shared -o libunrandom.so
LD_PRELOAD=$(pwd)/libunrandom.so ./test
x == y : ok
8621d6cc92f81cce 902ccb701fd13acc
x1 == 0x8621d6cc92f81cce : ok
x2 == 0x902ccb701fd13acc : ok
uuid[0] >> 2 == 0b110011 : ok
uuid[0] >> 2 == 0b110011 : ok
uuid[0] >> 2 == 0b110011 : ok
uuid[0] >> 2 == 0b110011 : ok
uuid[0] >> 2 == 0b110011 : ok
```

## credit

Based on [whitequark/unrandom][].

[whitequark/unrandom]: https://github.com/whitequark/unrandom
