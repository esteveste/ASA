/* TODO
    Get setters source

*/
#include <iostream>
#include <assert.h> /* assert */
#include <list>
#include <stack>
#include <deque>
#include <set> //is a tree
#include <memory>
#include <climits>

using namespace std;

//Debub
#define console(x) cout << x << endl
#define debug(x) cout << "Debug: " << x << endl

//Proto
class Vertex;
// class BFS;

class ResidualArc
{
  private:
    int _capacity;
    int _vertex_capacity;
    void _setPair(ResidualArc *p) { pair = p; }

  public:
    int flux;
    int getCapacity() { 
        // debug("cap "<<_capacity - flux);
        // return _capacity - flux; 
        return _vertex_capacity;}
    ResidualArc *pair;
    Vertex* dest_vertex;

    // Always init in pairs otherwise will SEGFAULT in pair
    ResidualArc(int c,Vertex* dest) : _capacity(c),_vertex_capacity(c), flux(0),pair(NULL),dest_vertex(dest) {}
    ResidualArc(int c,Vertex* dest, ResidualArc *p) : _capacity(c),_vertex_capacity(c), flux(0), pair(p),dest_vertex(dest){
        p->_setPair(this);
    }
    void addFlux(int f) {
         flux += f; 
         _vertex_capacity= _capacity - flux;
    }
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
    bool process;
    bool visited;
    Vertex* pred; 
    ResidualArc* pred_arc;

    Vertex() : excess_flux(0), height(0), process(true),visited(false),pred(NULL),pred_arc(NULL){}
    Vertex(bool p) : excess_flux(0), height(0), process(p),visited(false),pred(NULL),pred_arc(NULL){}
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

