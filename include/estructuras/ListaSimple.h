#include <string>
using namespace std;
class Ordenada
{
private:
    string buscada, reemplazada;

public:
    Ordenada(string buscada, string reemplazada)
    {
        this->buscada = buscada;
        this->reemplazada = reemplazada;
    }
};
class NodoL
{
private:
    Ordenada *object;
    NodoL *prevNodo;
    NodoL *nextNodo;

public:
    NodoL(Ordenada *object)
    {
        this->object = object;
        nextNodo = 0;
        prevNodo = 0;
    }
    ~NodoL()
    {
    }
    void setObject(Ordenada *c)
    {
        object = c;
    }
    Ordenada *getObject()
    {
        return this->object;
    }
    NodoL *getPrevNodo()
    {
        return this->prevNodo;
    }
    NodoL *getNextNodo()
    {
        return this->nextNodo;
    }
    void setPrevNodo(NodoL *prevNodo)
    {
        this->prevNodo = prevNodo;
    }
    void setNextNodo(NodoL *nextNodo)
    {
        this->nextNodo = nextNodo;
    }
};
class ListaSimple
{
private:
    int size;
    NodoL *headNodo, *lastNodo;

public:
    ListaSimple();
    ~ListaSimple();
};
