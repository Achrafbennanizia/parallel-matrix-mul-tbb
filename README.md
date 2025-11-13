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
