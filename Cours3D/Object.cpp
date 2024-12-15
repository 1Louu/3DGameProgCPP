#include "Object.h"

//je vais refaire une petite partie theorique

Object::Object(void* _vertice,  size_t _datasize) 
    : vertice(_vertice)
{
//tu peux avoir plusieur objet donc autant avoir un seul programme
    // Create new variable with uid  in buffer
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // Bind vertex buffer then configure vertex
    glBindVertexArray(VAO);

    //specify variable type
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, _datasize, vertice, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

}

Object::Object(std::string _path)
{
    datasize = setObjFile(_path); 

    // Create new variable with uid  in buffer
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // Bind vertex buffer then configure vertex
    glBindVertexArray(VAO);

    //specify variable type
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, datasize * sizeof(float), vertice, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Object::setAttrib(int _locationID, int _dimension, int _type, size_t _sizefullVertex, void* startOffset)
{
    glBindVertexArray(VAO);

    //specify variable type
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(_locationID, _dimension, _type, GL_FALSE, _sizefullVertex, startOffset);
    glEnableVertexAttribArray(_locationID);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Object::draw(int drawmode, int start, int nb)
{
    glBindVertexArray(VAO);
    glDrawArrays(drawmode, start, nb); // 1er digit : début du tableau, 2eme digit, fin du tableau
    glBindVertexArray(0);
}


void Object::discard()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

size_t Object::setObjFile(std::string _path)
{
    std::vector <glm::vec3> vertex;
    std::vector <glm::vec2> vertextexture;
    std::vector <glm::vec3> vertexnormal;
    std::vector <unsigned int> faces;
    float t, t2;
    unsigned int i, i2, i3;

    std::string ch;
    std::string line;
    float vx, vy, vz;

    try
    {
        std::ifstream objFile;
        objFile.open(_path);
        while (line, std::getline(objFile, line)) {

            std::stringstream ss(line);
            ss >> ch;
            if (ch == "v") {
                ss >> vx;
                ss >> vy;
                ss >> vz;
                vertex.push_back(glm::vec3(vx, vy, vz));
            }
            if (ch == "vt") {
                ss >> t;
                ss >> t2;
                vertextexture.push_back(glm::vec2(t, t2));
            }
            if (ch == "vn") {
                ss >> vx;
                ss >> vy;
                ss >> vz; 
                vertexnormal.push_back(glm::vec3(vx,vy, vz));
            }
            if (ch == "f") {
                std::string tmp;
                std::stringstream t;

                for (int k = 0; k < 3; k++) {
                    ss >> tmp;
                    t = std::stringstream(tmp);
                    std::getline(t, tmp, '/');
                    i = std::stoi(tmp);
                    std::getline(t, tmp, '/');
                    i2 = std::stoi(tmp);
                    std::getline(t, tmp, '/');
                    i3 = std::stoi(tmp);
                    faces.push_back(i);
                    faces.push_back(i2);
                    if(i3)
                        faces.push_back(i3);
                }
            }
        }
        objFile.close();
        // partie création float; 
        std::cout << faces.size() << std::endl; 
        if (vertexnormal.empty()) {
            std::vector <glm::vec3> vertexorderbytriangle;
            for (int a = 0; a < faces.size(); a += 3) {
                // vertex
                vx = vertex[faces[a] - 1].x;
                vy = vertex[faces[a] - 1].y;
                vz = vertex[faces[a] - 1].z;
                vertexorderbytriangle.push_back(glm::vec3(vx, vy, vz));
            }
            // Tableau vertexorderbytriangle rempli, on génére les normals; 
            for (int a = 0; a < vertexorderbytriangle.size(); a += 3) {
                glm::vec3 p1 = vertexorderbytriangle[a];
                glm::vec3 p2 = vertexorderbytriangle[a+1];
                glm::vec3 p3 = vertexorderbytriangle[a+2];

                glm::vec3 u = p2 - p1; 
                glm::vec3 v = p3 - p1; 

                glm::vec3 normal = glm::cross(u,v);

                vertexnormal.push_back(normal);
                vertexnormal.push_back(normal);
                vertexnormal.push_back(normal);
                std::vector<unsigned int>::iterator it; 
                it = faces.begin(); 
                faces.insert(it, a / 3 + 1);

            }
        }

        for (int a = 0; a < faces.size() ; a += 3) {
            // vertex
            vx = vertex[faces[a]-1].x;
            vy = vertex[faces[a]-1].y;
            vz = vertex[faces[a]-1].z;
            test.push_back(vx);
            test.push_back(vy);
            test.push_back(vz);

            // vertex texture 
            vx = vertextexture[faces[a + 1]-1].x;
            vy = vertextexture[faces[a + 1]-1].y;
            test.push_back(vx);
            test.push_back(vy);

            // vertex normal ( on saute ok ? )
            // Lq je veux essayer de calculer des normal authomatiquement et pas prendre celle de blender 
            vx = vertexnormal[faces[a + 2] - 1].x;
            vy = vertexnormal[faces[a + 2] - 1].y;
            vz = vertexnormal[faces[a + 2] - 1].z;
            test.push_back(vx);
            test.push_back(vy);
            test.push_back(vz);

        }
        //for (int i = 0; i < test.size(); i += 8*3) {
        //    glm::vec3 p1(test[i], test[i+1], test[i+2]);
        //    glm::vec3 p2(test[i+8], test[i +8+ 1], test[i+8 + 2]);
        //    glm::vec3 p3(test[i+8*2], test[i + 8 * 2 + 1], test[i + 8 * 2 + 2]);
        //
        //    glm::vec3 v = p2 - p1;
        //    glm::vec3 u = p3 - p1;

        //    glm::vec3 n = glm::cross(v, u);

        //    // + 0 == position 3 float
        //    // + 3 == texcoor 2 float
        //    // + 5 == normal 3 float
        //    // total = 8

        //    test[i + 5] = n.x;
        //    test[i + 5 + 1] = n.y;
        //    test[i + 5 + 2] = n.z;
        //    test[i + 8 * 1 + 5] = n.x;
        //    test[i + 8 * 1 + 5 + 1] = n.y;
        //    test[i + 8 * 1 + 5 + 2] = n.z;
        //    test[i + 8 * 2 + 5] = n.x;
        //    test[i + 8 * 2 + 5 + 1] = n.y;
        //    test[i + 8 * 2 + 5 + 2] = n.z;
        //}

        vertice = test.data();

    }
    catch (std::ifstream::failure& e) {
        std::cout << "ERROR OBJ : File cant be read; " << e.what() << std::endl;
        return test.size();
    }

    return test.size();
}

size_t Object::getdatasize()
{
    return datasize;
}
