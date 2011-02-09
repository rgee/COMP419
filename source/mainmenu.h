#ifndef _MAINMENU_H
#define _MAINMENU_H

#include "IwResManager.h"
#include "IwResGroup.h"
#include "IwGx.h"
#include "util.h"
#include "screen.h"

class MainMenu : Screen {
public:
    MainMenu();
    ~MainMenu();
    virtual void tick();
    virtual void render();
    void initRenderState();
private:
    CIwResGroup* images;
    CIwMat view;
    CIwMaterial mat;
};

#endif