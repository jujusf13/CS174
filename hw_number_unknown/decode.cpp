#include <iostream>
using namespace std;
#include <string.h>
#include "simplecanvas/SimpleCanvas.h"
#include <bitset>
#include<math.h>

/*

** Looping through the bits of an image and receiving the binary of that
image in return
**
*/


string getBinary(SimpleCanvas& image) {
    
    string binaryWhole;
    string binarySingle;

    for (int i = 0; i < image.height; i++) {
        for (int j = 0; j < image.width; j++) { //for loop for rgb // 3 rotations for red green and blue (0,1,2) and get a bit by dividing that by %2
            for (int l = 0; l < 3; l++){

                int color = (int)image.data[i][j][l]; //l is either a 0, 1, 2. 0 is red, 1 is green, 2 is blue 
                
            
                if (color%2 == 1){
                    binarySingle = "1";
                }
                else{
                    binarySingle = "0";
                }

                binaryWhole = binaryWhole + binarySingle;  //adds each new binary num to the whole

            }
        }
   
    }

    //cout << "binaryNumber1: " << binaryWhole << "\n";
    return binaryWhole;
}

void binaryToGroupsOfEight(string binaryNumber){ //taken from getBinary loop

    cout << "binaryNumber2: " << binaryNumber << "\n";
    int length = binaryNumber.length();
    for (int i = 0; i < length; i+=8){  //or while loop if there is a null terminator??


        string eightNumsBinary = binaryNumber.substr(i,8);
        cout << "eightNumsBinary: " << eightNumsBinary << "\n";
        int c = 0; //this was char c = 0; before
        int k = 128; //starts at 128, then we divide by two many times
        int binaryToNormalNum = 0;
        int newNumFromNormalNum = 0;
        cout << "c: ";
        for (int place = 0; place < 8; place++){ //does place reset everytime?
            if(eightNumsBinary[place] == '1'){ //problem is here, c is not what it should be
                c = 1;
            }

            cout << c;
            
            binaryToNormalNum = c * k; //this before k = k*2 because  we are getting numbers 2 to 256, not 1 to 128
            //cout << "binaryToNormalNum: " << binaryToNormalNum << "\n";
            k = k/2;
            //newNumFromNormalNum = newNumFromNormalNum + binaryToNormalNum;  
            //cout << "newNumFromNormalNum: " << newNumFromNormalNum << "\n";
            
            
        }

        cout << "\n";

        //
         //after this forloop, take the value of newNumFromNormalNum and use it with the ascii table
        //

        //cout << "newNumFromNormalNum: " << newNumFromNormalNum << "\n";
        

    }

}



//no need to write own ascii table

//get binary ,then decode binary method?


int main (int argc, char** argv){ //do i need argc here?

SimpleCanvas image(argv[1]);
//getBinary(image); --> doesn't store anywhere
string binaryNumber = getBinary(image);
binaryToGroupsOfEight(binaryNumber);

/*
    std::string str = "01000001";
 
    for (std::size_t i = 0; i < str.size(); i++) {
        std::cout << std::bitset<8>(str[i]) << ' ';
    }
 
   */

//char c = 001100010011011100110100001000010000101000000000;
//cout << c; //check photos from phone. Look for how to cast.

// 0 1 0 0 1 0 1 1 
//char c = 0*128 + 1*64 + 0*32 + 0*16 + 1*8 + 0*4 + 1*2 + 1*1;
//cout << c << "\n";

/*

char c = 115;
cout << c << "\n";
return 0;
*/

}


