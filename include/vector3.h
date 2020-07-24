#pragma once

#include <iostream>
#include <string>

class Vector2
{
public:
    Vector2() {};
    Vector2(float X, float Y): Data{X, Y} {};
    ~Vector2() {};

    std::string GetStringRepresentation() {return "X: " + std::to_string(X) + " Y: " + std::to_string(Y);};
public:
    union {
        float Data[2];
        struct {float X, Y;};
        struct {float U, V;};
    };
};

class Vector3
{
public:
    Vector3() {};
    Vector3(float X, float Y, float Z): Data{X, Y ,Z} {};
    ~Vector3() {};

    std::string GetStringRepresentation() {return "X: " + std::to_string(X) + " Y: " + std::to_string(Y);};

public:
    union {
        float Data[3];
        struct {float X, Y, Z;};
        struct {float R, G, B;};
    };
};
