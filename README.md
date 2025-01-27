### README para o Projeto "Transformações 3D"

Este projeto demonstra a renderização de dois objetos 3D (cubo e pirâmide) com cores distintas para cada face, utilizando OpenGL. Ele também inclui controles de câmera para manipular a visualização de cada objeto individualmente.

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

- **Alternar entre objetos**:

  - Pressione **`1`** para selecionar o **cubo**.
  - Pressione **`2`** para selecionar a **pirâmide**.

- **Movimentação da câmera**:
  - **Aproximar**: Pressione **`W`**.
  - **Afastar**: Pressione **`S`**.
  - **Rotacionar à esquerda**: Pressione **`A`**.
  - **Rotacionar à direita**: Pressione **`D`**.
  - **Rotacionar para cima**: Pressione **Seta para cima**.
  - **Rotacionar para baixo**: Pressione **Seta para baixo**.

---

#### Recursos do Projeto

- **Cores distintas por face**:

  - Cada face do cubo e da pirâmide tem cores únicas para facilitar a diferenciação durante a rotação.

- **Controle de objetos independentes**:

  - A câmera ajusta sua posição e distância para o objeto selecionado (cubo ou pirâmide).

- **Shaders personalizáveis**:
  - O código utiliza shaders de vértices e fragmentos para aplicar cores e realizar transformações.

---

Se precisar de mais instruções ou ajuda, é só avisar! 😊
