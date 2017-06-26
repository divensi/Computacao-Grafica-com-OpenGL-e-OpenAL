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
        this->rotX_ini = 0; // angulos
        this->rotY_ini = 0;
        this->rotZ_ini = 0;

        this->rotX = rotX_ini; // posicao
        this->rotY = rotX_ini;
        this->rotZ = rotX_ini;

        this->posX = 0; // posicao
        this->posY = 0;
        this->posZ = 0;

        this->posX_ini = 0; // posicao
        this->posY_ini = 0;
        this->posZ_ini = 0;

        this->scaX = 1; // escala
        this->scaY = 1;
        this->scaZ = 1;

        this->nome = "";

        this->animacao = 0;
    }
    Modelo(std::string folder, std::string model)
    {
        this->rotX_ini = 0; // angulos
        this->rotY_ini = 0;
        this->rotZ_ini = 0;

        this->rotX = rotX_ini; // posicao
        this->rotY = rotX_ini;
        this->rotZ = rotX_ini;

        this->posX = 0; // posicao
        this->posY = 0;
        this->posZ = 0;

        this->posX_ini = 0; // posicao
        this->posY_ini = 0;
        this->posZ_ini = 0;

        this->scaX = 1; // escala
        this->scaY = 1;
        this->scaZ = 1;

        this->nome = model;
        this->folder = folder;
        this->importarModelo(folder, model);

        this->animacao = 0;
    }
    Modelo(std::string folder, std::string model,
        float posX, float posY, float posZ,
        float rotX, float rotY, float rotZ)
    {
        this->rotX_ini = rotX; // posicao
        this->rotY_ini = rotY;
        this->rotZ_ini = rotZ;

        this->rotX = rotX; // posicao
        this->rotY = rotY;
        this->rotZ = rotZ;

        this->posX = posX; // posicao
        this->posY = posY;
        this->posZ = posZ;

        this->posX_ini = posX; // posicao
        this->posY_ini = posY;
        this->posZ_ini = posZ;

        this->scaX = 1; // escala
        this->scaY = 1;
        this->scaZ = 1;

        this->nome = model;
        this->folder = folder;
        this->importarModelo(folder, model);

        this->animacao = 0;

    }

    void home();

    std::vector<Vertice> v; // vertices
    std::vector<Vertice> vn; // vertices normal
    std::vector<Vertice> vt; // vertices textura

    std::vector<Membro> membros;
    std::vector<Modelo> filhos;
    std::vector<Animation> animations;

    int animacao;

    void importarModelo(std::string folder, std::string model);

    void renderizar();

    void animar(int animation, int frame, int veloc);

    void reset() {
        this->rotX = rotX_ini; // posicao
        this->rotY = rotY_ini;
        this->rotZ = rotZ_ini;
    }

    int LoadGLTextures();

    std::string nome;
    std::string folder;

    float scaX;
    float scaY;
    float scaZ;

    int rotX;
    int rotY;
    int rotZ;

    int rotX_ini;
    int rotY_ini;
    int rotZ_ini;

    float posX;
    float posY;
    float posZ;

    float posX_ini;
    float posY_ini;
    float posZ_ini;
};
