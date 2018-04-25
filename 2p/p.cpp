/* TODO
    Get setters source

*/
#include <iostream>
#include <assert.h> /* assert */
#include <list>
#include <stack>
#include <set>
#include <memory>

using namespace std;

class Vertex
{
  private:
    //position
    int _l,_c;
  public:
    int d, low; //for tarjan algoritm
    list<Vertex *> _connections;
    bool processed;

    Vertex(int l,int c) : _l(l), _c(c) {}

    void addConnection(Vertex *to)
    {
        _connections.push_back(to); //constante time
    }
};

class Graph{
    private:
        int _l; 
        int _c;
        Vertex* _source;
        Vertex* _target;
        bool** _outputM;
        int _cost;
    public:

        Graph():_source(new Vertex(-1,0)),_target(new Vertex(-2,0)){}

        void loadGraphFromStdin()
    {
        // Read input
        cin >> _l;//linhas
        cin >> _c;//colunas
        assert(_l >= 1);
        assert(_c >= 1);

        bool outm[_l][_c];
        _outputM=(bool**) outm;

        int m[2][_l][_c];
        int wv[_l][_c-1];
        int wh[_l-1][_c];

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
            for (int j = 0; j < _c-1; j++)
            {
                cin >> wv[i][j];
            }
        }
        for (int i = 0; i < _l-1; i++)
        {
            for (int j = 0; j < _c; j++)
            {
                cin >>wh[i][j];
            }
        }
        // cp_matrix =  m;

        // for (int t = 0; t < 2; t++)
        // {
        //     for (int i = 0; i < _l; i++)
        //     {
        //         for (int j = 0; j < _c; j++)
        //         {
        //             cout << m[t][i][j];
        //         }
        //         cout<<endl;
        //     }
        //     cout<<endl;
        // }
        // cout<<endl;
        // for (int i = 0; i < _l; i++)
        // {
        //     for (int j = 0; j < _c-1; j++)
        //     {
        //         cout << wv[i][j];
        //     }
        //     cout<<endl;
        // }
        // cout<<endl;
        // for (int i = 0; i < _l-1; i++)
        // {
        //     for (int j = 0; j < _c; j++)
        //     {
        //         cout << wh[i][j];
        //     }
        //     cout<<endl;
        // }
        // cout<<endl;
    }

    void printOutput(){
        cout<<_cost<<endl<<endl;

        for (int i = 0; i < _l; i++)
        {
            for (int j = 0; j < _c; j++)
            {
                cout << ((_outputM[i][j])?"P":"C");
                if (j<_c-1)
                    cout<<" ";
            }
            cout << endl;
        }

    }


};


// void Graph::loadGraphFromStdin()
//     {
//         // Read input
//         int _n; 
//         int _m; 
//         cin >> _n;//linhas
//         cin >> _m;//colunas
//         assert(_n >= 1);
//         assert(_m >= 1);
//         int m[2][_n][_m];
//         int wv[_n][_m-1];
//         int wh[_n-1][_m];
//         for (int t = 0; t < 2; t++)
//         {
//             for (int i = 0; i < _n; i++)
//             {
//                 for (int j = 0; j < _m; j++)
//                 {
//                     cin >> m[t][i][j];
//                 }
//             }
//         }
//         for (int i = 0; i < _n; i++)
//         {
//             for (int j = 0; j < _m-1; j++)
//             {
//                 cin >> wv[i][j];
//             }
//         }
//         for (int i = 0; i < _n-1; i++)
//         {
//             for (int j = 0; j < _m; j++)
//             {
//                 cin >>wh[i][j];
//             }
//         }
//         // cp_matrix =  m;

//         // for (int t = 0; t < 2; t++)
//         // {
//         //     for (int i = 0; i < _n; i++)
//         //     {
//         //         for (int j = 0; j < _m; j++)
//         //         {
//         //             cout << m[t][i][j];
//         //         }
//         //         cout<<endl;
//         //     }
//         //     cout<<endl;
//         // }
//         // cout<<endl;
//         // for (int i = 0; i < _n; i++)
//         // {
//         //     for (int j = 0; j < _m-1; j++)
//         //     {
//         //         cout << wv[i][j];
//         //     }
//         //     cout<<endl;
//         // }
//         // cout<<endl;
//         // for (int i = 0; i < _n-1; i++)
//         // {
//         //     for (int j = 0; j < _m; j++)
//         //     {
//         //         cout << wh[i][j];
//         //     }
//         //     cout<<endl;
//         // }
//         // cout<<endl;


//     }
class Algo
{
  private:
    int _n; 
    int _m; 
    int cp_matrix;
    int* w_vert;
    int* w_hor;
  public:

    

    int getNrVertices() { return _n; }
};
int main(){
    Graph g;
    g.loadGraphFromStdin();


    
    return 0;
}