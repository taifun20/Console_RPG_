
#include "Game_Scenes_.h"


//  Shadows of Eternia
int main()
{
    _Game_Scene_01_();
}


/*

Obiectiv:
Creati o aplicatie joc de tip console RPG.
Un jucator poate sa isi seteze numele si clasa din care face parte
    Wizard, Warrior, Rogue
Jocul trebuie sa aibe urmatoarele scene:
O scena Intro - se prezinta lumea si se intreaba jucatorul daca vrea sa joace
O scena SetupPlayer - Se intreaba numele jucatorului si ce clasa vrea sa fie iar dupa selectie
un mic mesaj despre alegerea facuta
O scena CrossRoads - I se prezinta jucatorului ca este la o intalnire de drumuri si poate alege
sa mearga pe una dintre cele 3 drumuri care duc catre o padure, un sat sau catre o pestera
O scena Cufar - Pe oricare drum ales jucatorului ii ies e in cale un cufar, daca alege sa deschida cufarul va trebui sa primeasca niste obiecte ce vor fi adaugate in inventar, aceste obiecte sa fie in functie de ce clasa este playerul.
O scena Battel - Pe drum ii iese un inamic random(poate fi orc, golbin sau troll) si trebuie sa lupte cu inamicul, in cazul in care castiga ajunge la destinatie, in caz contrar se va printa un
mesaj de end game.
Codul trebuie scris in C++ si sa fie urcat in Github
Pentru fiecare dintre scene trebuie schimbata melodia din fundal(Main_Menu.wav,Exploring.wav,BattelFinal.wav)

*/