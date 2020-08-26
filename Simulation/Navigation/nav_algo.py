#*****************************************************************************
#@Project  : SEP250
#@File     : nav_algo.py
#@Details  : This program simulates vehicle movement in an IPS environment, with
#            path planning.
#            This is the entry file for this simulation program.
#            Execution method: python3 nav_algo.py 
#            The coordinate (0,0) is located the top left corner. X-axis is 
#            horizontal, while Y-axis is vertical.
#@Author   : Liang Tang
#
#--------------------------------------------------------------------------
#@Revision  :
# Ver    Author      Date          Changes
#--------------------------------------------------------------------------
#  1.0   Liang T     2018-03-07    Initial Release
#******************************************************************************

import time
import math
import numpy as np
from dir_final_core import*
from path_plan      import*
from gv import*
#from Tkinter import*  #For Python2
from tkinter import*
import tkinter

###########################################################
#Private global variable
###########################################################
#__DBG_MAIN=True
__DBG_MAIN=False

global __DBG_RANGE_FINDER
#__DBG_RANGE_FINDER = True
__DBG_RANGE_FINDER = False

global __DBG_LINE_OVERLAP
#__DBG_LINE_OVERLAP= True
__DBG_LINE_OVERLAP= False

global __DBG_IPS_CALC
#__DBG_IPS_CALC=True
__DBG_IPS_CALC=False

__DBG_GRAPH_MAIN=True
#__DBG_GRAPH_MAIN=False


###########################################################
# switch: __NAV_MAP_AUTO
#         TURE:  The path planning is enabled.
#                Dijkstra algorithm is implemented here.
#                The selected nodes are in big red dots, with
#                "T.P.#" annotation, # is the order of the 
#                turning points.
#         FALSE: the path planning is disabled. The planned 
#                paths are manually set to nav_node[] array.
#the vehicle movement animation is enabled.
###########################################################
__PATH_PLAN_EN=True
#__PATH_PLAN_EN=False

###########################################################
#External global variable
###########################################################
#Direction ID
DIR_ID_F  = 0
DIR_ID_FL = 1
DIR_ID_L  = 2
DIR_ID_BL = 3
DIR_ID_B  = 4
DIR_ID_BR = 5
DIR_ID_R  = 6
DIR_ID_FR = 7
DIR_ID_STOP = 8
DIR_ID_NULL = 255

#Direction pattern
DIR_BIT_NULL= 0x00
DIR_BIT_F  = 0x01
DIR_BIT_FL = 0x02
DIR_BIT_L  = 0x04
DIR_BIT_BL = 0x08
DIR_BIT_B  = 0x10
DIR_BIT_BR = 0x20
DIR_BIT_R  = 0x40
DIR_BIT_FR = 0x80

MAX_NUMBER = 0x7FFFFFFF



###########################################################
#Vehicle/destination position
###########################################################
#Set 1
#veh_coordi_init = [30, 720]
#dest_coordi = [700, 100]

#Set 2
#veh_coordi_init = [200, 720]
#dest_coordi = [100, 100]

#Set 3: map test
veh_coordi_init = [50, 750]
dest_coordi = [800, 150]

#Other setting
#veh_coordi_init = [600, 750]
#veh_coordi_init = [30, 620]
#veh_coordi_init = [40, 20]

###########################################################
#Map definition
###########################################################
map_size = [1200, 800]



###########################################################
#Obstacle coordinat definition
###########################################################
NUM_OBSTACLE = 13
#NUM_OBSTACLE = 3

obstacle = np.zeros(NUM_OBSTACLE*4)
obstacle.shape = (NUM_OBSTACLE,4)
obstacle[ 0] = [ 100, 600, 300, 700]
obstacle[ 1] = [ 000, 300, 400, 400]
obstacle[ 2] = [ 200, 500, 250, 600]
obstacle[ 3] = [1000, 100,1200, 200]
obstacle[ 4] = [ 500, 400, 700, 500]
obstacle[ 5] = [ 650, 250, 900, 300]
obstacle[ 6] = [ 800, 400, 900, 600]
obstacle[ 7] = [1050, 300,1100, 500]
obstacle[ 8] = [ 350, 000, 550, 200]
obstacle[ 9] = [ 400, 600,1100, 700]
obstacle[10] = [ 100, 100, 250, 200]
obstacle[11] = [ 700, 100, 750, 250]
obstacle[12] = [ 390, 490, 410, 510]

#Path starting points
NODE_00 = [  50, 750] #1150, 750
NODE_01 = [ 350, 750] # 350, 450
NODE_02 = [ 350, 550] # 750, 550
NODE_03 = [ 450, 550] # 450, 250
NODE_04 = [ 450, 350] # 950, 350
NODE_05 = [ 750, 550] # 750, 350
NODE_06 = [ 950, 550] # 950,  50
NODE_07 = [  50, 250] # 600, 250
NODE_08 = [ 600, 350] # 600,  50
NODE_09 = [ 600,  50] #1150,  50
NODE_10 = [ 825, 175] # 950, 175
NODE_11 = [ 825,  50] # 825, 175
NODE_12 = [1150, 550] # 950, 550
NODE_13 = [1150, 750] #1150, 250
NODE_14 = [1150, 250] # 950, 250
#NODE_15 = [ 300,  50] #  50,  50
NODE_15 = [ 280,  50] #  50,  50
NODE_16 = [  50,  50] #  50, 250
#NODE_17 = [ 300, 250] # 300,  50
NODE_17 = [ 280, 250] # 300,  50
NODE_18 = [  50, 450] # 450, 450

