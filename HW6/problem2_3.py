# from collections import defaultdict

# # Function to perform Depth-First Search (DFS)
# def dfs(graph, node, visited):
#     visited.add(node)
#     for neighbor in graph[node]:
#         if neighbor not in visited:
#             dfs(graph, neighbor, visited)

# # Function to find connected components considering all arcs as undirected edges
# def undirected_connected_components(graph):
#     visited = set()
#     components = 0
#     for node in graph:
#         if node not in visited:
#             dfs(graph, node, visited)
#             components += 1
#     return components

# # Example directed graph represented as an adjacency list
# # Consider all arcs as undirected edges
# # Ensure to add both directions for each edge
# graph = {
#     '1': ['5', '6', '12'],
#     '2': ['3', '5', '9'],
#     '3': ['2', '4', '6', '7', '10'],  # Ensure that 'D' is a key in the graph dictionary
#     '4': ['3', '7', '14'],     # Add an empty list for node 'D'
#     '5': ['1', '2', '8'],
#     '6': ['1', '3', '7', '9', '13'],
#     '7': ['3', '6', '4'],
#     '8': ['5', '9'],
#     '9': ['2', '8', '6'],
#     '10': ['3', '12', '11', '13'],
#     '11': ['10', '14'],
#     '12': ['10', '1'],
#     '13': ['10', '6'],
#     '14': ['4', '11']
# }

# # Find the number of connected components in the modified undirected graph
# num_connected_components = undirected_connected_components(graph)

# # Output the number of connected components
# print(f"Number of Connected Components in the Modified Graph: {num_connected_components}")
from collections import defaultdict

# Function to perform Depth-First Search (DFS)
def dfs(graph, node, visited, component):
    visited.add(node)
    component.append(node)
    for neighbor in graph[node]:
        if neighbor not in visited:
            dfs(graph, neighbor, visited, component)

# Function to find connected components and their sizes
def undirected_connected_components(graph):
    visited = set()
    components = []
    for node in graph:
        if node not in visited:
            component = []
            dfs(graph, node, visited, component)
            components.append(component)
    return components

# Example directed graph represented as an adjacency list
# Consider all arcs as undirected edges
# Ensure to add both directions for each edge
graph = {
    '1': ['5', '6', '12'],
    '2': ['3', '5', '9'],
    '3': ['2', '4', '6', '7', '10'],  # Ensure that 'D' is a key in the graph dictionary
    '4': ['3', '7', '14'],     # Add an empty list for node 'D'
    '5': ['1', '2', '8'],
    '6': ['1', '3', '7', '9', '13'],
    '7': ['3', '6', '4'],
    '8': ['5', '9'],
    '9': ['2', '8', '6'],
    '10': ['3', '12', '11', '13'],
    '11': ['10', '14'],
    '12': ['10', '1'],
    '13': ['10', '6'],
    '14': ['4', '11']
}

# Find the connected components in the modified undirected graph
connected_components = undirected_connected_components(graph)

# Output the number of connected components
print(f"Number of Connected Components in the Modified Graph: {len(connected_components)}")

# Output the sizes of connected components
print("Sizes of Connected Components:")
for component in connected_components:
    print(f"Component: {component}, Size: {len(component)}")
