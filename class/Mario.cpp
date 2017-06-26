#include "Mario.h"

void Mario::importarHierarquia(){
    this->rotX = 0; // rotulos
    this->rotY = 0;
    this->rotZ = 0;

    this->posX = 0; // posicao
    this->posY = 0;
    this->posZ = 0;

    this->scaX = 0; // escala
    this->scaY = 0;
    this->scaZ = 0;

    std::string folder = "Mario64";

    Modelo torso                = Modelo(folder, "Torso"               , 0.0, 1.275, 0.0, 0.0, 0.0, 0.0);
    Modelo head                 = Modelo(folder, "Head"                , 0.0, 0.3, 0.1, 0.0, 0.0, 0.0);
    Modelo left_Arm_Upper       = Modelo(folder, "Left_Arm_Upper"      , 0.4, 0.2, 0.0, 90, -40, 0);
    Modelo left_Arm_Lower       = Modelo(folder, "Left_Arm_Lower"      , 0.3, 0.025,-0.1, 0.0, -40, 0.0);
    Modelo left_Arm_Hand        = Modelo(folder, "Left_Arm_Hand"       , 0.3, 0.0, -0.03, 0.0, 0.0, 0.0);
    Modelo right_Arm_Upper      = Modelo(folder, "Right_Arm_Upper"     ,-0.4, 0.2, 0.0, 90, 40, 0);
    Modelo right_Arm_Lower      = Modelo(folder, "Right_Arm_Lower"     ,-0.3, 0.025,-0.1, 0.0, 40, 0.0);
    Modelo right_Arm_Hand       = Modelo(folder, "Right_Arm_Hand"      ,-0.3, 0.0, -0.03, 0.0, 0.0, 0.0);
    Modelo left_Leg_Upper       = Modelo(folder, "Left_Leg_Upper"      , 0.25, -0.3,-0.1, -32,  32,  15);
    Modelo left_Leg_Lower       = Modelo(folder, "Left_Leg_Lower"      , 0.0, -0.4, 0.03, 25, 0.0, 0.0);
    Modelo left_Leg_Foot        = Modelo(folder, "Left_Leg_Foot"       , 0.0, -0.3, 0.2, 0.0, 0.0, 0.0);
    Modelo right_Leg_Upper      = Modelo(folder, "Right_Leg_Upper"     ,-0.25, -0.3,-0.1, -32, -32, -15);
    Modelo right_Leg_Lower      = Modelo(folder, "Right_Leg_Lower"     ,-0.0, -0.4, 0.03, 25, 0.0, 0.0);
    Modelo right_Leg_Foot       = Modelo(folder, "Right_Leg_Foot"      ,-0.0, -0.3, 0.2, 0.0, 0.0, 0.0);


    ////// ANIMACOES

    ///CAMINHAR
    Animation walk = Animation("walk");
    Animation empty = Animation("walk");
    for (unsigned int i = 0; i < 4; i++) {
        empty.frames.push_back(Frame());
    }

    torso.animations.push_back(empty);

    head.animations.push_back(empty);

    walk.frames.clear();
    walk.frames.push_back(Frame( 000, 000, -40));
    walk.frames.push_back(Frame( 000, 000, +40));
    walk.frames.push_back(Frame( 000, 000, +40));
    walk.frames.push_back(Frame( 000, 000, -40));
    left_Arm_Upper.animations.push_back(walk);

    left_Arm_Lower.animations.push_back(empty);

    left_Arm_Hand.animations.push_back(empty);

    walk.frames.clear();
    walk.frames.push_back(Frame( 000, 000, -40));
    walk.frames.push_back(Frame( 000, 000, +40));
    walk.frames.push_back(Frame( 000, 000, +40));
    walk.frames.push_back(Frame( 000, 000, -40));
    right_Arm_Upper.animations.push_back(walk);

    right_Arm_Lower.animations.push_back(empty);

    right_Arm_Hand.animations.push_back(empty);

    walk.frames.clear();
    walk.frames.push_back(Frame( -40, 000, 000));
    walk.frames.push_back(Frame( +40, 000, 000));
    walk.frames.push_back(Frame( +40, 000, 000));
    walk.frames.push_back(Frame( -40, 000, 000));
    left_Leg_Upper.animations.push_back(walk);

    walk.frames.clear();

    walk.frames.push_back(Frame( -20, 000, 000));
    walk.frames.push_back(Frame( +20, 000, 000));
    walk.frames.push_back(Frame( +20, 000, 000));
    walk.frames.push_back(Frame( -20, 000, 000));
    left_Leg_Lower.animations.push_back(walk);

    walk.frames.clear();
    walk.frames.push_back(Frame( +20, 000, 000));
    walk.frames.push_back(Frame( -20, 000, 000));
    walk.frames.push_back(Frame( +20, 000, 000));
    walk.frames.push_back(Frame( -20, 000, 000));
    left_Leg_Foot.animations.push_back(walk);

    walk.frames.clear();
    walk.frames.push_back(Frame( +40, 000, 000));
    walk.frames.push_back(Frame( -40, 000, 000));
    walk.frames.push_back(Frame( -40, 000, 000));
    walk.frames.push_back(Frame( +40, 000, 000));
    right_Leg_Upper.animations.push_back(walk);

    walk.frames.clear();
    walk.frames.push_back(Frame( +20, 000, 000));
    walk.frames.push_back(Frame( -20, 000, 000));
    walk.frames.push_back(Frame( -20, 000, 000));
    walk.frames.push_back(Frame( +20, 000, 000));
    right_Leg_Lower.animations.push_back(walk);

    walk.frames.clear();
    walk.frames.push_back(Frame( +20, 000, 000));
    walk.frames.push_back(Frame( -20, 000, 000));
    walk.frames.push_back(Frame( +20, 000, 000));
    walk.frames.push_back(Frame( -20, 000, 000));
    right_Leg_Foot.animations.push_back(walk);

    ///PULAR
    Animation jump = Animation("jump");

    jump.frames.clear();
    jump.frames.push_back(Frame( 000, 000, 000, 00, -0.2, 00));
    jump.frames.push_back(Frame( 000, 000, 000, 00, +2.0, 00));
    jump.frames.push_back(Frame( 000, 000, 000, 00, -0.8, 00));
    jump.frames.push_back(Frame( 000, 000, 000, 00, -1.0, 00));
    torso.animations.push_back(jump);

    head.animations.push_back(empty);

    jump.frames.clear();
    jump.frames.push_back(Frame( -90, 000, -45));
    jump.frames.push_back(Frame( -90, 000, -45));
    jump.frames.push_back(Frame( +90, 000, +45));
    jump.frames.push_back(Frame( +90, 000, +45));
    left_Arm_Upper.animations.push_back(jump);

    left_Arm_Lower.animations.push_back(empty);

    left_Arm_Hand.animations.push_back(empty);

    jump.frames.clear();
    jump.frames.push_back(Frame( 000, 000, 000));
    jump.frames.push_back(Frame( 000, 000, 000));
    jump.frames.push_back(Frame( 000, 000, 000));
    jump.frames.push_back(Frame( 000, 000, 000));
    right_Arm_Upper.animations.push_back(jump);

    right_Arm_Lower.animations.push_back(empty);

    right_Arm_Hand.animations.push_back(empty);

    jump.frames.clear();
    jump.frames.push_back(Frame( -80, 000, 000));
    jump.frames.push_back(Frame( +80, 000, 000));
    jump.frames.push_back(Frame( 000, 000, 000));
    jump.frames.push_back(Frame( 000, 000, 000));
    left_Leg_Upper.animations.push_back(jump);

    jump.frames.clear();

    jump.frames.push_back(Frame( +80, 000, +40));
    jump.frames.push_back(Frame( -80, 000, -40));
    jump.frames.push_back(Frame( 000, 000, 000));
    jump.frames.push_back(Frame( 000, 000, 000));
    left_Leg_Lower.animations.push_back(jump);

    jump.frames.clear();
    jump.frames.push_back(Frame( 000, 000, 000));
    jump.frames.push_back(Frame( 000, 000, 000));
    jump.frames.push_back(Frame( 000, 000, 000));
    jump.frames.push_back(Frame( 000, 000, 000));
    left_Leg_Foot.animations.push_back(jump);

    jump.frames.clear();
    jump.frames.push_back(Frame( -80, 000, 000));
    jump.frames.push_back(Frame( +80, 000, 000));
    jump.frames.push_back(Frame( 000, 000, 000));
    jump.frames.push_back(Frame( 000, 000, 000));
    right_Leg_Upper.animations.push_back(jump);

    jump.frames.clear();
    jump.frames.push_back(Frame( +80, 000, -40));
    jump.frames.push_back(Frame( -80, 000, +40));
    jump.frames.push_back(Frame( 000, 000, 000));
    jump.frames.push_back(Frame( 000, 000, 000));
    right_Leg_Lower.animations.push_back(jump);

    jump.frames.clear();
    jump.frames.push_back(Frame( +20, 000, 000));
    jump.frames.push_back(Frame( -20, 000, 000));
    jump.frames.push_back(Frame( +20, 000, 000));
    jump.frames.push_back(Frame( -20, 000, 000));
    right_Leg_Foot.animations.push_back(jump);

    ///BACKFLIP
    Animation backflip = Animation("backflip");

    backflip.frames.clear();
    backflip.frames.push_back(Frame( +000, 000, 000, 00, -0.2, 00));
    backflip.frames.push_back(Frame( -111, 000, 000, 00, +2.0, 00));
    backflip.frames.push_back(Frame( -111, 000, 000, 00, -0.8, 00));
    backflip.frames.push_back(Frame( -111, 000, 000, 00, -1.0, 00));
    torso.animations.push_back(backflip);

    head.animations.push_back(empty);

    backflip.frames.clear();
    backflip.frames.push_back(Frame( -90, 000, -45));
    backflip.frames.push_back(Frame( -90, 000, -45));
    backflip.frames.push_back(Frame( +90, 000, +45));
    backflip.frames.push_back(Frame( +90, 000, +45));
    left_Arm_Upper.animations.push_back(backflip);

    left_Arm_Lower.animations.push_back(empty);

    left_Arm_Hand.animations.push_back(empty);

    backflip.frames.clear();
    backflip.frames.push_back(Frame( 000, 000, 000));
    backflip.frames.push_back(Frame( 000, 000, 000));
    backflip.frames.push_back(Frame( 000, 000, 000));
    backflip.frames.push_back(Frame( 000, 000, 000));
    right_Arm_Upper.animations.push_back(backflip);

    right_Arm_Lower.animations.push_back(empty);

    right_Arm_Hand.animations.push_back(empty);

    backflip.frames.clear();
    backflip.frames.push_back(Frame( -80, 000, 000));
    backflip.frames.push_back(Frame( +80, 000, 000));
    backflip.frames.push_back(Frame( 000, 000, 000));
    backflip.frames.push_back(Frame( 000, 000, 000));
    left_Leg_Upper.animations.push_back(backflip);

    backflip.frames.clear();

    backflip.frames.push_back(Frame( +80, 000, +40));
    backflip.frames.push_back(Frame( -80, 000, -40));
    backflip.frames.push_back(Frame( 000, 000, 000));
    backflip.frames.push_back(Frame( 000, 000, 000));
    left_Leg_Lower.animations.push_back(backflip);

    backflip.frames.clear();
    backflip.frames.push_back(Frame( 000, 000, 000));
    backflip.frames.push_back(Frame( 000, 000, 000));
    backflip.frames.push_back(Frame( 000, 000, 000));
    backflip.frames.push_back(Frame( 000, 000, 000));
    left_Leg_Foot.animations.push_back(backflip);

    backflip.frames.clear();
    backflip.frames.push_back(Frame( -80, 000, 000));
    backflip.frames.push_back(Frame( +80, 000, 000));
    backflip.frames.push_back(Frame( 000, 000, 000));
    backflip.frames.push_back(Frame( 000, 000, 000));
    right_Leg_Upper.animations.push_back(backflip);

    backflip.frames.clear();
    backflip.frames.push_back(Frame( +80, 000, -40));
    backflip.frames.push_back(Frame( -80, 000, +40));
    backflip.frames.push_back(Frame( 000, 000, 000));
    backflip.frames.push_back(Frame( 000, 000, 000));
    right_Leg_Lower.animations.push_back(backflip);

    backflip.frames.clear();
    backflip.frames.push_back(Frame( +20, 000, 000));
    backflip.frames.push_back(Frame( -20, 000, 000));
    backflip.frames.push_back(Frame( +20, 000, 000));
    backflip.frames.push_back(Frame( -20, 000, 000));
    right_Leg_Foot.animations.push_back(backflip);


    right_Leg_Lower.filhos.push_back(right_Leg_Foot);
    right_Leg_Upper.filhos.push_back(right_Leg_Lower);
    torso.filhos.push_back(right_Leg_Upper);

    left_Leg_Lower.filhos.push_back(left_Leg_Foot);
    left_Leg_Upper.filhos.push_back(left_Leg_Lower);
    torso.filhos.push_back(left_Leg_Upper);

    right_Arm_Lower.filhos.push_back(right_Arm_Hand);
    right_Arm_Upper.filhos.push_back(right_Arm_Lower);
    torso.filhos.push_back(right_Arm_Upper);

    left_Arm_Lower.filhos.push_back(left_Arm_Hand);
    left_Arm_Upper.filhos.push_back(left_Arm_Lower);
    torso.filhos.push_back(left_Arm_Upper);

    torso.filhos.push_back(head);

    this->obj = torso;

};

