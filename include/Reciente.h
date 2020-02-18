#ifndef RECIENTE_H
#define RECIENTE_H
#include <pdcurs36/curses.h>
#include <string>
#include <sstream>
#include "estructuras/ListaCircular.h"
class Reciente
{
private:
    /* data */
public:
    Reciente(ListaCircular *listaArchivos);
    ~Reciente();
};

Reciente::Reciente(ListaCircular *listaArchivos)
{
    initscr();
    noecho();
    //Variables que manejan las caracteristicas de la ventana (win).
    int height, width, startY, startX;
    int yMax, xMax;
    //Se obtiene el tamanio de la ventana de la consola (stdscr).
    getmaxyx(stdscr, yMax, xMax);

    height = yMax - 2;
    width = xMax - 4;
    startX = 2;
    startY = 1;
    WINDOW *frameBorder = newwin(height, width, startY, startX);
    box(frameBorder, 0, 0);
    refresh();
    WINDOW *workSpace = newwin(height - 3, width - 2, startY + 1, startX + 1);
    wrefresh(frameBorder);
    mvwprintw(workSpace, 1, startX, "ARCHIVOS RECIENTES");
    mvwprintw(workSpace, startY+13, startX, "Ctrl+X para generar reporte.");

    for (int i = 1; i <= listaArchivos->getSize(); i++)
    {
        string info = "";
        stringstream ss1;
        ss1 << i;
        ss1 >> info;
        info.append(". ");
        info.append(listaArchivos->getObjectAt(i - 1)->getNombre());
        info.append("           ");
        info.append(listaArchivos->getObjectAt(i - 1)->getRuta());
        mvwprintw(workSpace, i + 1, startX + 3, info.c_str());
    }
    wrefresh(workSpace);

    keypad(workSpace, true);

    int opcion = getch();
    if (opcion == 24)
    {
        ofstream file;
        file.open("Archivos.dot");
        string graphviz = "digraph ReporteArchivos{\nrankdir=LR;\nnode [shape=record fontname=Arial];\n";
        int i = 0;
        for (i; i < listaArchivos->getSize(); i++)
        {
            stringstream ss1;
            ss1 << i;
            string s1;
            ss1 >> s1;
            graphviz.append("var");
            graphviz.append(s1);
            graphviz.append(" [label=\"");
            graphviz.append(listaArchivos->getObjectAt(i)->getNombre());
            graphviz.append("\\l");
            graphviz.append(listaArchivos->getObjectAt(i)->getRuta());
            graphviz.append("\\l\"];\n");
        }
        for (int j = 0; j < i; j++)
        {
            graphviz.append("var");
            stringstream ss2;
            ss2 << j;
            string s2;
            ss2 >> s2;
            graphviz.append(s2);
            graphviz.append(" -> ");
        }
        graphviz.append(" var");
        stringstream ss2;
        i = 0;
        ss2 << i;
        string s2;
        ss2 >> s2;
        graphviz.append(s2);
        graphviz.append(";\n}\n");
        file << graphviz;
        file.close();
    }
    getch();
    endwin();
}

Reciente::~Reciente()
{
}
#endif //RECIENTE_H