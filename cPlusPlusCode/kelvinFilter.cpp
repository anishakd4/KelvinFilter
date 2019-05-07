#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<iostream>

using namespace cv;
using namespace std;

//interpolation
void interpolation(uchar* lut, float* curve, float* originalValue){
    for(int i=0; i<256; i++){
        int j=0;
        float a = i;
        while (a>originalValue[j]){
            j++;
        }
        if(a == originalValue[j]){
            lut[i] = curve[j];
            continue;
        }
        float slope = ((float)(curve[j] - curve[j-1]))/((float)(originalValue[j] - originalValue[j-1]));
        float constant = curve[j] - slope * originalValue[j];
        lut[i] = slope * a + constant;
    }
}

int main(){

    //Read input image
    Mat image = imread("../assets/anish.jpg");

    //Check is image exits
    if(image.empty()){
        cout<<"can not find image"<<endl;
        return 0;
    }

    //define variable to store output image
    Mat output;

    //create a clone of input image to work on
    output = image.clone();

    //Split the channels
    vector<Mat> channels;
    split(output, channels);

    // Interpolation values
    float redValuesOriginal[] = {0, 60, 110, 150, 235, 255};
    float redValues[] =         {0, 102, 185, 220, 245, 245};
    float greenValuesOriginal[] = {0, 68, 105, 190, 255};
    float greenValues[] =         {0, 68, 120, 220, 255};
    float blueValuesOriginal[] = {0, 88, 145, 185, 255};
    float blueValues[] =         {0, 12, 140, 212, 255};

    //create lookup table
    Mat lookupTable(1, 256, CV_8U);
    uchar* lut = lookupTable.ptr();

    //Apply interpolation and create lookup table
    interpolation(lut, blueValues, blueValuesOriginal);
    //Apply mapping for Blue Channel
    LUT(channels[0], lookupTable, channels[0]);

    //Apply interpolation and create lookup table
    interpolation(lut, greenValues, greenValuesOriginal);
    //Apply mapping for green Channel
    LUT(channels[1], lookupTable, channels[1]);

    //Apply interpolation and create lookup table
    interpolation(lut, redValues, redValuesOriginal);
    //Apply mapping for Red Channel
    LUT(channels[2], lookupTable, channels[2]);

    //Merge back the channels
    merge(channels, output);

    //create windows to display images
    namedWindow("image", WINDOW_AUTOSIZE);
    namedWindow("Kelvin", WINDOW_AUTOSIZE);

    //Display images
    imshow("image", image);
    imshow("Kelvin", output);

    //Press esc to exi the program
    waitKey(0);

    //Close all the opened windows
    destroyAllWindows();

    return 0;
}