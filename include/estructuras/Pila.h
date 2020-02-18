#include <string.h>
#include "Letra.h"
using namespace std;
class Registro
{
private:
    int index;
    string wordToFind, wordToReplace;
    Letra *letrita;
    bool estadoRevertido;

public:
    Registro()
    {
        index = -1;
        wordToFind = "";
        wordToReplace = "";
    }
    Registro(int index, string wordToFind, string wordToReplace)
    {
        this->index = index;
        this->letrita = 0;
        this->wordToFind = wordToFind;
        this->wordToReplace = wordToReplace;
        this->estadoRevertido = false;
    }
    Registro(int index, Letra *letrita)
    {
        this->index = index;
        this->letrita = letrita;
        this->wordToFind = "";
        this->wordToReplace = "";
        this->estadoRevertido = false;
    }
    int getIndex()
    {
        return this->index;
    }
    string getWordToFind()
    {
        return this->wordToFind;
    }
    string getWordToReplace()
    {
        return this->wordToReplace;
    }
    Letra *getLetrita()
    {
        return this->letrita;
    }
    void setEstado(bool estado)
    {
        this->estadoRevertido = estado;
    }
};

class NodoP
{
private:
    Registro *object;
    NodoP *prevNodo;
    NodoP *nextNodo;

public:
    NodoP()
    {
        this->object = new Registro();
        prevNodo = 0;
        nextNodo = 0;
    }
    NodoP(Registro *object)
    {
        this->object = object;
        nextNodo = 0;
        prevNodo = 0;
    }
    ~NodoP()
    {
    }
    void setObject(Registro *c)
    {
        object = c;
    }
    Registro *getObject()
    {
        return this->object;
    }
    NodoP *getPrevNodo()
    {
        return this->prevNodo;
    }
    NodoP *getNextNodo()
    {
        return this->nextNodo;
    }
    void setPrevNodo(NodoP *prevNodo)
    {
        this->prevNodo = prevNodo;
    }
    void setNextNodo(NodoP *nextNodo)
    {
        this->nextNodo = nextNodo;
    }
};
#ifndef PILA_H
#define PILA_H
class Pila
{
private:
    int size;
    NodoP *headNodo;

public:
    Pila()
    {
        size = 0;
        headNodo = 0;
    }
    bool isEmpty() { return size == 0; }
    int getSize() { return size; }

    void push(Registro *data)
    {
        NodoP *newNodo = new NodoP(data);
        if (this->isEmpty())
        {
            this->headNodo = newNodo;
            this->size++;
        }
        else
        {
            //A newNodo se le asigna headNodo como su nextNodo
            newNodo->setNextNodo(headNodo);
            //A la pila se le asigna su nuevo headNodo
            this->headNodo = newNodo;
            this->size++;
        }
    }

    Registro *pop()
    {
        //Valida que la lista no este vacia
        if (this->headNodo != 0)
        {
            Registro *headRegistro = this->headNodo->getObject();
            //Validacion para que si se desea eliminar el primero y el tamaño es 1
            if (this->size == 1)
            {
                //delete firstNodo;
                headNodo = 0;
                size = 0;
                return headRegistro;
            }
            //Elimina el primero
            else if (this->size > 1)
            {
                //delete firstNodo;
                headNodo = headNodo->getNextNodo();
                this->size--;
                return headRegistro;
            }
        }
        return 0;
    }

    Registro *getHeadRegistro()
    {
        return this->headNodo->getObject();
    }
    void cleanPila()
    {
        size = 0;
        headNodo = 0;
    }
};
#endif // PILA_H
