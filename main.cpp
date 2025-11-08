#include <algorithm>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include "math/Vec3.h"
#include "math/Vec4.h"
#include "math/Mat4.h"
#include "math/Vec2.h"
#include "scene/scene.h"
#include <conio.h>

#include "shapes/parallelepiped.h"

bool input(camera* cam, bool& isMoving, bool& camChanged)
{
    isMoving = false;
    if (_kbhit())
    {
        const char key = static_cast<char>(_getch());
        isMoving = true;
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
            camChanged = true;
            return false; // смена камеры
        }

        // --- Обновление цели ---
        cam->camTarget = cam->camPos + forward;

        std::cout << "Position: (" << cam->camPos.X() << ", " << cam->camPos.Y() << ", " << cam->camPos.Z() << ")\n";
        // --- Пример выхода ---
        if (key == 27)
        {
            return true; // ESC
        }
    }
    return false;
}


int main()
{
    scene::createMainScene(720, 200);
    const auto cam1 = new camera(Vec3(5.0f, 5.0f, 5.0f), Vec3(1.0f, 1.0f, 1.0f), Vec3(0.0f, 1.0f, 0.0f));
    cam1->setPerspectiveProjectionMatrix(Mat4::makePerspective(50.0f,
                                                               scene::getMainScene()->getHeight(),
                                                               scene::getMainScene()->getWidth(),
                                                               scene::getMainScene()->getNearPlane(),
                                                               scene::getMainScene()->getFarPlane()));
    const auto cam2 = new camera(Vec3(0.0f, 0.0f, 10.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
    cam2->setPerspectiveProjectionMatrix(Mat4::makePerspective(50.0f,
                                                               scene::getMainScene()->getHeight(),
                                                               scene::getMainScene()->getWidth(),
                                                               scene::getMainScene()->getNearPlane(),
                                                               scene::getMainScene()->getFarPlane()));
    scene::getMainScene()->setCamera(cam1);
    shape* box1 = new parallelepiped();
    static_cast<parallelepiped*>(box1)->setModel(
        Mat4::scale(2.0f, 2.0f, 2.0f)
    );
    scene::getMainScene()->addShape(box1);
    shape* box2 = new parallelepiped(Vec3(2.0f, 2.0f, 2.0f), 2.0f, 2.0f, 0.0f);
    static_cast<parallelepiped*>(box2)->setModel(
        Mat4::rotationY(0.5f)
    );
    scene::getMainScene()->addShape(box2);
    camera* curCam = cam1;
    while (true)
    {
        bool isMoving = false;
        bool camChanged = false;

        if (input(curCam, isMoving, camChanged))
        {
            break; // Выход из программы
        }
        if (!isMoving)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }

        if (camChanged)
        {
            if (curCam == cam1)
            {
                curCam = cam2;
            }
            else
            {
                curCam = cam1;
            }
            scene::getMainScene()->setCamera(curCam);
        }

        scene::getMainScene()->clear();
        scene::getMainScene()->redrawBuffer();
        scene::getMainScene()->render();

        std::this_thread::sleep_for(std::chrono::milliseconds(30)); // ~33 FPS
    }
}
