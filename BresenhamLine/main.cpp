#include "tgaimage.h"

#define MINCOUNT = 0.01f;

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) { 
    
    bool steep = false; 
    if (std::abs(x0-x1)<std::abs(y0-y1)) { // if the line is steep, we transpose the image 
        std::swap(x0, y0); 
        std::swap(x1, y1); 
        steep = true; 
    } 

    if (x0 > x1)
    {
        std::swap(x0 ,x1);
        std::swap(y0, y1);
    }
/* mine
    for (int x = x0; x < x1; x++)
    {
        float t = ( x - x0 ) / (float)( x1 -x0);
        int y = y0 + (y1- y0) * t;
        if (steep)
        {
            image.set(y, x , color);
        }else{
            image.set(x, y , color);
        }
        
    }
*/
    int dx = x1-x0; 
    int dy = y1-y0; 
    float derror = std::abs(dy/float(dx)); 
    float error = 0; 
    int y = y0; 
    for (int x=x0; x<=x1; x++) { 
        if (steep) { 
            image.set(y, x, color); 
        } else { 
            image.set(x, y, color); 
        } 
        error += derror; 
        if (error>.5) { 
            y += (y1>y0?1:-1); 
            error -= 1.; 
        } 
    } 
}

int main(int argc, char** argv){

    TGAImage image(100, 100, TGAImage::RGB);

    line(13, 20, 80, 40, image, white); 
    line(20, 13, 40, 80, image, red); 
    line(80, 40, 13, 20, image, red);

    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
}
