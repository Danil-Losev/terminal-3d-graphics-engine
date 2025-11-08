//
// Created by user on 08.11.2025.
//

#include "control.h"
#include <conio.h>


control::control(scene* scn) : exitFlag(false), moveFlag(false), camChangedFlag(false)
{
    this->curScene = scn;
}

bool control::getExitFlag()
{
    return exitFlag;
}

bool control::getMoveFlag()
{
    if (moveFlag)
    {
        this->moveFlag = false;
        return true;
    }
    return moveFlag;
}

bool control::getCamChangedFlag()
{
    if (camChangedFlag)
    {
        this->camChangedFlag = false;
        return true;
    }
    return camChangedFlag;
}

bool control::processInput()
{
    moveFlag = false;
    if (_kbhit())
    {
        const char key = static_cast<char>(_getch());
        moveFlag = true;
        camera* cam = this->curScene->getCurrentCamera();
        constexpr float moveSpeed = 0.2f;
        constexpr float rotSpeed = 0.05f;

        // Вектор "вправо" через векторное произведение
        Vec3 forward = (cam->camTarget - cam->camPos).normalize();
        Vec3 right = forward.vectorMultiplication(cam->camUp).normalize();

        // --- Движение камеры (WASD) ---
        if (key == 'w') cam->camPos = cam->camPos + forward * moveSpeed;
        if (key == 's') cam->camPos = cam->camPos - forward * moveSpeed;
        if (key == 'a') cam->camPos = cam->camPos - right * moveSpeed;
        if (key == 'd') cam->camPos = cam->camPos + right * moveSpeed;

        // --- Вращение направления взгляда (IJKL) ---
        if (key == 'i') forward = (forward - cam->camUp * rotSpeed).normalize(); // вверх
        if (key == 'k') forward = (forward + cam->camUp * rotSpeed).normalize(); // вниз
        if (key == 'j') forward = (forward - right * rotSpeed).normalize(); // влево
        if (key == 'l') forward = (forward + right * rotSpeed).normalize(); // вправо

        if (key == 'c')
        {
            camChangedFlag = true;
            return false; // смена камеры
        }

        // --- Обновление цели ---
        cam->camTarget = cam->camPos + forward;

        std::cout << "Position: (" << cam->camPos.X() << ", " << cam->camPos.Y() << ", " << cam->camPos.Z() << ")\n";
        // --- Пример выхода ---
        if (key == 27)
        {
            exitFlag = true; // ESC
            return true;
        }
    }
    exitFlag = false;
    return false;
}
