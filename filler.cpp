/**
 * @file filler.cpp
 * Implementation of functions in the filler namespace.
 *
 */
#include <iostream>
using namespace std;
/**
 * Performs a multi-point flood fill using breadth first search.
 *
 * @param config      FillerConfig struct to setup the fill
 * @return animation  object illustrating progression of flood fill algorithm
 */
animation filler::fillBFS(FillerConfig &config)
{
    /**
     * @todo Your code here! You should replace the following line with a
     * correct call to fill.
     */
    animation an = fill<Queue>(config);
    return an;
}

/**
 * Performs a multi-point flood fill using depth first search.
 *
 * @param config      FillerConfig struct to setup the fill
 * @return animation  object illustrating progression of flood fill algorithm
 */
animation filler::fillDFS(FillerConfig &config)
{
    /**
     * @todo Your code here! You should replace the following line with a
     * correct call to fill.
     */
    animation an = fill<Stack>(config);

    return an;
}

/**
 * Run a multi-point flood fill on an image
 *
 * @param  config     FillerConfig struct with data for flood fill of image
 * @return animation  object illustrating progression of flood fill algorithm
 */

// struct FillerConfig
// {
//     int frameFreq;                 // Frequency with which to save frames to GIF animation.
//     float tolerance;               // Tolerance used to determine if pixel is in fill region.
//     PNG img;                       // Image to perform the fill on.
//     vector<center> centers;        // Seed locations where the fill will begin.
//     vector<colorPicker *> pickers; // colorPickers used to fill the regions.
// };


