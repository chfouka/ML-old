#!/usr/bin/python2.7

import os, sys
from subprocess import Popen, PIPE

units = [8, 16, 24, 32, 40, 48, 56, 64, 72, 80, 88, 96, 104, 112, 120, 128]
eta = 0.1

a = ' -i 6 -o 2 -d ./item/LOC/trainLoc -n ./item/LOC/normvaluesLoc -z 1 -E 1 -v 1 ' 




for u in units:
	#sys.stdout.write( str(u) + " " )	
	
	S = eta
	for i in range(10):
		S /= 1.2
		L = S / 8.0
		opts = a + '-u ' + str(u) + ' ' + '-L ' + str(L) + ' -S ' + str(S) #+ ' > ./item/learningCurve'
		cmd = './simulator' + opts
		#print( cmd )

		process = Popen(cmd.split(), stdout=PIPE)
		stdout, stderr = process.communicate()
		stdout.strip()
		sys.stdout.write( str(u) + " " + str(S) + " " + stdout )
		sys.stdout.flush()
	
		sys.stdout.write( '\n' )
		