#The path terminal points
NODE_19 = [ 350, 450]
NODE_20 = [ 450, 250]
NODE_21 = [ 950, 350]
NODE_22 = [ 750, 350]
NODE_23 = [ 950,  50]
NODE_24 = [ 600, 250]
NODE_25 = [1150,  50]
NODE_26 = [ 950, 175]
NODE_27 = [ 950, 250]
NODE_28 = [ 450, 450]



###########################################################
#Graph vertex definition
#All posible pathes are decided by these nodes
#Format:
#path_node[ X].[0]: coordinate x position
#path_node[ X].[1]: coordinate y position
#path_node[ X].[2]: d: shortest-path estimate
#path_node[ X].[3]: pi: predecessor ID
#path_node[ X].[4]: state: indicate whether the vetrex has
#                   been extracted or note
#X is the vertex ID.
###########################################################
NUM_PATH_NODE = 29
path_node = np.zeros(NUM_PATH_NODE*5)
path_node.shape = (NUM_PATH_NODE,5)

#Define the ID of the starting node:
ID_NODE_S = 0
#Define the ID of the end node:
ID_NODE_E = 10
path_node[ 0] = [NODE_00[0], NODE_00[1], 0, 0, 0]
path_node[ 1] = [NODE_01[0], NODE_01[1], 0, 0, 0]
path_node[ 2] = [NODE_02[0], NODE_02[1], 0, 0, 0]
path_node[ 3] = [NODE_03[0], NODE_03[1], 0, 0, 0]
path_node[ 4] = [NODE_04[0], NODE_04[1], 0, 0, 0]
path_node[ 5] = [NODE_05[0], NODE_05[1], 0, 0, 0]
path_node[ 6] = [NODE_06[0], NODE_06[1], 0, 0, 0]
path_node[ 7] = [NODE_07[0], NODE_07[1], 0, 0, 0]
path_node[ 8] = [NODE_08[0], NODE_08[1], 0, 0, 0]
path_node[ 9] = [NODE_09[0], NODE_09[1], 0, 0, 0]
path_node[10] = [NODE_10[0], NODE_10[1], 0, 0, 0]
path_node[11] = [NODE_11[0], NODE_11[1], 0, 0, 0]
path_node[12] = [NODE_12[0], NODE_12[1], 0, 0, 0]
path_node[13] = [NODE_13[0], NODE_13[1], 0, 0, 0]
path_node[14] = [NODE_14[0], NODE_14[1], 0, 0, 0]
path_node[15] = [NODE_15[0], NODE_15[1], 0, 0, 0]
path_node[16] = [NODE_16[0], NODE_16[1], 0, 0, 0]
path_node[17] = [NODE_17[0], NODE_17[1], 0, 0, 0]
path_node[18] = [NODE_18[0], NODE_18[1], 0, 0, 0]
path_node[19] = [NODE_19[0], NODE_19[1], 0, 0, 0]
path_node[20] = [NODE_20[0], NODE_20[1], 0, 0, 0]
path_node[21] = [NODE_21[0], NODE_21[1], 0, 0, 0]
path_node[22] = [NODE_22[0], NODE_22[1], 0, 0, 0]
path_node[23] = [NODE_23[0], NODE_23[1], 0, 0, 0]
path_node[24] = [NODE_24[0], NODE_24[1], 0, 0, 0]
path_node[25] = [NODE_25[0], NODE_25[1], 0, 0, 0]
path_node[26] = [NODE_26[0], NODE_26[1], 0, 0, 0]
path_node[27] = [NODE_27[0], NODE_27[1], 0, 0, 0]
path_node[28] = [NODE_28[0], NODE_28[1], 0, 0, 0]

###########################################################
#Graph edge definition
###########################################################
NUM_PATH = 37


#new format: based on node  : [0] is the ID of the starting node, [1] is the ID of the ending node
path_edge_list = np.zeros(NUM_PATH*2)
path_edge_list.shape = (NUM_PATH,2)

path_edge_list[ 0] = [ 0,  1]
path_edge_list[ 1] = [ 0, 18]
path_edge_list[ 2] = [ 1, 13]
path_edge_list[ 3] = [ 1,  2]
path_edge_list[ 4] = [ 2,  3]
path_edge_list[ 5] = [ 2, 19]
path_edge_list[ 6] = [18, 19]
path_edge_list[ 7] = [19, 28]
path_edge_list[ 8] = [ 3, 28]
path_edge_list[ 9] = [28,  4]
path_edge_list[10] = [ 4, 20]
path_edge_list[11] = [ 4,  8]
path_edge_list[12] = [20, 17]
path_edge_list[13] = [17, 15]
path_edge_list[14] = [17,  7]
path_edge_list[15] = [ 7, 16]
path_edge_list[16] = [15, 16]
path_edge_list[17] = [20, 24]
path_edge_list[18] = [ 8, 24]
path_edge_list[19] = [24,  9]

path_edge_list[20] = [ 9, 11]
path_edge_list[21] = [11, 10]
path_edge_list[22] = [11, 23]
path_edge_list[23] = [10, 26]
path_edge_list[24] = [23, 25]
path_edge_list[25] = [23, 26]
path_edge_list[26] = [26, 27]
path_edge_list[27] = [27, 14]
path_edge_list[28] = [27, 21]
path_edge_list[29] = [21,  6]

path_edge_list[30] = [ 3,  5]
path_edge_list[31] = [ 5, 22]
path_edge_list[32] = [ 8, 22]
path_edge_list[33] = [22, 21]
path_edge_list[34] = [ 6, 12]
path_edge_list[35] = [12, 14]
path_edge_list[36] = [13, 12]




