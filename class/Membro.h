#include "Face.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include <string>

class Membro {
public:
    Membro()
    {
        colR = 0;
        colG = 0;
        colB = 0;

        angX = 0;
        angY = 0;
        angZ = 0;

        posX = 0;
        posY = 0;
        posZ = 0;

        textura_nome = "";
        nome = "";
        useMaterial = "";
    }

    void desenha();
    std::vector<Face> faces;

    float colR;
    float colG;
    float colB;

    float angX;
    float angY;
    float angZ;

    float posX;
    float posY;
    float posZ;

    std::string textura_nome; // nome da textura

    GLuint textura; // as texturas pra valer

    std::string getNome() { return nome; };
    void setNome(std::string nome) { nome = this->nome; };

    float getColorR() { return colR; };
    float getColorG() { return colG; };
    float getColorB() { return colB; };

    void setColorR(float colR) { this->colR = colR; };
    void setColorG(float colG) { this->colG = colG; };
    void setColorB(float colB) { this->colB = colB; };

    std::string nome;
    std::string useMaterial;
};

void Membro::desenha(){
    //glPushMatrix(); // salva o contexto(1)

    //glPopMatrix(); // restaura o contexto(1)
};
