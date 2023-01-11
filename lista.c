//lista.c
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "lista.h"

// Reserva e inicializa la estructura para una lista de listas
NodoLista *crearLista(){
    NodoLista *nuevoNodo;
    
    if ((nuevoNodo = (NodoLista *)malloc(sizeof(NodoLista))) == NULL) { //se verifica que exista espacio suficiente en la memoria
		printf("crearListaLista: error en malloc");
		exit(1); //termina la ejecucion del programa y retorna 1
	}

    return nuevoNodo;
}

// Reserva e inicializa la estructura para una lista
int crearNodo(Nodo **nuevoNodo, int valor){

    if ((*nuevoNodo = (Nodo *)malloc(sizeof(Nodo))) == NULL) { //se verifica que exista espacio suficiente en la memoria
		printf("crearLista: error en malloc");
		return 0;
	}
    
    (*nuevoNodo)->valor = valor;
    (*nuevoNodo)->ant_sig = NULL;

    return 1;
}

//inicializa una lista de listas
void Inicializar(NodoLista *Lista) {
    Lista->inicio=Lista->fin=NULL;
    Lista->longitud=0;
}

//retorna 1 si la lista esta vacia y cero si no lo esta
int esVacia(NodoLista *Lista) {
    return (Lista->longitud == 0);
}

//retorna el XOR de dos apuntadores dados
Nodo *XOR(Nodo *a, Nodo *b) {
    return (Nodo *) ((uintptr_t) (a) ^ (uintptr_t) (b));
}

//inserta un nodo al principio de la lista
int insertarPrincipio(NodoLista **Lista, int valor) {
    //reservo memoria y le asigno el valor dado al nuevo nodo 
    Nodo *nuevoNodo;
    if (!(crearNodo(&nuevoNodo,valor))) //si no se logra crear devuelve 0
        return 0;

    /* Como el nuevo nodo se insertara al principio de la lista
    siempre tendra como campo el XOR de la direccion 
    de la cabeza actual de la lista y NULL*/
    nuevoNodo->ant_sig = (*Lista)->inicio;

    /*Si la lista no esta vacia, entonces ant_sig de la cabeza 
    actual va a ser el XOR del nuevo nodo y y el campo ant_sig de 
    la cabeza actual*/
    if ((*Lista)->inicio != NULL){
        (*Lista)->inicio->ant_sig = XOR(nuevoNodo, (*Lista)->inicio->ant_sig);
    } else {
        /*Si la lista esta vacia, el nuevo nodo siempre 
        va a ser el ultimo nodo*/
        (*Lista)->fin = nuevoNodo; 
    }
    //nueva cabeza de la lista
    (*Lista)->inicio = nuevoNodo;
    
    //incremento la longitud de la lista
    (*Lista)->longitud++;

    return 1;
}

//inserta un nodo al final de la lista
int insertarFinal(NodoLista **Lista, int valor) {
    //reservo memoria y le asigno el valor dado al nuevo nodo 
    Nodo *nuevoNodo;
    if (!(crearNodo(&nuevoNodo, valor))) //si no se logra crear devuelve 0
        return 0;

    nuevoNodo->ant_sig = (*Lista)->fin;

    if ((*Lista)->inicio != NULL){
        (*Lista)->fin->ant_sig = XOR((*Lista)->fin->ant_sig, nuevoNodo);
    } else {
        /*Si la lista esta vacia, el nuevo nodo siempre 
        va a ser el ultimo nodo*/
        (*Lista)->inicio = nuevoNodo; 
    }

    (*Lista)->fin = nuevoNodo;
    
    //incremento la longitud de la lista
    (*Lista)->longitud++;

    return 1;
}

//inserta un nodo en una lista ordenada
int insertarOrdenado(NodoLista **Lista, int valor) {
    // Si la lista esta vacia o el nuevo valor es menor o igual al valor inicial de la lista
    if (!(*Lista)->inicio || valor <= (*Lista)->inicio->valor)
        return insertarPrincipio(Lista, valor);

    // Si el valor de la lista es mayor o igual que el valor final de la lista
    if (valor >= (*Lista)->fin->valor)
        return insertarFinal(Lista, valor);

    Nodo *nuevoNodo;
    if (!(crearNodo(&nuevoNodo, valor))) //si no se logra crear devuelve 0
        return 0;

    Nodo *actual = (*Lista)->inicio;    
    Nodo *prev = NULL;
    Nodo *sig;

    // Mientras el valor actual de la lista es menor al valor a insertar
    while (actual->valor < valor) {
        sig = XOR(prev, actual->ant_sig);

        prev = actual;
        actual = sig;
    }

    // Si el valor de 'prev' es distinto de NULL
    if (prev) {
        /* Al nodo 'prev' se le asigna la direccion del nodo anterior y el nuevo nodo (sera el nodo siguiente)
         * A 'nuevoNodo' se le asigna la direccion del nodo 'prev' y del nodo 'actual'
         * Al nodo 'actual' se le asigna la direccion del nodo siguiente y el nuevo nodo (sera el nodo anterior)
         * 
         * La direccion del nodo anterior a 'prev' se obtiene aplicando XOR con el valor de prev->ant_sig y actual
         * La direccion del nodo siguiente a 'actual' se obtiene aplicando XOR con el valor de actual->ant_sig y prev
         */
        prev->ant_sig = XOR(XOR(prev->ant_sig, actual), nuevoNodo);
        nuevoNodo->ant_sig = XOR(prev, actual);
        actual->ant_sig = XOR(nuevoNodo, XOR(prev, actual->ant_sig));
    }

    (*Lista)->longitud++;

    return 1;
}

