#include "SOIL/SOIL.h"
#include "class/Modelo.cpp"
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "class/Mario.cpp"

void init(void);
void display(void);
void keyboard(unsigned char key, int x, int y);
void reshape(int w, int h);

GLfloat obsX, obsY, obsZ, obsX_ini, obsY_ini, obsZ_ini;
GLfloat rotX, rotY, rotX_ini, rotY_ini;
GLfloat angle;
GLfloat fAspect;
int x_ini, y_ini, bot;

//static GLint eixoy, eixox;
GLint largura, altura;
GLint xAux, yAux;
//static GLfloat spin = 0.0;

Mario mario = Mario();

//TODO variaveis de teste
GLfloat marioRotX = 0, marioRotY = 0, marioRotZ = 0;
GLfloat marioScaX = 0, marioScaY = 0, marioScaZ = 0;
GLfloat marioPosX = 0, marioPosY = 0, marioPosZ = 0;
unsigned int parte = 0;
unsigned int acao = 0;

void desenhaChao(void)
#define TAM 5
#define D 2
{
    // Flags para determinar a cor de cada quadrado
    bool flagx, flagz;
    // Define a normal apontando para cima
    glNormal3f(0, 1, 0);
    glBegin(GL_QUADS);
    flagx = false;
    // X varia de -TAM a TAM, de D em D
    for (float x = 0; x < TAM; x += D) {
        // Flagx determina a cor inicial
        if (flagx)
            flagz = false;
        else
            flagz = true;
        // Z varia de -TAM a TAM, de D em D
        for (float z = 0; z < TAM; z += D) {
            // Escolhe cor
            if (flagz)
                glColor3f(0.4, 0.4, 0.4);
            else
                glColor3f(1, 1, 1);
            // E desenha o quadrado
            glVertex3f(x, 0, z);
            glVertex3f(x + D, 0, z);
            glVertex3f(x + D, 0, z + D);
            glVertex3f(x, 0, z + D);
            // Alterna cor
            flagz = !flagz;
        }
        // A cada coluna, alterna cor inicial
        flagx = !flagx;
    }
    glEnd();
}

// Funo usada para especificar a posio do observador virtual
void PosicionaObservador(void)
{
    // Especifica sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);
    // Inicializa sistema de coordenadas do modelo
    glLoadIdentity();
    // Posiciona e orienta o observador
    glTranslatef(-obsX, -obsY, -obsZ);
    glRotatef(rotX, 1, 0, 0);
    glRotatef(rotY, 0, 1, 0);
}

void desenhaOrigem(void)
{
    glPushMatrix();
    // Desenhas as linhas das "bordas" do cubo
    glLineWidth(5.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINE); // frontal
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(100.0, 0.0, 0.0);
    glEnd();
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINE); // frontal
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 100.0, 0.0);
    glEnd();
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINE); // frontal
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 100.0);
    glEnd();

    glPopMatrix();
}

void EspecificaParametrosVisualizacao(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(angle, fAspect, 0.5, 500);
    glMatrixMode(GL_MODELVIEW);
    PosicionaObservador();
}

void init(void)
{
    // Define a cor de fundo da janela de visualizao como branca
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // Habilita a definio da cor do material a partir da cor corrente
    glEnable(GL_COLOR_MATERIAL);
    //Habilita o uso de iluminao
    glEnable(GL_LIGHTING);
    // Habilita as fontes de luz
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    // Habilita o depth-buffering
    glEnable(GL_DEPTH_TEST);

    // Inicializa a varivel que especifica o ngulo da projeo
    // perspectiva
    angle = 45;

    rotX = 30;
    rotY = 0;
    obsX = obsY = 0;
    obsZ = 20;


}

void reshape(int w, int h)
{
    // Para previnir uma diviso por zero
    if (h == 0)
        h = 1;

    altura = h;
    largura = w;
    // Especifica as dimenses da viewport
    glViewport(0, 0, w, h);

    // Calcula a correo de aspecto
    fAspect = (GLfloat)w / (GLfloat)h;

    EspecificaParametrosVisualizacao();
}


