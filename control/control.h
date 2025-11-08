//
// Created by user on 08.11.2025.
//

#ifndef TERMINAL_3D_GRAPHICS_ENGINE_CONTROL_H
#define TERMINAL_3D_GRAPHICS_ENGINE_CONTROL_H

#include "../scene/scene.h"

class control
{
private:
    scene* curScene;
    bool exitFlag;
    bool moveFlag;
    bool camChangedFlag;

public:
    explicit control(scene* scn);
    bool getExitFlag();
    bool getMoveFlag();
    bool getCamChangedFlag();
    bool processInput();
};


#endif //TERMINAL_3D_GRAPHICS_ENGINE_CONTROL_H
