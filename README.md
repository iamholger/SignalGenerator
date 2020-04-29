# SignalGenerator
Signal generator for non-discrete oscillation problem

# Requirements
AppEval

# Compilation of library
g++ -O3 -fopenmp -shared -fPIC  -march=native -mtune=native  -DNDEBUG  -std=c++17  -g -I/usr/include/eigen3 -I../AppEval/include/AppEval -Iinclude/SignalGenerator -L../AppEval/lib -lAppEval -o lib/libSignalGenerator.so src/SignalGenerator.cxx

