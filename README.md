# mish — Minimal UNIX Shell

`mish` es un intérprete de comandos (shell) UNIX minimalista implementado desde cero en **C11** sobre **GNU/Linux**, utilizando exclusivamente llamadas al sistema (syscalls) POSIX sin dependencias externas.

El objetivo del proyecto es explorar en profundidad el ciclo de vida de los procesos, la gestión de descriptores de archivos, la comunicación entre procesos (IPC) y el manejo de señales en sistemas operativos tipo UNIX.

---

## Características

* **Bucle REPL interactivo:** Lectura dinámica de entrada estándar de longitud arbitraria (`getline`) sin desbordamientos de búfer.
* **Ejecución de binarios externos:** Creación y sincronización de procesos mediante el modelo `fork` + `execvp` + `waitpid`.
* **Comandos internos (*Built-ins*):**
  * `cd [directorio]`: Cambio de directorio de trabajo en el proceso actual del shell (`chdir`), con soporte por defecto para `$HOME`.
  * `help`: Información de uso y comandos disponibles.
  * `exit`: Terminación limpia del bucle principal y liberación de memoria.
* **Redirección de E/S (`<` y `>`):** Manipulación de la tabla de descriptores de archivos (`open`, `dup2`, `close`) para redirigir `stdin` y `stdout` antes de reemplazar la imagen del proceso.
* **Tuberías (*Pipelines* `|`):** Comunicación inter-proceso unidireccional (`pipe`) ejecutando dos comandos de forma concurrente y gestionando el cierre estricto de extremos para evitar bloqueos por `EOF`.
* **Manejo de señales (`SIGINT`):** Protección del proceso padre (`SIG_IGN`) frente a `Ctrl+C`, restaurando la acción por defecto (`SIG_DFL`) en los procesos hijos en primer plano.

---

## Arquitectura

El código fuente está desacoplado en cuatro módulos independientes dentro de `src/` e `include/`:

```text
mish/
├── include/
│   ├── builtins.h    # Interfaz de comandos internos
│   ├── executor.h    # Interfaz de ejecución, redirecciones y pipes
│   ├── parser.h      # Interfaz de tokenización
│   └── shell.h       # Interfaz del ciclo principal (REPL)
├── src/
│   ├── main.c        # Punto de entrada
│   ├── shell.c       # Bucle REPL, manejo de memoria de línea y señales
│   ├── parser.c      # Tokenización dinámica de argumentos
│   ├── executor.c    # Gestión de fork/exec/wait, dup2 y pipe
│   └── builtins.c    # Implementación de cd, help y exit
└── Makefile          # Compilación estricta con sanitizers
```

### Decisiones de diseño clave
* **Aislamiento de procesos y fallos:** En los procesos hijos, cualquier error previo o posterior a `execvp` finaliza mediante `_exit(EXIT_FAILURE)` en lugar de `exit()` o `return`, evitando vaciar búferes `stdio` duplicados o clonar accidentalmente el bucle REPL del padre.
* **Seguridad de memoria:** Compilado bajo `-Wall -Wextra -Werror -pedantic` junto con `AddressSanitizer` y `UndefinedBehaviorSanitizer` (`-fsanitize=address,undefined`) para garantizar cero fugas de memoria (*memory leaks*) ni accesos fuera de límites.

---

## Compilación y uso

### Requisitos
* Compilador compatible con **C11** (`gcc` o `clang`)
* `make`
* Entorno Linux / POSIX

### Construir y ejecutar
```bash
git clone https://github.com/dantesuarezferrin/mish.git
cd mish
make
./mish
```

### Ejemplos de uso
```bash
mish> ls -la | grep src
mish> cat src/shell.c | wc -l
mish> echo "Hola UNIX" > salida.txt
mish> sort < salida.txt
mish> cd ..
mish> exit
```

### Limpieza de artefactos
```bash
make clean
```

---

## Posibles extensiones futuras
* Soporte para tuberías encadenadas arbitrarias ($N$ comandos: `cmd1 | cmd2 | cmd3`).
* Operador de redirección en modo *append* (`>>`) y redirección de `stderr` (`2>`).
* Ejecución de procesos en segundo plano (`&`) y control de trabajos (*job control* con `SIGTSTP`).