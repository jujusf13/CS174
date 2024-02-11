#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "simplecanvas/SimpleCanvas.h"
#include <bitset>
 
using namespace std;
 
/**
 * @brief Load in a character string from a text file
 * 
 * @param filename Path to filename you want to load
 * @return string Character string read from the file
 */
string loadFile(char* filename) {
    ifstream t(filename);
    stringstream buffer;
    buffer << t.rdbuf();
    t.close();
    return buffer.str();
}


//we are not changing the binary, only the int color. The color now matches the binary of the characters we have. We decode the color with decode.cpp

void getBinary(SimpleCanvas& image, string message) { //message is hellow world
    //cout << message;
    int messageIndex = 0;
    int bitIndex = 0; //when we exit forloop, bitIndex will reset to zero again?
    //string bits = bitset<8>(currentChar).to_string(); //loop through string bits 

    //cout << "bits: " << bits << "\n"; //why does it say bits is not declared
    for (int i = 0; i < image.height; i++) {
        for (int j = 0; j < image.width; j++) { //for loop for rgb // 3 rotations for red green and blue (0,1,2) and get a bit by dividing that by %2
            for (int k = 0; k < 3; k++){
                
                //cout << "messageIndex: " << messageIndex << "\n";
                char currentChar = message[messageIndex];
                string bits = bitset<8>(currentChar).to_string(); //string bits should change every 8 times through the loop
                int color = image.data[i][j][k];
                //cout << "current char: " << currentChar << "\n";
                
                if ((color%2 != bits[bitIndex]-'0') && (bitIndex!=8)){ //if color and the whatever bit (either 1 or 0) don't match as an int, we add 1 to the color except for if the color is 255, we subtract 1
                    if (color == 255){                          //doing the not equal 8 here because if it does equal 8, we are messing with something that we don't want to mess with
                        color--;                                // -'0' because it is worth 48, 1 less than 49 on ascii table
                    }else{
                        color++;
                    }
                }  

                //cout << "bits[bitIndex]: " << bits[bitIndex] << "\n"; //the issue is here. it prints a bunch of zeros. bits above the for loop prints the correct binary for "H"
                //cout << "color: " << color << "\n";
                
                
                //using this to compare if int color is even or odd, just like if there is a 1 or 0,
                if(message[messageIndex] == '\0'){ //i think this is where the fault might be. No seg fault with this. Seg fault with currentChar
                    break;
                } 

                //cout << "bitIndex: " << bitIndex << "\n"; //prins correct bitIndex
                
                bitIndex++; //need to reset this when  we get a new messageIndex
                if (bitIndex == 8){ // bitIndex being equal to 8, index can only go up to 7. we add index to 7, go through the loop, then once we hit bitIndex ==7, we change the messageIndex by +1
                    //cout << "messageIndex: " << messageIndex << "\n"; //prints correct message index
                    messageIndex++; //change index, moving to new letter
                    //cout << "message[messageIndex]: " << message[messageIndex] << "\n";
                    bitIndex = 0; //resets bit Index
                    cout << "\n";
                }
                

            }
        }
    }
}



//3 command line arguments
//A path to the image inside of which to hide the text
//A path to a text file containing the text you want to hide
//A path to the output image that will store the hidden text  //this is the encrypted image, then we decode this

//make sure to change decode2.cpp with what path it takes (it is locked into its main).
int main(int argc, char** argv) { 
    
    cout << "BEGIN FILE\n";

    //implement each of these into a method
    SimpleCanvas image(argv[1]); //path to image of where you want to hide text
    string contents = loadFile(argv[2]); //path to text file containing text you want to hide
    image.write(argv[3]); //path to output image that will store the hidden text
    //cout << contents;
    cout << "END FILE\n";

    getBinary(image, contents);
    

    return 0;
}