###########################################################
#Manual routing: all the decided navigation route nodes
###########################################################
NUM_NAV_NODE_MAX = 40
#Manual path planning 1
#NUM_NAV_NODE = 10
#nav_node = np.zeros(NUM_NAV_NODE_MAX*5)
#nav_node.shape = (NUM_NAV_NODE_MAX,5)
#nav_node[ 0] = path_node[ 0]
#nav_node[ 1] = path_node[18]
#nav_node[ 2] = path_node[19]
#nav_node[ 3] = path_node[28]
#nav_node[ 4] = path_node[ 4]
#nav_node[ 5] = path_node[20]
#nav_node[ 6] = path_node[24]
#nav_node[ 7] = path_node[ 9]
#nav_node[ 8] = path_node[11]
#nav_node[ 9] = path_node[10]
#DEST_NODE_ID = 10

#Manual path planning 2
NUM_NAV_NODE = 11
nav_node = np.zeros(NUM_NAV_NODE_MAX*5)
nav_node.shape = (NUM_NAV_NODE_MAX,5)
nav_node[ 0] = path_node[ 0]
nav_node[ 1] = path_node[18]
nav_node[ 2] = path_node[19]
nav_node[ 3] = path_node[28]
nav_node[ 4] = path_node[ 4]
nav_node[ 5] = path_node[ 8]
nav_node[ 6] = path_node[22]
nav_node[ 7] = path_node[21]
nav_node[ 8] = path_node[27]
nav_node[ 9] = path_node[26]
nav_node[10] = path_node[10]
DEST_NODE_ID = 10

#Manual path planning 3
#NUM_NAV_NODE =   2
#nav_node = np.zeros(NUM_NAV_NODE_MAX*5)
#nav_node.shape = (NUM_NAV_NODE_MAX,5)
#nav_node[ 0] = path_node[ 0]
#nav_node[ 1] = path_node[10]
#nav_node[ 2] = path_node[19]
#nav_node[ 3] = path_node[28]
#nav_node[ 4] = path_node[ 4]
#nav_node[ 5] = path_node[ 8]
#nav_node[ 6] = path_node[22]
#nav_node[ 7] = path_node[21]
#nav_node[ 8] = path_node[10]
#nav_node[ 9] = path_node[10]
##nav_node[10] = path_node[10]
#DEST_NODE_ID = 10

###########################################################
#Vehicle setting
###########################################################
#Vehicle size
veh_size = [10, 10]  #Length, width
scan_range = 20      #the distance that the valid sensor can detect obstacel
#Vehicle movement distance delta in each step
DELTA_X = 1
DELTA_Y = 1

###########################################################
#Destination definition
###########################################################
dest_size = 50  #Length, width


###########################################################
# IPS setting
###########################################################
#IPS_MOVE_SLEEP = 0.01 #0.01 second = 10 ms
IPS_MOVE_SLEEP = 0.05 #50 ms
IPS_CNT_MAX = 200  # 2 seconds
flag_reach = False


###########################################################
# Navigation definition
###########################################################
DIFF_MAX = 12


animation = Tk()

class mouse_click:
  def __init__(self, root):
    #print ("==> __init__")
    self.root = root
    self.mouse_stop = False
    self.mouse_pressed = False
    #f = tkinter.Frame(width=100, height=100, background="bisque")
    f = tkinter.Frame(width=30, height=30, background="red")
    #f.pack(padx=100, pady=100)
    #f = Label(root, text="Red", bg="red", fg="white")
    f.pack(padx=10, pady=5, fill=X)
    f.bind("<ButtonPress-1>", self.OnMouseDown)
    f.bind("<ButtonRelease-1>", self.OnMouseUp)

  def do_work(self):
    #print ("==> do_work")
    x = self.root.winfo_pointerx()
    y = self.root.winfo_pointery()
    #print ("button is being pressed... %s/%s" % (x, y))

  def OnMouseDown(self, event):
    #print ("==> OnMouseDown")
    self.mouse_stop = True
    self.mouse_pressed = True
    self.poll()

  def OnMouseUp(self, event):
    #print ("==> OnMouseUp")
    self.mouse_pressed = False
    self.root.after_cancel(self.after_id)

  def poll(self):
    #print ("==> poll")
    if self.mouse_pressed:
      self.do_work()
      self.after_id = self.root.after(250, self.poll)


###########################################################
# Function: detect if a dot is on an obstacle
#           if Yes, then return True, else return False
###########################################################
def dot_in_obstacle(dot_x, dot_y, obst_x_min, obst_y_min, obst_x_max, obst_y_max):
  if(dot_x>=obst_x_min)and(dot_x<=obst_x_max):
    if(dot_y>=obst_y_min)and(dot_y<=obst_y_max):
      flg_dot_det = True
    else:
      flg_dot_det = False
  else:
    flg_dot_det = False
  #if __DBG_LINE_OVERLAP:
  #  print("==> dot_in_obstacle: dot_x, dot_y, obst_x_min, obst_y_min, obst_x_max, obst_y_max, flg_dot_det", dot_x, dot_y, obst_x_min, obst_y_min, obst_x_max, obst_y_max, flg_dot_det)
  return (flg_dot_det)
 

