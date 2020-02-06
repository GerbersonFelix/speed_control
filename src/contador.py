#!/usr/bin/env python
# license removed for brevity
import rospy
import time
from rosgraph_msgs.msg import Clock

def count():
    pub = rospy.Publisher('clock', Clock, queue_size=10)
    rospy.init_node('count', anonymous=True)
    rate = rospy.Rate(10) # 10hz
    begin = raw_input("Iniciar o contador? ")
    if begin == 's':
        now = rospy.get_rostime()
        tempo_secI = int(now.secs)
        while not rospy.is_shutdown():
            now = rospy.get_rostime()
            timeC = Clock()
            timeC.clock.secs = int(now.secs) - tempo_secI
            timeC.clock.nsecs = int(now.nsecs)
            rospy.loginfo(timeC)
            pub.publish(timeC)
            rate.sleep()

if __name__ == '__main__':
    try:
        count()
    except rospy.ROSInterruptException:
        pass
