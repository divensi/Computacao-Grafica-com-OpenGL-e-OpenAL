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
        this->angX = 0; // angulos
        this->angY = 0;
        this->angZ = 0;

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
        this->angX = 0; // angulos
        this->angY = 0;
        this->angZ = 0;

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
        float angX, float angY, float angZ)
    {
        this->angX = angX; // posicao
        this->angY = angY;
        this->angZ = angZ;

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

    void animar(int animation);

    int LoadGLTextures();

    std::string nome;
    std::string folder;

    float scaX;
    float scaY;
    float scaZ;

    float angX;
    float angY;
    float angZ;

    float posX;
    float posY;
    float posZ;
};
