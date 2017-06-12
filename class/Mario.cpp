#include "Mario.h"

void Mario::importarHierarquia(){
    this->angX = 0; // angulos
    this->angY = 0;
    this->angZ = 0;

    this->posX = 0; // posicao
    this->posY = 2;
    this->posZ = 0;

    this->scaX = 0; // escala
    this->scaY = 0;
    this->scaZ = 0;

    std::string folder = "Mario64";

    Modelo torso                = Modelo(folder, "Torso"               , this->posX, this->posY, this->posZ, 0.0, 0.0, 0.0);
    Modelo head                 = Modelo(folder, "Head"                , 0.0, 0.3, 0.1, 0.0, 0.0, 0.0);
    Modelo left_Arm_Upper       = Modelo(folder, "Left_Arm_Upper"      , 0.2, 0.0, 0.0, 0.0, 0.0, 0.0);
    Modelo left_Arm_Lower       = Modelo(folder, "Left_Arm_Lower"      , 0.25, 0.0,-0.04, 0.0, 0.0, 0.0);
    Modelo left_Arm_Hand        = Modelo(folder, "Left_Arm_Hand"       , 0.22, 0.0, -0.04, 0.0, 0.0, 0.0);
    Modelo right_Arm_Upper      = Modelo(folder, "Right_Arm_Upper"     ,-0.2, 0.0, 0.0, 0.0, 0.0, 0.0);
    Modelo right_Arm_Lower      = Modelo(folder, "Right_Arm_Lower"     ,-0.25, 0.06,-0.04, 0.0, 0.0, 0.0);
    Modelo right_Arm_Hand       = Modelo(folder, "Right_Arm_Hand"      ,-0.22, 0.05, -0.04, 0.0, 0.0, 0.0);
    Modelo left_Leg_Upper       = Modelo(folder, "Left_Leg_Upper"      , 0.25, -0.3,-0.1, -32,  32,  15);
    Modelo left_Leg_Lower       = Modelo(folder, "Left_Leg_Lower"      , 0.0, -0.4, 0.1, 25, 0.0, 0.0);
    Modelo left_Leg_Foot        = Modelo(folder, "Left_Leg_Foot"       , 0.0, -0.3, 0.2, 0.0, 0.0, 0.0);
    Modelo right_Leg_Upper      = Modelo(folder, "Right_Leg_Upper"     ,-0.25, -0.3,-0.1, -32, -32, -15);
    Modelo right_Leg_Lower      = Modelo(folder, "Right_Leg_Lower"     ,-0.0, -0.4, 0.1, 25, 0.0, 0.0);
    Modelo right_Leg_Foot       = Modelo(folder, "Right_Leg_Foot"      ,-0.0, -0.3, 0.2, 0.0, 0.0, 0.0);

    Animation anime = Animation("something");
    anime.frames.push_back(Frame(0, 0, 0, 30, 0 ,0, 1, 2, 1));
    anime.frames.push_back(Frame(0, 0, 0, 60, 0 ,0, 1, 2, 1));
    anime.frames.push_back(Frame(0, 0, 0, 90, 0 ,0, 1, 2, 1));
    anime.frames.push_back(Frame(0, 0, 0,120, 0 ,0, 1, 2, 1));
    anime.frames.push_back(Frame(0, 0, 0,150, 0 ,0, 1, 2, 1));
    anime.frames.push_back(Frame(0, 0, 0,180, 0 ,0, 1, 2, 1));
    anime.frames.push_back(Frame(0, 0, 0,210, 0 ,0, 1, 2, 1));
    anime.frames.push_back(Frame(0, 0, 0,240, 0 ,0, 1, 2, 1));
    anime.frames.push_back(Frame(0, 0, 0,270, 0 ,0, 1, 2, 1));
    anime.frames.push_back(Frame(0, 0, 0,300, 0 ,0, 1, 2, 1));
    anime.frames.push_back(Frame(0, 0, 0,330, 0 ,0, 1, 2, 1));
    anime.frames.push_back(Frame(1, 0, 0,  0, 0 ,0, 1, 2, 1));

    torso.animations.push_back(anime);
    head.animations.push_back(anime);
    left_Arm_Upper.animations.push_back(anime);
    left_Arm_Lower.animations.push_back(anime);
    left_Arm_Hand.animations.push_back(anime);
    right_Arm_Upper.animations.push_back(anime);
    right_Arm_Lower.animations.push_back(anime);
    right_Arm_Hand.animations.push_back(anime);
    left_Leg_Upper.animations.push_back(anime);
    left_Leg_Lower.animations.push_back(anime);
    left_Leg_Foot.animations.push_back(anime);
    right_Leg_Upper.animations.push_back(anime);
    right_Leg_Lower.animations.push_back(anime);
    right_Leg_Foot.animations.push_back(anime);

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
