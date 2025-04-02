import numpy as np
import matplotlib.pyplot as plt
import time

def geometric_rv(lambda_):
    assert 0 < lambda_ < 1
    start = time.time()
    
    U = np.random.uniform(0, 1)
    n = int(np.log(U) / np.log(1 - lambda_))   
    
    end = time.time()
    print(f"Runtime of the function is: {end - start}")
    return n, end - start

def accept_reject(f, g, lambda_):
    N = 1
    m = 1
    while True:
        U = np.random.uniform(0, 1)
        Y, _= geometric_rv(lambda_)
        if U <= (f(Y)/m*g(Y)):
            return N
        N += 1

def factorial(n):
    if n == 0 or n == 1:
        return 1
    return n*factorial(n-1)

lambda_ = 0.1
f = lambda n: np.exp(-lambda_) * pow(lambda_, n) / factorial(n)
g = lambda n : (1-lambda_) * pow(lambda_, n)
n, _ = geometric_rv(0.1)
N = accept_reject(f, g, lambda_)
print(np.sqrt(
    2 / np.pi
) * np.exp(-1/2))
# print(n)