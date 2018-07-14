import serial
import math
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np
ser = serial.Serial('/dev/ttyUSB1',115200,timeout=1)
xlist=[]
ylist=[]
zlist=[]
phi = 0

while phi<=math.pi:

	data = ser.readline()
	print data
	
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
		
		
		
		
		
'''		
print xlist
print 
print ylist
print
print zlist
print
'''
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
plt.xlim((-300,300))
plt.ylim((-300,300))

ax.scatter(xlist,ylist,zlist)
plt.show()
