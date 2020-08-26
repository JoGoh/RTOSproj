#*****************************************************************************
#@Project  : SEP250
#@File     : path_plan.py
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

import math
import copy
import numpy as np

###########################################################
#External global variable
###########################################################
MAX_NUMBER = 0x7FFFFFFF

#Define the position of D and PI elements
POS_D = 2
POS_PI = 3
POS_STA = 4

###########################################################
#Private global variable
###########################################################
#__DBG_GRAPH_MAIN=True
__DBG_GRAPH_MAIN=False

#__DBG_GRAPH_CONSTRUC=True
__DBG_GRAPH_CONSTRUC=False

#__DBG_GRAPH_INIT=True
__DBG_GRAPH_INIT=False


def graph_construct(num_v, num_e, list_v, list_e, id_root):
  graph = np.zeros(num_v*num_v)
  graph.shape = (num_v,num_v) 
  for i in range(0, num_v):
    for j in range(0, num_v):
      for k in range(0, num_e):
        if (i==j):
          graph[i][j] = int(0)
          if __DBG_GRAPH_CONSTRUC:
            print("i=%2d, j=%2d, k=%2d, list_e[k][0]=%4d, list_e[k][1]=%4d,graph[i][j]=%4d"%(i,j,k,list_e[k][0],list_e[k][1],graph[i][j]))
        elif ((i==list_e[k][0])and(j==list_e[k][1])) or ((i==list_e[k][1])and(j==list_e[k][0])):
          delta_x = abs(list_v[i][0] - list_v[j][0])
          delta_y = abs(list_v[i][1] - list_v[j][1])
          distance1 = delta_x*delta_x + delta_y*delta_y
          distance = math.sqrt(distance1)
          graph[i][j] = int(distance)
          if __DBG_GRAPH_CONSTRUC:
            print("i=%2d, j=%2d, k=%2d, list_e[k][0]=%4d, list_e[k][1]=%4d,graph[i][j]=%4d"%(i,j,k,list_e[k][0],list_e[k][1],graph[i][j]))
          break
        else:
          graph[i][j] = int(-1)
          if __DBG_GRAPH_CONSTRUC:
            print("i=%2d, j=%2d, k=%2d, list_e[k][0]=%4d, list_e[k][1]=%4d,graph[i][j]=%4d"%(i,j,k,list_e[k][0],list_e[k][1],graph[i][j]))
  
  return (graph)


###########################################################
# Function: Shortest path algorithm: INITIALIZE-SINGLE-SOURCE(G,s)
# Algo    : Cormen's Algorithm book: Section 24.0, Page 648
#           for each vertex v in G.V     //
#             v.d = infinity             //d: shortest-path estimate
#             v.pi = NIL                 //pi: predecessor
#           s.d = 0                      //
###########################################################
def path_init_single_source(num_v, graph_in, path_node, id_root):
  for i in range(0, num_v):
    path_node[i][POS_D] = MAX_NUMBER
    path_node[i][POS_PI] = -1
  
  path_node[id_root][POS_D] = 0
  return (path_node)

############################################################
## Function: Calculate distance between virtex u and v
############################################################
#def path_calc_dist(graph_v, id_u, id_v):
#  start_x = graph_v[id_u].[0]
#  start_y = graph_v[id_u].[1]
#  end_x   = graph_v[id_v].[0]
#  end_y   = graph_v[id_v].[1]
#  delta_x = abs(end_x - start_x)
#  delta_y = abs(end_y - start_y)
#  w1 = pow(delta_x, 2) + pow(delta_x, 2)
#  w = sqrt(w1)
#
###########################################################
# Function: Shortest path algorithm: RELAX(u,v,w)
# Algo    : Cormen's Algorithm book: Section 24.0, Page 649
#           if v.d>u.d+w(u,v)
#             v.d = u.d + w(u,v)         //Calculate the new shortest-path estimate
#             v.pi = u                   //find the new predecessor
###########################################################
def path_relax(vertex_list, id_u, id_v, w, vertex_q_list):
  flg_relax = False
  if (vertex_q_list[id_v][POS_STA]==0):
    u_plus_w = vertex_list[id_u][POS_D] + w
    if (vertex_list[id_v][POS_D]>=u_plus_w):
      vertex_list[id_v][POS_D] = u_plus_w
      vertex_list[id_v][POS_PI] = id_u
      flg_relax = True
    if __DBG_GRAPH_MAIN:
      print("In path_relax: id_u=%d, id_v=%d, w=%d, vertex_list[id_u][POS_D]=%d, u_plus_w=%d, vertex_list[id_v][POS_D]=%d"%(id_u, id_v, w, vertex_list[id_u][POS_D], u_plus_w, vertex_list[id_v][POS_D]))
  return (flg_relax)

###########################################################
# Function: Shortest path algorithm: EXTRACT-MIN(vertex)
# Algo    : Cormen's Algorithm book: Section 24.3, Page 658
#           Find the Min. vertext
###########################################################
def path_extrac_min(num_v, vertex_q_list, flg_retreat):
  v_id = -1
  v_value = MAX_NUMBER
  for i in range(0, num_v):
    if (vertex_q_list[i][POS_STA]==0):
      if (vertex_q_list[i][POS_D]<v_value):
        v_value = vertex_q_list[i][POS_D]
        v_id = i
        vertex_q_list[i][POS_STA] = 1  #Indicate has been extracted
    elif (vertex_q_list[i][POS_STA]==2):
      if flg_retreat:
        if (vertex_q_list[i][POS_D]<v_value):
          v_value = vertex_q_list[i][POS_D]
          v_id = i
          vertex_q_list[i][POS_STA] = 1  #Indicate has been extracted
      

  #Clear the same distance nodes:
  #the nodes with same Min. distance, should be removed
  for i in range(0, num_v):
    if (vertex_q_list[i][POS_D]<MAX_NUMBER):
      if (vertex_q_list[i][POS_D]==v_value):
        vertex_q_list[i][POS_STA] = 2  #Indicate has been extracted

  ##Shift the remaining
  #num_v_m1 = num_v -1
  #print("in path_extrac_min:", num_v, num_v_m1, v_id)
  #if (num_v>1):
  #  if (v_id<num_v_m1):
  #    for i in range(v_id, num_v_m1):
  #      vertex_q_list[i] = vertex_q_list[i+1]
  return(v_id)

      

