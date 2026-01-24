#include "../../include/data/Map.h"
namespace MAP
{
int MAP::GRID::getWidth() const {return width;};
int MAP::GRID::getHeight() const {return height;};
MAP::Tile* MAP::GRID::getTiles() const {return tiles;};
void MAP::GRID::setWidth(int w) {width=w;};
void MAP::GRID::setHeight(int h) {height=h;};
void MAP::GRID::setTiles(MAP::Tile* t) {tiles=t;};
void MAP::GRID::BuildMAP()
{
    for(int i=0;i<width;i++)  
        {
            for(int j=0;j<height;j++)
            {
                tiles[j*width+i]=Tile(i,j,'.');
            }
        }
}
};