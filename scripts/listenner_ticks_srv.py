#!/usr/bin/env python
import rospy
from std_msgs.msg import String
from std_msgs.msg import Int16
from rosserial_arduino.srv import Test

def start():

    rospy.wait_for_service('/ticks_srv')
    try:
        serv = rospy.ServiceProxy('/ticks_srv',Test)
        req = serv("start")
        rospy.loginfo("Executed service")
    except rospy.ServiceException, e:
        pass



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
    start()
    rate.sleep()

def set():
    global pub_A
    global pub_B
    global pub_C
    global pub_D
    global rate

    rospy.init_node('listenner_ticks', anonymous=True)
    rospy.Subscriber("ticks", String, ticks_callback)
    pub_A = rospy.Publisher('ticks_A', Int16, queue_size=10)
    pub_B = rospy.Publisher('ticks_B', Int16, queue_size=10)
    pub_C = rospy.Publisher('ticks_C', Int16, queue_size=10)
    pub_D = rospy.Publisher('ticks_D', Int16, queue_size=10)
    
    start()

    rate = rospy.Rate(20)

    rospy.spin()




def talker():


    #rospy.loginfo('Encoder_A: %d', encoder_A)
    pub_A.publish(encoder_A)

    #rospy.loginfo('Encoder_B: %d', encoder_B)
    pub_B.publish(encoder_B)

    #rospy.loginfo('Encoder_C: %d', encoder_C)
    pub_C.publish(encoder_C)

    #rospy.loginfo('Encoder_D: %d', encoder_D)
    pub_D.publish(encoder_D)



if __name__ == '__main__':
    while not rospy.is_shutdown():
        set()
