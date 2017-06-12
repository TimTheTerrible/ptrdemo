/*
    ptrdemo.h

    See ptrdemo.c fore explanation.

*/

/* Define a simple structure */
typedef struct tStruct
{
    int anint;
    int anotherint;
}
tStruct;

/* Define some pointer types, to simplify declarations and
    typecasting */

/* a pointer to a tStruct */
typedef tStruct * pStruct;

/* a pointer to an array of tStructs. Look closely and notice that
    it's the same as the one above. C handles arrays as indexed
    pointers, so a pointer to one struct is the same as a pointer
    to a bunch of structs. */
typedef tStruct * pStructArray;

/* a pointer a an array of pointers to tStructs */
typedef tStruct ** pStructPtrArray;

/* function prototypes */
void make_struct_ptr_array_pointer ( tStruct ***somestructs );
void show_struct_ptr_array_pointer ( tStruct **somestructs );
void struct_array_pointer ( void );
void struct_pointer ( void );
void struct_ptr_array_pointer ( void );
int main ( void );

