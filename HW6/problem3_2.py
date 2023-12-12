INF = float('inf')

def repeated_squaring(initial_matrix):
    num_vertices = len(initial_matrix)
    d = [[[0 for _ in range(num_vertices)] for _ in range(num_vertices)] for _ in range(5)]

    # Initialize D(0)
    for i in range(num_vertices):
        for j in range(num_vertices):
            d[0][i][j] = initial_matrix[i][j]

    # Calculate D(2)
    for k in range(1, 3):
        for i in range(num_vertices):
            for j in range(num_vertices):
                d[k][i][j] = min(d[k - 1][i][j], d[k - 1][i][k - 1] + d[k - 1][k - 1][j])

    # Calculate D(4)
    for k in range(3, 5):
        for i in range(num_vertices):
            for j in range(num_vertices):
                d[k][i][j] = min(d[k - 1][i][j], d[k - 1][i][k - 1] + d[k - 1][k - 1][j])

    return d[2], d[4]

# Initial matrix (D(0))
initial_matrix = [
    [0, 5, 9, INF, 3],
    [INF, 0, 8, INF, INF],
    [INF, 1, 0, 7, 4],
    [INF, INF, INF, 0, INF],
    [11, INF, INF, 6, 0]
]

D_2, D_4 = repeated_squaring(initial_matrix)

print("D(2):")
for row in D_2:
    print(row)

print("\nD(4):")
for row in D_4:
    print(row)
