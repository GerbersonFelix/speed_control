#!/usr/bin/env python
import rospy
from std_msgs.msg import String
from nav_msgs.msg import Odometry
import numpy # carrega a biblioteca numpy
import matplotlib.pyplot as plt #carrega a biblioteca matplotlib
import matplotlib.gridspec as gridspec #carrega a biblioteca gridspec
from drawnow import * #carrega a biblioteca drawnow
from array import array #carrega a biblioteca array
import time

def plot_odom(msg):

    global temp
    global vel
    x = []
    y = []

    #twist = Twist()
    plt.ion()
    plt.show()
    temp = msg.header.stamp.to_sec()
    vel = msg.twist.twist.angular.z
    #self.odom.pose.pose.position.x
    print ("in plot_odom")
    print (temp)
    print (vel)
    x.append(temp)
    y.append(vel)
    print (x)
    print (y)
    
    #print "x ", x
    #print "y ", y
    #raw_input("continue")

    plt.plot(x,y)
    plt.ylabel("odom")
    plt.draw()
    time.sleep(0.05)

def listener():
    rospy.init_node('listener', anonymous=True)
    rospy.Subscriber("odom", Odometry, plot_odom)
    rospy.spin()
    #plt.show(block=True)

if __name__ == '__main__':
    listener()
