#include <iostream>
#include <vector>
using namespace std;
#include "../include/utils/Queue.h"
#include "../include/data/Map.h"
#include "../include/utils/BFS.h"

int main()
{
    MAP::GRID map(10,10);
    map.BuildMAP();
    MAP::Tile* tiles = map.getTiles();
    for(int i=0;i<10;i++)  
        {for(int j=0;j<10;j++)
            cout<<tiles[j*10+i].symbol<<" ";
        cout<<endl;
        }
    int* parent = BFS(tiles, 0, 0, 3, 4);
    if(parent) 
    {
        int i=34;
        while(i != -1)
        {
            tiles[i].symbol='#';
            i=parent[i];
        }
        delete [] parent;
    }
    else
        cout<<"BFS failed to find a path."<<endl;
    cout<<endl;
    for(int i=0;i<10;i++)
        {for(int j=0;j<10;j++)
            cout<<tiles[j*10+i].symbol<<" ";
        cout<<endl;
        }
    return 0;
}
