#include <vector>
#include <GL/gl.h>
#include <GL/glut.h>
#include "Membro.h"
#include "Vertice.h"

class Modelo {
public:
    Modelo() {
        largura = 0;
        altura  = 0;
        angulo  = 0;
    }
    Modelo(std::string folder, std::string model) {
        largura = 0;
        altura  = 0;
        angulo  = 0;
        this->importarModelo(folder, model);
    }

    std::vector<Vertice> v; // vertices
    std::vector<Vertice> vn; // vertices normal
    std::vector<Vertice> vt; // vertices textura

    std::vector<Membro> membros;

    void importarModelo(std::string folder, std::string model);

    float largura;
    float altura;
    float angulo;
};
