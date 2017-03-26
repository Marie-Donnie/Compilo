#include "scanner.h"

FILE *file;

void eat_space(){

}

int char_count(char *file_name){
  FILE *file;
  char c;
  int count = 0;
  file = fopen(file_name, "r");
  while ((c=fgetc(file))!=EOF){
    count++;
  }
  fclose(file);
  return count;
}

/*------------------- SCAN -------------------------*/

Lexical_unit* scan(char* chaine){

  /* Terminal si " " ou entier, NT tout le reste qui n'est pas blanc */
  /* On accepte pas un nom de variable type 1toto, mais toto1 oui */
  /* Construit trois listes différentes pour blancs (nouvelle page, espace, retour chariot, etc.), unité lexicale (tout ce qui n'est pas un blanc), et les opérateurs */



  /* int memory_read;    /\*this will be used as the variable for the value of the bytes read from the getline function*\/ */

  /* int nbytes = 200;    /\*this is the variable for the number of bytes initially allocated for your stream*\/ */

  /* char *your_string;    /\*this is the variable for the character file object used for your stream*\/ */

  /* puts (“Enter stream, or line of text, here:”);    /\*prompt for user to enter text*\/ */

  /* your_string = (char *) malloc (nbytes + 1);    /\*note the char cast operator as the pointer used will be a character pointer and also note that it’s added 1 to nbytes for the malloc function; the last character read by getline should be a null character and it’s added the one to account for the last null character that will be read*\/ */

  /* memory_read = getline (&your_string, &nbytes, stdin);     /\*the value of memory read will be determined by the return of your getline function*\/ */

  /* if (memory_read == -1) { /\* if a character is not read by getline, then -1 will be returned*\/ */
  /*     puts (“Error: only EOF without text read”);    /\*displays error no bytes had been read, hence, if -1 had been returned*\/ */
  /* } */

  /* else {  /\*if -1 had not been returned*\/ */
  /*   puts (your_string);   /\*displays string that had been entered*\/ */




  //}

}