###########################################################
# Function: detect obstacle in a certain direction
#           If any points between the start point and the 
#           end point, are in the obstacle area, then
#           return True, else return False
###########################################################
def line_hit_obstacle(start_x, start_y, end_x, end_y, obst_x_min, obst_y_min, obst_x_max, obst_y_max):
  delta_x = end_x - start_x
  delta_y = end_y - start_y
  flg_line_hit = False

  start_x_w = start_x
  end_x_w = end_x
  if   ((start_x<end_x)and(start_y<end_y)):
    start_end_case = 0
  elif ((start_x<end_x)and(start_y>=end_y)):
    start_end_case = 1
  elif ((start_x>=end_x)and(start_y<end_y)):
    start_end_case = 2
  else:
    start_end_case = 3

  if (delta_x>=0):
    start_x_w = start_x
    end_x_w   = end_x
  else:
    start_x_w = end_x
    end_x_w   = start_x

  if (delta_y>=0):
    start_y_w = start_y
    end_y_w   = end_y
  else:
    start_y_w = end_y
    end_y_w   = start_y

  if __DBG_LINE_OVERLAP:
    print("==> line_hit_obstacle: start_end_case, start_x, start_y, end_x, end_y, obst_x_min, obst_y_min, obst_x_max, obst_y_max", start_end_case, start_x, start_y, end_x, end_y, obst_x_min, obst_y_min, obst_x_max, obst_y_max)
      
  if (delta_x!=0):
    tan_angle = delta_y/delta_x
    flg_line_hit = False
    if __DBG_LINE_OVERLAP:
      print("==> line_hit_obstacle: start_x, start_y, end_x, end_y, delta_x, delta_y, tan_angle", start_x, start_y, end_x, end_y, delta_x, delta_y, tan_angle)
    
    for pos_x in range (start_x_w, end_x_w):
    #for pos_x in range (start_x, 96):
      delta_dyn_x = abs(pos_x)-abs(start_x)
      delta_dyn_x = abs(delta_dyn_x)
      #if (start_end_case==0)or(start_end_case==):
      #  delta_dyn_x = pos_x - start_x
      #else
      #  delta_dyn_x = pos_x - start_x
      delta_dyn_x = int(round(delta_dyn_x))
      delta_dyn_y = delta_dyn_x * tan_angle
      delta_dyn_y = abs(delta_dyn_y)
      #Note: the (0,0) is located at the top left corner in this coordinate grid
      if (start_end_case==0)or(start_end_case==2):
        pos_y = start_y + delta_dyn_y
      else:
        pos_y = start_y - delta_dyn_y
      if (pos_y<0):
        pos_y = 0
        print("==> FATAL: line_hit_obstacle: pos_y <0!!!!!")
      flg_dot_det = dot_in_obstacle(pos_x, pos_y, obst_x_min, obst_y_min, obst_x_max, obst_y_max)
      if __DBG_LINE_OVERLAP:
        print("==> line_hit_obstacle: start_end_case:pos_x, pos_y, obst_x_min, obst_y_min, obst_x_max, obst_y_max, flg_dot_det:", start_end_case, pos_x, pos_y, obst_x_min, obst_y_min, obst_x_max, obst_y_max, flg_dot_det)
      if (flg_dot_det==True):
        flg_line_hit = True
        break;
  else:
    pos_x = start_x
    for pos_y in range (start_y_w, end_y_w):
      flg_dot_det = dot_in_obstacle(pos_x, pos_y, obst_x_min, obst_y_min, obst_x_max, obst_y_max)
      if __DBG_LINE_OVERLAP:
        print("==> line_hit_obstacle: start_end_case:pos_x, pos_y, obst_x_min, obst_y_min, obst_x_max, obst_y_max, flg_dot_det:", start_end_case, pos_x, pos_y, obst_x_min, obst_y_min, obst_x_max, obst_y_max, flg_dot_det)
      if (flg_dot_det==True):
        flg_line_hit = True
        break;
  return (flg_line_hit)
  

