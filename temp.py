from python.euler import *
import numpy as np
import matplotlib.pyplot as plt


def f(y, t):
    
    a = 0
    phi = 0

    if 0 <= t < 1 or 2.7 <= t < 3.4:  
        a = 1
    elif 1 <= t < 2.7:
        a = -1


    if 0 <= t < 1:
        phi = 1
    elif 1 <= t < 2:
        phi = -1

    return np.array(
        [
            y[2] * np.cos(y[3]),
            y[2] * np.sin(y[3]),
            a,
            phi
        ]
    )

number_steps, sol = euler_higher_diemension(
    f, np.array([
        0, 0, 0, 0
    ]),
    0.1,
    0,
    10
)

plt.plot(
    sol[:, 1], sol[:, 0] 
)
plt.show()