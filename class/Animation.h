#include "Frame.h"

class Animation {
public:
    Animation()
    {
    };

    Animation(std::string nome)
    {
        this->nome = nome;
    }

    std::string nome;
    std::vector<Frame> frames;
};
