cmake_minimum_required(VERSION 3.14)
project(Canvas)
set(CMAKE_CXX_STANDARD 14)

add_executable(Canvas src/World/Main.cpp
        src/World/EventSystem.cpp
        src/World/Screen.cpp
        src/Primitives/Int2.cpp
        src/Primitives/Float2.cpp
        src/Primitives/Color.cpp
        src/Canvas2D/Canvas2D.cpp
        src/Primitives/Constants.h
        src/World/Debug.cpp
        src/UI/Graph.cpp
        src/UI/Button.cpp
        src/UI/IPointInside.h
        src/UI/Circle.cpp
        src/UI/Circle.h
        src/Primitives/CircleButton.cpp
        src/Primitives/CircleButton.h
        src/Helpers/Utils.h
        src/UI/TextButton.cpp
        src/UI/TextButton.h
        src/UI/Rect.cpp
        src/UI/Rect.h
        src/World/Camera.cpp
        src/World/Camera.h
        src/Primitives/Float3.h
        src/Primitives/Edge.h
        src/Objects/Crankshaft2D.cpp
        src/Objects/Crankshaft2D.h
        src/Objects/ObjectCreator.cpp
        src/Objects/ObjectCreator.h
        src/Objects/Object.h
        src/Objects/Triangle.h src/Objects/Crankshaft3D.cpp src/Objects/Crankshaft3D.h src/Objects/Face.cpp src/Objects/Face.h src/Objects/Crankshaft.cpp src/Objects/Crankshaft.h)

include_directories(include)
target_link_libraries(Canvas C:/Library/freeglut.lib)
