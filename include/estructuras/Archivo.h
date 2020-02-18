#include <string>
using namespace std;
#ifndef ARCHIVO_H
#define ARCHIVO_H
class Archivo
{
private:
    string nombre, ruta;

public:
    Archivo(string nombre, string ruta)
    {
        this->nombre = nombre;
        this->ruta = ruta;
    }
    string getNombre()
    {
        return this->nombre;
    }
    string getRuta()
    {
        return this->ruta;
    }
};
#endif //ARCHIVO_H