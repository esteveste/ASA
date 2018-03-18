#include <iostream>
#include <assert.h> /* assert */
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

class Node
{
  private:
    int _id;
  public:
    int d, low; //for tarjan algoritm
    shared_ptr<SCC> associatedSCC;
    list<Node *> _connections;
    bool processed;

    Node() : d(-1), processed(false) {}
    Node(int id) : _id(id), d(-1), processed(false) {}

    void setId(int id) { _id = id; }
    int getId() { return _id; }
    void addConnection(Node *to)
    {
        _connections.push_back(to); //constante time
    }
};

class SCC
{
  public:
    SCC() : smallest_id_Node(NULL) {}
    Node *smallest_id_Node;

    void associateNode(Node *n)
    {
        // Complexity constant
        if (smallest_id_Node == NULL || smallest_id_Node->getId() > n->getId())
        {
            smallest_id_Node = n;
        }
    }
    int getId() { return smallest_id_Node->getId(); }
};

struct SCC_Connection{
    int from;
    int to;
};

//compare (constant)
struct compare_SCC_Connection
{
    bool operator()(SCC_Connection *first, SCC_Connection *second)
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
    Node *vertices;

    Graph():vertices(NULL){}

    ~Graph()
    {
        delete[] vertices;
    }

    void loadGraphFromStdin()
    {
        // Read input
        cin >> _n;
        cin >> _m;
        assert(_n >= 2);
        assert(_m >= 1);

        // Initializing the vertices (2N?)
        vertices = new Node[_n];
        for (int i = 0; i < _n; i++)
        {
            vertices[i].setId(i + 1);
        }

        //read connections (1 indexed) (N)
        for (int i = 0; i < _m; i++)
        {
            int u, v;
            cin >> u >> v;
            vertices[u - 1].addConnection(&vertices[v - 1]);
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
    set<SCC_Connection *, compare_SCC_Connection> _sub_net_list;

    void _tarjanVisit(Node &n)
    {
        n.d = _visited;
        n.low = _visited;
        _visited++;
        _q.push(&n);
        //for each adj, constant
        for (Node *v : n._connections)
        {
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
            shared_ptr<SCC> scc(new SCC());
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
        //V+E -> NlogN with set insertion
        for (int i = 0; i < _g->getNrVertices(); i++)
        {
            for (Node *n_co : _g->vertices[i]._connections)
            {
                //currentSCC!=toSCC
                if (_g->vertices[i].associatedSCC->getId() != n_co->associatedSCC->getId())
                {
                    SCC_Connection* s = new SCC_Connection();

                    s->from = _g->vertices[i].associatedSCC->getId();
                    s->to = n_co->associatedSCC->getId();
                    //if the connection is already there
                    if (_sub_net_list.insert(s).second==false){ delete s; debug("delete");}
                    //set insertion logN
                }
            }
        }
    }

  public:
    Tarjan(Graph *g) : _visited(1), _g(g), _scc_nr(0) {}
    ~Tarjan()
    {
        for (SCC_Connection *c : _sub_net_list)
        {
            delete c;
        }
    }

    void execute()
    {
        //Tarjan algoritm O(N+E)
        for (int i = 0; i < _g->getNrVertices(); i++)
        {
            if (_g->vertices[i].d == -1)
            {
                _tarjanVisit(_g->vertices[i]);
            }
        }

        // Finding Sub nets + sorting them O(Nlog(N))
        _find_scc_sub_nets();
    }

    void printResult()
    {
        console(_scc_nr);
        console(_sub_net_list.size());
        for (SCC_Connection *c : _sub_net_list)
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