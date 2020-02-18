#ifndef CREAR_H
#define CREAR_H
#include <pdcurs36/curses.h>
#include <iostream>
#include <fstream>
#include "Inicio.h"
#include "estructuras/ListaDoblementeEnlazada.h"
#include "estructuras/Pila.h"
#include "estructuras/ListaCircular.h"
#include "Reciente.h"
#include <string>
using namespace std;
class Crear
{
public:
    Crear(string entradaArchivo, ListaCircular *listaArchivos)
    {
        /* INICIA PDCURSES */
        initscr();
        noecho();
        //Variables que manejan las caracteristicas de la ventana (win).
        int height, width, startY, startX;
        int yMax, xMax;
        //Se obtiene el tamanio de la ventana de la consola (stdscr).
        getmaxyx(stdscr, yMax, xMax);
        height = yMax - 2 + 0;
        width = xMax - 4 + 0;
        startX = 2 + 0;
        //startY = 1;
        startY = 1 + 1;
        //Imprime mensaje perteneciente a la stdscr (fuera de la caja).
        mvprintw(0, startX, "^w (Buscar y Reemplazar)    ^c (Reportes)   ^s (Guardar)");
        //Se refresca la pantalla "stdscr".
        refresh();
        //Ventana para el marco.
        WINDOW *frameBorder = newwin(height, width, startY, startX);
        //Se crea una caja dentro del puntero creado para el marco.
        box(frameBorder, 0, 0);
        //Refrescando nueva ventana creada.
        wrefresh(frameBorder);
        //Ventana para todos los textos
        WINDOW *workSpace = newwin(height - 3, width - 2, startY + 1, startX + 1);
        //Permite el scroll en una ventana cuando se llega al borde de la misma.
        //scrollok(workSpace, true);
        /* EMPIEZA EL VERGUEO */
        keypad(workSpace, true);

        //Variables enteras a utilizar.
        //tecla:aloja el valor ascii de un caracter.
        //posY:posicionY del cursor
        //posX:posicionX del cursor
        //rowMax:numero de filas maximas disponibles.
        //columnMax:numero maximo de caracteres posibles en una fila.
        int tecla, posY, posX, rowMax, columnMax;
        //Se indica que el cursos parte de (0,0).
        tecla = posY = posX = rowMax = 0;
        columnMax = getmaxx(workSpace);
        //Se crean las estructura dinamica.
        ListaDoblementeEnlazada *lDE = new ListaDoblementeEnlazada(columnMax);
        Pila *ctrlZ = new Pila();
        Pila *ctrlY = new Pila();
        for (int i = 0; i < entradaArchivo.length(); i++)
        {
            int chrEntrada = (int)entradaArchivo.at(i);
            Letra *newLetra = new Letra(posY, posX, chrEntrada);
            lDE->add(newLetra);
            if (posX < columnMax)
            {
                //Aumenta la posicion en X
                posX++;
                //Si es igual
                if (posX == columnMax || chrEntrada == 10 && posX != columnMax)
                {
                    //Coloca el cursor en una nueva linea
                    posX = 0;
                    posY++;
                    rowMax++;
                }
            }
            //Se deja vacio workSpace
            werase(workSpace);
            //Se obtiene el nodo cabeza
            Nodo *nodoaux = lDE->getNodoAt(0);
            //Reimpresion de todos los caracteres que le siguen al nodo cabeza
            while (nodoaux != 0)
            {
                //Se obtiene el objeto letra
                Letra *letrita = nodoaux->getObject();
                //se agrega el caracter a la ventana
                mvwaddch(workSpace, letrita->getPosY(), letrita->getPosX(), letrita->getAsciiCode());
                //se refresca la ventana mostrando el caracter que se le agrego
                nodoaux = nodoaux->getNextNodo();
            }
            wrefresh(workSpace);
        }
        mvprintw(0, xMax - 10, "%d", entradaArchivo.length());
        refresh();
        wmove(workSpace, posY, posX);
        do
        {
            //Se obtiene el valor de la tecla presionada.
            tecla = wgetch(workSpace);
            //Si es un caracter.
            if (tecla >= 32 && tecla <= 126 || tecla == 10)
            {
                //Se crea la letra nueva que entrara a la lista.
                Letra *newLetra = new Letra(posY, posX, tecla);
                //Se agrega a la lista y devuelve la posicion en la lista.
                int addedIndex = lDE->add(newLetra);
                //Imprime el caracter en workSpace.
                //wechochar(workSpace, char(tecla));
                //Se agrega el caracter recienIngresado para agregarlo a ctrlZ
                Registro *registroCtrlZ = new Registro(addedIndex, newLetra);
                ctrlZ->push(registroCtrlZ);
                //Se vacia la pila Ctrl+Y por la edicion del texto
                ctrlY->cleanPila();
                //Despues de colocar un caracter se cambian las variables posX y posY para
                //posteriormente desplazar el cursor.
                //Si la posicion del cursor no es igual al maxX del workSpace
                if (posX < columnMax)
                {
                    //Aumenta la posicion en X
                    posX++;
                    //Si es igual
                    if (posX == columnMax || tecla == 10 && posX != columnMax)
                    {
                        //Coloca el cursor en una nueva linea
                        posX = 0;
                        posY++;
                        rowMax++;
                    }
                }
                //Se deja vacio workSpace
                werase(workSpace);
                //Se obtiene el nodo cabeza
                Nodo *nodoaux = lDE->getNodoAt(0);
                //Reimpresion de todos los caracteres que le siguen al nodo cabeza
                while (nodoaux != 0)
                {
                    //Se obtiene el objeto letra
                    Letra *letrita = nodoaux->getObject();
                    //se agrega el caracter a la ventana
                    mvwaddch(workSpace, letrita->getPosY(), letrita->getPosX(), letrita->getAsciiCode());
                    //se refresca la ventana mostrando el caracter que se le agrego
                    nodoaux = nodoaux->getNextNodo();
                }
                wrefresh(workSpace);
            }
            /*Si es un enter
            else if (tecla == 10)
            {
                posX = 0;
                posY++;
                rowMax++;
            }
            */
            //Si son flechas.
            else if (tecla >= 258 && tecla <= 261)
            {
                //Flecha abajo.
                if (tecla == 258)
                {
                    //Valida que no baje mas lineas si no hay caracteres.
                    if (posY != rowMax)
                    {
                        posY++;
                    }
                }
                //Flecha arriba.
                else if (tecla == 259)
                {
                    if (posY == 0)
                    {
                        posY = 0;
                    }
                    else
                    {
                        posY--;
                    }
                }
                //Flecha izquierda.
                else if (tecla == 260)
                {
                    if (posX == 0 && posY == 0)
                    {
                        posX = 0;
                    }
                    else
                    {
                        int index = lDE->getIndexByPosition(posY, posX) - 1;
                        posX--;
                        if (posX == -1 && posY > 0)
                        {
                            //Coloca el cursor en una linea anterior
                            posX = columnMax - 1;
                            posY--;
                        }
                    }
                }
                //Flecha derecha.
                else if (tecla == 261)
                {
                    int index = -1;
                    index = lDE->getIndexByPosition(posY, posX);
                    mvprintw(0, xMax - 10, "%d %d %d %d", lDE->getSize(), index, posY, posX);
                    refresh();
                    if (!lDE->isEmpty())
                    {
                        if (index != lDE->getSize() && posX < columnMax)
                        {
                            posY = lDE->getNodoAt(index)->getObject()->getPosY();
                            posX = lDE->getNodoAt(index)->getObject()->getPosX();
                            posX++;
                            //!!!TEMPORAL!!!
                            //mvprintw(yMax - 1, xMax - 9, "%d %d %d %d", lDE->getSize(), index, posY, posX);
                            //Si es el ultimo de su fila.
                            if (posX == columnMax)
                            {
                                //Coloca el cursor en una nueva linea
                                posX = 0;
                                posY++;
                            }
                        }
                    }
                    else
                    {
                        posX = 0;
                        posY = 0;
                    }
                    /*
                    //Si la posicion no es igual al columnMax
                    if (posX < columnMax)
                    {
                        //Aumenta la posicion en X
                        posX++;
                        //Y si es igual
                        if (posX == columnMax)
                        {
                            //Coloca el cursor en una nueva linea
                            posX = 0;
                            posY++;
                            rowMax++;
                        }
                    }
                    */
                }
            }
            //Si es backspace (borrar).
            else if (tecla == 8)
            {
                int removedIndex = -1;
                removedIndex = lDE->getIndexByPosition(posY, posX) - 1;
                //!!!TEMPORAL!!!
                //mvprintw(yMax - 1, xMax - 9, "%d", removedIndex);
                //refresh();
                bool isEnter = false;
                if (removedIndex != -1)
                {
                    isEnter = lDE->removeAt(removedIndex);
                }
                if (removedIndex > 0 && lDE->getNodoAt(removedIndex - 1)->getObject()->getAsciiCode() != 10)
                {
                    posY = lDE->getNodoAt(removedIndex - 1)->getObject()->getPosY();
                    posX = lDE->getNodoAt(removedIndex - 1)->getObject()->getPosX();
                    posX++;
                }
                else if (removedIndex > 0 && lDE->getNodoAt(removedIndex - 1)->getObject()->getAsciiCode() == 10)
                {
                    posY = lDE->getNodoAt(removedIndex - 1)->getObject()->getPosY();
                    posX = 0;
                    posY++;
                }
                else if (removedIndex == 0)
                {
                    posX = 0;
                    posY = 0;
                }
                if (isEnter)
                {
                    rowMax--;
                }
                ctrlY->cleanPila();
                //Este no deberia de ir aqui, pero para evitar errores en la ejecucion...
                ctrlZ->cleanPila();
                //Se deja vacio workSpace
                werase(workSpace);
                //Se obtiene el nodo cabeza
                Nodo *nodoaux = lDE->getNodoAt(0);
                //Reimpresion de todos los caracteres que le siguen al nodo cabeza
                while (nodoaux != 0)
                {
                    //Se obtiene el objeto letra
                    Letra *letrita = nodoaux->getObject();
                    //se agrega el caracter a la ventana
                    mvwaddch(workSpace, letrita->getPosY(), letrita->getPosX(), letrita->getAsciiCode());
                    //se refresca la ventana mostrando el caracter que se le agrego
                    nodoaux = nodoaux->getNextNodo();
                }
                wrefresh(workSpace);
            }
            //Para hacer un mega refresh de todos los datos agregados al texto (just in case)
            //Presionar Ctrl+q
            else if (tecla == 17)
            {
                //Se deja vacio workSpace
                werase(workSpace);
                //Se obtiene el nodo que fue recien ingresado
                Nodo *nodoaux = lDE->getNodoAt(0);
                //Reimpresion de todos los caracteres que le siguen al nodo de la letra ingresada
                while (nodoaux != 0)
                {
                    //Se obtiene el objeto letra
                    Letra *letrita = nodoaux->getObject();
                    //se agrega el caracter a la ventana
                    mvwaddch(workSpace, letrita->getPosY(), letrita->getPosX(), letrita->getAsciiCode());
                    //se refresca la ventana mostrando el caracter que se le agrego
                    nodoaux = nodoaux->getNextNodo();
                }
                wrefresh(workSpace);
            }
            //Si es Ctrl+w (buscar y reemplazar)
            else if (tecla == 23)
            {
                //Muestra texto para indicar que se debe insertar informacion.
                mvprintw(1, startX, "Buscar y reemplazar: ");
                //Se crea string que contendra los datos para la busqueda.
                string entrada = "";
                int ascii = 0;
                //Espera que se inserte la info a buscar y a reemplazar
                //hasta que encuentre un enter y proceda a hacer la busqueda.
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
                        entrada.append(1u, newChar);
                        //Imprimiendo en pantalla.
                        mvprintw(1, startX + 21, entrada.c_str());
                    }
                } while (ascii != 10);
                //Empieza la busqueda.
                try
                {
                    //Separa los parametros.
                    string delimiter = ";";
                    string tokenFind = entrada.substr(0, entrada.find(delimiter));
                    string tokenReplace = entrada.substr(entrada.find(delimiter) + 1, entrada.length() - 1);
                    if (tokenFind.length() != 0 && tokenReplace.length() != 0)
                    {
                        //para llevar indexacion en 0
                        int tokenFindMax = tokenFind.length() - 1;
                        //char charToFind = tokenFind.at(0);
                        int asciiToFind = (int)tokenFind.at(0);
                        Nodo *nodoaux = lDE->getNodoAt(0);
                        int count = 0;
                        //Verifica si se encontro alguna coincidencia entre la palabra buscada y el texto.
                        bool matchedWord = false;
                        //Empieza a recorrer los nodos de la lista con los caracteres
                        while (nodoaux != 0)
                        {
                            //si encuentra un nodo en donde coincide la primera letra de la palabra buscada
                            if (nodoaux->getObject()->getAsciiCode() == asciiToFind)
                            {
                                //activa verificador
                                matchedWord = true;
                                //indica cuántos nodos serán reemplazados.
                                int i = 1;
                                //si la palabra contiene mas de un caracter
                                //recorre los caracteres de la palabra buscada
                                for (i; i <= tokenFindMax; i++)
                                {
                                    //compara cada caracter de la palabra buscada
                                    //con el nodo en el que deberia de ir el caracter siguiente para que coincida la palabra buscada
                                    if ((int)tokenFind.at(i) == lDE->getNodoAt(count + i)->getObject()->getAsciiCode())
                                    {
                                        //permanece activado el verificador
                                        matchedWord = true;
                                    }
                                    else
                                    {
                                        //hasta que encuentre una letra que no coincida
                                        matchedWord = false;
                                    }
                                }
                                //si coincidio la busqueda
                                if (matchedWord)
                                {
                                    //indica donde empiezan los reemplazos
                                    int replacedIndex = count;
                                    int posYReplaced = lDE->getNodoAt(count)->getObject()->getPosY();
                                    int posXReplaced = lDE->getNodoAt(count)->getObject()->getPosX();
                                    //Se agrega registro a la pila ctrl+z
                                    Registro *registroCtrlZ = new Registro(count, tokenFind, tokenReplace);
                                    ctrlZ->push(registroCtrlZ);
                                    ctrlY->cleanPila();
                                    //se eliminan los elementos de la lista que estan siendo reemplazados.
                                    for (int j = 0; j < i; j++)
                                    {
                                        lDE->removeAt(replacedIndex);
                                    }
                                    //se insertan los elementos de la nueva palabra.
                                    for (int j = 0; j < tokenReplace.length(); j++)
                                    {
                                        /*  INSERTARIA CORRECTAMENTE SI Y SOLO SI LA PALABRA COMPLETA SE ENCUENTRA EN 
                                            UNA UNICA LINEA Y NO LLEGA AL BORDE DE LA PANTALLA.S
                                        */
                                        Letra *newLetra = new Letra(posYReplaced, posXReplaced + j, (int)tokenReplace.at(j));
                                        lDE->addAtSpecificIndex(newLetra, replacedIndex + j);
                                    }
                                }
                            }
                            nodoaux = nodoaux->getNextNodo();
                            count++;
                        }
                        mvprintw(1, startX, "Se reemplazo         ");
                        //Se deja vacio workSpace
                        werase(workSpace);
                        //Se obtiene el nodo que fue recien ingresado
                        Nodo *nodoX = lDE->getNodoAt(0);
                        //Reimpresion de todos los caracteres que le siguen al nodo de la letra ingresada
                        while (nodoX != 0)
                        {
                            //Se obtiene el objeto letra
                            Letra *letrita = nodoX->getObject();
                            //se agrega el caracter a la ventana
                            mvwaddch(workSpace, letrita->getPosY(), letrita->getPosX(), letrita->getAsciiCode());
                            //se refresca la ventana mostrando el caracter que se le agrego
                            nodoX = nodoX->getNextNodo();
                        }
                        wrefresh(workSpace);
                    }
                    else if (tokenFind.length() == 0)
                    {
                        throw 1;
                    }
                    else if (tokenReplace.length() == 0)
                    {
                        throw 0;
                    }
                }
                catch (exception &e)
                {
                    mvprintw(1, columnMax - 25, "No cumple con la sintaxis");
                    //mvprintw(1, columnMax - 10, e.what());
                }
                catch (int a)
                {
                    if (a == 1)
                    {
                        mvprintw(1, columnMax - 22, "No hay palabra a buscar");
                    }
                    else if (a == 0)
                    {
                        mvprintw(1, columnMax - 22, "No hay palabra a reemp");
                    }
                }
            }
            //Si es Ctrl+z (Deshacer)
            else if (tecla == 26)
            {
                //Se recupera el ultimo cambio realizado
                Registro *unDo = ctrlZ->pop();
                if (unDo != 0)
                {

                    //Si es una palabra completa (se revisa que el atributo Letrita este vacio
                    //para asi saber si necesitamos reemplazar una palabra)
                    if (unDo->getLetrita() == 0)
                    {
                        //Se recupera la palabra que fue reemplazada
                        string wordToFind = unDo->getWordToReplace();
                        int posYReplaced = lDE->getNodoAt(unDo->getIndex())->getObject()->getPosY();
                        int posXReplaced = lDE->getNodoAt(unDo->getIndex())->getObject()->getPosX();
                        //Se recupera la palabra que fue encontrada para reemplazar
                        string wordToReplace = unDo->getWordToFind();
                        //Para revertir el cambio se realiza lo mismo que en buscar y reemplazar.
                        //se eliminan los elementos de la lista que estan siendo reemplazados.
                        for (int i = 0; i < wordToFind.length(); i++)
                        {
                            lDE->removeAt(unDo->getIndex());
                        }
                        //se insertan los elementos de la nueva palabra.
                        for (int j = 0; j < wordToReplace.length(); j++)
                        {
                            /*  INSERTARIA CORRECTAMENTE SI Y SOLO SI LA PALABRA COMPLETA SE ENCUENTRA EN 
                                UNA UNICA LINEA Y NO LLEGA AL BORDE DE LA PANTALLA.S
                            */
                            Letra *newLetra = new Letra(posYReplaced, posXReplaced + j, (int)wordToReplace.at(j));
                            lDE->addAtSpecificIndex(newLetra, unDo->getIndex() + j);
                        }
                    }
                    else if (unDo->getLetrita() != 0)
                    {
                        //Al ser una sola letra es como borrar unicamente ese caracter.
                        Letra *letraToFind = unDo->getLetrita();
                        int removedIndex = unDo->getIndex();
                        bool isEnter = false;
                        if (removedIndex != -1)
                        {
                            isEnter = lDE->removeAt(removedIndex);
                        }
                        if (removedIndex > 0 && lDE->getNodoAt(removedIndex - 1)->getObject()->getAsciiCode() != 10)
                        {
                            posY = lDE->getNodoAt(removedIndex - 1)->getObject()->getPosY();
                            posX = lDE->getNodoAt(removedIndex - 1)->getObject()->getPosX();
                            posX++;
                        }
                        else if (removedIndex > 0 && lDE->getNodoAt(removedIndex - 1)->getObject()->getAsciiCode() == 10)
                        {
                            posY = lDE->getNodoAt(removedIndex - 1)->getObject()->getPosY();
                            posX = 0;
                            posY++;
                        }
                        else if (removedIndex == 0)
                        {
                            posX = 0;
                            posY = 0;
                        }
                        if (isEnter)
                        {
                            rowMax--;
                        }
                    }
                    //Se agrega registro a la pila Ctrl+Y
                    unDo->setEstado(true);
                    ctrlY->push(unDo);
                    //Se deja vacio workSpace
                    werase(workSpace);
                    //Se obtiene el nodo que fue recien ingresado
                    Nodo *nodoX = lDE->getNodoAt(0);
                    //Reimpresion de todos los caracteres que le siguen al nodo de la letra ingresada
                    while (nodoX != 0)
                    {
                        //Se obtiene el objeto letra
                        Letra *letrita = nodoX->getObject();
                        //se agrega el caracter a la ventana
                        mvwaddch(workSpace, letrita->getPosY(), letrita->getPosX(), letrita->getAsciiCode());
                        //se refresca la ventana mostrando el caracter que se le agrego
                        nodoX = nodoX->getNextNodo();
                    }
                    wrefresh(workSpace);
                }
            }
            //Si es ctrl+Y (rehacer)
            else if (tecla == 25)
            {
                //Se recupera el ultimo cambio deshecho
                Registro *reDo = ctrlY->pop();
                if (reDo != 0)
                {
                    //Si es una palabra completa (se revisa que el atributo Letrita este vacio
                    //para asi saber si necesitamos reemplazar una palabra)
                    if (reDo->getLetrita() == 0)
                    {
                        //Se recupera la palabra que fue reemplazada
                        string wordToFind = reDo->getWordToFind();
                        int posYReplaced = lDE->getNodoAt(reDo->getIndex())->getObject()->getPosY();
                        int posXReplaced = lDE->getNodoAt(reDo->getIndex())->getObject()->getPosX();
                        //Se recupera la palabra que fue encontrada para reemplazar
                        string wordToReplace = reDo->getWordToReplace();
                        //Para revertir el cambio se realiza lo mismo que en buscar y reemplazar.
                        //se eliminan los elementos de la lista que estan siendo reemplazados.
                        for (int i = 0; i < wordToFind.length(); i++)
                        {
                            lDE->removeAt(reDo->getIndex());
                        }
                        //se insertan los elementos de la nueva palabra.
                        for (int j = 0; j < wordToReplace.length(); j++)
                        {
                            /*  INSERTARIA CORRECTAMENTE SI Y SOLO SI LA PALABRA COMPLETA SE ENCUENTRA EN 
                                UNA UNICA LINEA Y NO LLEGA AL BORDE DE LA PANTALLA.S
                            */
                            Letra *newLetra = new Letra(posYReplaced, posXReplaced + j, (int)wordToReplace.at(j));
                            lDE->addAtSpecificIndex(newLetra, reDo->getIndex() + j);
                        }
                    }
                    else if (reDo->getLetrita() != 0)
                    {
                        Letra *letraToFind = reDo->getLetrita();
                        lDE->add(letraToFind);
                    }
                    //Se agrega registro a la pila Ctrl+Y
                    reDo->setEstado(false);
                    ctrlZ->push(reDo);
                    //Se deja vacio workSpace
                    werase(workSpace);
                    //Se obtiene el nodo que fue recien ingresado
                    Nodo *nodoX = lDE->getNodoAt(0);
                    //Reimpresion de todos los caracteres que le siguen al nodo de la letra ingresada
                    while (nodoX != 0)
                    {
                        //Se obtiene el objeto letra
                        Letra *letrita = nodoX->getObject();
                        //se agrega el caracter a la ventana
                        mvwaddch(workSpace, letrita->getPosY(), letrita->getPosX(), letrita->getAsciiCode());
                        //se refresca la ventana mostrando el caracter que se le agrego
                        nodoX = nodoX->getNextNodo();
                    }
                    wrefresh(workSpace);
                }
            }
            //Guardar (Ctrl+S)
            else if (tecla == 19)
            {
                //Muestra texto para indicar que se debe insertar informacion.
                mvprintw(1, startX, "Para guardar coloque nombre archivo: ");
                //Se crea string que contendra los datos para la busqueda.
                string nombre = "";
                int ascii = 0;
                //Espera que se inserte la info a buscar y a reemplazar
                //hasta que encuentre un enter y proceda a hacer la busqueda.
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
                        mvprintw(1, startX + 37, nombre.c_str());
                    }
                } while (ascii != 10);
                try
                {
                    //Se crea objeto de clase ifstream
                    ofstream file;
                    string path = "";
                    path.append(nombre);
                    path.append(".txt");
                    file.open(path.c_str());
                    Nodo *nodoX = lDE->getNodoAt(0);

                    //Salida de todos los caracteres que le siguen al nodo de la primer letra
                    string textoSalida = "";
                    while (nodoX != 0)
                    {
                        //Se obtiene el objeto letra
                        Letra *letrita = nodoX->getObject();
                        //se agrega el caracter al texto
                        int ascii = letrita->getAsciiCode();
                        char c = (char)ascii;
                        textoSalida.append(1u, c);
                        nodoX = nodoX->getNextNodo();
                    }
                    //Se escribe dentro del archivo
                    file << textoSalida;
                    file.close();
                    string msg = "Archivo guardado en: ";
                    msg.append(path);
                    Archivo *newArchivo = new Archivo(path, path);
                    listaArchivos->addLast(newArchivo);
                    mvprintw(1, startX, msg.c_str());
                }
                catch (exception &e)
                {
                    mvprintw(1, startX, "No se pudo guardar el archivo");
                }
            }
            //Reportes (Ctrl+C)
            else if (tecla == 3)
            {
                //Se muestran las opciones y se pide que ingrese un numero.
                mvprintw(1, startX, "Reportes: 1)Lista  2)PalabrasBuscadas  3)PalabrasOrdenadas");
                int opcion = getch();
                //Selecciona Lista
                if (opcion == 49)
                {
                    ofstream file;
                    file.open("Lista.dot");
                    string graphviz = "digraph ReporteLista{ node [shape=record fontname=Arial];\n";
                    graphviz.append("var0 [shape=none label=\"null\"];\n");
                    int i = 1;
                    for (i; i <= lDE->getSize(); i++)
                    {
                        //graphviz.append("vari -> vari-1;\n");
                        stringstream ss1;
                        ss1 << i;
                        string s1;
                        ss1 >> s1;
                        int i2 = i - 1;
                        stringstream ss2;
                        ss2 << i2;
                        string s2;
                        ss2 >> s2;
                        graphviz.append("var");
                        graphviz.append(s1);
                        graphviz.append(" -> var");
                        graphviz.append(s2);
                        graphviz.append(";\n");
                        //graphviz.append("vari [shape=record label="H"];");
                        graphviz.append("var");
                        graphviz.append(s1);
                        graphviz.append(" [label=\"");
                        char letra = lDE->getNodoAt(i - 1)->getObject()->getCharacter();
                        graphviz.append(1u, letra);
                        graphviz.append("\"];\n");
                        //vari -> vari+1;
                        int i3 = i + 1;
                        stringstream ss3;
                        ss3 << i3;
                        string s3;
                        ss3 >> s3;
                        graphviz.append("var");
                        graphviz.append(s1);
                        graphviz.append(" -> var");
                        graphviz.append(s3);
                        graphviz.append(";\n");
                    }
                    stringstream ss;
                    ss << i;
                    string s;
                    ss >> s;
                    //var3 [shape=none label="null"];
                    graphviz.append("var");
                    graphviz.append(s);
                    graphviz.append(" [shape=none label=\"null\"];\n");
                    graphviz.append("}");
                    file << graphviz;
                    file.close();
                }
                //Selecciona PalabrasBuscadas
                else if (opcion == 50)
                {
                    ofstream file;
                    file.open("LogCambios.dot");
                    string graphviz = "digraph Pilas{\nnode [shape=record fontname=Arial];\n";
                    int i = 0;
                    Registro *regZ = ctrlZ->pop();
                    while (regZ != 0)
                    {
                        stringstream ss1;
                        ss1 << i;
                        string s1;
                        ss1 >> s1;
                        graphviz.append("var");
                        graphviz.append(s1);
                        if (regZ->getLetrita() == 0)
                        {
                            graphviz.append(" [label=\"Palabra Buscada: ");
                            graphviz.append(regZ->getWordToFind());
                            graphviz.append("\\lReemplazada por: ");
                            graphviz.append(regZ->getWordToReplace());
                            graphviz.append("\\lEstado: No revertido\\lPalabra: null\\lPosicion:null\\l\"];\n");
                        }
                        else if (regZ->getLetrita() != 0)
                        {
                            graphviz.append(" [label=\"Palabra Buscada: null\\lReemplazada por: null\\lEstado: No revertido\\lPalabra: ");
                            graphviz.append(1u, regZ->getLetrita()->getCharacter());
                            graphviz.append("\\lPosicion:null\\l\"];\n");
                        }
                        i++;
                        regZ = ctrlZ->pop();
                    }
                    for (int j = 0; j < i; j++)
                    {
                        graphviz.append("var");
                        stringstream ss2;
                        ss2 << j;
                        string s2;
                        ss2 >> s2;
                        graphviz.append(s2);
                        if (j != i - 1)
                        {
                            graphviz.append(" -> ");
                        }
                    }
                    graphviz.append("\n");
                    i = 0;
                    Registro *regY = ctrlY->pop();
                    while (regY != 0)
                    {
                        stringstream ss1;
                        ss1 << i;
                        string s1;
                        ss1 >> s1;
                        graphviz.append("vary");
                        graphviz.append(s1);
                        if (regY->getLetrita() == 0)
                        {
                            graphviz.append(" [label=\"Palabra Buscada: ");
                            graphviz.append(regY->getWordToFind());
                            graphviz.append("\\lReemplazada por: ");
                            graphviz.append(regY->getWordToReplace());
                            graphviz.append("\\lEstado: Revertido\\lPalabra: null\\lPosicion:null\\l\"];\n");
                        }
                        else if (regY->getLetrita() != 0)
                        {
                            graphviz.append(" [label=\"Palabra Buscada: null\\lReemplazada por: null\\lEstado: Revertido\\lPalabra: ");
                            graphviz.append(1u, regY->getLetrita()->getCharacter());
                            graphviz.append("\\lPosicion:null\\l\"];\n");
                        }
                        i++;
                        regY = ctrlY->pop();
                    }
                    for (int j = 0; j < i; j++)
                    {
                        graphviz.append("vary");
                        stringstream ss2;
                        ss2 << j;
                        string s2;
                        ss2 >> s2;
                        graphviz.append(s2);
                        if (j != i - 1)
                        {
                            graphviz.append(" -> ");
                        }
                    }
                    graphviz.append("\n}\n");
                    file << graphviz;
                    file.close();
                }
                //Selecciona PalabrasOrdenadas
                else if (opcion == 51)
                {
                }
            }

            //Mueve el cursor para que se coloque un nuevo caracter en esa posicion.
            wmove(workSpace, posY, posX);

            //!!!TEMPORAL!!!
            mvprintw(0, xMax - 10, "%d %d %d", tecla, posY, posX);
            refresh();

        } while (tecla != 24);
        wprintw(frameBorder, "sale del ciclo");
        wrefresh(frameBorder);

        getch();
        endwin();
        /* TERMINA PDCURSES */
        Reciente rec(listaArchivos);
        //Inicio newInicio(listaArchivos);
    }
    ~Crear()
    {
    }
};
#endif // CREAR_H