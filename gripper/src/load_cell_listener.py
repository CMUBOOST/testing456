#!/usr/bin/env python
import rospy
from std_msgs.msg import Int16
import matplotlib.pyplot as plt
import math

global count

def callback(data):
    #rospy.loginfo(rospy.get_caller_id() + "I heard %s", data.data)
    #print data.data
    #return data.data
    #boardPtTime = data.header.stamp.to_sec()
    #boardPt.setX(data.point.x)
    global count
    count += 1
    #print count
    if count%50 == 1:
    #plt.figure(1)
        plt.figure(1)
        plt.ion()
        plt.show()
        plt.scatter(count, data.data, 'r')
        plt.xlabel('Time')
        plt.ylabel('Load (mV)')
        plt.draw()    

def listener():

    # In ROS, nodes are uniquely named. If two nodes with the same
    # node are launched, the previous one is kicked off. The
    # anonymous=True flag means that rospy will choose a unique
    # name for our 'listener' node so that multiple listeners can
    # run simultaneously.
    rospy.init_node('listener', anonymous=True)
  
    rospy.Subscriber("chatter", Int16, callback)
    #print "data_test is:"
    #print data_test
    
    
def plotData(count, data):
	count += 1
	plt.figure(1)
	plt.plot(count, data.data, label='Actual Board Point X')
	plt.xlabel('Time')
	plt.ylabel('Angle (radians)')

def createFigure():
	plt.figure(1)
	plt.ion()
	plt.show()

if __name__ == '__main__':
	data = listener()
	global count
	count = 0
	#while not rospy.is_shutdown():
	#	createFigure()
	#	plotData(count, data)
	# spin() simply keeps python from exiting until this node is stopped
	rospy.spin()


