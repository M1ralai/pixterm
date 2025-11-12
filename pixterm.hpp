#ifndef PIXEL_H
#define PIXEL_H
#include <vector>
#include <termios.h>

//Getting char without enter, use this after create Canvas or TerminalSettings
char Getch();

class TerminalSettings {
    private:
        struct termios old;
    public:
        TerminalSettings();
        ~TerminalSettings();
};

class Options {
    public:
        Options();
        std::vector<std::string> values;
        int selected;
        void SelectUp();
        void SelectDown();
};

class Canvas{
    private:
        int x;
        int y;
        char filler;
        std::vector<char> pixels;
        Options* options;
        void AddOption(std::string);
        void AddOption(const char*);
        void FreeOptions();
        void SetOptions();
        TerminalSettings term;
    public:
        //constructor take x and y for create canvas and char for a filler
        Canvas(int, int, char);
        //writes canvas to terminal
        void DrawCanvas();
        //Set given x y's character as  a input
        int SetChar(int, int, char);
        //Starts writing at given x and y coordinates and if last one is 0 thats mean its writes if 1 thats mean that length of pixels are converted to a filler as you created canvas
        int SetString(int,int,const char*);
        //Starts writing at given x and y coordinates and if last one is 0 thats mean its writes if 1 thats mean that length of pixels are converted to a filler as you created canvas
        int SetString(int, int, std::string);
        // Set given x t o given y pixels as a filler
        int SetFiller(int,int,int);
        //Takes .txt file and row number and set all lines of canvas as them
        void SetScene(std::string, int);
        //Reset all canvas that you give while creating
        template<typename... Args>
        void NewOptions(const Args&... args) {
            delete options;
            options = new Options;
            (AddOption(args), ...);
        }
            void Reset();
        ~Canvas();
    };


#endif
