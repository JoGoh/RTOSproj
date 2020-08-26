
import time
import math
import numpy as np
from gv import*


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
#Private global variable
###########################################################
#__DBG_DIR_MAIN=True
__DBG_DIR_MAIN=False

#__DBG_NAVIGATE = True
__DBG_NAVIGATE = False

NUM_DIR = 8
NUM_DIR_M1 = 7
NAV_TIME_DELTA = 3
#NAV_TIME_DELTA = 18


def dir_inq_left(dir_in):
  dir_out = dir_in +1
  if (dir_out>=8):
    dir_out = dir_out - 8
    
  return(dir_out)

def dir_inq_right(dir_in):
  dir_out = dir_in -1
  if (dir_out<0):
    dir_out = dir_out + 8
    
  return(dir_out)


def dir_check_clear(dir_test, det_ptn):
  dir_bit = 1<<dir_test
  dir_check_mid = dir_bit & det_ptn
  
  dir_left = dir_inq_left(dir_test)
  dir_bit = 1<<dir_left
  dir_check_left = dir_bit & det_ptn
  
  dir_right = dir_inq_right(dir_test)
  dir_bit = 1<<dir_right
  dir_check_right = dir_bit & det_ptn
  
  #if ((dir_check_mid==0)and(dir_check_left==0)and(dir_check_right==0)):
  if ((dir_check_mid==0)):
    flg_dir_clear = True
  else:
    flg_dir_clear = False
    
  return(flg_dir_clear)

def dir_round(dir_in):
  if (dir_in>=8):
    dir_out = dir_in - 8
  elif (dir_in<0):
    dir_out = dir_in + 8
  else:
    dir_out = dir_in
  
  return(dir_out)


