/**
 *  LANGUAGE.H
 *
 *  Librería básica de manejo de lenguajes.
 *
 *  Autor: Jardón Fonseca Bruno
 *  https://github.com/bjardon
 *
 */

#ifndef PRACTICA02_OPERACIONESLENGUAJES_LANGUAGE_H_H
#define PRACTICA02_OPERACIONESLENGUAJES_LANGUAGE_H_H


#include <stdlib.h>
#include <stdio.h>
#include "mystring.h"



typedef struct _word
{
    char value[255];
    struct _word * next;
    struct _word * prev;
} _Word;
typedef _Word * Word;

typedef struct _lang
{
    struct _word * first;
} Lang;

// Function declarations
void lang_addf(Lang *, char *);
void lang_add(Lang *, string);
void lang_del(Lang *, int);
Word lang_get(Lang *, int);
int lang_contains(Lang *, char *);
int lang_isempty(Lang *);
int lang_count(Lang *);
void lang_print(Lang *list);
void lang_union(Lang *, Lang *);

void lang_addf(Lang *lang, char *value) {
    Word element;

    element = (Word)malloc(sizeof(_Word));

    str_copy(element->value, value);
    lang->first = element;
}

void lang_add(Lang *lang, string value) {
    if(!lang_isempty(lang)) {
        Word element;
        Word aux;

        element = (Word)malloc(sizeof(_Word));

        str_copy(element->value, value);
        aux = lang->first;

        while(aux->next)
            aux = aux->next;

        element->next = aux->next;
        aux->next = element;
    }
    else
        lang_addf(lang, value);
}

void lang_del(Lang *lang, int index) {
    if(!lang_isempty(lang)) {
        Word element = lang_get(lang, index);
        Word prev = lang_get(lang, index - 1);
        Word next = element->next;

        if(prev)
            prev->next = next;
        if(next)
            next->prev = prev;

        free(element);
    }
}

Word lang_get(Lang *lang, int index) {
    Word aux = lang->first;
    int i = 0;

    while(aux->next) {
        if(i == index)
            return aux;

        aux = aux->next;
        i++;
    }

    return aux;
}

int lang_contains(Lang *lang, char *value) {
    Word aux = lang->first;
    int i = 0;

    while(aux) {
        if(str_compare(aux->value, value))
            return 1;

        i++;
        aux = aux->next;
    }

    return 0;
}

int lang_isempty(Lang *lang) {
    if(lang->first != NULL)
        return 0;
    return 1;
}

int lang_count(Lang *lang) {
    int i = 1;
    Word aux = lang->first;

    if(lang->first)
        while(aux->next)
        {
            i++;
            aux = aux->next;
        }
    else
        return 0;

    return i;
}

void lang_print(Lang *list) {
    Word aux = list->first;
    printf("\n");

    while(aux) {
        printf("\nPalabra [%p]:\t %s",aux, aux->value);
        aux = aux->next;
    }

    printf("\n");
}


void lang_union(Lang *destination, Lang *origin) {
    for (int i = 0; i < lang_count(origin); ++i) {
        lang_add(destination, lang_get(origin, i)->value);
    }
}
#endif //PRACTICA02_OPERACIONESLENGUAJES_LANGUAGE_H_H
