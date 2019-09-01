import numpy
import pylab

t = numpy.linspace(0, 2.1, 100)

vx = 500
vy = 10
g = 9.81

x = vx * t
y = vy * t - g * t ** 2 / 2

pylab.plot(x, y)
pylab.show()
