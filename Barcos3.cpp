// Integrantes
// Deymar Andrés Ampudia Rivas
// Rodrigo Arturo Pérez Angulo

// notas adicionales del Ing. Ampudia para el Lic. Perez
// este es un archivo a parte del que usted hizo.
// no lo queria modificar por si nesecitaba algo de dicho codigo

// este es le codigo base (no funciona). Solo tiene la opcion de registar embarcacion
// todos los metodos implementados los hice guiandome del codigo AVL del profesor

// notas de actualizacion
// se implemento el metodo InOrden
// Se arreglo el problema en el registro. al parecer, funciona correctamente

//Notas adicionales del Lic. Pérez al Ing. Ampudia
//Este archivo es independiente de los otros 2, para rsolver problemasde registrarPasajeros y listarPasajeros
//Cree de manera temporal las opciones registrarPasajeros y ListarPasajeros
//En registrarPasajeros hay un problema, en un principio encontraba el barco deseado y permitia registrar un pasajero sin problemas, pero por alguna razon al registrar un segundo pasajero, me termina saltando el mensaje de que el viaje no tiene cupos
//Por otro lado, aunque ingreso la matricula/identificador (Los usé para probar), a veces ni siquiera encuentra el viaje y vuelve al menu principal
//ListarPasajeros no se si funciona correctamente, digo, lo probé y parece que no daba problemas, pero lo intenté de nuevo y no funcionó como lo esperado.
//Solicíto su pronta ayuda para solucionar estos problemas


// Nota extra
// Por alguna razon, el IUV (Identificador Unico de Viaje), se bugueaba y no permitía su busqueda en registrarPasajeros y listarPasajeros

#include <iostream>
#include <string.h>
#include <malloc.h>
using namespace std;

struct Barcos
{
    char NomEmbarcacion[50];
    int Precio = 0;
    char Destino[30];
    int Capacidad = 0;

    char Identificador[20];
    char Matricula[10];
    char Dia[10];
    char Mes[10];
    char Año[10];

    char NomPasajero[10];
    char ApellidoPasajero[10];
    int ID = 0;

    int acumulador = 0;

    Barcos *sig;
    Barcos *izq;
    Barcos *der;

    int altura = 0;
};

Barcos *raiz = NULL;
Barcos *cab = NULL;
Barcos *aux = NULL;
Barcos *aux2 = NULL;

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
    cout << "------------------------------------------------" << endl;

    if (sub->der != NULL)
    {
        InOrden(sub->der);
    }
    return 0;
}

char bucadorBarco[20];

int buscarEmbarcacion()
{
    aux = raiz;

    if (aux == NULL)
    {
        cout << "No hay embarcaciones registradas" << endl;
        return 0;
    }
    if (aux != NULL)
    {
        cout << "Ingrese el identificador de la embarcacion: ";
        cin >> bucadorBarco;

        if (aux->Identificador == bucadorBarco)
        {
            cout << "Nombre de la embarcacion: " << aux->NomEmbarcacion << endl;
            cout << "Destino del viaje: " << aux->Destino << endl;
            cout << "Precio del viaje: $" << aux->Precio << endl;
            cout << "Matricula: " << aux->Matricula << endl;
            cout << "Fecha de salida: " << aux->Dia << "/" << aux->Mes << "/" << aux->Año << endl;
            cout << "Numero de pasajeros: " << aux->Capacidad << endl;
            cout << "Identificador: " << aux->Identificador << endl;
            cout << "------------------------------------------------" << endl;
        }
        if (aux->Identificador != bucadorBarco)
        {
            if (bucadorBarco > aux->Identificador)
            {
                if (aux->der != NULL)
                {
                    aux = aux->der;
                    buscarEmbarcacion();
                }
            }
            if (bucadorBarco < aux->Identificador)
            {
                if (aux->izq != NULL)
                {
                    aux = aux->izq;
                    buscarEmbarcacion();
                }
            }
        }
    }
    return 0;
}

char buscadorBarco[20]; 

int registrarPasajeros()
{
    aux = raiz;
    if (aux != NULL)
    {
        cout << "Ingrese la matricula de la embarcacion: ";
        cin >> buscadorBarco;

        if (aux->acumulador == aux->Capacidad)
        {
            cout << "La embarcacion ya esta llena. Intente registrar el pasajero en otro viaje." << endl;
            return 0;
        }
        else
        {
            if (aux->Matricula == buscadorBarco)
            {
                if (cab == NULL)
                {
                    cab = (struct Barcos *)malloc(sizeof(struct Barcos));

                    cout << "ingrese el Nombre del Pasajero: ";
                    cin >> cab->NomPasajero;

                    cout << "ingrese el Apellido del Pasajero: ";
                    cin >> cab->ApellidoPasajero;

                    cout << "ingrese el ID del Pasajero: ";
                    cin >> cab->ID;

                    cab->sig = NULL;
                    free(aux);
                }
                else
                {
                    aux = (struct Barcos *)malloc(sizeof(struct Barcos));

                    cout << "ingrese el Nombre del Pasajero: ";
                    cin >> aux->NomPasajero;

                    cout << "ingrese el Apellido del Pasajero: ";
                    cin >> aux->ApellidoPasajero;

                    cout << "ingrese el ID del Pasajero: ";
                    cin >> aux->ID;

                    aux->sig = NULL;
                    aux2 = cab;

                    while (aux2->sig != NULL)
                    {
                        aux2 = aux2->sig;
                    }

                    aux->acumulador = aux2->acumulador + 1;

                    aux2->sig = aux;
                    aux = NULL;

                    aux2 = aux;
                    free(aux);
                    free(aux2);
                }
            }
        }
    }
    return 0;
}

int listarPasajeros(){
        aux = raiz;

        if (aux == NULL)
        {
            cout << "No hay viajes registradas" << endl;
            return 0;
        }
  
        if (aux != NULL)
        {
            cout << "Ingrese el identificador de la embarcacion: ";
            cin >> bucadorBarco;

            if (aux->Matricula == bucadorBarco)
            {

                for(aux=cab; aux != NULL; aux = aux->sig){
                cout << "Nombre del pasajero: " << aux->NomPasajero << endl;
                cout << "Apellido del pasajero: " << aux->ApellidoPasajero << endl;
                cout << "ID del Pasajero: $" << aux->ID << endl;
                cout << "------------------------------------------------" << endl;
            }
              }
            if (aux->Matricula != bucadorBarco)
            {
                if (bucadorBarco > aux->Matricula)
                {
                    if (aux->der != NULL)
                    {
                        aux = aux->der;
                        buscarEmbarcacion();
                    }
                }
                if (bucadorBarco < aux->Matricula)
                {
                    if (aux->izq != NULL)
                    {
                        aux = aux->izq;
                        buscarEmbarcacion();
                    }
                }
            }
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
        cout << "3. Buscar embarcacion" << endl;
        cout << "7. Salir" << endl;
        cin >> opcion;
        switch (opcion)
        {
        case 1:
            RegistrarEmbarcacion();
            raiz = insertar(raiz);
            break;
        case 2:
            cout << "------------embarcacion registrada------------" << endl;
            InOrden(raiz);
            cout << endl;
            break;
        case 3:
        buscarEmbarcacion();
        break;
    } while (opcion != 7);
    return 0;
}
