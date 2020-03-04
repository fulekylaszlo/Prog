#include <iostream>
#include "mlp.hpp"
#include <png++/png.hpp>
#include <fstream>

int main (int argc, char **argv)
{
   png::image <png::rgb_pixel> ach (argv[1]);
   
   int size = ach.get_height()*ach.get_width();
   
   Perceptron* p = new Perceptron(3, size, 256, size);
   
   double* image = new double[size+1];
   
   for (int i = 0; i < ach.get_width(); ++i)
      for (int j = 0; j < ach.get_height(); ++j)
           
          image[i*ach.get_width()+j] = ach[i][j].blue;
       
   double* value = (*p)(image);

    for(int i = 0; i < ach.get_width(); ++i)
        for(int j = 0; j<  ach.get_height(); ++j)
            {
            ach[i][j].green = value[i*ach.get_height()+j];
            }
    
    ach.write("kimenet.png");
   
   delete p;
   delete [] image;
}

