#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>
#include "dictionary.h"


void print_node(void* key, void* value);
void fskipchars(FILE*);
void inc_value(void*);


int main(int argc, char** argv) {
	if (argc < 3) {
		perror("Недостаточно аргументов командной строки.");
		exit(0);
	}

    int border_of_repeating;
    if (!sscanf(argv[1], "%d", &border_of_repeating)) {
        perror("Не удалось распознать требуемое количество вхождений слов.");
        exit(0);
    }; 

	FILE* input;
	char* file_name = argv[2];
  	
  	if ((input = fopen(file_name, "r")) == NULL) { 
  		perror("Не удалось открыть файл.");
		exit(0);
	} 
  	
	Dictionary *dict = create_dictionary(); 
    if (!dict){
        perror("Не удалось создать место для хранения записей.");
        exit(1);
    }

    char c;    
    char word[137];
    int i = 0;
    int sentence_count = 0;

    while ((c = fgetc(input)) != EOF) {
        if (!ispunct(c) && !isspace(c)) {
            word[i] = c;
            i++;
        }
        else {
            if (c == '.' || c == '!' || c == '?')
                ++sentence_count;

            word[i] = '\0';

            Node* n = has_key(dict, word);
            if(!n) {
                int inclusion = 1;
                size_t word_size = strlen(word) * sizeof(char);
                size_t inclusion_size = sizeof(inclusion);
                if(!push_front(dict, word, word_size, &inclusion, inclusion_size)) { 
                    perror("Не удалось создать новую запись.");
                    exit(1);
                }
            }
            else { 
                change_value(n, inc_value);
            } 
            fskipchars(input);
            i = 0;
        }
    } 

    for (i = border_of_repeating; i > 0; i--) {
        Node* n;
        while (n = has_value(dict, &i)) {
            delete_node(dict, n);    
        }
    }

    print_dictionary(dict, print_node);

    delete_dictionary(&dict);
  	fclose(input);

  	return 0;

}


void print_node(void* key, void* value) {
    printf("%s %d", (char*) key, *((int*) value));
}

void fskipchars(FILE* input) {
    char c;   
    while((c = fgetc(input)) != EOF)
        if(!ispunct(c) && !isspace(c)) break;
    if(c != EOF) ungetc(c, input);
} 

void inc_value(void* value) {
    *((int*) value) += 1;
}