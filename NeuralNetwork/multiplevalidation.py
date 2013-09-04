# !/usr/bin/python

import os, sys

units = [ '5', '10', '50', '80', '120' ]
wd = ['0.0005', '0.001', '0.005', '0.01', '0.05']


a = './simulator -i 6 -o 2 -d ./item/LOC/trainLoc -n ./item/LOC/normvaluesLoc -z 1 -E 1 -v 1 ' 

for u in units:
	for l in wd:
		s = a + '-l ' + l + ' -u ' + u +  ' > ./item/learningCurve'
		b = os.popen(s,'r',1)
		print b
		
