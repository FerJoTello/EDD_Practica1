#include <iostream>
#include <pdcurs36/curses.h>
#include <string>
#include <sstream>
#include <stdlib.h>
#include "include/Inicio.h"
#include "include/estructuras/ListaCircular.h"
//#include "include/estructuras/ListaDoblementeEnlazada.h"
using namespace std;

int main()
{
    ListaCircular *listaArchivos = new ListaCircular();
    Inicio ini(listaArchivos);
    return 0;
    
} 
