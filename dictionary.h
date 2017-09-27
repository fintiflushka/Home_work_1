#include <stddef.h>


typedef struct _Node {
    void* key;
    void* value;
    struct _Node *next;
    struct _Node *prev; 
} Node;

typedef struct _Dictionary {
    size_t size;
    Node *head;
    Node *tail;
} Dictionary;


Dictionary* create_dictionary(); 
void delete_dictionary(Dictionary **dict); 
void* push_front(Dictionary *dict, void* key, size_t key_size, void* value, size_t value_size);
void* pop_front(Dictionary *dict);
void* push_back(Dictionary *dict, void* key, size_t key_size, void* value, size_t value_size);
void* pop_back(Dictionary *dict);
Node* get_nth(Dictionary *dict, size_t index);
Node* get_nthq(Dictionary *dict, size_t index);
void* insert_nth(Dictionary *dict, size_t index, void* key, size_t key_size, void* value, size_t value_size);
void* delete_nth(Dictionary *dict, size_t index);
void* delete_node(Dictionary *dict, Node* n);
void print_dictionary(Dictionary *dict, void (*fun)(void*, void*));
Node* has_key(Dictionary *dict, void* key);
Node* has_value(Dictionary *dict, void* value);
void* get_key(Node* n);
void* get_value(Node* n);
void change_key(Node* n, void (*fun)(void*));
void change_value(Node* n, void (*fun)(void*));