###########################################################
# Function: using vehicle's sensor scan range dimension
#           to decide if there is obstacle in 8 directions.
#           Output is in bitwise direction format
###########################################################
def obstacle_report(veh_x0, veh_y0, veh_x1, veh_y1, range_x0, range_y0, range_x1, range_y1):
  #if (__DBG_RANGE_FINDER==True):
  #  print ('==> Info: range[x0, y0,x1,y1]=', range_x0, range_y0, range_x1, range_y1)
  det_ptn = 0
  
  #########################################################
  #Function step 1: all obstacles detection
  #########################################################
  for obs_idx in range(0, NUM_OBSTACLE):
    obst_x_min  = min(obstacle[obs_idx][0], obstacle[obs_idx][2])
    obst_y_min  = min(obstacle[obs_idx][1], obstacle[obs_idx][3])
    obst_x_max  = max(obstacle[obs_idx][0], obstacle[obs_idx][2])
    obst_y_max  = max(obstacle[obs_idx][1], obstacle[obs_idx][3])

    rang_x_min  = min(range_x0, range_x1)
    rang_y_min  = min(range_y0, range_y1)
    rang_x_max  = max(range_x0, range_x1)
    rang_y_max  = max(range_y0, range_y1)
    rang_x_mid = (range_x0 + range_x1)/2
    rang_y_mid = (range_y0 + range_y1)/2


    rang_x_min  = int(rang_x_min)
    rang_y_min  = int(rang_y_min)
    rang_x_max  = int(rang_x_max)
    rang_y_max  = int(rang_y_max)
    rang_x_mid  = int(rang_x_mid)
    rang_y_mid  = int(rang_y_mid)

    veh_x_min   = min(veh_x0, veh_x1)
    veh_y_min   = min(veh_y0, veh_y1)
    veh_x_max   = max(veh_x0, veh_x1)
    veh_y_max   = max(veh_y0, veh_y1)
    veh_x_mid   = (veh_x0 + veh_x1)/2
    veh_y_mid   = (veh_y0 + veh_y1)/2

    veh_x_min   = int(veh_x_min)
    veh_y_min   = int(veh_y_min)
    veh_x_max   = int(veh_x_max)
    veh_y_max   = int(veh_y_max)
    veh_x_mid   = int(veh_x_mid)
    veh_y_mid   = int(veh_y_mid)

    if (__DBG_RANGE_FINDER==True):
      print("==> Obstacle: x/y_min, x/y_max:", obst_x_min, obst_y_min, obst_x_max, obst_y_max)
      print("==> range x/y_min, x/y_max, x/y_mid:", rang_x_min, rang_y_min, rang_x_max, rang_y_max, rang_x_mid, rang_y_mid)
      print("==> veh x/y_min, x/y_max, x/y_mid:", veh_x_min , veh_y_min,  veh_x_max,  veh_y_max,  veh_x_mid,  veh_y_mid)
    #Try Dir: F
    flg_line_hit = line_hit_obstacle(veh_x_mid, veh_y_min, rang_x_mid, rang_y_min, obst_x_min, obst_y_min, obst_x_max, obst_y_max)
    if (flg_line_hit==True):
      det_ptn = det_ptn | DIR_BIT_F
    if __DBG_LINE_OVERLAP:
      print("==> obstacle_report: test DIR: F, result: 0x%X"%(det_ptn))
    #Try Dir: FL
    flg_line_hit = line_hit_obstacle(veh_x_min, veh_y_min, rang_x_min, rang_y_min, obst_x_min, obst_y_min, obst_x_max, obst_y_max)
    if (flg_line_hit==True):
      det_ptn = det_ptn | DIR_BIT_FL
    if __DBG_LINE_OVERLAP:
      print("==> obstacle_report: test DIR: FL, result: 0x%X"%(det_ptn))
    #Try Dir: L
    flg_line_hit = line_hit_obstacle(veh_x_min, veh_y_mid, rang_x_min, rang_y_mid, obst_x_min, obst_y_min, obst_x_max, obst_y_max)
    if (flg_line_hit==True):
      det_ptn = det_ptn | DIR_BIT_L
    if __DBG_LINE_OVERLAP:
      print("==> obstacle_report: test DIR: L, result: 0x%X"%(det_ptn))
    #Try Dir: BL
    flg_line_hit = line_hit_obstacle(veh_x_min, veh_y_max, rang_x_min, rang_y_max, obst_x_min, obst_y_min, obst_x_max, obst_y_max)
    if (flg_line_hit==True):
      det_ptn = det_ptn | DIR_BIT_BL
    if __DBG_LINE_OVERLAP:
      print("==> obstacle_report: test DIR: BL, result: 0x%X"%(det_ptn))
    #Try Dir: B
    flg_line_hit = line_hit_obstacle(veh_x_mid, veh_y_max, rang_x_mid, rang_y_max, obst_x_min, obst_y_min, obst_x_max, obst_y_max)
    if (flg_line_hit==True):
      det_ptn = det_ptn | DIR_BIT_B
    if __DBG_LINE_OVERLAP:
      print("==> obstacle_report: test DIR: B, result: 0x%X"%(det_ptn))
    #Try Dir: BR
    flg_line_hit = line_hit_obstacle(veh_x_max, veh_y_max, rang_x_max, rang_y_max, obst_x_min, obst_y_min, obst_x_max, obst_y_max)
    if (flg_line_hit==True):
      det_ptn = det_ptn | DIR_BIT_BR
    if __DBG_LINE_OVERLAP:
      print("==> obstacle_report: test DIR: BR, result: 0x%X"%(det_ptn))
    #Try Dir: R
    flg_line_hit = line_hit_obstacle(veh_x_max, veh_y_mid, rang_x_max, rang_y_mid, obst_x_min, obst_y_min, obst_x_max, obst_y_max)
    if (flg_line_hit==True):
      det_ptn = det_ptn | DIR_BIT_R
    if __DBG_LINE_OVERLAP:
      print("==> obstacle_report: test DIR: R, result: 0x%X"%(det_ptn))
    #Try Dir: FR
    flg_line_hit = line_hit_obstacle(veh_x_max, veh_y_min, rang_x_max, rang_y_min, obst_x_min, obst_y_min, obst_x_max, obst_y_max)
    if (flg_line_hit==True):
      det_ptn = det_ptn | DIR_BIT_FR
    if __DBG_LINE_OVERLAP:
      print("==> obstacle_report: test DIR: FR, result: 0x%X"%(det_ptn))

    if (__DBG_RANGE_FINDER==True):
      print("==> obstacle_report: obstacle[%d]: %4d,%4d,%4d,%4d; x/y_min, x/y_max: %4d/%4d,%4d/%4d; det_ptn: 0x%2X"% 
      (obs_idx, obstacle[obs_idx][0], obstacle[obs_idx][1], obstacle[obs_idx][2], obstacle[obs_idx][3], 
      obst_x_min, obst_y_min, obst_x_max, obst_y_max, det_ptn))
      
   
  #########################################################
  #Function step 2: Map grip boundary detection
  #########################################################
  map_width_limit = map_size[0] - 1
  map_verti_limit = map_size[1] - 1
  if (range_x0<1):
    det_ptn = det_ptn | DIR_BIT_L
    det_ptn = det_ptn | DIR_BIT_FL
    det_ptn = det_ptn | DIR_BIT_BL
    if (range_y0<1):
      det_ptn = det_ptn | DIR_BIT_F
    elif (range_y1>map_verti_limit):
      det_ptn = det_ptn | DIR_BIT_B
    #else:
  elif (range_x1>map_width_limit):
    det_ptn = det_ptn | DIR_BIT_R
    det_ptn = det_ptn | DIR_BIT_FR
    det_ptn = det_ptn | DIR_BIT_BR
    if (range_y0<1):
      det_ptn = det_ptn | DIR_BIT_F
    elif (range_y1>map_verti_limit):
      det_ptn = det_ptn | DIR_BIT_B
  else:
    if (range_y0<1):
      det_ptn = det_ptn | DIR_BIT_F
      det_ptn = det_ptn | DIR_BIT_FL
      det_ptn = det_ptn | DIR_BIT_FR
    elif (range_y1>map_verti_limit):
      det_ptn = det_ptn | DIR_BIT_B
      det_ptn = det_ptn | DIR_BIT_BL
      det_ptn = det_ptn | DIR_BIT_BR
      
  if (__DBG_RANGE_FINDER==True):
    print("==> obstacle_report: final det_ptn: 0x%X"%(det_ptn))
  return (det_ptn)

