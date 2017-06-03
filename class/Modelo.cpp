#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "Modelo.h"

void Modelo::importarModelo(std::string folder, std::string model) {

    // Modelo
    std::stringstream obj;
    obj << folder << "/" << model << ".obj";
//    std::cout << << obj.str().c_str() << "\n";
    //const char* file     = obj.str().c_str();
    //std::cout << file << "\n";

    //const char* obj.str().c_str() = "model/Mario64.obj";

    // Materiais
    std::stringstream mtl;
    mtl << folder << "/" << model << ".mtl";
    //    const char* material = mtl.str().c_str();
    //const char* material = "model/Mario64.mtl";



    this->membros.clear();

    Vertice vert    = Vertice();  // vertice
    Vertice norm    = Vertice(); // vertice normal
    Vertice text    = Vertice(); // vertice textura

    Ponto ponto     = Ponto(); //face
    Face face       = Face(); //face
    Membro membro   = Membro(); // vetor de pontos

    std::cout << "---------------------------------------\n";
    std::cout << "Carregando novo modelo:" << obj.str().c_str() << "\n\n";

    std::ifstream infile(obj.str().c_str()); // le do primeiro argumento

    std::string line;

    while (std::getline(infile, line)) {
        std::istringstream iss(line);

        std::string a;

        if (!(iss >> a)) {
            //std::cout << "Erro \n";
            //break;
        } // error
        if (a == "o") {
            if ( membro.faces.size() > 0 ) {
                // empurra membro pro modelo se existirem
                this->membros.push_back(membro);
            }
            // limpa membro
            membro.faces.clear();

            if (!(iss >> membro.nome)) { break; } // error


            std::cout << "Carregando novo membro:" << membro.nome << "\n";


        }
        if (a == "v") {
            //pega os proximos valores separados por espaço e empurra para a aux
            if (!(iss >> vert.x >> vert.y >> vert.z )) { break; } // error

            this->v.push_back(vert);
            //coloca aux no vetor
            //std::cout << "novo vertice\n";
        }
        if (a == "vn") {
            //pega os proximos valores separados por espaço e empurra para a aux
            if (!(iss >> norm.x >> norm.y >> norm.z )) { break; } // error
            //coloca aux no vetor
            this->vn.push_back(norm);

            //std::cout << "novo vertice normal\n";
        }
        if (a == "vt") {
            //pega os proximos valores separados por espaço e empurra para a aux
            if (!(iss >> text.x >> text.y )) { break; } // error
            // evita cagadas
            text.z = 0;
            //coloca aux no vetor
            this->vt.push_back(text);

            //std::cout << "novo vertice textura\n";
        }
        if (a == "usemtl") {
            if (!(iss >> membro.useMaterial )) { break; } // error
        }
        if (a == "f") {
            std::string value, facestring;

            //std::cout << line << "\n"; printa a linha da face

            //separa os pontos
            while (iss >> facestring) {
                // printa um ponto separado
                //std::cout << facestring << "\n";

                // cria stream de uma string
                std::istringstream ss(facestring);

                std::getline(ss, value, '/');
                //cria um stream de inteiro a partir da string pra jogar no ponto
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
                //std::cout << ponto.idVert << " " << ponto.idText << " " << ponto.idNorm << " " << '\n';
            }
            membro.faces.push_back(face);
            // limpa a face
            face.pontos.clear();
        }

    }

    std::cout << "EOF modelo\n";
    //carrega o último membro no modelo
    this->membros.push_back(membro);


    std::cout << "---------------------------------------\n";
    std::cout << "Carregando novo material:" << mtl.str().c_str() << "\n\n";

    std::ifstream inmaterial(mtl.str().c_str()); // le do primeiro argumento

    while (std::getline(inmaterial, line)) {
        std::istringstream iss(line);

        std::string a;

        if (!(iss >> a)) {
            //std::cout << "Erro \n";
            //break;
        } // error
        if (a == "newmtl") {

            if ( membro.useMaterial != "" ) {
                // empurra membro pro modelo se existirem
                for ( int i = 0; i <= this->membros.size(); i++ ) {
                    if ( this->membros[i].useMaterial == membro.useMaterial ) {

                        this->membros[i].setColorR(membro.colR);
                        this->membros[i].setColorG(membro.colG);
                        this->membros[i].setColorB(membro.colB);

                        this->membros[i].textura_nome = membro.textura_nome;
                    }
                }
            }
            // reinizializa membro
            membro = Membro();

            if (!(iss >> membro.useMaterial)) { break; } // error


            std::cout << "Carregando novo material:" << membro.useMaterial << "\n";

        }
        if (a == "Kd") { // cores
            if (!(iss >> membro.colR >> membro.colG >> membro.colB )) { break; } // error
        }
        if (a == "map_Kd") { // textura
            if (!(iss >> membro.textura_nome )) { break; } // error
        }
    }

    //empurra o último
    if ( membro.useMaterial != "" ) {
        // empurra membro pro modelo se existirem
        for ( int i = 0; i < this->membros.size(); i++ ) {
            if ( this->membros[i].useMaterial == membro.useMaterial ) {

                this->membros[i].colR = membro.colR;
                this->membros[i].colG = membro.colG;
                this->membros[i].colB = membro.colB;

                this->membros[i].textura_nome = membro.textura_nome;
            }
        }
    }

    std::cout << "EOF material\n";
}