void Mario::makeSound(const char * filename)
{
    ALuint buffer, source;
    ALuint state;

    // Capture errors
    alGetError();

    // Load pcm data into buffer
    buffer = alutCreateBufferFromFile(filename);

    // Create sound source (use buffer to fill source)
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, buffer);

    // Play
    alSourcePlay(source);

    // Wait for the song to complete
    do {
        alGetSourcei(source, AL_SOURCE_STATE, (ALint *)&state);
    } while (state == AL_PLAYING);

    // Clean up sources and buffers
    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);
}

void Mario::animate(int animacao) {
    //if (this->passo == 0) {
        //std::thread video(this->makeSound, "sound/step.wav");
    //}
    if (this->passo < this->veloc) {
        this->passo++;
        //for (this->passo = 0; this->passo < this->veloc; this->passo++ )
        this->obj.animar(animacao, this->frame, this->veloc);
    } else {
        if (this->frame < this->obj.animations[animacao].frames.size() - 1)
            this->frame++;
        else {
            this->frame = 0;
        }

        this->passo = 0;
        //for (this->passo = 0; this->passo < this->veloc; this->passo++ )
        this->obj.animar(animacao, this->frame, this->veloc);
    }
}

void Mario::frente(int aceleracao) {
    if ((passo == 2 && frame == 1) || (passo == 6 && frame == 2)) {
        std::thread audio = std::thread([]() {
            makeSound("sound/step.wav");
        });
        audio.detach();
    }
    this->rotY += 0;
    //this->posZ += (0.1 * aceleracao);
    float rad = this->rotY * M_PI/180;
    //std::cout << "rotY=" << (int)(this->rotY)%360  << "rad=" << rad  << '\n';
    this->posX += sin(rad) * this->accel;
    this->posZ += cos(rad) * this->accel;
    this->animate(0);
}

void Mario::esquerda(int aceleracao) {
    this->rotY += 3;
    this->animate(0);
}

void Mario::direita(int aceleracao) {
    this->rotY -= 3;
    this->animate(0);
}

void Mario::tras(int aceleracao) {
    this->rotY += 180;
    this->animate(0);
}

void Mario::renderizar() {
    glPushMatrix();
        glTranslatef(this->posX, this->posY, this->posZ); // vai para o meio do osso
        glRotatef(this->rotX, 1, 0, 0); // vai para o meio do osso
        glRotatef(this->rotY, 0, 1, 0); // vai para o meio do osso
        glRotatef(this->rotZ, 0, 0, 1); // vai para o meio do osso

        //glLoadIdentity();

        this->obj.renderizar();
    glPopMatrix();
}

void Mario::home() {
    this->obj.home();
    this->frame = 0;
    this->veloc = 8;
    this->passo = 0;
}

void Mario::pular() {
    home();
    // for (unsigned int x = 0; x < 16; x++ ) {
    //     //std::sleep(16);
    //     animate(1);
    //     glutPostRedisplay();
    // }
    //glutTimerFunc(16, &Mario::staticAnimate, 1);
    //this->animate(1);
}
