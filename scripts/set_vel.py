#!/usr/bin/env python
# -*- coding: cp1252 -*-

import rospy
from std_msgs.msg import Float32

# Inicia o nó "vel"
pub = rospy.Publisher('vel_set', Float32, queue_size=10)
rospy.init_node('vel_set', anonymous=True)

def set():
    global num
    while True:
        num = float(input("Digite o valor da velocidade desejada em m/s: "))
        talker()

def talker():
    rospy.loginfo(num)
    pub.publish(num)

if __name__ == '__main__':
    try:
        set()
    except rospy.ROSInterruptException:
        pass
