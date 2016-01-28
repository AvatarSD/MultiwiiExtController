#ifndef JOYTYPES
#define JOYTYPES

struct JoyData
{
    short int aux2;//RTrigger;   //порядок не менять!
    short int aux1;//Ltrigger;
    short int yaw;//RAxisY;
    short int throt;//LAxisX;
    short int pich;//LAxisY;
    short int roll;//RAxisX;





    //bool Btn1, Btn2, Btn3, Btn4, Btn5, Btn6, Btn7, Btn8, Btn9, Btn10, Btn11, Btn12, Btn13, Btn14, Btn15;
};

#endif // JOYTYPES

