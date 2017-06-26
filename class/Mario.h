#include <GL/gl.h>
#include <GL/glut.h>
#include <vector>

class Mario {
public:
    Mario()
    {
        rotX = 0; // rotulos
        rotY = 0;
        rotZ = 0;

        posX = 0; // posicao
        posY = 0;
        posZ = 0;

        scaX = 0; // escala
        scaY = 0;
        scaZ = 0;

        acao = "idle";

        this->importarHierarquia();
    }

    Modelo obj;

    std::string acao;

    void animate(int value);

    static void makeSound(const char * filename);

    void importarHierarquia();

    float scaX;
    float scaY;
    float scaZ;

    float rotX;
    float rotY;
    float rotZ;

    float posX;
    float posY;
    float posZ;

    unsigned int frame = 0;
    unsigned int veloc = 8;
    unsigned int accel = 1;
    unsigned int passo = 0;

    void renderizar();

    void frente(int aceleracao);

    void esquerda(int aceleracao);

    void direita(int aceleracao);

    void tras(int aceleracao);

    void pular();

    void home();

};
