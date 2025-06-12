#ifndef PIXEL_H
#define PIXEL_H
#include <vector>
class Canvas{
    public:
        int x;
        int y;
        char filler;
        std::vector<char> pixels;
        //set canvas size and filler char
        void Size(int,int,char);
        //writes canvas to terminal
        void DrawCanvas();
        //Starts writing at given x and y coordinates and if last one is 0 thats mean its writes if 1 thats mean this empt as you created canvas
        int DrawString(int,int,const char*,int);
        //Takes .txt file and row number and set all lines of canvas as them
        void SetScene(std::string, int);
        //Reset all canvas that you give while creating
        void Reset();
};
#endif