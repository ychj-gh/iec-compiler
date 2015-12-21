# iec-compiler

---
A compiler for IEC61131-3 language

## Features

---
1. Support recognition of POUs' declaration part & definition part
2. Support recognition of IL tokens

## Building Environment

---
1. OS: Ubuntu 14.04 x86_64
2. CMake 2.8.12.2
3. GCC 4.8.4 (-std=c++11)
4. flex 2.5.35
5. bison 3.0.2

## Building Steps

---
1. Change directory to the root directory of project
2. `$ mkdir build` and `$ cd build`
3. `$ cmake ..`
4. `$ make`
5. `$ ../iec_compiler.exe < ../test/test4lexer`

## Release Notes

---

## Thanks

---
Thanks to [Beremiz](http://www.beremiz.org/index.html.en)
