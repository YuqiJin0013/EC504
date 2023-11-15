import matplotlib.pyplot as plt
import numpy as np

# BFS_time = [8.26218, 0.00695167, 0.00475633, 0.000727125, 0.00014425, 4.725e-05, 0.00012275, 2.3e-05]
# DFS_time = [8.28385, 0.00585667, 0.00468333, 0.000551333, 0.000130375, 3.8e-05, 0.000108458, 1.4583e-05]
# connected_components = [32774, 767, 509, 193, 50, 15, 11, 2]

# '''graph 1'''

# plt.figure(figsize=(8, 6))

# plt.semilogy(connected_components, BFS_time, marker='o', linestyle='-', label='BFS Time')
# plt.semilogy(connected_components, DFS_time, marker='o', linestyle='-', label='DFS Time')

# plt.xlabel('Connected Components')
# plt.ylabel('time of execution (log scale)')
# plt.title('Time vs Connected Components for BFS and DFS')
# plt.legend()
# plt.grid(True)
# plt.show()

'''graph 2'''
connected_components = [32774, 767, 509, 193, 50, 15, 11, 2]
time_complexity = [131068, 1538, 2056, 382, 284, 70, 442, 22] # O(|V|+|E|)

plt.figure(figsize=(8, 6))

plt.plot(connected_components, time_complexity, marker='o', linestyle='-', color='b')

plt.xlabel('Connected Components')
plt.ylabel('Sum of Edges and Vertices')
plt.title('Sum of Edges and Vertices vs Connected Components')
plt.grid(True)
plt.show()


