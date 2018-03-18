// #include <stdlib.h>
// #include <stdio.h>
#include <iostream>
#include <assert.h> /* assert */
// #include <vector>
// #include <string>
// #include <queue>
// #include <forward_list>
#include <list>
#include <stack>
#include <set>
#include <memory>

using namespace std;

//Debub
#define console(x) cout << x << endl
#define debug(x) //cout << "Debug: " << x << endl

// prototypes
class Connection;
class Node;
class SCC;

// class Connection
// {
//   public:
//     Node *_from;
//     Node *_to;
//     Connection(Node *from, Node *to) : _from(from), _to(to) {}
// };

class Node
{
  private:
    int _id;

    // forward_list<int> flist1;
  public:
    int d, low; //for tarjan algoritm FIXME
    shared_ptr<SCC> associatedSCC;
    list<Node *> _connections;
    // list<Connection> _connections_T; //lista para o algoritmo Tarjan
    bool processed;

    Node() : d(-1), processed(false) {}
    Node(int id) : _id(id), d(-1), processed(false) {}

    void setId(int id) { _id = id; }
    int getId() { return _id; }
    void addConnection(Node *to)
    {
        _connections.push_back(to); //constante time
    }
    // void addConnection_T(Node* to){
    //     Connection* c = new Connection(this,to);
    //     _connections_T.push_back(*c);
    // }
};

class SCC
{
  public:
    SCC() : smallest_id_Node(NULL) {}
    Node *smallest_id_Node;
    list<SCC *> sub_net_conn;
    void associateNode(Node *n)
    {
        // Complexity constant
        if (smallest_id_Node == NULL || smallest_id_Node->getId() > n->getId())
        {
            smallest_id_Node = n;
        }
    }
    void associateSCC(SCC *s)
    {
        //FIXME
        sub_net_conn.push_back(s);
    }
    int getId() { return smallest_id_Node->getId(); }
};

class SCC_Connection
{
  private:
    shared_ptr<SCC> _from;
    shared_ptr<SCC> _to;

  public:
    SCC_Connection(shared_ptr<SCC> from, shared_ptr<SCC> to) : _from(from), _to(to) {}

    int getSCCFrom_id() { return _from->smallest_id_Node->getId(); }
    int getSCCTo_id() { return _to->smallest_id_Node->getId(); }
    void print_output_connection()
    {
        console(getSCCFrom_id() << " " << getSCCTo_id());
    }
};
struct SCC_Con{
    int from;
    int to;
};
//compare (constant)
// bool compare_SCC_Connection(SCC_Connection *first, SCC_Connection *second)
// {
//     if (first->getSCCFrom_id() > second->getSCCFrom_id())
//         return false;
//     else if (first->getSCCFrom_id() < second->getSCCFrom_id())
//         return true;
//     else
//     {
//         if (first->getSCCTo_id() > second->getSCCTo_id())
//             return false;
//         else
//             return true;
//     }
// }
//compare (constant)
struct compare_SCC_Connection
{
    bool operator()(SCC_Con *first, SCC_Con *second)
    {
        if (first->from > second->from)
            return false;
        else if (first->from < second->from)
            return true;
        else
        {
            if (first->to > second->to)
                return false;
            else if (first->to < second->to)
                return true;
            else
                return false;
        }
    }
};
class Graph
{
  private:
    int _n; // nr de pontos
    int _m; // nr de ligacoes

    // bool _visited[10];
  public:
    Node *_vertices; //im lazy FIXME

    Graph()
    {
        _vertices = NULL;
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
            _vertices[i].setId(i + 1);
        }

        //read connections (1 indexed) (N)
        for (int i = 0; i < _m; i++)
        {
            //FIXME without input verification
            int u, v;
            cin >> u >> v;
            _vertices[u - 1].addConnection(&_vertices[v - 1]);
            // _vertices[v-1].addConnection_T(&_vertices[u-1]); //register the transposed connection
        }
    }

    int getNrVertices() { return _n; }
};


class Tarjan
{
    int _visited;
    Graph *_g;
    stack<Node *> _q;
    int _scc_nr;
    // int _scc_conn_nr;
    set<SCC_Con *, compare_SCC_Connection> _sub_net_list;

    void _tarjanVisit(Node &n)
    {
        n.d = _visited;
        n.low = _visited;
        _visited++;
        _q.push(&n);
        //for each adj, constant
        for (Node *v : n._connections)
        {
            // Node &v = *(c->_to);
            if (v->d == -1)
            {
                _tarjanVisit(*v);
            }
            //did we already processed it?(Not a SCC,(not in stack and not visited))
            if (!v->processed)
            {
                n.low = min(n.low, v->low);
            }
        }

        if (n.d == n.low)
        {
            //Creating SCC
            // SCC* scc=new SCC();
            shared_ptr<SCC> scc(new SCC());
            // unique_ptr<SCC> scc(new SCC());
            // std::unique_ptr<SCC> scc = std::unique_ptr<SCC>(new SCC);
            // auto scc = make_unique<SCC>();
            //setting nr of Global SCC
            _scc_nr++;
            Node *n_q;

            debug("n: " << &n);
            do
            {
                n_q = _q.top();
                debug("n_q: " << n_q << " l: " << n_q->low << " id:" << n_q->getId() << " d:" << n_q->d);
                n_q->associatedSCC = scc;
                n_q->processed = true;
                scc->associateNode(n_q); //to smallest node, constant
                _q.pop();
                debug("n_q: SCC" << n_q->associatedSCC << "  ");
            } while (&n != n_q);
        }
    }

    void _find_scc_sub_nets()
    {
        //V+E
        for (int i = 0; i < _g->getNrVertices(); i++)
        {
            for (Node *n_co : _g->_vertices[i]._connections)
            {
                //currentSCC!=toSCC
                if (_g->_vertices[i].associatedSCC->getId() != n_co->associatedSCC->getId())
                {
                    // _scc_conn_nr++;
                    // new SCC_Connection(_g->_vertices[i].associatedSCC, c->_to->associatedSCC);
                    SCC_Con* s = new SCC_Con();

                    s->from = _g->_vertices[i].associatedSCC->getId();
                    s->to = n_co->associatedSCC->getId();
                    //if the connection is already there
                    if (_sub_net_list.insert(s).second==false){ delete s; debug("delete");}
                }
            }
        }

        //NlogN
        // _sub_net_list.sort(compare_SCC_Connection);
    }

  public:
    Tarjan(Graph *g) : _visited(1), _g(g), _scc_nr(0) {}
    ~Tarjan()
    {
        for (SCC_Con *c : _sub_net_list)
        {
            delete c;
        }
    }

    void execute()
    {
        //Tarjan algoritm O(N+E)
        for (int i = 0; i < _g->getNrVertices(); i++)
        {
            if (_g->_vertices[i].d == -1)
            {
                _tarjanVisit(_g->_vertices[i]);
            }
        }

        // Finding Sub nets + sorting them O(Nlog(N))
        _find_scc_sub_nets();
    }

    void printResult()
    {
        console(_scc_nr);
        console(_sub_net_list.size());
        for (SCC_Con *c : _sub_net_list)
        {
            console(c->from<<" "<<c->to);
        }
    }
};

int main(int argc, char **argv)
{
    Graph g;
    g.loadGraphFromStdin();

    Tarjan *alg = new Tarjan(&g);
    alg->execute();
    alg->printResult();

    delete alg;

    return 0;
}