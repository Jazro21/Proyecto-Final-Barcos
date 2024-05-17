//Integrantes
//Deymar Andrés Ampudia Rivas
//Rodrigo Arturo Pérez Angulo

#include <iostream>
#include <string.h>
#include <malloc.h>
using namespace std;

struct Barcos{
    char nomEmbarcacion;
    int Precio = 0;
    char destino;
    char matricula;

    int Dia = 0;
    int Mes = 0;
    int Año = 0;

    int Capacidad = 0;
    Barcos *sig;
};

Barcos *cab, *aux, *aux2;

int registroViajes() 
{
    if (cab == NULL)
    {
        cab = (struct Barcos *)malloc(sizeof(struct Barcos)); 

        cout << "Ingrese el nombre de la embarcacion: ";
        cin >> cab->nomEmbarcacion;

        cout << "Ingrese el destino del viaje: ";
        cin >> cab->destino;

        cout << "Ingrese el precio del viaje: $";
        cin >> cab->Precio;

        cout << "Ingrese la matricula de la embarcacion: ";
        cin >> cab->matricula;

        cout << "Ingrese el dia del viaje: ";
        cin >> cab->Dia;

        cout << "Ingrese el mes del viaje: ";
        cin >> cab->Mes;

        cout << "Ingrese el año del viaje: ";
        cin >> cab->Año;

        cout << "Ingrese la capacidad de la embarcacion: ";
        cin >> cab->Capacidad;

        cab->sig = NULL;
        free(aux);
    }
    else
    {
        aux = (struct Barcos *)malloc(sizeof(struct Barcos));
        cout << "Ingrese la matricula de la embarcación: ";
        cin >> aux->matricula;

        bool IDExiste = false;
        aux2 = cab;
        while (aux2 != NULL)
        {
            if (aux2->matricula == aux->matricula)
            {
                IDExiste = true;
                break;
            }
            aux2 = aux2->sig;
        }
        if (IDExiste)
        {
            cout << "La matricula ingresada ya esta registrada. Por favor, intente nuevamente." << endl;
            free(aux);
        }
        else
        {

            cout << "Ingrese el nombre de la embarcacion: ";
            cin >> aux->nomEmbarcacion;

            cout << "Ingrese el destino del viaje: ";
            cin >> aux->destino;

            cout << "Ingrese el precio del viaje: $";
            cin >> aux->Precio;

            cout << "Ingrese el dia del viaje: ";
            cin >> aux->Dia;

            cout << "Ingrese el mes del viaje: ";
            cin >> aux->Mes;

            cout << "Ingrese el año del viaje: ";
            cin >> aux->Año;

            cout << "Ingrese la capacidad de la embarcacion: ";
            cin >> aux->Capacidad;

            aux->sig = NULL;

            aux2 = cab;
            while (aux2->sig != NULL) 
            {
                aux2 = aux2->sig;
            }

            aux2->sig = aux;
            aux = NULL;
            aux2 = NULL;

            free(aux);
            free(aux2);
        }
    }
    return 0;
}

int opcion = 0;

int main(){
    do{
        cout << "Sistema de Registro de Embarcaciones" << endl;

        cout << "1. Registrar un nuevo viaje." << endl;
        cout << "2. Buscar un viaje por identificador." << endl;
        cout << "3. Listar todos los viajes." << endl;
        cout << "4. Eliminar un viaje por identificador." << endl;
        cout << "5. Registrar un pasajero en un viaje." <<endl;
        cout << "6. Listar todos los pasajeros de un viaje." << endl;
        cout << "7. Salir" << endl;
        cout << "" << endl;

        cout << "Ingrese la opcion deseada";
        cin >> opcion;

        switch (opcion){

        case 1:
            registroViajes();
            break;
        
        case 7:
            cout << "Programa finalizado, que tenga Buen día" << endl;
            break;
        
        default:
            cout << "Opcion no valida, Intentelo Nuevamente." <<endl;
            break;
        }
    } while (opcion != 7);
    return 0;
}