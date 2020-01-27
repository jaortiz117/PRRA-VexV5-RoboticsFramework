#ifndef UTIL_H
#define UTIL_H

namespace util 
{
  enum class Side{top, bottom};
  enum class Color{red, blue};
  class Position{
  private:
    Side s;
    Color c;
  public:
    Position(Side _s, Color _c){
      s = _s;
      c = _c;
    }
    Side getSide(){
      return s;
    }

    Color getColor(){
      return c;
    }
};
}

#endif