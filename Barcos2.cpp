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
// implementé el comando "strncpy", para que solo guarde los dos primeros digitos (exepto en año que es de 4), mientras que ignora los demas
// tambien implemente el comando "strcat", para concatenar una cadena de catarteres a otra. esto lo utilice exclusivamente para el identificador
// el metodo buscar sigue sin funcionar
// el metodo registrar pasajero siguen sin funcionar


#include <iostream>
#include <string.h>
#include <malloc.h>
#include <string>

using namespace std;

//--------------------estructura de las embarcaciones--------------------

struct Barcos
{
    char NomEmbarcacion[50];
    int Precio = 0;
    char Destino[30];
    int Capacidad = 0;

    char Identificador[20]; // el minimo son 10
    char Matricula[10];
    char Dia[5];
    char Mes[5];
    char Año[10];

    Barcos *izq = NULL;
    Barcos *der = NULL;

    int altura = 0;
};

Barcos *raiz = NULL;
Barcos *aux = NULL;

//-------------------------------------------------------------------

//--------------------estructura de los pasajeros--------------------
struct pasajeros
{
    char Nombre[20];
    char Apellido[20];
    int Cedula = 0;
    char EmbarcacionElegida[20];

    pasajeros *sig;
};
pasajeros *cab = NULL;
pasajeros *auxP1 = NULL;
pasajeros *auxP2 = NULL;

//-------------------------------------------------------------------

char temporalMatricula[3];
char temporalDia[3];
char temporalMes[3];
char temporalAño[3];

int RegistrarEmbarcacion()
{
    aux = (struct Barcos *)malloc(sizeof(struct Barcos));

    cout << "Ingrese la matricula de la embarcacion: ";
    cin >> temporalMatricula;
    strncpy(aux->Matricula, temporalMatricula, 2); // "strncpy" hace que solo reciba los dos primeros digitos. los demas lo ignora

    cout << "ingrese el nombre de la embarcacion: ";
    cin >> aux->NomEmbarcacion;

    cout << "ingrese el destino del viaje: ";
    cin >> aux->Destino;

    cout << "Ingrese el precio del viaje: $";
    cin >> aux->Precio;

    cout << "Ingrese el dia del viaje: ";
    cin >> temporalDia;
    strncpy(aux->Dia, temporalDia, 2);

    cout << "Ingrese el mes del viaje: ";
    cin >> temporalMes;
    strncpy(aux->Mes, temporalMes, 2);

    cout << "Ingrese el año del viaje: ";
    cin >> temporalAño;
    strncpy(aux->Año, temporalAño, 4);

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

int buscarEmbarcacion()
{
    aux = raiz;
    char buscadorBarco[20];
    if (aux == NULL)
    {
        cout << "No hay embarcaciones registradas" << endl;
        return 0;
    }
    if (aux != NULL)
    {
        cout << "Ingrese el identificador de la embarcacion: ";
        cin >> buscadorBarco;
        if (aux->Identificador == buscadorBarco)
        {
            cout << "--------------embarcacion registrada--------------" << endl;
            cout << "Nombre de la embarcacion: " << aux->NomEmbarcacion << endl;
            cout << "Destino del viaje: " << aux->Destino << endl;
            cout << "Precio del viaje: $" << aux->Precio << endl;
            cout << "Matricula: " << aux->Matricula << endl;
            cout << "Fecha de salida: " << aux->Dia << "/" << aux->Mes << "/" << aux->Año << endl;
            cout << "Numero de pasajeros: " << aux->Capacidad << endl;
            cout << "Identificador: " << aux->Identificador << endl;
            cout << "------------------------------------------------" << endl;
        }
        if (aux->Identificador != buscadorBarco)
        {
            if (buscadorBarco > aux->Identificador)
            {
                if (aux->der != NULL)
                {
                    aux = aux->der;
                    buscarEmbarcacion();
                }
            }
            if (buscadorBarco < aux->Identificador)
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

int registrarPasajero()
{
    if (cab == NULL)
    {
        cab = (struct pasajeros *)malloc(sizeof(struct pasajeros));

        cout << "ingrese su nombre: ";
        cin >> cab->Nombre;

        cout << "ingrese su apellido: ";
        cin >> cab->Apellido;

        cout << "Ingrese su cedula: ";
        cin >> cab->Cedula;

        cab->sig = NULL;
        return 0;
    }
    if (cab != NULL)
    {
        auxP1 = (struct pasajeros *)malloc(sizeof(struct pasajeros));
        cout << "ingrese su nombre: ";
        cin >> auxP1->Nombre;

        cout << "ingrese su apellido: ";
        cin >> auxP1->Apellido;

        cout << "Ingrese su cedula: ";
        cin >> auxP1->Cedula;

        auxP1->sig = NULL;
        auxP2 = cab;

        while (auxP2->sig != NULL)
        {
            auxP2 = auxP2->sig;
        }

        auxP2->sig = auxP1;
        auxP1 = NULL;
        auxP2 = auxP1;

        free(auxP1);
        free(auxP2);
    }
    return 0;
}

int MostrarPasajeros()
{
    for (auxP1 = cab; auxP1 != NULL; auxP1 = auxP1->sig)
    {
        cout << "Nombre: " << auxP1->Nombre << " " << auxP1->Apellido << endl;
        cout << "Numero de Cedula: " << auxP1->Cedula << endl;
        cout << "---------------------------------------------" << endl;
    }
    return 0;
}

int main()
{
    raiz = NULL;
    int opcion = 0;

    do
    {
        cout << "---------------Menu de opciones---------------" << endl;
        cout << "1. Registrar embarcacion (no se ha corregido)" << endl;
        cout << "2. buscar embarcacion (no funcional)" << endl;
        cout << "3. mostrar embarcaciones" << endl;
        cout << "4. eliminar embarcacion (no se ha hecho)" << endl;
        cout << "5. registrar pasajero (no se ha terminado)" << endl;
        cout << "6. mostrar pasajeros" << endl;
        cout << "7. Salir" << endl;
        cout << "---------------------------------------------" << endl;
        cout << "eliga una opcion: ";
        cin >> opcion;
        switch (opcion)
        {
        case 1:
            RegistrarEmbarcacion();
            raiz = insertar(raiz);
            break;
        case 2:
            buscarEmbarcacion();
            break;
        case 3:
            cout << "------------embarcaciones registradas------------" << endl;
            InOrden(raiz);
            cout << endl;
            break;
        case 5:
            registrarPasajero();
            break;
        case 6:
            cout << "------------pasajeros registrados------------" << endl;
            MostrarPasajeros();
            break;
        }
    } while (opcion != 7);
    return 0;
}