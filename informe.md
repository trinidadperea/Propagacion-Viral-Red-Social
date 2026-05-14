# Proyecto Ppyd

**Grupo:** Valerio Perla, Perea Trinidad

---

# Introducción

El presente proyecto tiene como objetivo desarrollar una simulación de propagación viral de contenido dentro de una red social utilizando programación paralela mediante MPI (Message Passing Interface).

La idea general consiste en modelar una red social como un conjunto de usuarios conectados entre sí mediante relaciones de seguimiento o amistad. Dentro de esta red, un contenido (por ejemplo un meme, noticia o publicación) será difundido entre los usuarios según ciertas probabilidades de visualización y compartido.

El proyecto buscará implementar inicialmente una versión secuencial del algoritmo y posteriormente una versión paralela distribuida utilizando MPI, permitiendo analizar el comportamiento de la propagación y el rendimiento de la solución paralela.

La simulación será realizada de manera offline y mediante iteraciones discretas, evitando el uso de interfaces gráficas complejas o conexiones reales de red, con el fin de centrar el desarrollo en el diseño paralelo y el análisis de rendimiento.

---

# Objetivo

Desarrollar una simulación paralela distribuida de propagación viral en una red social utilizando MPI, evaluando el rendimiento y la escalabilidad de la solución.

## Objetivos específicos

- Modelar una red social mediante una estructura de grafo.
- Implementar una simulación secuencial de propagación viral.
- Identificar las partes paralelizables del problema.
- Diseñar e implementar una versión paralela utilizando MPI.
- Analizar speedup, eficiencia y escalabilidad.
- Evaluar el costo de comunicación entre procesos.
- Comparar el rendimiento entre la versión secuencial y paralela.

---

# Descripción del problema

Cada usuario estará en alguno de los siguientes estados:

- **No alcanzado:** El usuario aún no vio el contenido.
- **Visualizó:** El usuario vio el contenido.
- **Compartió:** El usuario decidió compartir el contenido.
- **Ignoró:** El usuario vio el contenido y no hizo nada.

## Iteraciones

En cada iteración:

1. Los usuarios que recibieron el contenido podrán decidir compartirlo según una probabilidad determinada.
2. Si un usuario comparte contenido, este será enviado a sus seguidores.
3. Los seguidores cambiarán su estado en la siguiente iteración.

---

# Modelo

La red social será representada mediante un grafo en el cual:

- Cada nodo representará un usuario.
- Cada arista representará una conexión entre usuarios (si se conectan es que se siguen).

## Ejemplo

- Usuario A → Usuario B
- Usuario A → Usuario C
- Usuario B → Usuario D

Lo que se está representando mediante ese grafo es que:

- B sigue a A.
- C también sigue a A.
- D sigue a B.

Por lo tanto:

- Si A publica algo, lo verán B y C.
- Luego, si B decide compartirlo, D lo verá. En caso contrario, no.

## Ejemplo de iteraciones

- **Iteración 0:** A comparte.
- **Iteración 1:** B y C reciben el contenido.
- **Iteración 2:** Supongamos que B comparte y C ignora, entonces D recibe contenido.

Por lo tanto, la propagación depende de:

- La estructura de la red.
- Las probabilidades.
- Qué usuarios comparten.

---

# Alcance del proyecto

## Se incluirá

- Simulación offline.
- Propagación probabilística.
- Distribución de usuarios entre procesos MPI.
- Comunicación entre procesos.
- Análisis de rendimiento.

## No se incluirá

- Interfaz gráfica compleja.
- Conexiones reales de red.
- Bases de datos.
- Algoritmos avanzados de IA.
- Redes sociales reales.

---

# Desarrollo de la versión secuencial

La primera etapa del proyecto será desarrollar la versión secuencial completa de la simulación, con el objetivo de implementar el comportamiento básico de propagación viral sin utilizar paralelismo.

## Estructuras principales

### Usuario

- id
- estado actual
- lista de conexiones
- probabilidad de compartir

### Red Social

- Lista de usuarios: `[A, B, C, D]`
- Lista con las conexiones: `[A: B, C]`

Esto representa que el usuario A tiene como seguidores a B y C.

---

# Funcionamiento de la simulación

## Paso 1

Generar la red:

- Crear usuarios.
- Crear conexiones aleatorias.

## Paso 2

Seleccionar un usuario inicial que comparte el contenido.

## Paso 3: Iteraciones

Por cada iteración:

1. Recorrer usuarios activos.
2. Determinar si comparten el contenido.
3. Propagar el contenido a sus conexiones.
4. Actualizar estados.
5. Registrar estadísticas.

---

# Resultados de la versión secuencial

La simulación debe permitir observar:

- Cómo fue creciendo la propagación.
- Los usuarios alcanzados en cada iteración.

---

# Análisis de paralelización

Una vez implementada la versión secuencial, se realizará el análisis de paralelización.

Es decir, identificar las partes paralelizables del problema, donde distintos grupos de usuarios puedan procesarse independientemente.

Cada proceso podrá administrar una parte de la red social.

---

# Estrategia de división

La red será dividida mediante procesos MPI:

- **Proceso P0** → Usuarios `[0 - 2499]`
- **Proceso P1** → Usuarios `[2500 - 4999]`
- **Proceso P2** → Usuarios `[5000 - 7499]`
- **Proceso P3** → Usuarios `[7500 - 9999]`

Cada proceso será responsable de:

- Actualizar los estados de sus usuarios.
- Procesar propagaciones locales.
- Enviar eventos a otros procesos.

---

# Comunicación entre procesos

La comunicación ocurrirá cuando un usuario comparta contenido con seguidores pertenecientes a otro proceso.

Por ejemplo:

> “Usuario 120 comparte contenido, un seguidor pertenece al proceso 2, entonces se envía el evento al proceso 2.”

---

# Posibles problemas

- Overhead de comunicación.
- Balanceo de carga.
- Sincronización entre procesos.
- Cantidad de mensajes intercambiados.

---

# Diseño experimental

Posteriormente se realizará el análisis experimental del rendimiento utilizando distintas variables:

- Cantidad de usuarios.
- Cantidad de procesos.
- Densidad de conexiones.
- Número de iteraciones.

También se realizará una comparación entre:

- Tiempos secuenciales.
- Tiempos paralelos.

Calculando:

- Speedup.
- Eficiencia.

---

# Conclusión

El proyecto propuesto permite abordar un problema de propagación de información utilizando técnicas de programación paralela distribuida mediante MPI.

La simulación presenta paralelismo natural debido a la división de usuarios entre procesos y la necesidad de comunicación para propagar eventos entre distintas particiones de la red social.

Además del interés conceptual del problema, el proyecto permitirá realizar análisis de rendimiento, escalabilidad y comunicación distribuida, alineándose con los objetivos de la materia.