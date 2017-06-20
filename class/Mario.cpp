#include "Mario.h"

void Mario::importarHierarquia(){
    this->angX = 0; // angulos
    this->angY = 0;
    this->angZ = 0;

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

    Animation anime = Animation("idle");
    Animation empty = Animation("idle");

    for (unsigned int i = 0; i < 4; i++) {
        empty.frames.push_back(Frame());
    }

    torso.animations.push_back(empty);

    anime.frames.clear();

    anime.frames.push_back(Frame( 000, -10, 000));
    anime.frames.push_back(Frame( 000, -20, 000));
    anime.frames.push_back(Frame( 000, -30, 000));
    anime.frames.push_back(Frame( 000, +30, 000));
    anime.frames.push_back(Frame( 000, +20, 000));
    anime.frames.push_back(Frame( 000, +10, 000));
    anime.frames.push_back(Frame( 000, +10, 000));
    anime.frames.push_back(Frame( 000, +20, 000));
    anime.frames.push_back(Frame( 000, +30, 000));
    anime.frames.push_back(Frame( 000, -10, 000));
    anime.frames.push_back(Frame( 000, -20, 000));
    anime.frames.push_back(Frame( 000, -30, 000));
    head.animations.push_back(empty);

    anime.frames.clear();
    anime.frames.push_back(Frame( 000, 000, -40));
    anime.frames.push_back(Frame( 000, 000, +40));
    anime.frames.push_back(Frame( 000, 000, +40));
    anime.frames.push_back(Frame( 000, 000, -40));
    left_Arm_Upper.animations.push_back(anime);

    anime.frames.clear();
    left_Arm_Lower.animations.push_back(empty);

    anime.frames.clear();
    left_Arm_Hand.animations.push_back(empty);

    anime.frames.clear();
    anime.frames.push_back(Frame( 000, 000, -40));
    anime.frames.push_back(Frame( 000, 000, +40));
    anime.frames.push_back(Frame( 000, 000, +40));
    anime.frames.push_back(Frame( 000, 000, -40));
    right_Arm_Upper.animations.push_back(anime);

    anime.frames.clear();
    right_Arm_Lower.animations.push_back(empty);

    anime.frames.clear();
    right_Arm_Hand.animations.push_back(empty);

    anime.frames.clear();

    anime.frames.push_back(Frame( -40, 000, 000));
    anime.frames.push_back(Frame( +40, 000, 000));
    anime.frames.push_back(Frame( +40, 000, 000));
    anime.frames.push_back(Frame( -40, 000, 000));
    left_Leg_Upper.animations.push_back(anime);

    anime.frames.clear();

    anime.frames.push_back(Frame( -20, 000, 000));
    anime.frames.push_back(Frame( +20, 000, 000));
    anime.frames.push_back(Frame( +20, 000, 000));
    anime.frames.push_back(Frame( -20, 000, 000));
    left_Leg_Lower.animations.push_back(anime);

    anime.frames.clear();
    anime.frames.push_back(Frame( +20, 000, 000));
    anime.frames.push_back(Frame( -20, 000, 000));
    anime.frames.push_back(Frame( +20, 000, 000));
    anime.frames.push_back(Frame( -20, 000, 000));
    left_Leg_Foot.animations.push_back(anime);

    anime.frames.clear();
    anime.frames.push_back(Frame( +40, 000, 000));
    anime.frames.push_back(Frame( -40, 000, 000));
    anime.frames.push_back(Frame( -40, 000, 000));
    anime.frames.push_back(Frame( +40, 000, 000));
    right_Leg_Upper.animations.push_back(anime);

    anime.frames.clear();
    anime.frames.push_back(Frame( +20, 000, 000));
    anime.frames.push_back(Frame( -20, 000, 000));
    anime.frames.push_back(Frame( -20, 000, 000));
    anime.frames.push_back(Frame( +20, 000, 000));
    right_Leg_Lower.animations.push_back(anime);

    anime.frames.clear();
    anime.frames.push_back(Frame( +20, 000, 000));
    anime.frames.push_back(Frame( -20, 000, 000));
    anime.frames.push_back(Frame( +20, 000, 000));
    anime.frames.push_back(Frame( -20, 000, 000));
    right_Leg_Foot.animations.push_back(anime);

    anime.frames.clear();

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

void Mario::animate(int value) {

    if (this->passo < this->veloc) {
        this->passo++;
        //for (this->passo = 0; this->passo < this->veloc; this->passo++ )
        this->obj.animar(0, this->frame, this->veloc);
    } else {
        if (this->frame < this->obj.animations[this->obj.animacao].frames.size() - 1)
            this->frame++;
        else
            this->frame = 0;

        this->passo = 0;
        //for (this->passo = 0; this->passo < this->veloc; this->passo++ )
        this->obj.animar(0, this->frame, this->veloc);
    }
}

void Mario::frente(int aceleracao) {
    this->obj.rotY += 0;
    this->obj.posZ += (0.1 * aceleracao);
    this->animate(1);
}

void Mario::esquerda(int aceleracao) {
    this->obj.rotY--;
    //this->obj.posX += (0.1 * aceleracao);
    this->animate(1);
}

void Mario::direita(int aceleracao) {
    this->obj.rotY++;
    //this->obj.posX -= (0.1 * aceleracao);
    this->animate(1);
}

void Mario::tras(int aceleracao) {
    this->obj.rotY += 180;
    //this->obj.posZ -= (0.1 * aceleracao);
    this->animate(1);
}
