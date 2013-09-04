#!/usr/bin/python2.7

import os, sys
from subprocess import Popen, PIPE

units = [8, 16, 24, 32, 40, 48, 56, 64, 72, 80, 88, 96, 104, 112, 120, 128]
eta = 0.1

a = ' -i 6 -o 2 -d ./item/LOC/trainLoc -n ./item/LOC/normvaluesLoc -z 1 -E 1 -v 1 ' 


for u in units:
	#sys.stdout.write( str(u) + " " )	
	
    S = eta
    for i in range(5):
        S /= 1.2
        L = S / 8.0
        opts1 = a + '-u ' + str(u) + ' ' + '-L ' + str(L) + ' -S ' + str(S)
        cmd1 = './simulator' + opts1
        sys.stdout.write( str(u) + " " + str(S) + " " )

        S /= 1.2
        L = S / 8.0
        opts2 = a + '-u ' + str(u) + ' ' + '-L ' + str(L) + ' -S ' + str(S)
        cmd2 = './simulator' + opts2

#        print( cmd1 )
#        print( cmd2 )

        process1 = Popen(cmd1.split(), stdout=PIPE)
        process2 = Popen(cmd2.split(), stdout=PIPE)
        stdout1, stderr1 = process1.communicate()
        stdout2, stderr2 = process2.communicate()


        stdout1.strip()
        sys.stdout.write( stdout1 )
        sys.stdout.flush()
        sys.stdout.write( '\n' )

        stdout2.strip()
        sys.stdout.write( str(u) + " " + str(S) + " " + stdout2 )
        sys.stdout.flush()
        sys.stdout.write( '\n' )
		
