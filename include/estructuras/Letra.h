#ifndef LETRA_H
#define LETRA_H
class Letra
{
private:
    int posY, posX, asciiCode;
    char character;

public:
    Letra()
    {
        posY = -1;
        posX = -1;
        asciiCode = -1;
        character = ' ';
    }
    Letra(int posY, int posX, int asciiCode)
    {
        this->posY = posY;
        this->posX = posX;
        this->asciiCode = asciiCode;
        this->character = (char)asciiCode;
    }
    int getPosY()
    {
        return this->posY;
    }
    int getPosX()
    {
        return this->posX;
    }
    int getAsciiCode()
    {
        return this->asciiCode;
    }
    char getCharacter()
    {
        return this->character;
    }
    void setPosX(int posX)
    {
        this->posX = posX;
    }
    void setPosY(int posY)
    {
        this->posY = posY;
    }
    int increaseX(int columnMax)
    {
        //si se esta corriendo un enter
        if (this->asciiCode == 10)
        {
            //si se corre hacia el final de una linea
            if (posX == columnMax - 1)
            {
                posX = 0;
                posY++;
                //ENVIAR PARAMETRO EN DONDE AUMENTA LA POSY A TODOS LOS NODOS SIGUIENTES
                //Realiza el otro metodo para aumentar posY a todos los demas nodos
                return 2;
            }
            //se corre el enter
            else
            {
                this->posX++;
                //ROMPE EL CICLO
                return 0;
            }
        }
        else
        {
            //si esta al final de la linea
            if (posX == columnMax - 1)
            {
                posX = 0;
                posY++;
            }
            //si no esta al final de la linea
            else
            {
                this->posX++;
            }
            //Para que continue
            return 1;
        }
    }
    void increaseY()
    {
        posY++;
    }
    void decreaseY()
    {
        if (posY != 0)
        {
            posY--;
        }
    }
    int decreaseX(int columnMax)
    {
        //Si se esta corriendo un enter
        if (this->asciiCode == 10)
        {
            //si se encuentra al principio YA
            if (posX == 0 && posY != 0)
            {
                posX = columnMax - 1;
                posY--;
                //Realiza el otro metodo para disminuir posY a todos los demas nodos
                return 2;
            }
            //Se corre el enter YA
            else
            {
                this->posX--;
                //rompe ciclo YA
                return 0;
            }
        }
        else
        {
            //Si esta al principio Ya
            if (posX == 0)
            {
                posX = columnMax - 1;
                if (posY != 0)
                {
                    posY--;
                }
            }
            //Si no esta al principio YA
            else
            {
                this->posX--;
            }
            //Para que prosiga
            return 1;
        }
    }
};
#endif // LETRA_H