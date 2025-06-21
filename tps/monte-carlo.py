import numpy as np
import scipy as sp
import scipy.stats as stats
import matplotlib.pyplot as plt

def estimator_naif(n):
    X = np.random.normal(0 ,1, n)
    return np.mean(X >= 6)

def estimator_2(n):
    Y = np.random.normal(6, 1, n)
    return np.mean( (Y >= 6) * np.exp(-3 * Y) * np.exp(18))

alpha = 0.05
p = 10e-9
quantile = stats.norm.ppf(1 - alpha/2)

N = np.arange(1, 500)
values = []
confidence_values = []
for i in N :
    confidence_1 = [p - quantile/np.sqrt(N) , p + quantile / np.sqrt(N)] 
    confidence_values.append(confidence_1)
    estimator = estimator_naif(i)
    estimator_nonnaif = estimator_2(i)
    values.append(estimator_nonnaif)

values = np.array(values)
confidence_1 = np.array(confidence_1)

# plt.plot(N, confidence_1[1, :])
# plt.plot(N, confidence_1[0, :])
plt.plot(N, values)
plt.grid()
plt.show()


