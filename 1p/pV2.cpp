// #include <stdlib.h>
// #include <stdio.h>
#include <iostream>
#include <assert.h> /* assert */
#include <vector>
#include <string>
#include <queue>
#include <forward_list>
#include <list>
#include <stack>

using namespace std;

//Debub
#define console(x) cout<<x<<endl
#define debug(x) cout<<"Debug: "<<x<<endl


// prototypes
class Connection;
class Node;
class SCC;

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

        int d,low; //for tarjan algoritm FIXME
        SCC* associatedSCC;
        list<Connection> _connections;
        list<Connection> _connections_T; //lista para o algoritmo Tarjan
        bool processed;

        Node():d(-1),processed(false){}
        Node(int id):_id(id),d(-1),processed(false){}
        void setId(int id){_id=id;}
        int getId(){return _id;}
        void addConnection(Node* to){
            Connection* c = new Connection(this,to);
            _connections.push_back(*c); //constante time
        }
        void addConnection_T(Node* to){
            Connection* c = new Connection(this,to);
            _connections_T.push_back(*c);
        }
};

class SCC{
    public:
        SCC():smallest_id_Node(NULL){}
        Node* smallest_id_Node;
        list<SCC*> sub_net_conn;
        void associateNode(Node* n){
            // Complexity constant
            if(smallest_id_Node==NULL || smallest_id_Node->low>n->low){
                smallest_id_Node=n;
            }
        }
        void associateSCC(SCC* s){
            //FIXME
            sub_net_conn.push_back(s);
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
    Graph* _g;
    stack<Node*> _q;
    int _scc_nr;
    public:
        Tarjan(Graph* g):_visited(1),_g(g),_scc_nr(0){}
        // Tarjan(){}

        void execute(){
            for (int i = 0; i < _g->getNrVertices(); i++)
            {
                if (_g->_vertices[i].d==-1)
                {
                    _tarjanVisit(_g->_vertices[i]);
                }
            }

        }
        void _tarjanVisit(Node& n){
            n.d=_visited;
            n.low=_visited;
            _visited++;
            _q.push(&n);
            //for each adj, constant
            for(Connection c : n._connections)
            {
                Node& v = *c._to;
                if(v.d==-1){
                    _tarjanVisit(v);
                }
                //did we already processed it?(Not a SCC,(not in stack and not visited))
                if (!v.processed)
                {
                    n.low = min(n.low,v.low);
                }
                
            }

            if(n.d == n.low){
                //Creating SCC
                SCC scc;
                //setting nr of Global SCC
                _scc_nr++;
                Node* n_q;

                debug("n: "<<&n);
                do
                {
                    n_q=_q.top();
                    debug("n_q: "<<n_q<<" l: "<<n_q->low<<" id:"<<n_q->getId()<<" d:"<<n_q->d);
                    n_q->associatedSCC=&scc;
                    n_q->processed=true;
                    scc.associateNode(n_q); //to smallest node, constant
                    _q.pop();
                    
                } while(&n!=n_q);
            }
        }

        void printResult(){
            console(_scc_nr);
        }

};





int main(int argc, char **argv)
{
    Graph g;
    // Graph& a=NULL;
    g.loadGraphFromStdin();
    // int b;
    // int& a=b;

    
    // cout<<"D"<<endl;
    // for (int i = 0; i < g.getNrVertices(); i++)
    // {
    //     cout<<g._vertices[i].getId()<<"  " <<g._vertices[i]._connections.front()._to->getId()<<endl;

    // }

    Tarjan* alg=new Tarjan(&g);
    alg->execute();
    alg->printResult();
    // debug();
    // queue<Node> l;
    // l.pus
    delete alg;
    
    return 0;
}