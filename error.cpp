#include <iostream>
using namespace std;
void error_function(int code){
    switch (code) {
    case 0: //Command line error
        cerr << "Usage: ./slice-app <filename> <slice size>"<<endl;
        break;
    case 1: //Can't open file error
        cerr << "Can't open file"<<endl;
        break;
    case 2: //Slicer must be smaller than image
        cerr << "Slicer must be smaller than image" <<endl;
        break;
    default:
        break;
    }
}
