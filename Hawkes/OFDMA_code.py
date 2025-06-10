import numpy as np
from math import *
import matplotlib.pyplot as plt

C = 200 # kb / s
W = 250 # kHz
K = 10**6
gamma = 2.8
R = 300 # m
lambda_ = 0.01 # m-2
SNR_min = 0.1
p = 0.01
S_min = 30
S_max = 100

# Compute N_max
N_max = ceil(C / (W * log2(1 + SNR_min)))

print("Maximum number of slots per user: N_max =", N_max)

# Function performing a simple bisection search to find K
def compute_K(mu):
    A = -log(10**(-4)) / mu
    def f(x):
        z = (x / mu) # Change the variable
        return z * (log(z) - 1) - A + 1

    a = 1
    b = int(100 * mu) # b / mu is most probably greater than K
    while(b-a > 1):
        m = (a + b) // 2
        if(f(m) >= 0):
            b = m
        else:
            a = m
    return b

def compute_mus():
    mus = []
    r = 0
    for k in range(1, N_max):
        new_r = (K / (2**(C / (W * k)) - 1))**(1 / gamma)
        mus.append(p * lambda_* pi * (new_r**2 - r**2))
        r = new_r

    max_r = (SNR_min / K)**(-1 / gamma)
    mus.append(p * lambda_* pi * (max_r**2 - r**2))
    return mus

mus = compute_mus()
K_counts = [compute_K(mu) for mu in mus]
K_count = max(K_counts)

print("Mus: " , mus)
print("K_count : ", K_counts)

distributions = [np.array([mu**k / factorial(k) * exp(-mu) for k in range(K_count+1)]) for mu in mus]
k_distributions = [np.zeros(N_max * (K_count+1)) for i in range(N_max)]

print("Residues : ", [1 - distributions[k][:K_counts[k]+1].sum() for k in range(N_max)])

for k in range(N_max):
    k_distributions[k][::k+1][:len(distributions[k])] = distributions[k]

conv = k_distributions[0]
for i in range(1, N_max):
    conv = np.convolve(conv, k_distributions[i], mode="full")

def get_S():
    for S in range(len(conv)):
        if conv[S:].sum() < 0.01: 
            return S

print("S : ", get_S())

