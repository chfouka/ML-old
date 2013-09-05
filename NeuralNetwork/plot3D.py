#!/usr/bin/python

from mpl_toolkits.mplot3d import axes3d
import matplotlib.pyplot as plt
import numpy as np
import random

X = []
Y = []
Z = []

fig = plt.figure()
ax = fig.gca(projection='3d')
for i in open( "plot3Ddata" ):
	print( i.strip() )
	x, y, z = i.split()
	X.append( float(x) )
	Y.append( float(y) )
	Z.append( float(z) )

ax.scatter(X, Y, Z)

plt.show()

