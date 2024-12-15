#ifndef OBJECT_H__
#define OBJECT_H__
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

class Object {

    unsigned int VBO, VAO;
    std::vector <float> test;
    void* vertice;
    int dimensionVertice;
    int dimensionTexture; 
    int type; 
    size_t datasize; 
    size_t sizefullVertex;
    void* startVertex;
    void* startTexture;
public:
    Object(void* _vertice, size_t _datasize);
    Object(std::string _path); 
    void setAttrib(int _locationID, int _dimension,int _type, size_t _sizefullVertex, void* startOffset);
    void draw(int drawmode, int start, int nb);
    void discard(); 
    size_t setObjFile(std::string _path);
    size_t getdatasize(); 
};

#endif