// Funo callback para eventos de botes do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN) {
        // Salva os parmetros atuais
        x_ini = x;
        y_ini = y;
        obsX_ini = obsX;
        obsY_ini = obsY;
        obsZ_ini = obsZ;
        rotX_ini = rotX;
        rotY_ini = rotY;
        bot = button;
    } else
        bot = -1;
}

// Funo callback para eventos de movimento do mouse
#define SENS_ROT 5.0
#define SENS_OBS 10.0
#define SENS_TRANSL 10.0
void GerenciaMovim(int x, int y)
{
    // Boto esquerdo ?
    if (bot == GLUT_LEFT_BUTTON) {
        // Calcula diferenas
        int deltax = x_ini - x;
        int deltay = y_ini - y;
        // E modifica ngulos
        rotY = rotY_ini - deltax / SENS_ROT;
        rotX = rotX_ini - deltay / SENS_ROT;
    }
    // Boto direito ?
    else if (bot == GLUT_RIGHT_BUTTON) {
        // Calcula diferena
        int deltaz = y_ini - y;
        // E modifica distncia do observador
        obsZ = obsZ_ini + deltaz / SENS_OBS;
    }
    // Boto do meio ?
    else if (bot == GLUT_MIDDLE_BUTTON) {
        // Calcula diferenas
        int deltax = x_ini - x;
        int deltay = y_ini - y;
        // E modifica posies
        obsX = obsX_ini + deltax / SENS_TRANSL;
        obsY = obsY_ini - deltay / SENS_TRANSL;
    }
    PosicionaObservador();
    //glutPostRedisplay();
}

void renderizarModelos()
{
    glPushMatrix();
    mario.obj.renderizar();

    glPopMatrix();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // bottom right: rotating perspective view
    glViewport(0, 0, largura, altura);

    glPushMatrix();

    renderizarModelos();

    glPopMatrix();

    //desenhaOrigem();

    desenhaChao();

    EspecificaParametrosVisualizacao();

    glutSwapBuffers();
}

// Funo callback para tratar eventos de teclas especiais
void TeclasEspeciais(int tecla, int x, int y)
{
    switch (tecla) {
    case GLUT_KEY_LEFT:
        mario.obj.posX += 0.1;
        break;
    case GLUT_KEY_RIGHT:
        mario.obj.posX -= 0.1;
        break;
    case GLUT_KEY_UP:
        mario.obj.posZ += 0.1;
        break;
    case GLUT_KEY_DOWN:
        mario.obj.posZ -= 0.1;
        break;
    case GLUT_KEY_PAGE_UP:
        mario.obj.posY -= 2;
        break;
    case GLUT_KEY_PAGE_DOWN:
        mario.obj.posY += 2;
        break;
    case GLUT_KEY_HOME:
        if (angle >= 10)
            angle -= 5;
        break;
    case GLUT_KEY_END:
        if (angle <= 150)
            angle += 5;
        break;
    }
    PosicionaObservador();
    //glutPostRedisplay();
}

unsigned int frame = 0;
unsigned int veloc = 8;
unsigned int passo = 0;

void animate(int value) {

    if (passo < veloc) {
        passo += 1;
    } else {
        if (frame < mario.obj.animations[0].frames.size() - 1) {
            frame += 1;
        } else {
            frame = 0;
        }
        passo = 0;
    }

    for ( unsigned int passo = 0; passo < veloc; passo++ ) {
        mario.obj.animar(0, frame, passo, veloc);
    }
}

