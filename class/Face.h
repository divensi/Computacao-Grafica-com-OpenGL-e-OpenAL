#include "Ponto.h"
#include <vector>

class Face {
public:
    Face(std::vector<Ponto> pontos)
    {
        pontos = this->pontos;
    }
    Face() {}

    std::vector<Ponto> pontos;
};
