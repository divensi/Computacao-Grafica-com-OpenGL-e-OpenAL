#include "Modelo.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
std::string ds =
    #ifdef _WIN32
        "\\";
    #else
        "/";
    #endif

void Modelo::importarModelo(std::string folder, std::string model)
{
    this->nome = model;
    // Modelo
    std::stringstream obj;
    obj << folder << ds << model << ".obj";

    // Materiais
    std::stringstream mtl;
    mtl << folder << ds << model << ".mtl";

    this->membros.clear();

    Vertice vert = Vertice(); // vertice
    Vertice norm = Vertice(); // vertice normal
    Vertice text = Vertice(); // vertice textura

    Ponto ponto = Ponto(); // face
    Face face = Face(); // face
    Membro membro = Membro(); // vetor de pontos

    std::cout << "---------------------------------------\n";
    std::cout << "Carregando novo modelo:" << obj.str().c_str() << "\n\n";

    std::ifstream infile(obj.str().c_str()); // le do primeiro argumento

    std::string line;

    while (std::getline(infile, line)) {
        std::istringstream iss(line);

        std::string a;

        if (!(iss >> a)) {
            // std::cout << "Erro \n";
            // break;
        } // error
        if (a == "o") {
            if (membro.faces.size() > 0) {
                // empurra membro pro modelo se existirem
                this->membros.push_back(membro);
            }
            // limpa membro
            membro.faces.clear();

            if (!(iss >> membro.nome))
                break; // error

            std::cout << "Carregando novo membro:" << membro.nome << "\n";
        }
        if (a == "v") {
            // pega os proximos valores separados por espaço e empurra para a aux
            if (!(iss >> vert.x >> vert.y >> vert.z))
                break; // error

            // coloca vert no vetor
            this->v.push_back(vert);
            // std::cout << "novo vertice\n";
        }
        if (a == "vn") {
            // pega os proximos valores separados por espaço e empurra para a aux
            if (!(iss >> norm.x >> norm.y >> norm.z))
                break; // error

            // coloca norm no vetor
            this->vn.push_back(norm);
        }
        if (a == "vt") {
            // pega os proximos valores separados por espaço e empurra para a aux
            if (!(iss >> text.x >> text.y))
                break; // error
            // evita cagadas
            text.z = 0;
            // coloca text no vetor
            this->vt.push_back(text);

            // std::cout << "novo vertice textura\n";
        }
        if (a == "usemtl") {
            if (!(iss >> membro.useMaterial))
                break; // error
        }
        if (a == "f") {
            std::string value, facestring;

            // separa os pontos
            while (iss >> facestring) {
                // cria stream de uma string
                std::istringstream ss(facestring);

                std::getline(ss, value, '/');
                // cria um stream de inteiro a partir da string pra jogar no ponto
                std::istringstream intV(value);
                intV >> ponto.idVert;

                std::getline(ss, value, '/');
                std::istringstream intVt(value);
                intVt >> ponto.idText;

                std::getline(ss, value, '/');
                std::istringstream intVn(value);
                intVn >> ponto.idNorm;

                face.pontos.push_back(ponto);

                // printa itens individuais
                // std::cout << ponto.idVert << " " << ponto.idText << " " <<
                // ponto.idNorm << " " << '\n';
            }
            membro.faces.push_back(face);
            // limpa a face
            face.pontos.clear();
        }
    }

    std::cout << "EOF modelo\n";
    // carrega o último membro no modelo
    this->membros.push_back(membro);

    std::cout << "---------------------------------------\n";
    std::cout << "Carregando novo material:" << mtl.str().c_str() << "\n\n";

    std::ifstream inmaterial(mtl.str().c_str()); // le do primeiro argumento

    while (std::getline(inmaterial, line)) {
        std::istringstream iss(line);

        std::string a;

        if (!(iss >> a)) {
            std::cout << "Erro \n";
            // break;
        } // error
        if (a == "newmtl") {
            if (membro.useMaterial != "") {
                // empurra membro pro modelo se existirem
                for (unsigned int i = 0; i < this->membros.size(); i++) {
                    if (this->membros[i].useMaterial == membro.useMaterial) {
                        this->membros[i].setColorR(membro.colR);
                        this->membros[i].setColorG(membro.colG);
                        this->membros[i].setColorB(membro.colB);

                        this->membros[i].textura_nome = membro.textura_nome;
                    }
                }
            }
            // reinizializa membro
            membro = Membro();

            if (!(iss >> membro.useMaterial)) {
                break;
            } // error

            std::cout << "Carregando novo material:" << membro.useMaterial << "\n";
        }
        if (a == "Kd") { // cores
            if (!(iss >> membro.colR >> membro.colG >> membro.colB)) {
                break;
            } // error
        }
        if (a == "map_Kd") { // textura
            if (!(iss >> membro.textura_nome)) {
                break;
            } // error
        }
    }

    // empurra o último
    if (membro.useMaterial != "") {
        // empurra membro pro modelo se existirem
        for (unsigned int i = 0; i < this->membros.size(); i++) {
            if (this->membros[i].useMaterial == membro.useMaterial) {
                this->membros[i].colR = membro.colR;
                this->membros[i].colG = membro.colG;
                this->membros[i].colB = membro.colB;

                this->membros[i].textura_nome = membro.textura_nome;
            }
        }
    }

    std::cout << "EOF material\n";
}

