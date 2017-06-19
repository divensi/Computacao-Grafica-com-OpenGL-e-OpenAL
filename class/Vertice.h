#include <vector>

class Vertice {
public:
    Vertice()
    {
        x = 0;
        y = 0;
        z = 0;
    };

    Vertice(float x, float y, float z)
    {
        x = this->x;
        y = this->y;
        z = this->z;
    }

    float x;
    float y;
    float z;
};
