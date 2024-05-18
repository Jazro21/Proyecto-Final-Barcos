// Integrantes
// Deymar Andrés Ampudia Rivas
// Rodrigo Arturo Pérez Angulo

// notas adicionales del Ing. Ampudia para el Lic. Perez
// este es un archivo a parte del que usted hizo.
// no lo queria modificar por si nesecitaba algo de dicho codigo

// este es le codigo base (no funciona). Solo tiene la opcion de registar embarcacion
// todos los metodos implementados los hice guiandome del codigo AVL del profesor

#include <iostream>
#include <string.h>
#include <malloc.h>
using namespace std;

struct Barcos
{
    char NomEmbarcacion[20];
    int Precio = 0;
    char Destino[20];
    int Capacidad = 0;

    char Identificador[10];
    char Matricula[2];
    char Dia[2];
    char Mes[2];
    char Año[4];

    Barcos *izq;
    Barcos *der;

    int altura = 0;
};

Barcos *raiz = NULL;
Barcos *aux = NULL;

int RegistrarEmbarcacion()
{
    aux = (struct Barcos *)malloc(sizeof(struct Barcos));

    cout << "ingrese el nombre de la embarcacion: ";
    cin >> aux->NomEmbarcacion;

    cout << "ingrese el destino del viaje: ";
    cin >> aux->Destino;

    cout << "Ingrese el precio del viaje: $";
    cin >> aux->Precio;

    cout << "Ingrese la matricula de la embarcacion (solo dos caracteres): ";
    cin >> aux->Matricula;

    cout << "Ingrese el dia del viaje: ";
    cin >> aux->Dia;

    cout << "Ingrese el mes del viaje: ";
    cin >> aux->Mes;

    cout << "Ingrese el año del viaje: ";
    cin >> aux->Año;

    cout << "Ingrese la capacidad de la embarcacion (numero de personas): ";
    cin >> aux->Capacidad;

    strcat(aux->Identificador, aux->Matricula);
    strcat(aux->Identificador, aux->Año);
    strcat(aux->Identificador, aux->Mes);
    strcat(aux->Identificador, aux->Dia);

    aux->izq = NULL;
    aux->der = NULL;

    aux->altura = 1;
    return 0;
}
int ObtenerAltura(struct Barcos *sub1)
{
    if (sub1 == NULL)
    {
        return 0;
    }
    return sub1->altura;
}

int mayor(int sub2, int sub3)
{
    return (sub2 > sub3) ? sub2 : sub3;
}

struct Barcos *RotarDerecha(struct Barcos *suby)
{
    struct Barcos *subx = suby->izq;
    struct Barcos *sub4 = subx->der;

    subx->der = suby;
    suby->izq = sub4;

    suby->altura = mayor(ObtenerAltura(suby->izq), ObtenerAltura(suby->der)) + 1;
    subx->altura = mayor(ObtenerAltura(subx->izq), ObtenerAltura(subx->der)) + 1;

    return subx;
}

struct Barcos *RotarIzquierda(struct Barcos *subx)
{
    struct Barcos *suby = subx->der;
    struct Barcos *sub4 = suby->izq;

    suby->der = subx;
    subx->izq = sub4;

    subx->altura = mayor(ObtenerAltura(subx->izq), ObtenerAltura(subx->der)) + 1;
    suby->altura = mayor(ObtenerAltura(suby->izq), ObtenerAltura(suby->der)) + 1;

    return suby;
}

int ObtenerBalance(struct Barcos *sub5)
{
    if (sub5 == NULL)
    {
        return 0;
    }
    return ObtenerAltura(sub5->izq) - ObtenerAltura(sub5->der);
}

struct Barcos *insertar(struct Barcos *posicion)
{
    if (posicion == NULL)
    {
        return aux;
    }
    if (aux->Identificador < posicion->Identificador)
    {
        posicion->izq = insertar(posicion->izq);
    }
    else if (aux->Identificador > posicion->Identificador)
    {
        posicion->der = insertar(posicion->der);
    }
    else
    {
        return posicion;
    }

    posicion->altura = 1 + mayor(ObtenerAltura(posicion->izq), ObtenerAltura(posicion->der));

    int balance = ObtenerBalance(posicion);

    if (balance > 1 && aux->Identificador < posicion->izq->Identificador)
    {
        return RotarDerecha(posicion);
    }

    if (balance < -1 && aux->Identificador > posicion->der->Identificador)
    {
        return RotarIzquierda(posicion);
    }

    if (balance > 1 && aux->Identificador > posicion->izq->Identificador)
    {
        posicion->izq = RotarIzquierda(posicion->izq);
        return RotarDerecha(posicion);
    }

    if (balance < -1 && aux->Identificador < posicion->der->Identificador)
    {
        posicion->der = RotarDerecha(posicion->der);
        return RotarIzquierda(posicion);
    }

    return posicion;
}

int InOrden(struct Barcos *sub)
{

    if (sub->izq != NULL)
    {
        InOrden(sub->izq);
    }

    cout << "Nombre de la embarcacion: " << sub->NomEmbarcacion << endl;
    cout << "Destino del viaje: " << sub->Destino << endl;
    cout << "Precio del viaje: $" << sub->Precio << endl;
    cout << "Matricula: " << sub->Matricula << endl;
    cout << "Fecha de salida: " << sub->Dia << "/" << sub->Mes << "/" << sub->Año << endl;
    cout << "Numero de pasajeros: " << sub->Capacidad << endl;
    cout << "Identificador: " << sub->Identificador << endl;

    if (sub->der != NULL)
    {
        InOrden(sub->der);
    }
    return 0;
}

int main()
{
    raiz = NULL;
    int opcion = 0;

    do
    {
        cout << "Menu de opciones" << endl;
        cout << "1. Registrar embarcacion" << endl;
        cout << "2. Mostrar embarcaciones" << endl;
        cout << "7. Salir" << endl;
        cin >> opcion;
        switch (opcion)
        {
        case 1:
            RegistrarEmbarcacion();
            raiz = insertar(raiz);
            break;
        case 2:
            cout << "Recorrido de las embarcaciones (InOrden): ";
            InOrden(raiz);
            cout << endl;
            break;
        }
    } while (opcion != 7);
    return 0;
}