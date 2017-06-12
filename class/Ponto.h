class Ponto {
public:
    Ponto()
    {
        idVert = 0;
        idNorm = 0;
        idText = 0;
    };

    Ponto(int idVert, int idNorm, int idText)
    {
        this->idVert = idVert;
        this->idNorm = idNorm;
        this->idText = idText;
    }

    int idVert;
    int idNorm;
    int idText;
};
