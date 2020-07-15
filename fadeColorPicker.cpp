#include "fadeColorPicker.h"
#include <math.h>
fadeColorPicker::fadeColorPicker(double fade)
{
    /* your code here */
    fadeFactor = fade;
}

HSLAPixel fadeColorPicker::operator()(point p)
{
    /* your code here */
    HSLAPixel k = p.c.color;
    double centerL = k.l;
    int dltx =p.c.x - p.x;
    int dlty = p.c.y - p.y;
    double dist = sqrt(pow(dltx , 2) + pow(dlty, 2));
    double newL = centerL * pow(fadeFactor,dist);
    k.l = newL;
    return k;
    
}
