#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <learnopengl/shader_s.h>

#define STB_IMAGE_IMPLEMENTATION
#include <learnopengl/stb_image.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 800;

//Variables para el intercambio de la textura
float primeraImagen = 1;
float segundaImagen = 2;

void configurarDatosParaTriangulos(unsigned int VAO, unsigned int VBO, float* vertices, int size);
void dibujarTriangulo(unsigned int VAO, int numTriangulos);

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Defaz Joel - CI:1724915770", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader program
    Shader ourShader("shaders/vertexshader.vs", "shaders/fragmentshader.fs");

    //Vertices para cada triangulo de la figura con su respectivo color y textura
    float trianguloRojo1[] = {
    -0.33f, 0.81f, 0.0f,   1.0f, 0.40f, 0.2f,   0.33f, 0.905f,// A
    -0.38f, 0.56f, 0.0f,   1.0f, 0.40f, 0.2f,   0.31f, 0.78f, // B
    -0.12f, 0.49f, 0.0f,   1.0f, 0.40f, 0.2f,   0.44f, 0.74f// C 
    };

    float trianguloRojo2[] = {
    -0.33f, 0.81f, 0.0f,   1.0f, 0.40f, 0.2f,   0.33f, 0.905f,// A
    -0.12f, 0.49f, 0.0f,   1.0f, 0.40f, 0.2f,   0.44f, 0.74f,// C 
    -0.07f, 0.74f, 0.0f,   1.0f, 0.40f, 0.2f,   0.46f, 0.87f   //D
    };

    float trianguloAmarillo[] = {
    -0.62f, 0.44f, 0.0f,   0.89f, 0.79f, 0.2f,  0.19f, 0.72f,// E
    -0.21f, 0.1f, 0.0f,    0.89f, 0.79f, 0.2f,  0.39f, 0.55f,// F
     0.14f, 0.51f, 0.0f,   0.89f, 0.79f, 0.2f,  0.57f, 0.75f  // U
    };

    float trianguloVerdeOscuro[] = {
    -0.07f,  0.26f, 0.0f,  0.27f, 0.85f, 0.45f, 0.46f, 0.63f,// G
    -0.44f, -0.14f, 0.0f,  0.27f, 0.85f, 0.45f, 0.28f, 0.43f,// H
     0.30f, -0.08f, 0.0f,  0.27f, 0.85f, 0.45f, 0.65f, 0.46f  // I
    };

    float trianguloVerdeClaro[] = {
     -0.44f, -0.14f, 0.0f, 0.58f, 0.85f, 0.27f, 0.28f, 0.43f,// H
     -0.42f, -0.51f, 0.0f, 0.58f, 0.85f, 0.27f, 0.29f, 0.24f,// J
     -0.05f, -0.105f, 0.0f ,0.58f, 0.85f, 0.27f, 0.47f, 0.47f // K
    };

    float trianguloAzul[] = {
     -0.42f, -0.51f, 0.0f,0.26f, 0.58f, 0.87f, 0.29f, 0.24f, // J
     -0.69f, -0.74f, 0.0f, 0.26f, 0.58f, 0.87f, 0.15f, 0.13f,// P
     -0.42f, -0.78f, 0.0f ,0.26f, 0.58f, 0.87f, 0.29f, 0.11f // Q
    };

    float trianguloNaranja[] = {
     0.38f, -0.2f, 0.0f, 0.93f, 0.69f, 0.38f, 0.69f, 0.4f,// R
     0.68f, -0.20f, 0.0f,0.93f, 0.69f, 0.38f, 0.84f, 0.16f,// S
     0.7f, -0.51f, 0.0f, 0.93f, 0.69f, 0.38f, 0.85f, 0.24f  // T
    };

    float trianguloMorado1[] = {
    0.03f, -0.1f, 0.0f, 0.43f, 0.38f, 0.93f, 0.515f, 0.45f,// L
    0.26f, -0.33f, 0.0f, 0.43f, 0.38f, 0.93f, 0.63f, 0.33f,// M
    0.25f, -0.08f, 0.0f ,0.43f, 0.38f, 0.93f, 0.625f, 0.46f  // O
    };

    float trianguloMorado2[] = {
    0.26f, -0.33f, 0.0f, 0.43f, 0.38f, 0.93f, 0.63f, 0.33f,// M
    0.53f, -0.34f, 0.0f, 0.43f, 0.38f, 0.93f, 0.765f, 0.33f, // N 
    0.25f, -0.08f, 0.0f, 0.43f, 0.38f, 0.93f, 0.62f, 0.46f  // O
    };

    unsigned int VBOs[9], VAOs[9];
    glGenVertexArrays(9, VAOs);
    glGenBuffers(9, VBOs);

    configurarDatosParaTriangulos(VAOs[0], VBOs[0], trianguloRojo1, sizeof(trianguloRojo1));
    configurarDatosParaTriangulos(VAOs[1], VBOs[1], trianguloRojo2, sizeof(trianguloRojo2));
    configurarDatosParaTriangulos(VAOs[2], VBOs[2], trianguloAmarillo, sizeof(trianguloAmarillo));
    configurarDatosParaTriangulos(VAOs[3], VBOs[3], trianguloVerdeOscuro, sizeof(trianguloVerdeOscuro));
    configurarDatosParaTriangulos(VAOs[4], VBOs[4], trianguloVerdeClaro, sizeof(trianguloVerdeClaro));
    configurarDatosParaTriangulos(VAOs[5], VBOs[5], trianguloAzul, sizeof(trianguloAzul));
    configurarDatosParaTriangulos(VAOs[6], VBOs[6], trianguloNaranja, sizeof(trianguloNaranja));
    configurarDatosParaTriangulos(VAOs[7], VBOs[7], trianguloMorado1, sizeof(trianguloMorado1));
    configurarDatosParaTriangulos(VAOs[8], VBOs[8], trianguloMorado2, sizeof(trianguloMorado2));

    // load and create a texture 
    unsigned int texture1, texture2;
    // texture 1
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char* data = stbi_load("textures/paisaje.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture 1" << std::endl;
    }
    stbi_image_free(data);
    // texture 2
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // load image, create texture and generate mipmaps
    data = stbi_load("textures/figuras.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture 2" << std::endl;
    }
    stbi_image_free(data);

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    ourShader.use();
    // Se indica cada textura a donde corresponde en el fragment shader
    glUniform1i(glGetUniformLocation(ourShader.ID, "text1"), 0);
    glUniform1i(glGetUniformLocation(ourShader.ID, "text2"), 1);
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        // render the triangle
        ourShader.use();
        // Se indica que textura mostrar para los siguientes triangulos
        ourShader.setFloat("num_text",primeraImagen);
        dibujarTriangulo(VAOs[0], 3);
        dibujarTriangulo(VAOs[1], 3);
        dibujarTriangulo(VAOs[2], 3);
        dibujarTriangulo(VAOs[3], 3);

        // Se indica que textura mostrar para los siguientes triangulos
        ourShader.setFloat("num_text", segundaImagen);
        dibujarTriangulo(VAOs[4], 3);
        dibujarTriangulo(VAOs[5], 3);
        dibujarTriangulo(VAOs[6], 3);
        dibujarTriangulo(VAOs[7], 3);
        dibujarTriangulo(VAOs[8], 3);

        //Se envia la variable del tiempo para el movimiento de la figura
        float tiempo = glfwGetTime();
        ourShader.setFloat("tiempo", tiempo);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //Liberamos recursos�
    int tamano = sizeof(VAOs) / sizeof(VAOs[0]);
    for (int i = 0; i < tamano; i++) {
        glDeleteVertexArrays(1, &VAOs[0]);
        glDeleteBuffers(1, &VBOs[0]);
    }

    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window)
{
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        //Cambia el parametro para intercambiar las texturas
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            primeraImagen = 1;
            segundaImagen = 2;
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            primeraImagen = 2;
            segundaImagen = 1;
        }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

//Metodo qye configura la forma en que s leen los datos y de donde obtener los datos para dibujar utilizando primitivas
void configurarDatosParaTriangulos(unsigned int VAO, unsigned int VBO, float* vertices, int size) {
    glBindVertexArray(VAO);                 //Se indica el VAO  
    glBindBuffer(GL_ARRAY_BUFFER, VBO);     //Se indica el VBO
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), vertices, GL_STATIC_DRAW);      //Se pasan los datos de los vertices
    // Lectura de las coordenadas de posici�n
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Lectura de las coordenadas de color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // Lectura de las coordenadas de textura
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

//Metodo que presenta en la ejecucion mediante el uso de triangulos
void dibujarTriangulo(unsigned int VAO, int numTriangulos) {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, numTriangulos);
}