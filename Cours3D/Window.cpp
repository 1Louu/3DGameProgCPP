#include "Window.h"

Window::Window()
{
}

void Window::init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    mouseinput = new glm::vec2(0.f, 0.f);
    input = new glm::vec2(0.f, 0.f);
    lastMousePos = new glm::vec2(0.f, 0.f);
    view = glm::mat4(1.0f);
    projection = glm::mat4(1.0f);
    model = glm::mat4(1.0f); 
    angle = -2.0F;
}

void Window::create(int _width, int _height, std::string titre)
{
    width = _width; 
    height = _height; 


    window = glfwCreateWindow(_width, _height, titre.c_str(), NULL, NULL); //glfw vient du c donc il peut pas utiliser les class c++. donc il faut utiliser titre.c_str()
    // glfw CreateWindow(Width, Height , title, [...] )
    if (window == NULL) {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return;
    }

    
    double tmpx;
    double tmpy;

    glfwGetCursorPos(window, &tmpx, &tmpy);

    lastMousePos->x = tmpx;
    lastMousePos->y = tmpy;

    // set contexte de la fenetre ) thread actuel
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);// en gros le probleme vient que la fonction a besoin d une instance de la classe pour etre appellee. donc comment on change cela ? ca sert a quoi static ? static permet d utiliser une fonction d un class sans son instance.
    // framebufferSizeCallback est une fonction qu'on va créer après

    glfwSwapInterval(1);

    //Charger tout les pointeur sur fonction de OpenGL > Glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "failed to initiate GLAD" << std::endl;
        return;
    }

    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //create transofrmations
    projection = glm::perspective(glm::radians(45.0f), (float)_width / (float)_height, 0.1f, 100.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
}

bool Window::isOpen()
{
	return glfwWindowShouldClose(window);
}

void Window::clear(float _r, float _g, float _b)
{
    // Render 
    glClearColor(_r, _g, _b, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::pollEvents()
{
    //swap buffer and poll IO events
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Window::setShader(Shader* _shader)
{
    shader = _shader;
    shader->Use();

    shader->SetMatrix4("projection", projection);
    shader->SetMatrix4("view", view);

}

void Window::setCamera(Camera* _camera)
{
    camera = _camera; 

    view = camera->getMatrice();
}

GLFWwindow* Window::getWindow()
{
    return window;
}

void Window::setModelMatrix4(glm::mat4 _model)
{
    shader->Use();
    model = _model;
    shader->SetMatrix4("model", model);
}

void Window::setDeltaTime(float _time)
{
    time = _time; 
}

glm::mat4 Window::getprojection()
{
    return projection;
}

glm::mat4 Window::getview()
{
    view = camera->getMatrice();
    return view;
}

glm::mat4 Window::getmodel()
{
    return model;
}

void Window::process()
{
    if (input->x || input->y) {
        float d = std::sqrt(std::pow(input->x, 2) + std::pow(input->y, 2));

        float x = d == 0 ? 0 : input->x / d;
        float y = d == 0 ? 0 : input->y / d;

        camera->cameraMovement(glm::vec2(x, y), time);
    }
    else {
        camera->cameraMovement(glm::vec2(0, 0), time); 
    }

}

void Window::close()
{
    glfwSetWindowShouldClose(window, true);
    glfwTerminate();
}

void Window::window_size_callback(GLFWwindow* window, int width, int height)
{
    if (shader) {
        //create transfrmations

        shader->Use();
        glm::mat4 projection = glm::mat4(1.0f);
        if (width != 0 || height != 0) {
            projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
            shader->SetMatrix4("projection", projection);
        }
    }
}

void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) // 
{
    switch (key) {
    case GLFW_KEY_UP:
        if (action == GLFW_RELEASE) {
            input->y -= (1);
        }
        else if (action == GLFW_PRESS) { // faut gerer press et repeat car en soit tant que tu as pas release tu sais que tu es rester appuyer. d ou le probleme quand j ai appuyer sur une autre touche
            input->y += (1);
        }
        break;
    case GLFW_KEY_DOWN:
        if (action == GLFW_RELEASE) {
            input->y += (1);
        }
        else if (action == GLFW_PRESS) {
            input->y -= (1);
        }
        break;
    case GLFW_KEY_LEFT:
        if (action == GLFW_RELEASE) {
            input->x -= (1);
        }
        else if (action == GLFW_PRESS) {
            input->x += (1);
        }
        break;
    case GLFW_KEY_RIGHT:
        if (action == GLFW_RELEASE) {
            input->x += (1);
        }
        else if (action == GLFW_PRESS) {
            input->x -= (1);
        }
        break;
    case GLFW_KEY_W:
        if (action == GLFW_RELEASE) {
            input->y -= (1);
        }
        else if (action == GLFW_PRESS) { // faut gerer press et repeat car en soit tant que tu as pas release tu sais que tu es rester appuyer. d ou le probleme quand j ai appuyer sur une autre touche
            input->y += (1);
        }
        break;
    case GLFW_KEY_S:
        if (action == GLFW_RELEASE) {
            input->y += (1);
        }
        else if (action == GLFW_PRESS) {
            input->y -= (1);
        }
        break;
    case GLFW_KEY_A:
        if (action == GLFW_RELEASE) {
            input->x -= (1);
        }
        else if (action == GLFW_PRESS) {
            input->x += (1);
        }
        break;
    case GLFW_KEY_D:
        if (action == GLFW_RELEASE) {
            input->x += (1);
        }
        else if (action == GLFW_PRESS) {
            input->x -= (1);
        }
        break;
    case GLFW_KEY_TAB:
        if (action == GLFW_PRESS) {
            camera->toggle();
        }
        break; 
    case GLFW_KEY_SPACE:
        if (action == GLFW_PRESS) {
            camera->jump(); 
        }
        break; 
    }

}

void Window::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    double xoffset = xpos - lastMousePos->x;
    double yoffset = lastMousePos->y - ypos; // reversed since y-coordinates range from bottom to top
    lastMousePos->x = xpos;
    lastMousePos->y = ypos;
    mouseinput->x = xoffset;
    mouseinput->y = yoffset; 

    camera->Rotation(glm::vec2(xoffset,yoffset));
    // checker last position of mouse input pour confirmer
}

glm::vec2* Window::lastMousePos = nullptr;
glm::vec2* Window::mouseinput = nullptr;
glm::vec2* Window::input = nullptr;
Camera* Window::camera = nullptr;
Shader* Window::shader = nullptr;