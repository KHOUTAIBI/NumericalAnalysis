import numpy as np
import matplotlib.pyplot as plt

def euler(f,y_0,step,t_0,T):
    
    t_N = t_0 + T
    number_steps = np.arange(t_0, t_0 + T + step, step)
    y = [y_0]

    for j in range(0,len(number_steps)-1):

        dt = step
        y_n = y[j] + dt * f(number_steps[j],y[j])
        y.append(y_n)

    return number_steps , np.array(y)


# Example of Approximation problem

def f(t,y) :
    return 2 - np.exp(-4 * t) - 2*y

def exact(t):
    return 1 + 1/2 * np.exp(-4 * t) -1/2 * np.exp(-2 * t)

number_steps , y = euler(f=f, y_0=1, step=0.05, t_0=0, T=5)

# Plotting the reuslts and the exact results

plt.grid()
plt.plot(number_steps,y,label='Approximate Solution')
plt.plot(number_steps,exact(number_steps),label='Approximate Solution')
plt.legend()
plt.show()