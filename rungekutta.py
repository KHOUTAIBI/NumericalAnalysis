import numpy as np
import matplotlib.pyplot as plt


def classic_runge_kutta(f, y_0, step, t_0, T):
    """ Implementation of the classical Runge-Kutta Method"""
    """ In this case, q = 4"""

    number_steps = np.arange(t_0, t_0 + T + step, step)
    y = [y_0]
    dt = step

    for j in range(len(number_steps) - 1):

        p_n_1 = f(number_steps[j],y[j])
        t_n_2 = number_steps[j] + 1/2 * dt
        y_n_2 = y[j] + 1/2 * dt * p_n_1
        p_n_2 = f(t_n_2, y_n_2)

        t_n_3 = t_n_2
        y_n_3 = y[j] + 1/2 * dt * p_n_2
        p_n_3 = f(t_n_3,y_n_3)

        t_n_4 = number_steps[j] + dt
        y_n_4 = y[j] + dt * p_n_3
        p_n_4 = f(t_n_4, y_n_4)
        
        y.append(y[j] + dt * (1/6 * p_n_1 + 2/6 * p_n_2 + 2/6 * p_n_3 + 1/6 * p_n_4))

    return  number_steps, y

def runge_kutta_higher_dimension(f, y_0, step, t_0, T):
    """Implementing the runga Kutta Method MatrixWise"""
    
    number_steps = np.arange(t_0, t_0 + T + step, step)
    y = np.array([y_0])
    dt = step

    for j in range(len(number_steps) - 1):

        p_n_1 = f(y[j,:],number_steps[j])
        t_n_2 = number_steps[j] + 1/2 * dt
        y_n_2 = y[j,:] + 1/2 * dt * p_n_1
        p_n_2 = f(y_n_2,t_n_2)

        t_n_3 = t_n_2
        y_n_3 = y[j,:] + 1/2 * dt * p_n_2
        p_n_3 = f(y_n_3,t_n_3)

        t_n_4 = number_steps[j] + dt
        y_n_4 = y[j,:] + dt * p_n_3
        p_n_4 = f(y_n_4,t_n_4)
        
        y = np.append(y, [y[j,:] + dt * (1/6 * p_n_1 + 2/6 * p_n_2 + 2/6 * p_n_3 + 1/6 * p_n_4)], axis=0)

    return  number_steps, y


test_runga = False

if test_runga:
    def f(t,y) :  
        return 2 - np.exp(-4 * t) - 2*y

    def exact_function(t):  
        return 1 + 1/2 * np.exp(-4 * t) -1/2 * np.exp(-2 * t)
    
    number_steps , y = classic_runge_kutta(f=f, y_0=1, step=0.1, t_0=0, T=5)
    # Plotting the reuslts and the exact results

    plt.grid()
    plt.plot(number_steps,y,label='Approximate Solution')
    plt.plot(number_steps,exact_function(number_steps),label='exact',color='pink')
    plt.legend()
    plt.show()

