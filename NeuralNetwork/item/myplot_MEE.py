#!/usr/bin/env python
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt

mylist_Training = []
mylist_Validation = []

for i in open( "learningCurveMEE", "r" ):
	mylist_Training.append( i.split()[1] )
#	mylist_Validation.append(i.split()[2])
	

plt.plot( mylist_Training )
#plt.plot(mylist_Validation)
plt.ylabel('Mean Euclidean Error')
plt.xlabel('epoch')
plt.figtext(0.3, 0.8, "ETA_L=0.004, ETA_S=0.01,\nALPHA=1.0, MOM=0.8, #h.units=60")
plt.show()
