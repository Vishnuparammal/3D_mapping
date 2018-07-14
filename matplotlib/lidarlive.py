import serial
import math
import time
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np
plt.ion() #
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ser = serial.Serial('/dev/ttyUSB0',115200,timeout=1)
xlist=[]
ylist=[]
zlist=[]
j=0
while True:
	
	data = ser.readline()
	print data
	if data is '##########':
		break
	if len(data) is 11:
		theta = ""
		phi = ""
		dist = ""
		for i in range(3):
			theta+=data[i]
		for i in range(3,6):
			phi+=data[i]
		for i in range(6,10):
			dist+=data[i]
		
		theta=int(theta)*math.pi/180
		phi=int(phi)*math.pi/180
		dist=int(dist)
		
		
		x = dist*math.sin(phi)*math.cos(theta)
		y = dist*math.sin(phi)*math.sin(theta)
		z = dist*math.cos(phi)
		
		xlist.append(x)
		ylist.append(y)
		zlist.append(z)
		
		ax.scatter(xlist[j],ylist[j],zlist[j])
		j+=1
		plt.show()
		plt.pause(0.0001)
		
		
		
'''		
print xlist
print 
print ylist
print
print zlist
print
'''



