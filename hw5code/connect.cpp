#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;

/***********************************************************
Given two arrays: FirstVertex pointing to the EdgeList with destination
node for an undirected graph G(V,E).

The input file begins with number of vertices (V = |V|)
and number of edges (E =|E|) and the list of value for

int FirstVertex[V+1]
int EdgeList[E+1]

The vertices(nodes) are numbered 0,..,|V| -1.  The last entry
FirstVertex[V] = E pointing to  EdgeList[E] = -1;
represented as a null

You are to compute the number of the connected components.

************************************************************/

// Here is remendary Queue give at end of file.
typedef struct Queue
{
    int capacity;
    int size;
    int front;
    int rear;
    int *elements;
} Queue;

// Funcs for Queue
Queue *createQueue(int maxElements);
void Enqueue(Queue *Q, int element);
int Dequeue(Queue *Q);

// build the Stack
typedef struct Stack {
    int capacity;
    int size;
    int top;
    int *elements;
} Stack;
// Funcs for Stack
Stack *createStack(int maxElements);
void Push(Stack *S, int element);
int Pop(Stack *S);

int find_connected_components_BFS(int *FirstVertex, int V, int *EdgeList, int E);
void BFS(Queue *Q, int *Found, int *FirstVertex, int V, int *EdgeList,int E);

// Funcs for DFS
int find_connected_components_DFS(int *FirstVertex, int V, int *EdgeList, int E);
void DFS(Stack *S, int *Found, int *FirstVertex, int V, int *EdgeList,int E);

void PrintAdjacencyListFormat(int *FirstVertex, int V, int *EdgeList, int E);
void printArray(int *arr, int size);

// helper functions
int findMin(int *arr, int n);
int findMax(int *arr, int n);
void replace(int *arr, int size, int old_val, int new_val);
bool isany(int *arr, int size, int val);


int main(int argc, char *argv[]) {

    chrono::time_point<chrono::steady_clock> start, stop;
    chrono::duration<double> difference_in_time;
    double difference_in_seconds_BFS; // Holds the final run time for BFS
    double difference_in_seconds_DFS; // Holds the final run time for DFS

    ifstream infile1;
    int V;
    int E;
    int NumberCC_BFS;
    int NumberCC_DFS;

    infile1.open(argv[1]);
    if (!infile1) {
        cout << "Error opening file " << endl;
        return -1;
    }

    infile1 >> V;
    infile1 >> E;

    int *FirstVertex = new int[V + 1];
    for (int i = 0; i < V + 1; i++)
        infile1 >> FirstVertex[i]; //  Note: FirstVertex[V] = E  fake extra link

    int *EdgeList = new int[E + 1];
    for (int i = 0; i < E + 1; i++)
        infile1 >> EdgeList[i]; // Note  EdgeList[E] = -1;  is null flag

    infile1.close();

#if 1 // set to 1 to debug
    cout << endl
         << "A print in Adjacency  List form to help with Debugging! " << endl;
    PrintAdjacencyListFormat(FirstVertex, V, EdgeList, E);
#endif

    /* Find NumberCC_BFS   */
    start = chrono::steady_clock::now();
    NumberCC_BFS = find_connected_components_BFS(FirstVertex, V, EdgeList, E);
    stop = chrono::steady_clock::now();
    difference_in_time = stop - start;
    difference_in_seconds_BFS = double(difference_in_time.count());

    /* Find NumberCC_DFS   */
    start = chrono::steady_clock::now();
    NumberCC_DFS = find_connected_components_DFS(FirstVertex, V, EdgeList, E);
    stop = chrono::steady_clock::now();
    difference_in_time = stop - start;
    difference_in_seconds_DFS = double(difference_in_time.count());

    // Begin output file : DO NOT CHANGE
    ofstream outfile(strcat(argv[1], "_out"));
    outfile << difference_in_seconds_BFS << endl;
    outfile << NumberCC_BFS << endl;
    outfile << difference_in_seconds_DFS << endl;
    outfile << NumberCC_DFS << endl;
    // End output file

    return 0;
}

