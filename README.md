# Proyecto-Final-Barcos

Desarrollar una aplicación que permita gestionar los viajes programados de las embarcaciones de 
transporte fluvial en el Pacífico Colombiano. En esta aplicación, podrán registrar, buscar, listar y 
eliminar viajes y pasajeros.
Requisitos del Proyecto:

1. Estructura de Datos:
• Implementar un árbol AVL para gestionar viajes programados de diferentes
embarcaciones.
• Cada nodo del árbol AVL representa un viaje y debe tener una cola FIFO (First In, 
First Out) para gestionar los pasajeros de cada viaje.

2. Datos de Cada Viaje:
• Precio del viaje.
• Destino del viaje.
• Matrícula de la embarcación.
• Nombre de la embarcación.
• Fecha del viaje: día, mes y año.
• Capacidad de la embarcación (número máximo de pasajeros).

3. Identificación Única del Viaje:
• El identificador único de cada viaje se generará concatenando los dos primeros 
caracteres de la matrícula de la embarcación con el año, mes y día del viaje.
• Formato del identificador: XXYYYYMMDD donde XX son los dos primeros 
caracteres de la matrícula, YYYY es el año, MM es el mes y DD es el día.

4. Funciones a Implementar:
• Registrar Viaje: Permitir el registro de un nuevo viaje ingresando la matrícula de 
la embarcación, el nombre de la embarcación, la fecha del viaje, el precio, el destino 
y la capacidad. Generar el identificador único del viaje.
• Buscar Viaje: Buscar un viaje específico por su identificador único y mostrar los 
detalles del viaje.
• Listar Viajes: Listar todos los viajes en orden ascendente de sus identificadores 
únicos utilizando un recorrido en inorden del árbol AVL.
• Eliminar Viaje: Eliminar un viaje del sistema utilizando su identificador único.
• Registrar Pasajero: Registrar pasajeros en un viaje específico utilizando una 
estructura FIFO. El número de pasajeros no debe exceder la capacidad de la 
embarcación.
• Listar Pasajeros: Listar todos los pasajeros de un viaje en el orden en que fueron 
registrados.

5. Interfaz del Usuario:
• La aplicación debe proporcionar un menú de opciones que permita al usuario 
interactuar con el sistema:
1. Registrar un nuevo viaje.
2. Buscar un viaje por identificador.
3. Listar todos los viajes.
4. Eliminar un viaje por identificador.
5. Registrar un pasajero en un viaje.
6. Listar todos los pasajeros de un viaje.
7. Salir.


6. Balanceo y Mantenimiento:
• Asegurarse de que el árbol AVL de viajes se mantenga balanceado después de 
cada inserción y eliminación
