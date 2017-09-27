#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "dictionary.h"

Dictionary* create_dictionary() {
    Dictionary *tmp = (Dictionary*) malloc(sizeof(Dictionary));
    if (!tmp) return NULL;
    tmp->size = 0;
    tmp->head = tmp->tail = NULL;
 
    return tmp;
}


void delete_dictionary(Dictionary **dict) {
    Node *tmp = (*dict)->head;
    Node *next = NULL;
    while (tmp) {
        next = tmp->next;
        free(tmp->key);
        free(tmp->value);
        free(tmp);
        tmp = next;
    }
    free(*dict);
    (*dict) = NULL;
}



void* push_front(Dictionary *dict, void* key, size_t key_size, void* value, size_t value_size) {
    Node *tmp = (Node*) malloc(sizeof(Node));
    if (!tmp) return NULL;
   
    tmp->key = (void *)malloc(key_size); 
    if (!tmp->key) return NULL;
    strcpy(tmp->key, key);
    
    tmp->value = (void *)malloc(value_size); 
    if (!tmp->value) return NULL;
    strcpy(tmp->value, value);
   
    tmp->next = dict->head;
    tmp->prev = NULL;
    if (dict->head) {
        dict->head->prev = tmp;
    }
    dict->head = tmp;
 
    if (dict->tail == NULL) {
        dict->tail = tmp;
    }
    dict->size++;

    return tmp;
}



void* pop_front(Dictionary *dict) {
    Node *prev;
    void *tmp;
    if (dict->head == NULL) {
        return NULL;
    }
 
    prev = dict->head;
    dict->head = dict->head->next;
    if (dict->head) {
        dict->head->prev = NULL;
    }
    if (prev == dict->tail) {
        dict->tail = NULL;
    }
    free(prev->key);
    free(prev->value);
    free(prev);
 
    dict->size--;
    return tmp;
}



void* push_back(Dictionary *dict, void* key, size_t key_size, void* value, size_t value_size) {
    Node *tmp = (Node*) malloc(sizeof(Node));
	if (!tmp) return NULL;
    tmp->key = (void *)malloc(key_size); 
    if (!tmp->key) return NULL;
    tmp->value = (void *)malloc(value_size); 
    if (!tmp->value) return NULL;
    strcpy(tmp->value, value);
    tmp->next = NULL;
    tmp->prev = dict->tail;
    if (dict->tail) {
        dict->tail->next = tmp;
    }
    dict->tail = tmp;
 
    if (dict->head == NULL) {
        dict->head = tmp;
    }
    dict->size++;

    return tmp;
}

 
void* pop_back(Dictionary *dict) {
    Node *next;
    void *tmp;
    if (!(dict->tail)) return NULL;
 
    next = dict->tail;
    dict->tail = dict->tail->prev;
    if (dict->tail) {
        dict->tail->next = NULL;
    }
    if (next == dict->head) {
        dict->head = NULL;
    }
    free(next->key);
    free(next->value);
    free(next);
 
    dict->size--;
    return tmp;
}



Node* get_nth(Dictionary *dict, size_t index) {
    Node *tmp = dict->head;
    size_t i = 0;
 
    while (tmp && i < index) {
        tmp = tmp->next;
        i++;
    }
 
    return tmp;
}


Node* get_nthq(Dictionary *dict, size_t index) {
    Node *tmp = NULL;
    size_t i;
     
    if (index < dict->size/2) {
        i = 0;
        tmp = dict->head;
        while (tmp && i < index) {
            tmp = tmp->next;
            i++;
        }
    } else {
        i = dict->size - 1;
        tmp = dict->tail;
        while (tmp && i > index) {
            tmp = tmp->prev;
            i--;
        }
    }
 
    return tmp;
}


void* insert_nth(Dictionary *dict, size_t index, void* key, size_t key_size, void* value, size_t value_size) {
    Node *elm = NULL;
    Node *ins = NULL;
    elm = get_nth(dict, index);
    if (!(elm)) return NULL;
   
    ins = (Node*) malloc(sizeof(Node));
    if (ins == NULL) return NULL;
   
    ins->key = (void *)malloc(key_size); 
    if (!ins->key) return NULL;
    strcpy(ins->key, key);
   
    ins->value = (void *)malloc(value_size); 
    if (!ins->value) return NULL;
    strcpy(ins->value, value);
   
    ins->prev = elm;
    ins->next = elm->next;
    if (elm->next) {
        elm->next->prev = ins;
    }
    elm->next = ins;
 
    if (!elm->prev) {
        dict->head = elm;
    }
    if (!elm->next) {
        dict->tail = elm;
    }
 
    dict->size++;

    return ins;
}


void* delete_nth(Dictionary *dict, size_t index) {
    Node *elm = NULL;
    void *tmp = NULL;
    elm = get_nth(dict, index);
    if (!(elm)) return NULL;
    if (elm->prev) {
        elm->prev->next = elm->next;
    }
    if (elm->next) {
        elm->next->prev = elm->prev;
    }
    tmp = elm->value;
 
    if (!elm->prev) {
        dict->head = elm->next;
    }
    if (!elm->next) {
        dict->tail = elm->prev;
    }
 
    free(elm->key);
    free(elm->value);
    free(elm);
 
    dict->size--;
 
    return tmp;
}


void* delete_node(Dictionary *dict, Node* n) {
    Node *elm = n;
    void *tmp = NULL;
    if (!(elm)) return NULL;
    if (elm->prev) {
        elm->prev->next = elm->next;
    }
    if (elm->next) {
        elm->next->prev = elm->prev;
    }
    tmp = elm->value;
 
    if (!elm->prev) {
        dict->head = elm->next;
    }
    if (!elm->next) {
        dict->tail = elm->prev;
    }
 
    free(elm->key);
    free(elm->value);
    free(elm);
 
    dict->size--;
 
    return tmp;
}


void print_dictionary(Dictionary *dict, void (*fun)(void*, void*)) {
    Node *tmp = dict->head;
    while (tmp) {
        fun(tmp->key, tmp->value);
        tmp = tmp->next;
        printf("\n");
    }
}


Node* has_key(Dictionary *dict, void* key) {
    if (!dict->head) return NULL;
    Node *tmp = dict->head;
    while (tmp) {
        if(strcmp(tmp->key, key) == 0) {
            return tmp;
        }
        tmp = tmp->next;
    }
        
    return NULL;
}


Node* has_value(Dictionary *dict, void* value) {
    if (!dict->head) return NULL;
    Node *tmp = dict->head;
    while (tmp) {
        if(*(int*)tmp->value == *(int*)value) {
            return tmp;
        }
        tmp = tmp->next;
    }
        
    return NULL;
}


void* get_key(Node* n) {
	return n->key;
}


void* get_value(Node* n) {
	return n->value;
}


void change_key(Node* n, void (*fun)(void*)) {
	fun(n->key);
}


void change_value(Node* n, void (*fun)(void*)) {
	fun(n->value);
}


