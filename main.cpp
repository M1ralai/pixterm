#include "pixterm.hpp"
#include <iostream>
#include <thread>

void getInput() {
}

int main(){
    TerminalSettings t;
    while(true) {
        char c = Getch();
        std::cout<<c<<"\n";
    }
}
