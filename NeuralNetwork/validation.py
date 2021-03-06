#!/usr/bin/python

import os, sys
from subprocess import Popen, PIPE

units = [ '-u 8', '-u 16', '-u 32', '-u 64' ]
etas = ['-S 0.04 -L 0.01', '-S 0.02 -L 0.005', '-S 0.01 -L 0.0002']

a = ' -i 6 -o 2 -d ./item/LOC/trainLoc -n ./item/LOC/normvaluesLoc -z 1 -E 1 -v 1 -e 40000 ' 

for u in units:
	for l in etas :
		s = a + u + ' ' + l #+ ' > ./item/learningCurve'
		s = './simulator' + s

		process = Popen(s.split(), stdout=PIPE)
		stdout, stderr = process.communicate()
		stdout.strip()
		sys.stdout.write( stdout + '& ' )
		sys.stdout.flush()
	
	sys.stdout.write( '\\\\\n' )
		
