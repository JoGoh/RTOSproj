###############################################################################
#Project  : PID controller simulation                                         #
#File     : pid_run.py                                                        #
#Details  : PID controller simulation, with simulated motor.                  #
#Author   : Liang Tang                                                        #
#--------------------------------------------------------------------------   #
#Ver    Author      Date        Changes                                       #
#--------------------------------------------------------------------------   #
#1.0    Liang       2017-03-13  Class demo for PID simulation.                #
###############################################################################
import numpy as np
import matplotlib.pyplot as plt
import random

class PID:
  """
  Discrete PID control
  """
  #########################################################
  #PID.__init__ function is the PID class initialization. #
  #########################################################
  def __init__(self, P=2.0, I=0.0, D=1.0, Derivator=0, Integrator=0, Integrator_max=500, Integrator_min=-500):
    self.Kp=P
    self.Ki=I
    self.Kd=D
    self.Derivator=Derivator
    self.Integrator=Integrator
    self.Integrator_max=Integrator_max
    self.Integrator_min=Integrator_min

    self.set_point=0.0
    self.error=0.0
    
    print "==> PID.__init__: Kp=",self.Kp,"Ki=",self.Ki,"Kd=",self.Kd,"Derivator=",self.Derivator
    print "==>               Integrator=",self.Integrator,"I_max=",self.Integrator_max,"I_min=",self.Integrator_min

  #########################################################
  #The PID.update function is the detail PID controller   #
  #implementation:                                        #
  #1. Get error by subtracting the reading speed from the #
  #   set speed;                                          #
  #2. Calculate the propertion component: P_value;        #
  #3. Calculate the derivative component: D_value;        #
  #4. Calculate the integral   component: I_value;        #
  #5. PID result = P_value + D_value + I_value;           #
  #########################################################
  def update(self,current_value, tick):
    """
    Calculate PID output value for given reference input and feedback
    """

    #######################################################
    #Step 1: error = target speed - reading speed         #
    #######################################################
    self.error = self.set_point - current_value

    #######################################################
    #Step 2: P_value = Kp * error                         #
    #######################################################
    self.P_value = self.Kp * self.error

    #######################################################
    #Step 3: derivative = current error - previous error  #
    #        D_value = Kd * derivative                    #
    #######################################################
    self.D_value = self.Kd * ( self.error - self.Derivator)
    self.Derivator = self.error

    #######################################################
    #Step 4: integral = accumulation of all errors,       #
    #        bounded by the MAX and MIN range             #
    #        I_value = Ki * integral                      #
    #######################################################
    self.Integrator = self.Integrator + self.error
    if self.Integrator > self.Integrator_max:
      self.Integrator = self.Integrator_max
    elif self.Integrator < self.Integrator_min:
      self.Integrator = self.Integrator_min

    self.I_value = self.Integrator * self.Ki

    #######################################################
    #Step 5: PID result = P_value + D_value + I_value     #
    #######################################################
    PID = self.P_value + self.I_value + self.D_value
    print "==> Time tick:",tick,"error=",self.error,"P_value",self.P_value,"I_value=",self.I_value, "D_value=",self.D_value,"PID=",PID
    return PID

  #########################################################
  #PID.setPoint function is the target speed setting.     #
  #########################################################
  def setPoint(self,set_point):
    """
    Initilize the setpoint of PID
    """
    self.set_point = set_point
    self.Integrator=0
    self.Derivator=0


class MOTOR:

  #########################################################
  #MOTOR.__init__ is the MOTOR class initialization.      #
  #########################################################
  def __init__(self, pid_result, pwm_duty, factor_distort):
    self.pid_result=pid_result
    self.pwm_duty=pwm_duty
    self.factor_distort=factor_distort

  #########################################################
  #MOTOR.run is the function to convert the PID to speed, #
  #with the effect of noise.                              #
  #########################################################
  def run(self, pid, noise, tick):
    adjust = pid/8;
    self.pwm_duty = self.pwm_duty + adjust;
    self.speed = self.pwm_duty*(1-self.factor_distort) + noise
    print "==> MOTOR.run: Time tick:",tick,"pid=",pid,"adjust=",adjust,"noise=",noise,"pwm_duty=",self.pwm_duty,"speed=",self.speed
    return self.speed

###############################################################################
#Here is the main function!                                                   #
###############################################################################

###########################################################
#Program parameters                                       #
###########################################################
MAX_POINT =10000             #Number of sampling points
noise_mean =0                #Noise 2 mean/average value
noise_sigma = 2              #Noise 2 sigma
target_speed = 40            #The target speed
factor_distort = 0.3         #The simulated motor mechanical distortation
kp = 3.0                     #PID Kp parameter
ki = 0.4                     #PID Ki parameter
kd = 1.2                     #PID Kd parameter

###########################################################
#Plotting variables.                                      #
###########################################################
t = np.arange(0., MAX_POINT, 1)
speed_plot = np.empty(MAX_POINT)
pid_plot = np.empty(MAX_POINT)
noise_plot = np.empty(MAX_POINT)
noise1_plot = np.empty(MAX_POINT)
noise2_plot = np.empty(MAX_POINT)
error_plot = np.empty(MAX_POINT)
hist_grade = 50


###########################################################
#Algorithm initialization.                                #
###########################################################
tick = 0
pid_result = 0
m=MOTOR(pid_result, target_speed, factor_distort)
p=PID(kp, ki, kd)
p.setPoint(target_speed)

###########################################################
#Forever loop for the algorithm running.                  #
###########################################################
while True:
  
  noise = 0;
  noise1 = 0
  noise2 = 0
  noise1 = random.uniform(-1, 1);
  noise2 = np.random.normal(noise_mean, noise_sigma, 1)
  noise = noise1 + noise2
  noise_plot[tick] = noise
  noise1_plot[tick] = noise1
  noise2_plot[tick] = noise2
  
  #########################################################
  #Based on the PID result and noise, generate speed.     #
  #########################################################
  speed = m.run(pid_result, noise, tick)
  error_plot[tick] = target_speed - speed
  speed_plot[tick] = speed

  #########################################################
  #Based on the observed speed, generate PID result.      #
  #########################################################
  pid_result = p.update(speed, tick)
  pid_plot[tick] = pid_result
  tick=tick+1
  if (tick==MAX_POINT):
    break;

###########################################################
#Plot various figures.                                    #
###########################################################
plt.figure(1)
plt.subplot(231)
plt.title('Observed Speed')
plt.grid(True)
plt.plot(t, speed_plot, 'r--')

plt.subplot(232)
plt.title('PID Result')
plt.grid(True)
plt.plot(t, pid_plot, 'g--')

plt.subplot(233)
plt.title('Noise 1 + Noise 2')
plt.grid(True)
plt.plot(t, noise_plot, 'b--')

plt.subplot(234)
plt.title('Error = Target - observed')
plt.grid(True)
plt.plot(t, error_plot, 'k')

plt.subplot(235)
plt.title('Noise 1 Distribution')
count, bins, ignored = plt.hist(noise1_plot, hist_grade, normed=True)

plt.subplot(236)
plt.title('Noise 2 Distribution')
count, bins, ignored = plt.hist(noise2_plot, hist_grade, normed=True)
distribute = 1/(noise_sigma * np.sqrt(2 * np.pi)) *np.exp( - (bins - noise_mean)**2 / (2 * noise_sigma**2) )
plt.plot(bins, distribute,linewidth=2, color='r')


plt.show()
