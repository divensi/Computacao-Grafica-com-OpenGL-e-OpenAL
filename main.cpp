#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <thread>
#include <functional>
#include <unistd.h>
#include <math.h>

//OPENGL
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

//OPENAL
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

#include "SOIL/SOIL.h"
#include "class/Modelo.cpp"
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
GLint ultimaTecla, aceleracao;
GLint largura, altura;
GLint xAux, yAux;

GLboolean flagW = false, flagA = false, flagS = false,
          flagD = false, flagSpace = false, flagJumpin = false;

//static GLfloat spin = 0.0;

Mario mario = Mario();

//TODO variaveis de teste
GLfloat marioRotX = 0, marioRotY = 0, marioRotZ = 0;
GLfloat marioScaX = 0, marioScaY = 0, marioScaZ = 0;
GLfloat marioPosX = 0, marioPosY = 0, marioPosZ = 0;
unsigned int parte = 0;
unsigned int acao = 0;

void desenhaChao(void)
#define TAM 1000
#define D 3
{
    // Flags para determinar a cor de cada quadrado
    bool flagx, flagz;
    // Define a normal apontando para cima
    glNormal3f(0, 1, 0);
    glBegin(GL_QUADS);
    flagx = false;
    // X varia de -TAM a TAM, de D em D
    for (float x = -TAM; x < TAM; x += D) {
        // Flagx determina a cor inicial
        if (flagx)
            flagz = false;
        else
            flagz = true;
        // Z varia de -TAM a TAM, de D em D
        for (float z = -TAM; z < TAM; z += D) {
            // Escolhe cor
            if (flagz)
                glColor3f(0.8, 0.8, 0.8);
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

void desenhaBolas() {
    glColor3f(1, 0, 0);
    glPushMatrix();
        glTranslatef(-100, 0, 0);
        glutSolidSphere(2, 32, 32);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(100, 0, 0);
        glutSolidSphere(2, 32, 32);
    glPopMatrix();
}

// Funo usada para especificar a posio do observador virtual
void PosicionaObservador(void)
{
    // Especifica sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);
    // Inicializa sistema de coordenadas do modelo
    glLoadIdentity();
    // Posiciona e orienta o observador
    gluLookAt( mario.posX, mario.posY + 10, mario.posZ - 20,
              mario.posX, mario.posY, mario.posZ,
              0, 1, 0);
    //glTranslatef(-obsX + mario.posX, -obsY + mario.posY, -obsZ + mario.posZ);
    //glTranslatef(-obsX + mario.posX, -obsY + mario.posY - mario.posZ/2, -obsZ + mario.posZ);
    //glRotatef(rotX, 1, 0, 0);
    //glRotatef(rotY, 0, 1, 0);
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
    // glEnable(GL_DEPTH_TEST);

    // Inicializa a varivel que especifica o ngulo da projeo
    // perspectiva
    angle = 45;

    rotX = 30;
    rotY = 180;
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
}

void renderizarModelos()
{
    glPushMatrix();
    mario.renderizar();

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

    desenhaChao();

    desenhaBolas();

    EspecificaParametrosVisualizacao();

    glutSwapBuffers();
}

// Funo callback para tratar eventos de teclas especiais
void TeclasEspeciais(int tecla, int x, int y)
{
    if (tecla == ultimaTecla) {
        if (aceleracao < 2) {
            aceleracao += 0.1;
        }
    } else {
        aceleracao = 1;
    }

    if (tecla == GLUT_KEY_LEFT) {
        mario.esquerda(aceleracao);
    }
    ultimaTecla = tecla;
    PosicionaObservador();
}

void jump(int animacao) {
    flagJumpin = true;
    if (mario.passo == 2 && mario.frame == 0 && animacao == 1) {
        std::thread audio = std::thread([]() {
            Mario::makeSound("sound/yahoo.wav");
        });
        audio.detach();
    }
    if (mario.passo == 2 && mario.frame == 0 && animacao == 2) {
        std::thread audio = std::thread([]() {
            Mario::makeSound("sound/yippee.wav");
        });
        audio.detach();
    }

    if (mario.passo < mario.veloc) {
        mario.passo++;
        //for (mario.passo = 0; mario.passo < mario.veloc; mario.passo++ )
        mario.obj.animar(animacao, mario.frame, mario.veloc);
    } else {

        mario.obj.animar(animacao, mario.frame, mario.veloc);
        if (mario.frame < mario.obj.animations[animacao].frames.size()-1) {
            mario.frame++;
        } else {
             mario.frame = 0;
        }

        mario.passo = 0;

    }
    std::cout << "frame=" << mario.frame << " passo=" << mario.passo << '\n';
}

void verificaFlags() {
    if (flagW){
        mario.frente(aceleracao);
    }
    if (flagS){
        mario.tras(aceleracao);
    }
    if (flagA){
        mario.esquerda(aceleracao);
    }
    if (flagD){
        mario.direita(aceleracao);
    }
    if (flagSpace && !flagW){
        mario.home();
        for (unsigned int x = 0; x < 36; x++ ) {
            glutTimerFunc(16*x, jump, 1);
        }
        flagSpace = false;
    }
}

float dist(float X1, float Y1, float Z1, float X2, float Y2, float Z2) {
    return sqrt((X1 - X2)*(X1 - X2) + (Y1 - Y2)*(Y1 - Y2) + (Z1 - Z2)*(Z1 - Z2));
}

void make3DSound(const char * filename, float sourceX, float sourceY, float sourceZ)
{
    ALuint buffer, source;
    ALuint state;

    // Captura de erros
    alGetError();

    // carrega arquivo no buffer do OpenAL util
    buffer = alutCreateBufferFromFile(filename);

    // Cria fonte de audio com o buffer
    alGenSources(1, &source);

    alSourcei( source, AL_BUFFER, buffer);

    // Executa
    alSourcePlay(source);

    int x;
    //Espera o fim da execução do audio
    do {
        alGetSourcei(source, AL_SOURCE_STATE, (ALint *)&state);
        x++;
        if (x%100 == 0)
            alSourcef( source, AL_GAIN, 10/dist(sourceX, sourceY, sourceZ,
                                                mario.posX, mario.posY, mario.posZ));

        //std::cout << mario.posX << " " << mario.posY << " " << mario.posZ << '\n';
    } while (state == AL_PLAYING);

    // Limpa as fontes de audio e buffers
    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);
}

void teclaPressiona(unsigned char tecla, int x, int y) {
    if (tecla == ultimaTecla) {
        if (aceleracao < 10) {
            aceleracao += 0.1;
        }
    } else {
        aceleracao = 1;
    }
    std::cout << tecla << '\n';

    if (tecla == 27) // ESC ?
        exit(0);
    if (tecla == 'h')
        mario.home();
    if (tecla == 'w')
        flagW = true;
    if (tecla == 's')
        flagS = true;
    if (tecla == 'a')
        flagA = true;
    if (tecla == 'd')
        flagD = true;
    if (tecla == ' ')
        flagSpace = true;
    if (tecla == 'b' && !flagW) {
        mario.home();
        for (unsigned int x = 0; x < 36; x++ ) {
            glutTimerFunc(16*x, jump, 2);
        }
    }

    ultimaTecla = tecla;
}

void teclaSolta(unsigned char tecla, int x, int y) {
    if (tecla == 'w') {
        mario.home();
        flagW = false;
    }
    if (tecla == 's') {
        flagS = false;
        mario.home();
    }
    if (tecla == 'a') {
        flagA = false;
        mario.home();
    }
    if (tecla == 'd') {
        flagD = false;
        mario.home();
    }
    if (tecla == ' ')
        flagSpace = false;

    if (tecla == 'x') {
        std::thread audio1 = std::thread([]() {
           make3DSound("sound/castle.wav", -100, 0, 0);
        });
        audio1.detach();
        std::thread audio2 = std::thread([]() {
            make3DSound("sound/haunted.wav", 100, 0, 0);
        });
        audio2.detach();
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
    alutInit(0, NULL);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(900, 5);
    glutCreateWindow("Mario");

    glutTimerFunc(300, timer, 1);

    glutDisplayFunc(display);

    // Registra a funcao callback para tratamento das teclas normais
    glutIgnoreKeyRepeat(true);
    glutKeyboardFunc(teclaPressiona);
    glutKeyboardUpFunc(teclaSolta);

    // Registra a funcao callback para tratamento das teclas especiais
    glutSpecialFunc(TeclasEspeciais);    // Registra a funo callback para eventos de botes do mouse

    glutMouseFunc(GerenciaMouse);

    // Registra a funcao callback para eventos de movimento do mouse
    glutMotionFunc(GerenciaMovim);

    glutIdleFunc(verificaFlags);

    if (!mario.obj.LoadGLTextures()) {
        return 1; // If Texture Didn't Load Return FALSE
    }
    glutReshapeFunc(reshape);

    init();

    glutMainLoop();

    alutExit();

    return 0;
}
