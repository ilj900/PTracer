#include "utils.h"
#include "sphere.h"
#include "triangle.h"
#include "camera.h"
#include "timing.h"
#include "draw_manager.h"
#include "light.h"

#include "matrix2.h"
#include "matrix4.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "director.h"

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
    Timer tm;

    TheDirector D;

    static const std::uint32_t Width = 1920;
    static const std::uint32_t Height = 1080;
    static const std::uint32_t NumberOfChannels = 4;
    static const std::vector<FShape*> Shapes{new FSphere{{0.f, 0.f, 20.f}, {255, 0, 0, 255}, 5.f}};
    static const std::vector<FLight> Lights{{10.f, 0.f, 20.f}};
    UImage Image(Width, Height, {20, 15, 40, 255});
    FVector3 CameraPosition(0.f, 0.f, -10.f);
    FVector3 CameraDirection( 0.f, 0.f, 1.f);
    Camera Cam(CameraPosition, CameraDirection, 90.f, 100.f, 0.1f, Image);

    {
        Timer tm2;

        for (std::uint32_t Y = 0; Y < Height; ++Y)
        {
            for (std::uint32_t X = 0; X < Width; ++X)
            {
                FRay RayOut;
                FVector3 Normal;
                FRay Ray = Cam.GenerateRay(X, Y);
                for (auto item : Shapes) {
                    try {
                        if (item->Intersect(Ray, RayOut, Normal)) {
                            auto LightDirection = Lights[0].Position.GetVector3() - RayOut.Origin;
                            auto Cos = LightDirection.GetCos(Normal);
                            Cos = Cos > 0.f ? Cos : 0.f;

                            float Scale = (0.1f + Cos) / (1.1f);
                            Image[Y * Width + X] = {std::uint8_t (255.f * Cos),
                                                    0,
                                                    0,
                                                    255};
                        }
                    }
                    catch(...)
                    {
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
        window = glfwCreateWindow(3840, 2160, "", NULL, NULL);
        glfwSetWindowPos(window, 0, 0);

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
