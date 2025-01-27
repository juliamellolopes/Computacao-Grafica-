# Nome do projeto
project(transformacoes)

# Configuração de versão do C++
set(CMAKE_CXX_STANDARD 11)

# Arquivos de origem
set(SOURCES
    src/main.cpp
)

# Adicionar executável
add_executable(${PROJECT_NAME} ${SOURCES})

# Diretórios do GLEW
set(GLEW_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/include")
set(GLEW_LIBRARIES "${CMAKE_SOURCE_DIR}/lib/glew32s.lib")

# Diretórios do GLFW
set(GLFW_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/include")
set(GLFW_LIBRARIES "${CMAKE_SOURCE_DIR}/lib/glfw3.lib")

# Diretórios do GLM (adicionar caminho do GLM)
set(GLM_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/include/glm")

# Adicionar diretórios de inclusão
include_directories(${GLEW_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS})

# Linkar bibliotecas
add_definitions(-DGLEW_STATIC)
target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES} ${GLFW_LIBRARIES} OpenGL32)

# Resolver conflitos com MSVCRT
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:MSVCRT")
