Readme
This program simulates a vehicle's movement in an IPS (Indoor Positional System) environment.

The simulated navigation is written in Python language. Python version 3 environment is preferred. If Python version 2 is used, the "from Tkinter import*" in nav_algo.py should be enabled, while the "from tkinter import*" in that file should be disabled.

The nav_algo.py is the entry of this program. In an UNIX/LINUX environment, the following command should be executed to run this simulation:
$python3 nav_algo.py

After launching the program, there are following components on the picture:
1. Nodes: the possible turning points, in small orange color dots. Each node has an ID, labelled by "Node#".
2. Destination: a special turning point, in big green circuit.
3. Edge: the tiny green lines. Each edge has an ID, labelled by "path#".
4. Simulated vehicle: a small blue square.
5. Simulated vehicle's ultrasonic sensor range: a grey square around the simulated vehicle. Obstacle cannot be overlapped to this range.
6. Obstacles: various grey rectangle. Each obstacle has an ID, labelled by "OB#".
7. Selected Turning Points (TPs): TP list is the path planning result, which is a subset of Nodes.
8. Control Panel: the Control Panel is the bottom red rectangle. The first click on the Control Panel will pause the simulation. The simulation can be resumed by click again. However, the resumed simulation's "time" is triggered by each mouse clicking, or MouseTick, instead of the SysTick from timer.

There is a switch named "__PATH_PLAN_EN" in nav_algo.py. Please read the inline comment for this switch usage.

Any question about this program, please contact: Liang (tang677@hotmail.com)