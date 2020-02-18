//Ya no lo voy a usar
#ifndef NODO_H
#define NODO_H
template <class T>
class Nodo
{
private:
    T object;
    Nodo *prevNodo;
    Nodo *nextNodo;

public:
    Nodo()
    {
        std::cout << "Ya no sale :c" << std::endl;
        object = NULL;
        prevNodo = NULL;
        nextNodo = NULL;
    }
    ~Nodo()
    {
    }
    void setObject()
    {
    }
    T getObject()
    {
        return this.object;
    }
    Nodo getPrevNodo()
    {
        return this.prevNodo;
    }
    Nodo getNextNodo()
    {
        return this.nextNodo;
    }

protected:
    Nodo(T object)
    {
        this.object = object;
        nextNodo = NULL;
        prevNodo = NULL;
    }
    void setPrevNodo(Nodo prevNodo)
    {
        this.prevNodo = prevNodo;
    }
    void setNextNodo(Nodo nextNodo)
    {
        this.nextNodo = nextNodo;
    }
};

#endif //NODO_H