#ifndef INICIO_H
#define INICIO_H
#include <pdcurs36/curses.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Crear.h"
#include "estructuras/ListaCircular.h"
using namespace std;

class Inicio
{
private:
    /* data */
public:
    Inicio(ListaCircular *listaArchivos);
};
Inicio::Inicio(ListaCircular *listaArchivos)
{
    //cout << "Ya salio" << endl;
    /* INICIA PDCURSES */
    initscr();
    //Variables que manejan las caracteristicas de la ventana (win).
    int height, width, startY, startX;
    int yMax, xMax;
    //Se obtiene el tamanio de la ventana de la consola (stdscr).
    getmaxyx(stdscr, yMax, xMax);

    height = yMax - 2;
    width = xMax - 4;
    startX = 2;
    startY = 1;
    //Ventana donde se coloca la informacion que se desea.
    WINDOW *win = newwin(height, width, startY, startX);
    //Se refresca la pantalla "stdscr".
    refresh();
    //Se imprime la informacion que contendra el menu principal
    //insertando un texto indicando la ventana a utilizar, posY, posX y la cadena.
    mvwprintw(win, 1, 1, "Universidad de San Carlos de Guatemala\n Facultad de Ingenieria\n Estructuras de Datos\n Practica 01\n");
    //Imprime en el centro de la ventana win un mensaje.
    mvwprintw(win, height / 2, width / 2 - 17, "!Bienvenido a mi editor de texto!");
    mvwprintw(win, height / 2 + 1, width / 2 - 32, "Presiona las flechas para navegar y escoge una opcion con Enter");
    //Se crea una caja dentro del puntero creado para la ventana.
    box(win, 0, 0);
    //Se refresca la ventana "win".
    wrefresh(win);
    //Se crea un menu de opciones en las que el user puede
    //navegar.
    WINDOW *menu = newwin(5, width - 2, height - 5, startX + 1);
    //Se imprimen las opciones a utilizar.
    mvwprintw(menu, 0, 0, "MENU:");
    //Se refresca el menu.
    wrefresh(menu);
    //Se permite que se pueda usar cualquier tecla.
    //Recibe la tecla seleccionada.
    keypad(menu, true);
    //Arreglo de las opciones que se seleccionaran.
    string options[4] = {"1. Crear Archivo", "2. Abrir Archivo", "3. Archivos Recientes", "4. Salir"};
    //Variable que alojara la seleccion
    int choice;
    //Variable que indica la opcion que estara siendo resaltada.
    int highlight = 0;
    //(hilo) Permanece en el ciclo hasta que el usuario presione Enter.
    while (1)
    {
        for (int i = 0; i < 4; i++)
        {
            if (i == highlight)
            {
                //Se activa atributo reversa para una ventana en especifico.
                wattron(menu, A_REVERSE);
            }
            //Se imprime la opcion del arreglo con el cambio de atributo.
            mvwprintw(menu, i + 1, 1, options[i].c_str());
            //Se desactiva atributo reversa.
            wattroff(menu, A_REVERSE);
        }
        //Guarda la seleccion.
        choice = wgetch(menu);
        //Compara la tecla presionada.
        switch (choice)
        {
        //Presiona Arriba.
        case KEY_UP:
            //Regresa una posicion en el arreglo para cambiar la variable resaltada.
            highlight--;
            //Si se encuentra fuera del arreglo, regresa a 0.
            if (highlight == -1)
                highlight = 0;
            break;
        case KEY_DOWN:
            //Avanza una posicion en el arreglo para cambiar la variable.
            highlight++;
            //Si se encuentra fuera del arreglo, regresa a 3.
            if (highlight == 4)
                highlight = 3;
            break;
        }
        //Si presiona Enter.
        if (choice == 10)
        {
            //Rompe el hilo.
            break;
        }
        //Si presiona Enter.
        char c = '.';
        if (choice == 10)
        {
            refresh();
        }
    }
    //!!!TEMPORAL!!!
    printw("Escogiste: %s", options[highlight].c_str());
    //!!!TEMPORAL!!!
    getch();
    endwin();

    /* TERMINA PDCURSES */
    //switch (choice){ opciones de cambio de ventana segun la escogida en el menu. }
    //Para crear archivo.
    if (highlight == 0)
    {
        string vacio = "";
        Crear cre(vacio, listaArchivos);
    }
    //Para abrir archivo.
    else if (highlight == 1)
    {
        initscr();
        noecho();
        //Muestra texto para indicar que se debe insertar informacion.
        mvprintw(1, startX, "Abrir Archivo: ");
        //Se crea string que contendra los datos para la busqueda.
        string nombre = "";
        int ascii = 0;
        do
        {
            //Recibe el codigo ascii del caracter ingresado
            ascii = getch();
            //Lo convierte a tipo char
            char newChar = (char)ascii;
            //Si no es un enter continua recibiendo los parametros de busqueda.
            if (ascii != 10)
            {
                //Concatena el caracter al string.
                nombre.append(1u, newChar);
                //Imprimiendo en pantalla.
                mvprintw(1, startX + 16, nombre.c_str());
            }
        } while (ascii != 10);
        string text;
        ifstream file;
        file.open(nombre.c_str());
        getline(file, text);
        endwin();
        if (text.length() != 0)
        {
            Archivo *newArchivo = new Archivo(nombre, nombre);
            listaArchivos->addLast(newArchivo);
        }
        Crear cre(text, listaArchivos);
    }
    //Para archivos recientes.
    else if (highlight == 2)
    {
        Reciente rec(listaArchivos);
    }
    //Para salir.
    else if (highlight == 3)
    {
        exit(0);
    }
    else
    {
        exit(0);
    }

    /*
        //colores y atributos
        attron(A_BOLD);
        printw("letrita");
        attroff(A_BOLD);
        refresh();

        getch();
        */
}

#endif // INICIO_H