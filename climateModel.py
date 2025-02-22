from rungekutta import *
from euler import *
from carbone import *

fig, ax = plt.subplots()

twin1 = ax.twinx()
twin2 = ax.twinx()
twin3 = ax.twinx()
twin4 = ax.twinx()

# TO CHANGE

twin2.spines["right"].set_position(("outward", 40))
twin3.spines["right"].set_position(("outward", 60))
twin4.spines["right"].set_position(("outward", 80))

number_steps, y = runge_kutta_higher_dimension(f=derivative, y_0=x0, step=0.1, t_0=1850.0, T=750)


p0, = ax.plot(number_steps, y[:, 0], color="blue", label="Atmosphere")
p1, = twin1.plot(number_steps, y[:, 2], color="pink", label="DeepOcean")
p2, = twin2.plot(number_steps, y[:, 3], color="red", label="FossilFuelCarbon")
p3, = twin3.plot(number_steps, y[:, 4], color="green", label="Plants")
p4, = twin4.plot(number_steps, y[:, 5], color="orange", label="Soils")

ax.set_xlabel("Time")
ax.set_ylabel("Atmosphere", color="blue")
twin1.set_ylabel("DeepOcean", color="pink")
twin2.set_ylabel("FossilFuelCarbon", color="red")
twin3.set_ylabel("Plants", color="green")
twin4.set_ylabel("Soils", color="orange")

lines = [p0, p1, p2, p3, p4]
ax.legend(lines, [l.get_label() for l in lines], loc="best")


# plot and move left
plt.subplots_adjust(left=0.05)
plt.show()
