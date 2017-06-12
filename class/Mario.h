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

        this->importarHierarquia();
    }

    Modelo obj;

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

};
