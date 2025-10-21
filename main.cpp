#include "pixterm.hpp"
#include <iostream>
#include <thread>
#include <unistd.h>


void getInput() {
}

void GetInput(Canvas* canvas) {
    while(true){
        char ch = Getch();
        if (canvas->SetChar(10, 10, ch) < 0) perror("settingchar error");
    }
}

int main(){
    Canvas canvas(32, 32, ' ');
    std::thread t1(GetInput, &canvas);
    while(true) {
        canvas.DrawCanvas();
        std::this_thread::sleep_for(std::chrono::milliseconds(17));
    }
}
