#include <GLFW/glfw3.h>
#include <GLUT/glut.h>
#include <glm/trigonometric.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "src/Chunk.h"
#include "src/Renderer.h"
#include "src/Camera.h"
#include "src/Context.h"

void processInput(GLFWwindow *window, Camera &camera, float deltaTime);

void mouseCallback(GLFWwindow *window, double xpos, double ypos);

void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);

void setupOpenGL();

void drawCrosshair();

void spawnBlock(Chunk &chunk, const Camera &camera, float spawnDistance, GLFWwindow *window);

void scrollCallback(GLFWwindow *window, double xoffset, double yoffset);

void setupLighting();

float lastX = 400, lastY = 300;
bool firstMouse = true;

int main()
{
    if (!glfwInit())
    {
        return -1;
    }

    GLFWwindow *window = glfwCreateWindow(800, 600, "Voxel Engine", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    Context context;
    context.chunk.setVoxel(1, 1, 1, DIRT);
    context.chunk.setVoxel(2, 1, 1, GRASS); // Add more voxels for testing
    context.chunk.setVoxel(1, 2, 1, STONE);

    // Set the window user pointer to the context before setting callbacks
    glfwSetWindowUserPointer(window, &context);

    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetScrollCallback(window, scrollCallback);

    // Capture the mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Initialize FreeGLUT
    int argc = 1;
    char *argv[1] = {(char *) "VoxelEngine"};
    glutInit(&argc, argv);

    // Setup OpenGL
    setupOpenGL();
    setupLighting();

    Renderer renderer;

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        static float lastFrame = 0.0f;
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window, context.camera, deltaTime);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glMultMatrixf(glm::value_ptr(context.camera.getViewMatrix()));

        renderer.renderChunk(context.chunk);
        drawCrosshair();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window, Camera &camera, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    camera.processKeyboard(window, deltaTime);
}

void mouseCallback(GLFWwindow *window, double xpos, double ypos)
{
    Context *context = static_cast<Context *>(glfwGetWindowUserPointer(window));

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xOffset = xpos - lastX;
    float yOffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    context->camera.processMouse(xOffset, yOffset);
}

void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        Context *context = static_cast<Context *>(glfwGetWindowUserPointer(window));
        spawnBlock(context->chunk, context->camera, 4.0f, window);
    }
}

void setupOpenGL()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 4.0 / 3.0, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void drawCrosshair()
{
    int width, height;
    glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, width, height, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(width / 2 - 10, height / 2);
    glVertex2f(width / 2 + 10, height / 2);
    glVertex2f(width / 2, height / 2 - 10);
    glVertex2f(width / 2, height / 2 + 10);
    glEnd();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void spawnBlock(Chunk &chunk, const Camera &camera, float spawnDistance, GLFWwindow *window)
{
    glm::vec3 cameraPos = camera.getPosition();
    glm::vec3 cameraFront = camera.getFront();

    glm::vec3 blockPos = cameraPos + cameraFront * spawnDistance;
    int x = static_cast<int>(round(blockPos.x));
    int y = static_cast<int>(round(blockPos.y));
    int z = static_cast<int>(round(blockPos.z));

    if (x >= 0 && x < CHUNK_SIZE && y >= 0 && y < CHUNK_SIZE && z >= 0 && z < CHUNK_SIZE)
    {
        Context *context = static_cast<Context *>(glfwGetWindowUserPointer(window));
        chunk.setVoxel(x, y, z, context->currentBlockType);
    }
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    Context* context = static_cast<Context*>(glfwGetWindowUserPointer(window));

    // Cycle through block types on scroll
    if (yoffset > 0) {
        context->currentBlockType = static_cast<VoxelType>((context->currentBlockType + 1) % 6); // Assuming 6 block types
    } else if (yoffset < 0) {
        context->currentBlockType = static_cast<VoxelType>((context->currentBlockType - 1 + 6) % 6); // Assuming 6 block types
    }
}


void setupLighting()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat diffuseLight[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat lightPosition[] = {1.0f, 1.0f, 1.0f, 0.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}