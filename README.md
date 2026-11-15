cat << 'EOF' > README.md
# mish - Mini Shell

Un shell minimalista para sistemas tipo Unix escrito en C11 desde cero.

## Características actuales
- Bucle REPL con lectura dinámica de líneas (`getline`).
- Ejecución de comandos externos con búsqueda en `$PATH` (`fork`, `execvp`, `waitpid`).
- Comandos internos (*built-ins*): `cd`, `help`, `exit`.
- Redirección de entrada y salida estándar (`<`, `>`).

## Compilación y ejecución

Con entorno reproducible de Nix:
```bash
nix develop
make
./mish
```
o con gcc y make:
```bash
make
./mish
```
