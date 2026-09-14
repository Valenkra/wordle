# Wordle

Implementación en C++ del juego Wordle: hay que adivinar una palabra secreta de 5 letras en 6 intentos, recibiendo pistas sobre qué letras están bien ubicadas, cuáles están en la palabra pero en otra posición, y cuáles no están.

## Requisitos

- CMake (versión 3.10 o superior)
- Un compilador de C++ compatible con C++17
- Make (o el generador que use CMake en tu sistema)

## Estructura del proyecto

```
wordle/
├── CMakeLists.txt
├── lib.h              # Declaraciones de las funciones principales
├── lib.cpp            # Implementación de la lógica del juego
├── main.cpp           # Juego interactivo
├── listado.txt         # Listado de palabras válidas
└── tests/
    ├── tests.cpp
    ├── listado_test_lleno.txt
    └── listado_test_vacio.txt
```

## Compilación

Desde la raíz del proyecto:

```bash
cmake -S . -B build
cmake --build build
```

Esto genera dos ejecutables dentro de `build/`:

- **`wordle`**: el juego interactivo.
- **`tests`**: la suite de tests.

## Cómo jugar

Desde la carpeta `build/`:

```bash
./wordle
```

El juego elige una palabra secreta al azar del listado y hay que adivinarla en 6 intentos. Después de cada intento válido se muestra una respuesta con:

- `+` : la letra está en la posición correcta.
- `-` : la letra está en la palabra, pero en otra posición.
- `X` : la letra no está en la palabra.

Un intento solo es válido si tiene la misma longitud que la palabra secreta y si está dentro del listado de palabras.

## Cómo correr los tests

Los tests **deben ejecutarse desde la carpeta `build/`**, porque el archivo `tests/tests.cpp` usa rutas relativas (`../tests/...`) para acceder a los listados de prueba. Ejecutarlos desde otro directorio (por ejemplo, desde la raíz del proyecto) hace que no encuentre esos archivos y los tests fallen.

```bash
cd build
ctest --output-on-failure
```

`--output-on-failure` muestra el detalle completo de cualquier test que falle, sin ensuciar la salida cuando todo pasa correctamente.

También se puede correr el ejecutable de tests directamente (siempre desde `build/`):

```bash
cd build
./tests
```

## Funciones principales (`lib.h` / `lib.cpp`)

- **`cargar_listado(nombre_archivo)`**: lee un archivo con una palabra por línea y devuelve un `vector<string>` con las palabras válidas. Si el archivo no se puede abrir, devuelve un vector vacío.
- **`intento_valido(intento, palabra_secreta, listado)`**: indica si un intento es válido (misma longitud que la palabra secreta y presente en el listado).
- **`evaluar_intento(intento, palabra_secreta)`**: compara letra por letra el intento contra la palabra secreta y devuelve un `vector<EstadoLetra>` indicando el resultado de cada posición. Resuelve correctamente los casos con letras repetidas.
- **`respuesta_en_string(respuesta)`**: convierte el resultado de `evaluar_intento` a un string legible (`+`, `-`, `X`).

## Notas

- El listado de palabras no debe contener tildes ni la letra `ñ`, ya que la lógica de evaluación asume codificación ASCII (`a`-`z` en minúscula).
