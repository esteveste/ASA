/* TODO
    Get setters source

*/
#include <iostream>
#include <assert.h> /* assert */
#include <list>
#include <stack>
#include <queue>
#include <set>
#include <memory>

using namespace std;

class ResidualArc
{
  private:
    int _capacity;
    void _setPair(ResidualArc *p) { pair = p; }

  public:
    int flux;
    int getCapacity() { return _capacity - flux; }
    ResidualArc *pair;

    // Always init in pairs otherwise will SEGFAULT in pair
    ResidualArc(int c) : _capacity(c), flux(0) {}
    ResidualArc(int c, ResidualArc *p) : _capacity(c), flux(0), pair(p)
    {
        p->_setPair(pair);
    }
    void addFlux(int f) { flux += f; }
    int getFlux() { return flux; }
};

class Vertex
{
  private:
    //position
    int _l, _c;

  public:
    list<Vertex *> _connections;
    int excess_flux;
    int height;
    bool processed;
    Vertex() : excess_flux(0), height(0) {}
    Vertex(int l, int c) : _l(l), _c(c), excess_flux(0), height(0) {}

    void addConnection(Vertex *to)
    {
        _connections.push_back(to); //constante time
    }
};

class Graph
{
  private:
    int _l;
    int _c;
    Vertex *_source;
    Vertex *_target;
    Vertex *vertices;
    bool **_outputM;
    int _cost;

  public:
    Graph() : _source(new Vertex(-1, 0)), _target(new Vertex(-2, 0)) {}

    ~Graph()
    {
        delete vertices;
    }

    void loadGraphFromStdin()
    {
        // Read input
        cin >> _l; //linhas
        cin >> _c; //colunas
        assert(_l >= 1);
        assert(_c >= 1);

        bool outm[_l][_c];
        _outputM = (bool **)outm;

        vertices = new Vertex[_l * _c];

        int m[2][_l][_c];
        int wv[_l][_c - 1];
        int wh[_l - 1][_c];

        //FIXME Nao facas matrizes
        for (int t = 0; t < 2; t++)
        {
            for (int i = 0; i < _l; i++)
            {
                for (int j = 0; j < _c; j++)
                {
                    cin >> m[t][i][j];
                }
            }
        }
        for (int i = 0; i < _l; i++)
        {
            for (int j = 0; j < _c - 1; j++)
            {
                cin >> wv[i][j];
            }
        }
        for (int i = 0; i < _l - 1; i++)
        {
            for (int j = 0; j < _c; j++)
            {
                cin >> wh[i][j];
            }
        }
    }

    void printOutput()
    {
        cout << _cost << endl
             << endl;

        for (int i = 0; i < _l; i++)
        {
            for (int j = 0; j < _c; j++)
            {
                cout << ((_outputM[i][j]) ? "P" : "C");
                if (j < _c - 1)
                    cout << " ";
            }
            cout << endl;
        }
    }
};

class ReLabel
{

  public:
    void init_pre_flow(Graph g)
    {
    }
    void discharge(Vertex u)
    {
        while (u.excess_flux > 0)
        {
        }
    }
    void relabel(Vertex u)
    {
    }
    void run(Graph g)
    {
    }
};

class Algo
{
  private:
    int _n;
    int _m;
    int cp_matrix;
    int *w_vert;
    int *w_hor;

  public:
    int getNrVertices() { return _n; }
};
int main()
{
    Graph g;
    g.loadGraphFromStdin();
    ReLabel algorithm;
    algorithm.run(g);

    return 0;
}