template <template <class T> class OrderingStructure> animation filler::fill(FillerConfig &config)
{
    /**
     * @todo You need to implement this function!
     *
     * This is the basic description of a flood-fill algorithm: Every fill
     * algorithm requires an ordering structure, which is passed to this
     * function via its template parameter. For a breadth-first-search
     * fill, that structure is a Queue, for a depth-first-search, that
     * structure is a Stack. To begin the algorithm, you simply place the
     * given point in the ordering structure, marking it processed
     * (the way you mark it is a design decision you'll make yourself).
     * We have a choice to either change the color, if appropriate, when we
     * add the point to the OS, or when we take it off. In our test cases,
     * we have assumed that you will change the color when a point is added
     * to the structure.
     * Until the structure is empty, you do the following:
     *
     * 1.     Remove a point from the ordering structure, and then...
     *
     *        1.    add its unprocessed neighbors whose color values are
     *              within (or equal to) tolerance distance from the center,
     *              to the ordering structure, and
     *              mark them as processed.
     *        2.    if it is an appropriate frame, send the current PNG to the
     *              animation (as described below).
     *
     * 2.     When implementing your breadth-first-search and
     *        depth-first-search fills, you will need to explore neighboring
     *        pixels in some order.
     *
     *        While the order in which you examine neighbors does not matter
     *        for a proper fill, you must use the same order as we do for
     *        your animations to come out like ours! The order you should put
     *        neighboring pixels **ONTO** the queue or stack is as follows:
     *        ** LEFT(-x), DOWN(+y), RIGHT(+x), UP(-y). IMPORTANT NOTE: *UP*
     *        here means towards the top of the image, so since an image has
     *        smaller y coordinates at the top, this is in the *negative y*
     *        direction. Similarly, *DOWN* means in the *positive y*
     *        direction.** To reiterate, when you are exploring (filling out)
     *        from a given pixel, you must first try to fill the pixel to
     *        it's LEFT, then the one DOWN from it, then to the RIGHT and
     *        finally UP. If you do them in a different order, your fill may
     *        still work correctly, but your animations will be different
     *        from the grading scripts!
     *
     *        Because we are doing a multi-point flood fill you will repeat the flood
     *        fill from several locations stored in the `centers` variable of FillerConfig
     *        struct. Initial fill points should be visited in the order they stored in the
     *        `centers` vector. If a pixel lies in the fill region of multiple start points,
     *        it should only be updated by the first fill. To repeat, pixels should only
     *        be modified the first time they are visited by the filler algorithm.
     *
     * 3.     For every k pixels filled, **starting at the kth pixel**, you
     *        must add a frame to the animation, where k = frameFreq.
     *
     *        For example, if frameFreq is 4, then after the 4th pixel has
     *        been filled you should add a frame to the animation, then again
     *        after the 8th pixel, etc.  You must only add frames for the
     *        number of pixels that have been filled, not the number that
     *        have been checked. So if frameFreq is set to 1, a pixel should
     *        be filled every frame.
     *
     * 4.     Finally, as you leave the function, send one last frame to the
     *        animation. This frame will be the final result of the fill, and
     *        it will be the one we test against.
     *
     */
    animation an;

   

    int w = config.img.width();
    int h = config.img.height();
    int processed[w][h];
    int frameCount = 0; 

    an.addFrame(config.img);

    for (int i = 0; i< w ; i++){
        for (int j = 0 ; j < h ; j++){
            processed[i][j]=0;
        }
    }
    cout<<"made 1"<<endl;


    // Point p = new Point(config.centers[0]);
    // os.add(p);
    // processed[p.x][p.y] = 1;
    for (int i = 0; i < config.centers.size(); i++){
        // colorPicker cp = (*config.pickers[i]);
         OrderingStructure<point> os;
        center c = config.centers[i];
        point p = point(c);
     os.add(p);
     cout<<"made 2"<<endl;
    
     HSLAPixel pix = *(config.img.getPixel(p.x,p.y));
     *(config.img.getPixel(p.x,p.y)) = (*config.pickers[i])(p);
    //  cp(p);

     processed[p.x][p.y] = 1;
     frameCount++;
     while (!(os.isEmpty())){ 
        // bool didChange = false;
         cout<<"made 3"<<endl;
         point a = os.remove();
          if (0 <a.x && a.x<= w && processed[a.x - 1][a.y] == 0 && pix.dist(*(config.img.getPixel(a.x -1,a.y))) <= config.tolerance ){
              point left = point(a.x -1,a.y,c);
              os.add(left);
            //   cp(left);
            *(config.img.getPixel(left.x,left.y)) = (*config.pickers[i])(left);
              processed[left.x][left.y] = 1;
            //   didChange = true;
            frameCount++;
            if (frameCount == config.frameFreq){
              frameCount = 0;
              an.addFrame(config.img);
              
          }
            cout<<"made 4"<<endl;

          }

          cout<<"made 4.5"<<endl;
          if (0<=a.y && a.y<h  && processed[a.x][a.y + 1] == 0 && pix.dist(*(config.img.getPixel(a.x ,a.y + 1))) <= config.tolerance){
              point down = point(a.x,a.y + 1,c);
              os.add(down);
            //   cp(down);
            *(config.img.getPixel(down.x,down.y)) = (*config.pickers[i])(down);
              processed[a.x][a.y + 1] = 1;
            //   didChange = true;
            frameCount++;
            cout<<"made 5"<<endl;
            if (frameCount == config.frameFreq){
              frameCount = 0;
              an.addFrame(config.img);
          }
          }
          cout<<"made 5.5"<<endl;
          if (0 <= a.x && a.x< w && processed[a.x + 1][a.y] == 0 && pix.dist(*(config.img.getPixel(a.x +1,a.y))) <= config.tolerance ){
              point right = point(a.x + 1,a.y ,c);
              os.add(right);
            //   cp(right);
            *(config.img.getPixel(right.x, right.y)) = (*config.pickers[i])(right);
              processed[a.x + 1][a.y] = 1;
            //   didChange = true;
            frameCount++;
            cout<<"made 6"<<endl;
            if (frameCount == config.frameFreq){
              frameCount = 0;
              an.addFrame(config.img);
          }
          }
          cout<<"made 6.5"<<endl;
          if (0<a.y && a.y<=h ){
              cout<<"askjdsajdka"<<a.y << a.y - 1<<" assadadadsad "<< h<<endl;
              if(processed[a.x ][a.y - 1] == 0  ){
                  cout<<"made almost hello"<<endl;
                  if(pix.dist(*(config.img.getPixel(a.x,a.y - 1))) <= config.tolerance){
                      cout<<"made hello"<<endl;
                       cout<<"made 6.5.1"<<endl;
              point up = point(a.x,a.y-1,c);
              cout<<"made 6.5.2"<<endl;
              os.add(up);
              cout<<"made 6.5.3"<<endl;
            //   cp(up);
             *(config.img.getPixel(up.x,up.y)) = (*config.pickers[i])(up);
             cout<<"made 6.5.4"<<endl;
              processed[a.x][a.y - 1] = 1;
            //   didChange = true;
            frameCount++;
            cout<<"made 7"<<endl;
            if (frameCount == config.frameFreq){
              frameCount = 0;
              an.addFrame(config.img);
                    }

              }
              
             
          }
          }
          cout<<"made 7.5"<<endl;
          //if (didChange) { frameCount++;}
          if (frameCount == config.frameFreq){
              frameCount = 0;
              an.addFrame(config.img);
          }

     }

    }
    an.addFrame(config.img);
    return an;
}
