#include "Membro.h"
#include "Vertice.h"
#include "Animation.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include <vector>

class Modelo {
public:
    Modelo()
    {
        this->rotX = 0; // angulos
        this->rotY = 0;
        this->rotZ = 0;

        this->posX = 0; // posicao
        this->posY = 0;
        this->posZ = 0;

        this->scaX = 0; // escala
        this->scaY = 0;
        this->scaZ = 0;

        this->nome = "";
    }
    Modelo(std::string folder, std::string model)
    {
        this->rotX = 0; // angulos
        this->rotY = 0;
        this->rotZ = 0;

        this->posX = 0; // posicao
        this->posY = 0;
        this->posZ = 0;

        this->scaX = 0; // escala
        this->scaY = 0;
        this->scaZ = 0;

        this->nome = model;
        this->folder = folder;
        this->importarModelo(folder, model);
    }
    Modelo(std::string folder, std::string model,
        float posX, float posY, float posZ,
        float rotX, float rotY, float rotZ)
    {
        this->rotX = rotX; // posicao
        this->rotY = rotY;
        this->rotZ = rotZ;

        this->posX = posX; // posicao
        this->posY = posY;
        this->posZ = posZ;

        this->scaX = 0; // escala
        this->scaY = 0;
        this->scaZ = 0;

        this->nome = model;
        this->folder = folder;
        this->importarModelo(folder, model);
    }

    std::vector<Vertice> v; // vertices
    std::vector<Vertice> vn; // vertices normal
    std::vector<Vertice> vt; // vertices textura

    std::vector<Membro> membros;
    std::vector<Modelo> filhos;
    std::vector<Animation> animations;

    void importarModelo(std::string folder, std::string model);

    void renderizar();

    void animar(int animation, int frame, int passo, int veloc);

    int LoadGLTextures();

    std::string nome;
    std::string folder;

    float scaX;
    float scaY;
    float scaZ;

    int rotX;
    int rotY;
    int rotZ;

    float posX;
    float posY;
    float posZ;
};
