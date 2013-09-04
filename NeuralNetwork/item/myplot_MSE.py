#!/usr/bin/env python
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
from matplotlib.lines import Line2D


mylist_Training = []
mylist_Validation = []
#mylist_Test = []

for i in open( "learningCurve", "r" ):
	mylist_Training.append( i.split()[1] )
	mylist_Validation.append(i.split()[2])
	#mylist_Test.append( i.split()[3] )

p1 = plt.plot( mylist_Training, 'r',  linewidth=2.0)
p2 = plt.plot(mylist_Validation, 'b--',  linewidth=2.0)
#p3 = plt.plot(mylist_Test, 'b', linewidth=2.0, )


plt.grid(True)

#plt.figtext(0.21, 0.8, "etal=0.002, etas=0.002,\nalpha=0.2 lambda=0.01, #h.units=60")


#mylist_TrainingP = []
#mylist_ValidationP = []
#mylist_Test = []

#for i in open( "learningCurveMom", "r" ):
	#mylist_TrainingP.append( i.split()[1] )
	#mylist_ValidationP.append(i.split()[2])
	#mylist_Test.append( i.split()[3] )

#p3 = plt.plot( mylist_TrainingP, 'g:',  linewidth=2.0)
#p4 = plt.plot(mylist_ValidationP, 'y-.',  linewidth=2.0)
#p3 = plt.plot(mylist_Test, 'b', linewidth=2.0, )

plt.legend([p1, p2], ["training" , "validation"])


plt.ylabel('Mean Square Error')
plt.xlabel('epoch')
plt.show()
