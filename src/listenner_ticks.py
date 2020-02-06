#!/usr/bin/env python
import rospy
from std_msgs.msg import String
from std_msgs.msg import Int16

def ticks_callback(msg_ticks):
    global ticks
    global encoder_A
    global encoder_B
    global encoder_C
    global encoder_D

    ticks = msg_ticks.data
    encoders = ticks.split('#')
    rospy.loginfo('Encoders: %s', encoders)
    encoder_A = int(encoders[0])
    encoder_B = int(encoders[1])
    encoder_C = int(encoders[2])
    encoder_D = int(encoders[3])

    talker()

def set():
    rospy.Subscriber("ticks", String, ticks_callback)
    rospy.init_node('listenner_ticks', anonymous=True)


def talker():
    #rospy.loginfo('Encoder_A: %d', encoder_A)
    pub_A.publish(encoder_A)

    #rospy.loginfo('Encoder_B: %d', encoder_B)
    pub_B.publish(encoder_B)

    #rospy.loginfo('Encoder_C: %d', encoder_C)
    pub_C.publish(encoder_C)

    #rospy.loginfo('Encoder_D: %d', encoder_D)
    pub_D.publish(encoder_D)


pub_A = rospy.Publisher('ticks_A', Int16, queue_size=10)
pub_B = rospy.Publisher('ticks_B', Int16, queue_size=10)
pub_C = rospy.Publisher('ticks_C', Int16, queue_size=10)
pub_D = rospy.Publisher('ticks_D', Int16, queue_size=10)
rospy.Subscriber("ticks", String, ticks_callback)

rospy.init_node('listenner_ticks', anonymous=True)

rospy.spin()


if __name__ == '__main__':
    while not rospy.is_shutdown():
        set()
