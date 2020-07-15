#include "borderColorPicker.h"
#include <math.h>

borderColorPicker::borderColorPicker(unsigned int borderSize, HSLAPixel fillColor, PNG &img, double tolerance)
{
    /* your code here */
    this->borderSize = borderSize;
    this->fillColor= fillColor;
    this->img = img;                 // Image used in flood fill algorithm
    this->tolerance = tolerance; 
}

HSLAPixel borderColorPicker::operator()(point p){
double w = this->img.width();
double h = this->img.height();
bool xCondition = (p.x < borderSize) || (p.x > w - borderSize -1);
bool yCondition = (p.y < borderSize) || (p.y > h - borderSize -1);
//  bool top = (0 <= p.x <= w) && (0 <= p.y < this->borderSize);
//   bool right = (0 <= p.y <= h) && (0 <= p.x < this->borderSize);
//   bool bottom = (0 <= p.x <= w) && (h - this->borderSize <= p.y <= h);
//   bool left = (0 <= p.y <= h) && (w - this->borderSize <= p.x <= w);

  HSLAPixel k = p.c.color;
  HSLAPixel org = *img.getPixel(p.x,p.y);

    /* your code here */
    if (xCondition || yCondition){      //is it near border?
                // k.l = fillColor.l;
                // k.h = fillColor.h;
                // k.s = fillColor.s;
                // k.a = fillColor.a;
                return fillColor;
    } 
    // if (img.getPixel(p.x,p.y)->dist(k) > tolerance){
    //     return org;
    // }
    for (int x = 0; x< w;x++){
        for(int y = 0; y<h; y++){
            int dx = x - p.x;
            int dy = y - p.y;
            int disSq = pow(dx,2) + pow(dy,2);
            if (disSq <= pow(borderSize,2)){
                if (k.dist(*img.getPixel(x,y)) >= tolerance){
                    return fillColor;
                }
            }
        }
    }
    return org;
    //  return k;
}
