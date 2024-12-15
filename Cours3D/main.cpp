// Cours3D.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Window.h"
#include "Object.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"

std::vector <float> test; 

float d12[] = {
    0.000000, - 1.000000, 0.000000, 0.000069, 0.818137,
    0.723600, - 0.447215, 0.525720, 0.000069, 0.818137,
    -0.276385, - 0.447215, 0.850640, 0.000069, 0.818137,

    0.723600, - 0.447215, 0.525720, 0.157508, 0.727241,
    0.000000, - 1.000000, 0.000000, 0.157508, 0.727241,
    0.723600, - 0.447215, - 0.525720, 0.157508, 0.727241,

    0.000000, -1.000000, 0.000000, 0.157508, 0.909034,
    -0.276385, - 0.447215, 0.850640,0.157508, 0.909034,
    -0.894425, - 0.447215, 0.000000,0.157508, 0.909034,

    0.000000, -1.000000, 0.000000, 0.000069, 0.636344,
    -0.894425, -0.447215, 0.000000,0.000069, 0.636344,
    -0.276385, - 0.447215, - 0.850640, 0.000069, 0.636344,

    0.000000, -1.000000, 0.000000, 0.157508, 0.545448,
    -0.276385, - 0.447215, - 0.850640,0.157508, 0.545448,
    0.723600, - 0.447215, - 0.525720,0.157508, 0.545448,

    0.723600, -0.447215, 0.525720,0.000069, 0.090965,
    0.723600, - 0.447215, - 0.525720,0.000069, 0.090965,
    0.894425, 0.447215, 0.000000,0.000069, 0.090965,

    -0.276385, - 0.447215, 0.850640,0.157508, 0.000069,
    0.723600, - 0.447215, 0.525720,0.157508, 0.000069,
    0.276385, 0.447215, 0.850640,0.157508, 0.000069,

    -0.276385, - 0.447215, 0.850640,0.157508, 0.181862,
    0.723600, - 0.447215, 0.525720,0.157508, 0.181862,
    0.276385, 0.447215, 0.850640,0.157508, 0.181862,

    -0.894425, - 0.447215, 0.000000,0.000069, 0.272758,
    -0.276385, - 0.447215, 0.850640,0.000069, 0.272758,
    -0.723600, 0.447215, 0.525720,0.000069, 0.272758,

    -0.276385, - 0.447215, - 0.850640,0.157508, 0.363655,
    -0.894425, - 0.447215, 0.000000,0.157508, 0.363655,
    -0.723600, 0.447215, - 0.525720,0.157508, 0.363655,
    
    0.723600, - 0.447215, - 0.525720,0.000069, 0.454551,
    - 0.276385, - 0.447215, - 0.850640,0.000069, 0.454551,
    0.276385, 0.447215, - 0.850640,0.000069, 0.454551,

    0.723600, - 0.447215, 0.525720,0.314946, 0.636344,
    0.894425, 0.447215, 0.000000,0.314946, 0.636344,
    0.276385, 0.447215, 0.850640,0.314946, 0.636344,

    - 0.276385, - 0.447215, 0.850640,0.314946, 0.818137,
    0.276385, 0.447215, 0.850640,0.314946, 0.818137,
    - 0.723600, 0.447215, 0.525720,0.314946, 0.818137,

    - 0.894425, - 0.447215, 0.000000,0.314946, 0.090965,
    - 0.723600, 0.447215, 0.525720,0.314946, 0.090965,
    - 0.723600, 0.447215, - 0.525720,0.314946, 0.090965,

    - 0.276385, - 0.447215, - 0.850640,0.314946, 0.272758,
    - 0.723600, 0.447215, - 0.525720,0.314946, 0.272758,
    0.276385, 0.447215, - 0.850640,0.314946, 0.272758,

    0.723600, - 0.447215, - 0.525720,0.314946, 0.454551,
    0.276385, 0.447215, - 0.850640,0.314946, 0.454551,
    0.894425, 0.447215, 0.000000,0.314946, 0.454551,

    0.276385, 0.447215, 0.850640,0.314946, 0.999931,
    0.894425, 0.447215, 0.000000,0.314946, 0.999931,
    0.000000, 1.000000, 0.000000,0.314946, 0.999931,

    - 0.723600, 0.447215, 0.525720,0.472386, 0.727241,
    0.276385 ,0.447215, 0.850640,0.472386, 0.727241,
    0.000000, 1.000000, 0.000000,0.472386, 0.727241,

    - 0.723600, 0.447215, - 0.525720,0.472386, 0.909034,
    0.276385, 0.447215, 0.850640,0.472386, 0.909034,
    0.000000, 1.000000, 0.000000,0.472386, 0.909034,

    - 0.723600, 0.447215, - 0.525720,0.472386, 0.181862,
    - 0.723600, 0.447215, 0.525720,0.472386, 0.181862,
    0.000000, 1.000000, 0.000000,0.472386, 0.181862,

    0.276385, 0.447215, - 0.850640,0.472386, 0.363655,
    - 0.723600, 0.447215, - 0.525720,0.472386, 0.363655,
    0.000000, 1.000000, 0.000000,0.472386, 0.363655,

    0.894425, 0.447215, 0.000000,0.472386, 0.545448,
    0.276385, 0.447215, - 0.850640,0.472386, 0.545448,
    0.000000, 1.000000, 0.000000,0.472386, 0.545448,
};

