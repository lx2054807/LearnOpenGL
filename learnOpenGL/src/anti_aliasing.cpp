//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include "shader.h"
//#include "camera.h"
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
//#include <iostream>
//#include <glm/glm/glm.hpp>
//#include <glm/glm/gtc/matrix_transform.hpp>
//#include <glm/glm/gtc/type_ptr.hpp>
//#include <map>
//using namespace glm;
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow* window);
//unsigned int loadTexture(char const* path);
//unsigned int loadCubemap(vector<std::string> faces);
//
//// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//float lastX = SCR_WIDTH / 2.0f;
//float lastY = SCR_HEIGHT / 2.0f;
//Camera camera(vec3(0.0f, 0.0f, 3.0f));
//bool firstMouse = true;
//
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//
//int main()
//{
//    // glfw: initialize and configure
//    // ------------------------------
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_SAMPLES, 8);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//#ifdef __APPLE__
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif
//
//    // glfw window creation
//    // --------------------
//    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
//    if (window == NULL)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//    glfwSetCursorPosCallback(window, mouse_callback);
//    glfwSetScrollCallback(window, scroll_callback);
//
//    // tell GLFW to capture our mouse
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//    // glad: load all OpenGL function pointers
//    // ---------------------------------------
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//    {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        return -1;
//    }
//
//    // configure global opengl state
//    // -----------------------------
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_MULTISAMPLE);
//
//    // build and compile shaders
//    // -------------------------
//    Shader shader("anti_aliasing.vs", "anti_aliasing.fs");
//
//    // set up vertex data (and buffer(s)) and configure vertex attributes
//    // ------------------------------------------------------------------
//
//    GLfloat cubeVertices[] = {
//        // Positions       
//        -0.5f, -0.5f, -0.5f,
//         0.5f, -0.5f, -0.5f,
//         0.5f,  0.5f, -0.5f,
//         0.5f,  0.5f, -0.5f,
//        -0.5f,  0.5f, -0.5f,
//        -0.5f, -0.5f, -0.5f,
//
//        -0.5f, -0.5f,  0.5f,
//         0.5f, -0.5f,  0.5f,
//         0.5f,  0.5f,  0.5f,
//         0.5f,  0.5f,  0.5f,
//        -0.5f,  0.5f,  0.5f,
//        -0.5f, -0.5f,  0.5f,
//
//        -0.5f,  0.5f,  0.5f,
//        -0.5f,  0.5f, -0.5f,
//        -0.5f, -0.5f, -0.5f,
//        -0.5f, -0.5f, -0.5f,
//        -0.5f, -0.5f,  0.5f,
//        -0.5f,  0.5f,  0.5f,
//
//         0.5f,  0.5f,  0.5f,
//         0.5f,  0.5f, -0.5f,
//         0.5f, -0.5f, -0.5f,
//         0.5f, -0.5f, -0.5f,
//         0.5f, -0.5f,  0.5f,
//         0.5f,  0.5f,  0.5f,
//
//        -0.5f, -0.5f, -0.5f,
//         0.5f, -0.5f, -0.5f,
//         0.5f, -0.5f,  0.5f,
//         0.5f, -0.5f,  0.5f,
//        -0.5f, -0.5f,  0.5f,
//        -0.5f, -0.5f, -0.5f,
//
//        -0.5f,  0.5f, -0.5f,
//         0.5f,  0.5f, -0.5f,
//         0.5f,  0.5f,  0.5f,
//         0.5f,  0.5f,  0.5f,
//        -0.5f,  0.5f,  0.5f,
//        -0.5f,  0.5f, -0.5f
//    };
//
//    unsigned int cubeVAO, cubeVBO;
//    glGenVertexArrays(1, &cubeVAO);
//    glGenBuffers(1, &cubeVBO);
//    glBindVertexArray(cubeVAO);
//    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//
//    // draw as wireframe
//    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
//    // render loop
//    // -----------
//    while (!glfwWindowShouldClose(window))
//    {
//        // per-frame time logic
//        // --------------------
//        float currentFrame = glfwGetTime();
//        deltaTime = currentFrame - lastFrame;
//        lastFrame = currentFrame;
//
//        // input
//        // -----
//        processInput(window);
//
//        // render
//        // ------
//        // bind to framebuffer and draw scene as we normally would to color texture 
//
//        // make sure we clear the framebuffer's content
//        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        shader.use();
//        mat4 projection = perspective(camera.Zoom, (GLfloat)SCR_WIDTH / (GLfloat)SCR_HEIGHT, 0.1f, 1000.0f);
//        mat4 view = camera.GetViewMatrix();
//        mat4 model;
//        shader.setMat4("projection", projection);
//        shader.setMat4("view", view);
//        shader.setMat4("model", model);
//
//        glBindVertexArray(cubeVAO);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//        glBindVertexArray(0);
//
//        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//        // -------------------------------------------------------------------------------
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    // optional: de-allocate all resources once they've outlived their purpose:
//    // ------------------------------------------------------------------------
//    glDeleteVertexArrays(1, &cubeVAO);
//    glDeleteBuffers(1, &cubeVBO);
//
//    glfwTerminate();
//    return 0;
//}
//// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
//// ---------------------------------------------------------------------------------------------------------
//void processInput(GLFWwindow* window)
//{
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
//        camera.ProcessKeyboard(FORWARD, deltaTime);
//    }
//    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
//        camera.ProcessKeyboard(BACKWARD, deltaTime);
//    }
//    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
//        camera.ProcessKeyboard(UP, deltaTime);
//    }
//    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
//        camera.ProcessKeyboard(BOTTOM, deltaTime);
//    }
//    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
//        camera.ProcessKeyboard(LEFT, deltaTime);
//    }
//    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
//        camera.ProcessKeyboard(RIGHT, deltaTime);
//    }
//}
//
//// glfw: whenever the window size changed (by OS or user resize) this callback function executes
//// ---------------------------------------------------------------------------------------------
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//    // make sure the viewport matches the new window dimensions; note that width and 
//    // height will be significantly larger than specified on retina displays.
//    glViewport(0, 0, width, height);
//}
//
//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//    if (firstMouse)
//    {
//        lastX = xpos;
//        lastY = ypos;
//        firstMouse = false;
//    }
//
//    float xoffset = xpos - lastX;
//    float yoffset = lastY - ypos;
//    lastX = xpos;
//    lastY = ypos;
//
//    camera.ProcessMouseMovement(xoffset, yoffset);
//}
//
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//    camera.ProcessMouseScroll(yoffset);
//}
//
//unsigned int loadTexture(char const* path) {
//    unsigned int textureID;
//    glGenTextures(1, &textureID);
//
//    int width, height, nrComponents;
//    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
//    if (data)
//    {
//        GLenum format;
//        if (nrComponents == 1)
//            format = GL_RED;
//        else if (nrComponents == 3)
//            format = GL_RGB;
//        else if (nrComponents == 4)
//            format = GL_RGBA;
//
//        glBindTexture(GL_TEXTURE_2D, textureID);
//        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//        stbi_image_free(data);
//    }
//    else
//    {
//        std::cout << "Texture failed to load at path: " << path << std::endl;
//        stbi_image_free(data);
//    }
//    return textureID;
//}
//
//unsigned int loadCubemap(vector<std::string> faces)
//{
//    unsigned int textureID;
//    glGenTextures(1, &textureID);
//    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
//
//    int width, height, nrChannels;
//    for (unsigned int i = 0; i < faces.size(); i++)
//    {
//        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
//        if (data)
//        {
//            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//            stbi_image_free(data);
//        }
//        else
//        {
//            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
//            stbi_image_free(data);
//        }
//    }
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
//
//    return textureID;
//}