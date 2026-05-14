// logica de la version secuencial

// la simulacion se ahra entre iteraciones actualizando el estado actual de cada nodo del grafo, en funcion a lo que realizan

// arranco por un usuario inicial, recorro todos los usuarios
// si alguno esta en estado COMPARTIO, cambio todos sus seguidores a visualizo

// Luego de recorrer todos los estados, hago un segundo pase para que los que estan en estado_actual, pasen a estado_sig
// cuando paso al estado siguiente, con la funcion probabilidad decido si el que visualizo compartio o ignoro en el sig turno
#include "red_social.h"

// metodos

// generar_red()
// en este metodo inicializo el arreglo de usuario
// le asigno a cada usuario un numero aleatorio de seguidores de la lista global


// seleccionar_usuario_inicial()
// elijo un usuario inicial aleatorio, y cambio su estado_actual a compartio


// simulacion()
// en cada iteracion cuento cuantos usuarios hay en cada uno de los estados
// inicializo el tiempo y lo freno una vez que termino la iteracion
// ese tiempo sera mi valor secuencial, el T(1)

