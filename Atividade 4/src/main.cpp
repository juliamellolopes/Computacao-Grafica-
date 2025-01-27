#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Shader de Vértices
const char *fonteShaderVertice = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 vColor;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;
void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    vColor = aColor;
}
)";

// Shader de Fragmentos
const char *fonteShaderFragmento = R"(
#version 330 core
in vec3 vColor;
out vec4 CorFrag;
void main() {
    CorFrag = vec4(vColor, 1.0);
}
)";

// Variáveis globais
float camX = 0.0f, camY = 0.0f, camZ = 5.0f;
float camRotX = 0.0f, camRotY = 0.0f;
float camDistance = 5.0f;
bool controlarCubo = false; // Alterna entre controlar o cubo ou a câmera
float cuboRotX = 0.0f, cuboRotY = 0.0f;

void processarEntrada(GLFWwindow *janela) {
    const float velocidade = 0.05f;
    const float rotVelocidade = 0.02f;

    if (glfwGetKey(janela, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(janela, true);

    // Alternar entre controlar câmera e cubo
    if (glfwGetKey(janela, GLFW_KEY_C) == GLFW_PRESS)
        controlarCubo = false;
    if (glfwGetKey(janela, GLFW_KEY_O) == GLFW_PRESS)
        controlarCubo = true;

    if (controlarCubo) {
        // Rotacionar o cubo
        if (glfwGetKey(janela, GLFW_KEY_W) == GLFW_PRESS)
            cuboRotX -= rotVelocidade;
        if (glfwGetKey(janela, GLFW_KEY_S) == GLFW_PRESS)
            cuboRotX += rotVelocidade;
        if (glfwGetKey(janela, GLFW_KEY_A) == GLFW_PRESS)
            cuboRotY -= rotVelocidade;
        if (glfwGetKey(janela, GLFW_KEY_D) == GLFW_PRESS)
            cuboRotY += rotVelocidade;
    } else {
        // Controlar a câmera
        if (glfwGetKey(janela, GLFW_KEY_W) == GLFW_PRESS)
            camDistance -= velocidade;
        if (glfwGetKey(janela, GLFW_KEY_S) == GLFW_PRESS)
            camDistance += velocidade;
        if (glfwGetKey(janela, GLFW_KEY_A) == GLFW_PRESS)
            camRotY -= rotVelocidade;
        if (glfwGetKey(janela, GLFW_KEY_D) == GLFW_PRESS)
            camRotY += rotVelocidade;
        if (glfwGetKey(janela, GLFW_KEY_UP) == GLFW_PRESS)
            camRotX -= rotVelocidade;
        if (glfwGetKey(janela, GLFW_KEY_DOWN) == GLFW_PRESS)
            camRotX += rotVelocidade;
    }
}

void criarCubo(unsigned int &VAO, unsigned int &VBO) {
    float vertices[] = {
        // Posições          // Cores
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, // Preto
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, // Vermelho
         0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f, // Magenta
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f, // Azul

        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f, // Verde
         0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f, // Amarelo
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, // Branco
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f  // Turquesa
    };

    unsigned int indices[] = {
        0, 1, 2, 2, 3, 0, // Face traseira
        4, 5, 6, 6, 7, 4, // Face frontal
        0, 1, 5, 5, 4, 0, // Face inferior
        3, 2, 6, 6, 7, 3, // Face superior
        0, 3, 7, 7, 4, 0, // Face esquerda
        1, 2, 6, 6, 5, 1  // Face direita
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    unsigned int EBO;
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Falha ao inicializar GLFW" << std::endl;
        return -1;
    }

    GLFWwindow *janela = glfwCreateWindow(800, 600, "Cubo com Gradientes", NULL, NULL);
    if (!janela) {
        std::cerr << "Falha ao criar janela GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(janela);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Falha ao inicializar GLEW" << std::endl;
        return -1;
    }

    unsigned int VAO_Cubo, VBO_Cubo;
    criarCubo(VAO_Cubo, VBO_Cubo);

    unsigned int shaderVertice = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shaderVertice, 1, &fonteShaderVertice, NULL);
    glCompileShader(shaderVertice);

    unsigned int shaderFragmento = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shaderFragmento, 1, &fonteShaderFragmento, NULL);
    glCompileShader(shaderFragmento);

    unsigned int programaShader = glCreateProgram();
    glAttachShader(programaShader, shaderVertice);
    glAttachShader(programaShader, shaderFragmento);
    glLinkProgram(programaShader);

    glDeleteShader(shaderVertice);
    glDeleteShader(shaderFragmento);

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(janela)) {
        processarEntrada(janela);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(programaShader);

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        glm::mat4 view = glm::lookAt(
            glm::vec3(camDistance * sin(camRotY) * cos(camRotX), camDistance * sin(camRotX), camDistance * cos(camRotY) * cos(camRotX)),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );
        glm::mat4 model = glm::mat4(1.0f);

        if (controlarCubo) {
            model = glm::rotate(model, cuboRotX, glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, cuboRotY, glm::vec3(0.0f, 1.0f, 0.0f));
        }

        unsigned int projLoc = glGetUniformLocation(programaShader, "projection");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        unsigned int viewLoc = glGetUniformLocation(programaShader, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        unsigned int modelLoc = glGetUniformLocation(programaShader, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        glBindVertexArray(VAO_Cubo);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(janela);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}