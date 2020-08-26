Readme
This program calculates a coordinate by trilateration method, which is used in DigiPen SEP250 course.
Three circles are drawn, the centers are the location of IPS beacons (or, Anchor Nodes), while the radiuses are the "measured" distances between the "vehicle" and beacons.
The calculated coordinate is based on the coordinates of the beacons and the "measured" distances, which can be set be changing: NODE_00, NODE_01, NODE_02, DIST_0, DIST_1 and DIST_2 variables. The calculated coordinates will be shown as a bit red dot.


In an UNIX/LINUX environment, the following command should be executed to run this simulation:
$python3 ips_coor_calc.py

