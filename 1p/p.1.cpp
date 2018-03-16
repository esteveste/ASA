#include <stdlib.h>
#include <iostream>
#include <assert.h> /* assert */
// #include <vector>
#include <string>
// #include <fstream>

using namespace std;

int main(int argc, char **argv)
{
    // Read input
    int n; // nr de pontos
    int m; // nr de ligacoes
    cin >> n;
    cin >> m;
    assert(n>=2); assert(m>=1);
    //read connections
    for (int i = 0; i < m; i++)
    {
        //FIXME without input verification
        int u, v;
        cin >> u >> v;
    }

    return 0;
}