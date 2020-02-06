/*
Especificações:
– Tensão: 6V DC
– Velocidade: 210 RPM
– Diâmetro do eixo: 4mm
– Comprimento do eixo: 12mm
– Máxima eficiência: 2.0kg.cm/170rpm/2.0W/0.60A
– Máximo torque: 5.2kg.cm/110rpm/3.1W/1.10A
– Cabo de conexão: 6 fios
– Comprimento do cabo: 20 cm
– Comprimento total motor e eixo: 73mm
- Redução	1:34 (1:34.02)
- Resolução do Encoder	11 x Redução 34.02 = 341.2PPR
- Diâmetro do motor	25mm
– Largura da roda: 27mm
– Diâmetro da roda: 65mm

Pinagem:
– 1 – M1 Motor (Vermelho)
– 2 – GND Encoder (Preto)
– 3 – Encoder A phase (Amarelo)
– 4 – Encoder B phase (Verde)
– 5 – 3.3V Encoder (Azul)
– 6 – M1 motor (Branco)
*/

#define USE_USBCON// Para usar com o arduino Due para não dar o erro "Unable to sync with device; possible link problem or link software version mismatch such as hydro rosserial_python with groovy Arduino"
#include <Arduino.h>
#include <ros.h>
//#include <stdio.h>
//#include <iostream>
#include <std_msgs/UInt16.h> //Para PWM
#include <std_msgs/String.h> //Para encoders

//////////////////////////////////////ROS///////////////////////////////////////
ros::NodeHandle nh;

std_msgs::String ticks_msg;
ros::Publisher ticks("ticks", &ticks_msg);

/*Pinagem do arduino*/
///////Ponte01/////
//motor_A
const int IN1 = 3;
const int IN2 = 4;
const int velocidadeA = 2;

//motor_B
const int IN3 = 5;
const int IN4 = 6;
const int velocidadeB = 7;

//////Ponte02///////
//motor_C
const int IN5 = 12;
const int IN6 = 11;
const int velocidadeC = 13;

//motor_D
const int IN7 = 10;
const int IN8 = 9;
const int velocidadeD = 8;

/////////Encoders////////
//Encoder motor A
const int C1 = 30;
const int C2 = 31;
//Encoder motor B
const int C3 = 32;
const int C4 = 33;
//Encoder motor C
const int C5 = 34;
const int C6 = 35;
//Encoder motor D
const int C7 = 36;
const int C8 = 37;

char motores[80];
//Motor A(Lado esquerdo)
volatile int long temp_A, counter_A;
char motor_a[10];
//Motor B(Lado direito)
volatile int long temp_B, counter_B;
char motor_b[10];
//Motor C(Lado esquerdo)
volatile int long temp_C, counter_C;
char motor_c[10];
//Motor D(Lado direito)
volatile int long temp_D, counter_D;
char motor_d[10];
//amarelo C1
//verde C2

///////////////////////////////Variaveiis usadas////////////////////////////////
int vel = 30; //Velocidade do prototipo
int cmd, stop; // variaveis de comando e de parada
int ativo;
int cmd_vel_A, cmd_vel_B, cmd_vel_C, cmd_vel_D; //Variavel de velocidade variavel

void ai0()
{
  if (digitalRead(C2) == LOW)
  {
    counter_A++;
  }
}

void ai1()
{
  if (digitalRead(C1) == LOW)
  {
    counter_A--;
  }
}

void ai2()
{
  if (digitalRead(C4) == LOW)
  {
    counter_B--;
  }
}

void ai3()
{
  if (digitalRead(C3) == LOW)
  {
    counter_B++;
  }
}

void ai4()
{
  if (digitalRead(C6) == LOW)
  {
    counter_C--;
  }
}

void ai5()
{
  if (digitalRead(C5) == LOW)
  {
    counter_C++;
  }
}

void ai6()
{
  if (digitalRead(C8) == LOW)
  {
    counter_D++;
  }
}

void ai7()
{
  if (digitalRead(C7) == LOW)
  {
    counter_D--;
  }
}

void go_A(int duty_A)
{
    //Motor A
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    analogWrite(velocidadeA,duty_A);

}

