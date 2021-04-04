#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void pre_call_callback_default(const char *name, void *funcptr, int len_args, ...);
void post_call_callback_default(const char *name, void *funcptr, int len_args, ...);
void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

int main(int argc, char *argv[])
{
    if (glfwInit() != GL_TRUE)
    {
        std::cerr << "GLFW failed to initialize" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Needed for Mac OS
#endif

    int width = 1920, height = 1080;
    GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSwapInterval(1);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return EXIT_FAILURE;
    }
    glad_set_pre_callback(pre_call_callback_default);
    glad_set_post_callback(post_call_callback_default);

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(MessageCallback, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    unsigned long long frame_counter = 0;
    while (!glfwWindowShouldClose(window))
    {
        frame_counter++;
        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents(); // glfwWaitEvents()
    }

    std::cout << "Frames: " << frame_counter << std::endl;

    glfwTerminate();
    return EXIT_SUCCESS;
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    std::cout << "Framebuffer resize: " << width << ", " << height << std::endl;
    glViewport(0, 0, width, height);
}

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    // Some debug messages are just annoying informational messages
    if (id == 131185) // glBufferData
        return;

    printf("Message: %s\n", message);
    printf("Source: ");

    switch (source)
    {
        case GL_DEBUG_SOURCE_API:
            printf("API");
            break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            printf("Window System");
            break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            printf("Shader Compiler");
            break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:
            printf("Third Party");
            break;
        case GL_DEBUG_SOURCE_APPLICATION:
            printf("Application");
            break;
        case GL_DEBUG_SOURCE_OTHER:
            printf("Other");
            break;
    }

    printf("\n");
    printf("Type: ");

    switch (type)
    {
        case GL_DEBUG_TYPE_ERROR:
            printf("Error");
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            printf("Deprecated Behavior");
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            printf("Undefined Behavior");
            break;
        case GL_DEBUG_TYPE_PORTABILITY:
            printf("Portability");
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            printf("Performance");
            break;
        case GL_DEBUG_TYPE_MARKER:
            printf("Marker");
            break;
        case GL_DEBUG_TYPE_PUSH_GROUP:
            printf("Push Group");
            break;
        case GL_DEBUG_TYPE_POP_GROUP:
            printf("Pop Group");
            break;
        case GL_DEBUG_TYPE_OTHER:
            printf("Other");
            break;
    }

    printf("\n");
    printf("ID: %d\n", id);
    printf("Severity: ");

    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:
            printf("High");
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            printf("Medium");
            break;
        case GL_DEBUG_SEVERITY_LOW:
            printf("Low");
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            printf("Notification");
            break;
    }

    printf("\n\n");
}

void pre_call_callback_default(const char *name, void *funcptr, int len_args, ...)
{
    std::cout << "GLAD calling " << name << " with " << len_args << " args." << std::endl;
}

void post_call_callback_default(const char *name, void *funcptr, int len_args, ...)
{
    GLenum error_code;
    error_code = glad_glGetError();

    if (error_code != GL_NO_ERROR)
    {
        std::cerr << "GLAD: ERROR " << error_code << " in " <<  name << std::endl;
    }
}