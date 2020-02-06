#!/usr/bin/env python
# -*- coding: cp1252 -*-

import rospy
from std_msgs.msg import Float32

pub = rospy.Publisher('ki_set', Float32, queue_size=10)
rospy.init_node('ki_set', anonymous=True)

def set():
    global num
    num = float(input("Digite um valor para ki: "))
    talker()

def talker():
    rospy.loginfo(num)
    pub.publish(num)

if __name__ == '__main__':
    while not rospy.is_shutdown():
        set()

