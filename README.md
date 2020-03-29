# speed_control

Um pacote ROS que recebe valores de pulsos de encoders e realiza o controle de velocidade dos motores.

### Nós
O pacote contém atualmente 7 nós
1. **control**: Recebe os dados de odometria, velocidade de referência e dos parametros KP, KI, KD para calcular o PWM de controle dos motores. Na qual também publica a diferença da velocidade de referência com a velocidade lida. (Minicooper)
      * Script File: controle.py
      * Subscribers: "/odom"
		     "/vel_repeat"
		     "/kp_set"
		     "/ki_set"
		     "/kd_set"
      * Publishers: "/cmd_vel"
		    "/erro"
2. **listenner_ticks**: Recebe os valores de pulsos dos encoders do robô e os publica de forma individual a cada encoder. (wally2.0)
      * Script File: listenner_ticks.py
      * Subscribers: "/ticks"
      * Publishers: "/ticks_A"
		    "/ticks_B"
		    "/ticks_C"
		    "/ticks_D"
3. **listenner_ticks_srv**:Também recebe os valores de pulsos dos encoders do robô e os publica de forma individual a cada encoder, a diferença é que este solicita por meio de um service o envio dos valores. (wally2.0)
      * Script File: listenner_ticks_srv.py
      * Subscribers: "/ticks"
      * Publishers: "/ticks_A"
		    "/ticks_B"
		    "/ticks_C"
		    "/ticks_D"
      * Service: "/ticks_srv" (client)
4. **repeat**: Recebe o valor da velocidade de referência e o publica continuarmente para que esta seja mostrada no gráfico, na qual é comparada com a velocidade lida. (Minicooper)
      * Script File: repetidor.py
      * Subscribers: "/vel_set"
      * Publishers: "/vel_repeat"
5. **kd_set**: Responsável por receber do usuário o parâmetro diferencial do controle PID utilizado no robô. (Minicooper)
      * Script File: set_kd.py
      * Publishers: "/kd_set"
6. **ki_set**: Responsável por receber do usuário o parâmetro integrativo do controle PID utilizado no robô. (Minicooper)
      * Script File: set_ki.py
      * Publishers: "/ki_set"
7. **kp_set**: Responsável por receber do usuário o parâmetro proporcional do controle PID utilizado no robô. (Minicooper)
      * Script File: set_kp.py
      * Publishers: "/kp_set"
8. **vel_set**: Responsável por receber do usuário a velocidade de referência do robô. (Minicooper)
      * Script File: set_vel.py
      * Publishers: "/vel_set"

### Code arduino
Código responsável por fazer a leitura dos encoders e enviar os valores de uma vez só para a porta serial. No qual também é responsável por receber os valores de PWM para realizar o controle individual de cada motor.
* Script File: main.cpp
* Subscribers:  "/cmd_vel_A"
	        "/cmd_vel_B"
 		"/cmd_vel_C"
	        "/cmd_vel_D"
* Publishers: "/ticks"

Código responsável por fazer a leitura dos encoders e enviar os valores de uma vez só para a porta serial. No qual também é responsável por receber os valores de PWM para realizar o controle individual de cada motor, como também recebe a "permissão" através de um service de que pode publicar os valores de leitura dos encoders.
* Script File: WallyV2.ino
* Subscribers:  "/cmd_vel_A"
	        "/cmd_vel_B"
 		"/cmd_vel_C"
	        "/cmd_vel_D"
* Publishers: "/ticks"
* Service: "/ticks_srv" (server)
		        
### Passos para usar os nós
#### Passo1: Instale o pacote
```sh
$ cd /home/workspace/catkin_ws/src
$ git clone https://github.com/GerbersonFelix/speed_control.git
```
#### Passo2: Compile o pacote
```sh
$ cd /home/workspace/catkin_ws
$ catkin_make
$ source devel/setup.bash
```
