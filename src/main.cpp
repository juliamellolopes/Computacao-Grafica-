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

// Variáveis globais para controle da câmera
float camX = 0.0f, camY = 0.0f, camZ = 5.0f;
float camRotX = 0.0f, camRotY = 0.0f;
float camDistanceCubo = 5.0f, camDistancePiramide = 5.0f;
bool controlarCubo = true; // Controla qual objeto está ativo

void processarEntrada(GLFWwindow *janela) {
    const float velocidade = 0.05f;
    const float rotVelocidade = 0.02f;

    if (glfwGetKey(janela, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(janela, true);

    // Alternar entre cubo e pirâmide
    if (glfwGetKey(janela, GLFW_KEY_1) == GLFW_PRESS)
        controlarCubo = true;
    if (glfwGetKey(janela, GLFW_KEY_2) == GLFW_PRESS)
        controlarCubo = false;

    // Controlar a distância da câmera
    if (controlarCubo) {
        if (glfwGetKey(janela, GLFW_KEY_W) == GLFW_PRESS)
            camDistanceCubo -= velocidade;
        if (glfwGetKey(janela, GLFW_KEY_S) == GLFW_PRESS)
            camDistanceCubo += velocidade;
    } else {
        if (glfwGetKey(janela, GLFW_KEY_W) == GLFW_PRESS)
            camDistancePiramide -= velocidade;
        if (glfwGetKey(janela, GLFW_KEY_S) == GLFW_PRESS)
            camDistancePiramide += velocidade;
    }

    // Controlar a rotação da câmera
    if (glfwGetKey(janela, GLFW_KEY_A) == GLFW_PRESS)
        camRotY -= rotVelocidade;
    if (glfwGetKey(janela, GLFW_KEY_D) == GLFW_PRESS)
        camRotY += rotVelocidade;
    if (glfwGetKey(janela, GLFW_KEY_UP) == GLFW_PRESS)
        camRotX -= rotVelocidade;
    if (glfwGetKey(janela, GLFW_KEY_DOWN) == GLFW_PRESS)
        camRotX += rotVelocidade;
}

void criarCubo(unsigned int &VAO, unsigned int &VBO) {
    float vertices[] = {
        // Posições          // Cores
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f
    };

    unsigned int indices[] = {
        0, 1, 2, 2, 3, 0, // Face de trás
        4, 5, 6, 6, 7, 4, // Face da frente
        0, 1, 5, 5, 4, 0, // Face de baixo
        2, 3, 7, 7, 6, 2, // Face de cima
        0, 4, 7, 7, 3, 0, // Face da esquerda
        1, 5, 6, 6, 2, 1  // Face da direita
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

void criarPiramide(unsigned int &VAO, unsigned int &VBO) {
    float vertices[] = {
        // Posições         // Cores
        -0.5f, 0.0f, -0.5f,  0.0f, 0.0f, 1.0f,
         0.5f, 0.0f, -0.5f,  0.0f, 0.0f, 1.0f,
         0.5f, 0.0f,  0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f, 0.0f,  0.5f,  0.0f, 0.0f, 1.0f,

         0.0f, 1.0f,  0.0f,  1.0f, 1.0f, 0.0f
    };

    unsigned int indices[] = {
        0, 1, 2, 2, 3, 0, // Base
        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4
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

    GLFWwindow *janela = glfwCreateWindow(800, 600, "Visualizacao 3D", NULL, NULL);
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

    unsigned int VAO_Piramide, VBO_Piramide;
    criarPiramide(VAO_Piramide, VBO_Piramide);

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

        if (controlarCubo) {
            glm::mat4 view = glm::lookAt(
                glm::vec3(camDistanceCubo * sin(camRotY) * cos(camRotX), camDistanceCubo * sin(camRotX), camDistanceCubo * cos(camRotY) * cos(camRotX)),
                glm::vec3(-1.5f, 0.0f, 0.0f),
                glm::vec3(0.0f, 1.0f, 0.0f)
            );
            glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(-1.5f, 0.0f, 0.0f));

            unsigned int projLoc = glGetUniformLocation(programaShader, "projection");
            glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

            unsigned int viewLoc = glGetUniformLocation(programaShader, "view");
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

            unsigned int modelLoc = glGetUniformLocation(programaShader, "model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

            glBindVertexArray(VAO_Cubo);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        } else {
            glm::mat4 view = glm::lookAt(
                glm::vec3(camDistancePiramide * sin(camRotY) * cos(camRotX), camDistancePiramide * sin(camRotX), camDistancePiramide * cos(camRotY) * cos(camRotX)),
                glm::vec3(1.5f, 0.0f, 0.0f),
                glm::vec3(0.0f, 1.0f, 0.0f)
            );
            glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, 0.0f, 0.0f));

            unsigned int projLoc = glGetUniformLocation(programaShader, "projection");
            glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

            unsigned int viewLoc = glGetUniformLocation(programaShader, "view");
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

            unsigned int modelLoc = glGetUniformLocation(programaShader, "model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

            glBindVertexArray(VAO_Piramide);
            glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
        }

        glfwSwapBuffers(janela);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}