    Graph() : _source(new Vertex(false)), _target(new Vertex(false)) {}

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
                if (p!=0)
                {
                    ResidualArc *s_arc = new ResidualArc(p,getVertex(i,j));
                    ResidualArc *v_pair = new ResidualArc(0,_source,s_arc);
                    _source->addArc(s_arc);
                    getVertex(i,j)->addArc(v_pair);    
                }

         
            }
        }
        //Get The C's
        for (int i = 0; i < _l; i++)
        {
            for (int j = 0; j < _c; j++)
            {
                int c;
                cin >> c;
                if (c!=0)
                {
                    ResidualArc *t_arc = new ResidualArc(0,getVertex(i,j));
                    ResidualArc *v_pair = new ResidualArc(c,_target,t_arc);
                    _target->addArc(t_arc);
                    getVertex(i,j)->addArc(v_pair);
                }

            }
        }

        for (int i = 0; i < _l; i++)
        {
            for (int j = 0; j < _c - 1; j++)
            {
                int w;
                cin >> w;
                if (w!=0)
                {
                    ResidualArc *arc1 = new ResidualArc(w,getVertex(i,j+1));
                    ResidualArc *arc2 =new ResidualArc(w,getVertex(i,j),arc1);
                    getVertex(i,j)->addArc(arc1);
                    getVertex(i,j+1)->addArc(arc2);
                }

            }
        }
        for (int i = 0; i < _l - 1; i++)
        {
            for (int j = 0; j < _c; j++)
            {
                int w;
                cin >> w;
                if(w!=0){
                    ResidualArc *arc1 = new ResidualArc(w,getVertex(i+1,j));
                    ResidualArc *arc2 =new ResidualArc(w,getVertex(i,j),arc1);
                    getVertex(i,j)->addArc(arc1);
                    getVertex(i+1,j)->addArc(arc2);
                }
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

    void printOutput(int f)
    {
        // int total_flux=0;
        // for(ResidualArc* arcs : _target->_arcs)
        // {
        //     total_flux+=arcs->getCapacity();
        // }
        cout << f << endl
             << endl;

        // for (int i = 0; i < _l; i++)
        // {
        //     for (int j = 0; j < _c; j++)
        //     {
        //         cout << ((getVertex(i,j)->height>=_source->height) ? "C" : "P");
        //         cout << " ";
        //     }
        //     cout << endl;
        // }
    }
};


class BFS{
    public:


    void initBFS(Graph g){
        g._source->visited=false;
        g._target->visited=false;
        g._source->pred=NULL;
        g._target->pred=NULL;
        g._source->pred_arc=NULL;
        g._target->pred_arc=NULL;
        for (int i = 0; i < g._c * g._l; i++)
        {
            g.vertices[i].visited=false;
            g.vertices[i].pred=NULL;
            g.vertices[i].pred_arc=NULL;
        }
    }

    list<ResidualArc*> run(Graph g){

        initBFS(g);

        list<Vertex *> L;
        set<Vertex*> T;
        // L.clear();
        // T.clear();

        // int distance = 0;
        L.push_front(g._source);
        T.insert(g._source);
        g._source->visited=true;

        while (g._target->pred==NULL&&L.size()!=0)
        {
            Vertex* u=L.front();
            L.pop_front();
            for(ResidualArc* arc : u->_arcs)
            {
                if (!arc->dest_vertex->visited&&arc->getCapacity()>0)
                {
                    //distance
                    
                    L.push_back(arc->dest_vertex);
                    arc->dest_vertex->pred=u;
                    arc->dest_vertex->pred_arc=arc;
                    arc->dest_vertex->visited=true;
                    if (arc->dest_vertex==g._target){
                        debug("Break TARGET");
                        break;
                    }
                }
            }

        }
        // L.clear();
        list<ResidualArc*> Larcs;
        if (g._target->visited==false)
        {
            return Larcs;
        }else
        {
            Vertex* u = g._target;
            while (u->pred_arc!=NULL)
            {
                Larcs.push_front(u->pred_arc);
                u = u->pred;
            }
            return Larcs;
        }


    }
};


class EdmondsKarp{
    public:
    int run(Graph g){
        int flow=0;
        while (true)
        {
            BFS search;
            list<ResidualArc *> pred = search.run(g);

            if (pred.size()!=0)
            {
                //check how much flow we can send
                int df = INT_MAX;
                for(ResidualArc* arc : pred)
                {
                    df = min(df,arc->getCapacity());
                }
                for(ResidualArc* arc : pred)
                {
                    arc->addFlux(df);
                    arc->pair->addFlux(-df);
                }
                flow+=df;

            }else
            {
                return flow;
            }
        }

    }
};


class ReLabel
{
  private:
    list<Vertex*> L;
    list<Vertex*>::iterator l_it;
    Vertex* v_pushed;
    int maxH;
  public:
    void init_pre_flow(Graph g)
    {

        g._source->height=g._l * g._c+2;//set height source
        
        for(ResidualArc* arc : g._source->_arcs)
        {
            int capacity = arc->getCapacity(); //since our capacity keeps changing
            if (capacity>0)
            {
                arc->pair->addFlux(-capacity);
                arc->addFlux(capacity);
                g._source->excess_flux -=capacity;
                arc->dest_vertex->excess_flux += capacity;
                L.push_front(arc->dest_vertex);
            }

        } 
    }
    void createList(Graph g){
        // for (int i = 0; i < g._l; i++)
        // {
        //     for (int j = 0; j < g._c; j++)
        //     {
        //         //the vertices in Graph are fixed array
        //         //source and target not included
        //         L.push_back(g.getVertex(i,j));
        //     }
        // }
    }


    void push(Vertex* u,ResidualArc* arc){
        // assert(u->excess_flux>0 && u->height==arc->dest_vertex->height+1);
        // int cap_nr=0;
        // if (v_pushed==u)
        // {
        //     for(ResidualArc* arc : u->_arcs)
        //     {
        //         if (arc->getCapacity()>0){
        //             cap_nr++;
        //         }    
        //     }
        //     if (cap_nr<=2)
        //     {
        //         u->height=maxH;
        //         arc->dest_vertex->height=maxH;
        //     }
        // }
        // if (cap_nr>2)
        // {
        //     v_pushed = u;
        // }else
        // {
        //     v_pushed = NULL;
        // }
        

        int d = min(u->excess_flux,arc->getCapacity());
        arc->addFlux(d);
        arc->pair->addFlux(-d);
        u->excess_flux-=d;
        arc->dest_vertex->excess_flux+=d;

        if (arc->dest_vertex->process)
        {
            L.push_front(arc->dest_vertex);
            l_it= L.begin();
        }
        

    }
    void discharge(Vertex* u)
    {
        list<ResidualArc*> v_arcs = u->_arcs;

        while (u->excess_flux > 0)
        {
            if (v_arcs.size()==0)
            {
                relabel(u);
                v_arcs = u->_arcs;
            }else
            {
                ResidualArc* arc = v_arcs.front();
                v_arcs.pop_front();
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
        maxH = g._l * g._c+2;
        init_pre_flow(g);
        createList(g);
        

        l_it= L.begin();
        Vertex* u = *(l_it);
        while (l_it!= L.end())
        {
            l_it=L.erase(l_it);
            // int old_height = u->height;
            discharge(u);
            //relabel occured
            // if (u->height>old_height)
            // {

            // L.push_front(u);
            // l_it= L.begin();
            // }
            
            u = *(l_it);


        }

    }
};

int main()
{
    Graph g;
    g.loadGraphFromStdin();
    EdmondsKarp algorithm;
    g.printOutput(algorithm.run(g));
    return 0;
}