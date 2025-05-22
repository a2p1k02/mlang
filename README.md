# mlang

This is a lisp-like language written on C++ and Boost library.

## How to build 
```bash
sudo pacman -Syu clang boost boost-libs
mkdir build && cd build
cmake ..
make
./mlang
```

## Example
```lispy
Type [q or Q] to quit


>>> + 2 4 6
12
```