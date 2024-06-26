// Integrantes
// Deymar Andrés Ampudia Rivas
// Rodrigo Arturo Pérez Angulo

#include <iostream>
#include <malloc.h>

using namespace std;

//--------------------estructura de las embarcaciones--------------------

struct Barcos
{
    char NomEmbarcacion[50];
    char Destino[50];
    int Precio = 0;
    int Capacidad = 0;

    long long Identificador = 0; // el minimo son 10
    long long Matricula = 0;     // solo guarda los 2 primeros

    int MatriculaOriginal = 0; // guarda la matricula completa
    int Dia = 0;
    int Mes = 0;
    int Año = 0;

    int PasajerosAbordo = 0;

    Barcos *izq = NULL;
    Barcos *der = NULL;

    int altura = 0;
};

Barcos *raiz = NULL;
Barcos *aux = NULL;
Barcos *aux2 = NULL;

//-------------------------------------------------------------------

//--------------------estructura de los pasajeros--------------------
struct pasajeros
{
    char Nombre[20];
    char Apellido[20];

    long long IdentificadorElegido = 0;
    // char EmbarcaionEligida[20]; // no se está implementando

    int Cedula = 0;

    pasajeros *sig;
};
pasajeros *cab = NULL;
pasajeros *auxP1 = NULL;
pasajeros *auxP2 = NULL;

//-------------------------------------------------------------------

long long TemporalIdentificador = 0;
long long temporalMatricula = 0;
int temporalDia = 0;
int temporalMes = 0;
int temporalAño = 0;

long long a = 0, b = 0, c = 0, d = 0;

long long buscadorBarco = 0;

int RegistrarEmbarcacion()
{
    aux = ((struct Barcos *)malloc(sizeof(struct Barcos)));

    cout << "Ingrese la matricula del viaje: ";
    cin >> aux->MatriculaOriginal;
    temporalMatricula = aux->MatriculaOriginal;

    if (temporalMatricula < 10)
    {
        cout << "Matricula invalida. intente nuevamente" << endl;
        RegistrarEmbarcacion();
    }
    else
    {
        while (temporalMatricula >= 100)
        {
            temporalMatricula = temporalMatricula / 10;
        }
        if (temporalMatricula < 100)
        {
            aux->Matricula = temporalMatricula;
        }
    }

    cout << "Ingrese el nombre de la embarcacion: ";
    cin >> aux->NomEmbarcacion;

    cout << "Ingrese el destino del viaje: ";
    cin >> aux->Destino;

    cout << "Ingrese el precio del viaje: $";
    cin >> aux->Precio;

    cout << "Ingrese la capacidad maxima de la embarcacion (numero de personas abordo): ";
    cin >> aux->Capacidad;
    aux->PasajerosAbordo = 0;
    // ------------------------------------------------------------
    cout << "Ingrese el ano del viaje: ";
    cin >> temporalAño;
    aux->Año = temporalAño;

    cout << "Ingrese el mes del viaje: ";
    cin >> temporalMes;
    aux->Mes = temporalMes;

    cout << "Ingrese el dia del viaje: ";
    cin >> temporalDia;
    aux->Dia = temporalDia;
    // ------------------------------------------------------------
    a = (temporalMatricula * 100000000);
    b = (temporalAño * 10000);
    c = (temporalMes * 100);
    d = (temporalDia * 1);

    TemporalIdentificador = a + b + c + d;

    aux->Identificador = TemporalIdentificador;
    // ------------------------------------------------------------

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

    suby->izq = subx;
    subx->der = sub4;

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
    cout << "Nombre del viaje: " << sub->NomEmbarcacion << endl;
    cout << "Destino del viaje: " << sub->Destino << endl;
    cout << "Precio del viaje: $" << sub->Precio << endl;
    cout << "Matricula: " << sub->MatriculaOriginal << endl;
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
    if (aux == NULL)
    {
        cout << "No hay viajes registrados" << endl;
        return 0;
    }
    if (aux != NULL)
    {
        if (aux->Identificador == buscadorBarco)
        {
            cout << "--------------viaje registrado--------------" << endl;
            cout << "Nombre del viaje: " << aux->NomEmbarcacion << endl;
            cout << "Destino del viaje: " << aux->Destino << endl;
            cout << "Precio del viaje: $" << aux->Precio << endl;
            cout << "Matricula: " << aux->MatriculaOriginal << endl;
            cout << "Fecha de salida: " << aux->Dia << "/" << aux->Mes << "/" << aux->Año << endl;
            cout << "Numero de pasajeros: " << aux->Capacidad << endl;
            cout << "Identificador: " << aux->Identificador << endl;
            cout << "------------------------------------------------" << endl;
            return 0;
        }
        if (aux->Identificador != buscadorBarco)
        {
            if (buscadorBarco < aux->Identificador)
            {
                if (aux->izq != NULL)
                {
                    aux = aux->izq;
                    buscarEmbarcacion();
                }
            }
            if (buscadorBarco > aux->Identificador)
            {
                if (aux->der != NULL)
                {
                    aux = aux->der;
                    buscarEmbarcacion();
                }
            }
        }
    }
    return 0;
}

