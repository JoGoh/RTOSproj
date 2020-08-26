#*****************************************************************************
#@Project  : SEP250
#@File     : gv.py
#@Details  : This program simulates vehicle movement in an IPS environment, with
#            path planning.
#            This file declares and initializes global variables.
#@Author   : Liang Tang
#
#--------------------------------------------------------------------------
#@Revision  :
# Ver    Author      Date          Changes
#--------------------------------------------------------------------------
#  1.0   Liang T     2018-03-07    Initial Release
#******************************************************************************

import numpy as np

global gv_time_prev
global gv_flg_time_delta
gv_time_prev = 0
gv_flg_time_delta = False