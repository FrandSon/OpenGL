#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <learnopengl/shader_s.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 480;

int main()
{
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "B1P3", NULL, NULL);
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

    // Build and Compile our shader program
    Shader ourShader("shaders/shader_B1P3.vs", "shaders/shader_B1P3.fs");

    // Vértices y colores (repetidos según sea necesario para evitar EBO)
    float vertices[] = {
        // positions         // colors
        -0.2f,  0.0f, 0.0f,  0.541f, 0.522f, 0.549f,  // 1
         0.3f,  0.5f, 0.0f,  0.71f, 0.667f, 0.969f,  // 2
         0.3f,  0.0f, 0.0f,  0.878f, 0.408f, 0.055f,   // 3

        -0.2f,  0.0f, 0.0f,  0.541f, 0.522f, 0.549f,  // 1
         0.3f,  0.5f, 0.0f,  0.71f, 0.667f, 0.969f,  // 2
        -0.2f,  0.5f, 0.0f,  0.749f, 0.463f, 0.02f,  // 8

         0.0f,  0.0f, 0.0f,  0.89, 0.616f, 0.106f,  // 5
         0.15f, -0.15f, 0.0f,  0.89, 0.616f, 0.106f,  // 6
        -0.15f, -0.15f, 0.0f,  0.89, 0.616f, 0.106f,   // 7

         0.3f,  0.5f, 0.0f,  0.71f, 0.667f, 0.969f,  // 2
         0.45f, 0.35f, 0.0f, 0.757f, 0.878f, 0.98f,  // 15
         0.3f,  0.2f, 0.0f,  0.573f, 0.922f, 0.09f,   // 13

        -0.2f,  0.5f, 0.0f,  0.749f, 0.463f, 0.02f,  // 8
        -0.2f,  0.7f, 0.0f,  0.424f, 0.294f, 0.49f,  // 10
         0.0f,  0.5f, 0.0f,  0.424f, 0.294f, 0.49f,  // 9

         0.0f,  0.5f, 0.0f,  0.424f, 0.294f, 0.49f,  // 9
        -0.2f,  0.7f, 0.0f,  0.424f, 0.294f, 0.49f,  // 10
         0.0f,  0.7f, 0.0f,  0.655f, 0.302f, 0.839f,  // 11

        -0.2f,  0.5f, 0.0f,  0.749f, 0.463f, 0.02f,  // 8
        -0.2f,  0.7f, 0.0f,  0.424f, 0.294f, 0.49f,  // 10
        -0.4f,  0.5f, 0.0f,  0.0f, 0.0f, 0.0f,  // 12

         0.3f,  0.5f, 0.0f,  0.71f, 0.667f, 0.969f,  // 2
         0.45f, 0.35f, 0.0f,  0.757f, 0.878f, 0.98f,  // 15
         0.45f, 0.65f, 0.0f,  1.0f, 1.0f, 1.0f,   // 4

         0.45f, 0.35f, 0.0f,  0.757f, 0.878f, 0.98f,  // 15
         0.45f, 0.65f, 0.0f,  1.0f, 1.0f, 1.0f,   // 4
         0.75f, 0.65f, 0.0f,  1.0f, 1.0f, 1.0f   // 14
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.use();

        glBindVertexArray(VAO);

        // Draw figures
        glDrawArrays(GL_TRIANGLES, 0, 3);   
        glDrawArrays(GL_TRIANGLES, 3, 3);    
        glDrawArrays(GL_TRIANGLES, 6, 3);   
        glDrawArrays(GL_TRIANGLES, 9, 3); 
        glDrawArrays(GL_TRIANGLES, 12, 3);   
        glDrawArrays(GL_TRIANGLES, 15, 3);   
        glDrawArrays(GL_TRIANGLES, 18, 3);
        glDrawArrays(GL_TRIANGLES, 21, 3); 
        glDrawArrays(GL_TRIANGLES, 24, 3);
        glDrawArrays(GL_TRIANGLES, 27, 3);

        //Get and Set timeValue to make the colors and position dynamic
        float timeValue = glfwGetTime()*0.4;
        ourShader.setFloat("time", timeValue);

        float offset = glfwGetTime();
        ourShader.setFloat("xOffset", offset);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
