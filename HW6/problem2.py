from collections import defaultdict

# Depth-First Search to identify connected components
def dfs(graph, node, visited, component):
    visited.add(node)
    component.append(node)
    for neighbor in graph[node]:
        if neighbor not in visited:
            dfs(graph, neighbor, visited, component)

# Function to find directed connected components
def directed_connected_components(graph):
    visited = set()
    components = []
    for node in graph:
        if node not in visited:
            component = []
            dfs(graph, node, visited, component)
            components.append(component)
    
    return components

# Example directed graph represented as an adjacency list
graph = {
    '1': ['5', '6', '12'],
    '2': ['3', '5', '9'],
    '3': ['6', '7', '10'],  # Ensure that 'D' is a key in the graph dictionary
    '4': ['3', '7', '14'],     # Add an empty list for node 'D'
    '5': ['8'],
    '6': ['9', '13'],
    '7': ['6'],
    '8': [],
    '9': ['8'],
    '10': ['11', '12'],
    '11': ['14'],
    '12': [],
    '13': ['10'],
    '14': []
}

# Find the directed connected components
connected_components = directed_connected_components(graph)

# Output the number and size of connected components
print(f"Number of Directed Connected Components: {len(connected_components)}")
print("Sizes of Connected Components:")
for component in connected_components:
    print(f"Component: {component}, Size: {len(component)}")