void go_B(int duty_B)
{
    //Motor B
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
    analogWrite(velocidadeB,duty_B);
}

void go_C(int duty_C)
{
    //Motor C
    digitalWrite(IN5,LOW);
    digitalWrite(IN6,HIGH);
    analogWrite(velocidadeC,duty_C);
}

void go_D(int duty_D)
{
    //Motor D
    digitalWrite(IN7,LOW);
    digitalWrite(IN8,HIGH);
    analogWrite(velocidadeD,duty_D);
}

void back()
{
    //Motores A
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    //Motores B
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
    analogWrite(velocidadeA,120);
    analogWrite(velocidadeB,120);
    //Motores C
    digitalWrite(IN5,HIGH);
    digitalWrite(IN6,LOW);
    //Motores D
    digitalWrite(IN7,HIGH);
    digitalWrite(IN8,LOW);
    analogWrite(velocidadeC,120);
    analogWrite(velocidadeD,120);
}

void left()
{
    //Motores A
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    //Motores B
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
    analogWrite(velocidadeA,120);
    analogWrite(velocidadeB,120);
    //Motores C
    digitalWrite(IN5,HIGH);
    digitalWrite(IN6,LOW);
    //Motores D
    digitalWrite(IN7,LOW);
    digitalWrite(IN8,HIGH);
    analogWrite(velocidadeC,120);
    analogWrite(velocidadeD,120);
}

void right()
{
    //Motores A
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    //Motores B
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
    analogWrite(velocidadeA,120);
    analogWrite(velocidadeB,120);
    //Motores C
    digitalWrite(IN5,LOW);
    digitalWrite(IN6,HIGH);
    //Motores D
    digitalWrite(IN7,HIGH);
    digitalWrite(IN8,LOW);
    analogWrite(velocidadeC,120);
    analogWrite(velocidadeD,120);
}

void stop_motor()
{
    //Motores A
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,LOW);
    //Motores B
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,LOW);
    analogWrite(velocidadeA,0);
    analogWrite(velocidadeB,0);
    //Motores C
    digitalWrite(IN5,LOW);
    digitalWrite(IN6,LOW);
    //Motores D
    digitalWrite(IN7,LOW);
    digitalWrite(IN8,LOW);
    analogWrite(velocidadeC,0);
    analogWrite(velocidadeD,0);
}


void velCallBack_A(const std_msgs::UInt16& msg_A) //Função de comandos recebidos da Jetson
{
  cmd_vel_A = msg_A.data;
  go_A(cmd_vel_A);
}

void velCallBack_B(const std_msgs::UInt16& msg_B) //Função de comandos recebidos da Jetson
{
  cmd_vel_B = msg_B.data;
  go_B(cmd_vel_B);
}

void velCallBack_C(const std_msgs::UInt16& msg_C) //Função de comandos recebidos da Jetson
{
  cmd_vel_C = msg_C.data;
  go_C(cmd_vel_C);
}

