#!/usr/bin/python

import os, sys
from subprocess import Popen, PIPE

units = [ '-u 8', '-u 16', '-u 32', '-u 64' ]
etas = ['-S 0.004 -L 0.001', '-S 0.02 -L 0.005', '-S 0.01 -L 0.0002']


a = '. -i 6 -o 2 -d ./item/LOC/trainLoc -n ./item/LOC/normvaluesLoc -z 1 -E 1 -v 1 ' 

for u in units:
	for l in etas :
		s = a + u + ' ' + l #+ ' > ./item/learningCurve'
		print './simulator' + s
		options = s.split()
		
		
		process = Popen(['./simulator', options], stdout=PIPE)
		stdout, stderr = process.communicate()
		sys.stdout.write( stderr + ' ')

	sys.stdout.write( '\n' )
		
