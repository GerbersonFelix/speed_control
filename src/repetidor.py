#!/usr/bin/env python
# -*- coding: cp1252 -*-

import rospy
from std_msgs.msg import Float32

vel_ref = 0

#rate = rospy.Rate(10) #hz

def vel_callback(msg_v):

    global vel_ref
    vel_ref = msg_v.data #Velocidade de referencia
    

def repetir():

    pub.publish(vel_ref)
    #rospy.loginfo('Sinal de velocidade recebido: %f' % vel_ref)


# Inicia o nó "repeat"
pub = rospy.Publisher('vel_repeat', Float32, queue_size=10)
rospy.Subscriber("vel_set", Float32, vel_callback)
rospy.init_node('repeat', anonymous=True)


if __name__ == '__main__':
    
    while not rospy.is_shutdown():
        repetir()
        #rate.sleep()
