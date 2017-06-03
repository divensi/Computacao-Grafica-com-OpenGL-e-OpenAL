#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include "SOIL/SOIL.h"
#include "class/Modelo.cpp"

void init(void);
void display(void);
void keyboard(unsigned char key, int x, int y);
void reshape (int w, int h);

GLfloat cameraX = 0;
GLfloat cameraY = 0;
GLfloat cameraZ = 0;
GLfloat angle, fAspect;

static int eixoy, eixox;
int largura, altura;
int xAux, yAux;

//modelo do mario
// std::string folder  = "model";
// std::string model   = "Mario64";
std::string ds      = "/"; // separador de diretorio


std::string folder = "Buzz";
std::string model = "buzz";

Modelo rotBox = Modelo(folder, model); // mario

// Load Bitmaps And Convert To Textures
int LoadGLTextures() {
    for ( int i = 0; i < rotBox.membros.size(); i++ ) {
        if (rotBox.membros[i].textura_nome != "" ){
            std::stringstream texture_file;
            texture_file << folder << ds << rotBox.membros[i].textura_nome;
            //std::cout << texture_file.str() << "\n";
            /* load an image file directly as a new OpenGL texture */
            rotBox.membros[i].textura = SOIL_load_OGL_texture( texture_file.str().c_str(),
                SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_DDS_LOAD_DIRECT | SOIL_FLAG_TEXTURE_REPEATS);

            if (rotBox.membros[i].textura == 0 ) {
                std::cout << "ERRO: falha ao ler textura " << texture_file.str() << "\n";
            }
        }
        // Typical Texture Generation Using Data From The Bitmap
        glBindTexture(GL_TEXTURE_2D, rotBox.membros[i].textura);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        //
        // glEnable(GL_TEXTURE_2D);			    // Enable Texture Mapping ( NEW )
        // glShadeModel(GL_SMOOTH);			    // Enable Smooth Shading
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Black Background
        glClearDepth(1.0f);						// Depth Buffer Setup
        glEnable(GL_DEPTH_TEST);				// Enables Depth Testing
        // glDepthFunc(GL_LEQUAL);					// The Type Of Depth Testing To Do
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
    }


    return true; // Return Success
}

void init(void) {
    // Define a cor de fundo da janela de visualiza��o como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Inicializa a vari�vel que especifica o �ngulo da proje��o
	// perspectiva
	angle = 45;

	// Inicializa as vari�veis utilizadas para implementa��o
	// da opera��o de pan
	cameraX = 0.0f;
	cameraY = 0.0f;
	cameraZ = 0.0f;

}

void EspecificaParametrosVisualizacao(void) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angle, fAspect, 0.5, 500);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0+cameraX,0+cameraY,10+cameraZ,
		      0,0,0, 0,1,0);
}

void reshape (int w, int h) {
    // Para previnir uma divis�o por zero
	if ( h == 0 ) h = 1;

	// Especifica as dimens�es da viewport
	glViewport(0, 0, w, h);

	// Calcula a corre��o de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao();
}


// Funeeo callback para eventos de botees do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN) {  // zoom in
			if (angle >= 10) angle -= 5;
		}
	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN) {  // zoom out
			if (angle <= 130) angle += 5;
		}
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

void display(void) {
    glPushMatrix();
    glLoadIdentity();

    glRotatef ((GLfloat) eixoy, 0.0, 1.0, 0.0);
    glRotatef ((GLfloat) eixox, 1.0, 0.0, 0.0);

    EspecificaParametrosVisualizacao();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    //percorre membros
    for ( int i = 0 ; i < rotBox.membros.size(); i++) {

        if ( rotBox.membros[i].textura_nome != "" ) {
            glColor3f(1.0, 1.0, 1.0);

            std::cout << rotBox.membros[i].textura_nome << "/" << rotBox.membros[i].useMaterial << "\n";
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, rotBox.membros[i].textura);
        } else {
            float r = rotBox.membros[i].colR;
            float g = rotBox.membros[i].colG;
            float b = rotBox.membros[i].colB;

            //std::cout << "\n nome:" << rotBox.membros[i].nome << " textura:" << rotBox.membros[i].useMaterial <<  " R:" << r << " G:" << g << " B:" << b << '\n';

            glColor3f(r, g, b);
        }
        //percorre faces
        for (int j = 0; j < rotBox.membros[i].faces.size(); j++) {
            glBegin(GL_POLYGON);

            //percorre pontos
            for (int k = 0; k < rotBox.membros[i].faces[j].pontos.size(); k++) {
                // id - 1 pois o objeto comeca em 1
                float xv = rotBox.v[rotBox.membros[i].faces[j].pontos[k].idVert - 1].x;
                float yv = rotBox.v[rotBox.membros[i].faces[j].pontos[k].idVert - 1].y;
                float zv = rotBox.v[rotBox.membros[i].faces[j].pontos[k].idVert - 1].z;

                float xt = rotBox.vt[rotBox.membros[i].faces[j].pontos[k].idVert - 1].x;
                float yt = rotBox.vt[rotBox.membros[i].faces[j].pontos[k].idVert - 1].y;

                glTexCoord2f(xt, yt);
                glVertex3f(xv, yv, zv);
            }

            glEnd();
        }
        if ( rotBox.membros[i].textura_nome != "" ) {
            glDisable(GL_TEXTURE_2D);
            glColor3f(1.0, 1.0, 1.0);

        }

    //    glPopMatrix();
    }
    glPopMatrix();
    glutSwapBuffers();
}

void TeclasEspeciais(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP:		// desloca o volume de visualiza��o para cima
								cameraY -= 0.1;
								break;
		case GLUT_KEY_DOWN:		// desloca o volume de visualiza��o para baixo
								cameraY += 0.1;
								break;
		case GLUT_KEY_LEFT:		// desloca o volume de visualiza��o para o lado esquerdo
								cameraX += 0.1;
								break;
		case GLUT_KEY_RIGHT:	// desloca o volume de visualiza��o para o lado direito
								cameraX -= 0.1;
								break;
		case GLUT_KEY_PAGE_UP:	// desloca o volume de visualiza��o para frente
								cameraZ -= 0.1;
								break;
		case GLUT_KEY_PAGE_DOWN:// desloca o volume de visualiza��o para tr�s
								cameraZ += 0.1;
		break;
	}
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}


void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            exit(0);
            break;
        case 'a':
            printf("%d, %d\n", x, y);
            break;
        case 'y':
            eixoy = (eixoy + 5) % 360;
            glutPostRedisplay();
            break;
        case 'Y':
            eixoy = (eixoy - 5) % 360;
            glutPostRedisplay();
            break;
        case 'x':
            eixox = (eixox + 5) % 360;
            glutPostRedisplay();
            break;
        case 'X':
            eixox = (eixox - 5) % 360;
            glutPostRedisplay();
            break;
        case 'p':
            glLoadIdentity();
            gluPerspective(65.0, (GLfloat) largura/(GLfloat) altura, 20.0, 120.0);
            gluLookAt(0, 0, -30, 0, 0, 0, 0, 1, 0);
            glutPostRedisplay();
            break;
        case 'o':
            glLoadIdentity();
            glOrtho (-5, 5, -5, 5, -5 , 5);
            glutPostRedisplay();
            break;
    }
}

int main(int argc, char** argv) {


    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowSize (300, 300);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(TeclasEspeciais);
    glutMouseFunc(GerenciaMouse);

    if (!LoadGLTextures()){
		return 1; // If Texture Didn't Load Return FALSE
	}

    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}