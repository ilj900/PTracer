#ifndef DRAW_MANAGER_H
#define DRAW_MANAGER_H

#include "image.h"

class DrawManager
{
public:
    DrawManager(UImage* Image);
    void Use();
    void Draw();

private:
    UImage* ImageToDraw;
    unsigned int ShaderProgram = 0;
    unsigned int Texture = 0;
    unsigned int VAO = 0;
};

#endif //DRAW_MANAGER_H
