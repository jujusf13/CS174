#include "ellipse.h"
#include <cmath>
#include <iostream>
using namespace std;
// TODO: Fill this in

/*

void printGreeting(){

    cout << "Hello World\n";
    for (int i = 0; i<10; i++){
        cout << i << " ";
    }
    cout << "\n";

}
*/


uint8_t** allocateImage(int width, int height){

    uint8_t** arr = new uint8_t*[width]; //array created with width number of locations in outer regionn
    for (int i = 0; i<height; i++){    //should it be unit8_t or int?
        arr[i] = new uint8_t[width];    
        //cout << 1;
    }                                    

    return arr;
}

void freeImage(uint8_t** image, int height){ //we created image in other array.
    
    for (int i = 0; i<height; i++){
        delete[] image[i];    //deletes each individual piece of inner array
    }
    delete[] image; //deletes outer array
   
}

/*
void drawEllipse(uint8_t** image, int width, int height, float cx, float cy, float sx, float sy, uint8_t shade){

    //double equation = (pow((width-cx),2)/pow(sx,2)) + (pow((height-cy),2)/pow(sy,2));


    for (int i = 0; i<width; i++){
        for (int j = 0; j<height; j++){//inner array

            double equation = (pow((i-cx),2)/pow(sx,2)) + (pow((j-cy),2)/pow(sy,2));


            if (equation <= 1){
               image[i][j] += shade; //equals writes over previous value?
            }
            else{
                image[i][j] += 0; //+=0?
            }
        } 
    }

}
*/


void drawEllipse(uint8_t** image, int width, int height, float cx, float cy, float sx, float sy, uint8_t shade){

    //double equation = (pow((width-cx),2)/pow(sx,2)) + (pow((height-cy),2)/pow(sy,2));


    for (int i = 0; i<width; i++){
        for (int j = 0; j<height; j++){//inner array

            double equation = (pow((j-cx),2)/pow(sx,2)) + (pow((i-cy),2)/pow(sy,2));  //j is used for x axis. Should width and height be switched in for loop because width is actually determined 


            if (equation <= 1){
               image[i][j] += shade; //equals writes over previous value?
            }
            else{
                image[i][j] += 0; //+=0?
            }
        } 
    }

}
