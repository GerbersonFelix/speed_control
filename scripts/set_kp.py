#!/usr/bin/env python
# -*- coding: cp1252 -*-

import rospy
from std_msgs.msg import Float32

pub = rospy.Publisher('kp_set', Float32, queue_size=10)
rospy.init_node('kp_set', anonymous=True)

def set():
    global num
    num = float(input("Digite um valor para kp: "))
    talker()

def talker():
    rospy.loginfo(num)
    pub.publish(num)

if __name__ == '__main__':
    while not rospy.is_shutdown():
        set()

