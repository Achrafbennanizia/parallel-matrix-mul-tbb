# Parallel Matrix Multiplication (C++ & Intel TBB)

Kleine Demo für parallele Matrixmultiplikation mit Intel oneTBB.

Ziel:

- Unterschied zwischen sequentieller und paralleler Berechnung zeigen
- Grundlagen von Parallelisierung mit `tbb::parallel_for` demonstrieren
- Laufzeiten vergleichen

## Features

- Generierung zufälliger Matrizen (double-Werte)
- Sequentielle Matrixmultiplikation
- Parallele Matrixmultiplikation mit Intel TBB (`tbb::parallel_for`, `tbb::blocked_range2d`)
- Vergleich der Laufzeiten und Ergebnisprüfung (max. Fehlernorm)

## Tech Stack

- C++20
- [oneTBB / Intel TBB](https://www.intel.com/content/www/us/en/developer/tools/oneapi/onetbb.html)
- CMake (optional, aber empfohlen)

## Build (mit CMake)

```bash
git clone https://github.com/<DEIN-USERNAME>/parallel-matrix-mul-tbb.git
cd parallel-matrix-mul-tbb
mkdir build && cd build
cmake ..
cmake --build .

```

## Build (mit Ninja)

1. Ninja installieren (macOS)
```bash
brew install ninja
ninja --version
```

2. Projekt mit Ninja konfigurieren
```bash
git clone https://github.com/<DEIN-USERNAME>/parallel-matrix-mul-tbb.git
cd parallel-matrix-mul-tbb
mkdir build && cd build
cmake .. -G Ninja
ninja
ninja matrix_mul
```
Starten:
```bash
./matrix_mul
```

## Beispielausgabe
```bash
Matrixgrößen: A = 800 x 800, B = 800 x 800
Sequentiell:  0.742 s
Parallel:     0.219 s
Max. Fehler   = 2.27e-13
Speedup:      3.39x
```
