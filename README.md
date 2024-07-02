# Neural Signal Operated Intelligent Robot

 ## Introduction
Brain-computer Interface (BCI) applications based on steady-state visual evoked potentials (SSVEP) have the advantages of being fast, accurate and mobile. SSVEP... (explains SSVEP). The majority of SSVEP applications focus on the spelling task. Usually the subjects are asked to stare at a group of letters flashing at different rate on the screen, and EEG data is simultaneously recorded to decode which letter the subject is currently looking at. Many researchers in the field are constantly working on expanding the number of classes for classification as well as the accuracy of the classification algorithm. As a group of high school students, we know that it would be extremely challenging to come up with a better algorithm for SSVEP classification. Thus, we decided to slightly modifying an existing algorithm and focus on expanding the application side of SSVEP. Robot maze navigation has always been a challenging field in computer algorithms. Being able to design a robot that is capable of making real-time decisions and solve unexpected problems post a great challenge (https://www.frontiersin.org/journals/robotics-and-ai/articles/10.3389/frobt.2022.834021/full). The current directions of robot maze navigation has been focused on equipping the robot with more sensors to acquire more information and improving path finding algorithms. Most of the existing algorithms rely solely on the robots to make its own decision, such method could be advantageous in applications which human supervision cannot be provided. However, in some applications in which a human supervisor is available and time is a key factor, it may be advantageous for human and robot collaboration. In this paper, we propose a novel robot maze navigation system with contactless human guidance through SSVEP. The robot car is equipped with basic path finding algorithms, and when a decision has to be made, usually at a cross-section, the robot stops and asks for human guidance. The operator could give instructions to the robot car by staring at one of the threes flashing LEDs equipped at the front, left and right side attached on the robot, each LED corresponds to the command "move forward", "turn 90 degrees left" and "turn 90 degrees right". Combining with the human's intelligence that sees the entirety of the maze, the robot can navigate its way out of the maze more efficiently. We believe such a human machine collaboration scheme could be implemented at elderly homes to help elderly people carry out simple daily tasks such as object retrieval, taking out trash and assist with other activities. 
 ##Requirements
| name        | function |  website  |
| :--------  | :-----  | :----:  |
| Cyton board | data conversion|[openBCI](https://docs.openbci.com/GettingStarted/Boards/CytonGS/)|
| Python | data processing and flask server|[Python](https://www.python.org/downloads/)|
| Ear clip electrodes and wires | data collection|[openBCI](https://docs.openbci.com/GettingStarted/Boards/CytonGS/)|
| Arduino based ESP32 board | car CPU|[Arduino](https://www.arduino.cc/)|
| Motor and wooden based vehicle frame| car frame| Nolink|
| LED, resistance and lithium battery| car material| Nolink|

#### Python lib

Python (LSL connection): `pip install pylsl`

Python (Server connection): `pip install requests`

Python (AI frame): `pip install scikit-learn`

Python (AI frame): `pip install tensorflow-gpu==2.0.0`

Python (Scipy): `pip install scipy`

Python (Server frame): `pip install flask`