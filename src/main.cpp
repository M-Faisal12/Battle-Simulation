#include <iostream>
#include <vector>
using namespace std;
#include "include/utils/Queue.h"
struct Tile
{
    char symbol;
    int x, y;
    Tile(int ax=0, int ay=0, char sym='.') : x(ax), y(ay), symbol(sym) {}
};

int* BFS(Tile* grid, int startX, int startY, int endX, int endY)
{
    //TODO BFS implementation would go here 
    if(!grid || startX < 0 || startX >=10 || startY < 0 || startY >=10
       || endX < 0 || endX >=10 || endY < 0 || endY >=10)
        return nullptr;
        
    bool visited[100] = {false};
    int* parent=new int[100];
    for (int i = 0; i < 100; i++)
        parent[i] = -1;
    Queue<int> q;
    q.enqueue(startX + startY*10);
    visited[startX + startY*10] = true;
    while(!q.isEmpty())
    {
        if(grid[q.peek()].x == endX && grid[q.peek()].y == endY)
        {
            printf("Found B");
            return parent;
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
    return nullptr;
}

int main()
{
    return 0;
}
