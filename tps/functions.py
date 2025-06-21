import numpy as np
import math

rng = np.random.default_rng()


def sample_metropolis(kernel, size=1, init=0.0):
    ###########################
    X_n = np.zeros(size)
    X_n[0] = init
    U = np.random.uniform(0, 1, size=size)
    acceptance = 0
    for i in range(1, size):
        X = X_n[i-1]
        Y = kernel.rvs() + X
        acceptance_rate = np.exp(-(Y**2 - X**2)/2)
        if U[i] <= acceptance_rate:
            X_n[i] = Y
            acceptance +=1
        else :
            X_n[i] = X
    
    return X_n, acceptance / size
    # YOUR CODE HERE
    ###########################


def sample_metropolis_2d(kernel, density, size=1, init=(0.0, 0.0)):
    ###########################
    # YOUR CODE HERE
    X_n = np.zeros((size,2))
    X_n[0] = init
    U = np.random.uniform(0, 1, size=size)
    acceptance = 0
    for i in range(1, size):
        X = X_n[i-1]
        Y = kernel.rvs() + X
        acceptance_rate = density(Y[0], Y[1]) / density(X[0], X[1]) if density(X[0], X[1]) else np.inf
        if U[i] <= acceptance_rate:
            X_n[i] = Y
            acceptance += 1
        else :
            X_n[i] = X
    return X_n, acceptance / size
    ###########################


def rejection_sampling(proposal, n):
    ############################
    X_n = np.zeros((n,2))
    U = np.random.uniform(0, 1, size=n)
    acceptance_rate = 0
    for i in range(1, n):
        X = X_n[i]
        Y = proposal.rvs()
        accept = pow(np.cos(Y[0]), 2) * pow(np.sin(Y[1]), 2)
        if U[i] <= accept:
            X_n[i] = Y
            acceptance_rate +=1
        else :
            X_n[i] = X  
    
    return X_n, acceptance_rate / n
    ############################
