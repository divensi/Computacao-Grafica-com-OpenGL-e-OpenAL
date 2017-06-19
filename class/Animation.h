#include "Frame.h"

class Animation {
public:
    Animation()
    {
        executando = false;
    };

    Animation(std::string nome)
    {
        this->nome = nome;
        executando = false;
    }

    bool executando;
    std::string nome;
    std::vector<Frame> frames;
};