int registrarPasajero()
{
    if (aux == NULL) // no hay embarcaciones registradas
    {
        cout << "No hay viajes registrados" << endl;
        return 0;
    }
    if (aux != NULL) // hay embarcaciones registradas
    {
        if (aux->Identificador == buscadorBarco) // el buscador coincide con el identificador
        {
            if (cab == NULL)
            {
                cab = (struct pasajeros *)malloc(sizeof(struct pasajeros));

                if (aux->PasajerosAbordo < aux->Capacidad)
                {
                    aux->PasajerosAbordo = aux->PasajerosAbordo + 1;
                }
                else if (aux->PasajerosAbordo == aux->Capacidad)
                {
                    cout << "Ya no hay cupos disponibles en este viaje " << endl;
                    return 0;
                }

                cout << "Ingrese su nombre: ";
                cin >> cab->Nombre;

                cout << "Ingrese su apellido: ";
                cin >> cab->Apellido;

                cout << "Ingrese su cedula: ";
                cin >> cab->Cedula;

                cab->IdentificadorElegido = aux->Identificador;

                cab->sig = NULL;
                return 0;
            }
            if (cab != NULL)
            {
                auxP1 = (struct pasajeros *)malloc(sizeof(struct pasajeros));

                if (aux->PasajerosAbordo < aux->Capacidad)
                {
                    aux->PasajerosAbordo = aux->PasajerosAbordo + 1;
                }
                else if (aux->PasajerosAbordo == aux->Capacidad)
                {
                    cout << "Ya no hay cupos disponibles" << endl;
                    return 0;
                }
                cout << "Ingrese su nombre: ";
                cin >> auxP1->Nombre;

                cout << "Ingrese su apellido: ";
                cin >> auxP1->Apellido;

                cout << "Ingrese su cedula: ";
                cin >> auxP1->Cedula;

                auxP1->IdentificadorElegido = aux->Identificador;

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
        }
        if (aux->Identificador != buscadorBarco) // no coincide
        {
            if (aux->der != NULL)
            {
                aux = aux->der;
                registrarPasajero();
            }
            if (aux->izq != NULL)
            {
                aux = aux->izq;
                registrarPasajero();
            }
        }
    }
    return 0;
}

int MostrarPasajeros()
{
    if (aux == NULL)
    {
        cout << "No hay pasajeros registrados" << endl;
        return 0;
    }
    if (aux != NULL)
    {
        for (auxP1 = cab; auxP1 != NULL; auxP1 = auxP1->sig)
        {
            if (auxP1->IdentificadorElegido == buscadorBarco)
            {
                cout << "Nombre: " << auxP1->Nombre << " " << auxP1->Apellido << endl;
                cout << "Numero de Cedula: " << auxP1->Cedula << endl;
                cout << "---------------------------------------------" << endl;
            }
        }
        return 0;
    }
    return 0;
}

int Ubicar(Barcos *aux3, int buscarB)
{
    if (aux3->Identificador == buscarB)
    {
        aux = aux3;
    }
    else
    {
        if (aux3->izq != NULL)
        {
            Ubicar(aux3->izq, buscarB);
        }
        if (aux3->der != NULL)
        {
            Ubicar(aux3->der, buscarB);
        }
    }
    return 0;
}

int UbicarPadre(Barcos *padre)
{
    if ((padre->izq != NULL) && (padre->izq != aux))
    {
        UbicarPadre(padre->izq);
    }
    if (padre->izq == aux)
    {
        aux2 = padre;
    }
    if ((padre->der != NULL) && (padre->der != aux))
    {
        UbicarPadre(padre->der);
    }
    if (padre->der == aux)
    {
        aux2 = padre;
    }
    return 0;
}

int EliminarCaso1() // el nodo no tiene hijos
{
    if (aux != raiz)
    {
        UbicarPadre(raiz);
    }
    if (aux2->izq == aux)
    {
        aux2->izq = NULL;
        free(aux);
        return 0;
    }
    else if (aux2->der == aux)
    {
        aux2->der = NULL;
        free(aux);
        return 0;
    }
    return 0;
}

int EliminarCaso2() // el nodo tiene un hijo
{
    if (aux != raiz)
    {
        UbicarPadre(raiz);
    }
    else
    {
        free(aux);
        return 0;
    }

    if (aux2->izq == aux)
    {
        if (aux->izq != NULL)
        {
            aux2->izq = aux->izq;
        }
        if (aux->der != NULL)
        {
            aux2->izq = aux->der;
        }
    }

    if (aux2->der == aux)
    {
        if (aux->izq != NULL)
        {
            aux2->der = aux->izq;
        }
        if (aux->der != NULL)
        {
            aux2->der = aux->der;
        }
    }
    free(aux);
    return 0;
}

int EliminarCaso3() // el nodo tiene dos hijos
{
    return 0;
}

int EliminarEmbarcacion()
{
    cout << "Ingrese el identificador del viaje que desea eliminar: ";
    cin >> buscadorBarco;

    Ubicar(raiz, buscadorBarco);

    if (aux == NULL)
    {
        cout << "No hay viajes registrados" << endl;
        return 0;
    }

    if (aux->izq == NULL && aux->der == NULL) // caso 1
    {
        EliminarCaso1();
        cout << "Eliminacion exitosa" << endl;
        return 0;
    }
    if ((aux->izq == NULL && aux->der != NULL) && (aux->izq != NULL && aux->der == NULL)) // caso 2
    {
        EliminarCaso2();
        cout << "Eliminacion exitosa" << endl;
        return 0;
    }
    if (aux->izq != NULL && aux->der != NULL) // caso 3
    {
        EliminarCaso3();
        return 0;
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
        cout << "1. Registrar un nuevo viaje" << endl;
        cout << "2. Buscar un viaje por identificador" << endl;
        cout << "3. Listar todos los viajes" << endl;
        cout << "4. Eliminar un viaje por identificador" << endl;
        cout << "5. Registrar un pasajero en un viaje" << endl;
        cout << "6. Listar pasajeros de un viaje" << endl;
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
            cout << "Ingrese el identificador de la embarcacion: ";
            cin >> buscadorBarco;

            aux = raiz;
            buscarEmbarcacion();
            break;
        case 3:
            cout << "------------embarcaciones registradas------------" << endl;
            InOrden(raiz);
            cout << endl;
            break;
        case 4:
            EliminarEmbarcacion();
            raiz = insertar(raiz);
            break;
        case 5:
            aux = raiz;
            cout << "Ingrese el identificador del viaje: ";
            cin >> buscadorBarco;
            registrarPasajero();
            break;
        case 6:
            cout << "Ingrese la identificador del viaje: ";
            cin >> buscadorBarco;
            cout << "------------pasajeros registrados en el viaje------------" << endl;
            MostrarPasajeros();
            break;
        case 7:
            cout << "Programa finalizado. Que tenga un buen dia" << endl;
            break;
        }
    } while (opcion != 7);

    return 0;
}
