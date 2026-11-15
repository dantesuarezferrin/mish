#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
/**
 * @brief Tokeniza una cadena de entrada en un arreglo de argumentos terminado en NULL.
 *
 * Divide la línea utilizando espacios, tabulaciones y saltos de línea como
 * delimitadores. La cadena original es modificada en el lugar (in-place)
 * reemplazando los delimitadores por caracteres nulos ('\0').
 *
 * @note Los elementos del arreglo devuelto apuntan directamente dentro del búfer
 *       @p line, por lo que @p line debe permanecer válido mientras se utilice
 *       el arreglo resultante.
 *
 * @param line Cadena terminada en '\0' con la entrada cruda a procesar.
 *
 * @return Arreglo dinámico de punteros a cadenas terminado en NULL, o NULL si
 *         ocurre un error de asignación de memoria o @p line es NULL.
 *         El llamador es responsable de liberar este arreglo con free().
 */
char **parseLine(char *line);

#endif /* PARSER_H */
