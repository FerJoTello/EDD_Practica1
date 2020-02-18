#include <string>
#include "Archivo.h"
using namespace std;
#ifndef NODOLC_H
#define NODOLC_H
class NodoLC
{
private:
    Archivo *object;
    NodoLC *prevNodo;
    NodoLC *nextNodo;

public:
    NodoLC(Archivo *object)
    {
        this->object = object;
        nextNodo = 0;
        prevNodo = 0;
    }
    ~NodoLC()
    {
    }
    void setObject(Archivo *c)
    {
        object = c;
    }
    Archivo *getObject()
    {
        return this->object;
    }
    NodoLC *getPrevNodo()
    {
        return this->prevNodo;
    }
    NodoLC *getNextNodo()
    {
        return this->nextNodo;
    }
    void setPrevNodo(NodoLC *prevNodo)
    {
        this->prevNodo = prevNodo;
    }
    void setNextNodo(NodoLC *nextNodo)
    {
        this->nextNodo = nextNodo;
    }
};
#endif //NODOLC_H
#ifndef LISTACIRCULAR_H
#define LISTACIRCULAR_H
class ListaCircular
{
private:
    NodoLC *firstNodo;
    NodoLC *lastNodo;
    int size;

public:
    ListaCircular()
    {
        firstNodo = 0;
        lastNodo = 0;
        size = 0;
    }
    bool isEmpty()
    {
        return size == 0;
    }
    void addLast(Archivo *data)
    {
        if (this->isEmpty())
        {
            NodoLC *newNodo = new NodoLC(data);
            this->firstNodo = newNodo;
            this->lastNodo = newNodo;
            size++;
        }
        else
        {
            NodoLC *newNodo = new NodoLC(data);
            this->lastNodo->setNextNodo(newNodo);
            newNodo->setNextNodo(this->firstNodo);
            this->lastNodo = newNodo;
            this->size++;
        }
    }
    Archivo *getObjectAt(int index)
    {
        if (index >= 0 && index < this->size)
        {
            NodoLC *nodoAux = this->firstNodo;
            int count = 0;
            while (nodoAux != 0)
            {
                if (index == count)
                {
                    return nodoAux->getObject();
                }
                nodoAux = nodoAux->getNextNodo();
                count++;
            }
        }
        else
        {
            return 0;
        }
    }
    int getSize(){
        return size;
    }
};
#endif //LISTACIRCULAR_H