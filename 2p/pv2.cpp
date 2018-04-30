#include <iostream>
#include <assert.h> /* assert */
#include <list>
#include <climits>

using namespace std;

//Debub
#define console(x) cout << x << endl
#define debug(x) //cout << "Debug: " << x << endl

//Proto
class Vertex;

class ResidualArc
{
  private:
    int _capacity;
    int _vertex_capacity;
    void _setPair(ResidualArc *p) { pair = p; }

  public:
    int flux;
    int getCapacity()
    {
        return _vertex_capacity;
    }
    ResidualArc *pair;
    Vertex *dest_vertex;

    // Always init in pairs otherwise will SEGFAULT in pair
    ResidualArc(int c, Vertex *dest) : _capacity(c), _vertex_capacity(c), flux(0), pair(NULL), dest_vertex(dest) {}
    ResidualArc(int c, Vertex *dest, ResidualArc *p) : _capacity(c), _vertex_capacity(c), flux(0), pair(p), dest_vertex(dest)
    {
        p->_setPair(this);
    }
    void addFlux(int f)
    {
        flux += f;
        _vertex_capacity = _capacity - flux;
    }
    int getFlux() { return flux; }
};

class Vertex
{
  public:
    list<ResidualArc *> _arcs;

    int excess_flux;
    int height;
    bool process;
    bool visited;

    Vertex *pred;
    ResidualArc *pred_arc;
    bool out;

    Vertex() : excess_flux(0), height(0), process(true), visited(false), pred(NULL), pred_arc(NULL), out(false) {}
    Vertex(bool p) : excess_flux(0), height(0), process(p), visited(false), pred(NULL), pred_arc(NULL), out(false) {}

    void addExcess_Flux(int f) { excess_flux += f; }

    void addArc(ResidualArc *c)
    {
        _arcs.push_back(c); //constante time
    }
};

class Graph
{
  private:
  public:
    int _l;
    int _c;
    int flowCarry;
    Vertex *_source;
    Vertex *_target;
    Vertex *vertices;

    Graph() : flowCarry(0), _source(new Vertex(false)), _target(new Vertex(false)) {}

    // ZERO INDEXED
    Vertex *getVertex(int l, int c)
    {
        return &vertices[l * _c + c];
    }

    void loadGraphFromStdin()
    {
        // Read input
        cin >> _l; //linhas
        cin >> _c; //colunas
        assert(_l >= 1);
        assert(_c >= 1);

        int* count = new int[_l * _c];

        //P calc
        for (int i = 0; i < _l; i++)
        {
            for (int j = 0; j < _c; j++)
            {
                cin >> count[i * _c + j];
            }
        }
        // C calc
        for (int i = 0; i < _l; i++)
        {
            for (int j = 0; j < _c; j++)
            {
                int temp;
                cin >> temp;
                flowCarry += min(count[i * _c + j], temp);
                count[i * _c + j] -= temp;
            }
        }

        vertices = new Vertex[_l * _c];
        //Put the right values
        for (int i = 0; i < _l; i++)
        {
            for (int j = 0; j < _c; j++)
            {
                int value = count[i * _c + j];
                if (value > 0)
                {
                    ResidualArc *s_arc = new ResidualArc(value, getVertex(i, j));
                    ResidualArc *v_pair = new ResidualArc(0, _source, s_arc);
                    _source->addArc(s_arc);
                    getVertex(i, j)->addArc(v_pair);
                }
                else if (value < 0)
                {
                    ResidualArc *t_arc = new ResidualArc(0, getVertex(i, j));
                    ResidualArc *v_pair = new ResidualArc(-value, _target, t_arc);
                    _target->addArc(t_arc);
                    getVertex(i, j)->addArc(v_pair);
                }
            }
        }
        //reduce space since no longer needed O(V)
        delete[] count;
        for (int i = 0; i < _l; i++)
        {
            for (int j = 0; j < _c - 1; j++)
            {
                int w;
                cin >> w;
                if (w != 0)
                {
                    ResidualArc *arc1 = new ResidualArc(w, getVertex(i, j + 1));
                    ResidualArc *arc2 = new ResidualArc(w, getVertex(i, j), arc1);
                    getVertex(i, j)->addArc(arc1);
                    getVertex(i, j + 1)->addArc(arc2);
                }
            }
        }
        for (int i = 0; i < _l - 1; i++)
        {
            for (int j = 0; j < _c; j++)
            {
                int w;
                cin >> w;
                if (w != 0)
                {
                    ResidualArc *arc1 = new ResidualArc(w, getVertex(i + 1, j));
                    ResidualArc *arc2 = new ResidualArc(w, getVertex(i, j), arc1);
                    getVertex(i, j)->addArc(arc1);
                    getVertex(i + 1, j)->addArc(arc2);
                }
            }
        }
    }
};

class BFS
{
  public:
    void initBFS(Graph g)
    {
        g._source->visited = false;
        g._target->visited = false;
        g._source->pred = NULL;
        g._target->pred = NULL;
        g._source->pred_arc = NULL;
        g._target->pred_arc = NULL;
        for (int i = 0; i < g._c * g._l; i++)
        {
            g.vertices[i].visited = false;
            g.vertices[i].pred = NULL;
            g.vertices[i].pred_arc = NULL;
        }
    }

    list<ResidualArc *> run(Graph g)
    {
        initBFS(g);

        list<Vertex *> L;
        L.push_front(g._source);
        g._source->visited = true;

        while (g._target->pred == NULL && L.size() != 0)
        {
            Vertex *u = L.front();
            L.pop_front();
            for (ResidualArc *arc : u->_arcs)
            {
                if (!arc->dest_vertex->visited && arc->getCapacity() > 0)
                {
                    L.push_back(arc->dest_vertex);
                    arc->dest_vertex->pred = u;
                    arc->dest_vertex->pred_arc = arc;
                    arc->dest_vertex->visited = true;
                    if (arc->dest_vertex == g._target)
                    {
                        break;
                    }
                }
            }
        }
        list<ResidualArc *> Larcs;
        if (g._target->visited == false)
        {
            return Larcs;
        }
        else
        {
            Vertex *u = g._target;
            while (u->pred_arc != NULL)
            {
                Larcs.push_front(u->pred_arc);
                u = u->pred;
            }
            return Larcs;
        }
    }
};

class EdmondsKarp
{
  private:
    int flow;

  public:
    EdmondsKarp() : flow(0) {}
    int run(Graph g)
    {
        flow = 0;
        while (true)
        {
            BFS search;
            list<ResidualArc *> pred = search.run(g);

            if (pred.size() != 0)
            {
                //check how much flow we can send
                int df = INT_MAX;
                for (ResidualArc *arc : pred)
                {
                    df = min(df, arc->getCapacity());
                }
                for (ResidualArc *arc : pred)
                {
                    arc->addFlux(df);
                    arc->pair->addFlux(-df);
                }
                flow += df;
            }
            else
            {
                return flow;
            }
        }
    }

    void printOutput(Graph g)
    {
        cout << flow + g.flowCarry << endl
             << endl;
        for (int i = 0; i < g._l; i++)
        {
            for (int j = 0; j < g._c; j++)
            {
                cout << (g.getVertex(i, j)->visited ? "C" : "P");
                cout << " ";
            }
            cout << endl;
        }
    }
};

int main()
{
    Graph g;
    g.loadGraphFromStdin();
    EdmondsKarp algorithm;
    algorithm.run(g);
    algorithm.printOutput(g);
    return 0;
}