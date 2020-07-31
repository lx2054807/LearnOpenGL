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
//using namespace glm;
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow* window);
//unsigned int loadTexture(char const* path);
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
//vec3 lightPos(1.2f, 1.0f, 2.0f);
//
//int main()
//{
//    // glfw: initialize and configure
//    // ------------------------------
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//#ifdef __APPLE__
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
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
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//    // glad: load all OpenGL function pointers
//    // ---------------------------------------
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//    {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        return -1;
//    }
//    glEnable(GL_DEPTH_TEST);
//
//    Shader lightingShader("multi_light.vs", "multi_light.fs");
//    Shader CubeShader("light_cube.vs", "light_cube.fs");
//
//    // set up vertex data (and buffer(s)) and configure vertex attributes
//    // ------------------------------------------------------------------
//    float vertices[] = {
//        // positions          // normals           // texture coords
//        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
//         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
//         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
//         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
//
//        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
//         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
//         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
//         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
//
//        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
//        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//
//         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
//         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
//         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//
//        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
//         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
//         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
//         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
//
//        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
//         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
//         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
//         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
//    };
//
//    vec3 cubePositions[] = {
//    vec3(0.0f,  0.0f,  0.0f),
//    vec3(2.0f,  5.0f, -5.0f),
//    vec3(-1.5f, -2.2f, -2.5f),
//    vec3(-3.8f, -2.0f, -2.3f),
//    vec3(2.4f, -0.4f, -3.5f),
//    vec3(-1.7f,  3.0f, -7.5f),
//    vec3(1.3f, -2.0f, -2.5f),
//    vec3(1.5f,  2.0f, -2.5f),
//    vec3(1.5f,  0.2f, -1.5f),
//    vec3(-1.3f,  1.0f, -1.5f)
//    };
//
//    vec3 pointLightPositions[] = {
//       vec3(0.7f,  0.2f,  2.0f),
//       vec3(2.3f, -3.3f, -4.0f),
//       vec3(-4.0f,  2.0f, -2.0f),
//       vec3(0.0f,  0.0f, -3.0f)
//    };
//
//    unsigned int VBO, cubeVAO;
//    glGenVertexArrays(1, &cubeVAO);
//    glGenBuffers(1, &VBO);
//
//    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
//    glBindVertexArray(cubeVAO);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0));
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//    glEnableVertexAttribArray(2);
//
//    unsigned int lightVAO;
//    glGenVertexArrays(1, &lightVAO);
//    glBindVertexArray(lightVAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0));
//    glEnableVertexAttribArray(0);
//
//    unsigned int diffuseMap = loadTexture("container2.png");
//    unsigned int specularMap = loadTexture("container2_specular.png");
//    //unsigned int specularMap = loadTexture("lighting_maps_specular_color.png"); 
//
//    lightingShader.use();
//    lightingShader.setInt("material.diffuse", 0);
//    lightingShader.setInt("material.specular", 1);
//    // uncomment this call to draw in wireframe polygons.
//    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
//    // render loop
//    // -----------
//    while (!glfwWindowShouldClose(window))
//    {
//        // input
//        // -----
//        processInput(window);
//
//        // render
//        // ------
//        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        //vec3 lightPos(sin(glfwGetTime()), 1.0f, 2.0f); // �ƶ���Դ
//        lightingShader.use();
//        lightingShader.setVec3("viewPos", camera.Position);
//        lightingShader.setFloat("material.shininess", 32.0f);
//
//        /*vec3 lightColor;
//        lightColor.x = sin(glfwGetTime() * 2.0f);
//        lightColor.y = sin(glfwGetTime() * 0.7f);
//        lightColor.z = sin(glfwGetTime() * 1.3f);
//
//        vec3 diffuseColor = lightColor * vec3(0.5f);
//        vec3 ambientColor = diffuseColor * vec3(0.2f);*/
//        // directional light
//        lightingShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
//        lightingShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
//        lightingShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
//        lightingShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
//        // point light 1
//        lightingShader.setVec3("pointLights[0].position", pointLightPositions[0]);
//        lightingShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
//        lightingShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
//        lightingShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
//        lightingShader.setFloat("pointLights[0].constant", 1.0f);
//        lightingShader.setFloat("pointLights[0].linear", 0.09);
//        lightingShader.setFloat("pointLights[0].quadratic", 0.032);
//        // point light 2
//        lightingShader.setVec3("pointLights[1].position", pointLightPositions[1]);
//        lightingShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
//        lightingShader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
//        lightingShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
//        lightingShader.setFloat("pointLights[1].constant", 1.0f);
//        lightingShader.setFloat("pointLights[1].linear", 0.09);
//        lightingShader.setFloat("pointLights[1].quadratic", 0.032);
//        // point light 3
//        lightingShader.setVec3("pointLights[2].position", pointLightPositions[2]);
//        lightingShader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
//        lightingShader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
//        lightingShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
//        lightingShader.setFloat("pointLights[2].constant", 1.0f);
//        lightingShader.setFloat("pointLights[2].linear", 0.09);
//        lightingShader.setFloat("pointLights[2].quadratic", 0.032);
//        // point light 4
//        lightingShader.setVec3("pointLights[3].position", pointLightPositions[3]);
//        lightingShader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
//        lightingShader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
//        lightingShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
//        lightingShader.setFloat("pointLights[3].constant", 1.0f);
//        lightingShader.setFloat("pointLights[3].linear", 0.09);
//        lightingShader.setFloat("pointLights[3].quadratic", 0.032);
//        // spotLight
//        lightingShader.setVec3("spotLight.position", camera.Position);
//        lightingShader.setVec3("spotLight.direction", camera.Front);
//        lightingShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
//        lightingShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
//        lightingShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
//        lightingShader.setFloat("spotLight.constant", 1.0f);
//        lightingShader.setFloat("spotLight.linear", 0.09);
//        lightingShader.setFloat("spotLight.quadratic", 0.032);
//        lightingShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
//        lightingShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
//
//        mat4 view;
//        view = camera.GetViewMatrix();
//        lightingShader.setMat4("view", view);
//
//        mat4 projection;
//        projection = perspective(radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//        lightingShader.setMat4("projection", projection);
//
//        mat4 model;
//        lightingShader.setMat4("model", model);
//
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, diffuseMap);
//
//        glActiveTexture(GL_TEXTURE1);
//        glBindTexture(GL_TEXTURE_2D, specularMap);
//
//        glBindVertexArray(cubeVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
//
//        for (unsigned i = 0; i < 10; i++) {
//            model = translate(model, cubePositions[i]);
//            float angle = 20.0f * i;
//            model = rotate(model, radians(angle), vec3(1.0f, 0.3f, 0.5f));
//            lightingShader.setMat4("model", model);
//            glDrawArrays(GL_TRIANGLES, 0, 36);
//        }
//
//        CubeShader.use();
//        CubeShader.setMat4("projection", projection);
//        CubeShader.setMat4("view", view);
//        glBindVertexArray(lightVAO);
//
//        for (unsigned i = 0; i < 4; i++) {
//            model = mat4(1.0f);
//            model = translate(model, pointLightPositions[i]);
//            model = scale(model, vec3(0.2f));
//            CubeShader.setMat4("model", model);
//            glDrawArrays(GL_TRIANGLES, 0, 36);
//        }
//
//        float currentFrame = glfwGetTime();
//        deltaTime = currentFrame - lastFrame;
//        lastFrame = currentFrame;
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
//    glDeleteVertexArrays(1, &lightVAO);
//
//    glDeleteBuffers(1, &VBO);
//
//    // glfw: terminate, clearing all previously allocated GLFW resources.
//    // ------------------------------------------------------------------
//    glfwTerminate();
//    return 0;
//}
//
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
//    int width, height, nrComponents;
//    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
//    if (data) {
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
//    else {
//        cout << "Texture failed to load at path:" << path << endl;
//        stbi_image_free(data);
//    }
//    return textureID;
//}