###########################################################
# Function: Shortest path algorithm: EXTRACT-MIN(vertex)
# Algo    : Cormen's Algorithm book: Section 24.3, Page 658
#           INITIALIZE-SINGLE-SOURCE(G,s)
#           S=NIL
#           Q=G.V
#           while Q != NIL
#             u=EXTRACT-MIN(Q)
#             S=S union {u}
#             for each vertex v in G.Adj[u]
#               RELAX(u,v,w)
###########################################################
def path_dijkstra(num_v, graph_in, vertex_list, id_root):
  #Step 1: init
  vertex_list_init = path_init_single_source(num_v, graph_in, vertex_list, id_root)
  #print("vertex_list_init @pos 1",vertex_list_init)
  
  if __DBG_GRAPH_INIT:
    for i in range(0, num_v):
      #print("path_node[%2d]: x=%4d, y=%4d, d=%8d, pi=%8d "%(vertex_list[i][0], vertex_list[i][1], vertex_list[i][2], vertex_list[i][3]))
      print("Dijkstra: after init: path_node[%2d]: x=%4d, y=%4d, d=%8d, pi=%8d "%(i, vertex_list[i][0], vertex_list[i][1], vertex_list[i][2], vertex_list[i][3]))

  #Step 2: create empty S graph
  graph_s = np.zeros(num_v*num_v)
  graph_s.shape = (num_v,num_v)
  vertex_list_s = np.zeros(num_v)
  
  vertex_list_adj = np.zeros(num_v)
  
  
  #Step 3: Q=G.V
  graph_v_q = copy.copy(vertex_list_init)
  len_q = num_v

  #Step 4: continue if Q is not empty
  idx = 0
  
  #len_q = 1 #test
  flg_relax_all = True
  flg_retreat = False
  while (len_q>0):
    #if len_q<28:
    #  break
      
    #Step 5: extract the Min. from Q
    if __DBG_GRAPH_MAIN:
      print("////////////////////////////////////////////////////////////")
      print("//Starting of the while loop...")
      print("////////////////////////////////////////////////////////////")
    if __DBG_GRAPH_INIT:
      print("1st in the loop: len_q=%d"%(len_q))
    if flg_relax_all==True:
      #print("vertex_list_init @pos 2",vertex_list_init)
      #id_u = path_extrac_min(len_q, graph_v_q)
      id_u = path_extrac_min(num_v, graph_v_q, flg_retreat)
      #print("vertex_list_init @pos 3",vertex_list_init)
    
      if __DBG_GRAPH_INIT:
        print("Dijkstra: path_extrac_min result: id_u=%d, len_q=%d"%(id_u,len_q))
        #print("Dijkstra: path_extrac_min result: graph_v_q:",graph_v_q)
        for i in range(0, num_v): 
          print("graph_v_q: Row[%2d]: %5d, %5d, %10d, %5d, %2d"%(i, graph_v_q[i][0], graph_v_q[i][1],graph_v_q[i][2],graph_v_q[i][3],graph_v_q[i][4]))

      vertex_list_s[idx] = id_u
      idx = idx +1

    len_q = len_q -1

    #Step X: find v from G.Adj[u]
    num_adj = 0
    for j in range(0, num_v):
      if (graph_in[id_u][j]>0):
        vertex_list_adj[num_adj] = j
        num_adj = num_adj + 1
   
    if __DBG_GRAPH_INIT:
      for j in range(0, num_adj):
        print("==> After finding adj: adj[%2d]:%3d "%(j, vertex_list_adj[j]))
      print(" ")
    
    
    #print("graph_v_q before relax:", graph_v_q)
    flg_relax_all = False
    for i in range(0, num_adj):
      id_v = vertex_list_adj[i]
      id_v = int(id_v)
      w = graph_in[id_u][id_v]
      
      
      flg_relax = path_relax(graph_v_q, id_u, id_v, w, graph_v_q)
      if flg_relax:
        flg_relax_all = True
      if __DBG_GRAPH_INIT:
        print("Dijkstra: after relax: num_adj=%d, i=%d, vertex_list[%d].d=%d, pi=%d"%(num_adj, i, id_v, graph_v_q[id_v][POS_D], graph_v_q[id_v][POS_PI]))

    #Need retreate to the previous node
    if (flg_relax_all==False):
      #Remove the S list
      idx = idx -1
      id_u = vertex_list_s[idx-1]
      id_u = int(id_u)
      if __DBG_GRAPH_MAIN:
        print("Warning: no relax here: retrieve the parent node: id_u=%d, idx=%d"%(id_u, idx))
    
    if __DBG_GRAPH_MAIN:  
      print("graph_v_q after relax:")
      for i in range(0, num_v): 
        print("graph_v_q: Row[%2d]: %5d, %5d, %10d, %5d, %2d"%(i, graph_v_q[i][0], graph_v_q[i][1],graph_v_q[i][2],graph_v_q[i][3],graph_v_q[i][4]))


  
  if __DBG_GRAPH_INIT:
    print("Dijkstra final result: ", vertex_list_s)
  return(vertex_list_s)

#def enq_graph_vertex(graph_v):
#  num_v = 10
#  return(num_v)