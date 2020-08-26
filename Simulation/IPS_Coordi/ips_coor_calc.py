#*****************************************************************************
#@Project  : SEP250
#@File     : ips_coor_calc.py
#@Details  : This program demonstrates the IPS coordinate calculation by using
#            geometry equations.
#            Please note: the coordinate of the first reference point, NODE_00,
#            is fixed as [0,0] in this algorithm.
#            Eight test vectors are provided in this file. User should generate
#            test vectors to verify if their IPS coordiate calculation is correct.
#            The coordinate (0,0) is located the top left corner. X-axis is 
#            horizontal, while Y-axis is vertical.
#@Author   : Liang Tang
#
#--------------------------------------------------------------------------
#@Revision  :
# Ver    Author      Date          Changes
#--------------------------------------------------------------------------
#  1.0   Liang T     2017-09-16    Initial Release with test vector
#******************************************************************************

import time
import math
import numpy as np
#from Tkinter import*  #For Python2
from tkinter import*
import tkinter

###########################################################
#External global variable
###########################################################


###########################################################
#Reference Point definition
###########################################################
map_size = [1200, 800]

#Test Vector 1
#NODE_00 = [   0, 0]
#NODE_01 = [ 400, 0]
#NODE_02 = [ 400, 600]
#DIST_0 = 300
#DIST_1 = 440
#DIST_2 = 100
#Result: 70.5 453.0

#Test Vector 2
NODE_00 = [   0, 0]
NODE_01 = [ 400, 0]
NODE_02 = [ 400, 600]
DIST_0 = 300
DIST_1 = 440
DIST_2 = 450
#Result: 70.5 292.583333333

#Test Vector 3
#NODE_00 = [   0, 0]
#NODE_01 = [ 400, 0]
#NODE_02 = [ 400, 600]
#DIST_0 = 500
#DIST_1 = 440
#DIST_2 = 220
#Result: 270.5 421.0

#Test Vector 4
#NODE_00 = [   0, 0]
#NODE_01 = [ 200, 400]
#NODE_02 = [   0, 600]
#DIST_0 = 500
#DIST_1 = 440
#DIST_2 = 722
#Result: 493.14 73.93

#Test Vector 5
#NODE_00 = [   0, 0]
#NODE_01 = [ 200, 400]
#NODE_02 = [ 600, 0]
#DIST_0 = 500
#DIST_1 = 440
#DIST_2 = 125
#Result: 495.3125 72.84375 

#Test Vector 6
#NODE_00 = [   0, 0]
#NODE_01 = [ 200, 400]
#NODE_02 = [ 600, 600]
#DIST_0 = 500
#DIST_1 = 440
#DIST_2 = 536
#Result: 496.84 72.08 

#Test Vector 7
#NODE_00 = [   0, 0]
#NODE_01 = [ 360, 750]
#NODE_02 = [ 0, 640]
#DIST_0 = 500
#DIST_1 = 460
#DIST_2 = 536
#Result: 408.619791667 290.8625

#Test Vector 8
#NODE_00 = [   0, 0]
#NODE_01 = [ 700, 0]
#NODE_02 = [ 0, 640]
#DIST_0 = 500
#DIST_1 = 460
#DIST_2 = 490
#Result: 377.428571429 327.734375

NUM_REF_POINT = 3
ref_point = np.zeros(NUM_REF_POINT*2)
ref_point.shape = (NUM_REF_POINT,2)
ref_point[ 0] = [NODE_00[0], NODE_00[1]]
ref_point[ 1] = [NODE_01[0], NODE_01[1]]
ref_point[ 2] = [NODE_02[0], NODE_02[1]]

read_dist = np.zeros(NUM_REF_POINT*1)
read_dist.shape = (NUM_REF_POINT,1)
read_dist[ 0] = [DIST_0]
read_dist[ 1] = [DIST_1]
read_dist[ 2] = [DIST_2]


animation = Tk()

###########################################################
# Program initialization
###########################################################
print("SEP250 IPS coordinate calculation")


map_grid = Canvas(animation, width=map_size[0], height=map_size[1])
map_grid.grid()
map_grid.pack()
map_grid.create_line( 0            ,             0, map_size[0]-1,             0, fill="DarkOrchid4", width=10)
map_grid.create_line( 0            ,             0,             0, map_size[1]-1, fill="DarkOrchid4", width=10)
map_grid.create_line( 0            , map_size[1]-1, map_size[0]-1, map_size[1]-1, fill="DarkOrchid4", width=10)
map_grid.create_line( map_size[0]-1,             0, map_size[0]-1, map_size[1]-1, fill="DarkOrchid4", width=10)

#Draw map nodes
for i in range(0, NUM_REF_POINT):
  radius = read_dist[i][0]
  r_small = 10
  offset_text_h = 80
  offset_text_v = 20
  map_grid.create_oval(ref_point[i][0]-r_small, ref_point[i][1]-r_small, ref_point[i][0]+r_small, ref_point[i][1]+r_small, fill="burlywood2")
  map_grid.create_oval(ref_point[i][0]-radius, ref_point[i][1]-radius, ref_point[i][0]+radius, ref_point[i][1]+radius)
  map_grid.create_text(ref_point[i][0]+offset_text_h, ref_point[i][1]+offset_text_v, font=("Purisa",22), text="Abchor Node:%d"%(i)) 
  

###########################################################
# Non-matrix method
###########################################################
if (NUM_REF_POINT==3):
  x0 = ref_point[0][0]
  y0 = ref_point[0][1]
  x1 = ref_point[1][0]
  y1 = ref_point[1][1]
  x2 = ref_point[2][0]
  y2 = ref_point[2][1]
  d0d0md2d2 = DIST_0*DIST_0 - DIST_2*DIST_2
  x2x2py2y2 = x2*x2 + y2*y2
  block1 = d0d0md2d2 + x2x2py2y2
  
  d0d0md1d1 = DIST_0*DIST_0 - DIST_1*DIST_1
  x1x1py1y1 = x1*x1 + y1*y1
  
  #If x1 is 0, you need use other way to solve!
  ratio = x2/x1
  block2 = d0d0md1d1 + x1x1py1y1
  block2_p = block2 * ratio
  
  block3 = y2 - ratio*y1
  
  pos_y = (block1 - block2_p)/block3
  pos_y = pos_y/2
  
  pos_x = block2 - 2*pos_y*y1
  pos_x = pos_x/x1
  pos_x = pos_x/2
  
  radius = 10
  map_grid.create_oval(pos_x-radius, pos_y-radius, pos_x+radius, pos_y+radius, fill="red")
  map_grid.create_text(pos_x, pos_y, font=("Purisa",20), text="Calculated coordinate!") 
  
  print("//////////////////////////////////////////////////////////////")
  print("//Reference Point 0 [x/y]: ", NODE_00[0], NODE_00[1], "; Distance:", DIST_0)
  print("//Reference Point 1 [x/y]: ", NODE_01[0], NODE_01[1], "; Distance:", DIST_1)
  print("//Reference Point 2 [x/y]: ", NODE_02[0], NODE_02[1], "; Distance:", DIST_2)
  print("//Calculated x/y result:", pos_x, pos_y)
else:
  print("The number of reference points is not 3. Non-matrix method cannot be used!")



###########################################################
# Matrix method
###########################################################
#Not implemented yet.
  

animation.update()
    

mainloop()
