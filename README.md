# Runge-Kutta and Euler Method Implementations

## Overview
This repository contains implementations of numerical methods for solving ordinary differential equations (ODEs) using the **Euler method** and **Runge-Kutta methods** (RK2 and RK4) in both Python and C++.

## Features
- **Euler Method**: A simple first-order numerical approach for solving ODEs.
- **Runge-Kutta Methods**: Higher-order methods (RK2 and RK4) for improved accuracy.
- **Comparative Analysis**: Evaluates the accuracy of different methods.
- **Multi-Language Support**: Implementations in Python and C++.

## Usage

### Running the Python Implementation
```sh
python euler.py
python rungekutta.py
```

### Compiling and Running the C++ Implementation
```sh
g++ rungekutta.cpp -o runge_kutta_euler
./runge_kutta_euler
g++ euler.cpp -o euler
./euler
```

## File Structure
```
runge-kutta-euler/
│── python/
│   ├── euler.py
│   ├── rungekutta.py
│   ├── climate.py
    ├── carbon.py
│
│── cpp/
│   ├── euler.cpp
│   ├── rungekutta.cpp
│   ├── euler.h
    ├── rungekutta.h
│
│── README.md
```