int find_connected_components_BFS(int *FirstVertex, int V, int *EdgeList, int E) {
    int NumberCC_BFS = 0;
    int *Found = new int[V];
    fill_n(Found, V, -1);
    Queue *Q = createQueue(V);

    // Write code to interate over BFS to find all connected compoents
    int number_iters = 0;
    while (isany(Found, V, -1)) {
        BFS(Q, Found, FirstVertex, V, EdgeList, E);
        number_iters++;
    }

    cout << "Found: ";
    printArray(Found, V);
    cout << endl;
    cout << "n iterations: " << number_iters << endl;

    // Count the number of different components
    bool* components = new bool[V];
    fill_n(components, V, false);
    int number_components = 0;
    int this_component;
    for (int i = 0; i<V; i++) {
        this_component = Found[i];
        if (!components[this_component]) {
            components[this_component] = true;
            number_components++;
        }
    }
    NumberCC_BFS = number_components;

    delete[] Found;
    free(Q->elements);
    free(Q);

    return NumberCC_BFS;
}

int find_connected_components_DFS(int *FirstVertex, int V, int *EdgeList, int E) {
    int NumberCC_DFS = 0;
    int *Found = new int[V];
    fill_n(Found, V, -1);
    Stack *S = createStack(V);

    // Write code to interate over BFS to find all connected compoents.
    int number_iters = 0;
    while (isany(Found, V, -1)) {
        DFS(S, Found, FirstVertex, V, EdgeList, E);
        number_iters++;
    }

    cout << "Found: ";
    printArray(Found, V);
    cout << endl;
    cout << "n iterations: " << number_iters << endl;

    // Count the number of unique components
    bool* components = new bool[V];
    fill_n(components, V, false);
    int number_components = 0;
    int this_component;
    for (int i = 0; i<V; i++) {
        this_component = Found[i];
        if (!components[this_component]) {
            components[this_component] = true;
            number_components++;
        }
    }
    NumberCC_DFS = number_components;

    delete[] Found;
    free(S->elements);
    free(S);
    return NumberCC_DFS;
}

/* QUEUE FUCTIONS */
Queue *createQueue(int maxElements) {
    /* Create a Queue */
    Queue *Q;
    Q = (Queue *)malloc(sizeof(Queue));
    /* Initialise its properties */
    Q->elements = (int *)malloc(sizeof(int) * maxElements);
    Q->size = 0;
    Q->capacity = maxElements;
    Q->front = 0;
    Q->rear = -1;
    /* Return the pointer */
    return Q;
}

void Enqueue(Queue *Q, int element) {
    /* If the Queue is full, we cannot push an element into it as there is no space for it.*/
    if (Q->size == Q->capacity) {
        printf("Queue is Full\n");
    }
    else {
        Q->size++;
        Q->rear = Q->rear + 1;
        /* As we fill the queue in circular fashion */
        if (Q->rear == Q->capacity) {
            Q->rear = 0;
        }
        /* Insert the element in its rear side */
        Q->elements[Q->rear] = element;
    }
    return;
}

int Dequeue(Queue *Q) {
    int element = -1;
    /* If Queue size is zero then it is empty. So we cannot pop */
    if (Q->size == 0) {
        //              printf("Queue is Empty\n");
        return element;
    }
    /* Removing an element is equivalent to incrementing index of front by one */
    else {
        element = Q->elements[Q->front];
        Q->size--;
        Q->front++;
        /* As we fill elements in circular fashion */
        if (Q->front == Q->capacity)
        {
            Q->front = 0;
        }
    }
    return element;
}

Stack *createStack(int maxElements) {
    /* Create a Stack */
    Stack *S;
    S = (Stack *)malloc(sizeof(Stack));
    /* Initialise its properties */
    S->elements = (int *)malloc(sizeof(int) * maxElements);
    S->size = 0;
    S->capacity = maxElements;
    S->top = -1;
    return S;
}

void Push(Stack *S, int element) {
    if (S->top == S->capacity - 1) {
        printf("Stack is Full\n");
    } else {
        S->size++;
        S->top++;
        S->elements[S->top] = element;
    }
}

int Pop(Stack *S) {
    int element = -1;
    if (S->size == 0) {
        return element;
    } else {
        S->size--;
        element = S->elements[S->top];
        S->top--;
    }
    return element;
}

void PrintAdjacencyListFormat(int *FirstVertex, int V, int *EdgeList, int E) {
    int v;
    int e;
    cout << "V = " << V << "  E = " << E << endl;
    for (v = 0; v < V; v++)
    {
        cout << endl;
        cout << v << ": ";

        for (e = FirstVertex[v]; e < FirstVertex[v + 1]; e++)
            cout << EdgeList[e] << "-> ";

        cout << "nil";
    }

    cout << endl;
    cout << v << " : ";
    cout << EdgeList[e] << " That's Edge List  nil  Folks " << endl;
}