// Funo callback chamada para gerenciar eventos de teclas normais (ESC)
void Teclado(unsigned char tecla, int x, int y)
{
    if (tecla == 27) // ESC ?
        exit(0);
    if (tecla >= '0' && tecla <= '2') {
       for (unsigned int i = 0; i < mario.obj.animations[0].frames.size(); i++) {
            glutTimerFunc(i*50, animate, 1);
       }
    }
    if (tecla == 'a') {
        acao++;
        if (acao == 2)
            acao = 0;
        if (acao == 0)
            std::cout << "parte = Rotacao" << '\n';
        if (acao == 1)
            std::cout << "parte = Posicao" << '\n';
        if (acao == 2)
            std::cout << "parte = Escala" << '\n';
    }
    if (tecla == 'x') {
        if (acao == 0)
            mario.obj.filhos[parte].rotX = ++marioRotX;
        if (acao == 1)
            mario.obj.filhos[parte].posX = ++marioPosX/10;
        if (acao == 2)
            mario.obj.filhos[parte].scaX = ++marioScaX;
    }
    if (tecla == 'X') {
        if (acao == 0)
            mario.obj.filhos[parte].rotX = --marioRotX;
        if (acao == 1)
            mario.obj.filhos[parte].posX = --marioPosX/10;
        if (acao == 2)
            mario.obj.filhos[parte].scaX = --marioScaX;
    }
    if (tecla == 'y') {
        if (acao == 0)
            mario.obj.filhos[parte].rotY = ++marioRotY;
        if (acao == 1)
            mario.obj.filhos[parte].posY = ++marioPosY/10;
        if (acao == 2)
            mario.obj.filhos[parte].scaY = ++marioScaY;
    }
    if (tecla == 'Y') {
        if (acao == 0)
            mario.obj.filhos[parte].rotY = --marioRotY;
        if (acao == 1)
            mario.obj.filhos[parte].posY = --marioPosY/10;
        if (acao == 2)
            mario.obj.filhos[parte].scaY = --marioScaY;
    }
    if (tecla == 'z') {
        if (acao == 0)
            mario.obj.filhos[parte].rotZ = ++marioRotZ;
        if (acao == 1)
            mario.obj.filhos[parte].posZ = ++marioPosZ/10;
        if (acao == 2)
            mario.obj.filhos[parte].scaZ = ++marioScaZ;
    }
    if (tecla == 'Z') {
        if (acao == 0)
            mario.obj.filhos[parte].rotZ = --marioRotZ;
        if (acao == 1)
            mario.obj.filhos[parte].posZ = --marioPosZ/10;
        if (acao == 2)
            mario.obj.filhos[parte].scaZ = --marioScaZ;
    }

    if (tecla == 's') {
        std::cout << mario.obj.filhos[parte].nome << " = "
            << "\n" << mario.obj.filhos[parte].posX
            << ", " << mario.obj.filhos[parte].posY
            << ", " << mario.obj.filhos[parte].posZ
            << ", " << mario.obj.filhos[parte].rotX%360
            << ", " << mario.obj.filhos[parte].rotY%360
            << ", " << mario.obj.filhos[parte].rotZ%360
            << ", " << mario.obj.filhos[parte].scaX
            << ", " << mario.obj.filhos[parte].scaY
            << ", " << mario.obj.filhos[parte].scaZ
            << '\n';
        tecla = 0;
    }
}

void timer(int value) {
    // em teoria limita
    glutPostRedisplay();
    glutTimerFunc(16, timer, 1);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(900, 5);
    glutCreateWindow("Mario");

    glutTimerFunc(300, timer, 1);

    glutDisplayFunc(display);

    // Registra a funo callback para tratamento das teclas normais
    glutKeyboardFunc(Teclado);

    // Registra a funo callback para tratamento das teclas especiais
    glutSpecialFunc(TeclasEspeciais);    // Registra a funo callback para eventos de botes do mouse

    glutMouseFunc(GerenciaMouse);

    // Registra a funo callback para eventos de movimento do mouse
    glutMotionFunc(GerenciaMovim);
    // glutIdleFunc(spinDisplay);

    if (!mario.obj.LoadGLTextures()) {
        return 1; // If Texture Didn't Load Return FALSE
    }
    glutReshapeFunc(reshape);

    init();

    glutMainLoop();

    return 0;
}
