class Frame {
public:
    Frame()
    {
        posX = 0;
        posY = 0;
        posZ = 0;

        rotX = 0;
        rotY = 0;
        rotZ = 0;

        scaX = 1;
        scaY = 1;
        scaZ = 1;
    };

    Frame(GLfloat posX, GLfloat posY, GLfloat posZ,
          GLfloat rotX, GLfloat rotY, GLfloat rotZ,
          GLfloat scaX, GLfloat scaY, GLfloat scaZ)
    {
        this->posX = posX;
        this->posY = posY;
        this->posZ = posZ;

        this->rotX = rotX;
        this->rotY = rotY;
        this->rotZ = rotZ;

        this->scaX = scaX;
        this->scaY = scaY;
        this->scaZ = scaZ;
    }

    GLfloat posX, posY, posZ;
    GLfloat rotX, rotY, rotZ;
    GLfloat scaX, scaY, scaZ;
};