void Modelo::renderizar() {

        glTranslatef(this->posX, this->posY, this->posZ); // vai para o meio do osso
        glRotatef(this->rotX, 1, 0, 0); // vai para o meio do osso
        glRotatef(this->rotY, 0, 1, 0); // vai para o meio do osso
        glRotatef(this->rotZ, 0, 0, 1); // vai para o meio do osso

        for (unsigned int i = 0; i < this->membros.size(); i++) {

            if (this->membros[i].textura_nome != "") {
                glColor3f(1.0, 1.0, 1.0);

                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, this->membros[i].textura);
            } else {
                float r = this->membros[i].colR;
                float g = this->membros[i].colG;
                float b = this->membros[i].colB;

                glColor3f(r, g, b);
            }
            // percorre faces
            for (unsigned int j = 0; j < this->membros[i].faces.size(); j++) {
                glBegin(GL_POLYGON);

                // percorre pontos
                for (unsigned int k = 0; k < this->membros[i].faces[j].pontos.size(); k++) {
                    // id - 1 pois o objeto comeca em 1
                    float xv = this->v[this->membros[i].faces[j].pontos[k].idVert - 1].x;
                    float yv = this->v[this->membros[i].faces[j].pontos[k].idVert - 1].y;
                    float zv = this->v[this->membros[i].faces[j].pontos[k].idVert - 1].z;

                    float xn = this->vn[this->membros[i].faces[j].pontos[k].idNorm - 1].x;
                    float yn = this->vn[this->membros[i].faces[j].pontos[k].idNorm - 1].y;
                    float zn = this->vn[this->membros[i].faces[j].pontos[k].idNorm - 1].z;

                    float xt = this->vt[this->membros[i].faces[j].pontos[k].idText - 1].x;
                    float yt = this->vt[this->membros[i].faces[j].pontos[k].idText - 1].y;

                    glTexCoord2f(xt, yt);
                    glNormal3f(xn, yn, zn);
                    glVertex3f(xv, yv, zv);
                }
                glEnd();
            }
            if (this->membros[i].textura_nome != "") {
                glDisable(GL_TEXTURE_2D);
                glColor3f(1.0, 1.0, 1.0);
            }
        }

        for (unsigned int i = 0; i < this->filhos.size(); i++ ) {
            glPushMatrix();
            this->filhos[i].renderizar();
            glPopMatrix();
        }

}

// Load Bitmaps And Convert To Textures
int Modelo::LoadGLTextures()
{
    for (unsigned int i = 0; i < this->membros.size(); i++) {
        if (this->membros[i].textura_nome != "") {
            std::stringstream texture_file;
            texture_file << this->folder << ds << this->membros[i].textura_nome;
            // std::cout << texture_file.str() << "\n";
            /* load an image file directly as a new OpenGL texture */
            this->membros[i].textura = SOIL_load_OGL_texture(
                texture_file.str().c_str(), SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID,
                SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y); //SOIL_FLAG_TEXTURE_REPEATS

            if (this->membros[i].textura == 0) {
                std::cout << "ERRO: falha ao ler textura " << texture_file.str()
                          << "\n";
            }
        }
        // Typical Texture Generation Using Data From The Bitmap
        glBindTexture(GL_TEXTURE_2D, this->membros[i].textura);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //
        // glEnable(GL_TEXTURE_2D);			    // Enable Texture Mapping (
        // NEW ) glShadeModel(GL_SMOOTH);			    // Enable Smooth
        // Shading
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black Background
        glClearDepth(1.0f); // Depth Buffer Setup
        glEnable(GL_DEPTH_TEST); // Enables Depth Testing
        // glDepthFunc(GL_LEQUAL);	// The Type Of
        // Depth Testing To Do
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Really Nice Perspective Calculations
    }

    for (unsigned int i = 0; i < this->filhos.size(); i++ ) {
        this->filhos[i].LoadGLTextures();
    }

    return true; // Return Success
}

void Modelo::animar(int animation, int frame, int veloc) {

    //std::cout << "animation " << this->animations[animation].frames.size() <<  ":" << frame << '\n';

    this->posX  = this->posX + (this->animations[animation].frames[frame].posX/veloc); // angulos
    this->posY  = this->posY + (this->animations[animation].frames[frame].posY/veloc);
    this->posZ  = this->posZ + (this->animations[animation].frames[frame].posZ/veloc);

    this->rotX  = this->rotX + (this->animations[animation].frames[frame].rotX/veloc); // angulos
    this->rotY  = this->rotY + (this->animations[animation].frames[frame].rotY/veloc);
    this->rotZ  = this->rotZ + (this->animations[animation].frames[frame].rotZ/veloc);

    alListener3f( AL_POSITION, this->posX*10,this->posZ*10, this->posY*10);
    alListener3f( AL_VELOCITY, 1, 1, 1);

    //std::cout << "(" << this->posX << ", " << this->posY << ", " << this->posZ << ") - (" << this->rotX << ", " << this->rotY << ", " << this->rotZ <<")\n";

    for (unsigned int i = 0; i < this->filhos.size(); i++ ) {
        this->filhos[i].animar(animation, frame, veloc);
    }
}

void Modelo::home() {
    this->rotX = this->rotX_ini;
    this->rotY = this->rotY_ini;
    this->rotZ = this->rotZ_ini;

    this->posX = this->posX_ini;
    this->posY = this->posY_ini;
    this->posZ = this->posZ_ini;

    for (unsigned int i = 0; i < this->filhos.size(); i++ ) {
        this->filhos[i].home();
    }
}
