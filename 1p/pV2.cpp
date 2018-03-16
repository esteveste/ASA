// #include <stdlib.h>
// #include <stdio.h>
#include <iostream>
#include <assert.h> /* assert */
#include <vector>
#include <string>
#include <queue>
#include <forward_list>
// #include <fstream>

using namespace std;

// prototypes
class Connection;
class Node;
class Connection{
    public:
        Node* _from;
        Node* _to;
        Connection(Node* from, Node* to):_from(from),_to(to){}
};

class Node{
    private:
        int _id;

        // forward_list<int> flist1;
    public:

        int _d,_low; //for tarjan algoritm FIXME
        forward_list<Connection> _connections;
        forward_list<Connection> _connections_T; //lista para o algoritmo Tarjan
        bool visited;

        Node():_d(-1){}
        Node(int id):_id(id),_d(-1),visited(false){}
        void setId(int id){_id=id;}
        int getId(){return _id;}
        void addConnection(Node* to){
            Connection* c = new Connection(this,to);
            _connections.emplace_after(*c); //constante time
        }
        void addConnection_T(Node* to){
            Connection* c = new Connection(this,to);
            _connections_T.emplace_after(*c);
        }
};



class Graph
{
    private:
        int _n; // nr de pontos
        int _m; // nr de ligacoes

        // bool _visited[10];
    public:

        Node* _vertices; //im lazy FIXME

        Graph()
        {
            _vertices=NULL;
        }

        ~Graph()
        {
            delete[] _vertices;
        }

        void loadGraphFromStdin()
        {
            // Read input
            cin >> _n;
            cin >> _m;
            assert(_n >= 2);
            assert(_m >= 1);

            // Initializing the vertices (2N?)
            _vertices = new Node[_n];
            for (int i = 0; i < _n; i++)
            {
                _vertices[i].setId(i+1);
            }
            
            //read connections (1 indexed) (N)
            for (int i = 0; i < _m; i++)
            {
                //FIXME without input verification
                int u, v;
                cin >> u >> v;
                _vertices[u-1].addConnection(&_vertices[v-1]);
                _vertices[v-1].addConnection_T(&_vertices[u-1]); //register the transposed connection

            }
        }
    
        int getNrVertices(){return _n;}
};

class Tarjan{
    int _visited;
    Graph _g;
    queue<Node> _q;
    public:
        Tarjan(Graph g):_visited(0),_g(g){}
        void execute(){
            for (int i = 0; i < _g.getNrVertices(); i++)
            {
                if (_g._vertices[i]._d==-1)
                {
                    _tarjanVisit(_g._vertices[i]);
                }
            }
        }
        void _tarjanVisit(Node n){
            n._d=_visited;
            n._low=_visited;
            _q.push(n);
            //for each adj, max size constante
            for (int i = 0; i < n._connections.max_size(); i++)
            {
                Node v = 
                if(n._d==-1){//do we need visited?
                _tarjanVisit()
                }
            }

        }
};



void debug(){
    // test list
    // std::str
}

int main(int argc, char **argv)
{
    // Graph g;
    // g.loadGraphFromStdin();

    debug();
    queue<Node> l;
    // l.pus

    return 0;
}