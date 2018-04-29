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
class Vertex;

class ResidualArc
{
  private:
    int _capacity;
    void _setPair(ResidualArc *p) { pair = p; }

  public:
    int flux;
    int getCapacity() { return _capacity - flux; }
    ResidualArc *pair;
    Vertex* dest_vertex;
    // Always init in pairs otherwise will SEGFAULT in pair
    ResidualArc(int c,Vertex* dest) : _capacity(c), flux(0),pair(NULL),dest_vertex(dest) {}
    ResidualArc(int c,Vertex* dest, ResidualArc *p) : _capacity(c), flux(0), pair(p),dest_vertex(dest)
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
    // int _l, _c;

  public:
    list<ResidualArc *> _arcs;

    int excess_flux;
    int height;
    bool processed;
    Vertex() : excess_flux(0), height(0) {}
    // Vertex(int l, int c) : _l(l), _c(c), excess_flux(0), height(0) {}

    ~Vertex(){
        for(ResidualArc *c : _arcs)
        {
            delete c;
        }
    }

    void addArc(ResidualArc *c)
    {
        _arcs.push_back(c); //constante time
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

    // ZERO INDEXED
    Vertex* getVertex(int l,int c){
        return &vertices[l*_c+c];
    }

  public:
    Graph() : _source(new Vertex()), _target(new Vertex()) {}

    ~Graph()
    {
        delete _source;
        delete _target;
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

        //Get The P's
        for (int i = 0; i < _l; i++)
        {
            for (int j = 0; j < _c; j++)
            {
                int p;
                cin >> p;
                ResidualArc *s_arc = new ResidualArc(p,getVertex(i,j));
                ResidualArc *v_pair = new ResidualArc(0,_source,s_arc);
                _source->addArc(s_arc);
                getVertex(i,j)->addArc(v_pair);
            }
        }
        //Get The C's
        for (int i = 0; i < _l; i++)
        {
            for (int j = 0; j < _c; j++)
            {
                int c;
                cin >> c;
                ResidualArc *t_arc = new ResidualArc(0,getVertex(i,j));
                ResidualArc *v_pair = new ResidualArc(c,_target,t_arc);
                _target->addArc(t_arc);
                getVertex(i,j)->addArc(v_pair);
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






        // int m[2][_l][_c];
        // int wv[_l][_c - 1];
        // int wh[_l - 1][_c];

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