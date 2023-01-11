//menu
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "lista.h"

int main(){
    
    NodoLista *Lista=NULL;
    int opc,e; //variable para menu //fila columna y elemento 
    printf("                LISTA ENLAZADA XOR\n");//encabezado
    Lista = crearLista(); //se reserva el espacio en memoria de la lista
    Inicializar(Lista); //se inicializa la lista
    //menu
    do{ 
        printf("\n\n\n"); //dejo espacios arriba
        printf("Ingrese la operacion que desea realizar\n\n");
        printf("   1. Revisar si la lista esta vacia\n");
        printf("   2. Insertar elemento al principio de la lista\n");
        printf("   3. Insertar elemento al final de la lista\n"); 
        printf("   4. Insertar elemento en la lista ordenada\n");
        printf("   5. Buscar un elemento en la lista\n");
        printf("   6. Sacar el primer elemento de la lista\n");
        printf("   7. Sacar el ultimo elemento de la lista\n");
        printf("   8. Sacar la primera ocurrencia de un elemento dado\n");
        printf("   9. Listar de inicio a final\n");
        printf("   10. Listar de final a inicio\n");
        printf("   11. Mostrar la cantidad de elementos de la lista\n");
        printf("   0. Salir\n");
        scanf("%i", &opc);
        printf("\n\n");
        switch (opc){
        case 1:
            if (esVacia(Lista))
                printf("La lista esta vacia\n");
            else 
                printf("La lista no esta vacia\n");  
            break;
        case 2:
            printf("Ingrese el elemento que desea insertar a la lista\n");
            scanf("%i", &e);
            insertarPrincipio(&Lista,e);
            break; 
        case 3:
            printf("Ingrese el elemento que desea insertar a la lista\n");
            scanf("%i", &e);
            insertarFinal(&Lista,e);
            break;
        case 4:
            printf("Ingrese el elemento que desea insertar a la lista ordenada\n");
            scanf("%i", &e);
            insertarOrdenado(&Lista,e);
            break;
        case 5:
            printf("Ingrese el elemento que desea buscar en la lista\n");
            scanf("%i", &e);

            /*se guarda el resultado para no tener que hacer el calculo dos veces*/
            int result=buscar(Lista, e);

           if(!result)
                printf("El elemento no se encuentra en la lista\n");
            else
                printf("El elemento se encuentra en la lista en el nodo %i\n", result);
            break;
        case 6:
            sacarPrincipio(Lista,&e);
            printf("El primer elemento sacado fue %i\n", e);
            break;
        case 7:
            sacarFinal(Lista, &e);
            printf("El ultimo elemento sacado fue %i\n", e);
            break;
        case 8:
            printf("Ingrese el elemento al que desea sacar su primera ocurrencia\n");
            scanf("%i", &e);
            sacarPrimeraOcurrencia(Lista, e);
            break;
        case 9:
            listarInicioAFinal(Lista);
            printf("\n\n");
            break;
        case 10:
            listarFinalAInicio(Lista);
            printf("\n\n");
            break;
        case 11:
            printf("La cantidad de elementos de la lista es %i\n", cantidadElementos(Lista));
            break;
        case 0:
            break;      
        default:
            printf("No ingresaste una opcion valida\n");
            break;
        }

    }while(opc); //opc distinto de cero

    return 0;    
}
