class Ponto {
public:
    Ponto() {
        idVert = 0;
        idNorm = 0;
        idText = 0;
    };

    Ponto(int idVert, int idNorm, int idText) {
        idVert = this->idVert;
        idNorm = this->idNorm;
        idText = this->idText;
    }

    int idVert;
    int idNorm;
    int idText;
};
