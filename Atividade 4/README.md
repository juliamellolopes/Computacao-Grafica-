### README para o Projeto "Transformações 3D"

Este projeto demonstra a renderização de um cubo 3D com gradientes de cores em cada face, utilizando OpenGL. O programa inclui controles para manipular a visualização da câmera e do objeto.

---

#### Estrutura do Projeto

Certifique-se de que a estrutura do projeto está assim:

```
Transformacoes/
├── include/
│   ├── GL/
│   │   ├── glew.h
│   │   ├── wglew.h
│   ├── GLFW/
│       ├── glfw3.h
│       ├── glfw3native.h
├── lib/
│   ├── glew32s.lib
│   ├── glfw3.lib
├── src/
│   ├── main.cpp
├── CMakeLists.txt
```

---

#### Passos para Compilar e Executar

1. **Crie a pasta `build` e entre nela**:

   ```bash
   mkdir build; cd build
   ```

2. **Configure o projeto com o CMake**:

   ```bash
   cmake ..
   ```

3. **Compile o projeto**:

   ```bash
   cmake --build .
   ```

4. **Execute o programa**:
   - O executável será gerado na pasta `build/Debug/` (Windows) ou `build/` (Linux/Mac).
   - Execute o programa com:
     ```bash
     ./transformacoes.exe
     ```

---

#### Controles do Programa

- **Movimentação da câmera**:

  - **Aproximar**: Pressione **`W`**.
  - **Afastar**: Pressione **`S`**.
  - **Rotacionar à esquerda**: Pressione **`A`**.
  - **Rotacionar à direita**: Pressione **`D`**.
  - **Rotacionar para cima**: Pressione **Seta para cima**.
  - **Rotacionar para baixo**: Pressione **Seta para baixo**.

- **Controle do objeto (Cubo)**:

  - **Ativar controle do cubo**: Pressione **`O`**.
  - **Rotacionar cubo no eixo X (para cima/baixo)**: Pressione **`W`**/**`S`**.
  - **Rotacionar cubo no eixo Y (para os lados)**: Pressione **`A`**/**`D`**.

- **Alternar entre controle de câmera e objeto**:
  - **Controle da câmera**: Pressione **`C`**.
  - **Controle do cubo**: Pressione **`O`**.

---

#### Recursos do Projeto

- **Gradientes de cores**:

  - Cada face do cubo possui gradientes suaves entre as cores, como mostrado na especificação do projeto. As cores das pontas incluem Preto, Vermelho, Verde, Azul, Magenta, Amarelo e Turquesa, criando um efeito de transição nas arestas.

- **Câmera e objeto manipuláveis**:

  - A câmera pode ser movida em torno do objeto e o cubo pode ser rotacionado nos eixos X e Y de forma independente.

- **Shaders personalizáveis**:
  - O código utiliza shaders de vértices e fragmentos para aplicar as cores e realizar transformações geométricas no espaço 3D.

---
