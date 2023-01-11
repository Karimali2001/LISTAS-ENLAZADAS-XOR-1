//lista.h
#ifndef lista_h
#define lista_h
//Estructura de lista enlazada XOR
typedef struct nodo{
    int valor;              //valor que guarda el nodo
    struct nodo *ant_sig;   //campo del XOR del nodo siguiente y el anterior
}Nodo;

//Estructura de lista de listas XOR
typedef struct nodolista{
    int longitud; //longitud de la lista
    Nodo *inicio, *fin;     //apuntadores al inicio y al fin de la lista
}NodoLista;

// Reserva e inicializa la estructura para una lista de listas
NodoLista *crearLista();
// Reserva e inicializa la estructura para una lista
int crearNodo(Nodo **nuevoNodo, int valor);
//inicializa una lista de listas
void Inicializar(NodoLista *Lista);
//retorna 1 si la lista esta vacia y cero si no lo esta
int esVacia(NodoLista *Lista);
//retorna el XOR de dos apuntadores dados
Nodo *XOR(Nodo *a, Nodo *b);
//inserta un nodo al principio de la lista
int insertarPrincipio(NodoLista **Lista, int valor);
//inserta un nodo al final de la lista
int insertarFinal(NodoLista **Lista, int valor);
//inserta un nodo en una lista ordenada
int insertarOrdenado(NodoLista **Lista, int valor);
/*busca un elemento en una lista retornando
su posicion o cero si no esta*/
int buscar(NodoLista *Lista, int valor);
//saca el primer elemento de la lista
int sacarPrincipio(NodoLista *Lista, int *elemento);
//Saca el ultimo elemento de una lista
int sacarFinal(NodoLista *Lista, int *elemento);
//Saca la primera ocurrencia en una lista
int sacarPrimeraOcurrencia(NodoLista *Lista, int elemento);
/*lista los valores de la lista enlazada XOR
desde la cabeza hasta el final*/
void listarInicioAFinal(NodoLista *Lista);
/*lista los valores de la lista enlazada XOR
desde el final hasta el inicio*/
void listarFinalAInicio(NodoLista *Lista);
//Retorna el numero de elementos de la Lista
int cantidadElementos(NodoLista *Lista);

#endif
