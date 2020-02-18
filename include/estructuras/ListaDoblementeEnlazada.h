#include "Letra.h"
class Nodo
{
private:
    Letra *object;
    Nodo *prevNodo;
    Nodo *nextNodo;

public:
    Nodo()
    {
        this->object = new Letra();
        prevNodo = 0;
        nextNodo = 0;
    }
    Nodo(Letra *object)
    {
        this->object = object;
        nextNodo = 0;
        prevNodo = 0;
    }
    ~Nodo()
    {
    }
    void setObject(Letra *c)
    {
        object = c;
    }
    Letra *getObject()
    {
        return this->object;
    }
    Nodo *getPrevNodo()
    {
        return this->prevNodo;
    }
    Nodo *getNextNodo()
    {
        return this->nextNodo;
    }
    void setPrevNodo(Nodo *prevNodo)
    {
        this->prevNodo = prevNodo;
    }
    void setNextNodo(Nodo *nextNodo)
    {
        this->nextNodo = nextNodo;
    }

protected:
};
#ifndef LISTADOBLEMENTENELAZADA_H
#define LISTADOBLEMENTEENLAZADA_H
class ListaDoblementeEnlazada
{
private:
    int size, columnMax;
    Nodo *firstNodo;
    Nodo *lastNodo;
    

public:
    ListaDoblementeEnlazada(int columnMax)
    {
        this->columnMax = columnMax;
        size = 0;
        firstNodo = 0;
        lastNodo = 0;
    }
    bool isEmpty() { return size == 0; }
    int getSize() { return size; }

    void addFirst(Letra *data)
    {
        Nodo *newNodo = new Nodo(data);
        if (this->isEmpty())
        {
            this->firstNodo = newNodo;
            this->lastNodo = newNodo;
            this->size++;
        }
        else
        {
            //A newNodo se le asigna firstNodo como su nextNodo
            newNodo->setNextNodo(firstNodo);
            //A firstNodo se le asigna newNodo como su prevNodo
            this->firstNodo->setPrevNodo(newNodo);
            this->firstNodo = newNodo;
            this->size++;
            if (firstNodo->getObject()->getAsciiCode() == 10)
            {
                corrimiento(firstNodo, 3);
            }
            else
            {
                corrimiento(firstNodo, 1);
            }
        }
    }
    void addLast(Letra *data)
    {
        if (this->isEmpty())
        {
            this->addFirst(data);
        }
        else
        {
            Nodo *n = new Nodo(data);
            this->lastNodo->setNextNodo(n);
            n->setPrevNodo(this->lastNodo);
            this->lastNodo = n;
            this->size++;
        }
    }
    void addAtSpecificIndex(Letra *data, int index)
    {
        if (index >= 0 && index <= this->size)
        {
            if (index == 0)
            {
                this->addFirst(data);
            }
            else if (index == this->size)
            {
                this->addLast(data);
            }
            else
            {
                Nodo *aux = this->firstNodo;
                int x = 0;
                while (aux != 0)
                {
                    if (x == index)
                    {
                        break;
                    }
                    aux = aux->getNextNodo();
                    x++;
                }
                Nodo *n = new Nodo(data);
                aux->getPrevNodo()->setNextNodo(n);
                n->setPrevNodo(aux->getPrevNodo());
                n->setNextNodo(aux);
                aux->setPrevNodo(n);
                this->size++;
                if (n->getObject()->getAsciiCode() == 10)
                {
                    corrimiento(n, 3);
                }
                else
                {
                    corrimiento(n, 1);
                }
            }
        }
    }
    int add(Letra *data)
    {
        //posY, posX, character
        //Si esta vacia la agrega sin problema
        if (isEmpty())
        {
            addFirst(data);
            return 0;
        }
        //Si no esta vacia
        else
        {
            int count = 0;
            Nodo *aux = this->firstNodo;
            //Se recorre la lista
            while (aux != 0)
            {
                //Compara que los atributos del objeto del nodoAuxiliar (posY, posX) sean los mismos de la posicion de la Letra que se desea insertar
                if (aux->getObject()->getPosY() == data->getPosY() && aux->getObject()->getPosX() == data->getPosX())
                {
                    //Agrega la letra a la lista en donde se desea
                    addAtSpecificIndex(data, count);
                    return count;
                }
                count++;
                aux = aux->getNextNodo();
            }
            //Si no se encuentra la posicion indicada y se llego al final de la lista.
            if (count == getSize())
            {
                //Se agrega al final.
                addLast(data);
                return count;
            }
            return -1;
        }
    }

