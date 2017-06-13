/*
    ptrdemo.h

    See ptrdemo.c fore explanation.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
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

