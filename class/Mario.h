#include <GL/gl.h>
#include <GL/glut.h>
#include <vector>

class Mario {
public:
    Mario()
    {
        angX = 0; // angulos
        angY = 0;
        angZ = 0;

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

    void importarHierarquia();

    float scaX;
    float scaY;
    float scaZ;

    float angX;
    float angY;
    float angZ;

    float posX;
    float posY;
    float posZ;

    unsigned int frame = 0;
    unsigned int veloc = 8;
    unsigned int accel = 1;
    unsigned int passo = 0;

    void frente(int aceleracao);

    void esquerda(int aceleracao);

    void direita(int aceleracao);

    void tras(int aceleracao);

    void pular();

    void home();

};
