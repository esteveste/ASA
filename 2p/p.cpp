/* TODO
    Get setters source

*/
#include <iostream>
#include <assert.h> /* assert */
#include <list>
#include <stack>
// #include <deque>
#include <set>
#include <memory>
#include <climits>

using namespace std;

//Debub
#define console(x) cout << x << endl
#define debug(x) cout << "Debug: " << x << endl

//Proto
class Vertex;

class ResidualArc
{
  private:
    int _capacity;
    void _setPair(ResidualArc *p) { pair = p; }

  public:
    int flux;
    int getCapacity() { 
        debug("cap "<<_capacity - flux);
        return _capacity - flux; }
    ResidualArc *pair;
    Vertex* dest_vertex;

    // Always init in pairs otherwise will SEGFAULT in pair
    ResidualArc(int c,Vertex* dest) : _capacity(c), flux(0),pair(NULL),dest_vertex(dest) {}
    ResidualArc(int c,Vertex* dest, ResidualArc *p) : _capacity(c), flux(0), pair(p),dest_vertex(dest){
        p->_setPair(this);
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

    // ~Vertex(){
    //     for(ResidualArc *c : _arcs)
    //     {
    //         delete c;
    //     }
    // }

    void addExcess_Flux(int f){excess_flux+=f;}

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
    Vertex *_source;
    Vertex *_target;
    Vertex *vertices;

    Graph() : _source(new Vertex()), _target(new Vertex()) {}

    ~Graph()
    {
        // delete _source;
        // delete _target;
        // delete vertices;
    }

    // ZERO INDEXED
    Vertex* getVertex(int l,int c){
        return &vertices[l*_c+c];
    }

    void loadGraphFromStdin()
    {
        // Read input
        cin >> _l; //linhas
        cin >> _c; //colunas
        assert(_l >= 1);
        assert(_c >= 1);

        // bool outm[_l][_c];
        // _outputM = (bool **)outm;

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
                
                debug(p);
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

                debug(c);
            }
        }

        for (int i = 0; i < _l; i++)
        {
            for (int j = 0; j < _c - 1; j++)
            {
                int w;
                cin >> w;
                ResidualArc *arc1 = new ResidualArc(w,getVertex(i,j+1));
                ResidualArc *arc2 =new ResidualArc(w,getVertex(i,j),arc1);
                getVertex(i,j)->addArc(arc1);
                getVertex(i,j+1)->addArc(arc2);
            }
        }
        for (int i = 0; i < _l - 1; i++)
        {
            for (int j = 0; j < _c; j++)
            {
                int w;
                cin >> w;
                ResidualArc *arc1 = new ResidualArc(w,getVertex(i+1,j));
                ResidualArc *arc2 =new ResidualArc(w,getVertex(i,j),arc1);
                getVertex(i,j)->addArc(arc1);
                getVertex(i+1,j)->addArc(arc2);
            }
        }






        // int m[2][_l][_c];
        // int wv[_l][_c - 1];
        // int wh[_l - 1][_c];

        //FIXME Nao facas matrizes
        // for (int t = 0; t < 2; t++)
        // {
        //     for (int i = 0; i < _l; i++)
        //     {
        //         for (int j = 0; j < _c; j++)
        //         {
        //             cin >> m[t][i][j];
        //         }
        //     }
        // }
        // for (int i = 0; i < _l; i++)
        // {
        //     for (int j = 0; j < _c - 1; j++)
        //     {
        //         cin >> wv[i][j];
        //     }
        // }
        // for (int i = 0; i < _l - 1; i++)
        // {
        //     for (int j = 0; j < _c; j++)
        //     {
        //         cin >> wh[i][j];
        //     }
        // }
    }

    void printOutput()
    {
        int total_flux=0;
        for(ResidualArc* arcs : _target->_arcs)
        {
            total_flux+=arcs->getCapacity();
        }
        cout << total_flux << endl
             << endl;

        for (int i = 0; i < _l; i++)
        {
            for (int j = 0; j < _c; j++)
            {
                cout << ((getVertex(i,j)->height>_source->height) ? "C" : "P");
                if (j < _c - 1)
                    cout << " ";
            }
            cout << endl;
        }
    }
};

class ReLabel
{
  private:
    list<Vertex*> L;
  public:
    void init_pre_flow(Graph g)
    {

        g._source->height=g._l * g._c +2;//set height source
        
        for(ResidualArc* arc : g._source->_arcs)
        {
            debug("b capacity "<<arc->getCapacity());
            int capacity = arc->getCapacity(); //since our capacity keeps changing
            arc->pair->addFlux(-capacity);
            arc->addFlux(capacity);
            debug("after "<<arc->getCapacity()<< " ot "<<arc->pair->getCapacity());
            g._source->excess_flux -=capacity;
            arc->dest_vertex->excess_flux += capacity;
        } 
    }
    void createList(Graph g){
        for (int i = 0; i < g._l; i++)
        {
            for (int j = 0; j < g._c; j++)
            {
                //the vertices in Graph are fixed array
                //source and target not included
                L.push_back(g.getVertex(i,j));
            }
        }
    }


    void push(Vertex* u,ResidualArc* arc){
        debug("push ");
        assert(u->excess_flux>0 && u->height>arc->dest_vertex->height);
        


        int d = min(u->excess_flux,arc->getCapacity());
        arc->addFlux(d);
        arc->pair->addFlux(-d);
        u->excess_flux-=d;
        arc->dest_vertex->excess_flux+=d;

        debug("push "<<d);
    }
    void discharge(Vertex* u)
    {
        list<ResidualArc*> v_arcs = u->_arcs;

        while (u->excess_flux > 0)
        {
            if (v_arcs.size()==0)
            {
                debug("u "<<u->height);
                relabel(u);
                v_arcs = u->_arcs;
            }else
            {
                ResidualArc* arc = v_arcs.front();
                v_arcs.pop_front();
                debug("u h "<<u->height<<"ar h "<<arc->dest_vertex->height);
                if(arc->getCapacity()>0 && u->height>arc->dest_vertex->height){
                    push(u,arc);
                }
            }

        }
    }
    void relabel(Vertex* u)
    {
        int min_height=INT_MAX;
        for(ResidualArc* arc : u->_arcs)
        {
            if (arc->getCapacity()>0&&arc->dest_vertex->height<min_height){
                min_height=arc->dest_vertex->height;
            }
            
        }
        assert(u->excess_flux>0);
        assert(u->height<=min_height);
        
        u->height=min_height+1;

    }
    void run(Graph g)
    {
        init_pre_flow(g);
        createList(g);
        
        list<Vertex*>::iterator l_it= L.begin();

        Vertex* u = *(l_it);
        while (l_it!= L.end())
        {
            debug("list size "<<L.size());
            int old_height = u->height;
            discharge(u);
            //relabel occured
            if (u->height>old_height)
            {
                l_it=L.erase(l_it);
                L.push_front(u);
                l_it= L.begin();
            }
            
            u = *(++l_it);

        }

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
    g.printOutput();
    return 0;
}