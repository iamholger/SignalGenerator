# SignalGenerator
Signal generator for non-discrete oscillation problem

# Requirements
AppEval

# Compilation of library
g++ -O3 -fopenmp -shared -fPIC  -march=native -mtune=native  -DNDEBUG  -std=c++17  -g -IEigen3.3.7 -IAppEval -Iinclude/SignalGenerator -lAppEval -o libSignalGenerator.so src/SignalGenerator.cxx
