#include "pixel.h"
#include <iostream>
#include <fstream>
void Canvas::Size(int given_x,int given_y, char ch){
    y = given_y;
    x = given_x;
    filler = ch;
    pixels.resize(x*y);
    for(int i = 0; i < x*y; i++){
        pixels[i] = filler;
    }
    for (int i = 0; i < x; i++){
        pixels[i] = '-';
        pixels[i+x*(y-1)] = '-';
    }
    for (int i = 0; i < y; i++){
        pixels[i*x] = '|';
        pixels[i*x+x-1] = '|';
    }
}
void Canvas::DrawCanvas(){
    std::cout<<"\33c\e[3J";
    for(int i = 0; i < y; i++){
        for(int j = 0; j < x; j++){
            std::cout<<pixels[j+i*x];
        }
        std::cout<<"\n \r";
    }
}
int Canvas::DrawString(int targetx, int targety, const char *str, int clear = 0){
    if(x-(strlen(str) + targetx) < 0){
        return -1;
    }else{
        if(clear == 0){
            for(int i  = 0; i < strlen(str); i++){
                pixels[targety*x+targetx+i] = str[i];
            }
            return 0;
        } else{
            for(int i  = 0; i < strlen(str); i++){
                pixels[targety*x+targetx+i] = filler;
            }
            return 0;
        }
    }
}
void Canvas::Reset(){
    for(int i = 0; i < x*y; i++){
        pixels[i] = filler;
    }
    for (int i = 0; i < x; i++){
        pixels[i] = '-';
        pixels[i+x*(y-1)] = '-';
    }
    for (int i = 0; i < y; i++){
        pixels[i*x] = '|';
        pixels[i*x+x-1] = '|';
    }
}
void Canvas::SetScene(std::string FilePath,int ROWS){
    std::ifstream scene;
    std::string SceneData[ROWS];
    int i = 0;
    scene.open(FilePath);
    while(getline(scene,SceneData[i])){
        Canvas::DrawString(1,i,SceneData[i].c_str(),0);
        i++;
    }
    scene.close();
}