//
// Created by user on 05.11.2025.
//

#ifndef TERMINAL_3D_GRAPHICS_ENGINE_SCENE_H
#define TERMINAL_3D_GRAPHICS_ENGINE_SCENE_H

#include "../shapes/shape.h"
#include "camera.h"

class scene
{
private:
    int width, height;
    char** buffer;
    float** zBuffer;

    float nearPlane;
    float farPlane;

    static scene* mainScene;

    std::vector<shape*> shapes;
    camera* cam;

public:
    scene();
    scene(int width, int height);
    ~scene();

    static scene* getMainScene();
    static void createMainScene(int width, int height);
    static void destroyMainScene();

    void addShape(shape* shp);
    void removeShape(shape* shp);

    void setCamera(camera* cam);
    camera* getCamera() const;

    [[nodiscard]] int getWidth() const;
    [[nodiscard]] int getHeight() const;

    [[nodiscard]] float getNearPlane() const;
    [[nodiscard]] float getFarPlane() const;

    void setNearPlane(float nearPlane);
    void setFarPlane(float farPlane);

    char** getBuffer() const;
    void redrawBuffer() const;
    void render() const;
    void clear() const;
    void setPixel(int x, int y, float depth, char pixel) const;
};


#endif //TERMINAL_3D_GRAPHICS_ENGINE_SCENE_H
