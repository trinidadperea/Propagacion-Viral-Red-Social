// logica de la version secuencial

// la simulacion se ahra entre iteraciones actualizando el estado actual de cada nodo del grafo, en funcion a lo que realizan

// arranco por un usuario inicial, recorro todos los usuarios
// si alguno esta en estado COMPARTIO, cambio todos sus seguidores a visualizo

// Luego de recorrer todos los estados, hago un segundo pase para que los que estan en estado_actual, pasen a estado_sig
// cuando paso al estado siguiente, con la funcion probabilidad decido si el que visualizo compartio o ignoro en el sig turno
#include "red_social.h"
#include <time.h>
#include <stdio.h> 
#include <mpi.h>

// metodos

// funcion 
int pertenece(int usuario, int *lista, int tamaño_lista){
    // recorro la lista y veo si esta ese usuario
    for (int i = 0; i < tamaño_lista; i++){
        if (lista[i] == usuario){
            return 1; // existe
        }
    }
    return 0; // no existe
}


// generar_red()
// en este metodo inicializo el arreglo de usuario
// le asigno a cada usuario un numero aleatorio de seguidores de la lista global
void generar_red(Usuario *red, int n) {
    for (int i = 0; i < n; i++) {
        // asigno el usuario
        red[i].id = i;
        red[i].estado_actual = NO_ALCANZADO;
        red[i].estado_siguiente = NO_ALCANZADO;
        red[i].probabilidad_compartir = PROB_BASE;
        int cant = rand() % n; // seguidores aleatorios para ese usuario, entre 0 y 20 (esto seria la cant)
        red[i].cant_seguidores = cant;

        if (cant > 0) {
            red[i].seguidores = (int *) malloc(cant * sizeof(int)); // armo el vector para ese nodo en especifico

            for (int j = 0; j < cant; j++) {
                int posible_seguidor = rand() % n;
                
                // no se puede seguir a si mismo y tampoco se puede repetir
                if (posible_seguidor != i && !pertenece(posible_seguidor, red[i].seguidores, j)) { // esto es para que no se siga a si mismo
                    red[i].seguidores[j] = posible_seguidor;
                } else {
                    j--; // reintento en esa pos
                }
            }
        } else {
            red[i].seguidores = NULL; // El usuario no tiene seguidores
        }
    }
}

// funcion que agrego para mostrar string con el estado en vez del nro
const char* estado_a_string(Estado e) {
    switch (e) {
        case NO_ALCANZADO: return "NO_ALCANZADO";
        case VISUALIZADO:    return "VISUALIZADO";
        case COMPARTIDO:    return "COMPARTIDO";
        case IGNORO:       return "IGNORO";
        case ALCANZADO:     return "ALCANZADO";
        default:           return "DESCONOCIDO";
    }
}

// imprimo la red para ver que genera
void imprimir_red(Usuario *red, int n) {
    printf("\n--- Red Social ---\n");
    for (int i = 0; i < n; i++) {
        printf("Usuario: %d tiene: %d seguidores, estado actual: %s , estado siguiente: %s", red[i].id, red[i].cant_seguidores, estado_a_string(red[i].estado_actual), estado_a_string(red[i].estado_siguiente));
        printf(" ,usuario/usuarios que lo siguen: ");
        
        
        if (red[i].cant_seguidores > 0) {
            printf("[ ");
            for (int j = 0; j < red[i].cant_seguidores; j++) {
                printf("%d ", red[i].seguidores[j]);
            }
            printf("]");
        } else {
            printf("Sin seguidores");
        }
        printf("\n");
    }
    printf("------------------------------------------\n\n");
}


// vuelvo todo al inicio (usado para hacer muchas pruebas y que todas empiecen con la lista en no alcanzado)
void liberar_red(Usuario *red, int n) {
    for (int i = 0; i < n; i++) {
        if (red[i].seguidores != NULL) {
            free(red[i].seguidores);
        }
    }
}

// seleccionar_usuario_inicial()
// elijo un usuario inicial aleatorio, y cambio su estado_actual a compartido
int seleccionar_usuario_inicial(Usuario *red, int n){
    // selecciono un usuario aleatorio y le cambio el estado a compartido (este va a ser el inicial)
    int aletorio = rand() % n; 
    //printf("Usuario aleatorio a empezar: %d", red[aletorio].id);
    //red[aletorio].estado_actual = COMPARTIDO;
    return aletorio;
}

