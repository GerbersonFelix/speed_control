#!/usr/bin/env python
# license removed for brevity

import rospy
from nav_msgs.msg import Odometry
from std_msgs.msg import UInt16
from std_msgs.msg import Float32
from std_msgs.msg import Int16

kp = 20
ki = 0.5
kd = 0
e_P = 0
e_I = 0
e_D = 0
vel_ref = 0
vel_lido = 0

global dt
dt = 0.05 #Defined at interruption

e_ant_I = 0
e_ant_D = 0

'''
e = v_ref-v_rpm;
                                      
  e_P = e;
  e_I = e_ant_I + e*dt;
  e_D = (e-e_ant_D)/dt;         
              
  duty = Kp*e_P + Ki*e_I + Kd*e_D;
'''


def map(x, in_min, in_max, out_min, out_max):
    return int((x-in_min) * (out_max-out_min) / (in_max-in_min) + out_min)

def odom_callback(msg_o):
    global vel_lido
    vel_lido = msg_o.twist.twist.linear.x #Velocidade recebida da odometria
    
def vel_callback(msg_v):
    global vel_ref
    vel_ref = msg_v.data #Velocidade de referencia
    
def kp_callback(msg_kp):
    global kp
    kp = msg_kp.data

def ki_callback(msg_ki):
    global ki
    ki = msg_ki.data

def kd_callback(msg_kd):
    global kd
    kd = msg_kd.data


pub = rospy.Publisher('cmd_vel', UInt16, queue_size=10)
pub2 = rospy.Publisher('erro', Float32, queue_size=10)
rospy.Subscriber("odom", Odometry, odom_callback)
rospy.Subscriber("vel_repeat", Float32, vel_callback)
rospy.Subscriber("kp_set", Float32, kp_callback)
rospy.Subscriber("ki_set", Float32, ki_callback)
rospy.Subscriber("kd_set", Float32, kd_callback)

# starts the node
rospy.init_node('control', anonymous=True)

rate = rospy.Rate(500) #hz

def control():
    global e_ant_I
    global e_I
    global dt
    global e_ant_D
    global e_D

    if vel_ref == 0:
        pwm_final = 0
        pub.publish(pwm_final)

        rospy.loginfo('Sinal de pwm enviado: %i' % pwm_final)

    else:
        erro = vel_ref - vel_lido
        rospy.loginfo('Sinal de erro: %f' % erro)
        pub2.publish(erro)

        e_P = erro
        e_I = e_ant_I + erro*dt
        e_D = (erro-e_ant_D)/dt

        pwm = erro * kp + ki * e_I + kd * e_D

        pwm = int(pwm)
        
        pwm_final = map(pwm,-20,40,0,60)
        pub.publish(pwm_final)

        e_ant_I = e_I
        e_ant_D = erro

        rospy.loginfo('Sinal de pwm enviado: %i' % pwm_final)
    



if __name__ == '__main__':

    while not rospy.is_shutdown():
        control()
        rate.sleep()