int findMin(int *arr, int n) {
    int min = arr[0];
    for (int i=0; i<n; i++)
    {
        if (arr[i] < min)
            min = arr[i];
    }
    return min;
}

int findMax(int *arr, int n) {
    int max = arr[0];
    for (int i=0; i<n; i++)
    {
        if (arr[i] > max)
            max = arr[i];
    }
    return max;
}

void replace(int *arr, int size, int old_val, int new_val) {
    for (int i=0; i<size; i++) {
        if (arr[i] == old_val)
            arr[i] = new_val;
    }
    return;
}

bool isany(int *arr, int size, int val) {
    bool output = false;
    for (int i=0; i<size; i++) {
        if (arr[i] == val) {
            output = true;
            break;
        }
    }
    return output;
}

void printArray(int *arr, int size) {
    for (int i=0; i<size; i++) {
        cout << arr[i] << " ";
    }
    return;
}

void BFS(Queue *Q, int *Found, int *FirstVertex, int V, int *EdgeList, int E) {
    // Determine the number to assign for these next components
    int last_component = findMax(Found, V);
    int this_component = last_component + 1;

    // Find the next unvisited node
    bool start_found = false;
    int v = 0;
    int start_node;
    while (!start_found) {
        if (Found[v] == -1) {
            start_node = v;
            start_found = true;
        }
        else {
            v++;
        }
    }

    // Add the first node the the Queue
    Enqueue(Q, start_node);

    Found[start_node] = this_component;

    int number_neighboring_nodes;
    while (Q->size > 0) {
        int current = Dequeue(Q);
        int neigbor_start_idx = FirstVertex[current];

        // Count number of nodes current 
        if (FirstVertex[current] == FirstVertex[current+1] && FirstVertex[current+1] != -1) {
            number_neighboring_nodes = 0;
        }
        else if (current + 1 == V) {
            number_neighboring_nodes = E - FirstVertex[current];
        }
        else {
            number_neighboring_nodes = FirstVertex[current+1] - FirstVertex[current];
        }
        // Add neighbor nodes to the queue
        for (int i = 0; i < number_neighboring_nodes; i++) {
            int neighbor = EdgeList[neigbor_start_idx + i];

            if (Found[neighbor] == -1) {
                Enqueue(Q, neighbor);
                Found[neighbor] = this_component;
            }
            else if (Found[neighbor] != this_component) {
                // Make all nodes the neighbor is connected to part of this component
                replace(Found, V, Found[neighbor], this_component);
            }
        }
    }
}

void DFS(Stack *S, int *Found, int *FirstVertex, int V, int *EdgeList, int E) {
    // Determine the number to assign for these next components
    int last_component = findMax(Found, V);
    int this_component = last_component + 1;

    // Find the next unvisited node
    bool start_found = false;
    int v = 0;
    int start_node;
    while (!start_found) {
        if (Found[v] == -1) {
            start_node = v;
            start_found = true;
        }
        else {
            v++;
        }
    }
    // Add the first node to the Queue
    Push(S, start_node);

    // Mark the start node
    Found[start_node] = this_component;

    int number_neighboring_nodes;
    while (S->size > 0) {
        int current = Pop(S);
        int neigbor_start_idx = FirstVertex[current];

        // Count number of nodes current
        if (FirstVertex[current] == FirstVertex[current+1] || FirstVertex[current+1] == -1) {
            number_neighboring_nodes = 0;
        }
        else if (current+1 == V) {
            number_neighboring_nodes = E - FirstVertex[current];
        }
        else {
            number_neighboring_nodes = FirstVertex[current + 1] - FirstVertex[current];
        }

        // Add neighbor nodes to the Stack
        for (int i = 0; i < number_neighboring_nodes; i++) {
            int neighbor = EdgeList[neigbor_start_idx + i];

            if (Found[neighbor] == -1) {
                Push(S, neighbor);
                Found[neighbor] = this_component;
            }
            else if (Found[neighbor] != this_component) {
                // Make all nodes the neighbor is connected to part of this component
                replace(Found, V, Found[neighbor], this_component);
            }
        }
    }
}