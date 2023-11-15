def create_forward_star_representation(vertex_number, array_edge):
    forward_star_representation = []

    for i in range(len(vertex_number) - 1):
        start_index = vertex_number[i]
        end_index = vertex_number[i + 1]
        edges = array_edge[start_index - 1:end_index - 1]
        forward_star_representation.append(edges)

    return forward_star_representation

# Given forward star representation data
vertex_number = [1, 3, 4, 5, 7, 8, 12, 12, 14, 14, 15, 17]
array_edge = [2, 6, 6, 7, 3, 7, 8, 5, 8, 9, 10, 9, 11, 9, 9, 10, -1]

# Create forward star representation
forward_star_representation = create_forward_star_representation(vertex_number, array_edge)

# Print the forward star representation
for i, edges in enumerate(forward_star_representation, start=1):
    print(f"Vertex {i}: {edges}")
    

