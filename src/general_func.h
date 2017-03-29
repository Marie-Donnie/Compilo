#ifndef GENERAL_FUNC_H
#define GENERAL_FUNC_H

#include <stdbool.h>
#include <stdio.h>

/** \fn long char_count(FILE *file)
 *  \brief Counts the characters in a file.
 *  \param file the file pointer to the file to process
 *  \return the number of characters
 */
long char_count(FILE *file);
char* read_file(char *path);
void* check_malloc(size_t size);
void* check_realloc(void* p, size_t size);
void fail(char *msg);

void eat_space();

bool might_be_double(char c);
bool is_double(char c, char cc);

/*------------------- SCAN -------------------------*/
void scan(char* chaine);

#endif //GENERAL_FUNC_H