// simulacion()
// en cada iteracion cuento cuantos usuarios hay en cada uno de los estados
// inicializo el tiempo y lo freno una vez que termino la iteracion
// ese tiempo sera mi valor secuencial, el T(1)
void simulacion(Usuario *red, int n, int usuario_inicial, Estadisticas *estadisticas) {
    // PASO 2: Paciente Cero
    red[usuario_inicial].estado_actual = COMPARTIDO;
    estadisticas->total_compartieron++;
    estadisticas->total_alcanzados++;
    printf("Usuario inicial %d\n", usuario_inicial);

    for (int it = 1; it <= MAX_ITERACIONES; it++) {
        int nuevos_alcanzados = 0;

        // FASE 1: Marcar seguidores (quiénes ven el post)
        for (int i = 0; i < n; i++) {
            if (red[i].estado_actual == COMPARTIDO) {
                // A los seguidores del usuario los cambio a visualizado
                for (int j = 0; j < red[i].cant_seguidores; j++) {
                    int id_seguidor = red[i].seguidores[j];
                    if (red[id_seguidor].estado_actual == NO_ALCANZADO) {
                        red[id_seguidor].estado_siguiente = VISUALIZADO;
                    }
                }
            }
        }
        // imprimo a los seguidores en visualizo
        //printf("Seguidores en visualizo: \n");
        //imprimir_red(red, n);

        // ahora segun la probabilidad algunos compartiran y otros ignoraran
        for (int i = 0; i < n; i++) {
            if (red[i].estado_siguiente == VISUALIZADO) { 
                estadisticas->total_alcanzados++;
                float prob = (float)rand() / (float)RAND_MAX;
                
                if (prob <= PROB_BASE) { 
                    red[i].estado_actual = COMPARTIDO;
                    nuevos_alcanzados++;
                } else {
                    red[i].estado_actual = IGNORO;
                    estadisticas->total_ignoraron++;
                }
                // limpio para la sig iteracion
                red[i].estado_siguiente = NO_ALCANZADO; 
            } 
            else if (red[i].estado_actual == COMPARTIDO) {
                // El que ya compartió no participa mas para evitar bucles, asique queda en estado alcanzado
                red[i].estado_actual = ALCANZADO;
            }
        }

        printf("Iteración %d: %d nuevos compartieron.\n", it, nuevos_alcanzados);
        
        if (nuevos_alcanzados == 0) {
            printf("La propagación se detuvo.\n");
            break;
        }
    }
}
void mostrar_estadisticas(Estadisticas st, int n) {
    printf("\nEstadisticas\n");
    printf("Usuarios totales en la red: %d\n", n);
    printf("Usuarios alcanzados: %d (%.2f%%)\n", 
            st.total_alcanzados, (float)st.total_alcanzados/n*100);
    printf("Usuarios que compartieron:    %d\n", st.total_compartieron);
    printf("Usuarios que ignoraron:       %d\n", st.total_ignoraron);
    printf("Tiempo de ejecución T(1):     %f segundos\n", st.tiempo_ejecucion);

}

int main(int argc, char **argv) {
    int n = 1500; // usuarios

    double t_inicial, t_final;
    // para el tiempo secuencial
    MPI_Init(&argc, &argv); 

    srand(time(NULL)); // para la aletoriedad

    Usuario *red = (Usuario *) malloc(n * sizeof(Usuario));

    // Inicializamos la red (llamando a tu función)
    generar_red(red, n);

    // Los inicializo a todos en no alcanzado
    int inicio = seleccionar_usuario_inicial(red, n);

    // Probamos qué devuelve la función
    printf("Red incicial");
    imprimir_red(red, n);

    // antes de la simulacion inicio el tiempo
    t_inicial = MPI_Wtime();
    Estadisticas estadisticas = {0,0,0,0.0};

    // simulacion
    printf("Empieza la simulacion \n");
    simulacion(red, n, inicio, &estadisticas);

    t_final = MPI_Wtime();

    estadisticas.tiempo_ejecucion = t_final - t_inicial;

    imprimir_red(red, n);

    printf("Tiempo de ejecución secuencial T(1): %f segundos\n", estadisticas.tiempo_ejecucion);

    mostrar_estadisticas(estadisticas,n);

    // No olvides liberar la memoria como vimos antes
    liberar_red(red, n);
    free(red);

    MPI_Finalize();
    return 0;
}