###########################################################
# Function: Calculate the vehicle sensor scan dimension
###########################################################
def veh_range_calc():
  veh_range_dimen[0] = veh_dimen[0] - scan_range
  veh_range_dimen[1] = veh_dimen[1] - scan_range
  veh_range_dimen[2] = veh_dimen[2] + scan_range
  veh_range_dimen[3] = veh_dimen[3] + scan_range

###########################################################
# Function: decide the vehicle moving direction based on the
#           vehicle's current coordinate and destimation's
#           coordinate
###########################################################
def dir_ips_calc(veh_x, veh_y, dest_x, dest_y):
  distance = 0
  distance_1 = 0
  if __DBG_IPS_CALC:
    print("==> dir_ips_calc: veh_x, veh_y, dest_x, dest_y:", veh_x, veh_y, dest_x, dest_y)
  diff_x = abs(dest_x - veh_x)
  diff_y = abs(dest_y - veh_y)
  dir_ips = DIR_ID_NULL
  if (dest_x>veh_x) and (diff_x>DIFF_MAX):
    if (dest_y>veh_y) and (diff_y>DIFF_MAX):
      dir_ips = DIR_ID_BR
    elif (dest_y<veh_y) and (diff_y>DIFF_MAX):
      dir_ips = DIR_ID_FR
    else:
      dir_ips = DIR_ID_R
  elif (dest_x<veh_x) and (diff_x>DIFF_MAX):
    if (dest_y>veh_y) and (diff_y>DIFF_MAX):
      dir_ips = DIR_ID_BL
    elif (dest_y<veh_y) and (diff_y>DIFF_MAX):
      dir_ips = DIR_ID_FL
    else:
      dir_ips = DIR_ID_L
  else:
    distance_1 = diff_x*diff_x + diff_y*diff_y
    distance = math.sqrt(distance_1)
    if (distance<DIFF_MAX):
      dir_ips = DIR_ID_STOP
    else:
      if (dest_y>veh_y):
        dir_ips = DIR_ID_B
      else:
        dir_ips = DIR_ID_F
      

  if __DBG_IPS_CALC:
    print("==> dir_ips_calc: dir_ips result:%d, diff_x/y: %d/%d, distance_1:%d, distance:%d"%(dir_ips, diff_x, diff_y, distance_1, distance))
  
  #if (dir_ips==DIR_ID_STOP):
  #  for i in range(0, MAX_NUMBER):
  #    time.sleep(0.1)  #for multi-thread communication
  #    print("==> dir_ips_calc: stop!")
  return (dir_ips)


def veh_reach_dest(veh_dimen, dest_x, dest_y):
  dest_x_min  = dest_x-20
  dest_y_min  = dest_y-20
  dest_x_max  = dest_x+20
  dest_y_max  = dest_y+20

  veh_x_min   = min(veh_dimen[0], veh_dimen[2])
  veh_y_min   = min(veh_dimen[1], veh_dimen[3])
  veh_x_max   = max(veh_dimen[0], veh_dimen[2])
  veh_y_max   = max(veh_dimen[1], veh_dimen[3])
  flg_reach = False
  if (veh_dimen[0]>dest_x_min)and(veh_dimen[0]>dest_x_min):
    flg_reach = True
  return(flg_reach)



###########################################################
# Program initialization
###########################################################
#Vehicle dimension
veh_dimen = np.zeros(4)
veh_range_dimen = np.zeros(4)
dest_dimen = np.zeros(4)

print("SEP200 Navigation Algorithm Simulation")
print("==> Step 1: Parameter setting:")
print("==> Obstacle dimension definitions:")
print(obstacle)

map_grid = Canvas(animation, width=map_size[0], height=map_size[1])
map_grid.grid()
map_grid.pack()
map_grid.create_line( 0            ,             0, map_size[0]-1,             0, fill="DarkOrchid4", width=10)
map_grid.create_line( 0            ,             0,             0, map_size[1]-1, fill="DarkOrchid4", width=10)
map_grid.create_line( 0            , map_size[1]-1, map_size[0]-1, map_size[1]-1, fill="DarkOrchid4", width=10)
map_grid.create_line( map_size[0]-1,             0, map_size[0]-1, map_size[1]-1, fill="DarkOrchid4", width=10)

#Create vehicle
veh_dimen[0] = veh_coordi_init[0]
veh_dimen[1] = veh_coordi_init[1]
veh_dimen[2] = veh_coordi_init[0] + veh_size[0]
veh_dimen[3] = veh_coordi_init[1] + veh_size[1]
veh_range_calc()

