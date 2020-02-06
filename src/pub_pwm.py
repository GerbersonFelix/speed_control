#!/usr/bin/env python
# -*- coding: cp1252 -*-

import rospy
from std_msgs.msg import UInt16

# Inicia o nó "vel"
pub = rospy.Publisher('vel', UInt16, queue_size=10)
rospy.init_node('vel', anonymous=True)

def captura():
    global num
    while True:
        num = int(input("Digite o valor do PWM: "))
        talker()

def talker():
    rospy.loginfo(num)
    pub.publish(num)

if __name__ == '__main__':
    try:
        captura()
    except rospy.ROSInterruptException:
        pass
