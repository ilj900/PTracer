#include "utils.h"
#include "sphere.h"
#include "triangle.h"
#include "camera.h"
#include "timing.h"
#include "draw_manager.h"

#include "matrix2.h"
#include "matrix4.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <cstdint>

static void KeyCallback(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods)
{
    if (Key == GLFW_KEY_ESCAPE && Action == GLFW_PRESS)
        glfwSetWindowShouldClose(Window, GL_TRUE);
    if (Key == GLFW_KEY_S && Action == GLFW_PRESS && glfwGetKey(Window, GLFW_KEY_LEFT_SHIFT))
    {

    }
}

int main()
{
    FMatrix4 Mat(4.f, 3.f, 2.f, 2.f,
                 0.f, 1.f, -3.f, 3.f,
                 0.f, -1.f, 3.f, 3.f,
                 0.f, 3.f, 1.f, 1.f);
    std::cout << Mat << std::endl;
    FMatrix4 Inversed = Mat.GetInversed();
    std::cout << Mat << std::endl;
    std::cout <<Inversed;
    Timer tm;
    static const std::uint32_t Width = 1920;
    static const std::uint32_t Height = 1080;
    static const std::uint32_t NumberOfChannels = 4;
    static const std::vector<FShape*> Shapes{new FSphere{{4.f, 4.f, 10.f}, {255, 0, 0, 255}, 2.f},
                                new FSphere{{18.f, 7.f, 12.f}, {0, 128, 192, 255}, 3.f},
                                new FSphere{{-3.f, 0.f, 25.f}, {0, 255, 0, 255}, 2.f},
                                new FSphere{{-90.f, -45.f, 120.f}, {255, 0, 128, 255}, 10.f},
                                new FTriangle{{0.f, 0.f, 10.f}, {255, 255, 0, 255}, {0.f, 3.f, 10.f}, {-3.f, 0.f, 10.f}, {0.f, 0.f, 10.0f}}};

    UImage Image(Width, Height, {20, 15, 40, 255});
    FVector3 CameraCenter(0.f, 0.f, -10.f);
    FVector3 CameraDirection( 0.f, 0.f, 1.f);
    Camera Cam(CameraCenter, CameraDirection, 90.f, 100.f, 0.1f, Image);

    {
        Timer tm2;

        for (std::uint32_t Y = 0; Y < Height; ++Y)
        {
            for (std::uint32_t X = 0; X < Width; ++X)
            {
                FRay RayOut;
                FRay Ray = Cam.GenerateRay(X, Y);
                for (auto item : Shapes) {
                    if (item->Intersect(Ray, RayOut)) {
                        Image[Y * Width + X] = item->Albedo;
                    }
                }
            }
        }
    }

    GLFWwindow* window;

    {
        if (!glfwInit())
            return -1;

        glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
        window = glfwCreateWindow(Image.GetWidth(), Image.GetHeight(), "", NULL, NULL);
        glfwSetWindowPos(window, 100, 100);

        if (!window) {
            glfwTerminate();
            return -1;
        }

        glfwSetKeyCallback(window, KeyCallback);

        glfwMakeContextCurrent(window);
    }

    {
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            std::cout << "Failed to initialize OpenGL context" << std::endl;
            return -1;
        }
    }

    DrawManager DM(&Image);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        DM.Use();
        DM.Draw();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
