#include "parser.h"

/* Includes */
#include <string.h>
#include <stdlib.h>

/* Defines */
#define TOKEN_DELIMITERS " \t\r\n"
#define INITIAL_TOKEN_CAPACITY 64

char **parseLine(char *line){
	if(line == NULL)
		return NULL;
	
	char **params = malloc(sizeof(char *)*INITIAL_TOKEN_CAPACITY);
	char **tmp;
	if(params == NULL)
		return NULL;

	size_t nToken=0;
	size_t size = INITIAL_TOKEN_CAPACITY;
	char *token;
	
	token = strtok(line, TOKEN_DELIMITERS);

	while( token != NULL ){
		if(nToken >= size -1){
			size*=2;
			tmp = realloc(params, size*sizeof(char*));
			if(tmp==NULL){
				free(params);
				return NULL;
			}
			params=tmp;
		}
		params[nToken++] = token;
		token = strtok(NULL, TOKEN_DELIMITERS);
	}
	params[nToken] = NULL;
	
	return params;
}
