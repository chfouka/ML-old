#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import csv

dataset = csv.reader(open(sys.argv[1]), delimiter=' ')

out_file = open(sys.argv[2], "w")

for row in dataset:
	line = row[1] + ' ' + row[2] + ' ' + row[3] + ' ' + row[4] + ' ' + row[5] + ' ' + row[6] +  ' ' + row[7] + ' ' + row[8] + ' ' + row[9] + ' ' + row[10] + ' ' + row[11] + ' ' + row[12] + ' ' + row[13] + ' ' + row[14] + ' ' + row[15] + ' ' + row[16] + ' ' + row[17] + ' ' + row[0] +  '\n'	
	out_file.write(line)

out_file.close()

