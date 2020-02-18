#ifndef PERSONA_H
#define PERSONA_H
#include <string>
using namespace std;

class Persona
{
public:
    Persona()
    {
        edad = 0;
        nombre = "";
        cout << "no indica edad" << endl;
        cout << "no indica nombre" << endl;
    }

    Persona(int e, string n)
    {
        edad = e;
        nombre = n;
        cout << edad << endl;
        cout << nombre << endl;
    }

    ~Persona()
    {
        //dtor
    }

    //protected:

private:
    int edad;
    string nombre;
};

#endif // PERSONA_H
