#pragma once
#include <iostream>
namespace MAP
{
  struct Tile
  {
    char symbol;
    int x, y;
    Tile(int ax=0, int ay=0, char sym='.') : x(ax), y(ay), symbol(sym) {}
  };
  class GRID
  {
    int width;
    int height;
    Tile* tiles;
    public:
      GRID(int w=10, int h=10) : width(w), height(h) {tiles=new Tile[width*height];}
      ~GRID() {delete [] tiles;}
      // Graph related methods would go here
      int getWidth() const;
      int getHeight() const;
      MAP::Tile* getTiles() const;
      void setWidth(int w);
      void setHeight(int h);
      void setTiles(MAP::Tile* t);
      void BuildMAP();
    };
};