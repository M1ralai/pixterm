#include "pixterm.hpp"
#include <iostream>
#include <fstream>
#include <stdarg.h>
#include <termios.h>
#include <unistd.h>

void Options::SelectUp() {
    if (selected == 0) {
        selected = values.size() - 1;
    } else {
        selected -= 1;
    }
}

void Options::SelectDown() {
    if (selected == values.size()) {
        selected = 0;
    } else {
        selected += 1;
    }
}

//burası da genellikle windowsta connio.h ile yapılıyor linux için termios kullandım
 TerminalSettings::TerminalSettings() {
    old = {0};

    if (tcgetattr(STDIN_FILENO, &old) < 0) perror("tcgetattr");

    struct termios newt = old;
    newt.c_lflag &= ~ICANON; // canonical modu kapat (Enter gerekmez)
    newt.c_lflag &= ~ECHO;   // karakteri ekrana yazma
    newt.c_cc[VMIN] = 1;     // minimum okuma
    newt.c_cc[VTIME] = 0;

    if (tcsetattr(STDIN_FILENO, TCSANOW, &newt) < 0) perror("tcsetattr");
}

TerminalSettings::~TerminalSettings() {
    tcsetattr(STDIN_FILENO, TCSANOW, &old);
}

Options::Options() {
    selected = 0;
}



Canvas::Canvas(int given_x, int given_y, char ch) : pixels(given_x * given_y, ch ){
    y = given_y;
    x = given_x;
    filler = ch;
    for (int i = 0; i < x; i++) {
        pixels[i] = '-';
        pixels[i + x * (y - 1)] = '-';
    }
    for (int i = 0; i < y; i++) {
        pixels[i * x] = '|';
        pixels[i * x + x - 1] = '|';
    }
}

//Burası linuxa göre yazıldı terminalin temizleme kodu powershellde farklı
void Canvas::DrawCanvas() {
    std::cout << "\33c\e[3J";
    if(options != nullptr) SetOptions();
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            std::cout << pixels[j + i *  x];
        }
        std::cout << "\n \r";
    }
}
void Canvas::SetOptions() {
    for (int i = 0; i < options->values.size(); i++) {
        if (i != options->selected) {
            SetString(2, 2 + i*2, options->values[i]);
        } else {
            SetString(2, 2 + i*2, "->" + options->values[i]);
        }
    }
}

int Canvas::SetChar(int given_x, int given_y, char ch) {
    if(given_x <= x && given_y < y && given_x >= 0 && given_y >= 0) {
        pixels[given_x + given_y * x] = ch;
        return 1;
    } else {
        return -1;
    }
}

int Canvas::SetString(int targetx, int targety, const char *str) {
    if (x - (strlen(str) + targetx) < 0) {
        return -1;
    } else {
        for (int i = 0; i < strlen(str); i++) {
            pixels[targety * x + targetx + i] = str[i];
        }
        return 0;
    }
}
int Canvas::SetString(int targetx, int targety, std::string str) {
    if (x - (str.length() + targetx) < 0 ) {
        return -1;
    } else {
        for ( int i = 0; i < str.length(); i++ ) {
            pixels[targety * x + targetx + i] = str[i];
        }
        return 0;
    }
}

int Canvas::SetShape(int targetx, int targety, std::vector<std::vector<char>> shape) {
    int width = shape[0].size();
    int height = shape.size();
    if (targetx + shape[0].size() > x &&  targety + shape.size() > y ) return -1;
    for(int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (shape[i][j] != ' ') pixels[(targety + i) * x + targetx + j] = shape[i][j];
        }
    }
    return 0;
}

int Canvas::SetFiller(int targetx, int targety, int length) {
    if (x - (length + targetx) < 0)
    {
        return -1;
    }
    for (int i = 0; i < length; i++)
    {
        pixels[targety * x + targetx + i] = filler;
    }
    return 0;
}
void Canvas::Reset() {
    for (int i = 0; i < x * y; i++)
    {
        pixels[i] = filler;
    }
    for (int i = 0; i < x; i++)
    {
        pixels[i] = '-';
        pixels[i + x * (y - 1)] = '-';
    }
    for (int i = 0; i < y; i++)
    {
        pixels[i * x] = '|';
        pixels[i * x + x - 1] = '|';
    }
}
void Canvas::SetScene(std::string FilePath, int ROWS) {
    std::ifstream scene;
    std::vector<std::string> SceneData;
    SceneData.resize(ROWS);
    int i = 0;
    scene.open(FilePath);
    while (getline(scene, SceneData[i]))
    {
        Canvas::SetString(1, i, SceneData[i].c_str());
        i++;
    }
    scene.close();
}

void Canvas::AddOption(std::string value) {
    options->values.push_back(value);
}

void Canvas::AddOption(const char* value) {
    options->values.push_back(std::string(value));
}

void Canvas::FreeOptions() {
    delete options;
}


Canvas::~Canvas() {
    FreeOptions();
}


char Getch() {
    char buf = 0;

    if (read(STDIN_FILENO, &buf, 1) < 0) perror("read error occured");

    return buf;
}