void velCallBack_D(const std_msgs::UInt16& msg_D) //Função de comandos recebidos da Jetson
{
  cmd_vel_D = msg_D.data;
  go_D(cmd_vel_D);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

ros::Subscriber<std_msgs::UInt16> pwm_A("cmd_vel_A", &velCallBack_A);
ros::Subscriber<std_msgs::UInt16> pwm_B("cmd_vel_B", &velCallBack_B);
ros::Subscriber<std_msgs::UInt16> pwm_C("cmd_vel_C", &velCallBack_C);
ros::Subscriber<std_msgs::UInt16> pwm_D("cmd_vel_D", &velCallBack_D);

//Inicializa Pinos
void setup(){
//Serial.begin(9600);
pinMode(IN1,OUTPUT);
pinMode(IN2,OUTPUT);
pinMode(IN3,OUTPUT);
pinMode(IN4,OUTPUT);
pinMode(velocidadeA,OUTPUT);
pinMode(velocidadeB,OUTPUT);
pinMode(IN5,OUTPUT);
pinMode(IN6,OUTPUT);
pinMode(IN7,OUTPUT);
pinMode(IN8,OUTPUT);
pinMode(velocidadeC,OUTPUT);
pinMode(velocidadeD,OUTPUT);

//Motor A
pinMode(C1, INPUT_PULLUP);// Canal 1
pinMode(C2, INPUT_PULLUP);// Canal 2
//Motor B
pinMode(C3, INPUT_PULLUP);// Canal 1
pinMode(C4, INPUT_PULLUP);// Canal 2
//Motor C
pinMode(C5, INPUT_PULLUP);// Canal 1
pinMode(C6, INPUT_PULLUP);// Canal 2
//Motor D
pinMode(C7, INPUT_PULLUP);// Canal 1
pinMode(C8, INPUT_PULLUP);// Canal 2

nh.getHardware()->setBaud(115200); //Baudrate de 115200
nh.initNode();
nh.subscribe(pwm_A);
nh.subscribe(pwm_B);
nh.subscribe(pwm_C);
nh.subscribe(pwm_D);

nh.advertise(ticks); //Todos os encoders

//Interrupções do encoder do motor A
attachInterrupt(digitalPinToInterrupt(C1), ai0, RISING); //Canal 1
attachInterrupt(digitalPinToInterrupt(C2), ai1, RISING); //Canal 2
//Interrupçoes do encoder do motor B
attachInterrupt(digitalPinToInterrupt(C3), ai2, RISING); //Canal 1
attachInterrupt(digitalPinToInterrupt(C4), ai3, RISING); //Canal 2
//Interrupções do encoder do motor C
attachInterrupt(digitalPinToInterrupt(C5), ai4, RISING); //Canal 1
attachInterrupt(digitalPinToInterrupt(C6), ai5, RISING); //Canal 2
//Interrupçoes do encoder do motor D
attachInterrupt(digitalPinToInterrupt(C7), ai6, RISING); //Canal 1
attachInterrupt(digitalPinToInterrupt(C8), ai7, RISING); //Canal 2

}

void loop(){

  //Interrupções do encoder do motor A
  //attachInterrupt(digitalPinToInterrupt(C1), ai0, CHANGE); //Canal 1
  //attachInterrupt(digitalPinToInterrupt(C2), ai1, CHANGE); //Canal 2
  //sprintf(motor_a, "%ld", counter_A);
  //detachInterrupt(digitalPinToInterrupt(C1)); //Canal 1
  //detachInterrupt(digitalPinToInterrupt(C2)); //Canal 2
  //delay(1);

  //Interrupçoes do encoder do motor B
  //attachInterrupt(digitalPinToInterrupt(C3), ai2, CHANGE); //Canal 1
  //attachInterrupt(digitalPinToInterrupt(C4), ai3, CHANGE); //Canal 2
  //sprintf(motor_b, "%ld", counter_B);
  //detachInterrupt(digitalPinToInterrupt(C3)); //Canal 1
  //detachInterrupt(digitalPinToInterrupt(C4)); //Canal 2

  //Interrupções do encoder do motor C
  //attachInterrupt(digitalPinToInterrupt(C5), ai4, RISING); //Canal 1
  //attachInterrupt(digitalPinToInterrupt(C6), ai5, RISING); //Canal 2
  //sprintf(motor_c, "%ld", counter_C);
  //detachInterrupt(digitalPinToInterrupt(C5)); //Canal 1
  //detachInterrupt(digitalPinToInterrupt(C6)); //Canal 2

  //Interrupçoes do encoder do motor D
  //attachInterrupt(digitalPinToInterrupt(C7), ai6, RISING); //Canal 1
  //attachInterrupt(digitalPinToInterrupt(C8), ai7, RISING); //Canal 2
  //sprintf(motor_d, "%ld", counter_D);
  //detachInterrupt(digitalPinToInterrupt(C7)); //Canal 1
  //detachInterrupt(digitalPinToInterrupt(C8)); //Canal 2

  sprintf(motores,"%ld#%ld#%ld#%ld", counter_A, counter_B, counter_C, counter_D);
  //sprintf(motores2)
  //motores ="#" + "v";
  ticks_msg.data = motores;//strcat(motor_a, "#", motor_b, "#", motor_c, "#", motor_d);
  ticks.publish( &ticks_msg);

  nh.spinOnce();
  //delay(1);

}
