import numpy
import pylab

t = numpy.linspace(0, 2.2, 100)

v0x = 500
v0y = 10
g = 9.81

x0 = 0
y0 = 1.5

x = x0 + v0x * t
y = y0 + v0y * t - g * t ** 2 / 2

pylab.plot(x, y)
pylab.show()