float cube[] = {
    //Face avant
     0.5f, -0.5f, 0.5f, 1.f, 1.f, // R-D
     0.5f,  0.5f, 0.5f, 1.f, 0.f, // R-T
    -0.5f, -0.5f, 0.5f, 0.f, 1.f, // L-D
    -0.5f, -0.5f, 0.5f, 0.f, 1.f, // L-D
     0.5f,  0.5f, 0.5f, 1.f, 0.f, // R-T
    -0.5f,  0.5f, 0.5f, 0.f, 0.f, // 
    //Face droite
    0.5f, -0.5f,  0.5f, 0.f, 1.f,
    0.5f,  0.5f,  0.5f, 0.f, 0.f,
    0.5f,  0.5f, -0.5f, 1.f, 0.f,
    0.5f, -0.5f,  0.5f, 0.f, 1.f,
    0.5f, -0.5f, -0.5f, 1.f, 1.f,
    0.5f,  0.5f, -0.5f, 1.f, 0.f,
    //Face gauche
    -0.5f, -0.5f,  0.5f, 1.f, 1.f,
    -0.5f,  0.5f,  0.5f, 1.f, 0.f,
    -0.5f,  0.5f, -0.5f, 0.f, 0.f,
    -0.5f, -0.5f,  0.5f, 1.f, 1.f,
    -0.5f, -0.5f, -0.5f, 0.f, 1.f,
    -0.5f,  0.5f, -0.5f, 0.f, 0.f,
    //Face haute
    -0.5f, 0.5f,  0.5f, 0.f, 1.f,
     0.5f, 0.5f,  0.5f, 1.f, 1.f,
    -0.5f, 0.5f, -0.5f, 0.f, 0.f,
     0.5f, 0.5f,  0.5f, 1.f, 1.f,
     0.5f, 0.5f, -0.5f, 1.f, 0.f,
    -0.5f, 0.5f, -0.5f, 0.f, 0.f,
    //Face basse
    -0.5f, -0.5f,  0.5f, 0.f, 0.f,
     0.5f, -0.5f,  0.5f, 1.f, 0.f,
    -0.5f, -0.5f, -0.5f, 0.f, 1.f,
     0.5f, -0.5f,  0.5f, 1.f, 0.f,
     0.5f, -0.5f, -0.5f, 1.f, 1.f,
    -0.5f, -0.5f, -0.5f, 0.f, 1.f,
    // Face arrière
     0.5f, -0.5f, -0.5f, 1.f, 1.f,
     0.5f,  0.5f, -0.5f, 1.f, 0.f,
    -0.5f, -0.5f, -0.5f, 0.f, 1.f,
    -0.5f, -0.5f, -0.5f, 0.f, 1.f,
     0.5f,  0.5f, -0.5f, 1.f, 0.f,
    -0.5f,  0.5f, -0.5f, 0.f, 0.f,
};

float vertices[] = {
    //Face avant
     0.5f, -0.5f, 0.5f, 1.f, 1.f, // R-D
     0.5f,  0.5f, 0.5f, 1.f, 0.f, // R-T
    -0.5f, -0.5f, 0.5f, 0.f, 1.f, // L-D
    -0.5f, -0.5f, 0.5f, 0.f, 1.f, // L-D
     0.5f,  0.5f, 0.5f, 1.f, 0.f, // R-T
    -0.5f,  0.5f, 0.5f, 0.f, 0.f, // 
    //Face droite
    0.5f, -0.5f,  0.5f, 0.f, 1.f,
    0.5f,  0.5f,  0.5f, 0.f, 0.f,
    0.5f,  0.5f, -0.5f, 1.f, 0.f,
    0.5f, -0.5f,  0.5f, 0.f, 1.f,
    0.5f, -0.5f, -0.5f, 1.f, 1.f,
    0.5f,  0.5f, -0.5f, 1.f, 0.f,
    //Face gauche
    -0.5f, -0.5f,  0.5f, 1.f, 1.f,
    -0.5f,  0.5f,  0.5f, 1.f, 0.f,
    -0.5f,  0.5f, -0.5f, 0.f, 0.f, 
    -0.5f, -0.5f,  0.5f, 1.f, 1.f, 
    -0.5f, -0.5f, -0.5f, 0.f, 1.f, 
    -0.5f,  0.5f, -0.5f, 0.f, 0.f,
    //Face haute
    -0.5f, 0.5f,  0.5f, 0.f, 1.f,
     0.5f, 0.5f,  0.5f, 1.f, 1.f,
    -0.5f, 0.5f, -0.5f, 0.f, 0.f,
     0.5f, 0.5f,  0.5f, 1.f, 1.f,
     0.5f, 0.5f, -0.5f, 1.f, 0.f,
    -0.5f, 0.5f, -0.5f, 0.f, 0.f,
    //Face basse
    -0.5f, -0.5f,  0.5f, 0.f, 0.f,
     0.5f, -0.5f,  0.5f, 1.f, 0.f,
    -0.5f, -0.5f, -0.5f, 0.f, 1.f,
     0.5f, -0.5f,  0.5f, 1.f, 0.f,
     0.5f, -0.5f, -0.5f, 1.f, 1.f,
    -0.5f, -0.5f, -0.5f, 0.f, 1.f,
    // Face arrière
     0.5f, -0.5f, -0.5f, 1.f, 1.f,
     0.5f,  0.5f, -0.5f, 1.f, 0.f,
    -0.5f, -0.5f, -0.5f, 0.f, 1.f,
    -0.5f, -0.5f, -0.5f, 0.f, 1.f,
     0.5f,  0.5f, -0.5f, 1.f, 0.f,
    -0.5f,  0.5f, -0.5f, 0.f, 0.f,
};


