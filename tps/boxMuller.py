import numpy as np
import matplotlib.pyplot as plt
import time
import sys

def box_muller(n: int) -> tuple:
    
    start = time.time()
    U = np.random.uniform(0, 1, n)
    V = np.random.uniform(0, 1, n)

    X = np.sqrt(-2*np.log(U)) * np.cos(2*np.pi*U)
    Y = np.sqrt(-2*np.log(U)) * np.sin(2*np.pi*V)

    end = time.time()
    print(f"Runtime of the box muller function function is: {end-start}")
    return X, Y


X, Y = box_muller(1000)
start = time.time()
normalX = np.random.normal(size=1000)
end = time.time()
print(f"Runtime of the built in numpy function is: {end-start}")

def cauchy(n):
    U = np.random.uniform(0, 1, n)
    return 1 / np.tan(np.pi * U)

def exponential(labda, n):
    assert labda > 0
    U = np.random.uniform(0, 1, n)
    return -1/labda * np.log(1-U)