veh_range = map_grid.create_rectangle( veh_range_dimen[0], veh_range_dimen[1], veh_range_dimen[2], veh_range_dimen[3], fill="#999999")
veh = map_grid.create_rectangle(veh_dimen[0], veh_dimen[1], veh_dimen[2], veh_dimen[3], fill="blue")

#Create destination
dest_dimen[0] = dest_coordi[0]
dest_dimen[1] = dest_coordi[1]
dest_dimen[2] = dest_coordi[0] + dest_size
dest_dimen[3] = dest_coordi[1] + dest_size

dest = map_grid.create_oval(dest_dimen[0], dest_dimen[1], dest_dimen[2], dest_dimen[3], fill="green")

print ("==> veh_dimen: ", veh_dimen)
print ("==> veh_range_dimen: ", veh_range_dimen)
#Create obstacles
for i in range(0, NUM_OBSTACLE):
  map_grid.create_rectangle(obstacle[i][0], obstacle[i][1], obstacle[i][2], obstacle[i][3], fill="gray")
  map_grid.create_text(obstacle[i][2]-20, obstacle[i][3]-10, font=("Purisa", 14), text="OB%d"%(i)) 
#map_grid.create_polygon(10, 10, 10, 10, 60, 50, 35, 80)

#Create map lane
#map_grid.create_line( 40, 750, 1150, 750, fill="lawn green", width=1)
for i in range(0, NUM_PATH):
  #map_grid.create_line(path_edge[i][0], path_edge[i][1], path_edge[i][2], path_edge[i][3], fill="lawn green", width=1)
  id_node_start = int(path_edge_list[i][0])
  id_node_end   = int(path_edge_list[i][1])
  #print("XXXXX", id_node_start, id_node_end)
  #id_node_start = 0
  #id_node_end   = 13
  map_grid.create_line(path_node[id_node_start][0], path_node[id_node_start][1], path_node[id_node_end][0], path_node[id_node_end][1], fill="lawn green", width=1)
  #text_pos_x = (path_edge[i][0] + path_edge[i][2])/2
  #text_pos_y = (path_edge[i][1] + path_edge[i][3])/2
  text_pos_x = (path_node[id_node_start][0] + path_node[id_node_end][0])/2
  text_pos_y = (path_node[id_node_start][1] + path_node[id_node_end][1])/2
  map_grid.create_text(text_pos_x, text_pos_y, font=("Purisa", 14), text="path%d"%(i)) 

#Draw map nodes
for i in range(0, NUM_PATH_NODE):
  map_grid.create_oval(path_node[i][0]-5, path_node[i][1]-5, path_node[i][0]+5, path_node[i][1]+5, fill="burlywood2")
  map_grid.create_text(path_node[i][0], path_node[i][1], font=("Purisa",14), text="Node%d"%(i)) 


###########################################################
# Mouse click response
###########################################################
app = mouse_click(map_grid)

###########################################################
# Navigation
###########################################################
#Default: move forward
adj_x, adj_y = 0, -DELTA_Y
dir_curr = DIR_ID_F
dir_prev = DIR_ID_F
det_ptn_prev = DIR_BIT_NULL

cnt_ips = 0
systick = 0

mouse_pressed_prev = False


if __PATH_PLAN_EN:
  map_grid.create_text(150, 20, font=("Purisa", 22), text="Path Planning is Enabled!", fill = 'red')
  
  #########################################################
  #Dijkstra's algorithm to decide the routing path, i.e.,
  #the list of the Turning Points
  #########################################################
  id_root = 0
  graph_nav = graph_construct(NUM_PATH_NODE, NUM_PATH, path_node, path_edge_list, id_root)
  #graph_nav[0][10]=34
  if __DBG_GRAPH_MAIN:
    print("main: graph_nav = ")
    for i in range(0, NUM_PATH_NODE):
      for j in range(0, NUM_PATH_NODE):
        print("%4d "%(graph_nav[i][j]), end=''),
      print("//Node: ",i)

  graph_plan = path_dijkstra(NUM_PATH_NODE, graph_nav, path_node, id_root)

  if __DBG_GRAPH_MAIN:
    print("dijkstra output: ")
    for i in range(0, NUM_PATH_NODE):
      print("Node: %d"%i, " %4d "%(path_node[i][0]), "%4d "%(path_node[i][1]), "%4d "%(path_node[i][2]), "%4d "%(path_node[i][3]))


  print("The Shortest path result by Dijkstra's algorithm: the node IDs are listed below:")
  print(graph_plan)

  #########################################################
  #Highlight the selected Turning Points
  #########################################################
  for i in range(0, NUM_PATH_NODE):
    idx = int(graph_plan[i])
    pos_x = path_node[idx][0]
    pos_y = path_node[idx][1]
    map_grid.create_oval(pos_x-10, pos_y-10, pos_x+10, pos_y+10, fill="red")
    map_grid.create_text(pos_x+20, pos_y+20, font=("Purisa", 14), text="T.P.%d"%(i))
    if (idx==ID_NODE_E):
      break
  #num_node = enq_graph_vertex(graph_plan)

  #########################################################
  #Decide the number of Turning Points and place the selected
  #Nodes (path_node) to the Turning Point array (nav_node)
  #########################################################
  num_node = 0
  graph_size = len(graph_plan)
  for i in range(0, graph_size):
    id_select_node = int(graph_plan[num_node])
    print(id_select_node)
    nav_node[ num_node ] = path_node[ id_select_node]
    num_node = num_node + 1
    if id_select_node == DEST_NODE_ID:
      print("The last node is the destination!")
      break
  
