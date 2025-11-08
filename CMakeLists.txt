cmake_minimum_required(VERSION 4.0)
project(terminal_3d_graphics_engine)

set(CMAKE_CXX_STANDARD 20)

add_executable(terminal_3d_graphics_engine main.cpp
        renderer/renderer.cpp
        renderer/renderer.h
        loader/loader.cpp
        loader/loader.h
        scene/scene.cpp
        scene/scene.h
        math/Vec3.cpp
        math/Vec3.h
        math/Vec2.cpp
        math/Vec2.h
        math/Mat4.cpp
        math/Mat4.h
        math/Vec4.cpp
        math/Vec4.h
        shapes/shape.cpp
        shapes/shape.h
        shapes/parallelepiped.cpp
        shapes/parallelepiped.h
        scene/camera.cpp
        scene/camera.h)