###########################################################
# Function: decide the vehicle moving direction based on the
#           vehicle's current coordinate and destimation's
#           coordinate
#           If the IPS recommended direction is 7, or FR,
#           the final direction try order should be:
#           F, R, FL, BR, L, B, BL
###########################################################
def dir_final_core(dir_ips, dir_curr, dir_prev, tim_tick, det_ptn_curr, det_ptn_prev):
  if (__DBG_NAVIGATE==True):
    print ("==> dir_final_core: dir_ips=%d, dir_curr=%d, dir_prev=%d, tim_tick=%d, det_ptn_curr=0x%X, det_ptn_prev=0x%X"
    %(dir_ips, dir_curr, dir_prev, tim_tick, det_ptn_curr, det_ptn_prev))
  
  global gv_time_prev
  global gv_flg_time_delta
  
  if (tim_tick>=gv_time_prev):
    time_delta = tim_tick - gv_time_prev
  else:
    time_delta = 1   #fixed value
  
  #gv_flg_time_delta = False

  dir_final = DIR_ID_NULL
  dir_done = False
  #dir_try = dir_ips
  #Only process if the suggested DIR from IPS is not STOP
  if (dir_ips<DIR_ID_STOP):
    #if (time_delta>=NAV_TIME_DELTA):
    if ((det_ptn_curr!=det_ptn_prev)or(det_ptn_curr==DIR_BIT_NULL)):
      gv_time_prev = tim_tick
      gv_flg_time_delta = True
      if __DBG_DIR_MAIN:
        print("=========================")

    if (__DBG_NAVIGATE==True):
      print ("==> dir_final_core: gv_time_prev:%d, time_delta:%d, gv_flg_time_delta:%s"%(gv_time_prev, time_delta, gv_flg_time_delta))


    if (__DBG_NAVIGATE==True):
      print ("==> time_delta checking:tim_tick:%d, gv_time_prev:%d, time_delta:%d"%(tim_tick,gv_time_prev,time_delta))

    #if (gv_flg_time_delta==True)and(time_delta>=NAV_TIME_DELTA):
    if (det_ptn_curr==DIR_BIT_NULL)or((gv_flg_time_delta==True)and(time_delta>=NAV_TIME_DELTA)):
    #if (gv_flg_time_delta==True):
      gv_flg_time_delta = False
      if (__DBG_NAVIGATE==True):
        print ("==> time_delta checking pass!!!!!!!!!!!!!",tim_tick,gv_time_prev,time_delta)
      #Try NUM_DIR times, use the dir_try variable to differentiate the loop
      for i in range(0, NUM_DIR):
        if (__DBG_NAVIGATE==True):
          print ("==> dir_final_core: Loop i = %d"%(i))
        flg_dir_clear = dir_check_clear(dir_ips, det_ptn_curr)
        
        if __DBG_DIR_MAIN:
          print ("==> dir_final_core: i=%d, DIR ID: IPS:%d, flg_dir_clear=%d"%(i, dir_ips, flg_dir_clear))
        
        flg_really_clear = False
        if (flg_dir_clear):
          if (dir_ips!=dir_prev):
            flg_really_clear = True
          else:
            flg_really_clear = False
            if (__DBG_NAVIGATE==True):
              print("==> dir_final_core: IPS suggested direction is clear, but it is the previous path! i=%d"%(i))
            
        if flg_really_clear:
          if (__DBG_NAVIGATE==True):
            print("==> dir_final_core: IPS suggested direction is clear: move! i=%d"%(i))
          dir_final = dir_ips
          break
          
        else:
          if (__DBG_NAVIGATE==True):
            print ("==> dir_final_core: IPS suggested direction is blocked!")
          if (dir_done ==True):
            if (__DBG_NAVIGATE==True):
              print ("==> dir_final_core: Althoug IPS suggested direction is blocked, dir_done is True! i=%d"%(i))
            break;
      
          for j in range(0, NUM_DIR_M1):
            if (__DBG_NAVIGATE==True):
              print("==> dir_final_core: DIR: %d is blocked, evaluting DIR: %d"%(i, j))
            if (j==0):
              dir_try = dir_ips + 1
              dir_try = dir_round(dir_try)
            elif (j==1):
              dir_try = dir_ips - 1
              dir_try = dir_round(dir_try)
            elif (j==2):
              dir_try = dir_ips + 2
              dir_try = dir_round(dir_try)
            elif (j==3):
              dir_try = dir_ips - 2
              dir_try = dir_round(dir_try)
            elif (j==4):
              dir_try = dir_ips + 3
              dir_try = dir_round(dir_try)
            elif (j==5):
              dir_try = dir_ips - 3
              dir_try = dir_round(dir_try)
            else:
              dir_try = dir_ips + 4
              dir_try = dir_round(dir_try)

            flg_dir_clear = dir_check_clear(dir_try, det_ptn_curr)
            if (flg_dir_clear):
              if (dir_try!=dir_prev):
                dir_final = dir_try
                dir_done = True
                if (__DBG_NAVIGATE==True):
                  print("==> dir_final_core: successful try: i=%d, j=%d, dir_try=%d, dir_final=%d"%(i,j, dir_try, dir_final))
                break
              else:
                if (__DBG_NAVIGATE==True):
                  print("==> dir_final_core: flg_dir_clear successful but dir_prev failed: i=%d, j=%d, dir_try=%d, dir_final=%d"%(i,j, dir_try, dir_final))
            #else        
            if (__DBG_NAVIGATE==True):    
              print ("==> dir_final_core: failed try: i=%d, j=%d, dir_try=%d, det_ptn_curr=%d!"%(i,j,dir_try, det_ptn_curr))
      
      dir_final_id = dir_round(dir_final)
      #if (dir_final_id!=dir_curr):
      #  gv_time_prev = tim_tick
      
      if __DBG_DIR_MAIN:
        print ("==> dir_final_core: the end: i=%d, dir_final ID=%d, dir_curr=%d"%(i, dir_final_id, dir_curr))
    else:
      #if (time_delta>=NAV_TIME_DELTA) is false: keep the current direction
      dir_final_id = dir_curr
  else:
    dir_final_id = dir_ips
    if __DBG_DIR_MAIN:
      print("==> dir_final_core: Fatal error 2: dir_ips invalid:", dir_ips)


  if (dir_final_id==DIR_ID_NULL):
    for i in range(0, MAX_NUMBER):
      time.sleep(0.1)  #for multi-thread communication
      print("==> dir_final_core: dir_final_id=DIR_ID_NULL")
  return (dir_final_id)


###########################################################
# Function: decide the vehicle moving direction based on the
#           manually planned pathes.
#           If the IPS recommended direction is 7, or FR,
#           the final direction try order should be:
#           F, R, FL, BR, L, B, BL
###########################################################
def dir_path_manual(dir_ips, dir_curr, dir_prev, tim_tick, det_ptn_curr, det_ptn_prev, path):
  dir_final_id = 1
  return (dir_final_id)