/*busca un elemento en una lista retornando
su posicion o cero si no esta*/
int buscar(NodoLista *Lista, int valor) {
    Nodo *actual = Lista->inicio;
    Nodo *prev = NULL;
    Nodo *sig;
    int c=1; //contador de nodos

    while (actual != NULL) {
        if (actual->valor == valor) //encontre el elemento           
            return c;

        sig = XOR(prev, actual->ant_sig);
 
        /*actualizamos los valores de prev, actual 
        y el contador para la siguiente iteracion*/
        prev = actual;
        actual = sig;
        c++;
    }

    return 0;
}

//saca el primer elemento de la lista
int sacarPrincipio(NodoLista *Lista, int *elemento) {
    Nodo *nodoAux = Lista->inicio;

    if (nodoAux) {
        *elemento = nodoAux->valor;
        Lista->inicio = Lista->inicio->ant_sig;

        if (Lista->inicio) 
            Lista->inicio->ant_sig = XOR(nodoAux, Lista->inicio->ant_sig); //calculamos su nuevo valor al campo ant_sig
        else
            Lista->inicio = Lista->fin = NULL; //si no existe entonces el inicio de la lista tambien apunta a NULL

        free(nodoAux);
        Lista->longitud--;

        return 1;
    }

    return 0;
}

//Saca el ultimo elemento de una lista
int sacarFinal(NodoLista *Lista, int *elemento){
    Nodo *nodoAux = Lista->fin;
    //Si existe al menos un nodo
    if (nodoAux){
        *elemento = nodoAux->valor; //saco el valor
        Lista->fin = nodoAux->ant_sig; //fin apunta al penultimo nodo (si lo hay)

        if(Lista->fin) //si existe un penultimo nodo
            Lista->fin->ant_sig = XOR(nodoAux, Lista->fin->ant_sig); //calculamos su nuevo valor al campo ant_sig
        else
            Lista->inicio = NULL; //si no existe entonces el inicio de la lista tambien apunta a NULL

        free(nodoAux); //liberamos el espacio reservado en memoria
        Lista->longitud--; //decrementamos la cantidad de elementos 

        return 1;
    }

    return 0; 
}

//Saca la primera ocurrencia en una lista
int sacarPrimeraOcurrencia(NodoLista *Lista, int elemento){
   Nodo *actual = Lista->inicio, *prev = NULL, *sig;
   sig = actual->ant_sig;

    while (actual != NULL) {
        
        if (actual->valor == elemento){ //encontre el elemento

            if( prev) //hay un nodo previo
                /* prev->ant_sig= sig^ant^sig^actual=ant^actual=ant^sig 
                    (actual es el nodo siguiente de prev)
                 */
                prev->ant_sig = XOR(sig, XOR(prev->ant_sig, actual));
            else 
                Lista->inicio = sig; //El inicio de la lista es el nodo siguiente
            
            if (sig) //hay un nodo siguiente
                /* sig->ant_sig= prev^ant^sig^actual=actual^sig=ant^sig
                 (actual es el anterior del nodo siguiente) 
                */
                sig->ant_sig = XOR(prev, XOR(sig->ant_sig, actual));
            else
                Lista->fin = prev; //el fin de la lista es el nodo previo

            free(actual); //liberamos el espacio reservado en memoria
            Lista->longitud--; //decrementamos la longitud 
            
            return 1;    
        }

        /*actualizamos los valores de prev y actual
        para la siguiente iteracion*/ 
        prev = actual;
        actual = sig;

        /*calculamos la direccion del siguiente nodo
        sig = prev ^ (prev ^ sig) = sig */
        sig = XOR (prev, actual->ant_sig);
    }

    return 0; 
}

/*lista los valores de la lista enlazada XOR
desde la cabeza hasta el final*/
void listarInicioAFinal(NodoLista *Lista){
    Nodo *actual = Lista->inicio, *prev = NULL, *sig;
    printf("Valores desde el inicio hasta al final\nde la lista enlazada XOR\n\n");
    
    while (actual != NULL) {
        //imprime el valor del nodo actual
        printf ("%i ", actual->valor);

        /*calculamos la direccion del siguiente nodo
         sig = prev ^ (prev ^ sig) = sig */
        sig = XOR (prev, actual->ant_sig);
 
        /*actualizamos los valores de prev y actual
        para la siguiente iteracion*/ 
        prev = actual;
        actual = sig;
    }
}

/*lista los valores de la lista enlazada XOR
desde el final hasta el inicio*/
void listarFinalAInicio(NodoLista *Lista){
    Nodo *actual = Lista->fin, *prev = NULL, *sig;
    printf("Valores desde el final hasta el inicio\nde la lista enlazada XOR\n\n");
    
    while (actual != NULL) {
        //imprime el valor del nodo actual
        printf ("%i ", actual->valor);

        /*calculamos la direccion del siguiente nodo
         sig = prev ^ (prev ^ sig) = sig */
        sig = XOR (prev, actual->ant_sig);
 
        /*actualizamos los valores de prev y actual
        para la siguiente iteracion*/ 
        prev = actual;
        actual = sig;
    }
}
//Retorna el numero de elementos de la Lista
int cantidadElementos(NodoLista *Lista){
    return Lista->longitud;
}