else:
  map_grid.create_text(150, 20, font=("Purisa", 22), text="Path Planning is Disabled!", fill = 'red')
  num_node = NUM_NAV_NODE

#Draw the decided navigation path nodes
if (__PATH_PLAN_EN==False):
  for i in range(0, NUM_NAV_NODE):
    map_grid.create_oval(nav_node[i][0]-10, nav_node[i][1]-10, nav_node[i][0]+10, nav_node[i][1]+10, fill="red")

#########################################################
# Show the vehicle movement animation
#########################################################
for i in range(0, num_node):
  while (flag_reach==False):
    if (app.mouse_stop==False):
      run_check = True
    else:
      if ((mouse_pressed_prev==True)and(app.mouse_pressed==False)):
        run_check = True
      else:
        run_check = False
    mouse_pressed_prev = app.mouse_pressed
    time.sleep(0.01)  #for multi-thread communication
    
    if (run_check==True):
      if (__DBG_MAIN): 
        print ("//-------------------------------------------------------------------------------------------------------------------//")
  
      systick = systick + 1
      if cnt_ips == IPS_CNT_MAX:
        cnt_ips = 0
      else:
        cnt_ips = cnt_ips + 1
      time.sleep(IPS_MOVE_SLEEP)
      
      veh_center_x = (veh_dimen[0] + veh_dimen[2])/2
      veh_center_y = (veh_dimen[1] + veh_dimen[3])/2
      dest_center_x = (dest_dimen[0] + dest_dimen[2])/2
      dest_center_y = (dest_dimen[1] + dest_dimen[3])/2
      
      #Range Finder: decide the detection obstacle pattern
      det_ptn_curr = obstacle_report(veh_dimen[0], veh_dimen[1], veh_dimen[2], veh_dimen[3], 
                     veh_range_dimen[0], veh_range_dimen[1], veh_range_dimen[2], veh_range_dimen[3])
      #dir_ips = dir_ips_calc(veh_center_x, veh_center_y, dest_center_x, dest_center_y)
      dir_ips = dir_ips_calc(veh_center_x, veh_center_y, nav_node[i][0], nav_node[i][1])
      
      if (dir_ips!=DIR_ID_STOP):
        #Kernal of navigation
        dir_fianl = dir_final_core(dir_ips, dir_curr, dir_prev, systick, det_ptn_curr, det_ptn_prev)
        #dir_fianl = dir_path_manual(dir_ips, dir_curr, dir_prev, systick, det_ptn_curr, det_ptn_prev, path)
        if (__DBG_MAIN):
          print ("==> main(%d): veh_center_x/y:%d/%d, dest_center_x/y:%d/%d, dir_ips:%d, dir_curr:%d, dir_prev:%d, det_ptn_curr:0x%X,det_ptn_prev:0x%X, dir_final=%d"% 
          (systick,veh_center_x, veh_center_y, dest_center_x, dest_center_y, 
          dir_ips,dir_curr, dir_prev, det_ptn_curr, det_ptn_prev, dir_fianl))
        
        det_ptn_prev = det_ptn_curr
        
        if (dir_curr != dir_fianl):
          dir_prev = dir_curr #???
          dir_curr = dir_fianl
        
        if (dir_fianl ==DIR_ID_F):
          adj_x = 0
          adj_y = -DELTA_Y
        elif (dir_fianl ==DIR_ID_FL):
          adj_x = -DELTA_X
          adj_y = -DELTA_Y
        elif (dir_fianl ==DIR_ID_L):
          adj_x = -DELTA_X
          adj_y = 0
        elif (dir_fianl ==DIR_ID_BL):
          adj_x = -DELTA_X
          adj_y = DELTA_Y
        elif (dir_fianl ==DIR_ID_B):
          adj_x = 0
          adj_y = DELTA_Y
        elif (dir_fianl ==DIR_ID_BR):
          adj_x = DELTA_X
          adj_y = DELTA_Y
        elif (dir_fianl ==DIR_ID_R):
          adj_x = DELTA_X
          adj_y = 0    
        elif (dir_fianl ==DIR_ID_FR):
          adj_x = DELTA_X
          adj_y = -DELTA_Y
        elif (dir_fianl ==DIR_ID_STOP):  
          adj_x = 0
          adj_y = 0
          print("==> Reach destination!")
        else:
          print("==> Fatal error 1! dir_fianl ID is invalid: %d"%(dir_fianl))
        
        if (__DBG_MAIN):
          print ("==> main(%d): adj_x/y:%d/%d"%(systick,adj_x, adj_y))
        
        #Update veh and range dimension
        veh_dimen[0] = veh_dimen[0] + adj_x
        veh_dimen[1] = veh_dimen[1] + adj_y
        veh_dimen[2] = veh_dimen[2] + adj_x
        veh_dimen[3] = veh_dimen[3] + adj_y
        
        veh_range_calc()
        
        #flag_reach = veh_reach_dest(veh_dimen, nav_node[i][0], nav_node[i][1])
      else:
        print("==> main: Vehicle reaches a Turning Point!")
        break
    
    #################################################
    #Update the figure
    #################################################  
    map_grid.move(veh, adj_x, adj_y)
    map_grid.delete(veh)
    map_grid.delete(veh_range)
    veh_range = map_grid.create_rectangle( veh_range_dimen[0], veh_range_dimen[1], veh_range_dimen[2], veh_range_dimen[3], fill="#999999")
    veh = map_grid.create_rectangle(veh_dimen[0], veh_dimen[1], veh_dimen[2], veh_dimen[3], fill="blue")
    animation.update()
    

mainloop()