// constants ; 
const unsigned int WIDTH_SCREEN = 1600; 
const unsigned int HEIGHT_SCREEN = 1200; 

int main()
{

    Window w; 
    w.init(); 
    w.create(WIDTH_SCREEN, HEIGHT_SCREEN, "CoursC++");
    Shader s("./vertexShader.shader", "./fragmentShader.shader");
    w.setShader(&s);
    s.Use();
    Camera c(glm::vec3(0,1,-2));
    w.setCamera(&c);
    s.SetVector3("lightColor", 0.1f, 1.0f, 1.0f);
    s.SetVector3("objectColor", 1.0f, 1.0f, 1.0f);
    s.SetVector3("viewPos", c.getcamPos() );
    s.SetFloat("ambiantStrength", 0.1f);
    glm::vec3 lightPosition(1, 1, -1);
    s.SetVector3("lightPos", lightPosition);

    Shader shaderLight("./vertexLight.shader", "fragLight.shader");
    std::cout << "Hello World!\n";


    shaderLight.Use();
    shaderLight.SetMatrix4("projection", w.getprojection());
    shaderLight.SetMatrix4("view", w.getview());
    
    glm::mat4 model3 = glm::mat4(1.0f);
    model3 = glm::translate(model3, lightPosition);
    model3 = glm::scale(model3, glm::vec3(0.2f, 0.2f, 0.2f));
    shaderLight.SetMatrix4("model", model3);

    

    //Object o(cube, sizeof(cube)); 
    //Object o(test.data(), test.size());
    Object o("./objects/test-building.obj");
    o.setAttrib(0, 3, GL_FLOAT, sizeof(float) * 8, 0);
    o.setAttrib(1, 2, GL_FLOAT, sizeof(float) * 8, (void*)(3 * sizeof(float)));
    o.setAttrib(2, 3, GL_FLOAT, sizeof(float) * 8, (void*)(5 * sizeof(float)));

    Texture t; 

    t.LoadTexture("./image.jpg");

    Texture t2;

    t2.LoadTexture("./image.png");

    s.Use();
    s.SetInt("texture", 0);
    float angle = 0;
    // render loop 

    double currentFrame = glfwGetTime();
    double lastFrame = currentFrame;
    double deltaTime;

    while (!w.isOpen()) {
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        w.setDeltaTime(deltaTime);
        w.process(); 

        //Intputs
        if (glfwGetKey(w.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            w.close();
        }

        w.pollEvents();
        w.clear(0.1f, 0.1f, 0.1f);

        

        s.Use();
        s.SetVector3("viewPos", c.getcamPos());
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0, 0, 0));
        model = glm::rotate(model, glm::radians(angle), glm::vec3(0, 1, 0));
        //w.setModelMatrix4(model);
        s.SetMatrix4("model", model);
        s.SetMatrix4("view", w.getview());
        t.activeTexture(); 
        o.draw(GL_TRIANGLES, 0, 9504);

        shaderLight.Use();
        shaderLight.SetMatrix4("projection", w.getprojection());
        shaderLight.SetMatrix4("view", w.getview());
        o.draw(GL_TRIANGLES, 0, 9504);
        //model = glm::mat4(1.0f);
        //model = glm::translate(model, glm::vec3(1, 0, 0));
        //model = glm::rotate(model, glm::radians(angle), glm::vec3(0.5f, 0.2f, 0.1f));
        //w.setModelMatrix4(model);
        //o.draw(GL_TRIANGLES, 0, 720);

        //t2.activeTexture();

        angle -= 0;
    }

    shaderLight.Shutdown(); 
    s.Shutdown();
    o.discard();

    return 0; 
}


// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
