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

    Frame(GLint rotX, GLint rotY, GLint rotZ,
          GLfloat posX, GLfloat posY, GLfloat posZ,
          GLfloat scaX, GLfloat scaY, GLfloat scaZ)
    {
        this->rotX = rotX;
        this->rotY = rotY;
        this->rotZ = rotZ;

        this->posX = posX;
        this->posY = posY;
        this->posZ = posZ;

        this->scaX = scaX;
        this->scaY = scaY;
        this->scaZ = scaZ;
    }

    Frame(GLint rotX, GLint rotY, GLint rotZ,
          GLfloat posX, GLfloat posY, GLfloat posZ)
    {
        this->rotX = rotX;
        this->rotY = rotY;
        this->rotZ = rotZ;

        this->posX = posX;
        this->posY = posY;
        this->posZ = posZ;

        this->scaX = 1;
        this->scaY = 1;
        this->scaZ = 1;
    }

    Frame(GLint rotX, GLint rotY, GLint rotZ)
    {
        this->rotX = rotX;
        this->rotY = rotY;
        this->rotZ = rotZ;

        this->posX = 0;
        this->posY = 0;
        this->posZ = 0;

        this->scaX = 1;
        this->scaY = 1;
        this->scaZ = 1;
    }

    GLint rotX, rotY, rotZ;
    GLfloat posX, posY, posZ;
    GLfloat scaX, scaY, scaZ;
};
