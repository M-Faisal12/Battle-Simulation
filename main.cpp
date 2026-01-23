#include <iostream>
using namespace std;
#include "Queue.h"
struct Tile
{
    char symbol;
    int x, y;
    Tile(int ax=0, int ay=0, char sym='.') : x(ax), y(ay), symbol(sym) {}
};
int main()
{
    Tile grid[100];
    // Initialize grid with default tiles
    grid[0] = Tile(0, 0, 'A'); // Example: Place an 'A' at position (0,0)
    grid[99] = Tile(9, 9, 'B'); // Example: Place a 'B' at position (9,9)
    for(int i=0; i<10; ++i)
    {
            for(int j=0; j<10; ++j)
            {
                grid[i*10+j] = Tile(i, j, '#');
                cout<< grid[i*10+j].symbol << ' ';
            }
    cout<< endl;
    }
    bool visited[100] = {false};
    int parent[100];
    for (int i = 0; i < 100; i++)
        parent[i] = -1;
    Queue<int> q;
    q.enqueue(0);
    visited[0] = true;
    while(!q.isEmpty())
    {
        if(grid[q.peek()].symbol == 'B')
        {
            printf("Found B");
            break;
        }
        int i=grid[q.peek()].x,j=grid[q.peek()].y;
        q.dequeue();
        if(j+1 < 10 && !visited[(j+1)*10+i]) // down
        {
            j++;
            q.enqueue(j*10+i);
            parent[ j*10+i ] = (j-1)*10+i;
            visited[ j*10+i ] = true;
            j--;
        }
        if(i+1 < 10 && !visited[j*10+i+1]) // right
        {
            i++;
            q.enqueue(j*10+i);
            parent[ j*10+i ] = j*10+(i-1);
            visited[ j*10+i ] = true;
            i--;
        }
        if(j-1 >= 0 && !visited[(j-1)*10+i]) // up
        {
            j--;
            q.enqueue(j*10+i);
            parent[ j*10+i ] = (j+1)*10+i;
            visited[ j*10+i ] = true;
            j++;
        }
        if(i-1 >= 0 && !visited[j*10+(i-1)]) // left
        {
            i--;
            q.enqueue(j*10+i);
            parent[ j*10+i ] = j*10+(i+1);
            visited[ j*10+i ] = true;
            i++;
        }
        if(j+1 < 10 && i+1 < 10 && !visited[(j+1)*10+(i+1)]) // down-right
        {
            j++; i++;
            q.enqueue(j*10+i);
            parent[ j*10+i ] = (j-1)*10+(i-1);
            visited[ j*10+i ] = true;
            j--; i--;
        }
        if(j-1 >= 0 && i-1 >= 0 && !visited[(j-1)*10+(i-1)]) // up-left
        {
            j--; i--;
            q.enqueue(j*10+i);
            parent[ j*10+i ] = (j+1)*10+(i+1);
            visited[ j*10+i ] = true;
            j++; i++;
        }
        if(j+1 < 10 && i-1 >= 0 && !visited[(j+1)*10+(i-1)]) // down-left
        {
            j++; i--;
            q.enqueue(j*10+i);
            parent[ j*10+i ] = (j-1)*10+(i+1);
            visited[ j*10+i ] = true;
            j--; i++;
        }
        if(j-1 >= 0 && i+1 < 10 && !visited[(j-1)*10+(i+1)]) // up-right
        {
            j--; i++;
            q.enqueue(j*10+i);
            parent[ j*10+i ] = (j+1)*10+(i-1);
            visited[ j*10+i ] = true;
            j++; i--;
        }
    }
}