#include<iostream>

using namespace std;


const int MAX  = 100;
struct Node
{
    int vertex;
    Node* next;
    Node(int vertex){

        this->vertex = vertex;
        next = nullptr;
    }
};

class Graph
{
private:

Node* adjencyList[MAX];
bool visted[MAX];
int numVertices;

void DFSUtil(int v){
    visted[v] = true;
    cout<< v <<" ";
    
    Node* temp = adjencyList[v];

    while (temp !=nullptr)
    {
        int adjVetex = temp->vertex;
        if(!visted[adjVetex]){

            DFSUtil(adjVetex);
        }
        temp = temp->next;
    }
    
}

public:
    Graph(int vertices = -1){

        numVertices = vertices;

        for(int i =0 ; i<vertices; i++){
            adjencyList[i] = nullptr;
            visted[i] = false;
        }
    }


    void insert(int u, int v){
        Node* newNode = new Node(v);
        newNode->next = adjencyList[u];
        adjencyList[u] = newNode;

    }

    void ApplyDFS(int start ){

        //Reset visted array
        for(int i =0 ; i<numVertices; i++){
            visted[i]  = false;
        }
        DFSUtil(start);
        cout<<endl;
    }

    ~Graph(){}
};



int main(){


    Graph g(4);

    g.insert(0,1);
    g.insert(0, 2);
    g.insert(1, 2);
    g.insert(2, 0);
    g.insert(2, 3);
    g.insert(3, 3);

    cout<<"DFS Traversal of Graph (starting from vertex 2):\n";

    g.ApplyDFS(2);
    


    return 0;
}