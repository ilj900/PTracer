#include "draw_manager.h"
#include "glad/glad.h"
#include <iostream>

const char* kVertexShaderCode = "#version 440 core\n"
                                "layout (location = 0) in vec3 aPos;\n"
                                "layout (location = 1) in vec2 aTexCoord;\n"
                                "out vec2 TexCoord;\n"
                                "void main()\n"
                                "{\n"
                                "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                "    TexCoord = aTexCoord;\n"
                                "}";
const char* kFragmentShaderCode = "#version 440 core\n"
                                  "in vec2 TexCoord;\n"
                                  "uniform sampler2D Texture;\n"
                                  "out vec4 FragColor;\n"
                                  "void main()\n"
                                  "{\n"
                                  "    FragColor = texture(Texture, vec2(TexCoord.x, 1 - TexCoord.y));\n"
                                  "}";

DrawManager::DrawManager(UImage* Image):
    ImageToDraw(Image) {
    {
        // Create shaders, attach them to program and link them
        auto VertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(VertexShader, 1, &kVertexShaderCode, NULL);
        glCompileShader(VertexShader);

        auto FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(FragmentShader, 1, &kFragmentShaderCode, NULL);
        glCompileShader(FragmentShader);

        ShaderProgram = glCreateProgram();
        glAttachShader(ShaderProgram, VertexShader);
        glAttachShader(ShaderProgram, FragmentShader);
        glLinkProgram(ShaderProgram);

        glDeleteShader(VertexShader);
        glDeleteShader(FragmentShader);
    }

    {
        // Create vertex buffer and vertex array objects, fill the, and configure
        unsigned int VBO;
        glGenBuffers(1, &VBO);
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        float ScreenQuad[] = {-1.f, -1.f, 0.f, 0.f, 0.f,
                              1.f, 1.f, 0.f, 1.f, 1.f,
                              -1.f, 1.f, 0.f, 0.f, 1.f,
                              1.f, 1.f, 0.f, 1.f, 1.f,
                              -1.f, -1.f, 0.f, 0.f, 0.f,
                              1.f, -1.f, 0.f, 1.f, 0.f};
        glBufferData(GL_ARRAY_BUFFER, sizeof(ScreenQuad), ScreenQuad, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }

    {
        // Load and setup texture
        glGenTextures(1, &Texture);
        glBindTexture(GL_TEXTURE_2D, Texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, Image->GetWidth(), Image->GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE,
                     Image->GetData());
        glUniform1i(glGetUniformLocation(ShaderProgram, "Texture"), 0);
    }

    {
        // Set OpenGL parameters
        glClearColor(1.f, 0.f, 1.f, 0.f);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
}

void DrawManager::Use()
{
    glUseProgram(ShaderProgram);
}

void DrawManager::Draw()
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

