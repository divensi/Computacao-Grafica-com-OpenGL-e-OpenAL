#include "Membro.h"
#include "Vertice.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include <vector>

class Modelo {
public:
    Modelo()
    {
        largura = 0;
        altura = 0;
        angulo = 0;
    }
    Modelo(std::string model, std::string ds)
    {
        largura = 0;
        altura = 0;
        angulo = 0;
        this->importarModelo(model, ds);
    }

    std::vector<Vertice> v; // vertices
    std::vector<Vertice> vn; // vertices normal
    std::vector<Vertice> vt; // vertices textura

    std::vector<Membro> membros;

    void importarModelo(std::string model, std::string ds);

    float largura;
    float altura;
    float angulo;
};
