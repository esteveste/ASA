#include <stdlib.h>
#include <stdio.h>
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

template<typename T> class LinkedList{

    T* _head;
    T* _tail;
    
    public:
        LinkedList():_head(NULL),_tail(NULL){}
        LinkedList(T* h):_head(h),_tail(h){}
        void add(T* e){
            // T* e = new T(c);
            if(_tail==NULL){
                _head = e;
                _tail = e;
                return;
            }

            _tail->next = e;
            _tail=e;
        }
        T* getHead(){return _head;}
        // T getNext(bool reset){}
        ~LinkedList(){
            
            T *next = _head;

            while(next) {       
                T *del = next;
                next = next->next;    
                delete del;  
            }
        }
};

template<typename T> class Element{
    /** Elemento da Lista Ligada (LinkedList)
     * */
    public:
        T* next;
        Element():next(NULL){}
};
class ElementConnection : public Element<ElementConnection>{
    public:
        Connection* c;
        ElementConnection(Connection* connection):Element(),c(connection){}
};

class ElementSCC : public Element<ElementSCC>{
    /** Elemento para a lista de componentes fortemente ligadas
     * */
    public:
        Node* smallest_id_Node;
        LinkedList<ElementSCC> sub_net_conn;
        ElementSCC(Node* n):Element(),smallest_id_Node(n){}
};

class Connection{
    public:
        Node* _from;
        Node* _to;
        Connection(Node* from, Node* to):_from(from),_to(to){}
};

class Node{
    private:
        int _id;
        LinkedList<ElementConnection> _connections;
        LinkedList<ElementConnection> _connections_T; //lista para o algoritmo Tarjan
        
    public:

        int _d,_low; //for tarjan algoritm FIXME

        Node():_d(-1){}
        Node(int id):_id(id),_d(-1){}
        void setId(int id){_id=id;}
        int getId(){return _id;}
        void addConnection(Node* to){
            Connection* c = new Connection(this,to);
            _connections.add(new ElementConnection(c));
        }
        void addConnection_T(Node* to){
            Connection* c = new Connection(this,to);
            _connections_T.add(new ElementConnection(c));
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
            // //for each adj
            // for (int i = 0; i < n._connections; i++)
            // {
                
            // }

        }
};



void debug(){
    // test list
    LinkedList<ElementConnection> l;
    Node* n1 = new Node(1);
    Node* n2 = new Node(2);
    Connection* c = new Connection(n1,n2);
    Connection* c2 = new Connection(n2,n1);
    l.add(new ElementConnection(c));
    l.add(new ElementConnection(c2));
    l.add(new ElementConnection(c));
    l.add(new ElementConnection(c2));
    l.add(new ElementConnection(c2));

    // kind a dangerous code
    ElementConnection* ec = l.getHead();
    cout<<ec->c->_from->getId()<<endl;

    delete n1;
    delete n2;
    delete c;
    delete c2;
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