# include <stdlib.h>
# include <ctype.h>
# include <stdio.h>

# define DICTIONARY_SIZE 1024

void insert(int *dictionary, int i) {
  dictionary[i/32] |= (1 << (i%32));
}

void delete(int *dictionary, int i) {
  dictionary[i/32] &= ~(1 << (i%32));
}

int search(int *dictionary, int i) {
  return dictionary[i/32] & (1 << (i%32));
} 

int main (void) {

  char op;
  int i;
  int *dictionary = calloc(sizeof(int), DICTIONARY_SIZE/sizeof(int));

  printf("___BitVector Dictionary___\n");
  printf("Let i be a number between 0 and %d.\n", DICTIONARY_SIZE-1);
  printf("\tOperations:\n");
  printf("\t\tI i : insert n.\n");
  printf("\t\tD i : delete n.\n");
  printf("\t\tS i : search for n.\n");
  printf("\nEnter CTRL-C to exit.\n\n");

  for(;;) {
    
    scanf("%c %d", &op, &i);
    getchar();

    op = toupper(op);

    if (i < 0 || i > DICTIONARY_SIZE-1) {
      printf("ERROR: key is out of range.\n");
      continue;
    }

    switch(op) {
      case 'I': 
        insert(dictionary, i); 
        break;
      case 'D':
        delete(dictionary, i);
        break;
      case 'S':
        printf("The dictionary does %scontain %d.\n", search(dictionary, i) ? "" : "not ", i);;
        break;
      default:
        printf("Unsupported operation.\n");
    }
  }

  return 0;
}
