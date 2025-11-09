#include <algorithm>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <conio.h>

#include "math/Vec3.h"
#include "math/Mat4.h"

#include "shapes/parallelepiped.h"
#include "control/control.h"
#include "scene/scene.h"
#include "shapes/sphere.h"
#include "shapes/ellipsoid.h"

int main()
{
    scene::createMainScene(720, 200);
    const auto cam1 = new camera({5.0f, 5.0f, 5.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f});
    cam1->setPerspectiveProjectionMatrix(Mat4::makePerspective(50.0f,
                                                               scene::getMainScene()->getHeight(),
                                                               scene::getMainScene()->getWidth(),
                                                               scene::getMainScene()->getNearPlane(),
                                                               scene::getMainScene()->getFarPlane()));
    const auto cam2 = new camera({0.0f, 0.0f, 10.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f});
    cam2->setPerspectiveProjectionMatrix(Mat4::makePerspective(50.0f,
                                                               scene::getMainScene()->getHeight(),
                                                               scene::getMainScene()->getWidth(),
                                                               scene::getMainScene()->getNearPlane(),
                                                               scene::getMainScene()->getFarPlane()));
    scene::getMainScene()->addCamera(cam1);
    scene::getMainScene()->addCamera(cam2);
    shape* box1 = new parallelepiped();
    box1->setModel(
        Mat4::scale(2.0f, 2.0f, 2.0f)
    );
    scene::getMainScene()->addShape(box1);
    shape* box2 = new parallelepiped({2.0f, 2.0f, 2.0f}, 0.3f, 2.0f, 0.2f);
    box2->setModel(
        Mat4::rotationY(0.5f)
    );
    scene::getMainScene()->addShape(box2);

    shape* ellipsoid1 = new ellipsoid({3.0f, 0.0f, 0.0f}, 1.0f, 1.0f, 0.0f, 24, 24);
    ellipsoid1->setModel(
        Mat4::translation(3.0f, 0.0f, 0.0f)
    );
    scene::getMainScene()->addShape(ellipsoid1);

    control curControl(scene::getMainScene());

    while (true)
    {
        curControl.processInput();

        if (curControl.getExitFlag())
        {
            break; // Выход из программы
        }
        if (!curControl.getMoveFlag())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }

        if (curControl.getCamChangedFlag())
        {
            scene::getMainScene()->changeCamera();
        }

        scene::getMainScene()->clear();
        scene::getMainScene()->redrawBuffer();
        scene::getMainScene()->render();

        std::this_thread::sleep_for(std::chrono::milliseconds(30)); // ~33 FPS
    }
}