    bool removeAt(int index)
    {
        bool isEnter = false;
        //Valida que la lista no este vacia
        if (this->firstNodo != 0)
        {
            //Valida que se desee eliminar un elemento perteneciente
            if (index >= 0 && index <= this->size)
            {
                //Validacion para que si se desea eliminar el primero y el tamaño es 1
                if (index == 0 && this->size == 1)
                {
                    //delete firstNodo;
                    firstNodo = 0;
                    lastNodo = 0;
                    size = 0;
                }
                //Elimina el primero
                else if (index == 0)
                {
                    Nodo *aux = this->firstNodo->getNextNodo();
                    if (aux->getObject()->getAsciiCode() == 10)
                    {
                        regresamiento(firstNodo, 3);
                        isEnter = true;
                    }
                    else
                    {
                        regresamiento(firstNodo, 1);
                    }
                    firstNodo->setNextNodo(0);
                    //delete firstNodo;
                    firstNodo = aux;
                    firstNodo->setPrevNodo(0);
                    this->size--;
                }
                //Elimina el ultimo elemento de la lista
                else if (index == this->size - 1)
                {
                    if (lastNodo->getObject()->getAsciiCode() == 10)
                    {
                        isEnter = true;
                    }
                    Nodo *aux = this->lastNodo->getPrevNodo();
                    //delete lastNodo;
                    lastNodo = aux;
                    lastNodo->setNextNodo(0);
                    this->size--;
                }
                //Elimina un elemento que no es el ultimo ni el primero
                else if (index > 0 && index < this->size - 1)
                {
                    Nodo *aux = this->firstNodo;
                    int x = 0;
                    while (aux != 0)
                    {
                        if (x == index)
                        {
                            break;
                        }
                        aux = aux->getNextNodo();
                        x++;
                    }
                    aux->getPrevNodo()->setNextNodo(aux->getNextNodo());
                    aux->getNextNodo()->setPrevNodo(aux->getPrevNodo());

                    if (aux->getObject()->getAsciiCode() == 10)
                    {
                        regresamiento(aux, 3);
                        isEnter = true;
                    }
                    else
                    {
                        regresamiento(aux, 1);
                    }
                    aux->setNextNodo(0);
                    aux->setPrevNodo(0);
                    //delete aux;
                    size--;
                }
            }
        }
        return isEnter;
    }

    Nodo *getNodoAt(int index)
    {
        if (index >= 0 && index < this->size)
        {
            Nodo *aux = this->firstNodo;
            int x = 0;
            while (aux != 0)
            {
                if (index == x)
                {
                    return aux;
                }
                aux = aux->getNextNodo();
                x++;
            }
        }
        return 0;
    }

    int getIndexByPosition(int posY, int posX)
    {
        Nodo *aux = firstNodo;
        int count = 0;
        while (aux != 0)
        {
            if (aux->getObject()->getPosY() == posY && aux->getObject()->getPosX() == posX)
            {
                return count;
            }
            else if (aux == this->lastNodo)
            {
                count++;
                return count;
            }
            aux = aux->getNextNodo();
            count++;
        }
        return -1;
    }
    void regresamiento(Nodo *nodoBase, int status)
    {
        Nodo *aux = nodoBase->getNextNodo();
        //status=0 Rompe ciclo
        //status=1 se corren todos decreseX
        //status=2 decrementaY
        //status=3 esta siendo eliminado un enter.
        if (status == 3)
        {

            int actualColumn = nodoBase->getObject()->getPosX();
            int actualRow = nodoBase->getObject()->getPosY();
            //Se les coloca nueva posicion si se elimino un enter.
            while (aux != 0)
            {
                aux->getObject()->setPosY(actualRow);
                aux->getObject()->setPosX(actualColumn);
                actualColumn++;
                if (actualColumn == columnMax)
                {
                    actualColumn = 0;
                    actualRow++;
                }
                aux = aux->getNextNodo();
            }
        }
        while (aux != 0 && status != 0)
        {
            if (status == 1)
            {
                status = aux->getObject()->decreaseX(columnMax);
                aux = aux->getNextNodo();
            }
            else if (status == 2)
            {
                aux->getObject()->decreaseY();
                aux = aux->getNextNodo();
            }
        }
    }
    //Desplaza a la posX y la posY
    void corrimiento(Nodo *nodoBase, int status)
    {
        Nodo *aux = nodoBase->getNextNodo();
        //status=0 Rompe ciclo
        //status=1 se corren todos. incrementaX (corrimiento lateral)
        //status=2 incrementaY (corrimiento vertical)
        //status=3 Esta siendo ingresado un enter.
        if (status == 3)
        {
            //Fila del Enter que se inserto
            int enterRow = nodoBase->getObject()->getPosY();
            int actualColumn = 0;
            while (aux != 0)
            {
                if (aux->getObject()->getPosY() == enterRow)
                {
                    aux->getObject()->increaseY();
                    aux->getObject()->setPosX(actualColumn);
                    actualColumn++;
                }
                else if ((aux->getObject()->getPosY() > enterRow))
                {
                    aux->getObject()->increaseY();
                }
                aux = aux->getNextNodo();
            }
        }
        else
        {
            while (aux != 0 && status != 0)
            {
                if (status == 1)
                {
                    status = aux->getObject()->increaseX(columnMax);
                    aux = aux->getNextNodo();
                }
                else if (status == 2)
                {
                    aux->getObject()->increaseY();
                    aux = aux->getNextNodo();
                }
            }
        }
    }
};
#endif // LISTADOBLEMENTEENLAZADA_H
