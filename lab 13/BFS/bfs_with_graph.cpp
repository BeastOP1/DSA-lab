#include <iostream>
using namespace std;

const int MAX = 100;

struct Node {
    int vertex;
    Node* next;
    Node(int v) : vertex(v), next(nullptr) {}
};

struct QueueNode {
    int vertex;
    QueueNode* next;
    QueueNode(int v) : vertex(v), next(nullptr) {}
};

class Queue {
private:
    QueueNode *front, *rear;
public:
    Queue() : front(nullptr), rear(nullptr) {}
    
    void enqueue(int v) {
        QueueNode* newNode = new QueueNode(v);
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }
    
    int dequeue() {
        if (front == nullptr) return -1;
        QueueNode* temp = front;
        front = front->next;
        if (front == nullptr) rear = nullptr;
        int v = temp->vertex;
        delete temp;
        return v;
    }
    
    bool isEmpty() {
        return front == nullptr;
    }
};

class GraphBFS {
private:
    Node* adjList[MAX];
    bool visited[MAX];
    int numVertices;
    
public:
    GraphBFS(int vertices) : numVertices(vertices) {
        for (int i = 0; i < numVertices; i++) {
            adjList[i] = nullptr;
            visited[i] = false;
        }
    }
    
    void insert_graph(int u, int v) {
        Node* newNode = new Node(v);
        newNode->next = adjList[u];
        adjList[u] = newNode;
    }
    
    void bfs_graph(int start) {
        // Reset visited array
        for (int i = 0; i < numVertices; i++) {
            visited[i] = false;
        }
        
        Queue q;
        visited[start] = true;
        q.enqueue(start);
        
        while (!q.isEmpty()) {
            int current = q.dequeue();
            cout << current << " ";
            
            Node* temp = adjList[current];
            while (temp != nullptr) {
                int adjVertex = temp->vertex;
                if (!visited[adjVertex]) {
                    visited[adjVertex] = true;
                    q.enqueue(adjVertex);
                }
                temp = temp->next;
            }
        }
    }
};

int main() {
    GraphBFS g(4);
    g.insert_graph(0, 1);
    g.insert_graph(0, 2);
    g.insert_graph(1, 2);
    g.insert_graph(2, 0);
    g.insert_graph(2, 3);
    g.insert_graph(3, 3);

    cout << "BFS Traversal of Graph (starting from vertex 2):\n";
    g.bfs_graph(2);
    cout << endl;
    
    return 0;
}