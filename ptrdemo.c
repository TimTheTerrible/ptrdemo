/*
    ptrdemo.c

    This porgram demonstrates various ways to use pointers to
    dynamically allocated memory. It started out as a desperate
    effort on my part to solve the mystery of how to address
    an array of pointers to complex structures, as well as the
    semantics of passing a reference to such an array into a
    function.

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

#include <stdio.h>
#include <stdlib.h>
#include "ptrdemo.h"

#define NUM_INTS 5
#define NUM_STRUCTS 5

/*
    int_pointer()

    int_pointer() demonstrates how to allocate space for an
    integer value and how to reference it. This is brain-dead
    simple, but it's included for completeness.
*/
void
int_pointer ( void )
{
    int *someint;

    printf("Pointer to an integer\n");
    printf("allocating int *someint...\n");
    someint = (int *)malloc(sizeof(int));

    printf("setting someint...\n");
    *someint = 123;

    printf("someint is %d\n", *someint);

    free(someint);

    printf("\n");
}

/*
    int_array_pointer()

    int_array_pointer() demonstrates how to allocate space for an
    array of integer values and how to reference the array, as well
    as the integers inside. This one is a little trickier, but still
    simple. It's also included for completeness.
*/
void
int_array_pointer ( void )
{
    int i;
    int *someints;

    printf("Pointer to an array of integers\n");
    printf("allocating int *someints...\n");

    /* allocate enough space to hold all the integers, and typ-
    cast it as a pointer to an integer, which is identical to a
    pointer to an array of integers, since C's array handling is
    done with pointers even on statically declared arrays. */
    someints = (int *)malloc(sizeof(int) * NUM_INTS);

    printf("setting values...\n");
    for ( i = 0; i < NUM_INTS; i++ ) {
        printf("setting (int)someints[%d]...\n", i);

        /* notice how this looks just like how you access a statically
        declared array of pointers. */

        someints[i] = i;
    }

    printf("showing values...\n");
    for ( i = 0; i < NUM_INTS; i++ ) {
        printf("someints[%d] = %d\n", i, someints[i]);
    }

    free(someints);

    printf("\n");
}

/*
    int_ptr_array_pointer()

    int_ptr_array_pointer() demonstrates how to allocate space for an
    array of pointers to integer values and how to reference the array,
    the pointers it contains, as well as the integers the pointers point to.
    This one is quite tricky, so look closely at how the integer values are
    finally referenced.
*/
void
int_ptr_array_pointer ( void )
{
    int i;
    int **someints;

    printf("Pointer to an array of pointers to integers\n");
    printf("allocating int **someints...\n");

    /* allocate enough space to hold a pointer for each integer.
    Coincidentally, a pointer and an integer are the same size on Intel-
    based architectures, so this block will be the same size as the one
    allocated in the previous example. */

    someints = (int **)malloc(sizeof(int *) * NUM_INTS);

    for ( i = 0; i < NUM_INTS; i++ ) {
        printf("allocating someints[%d]...\n", i);

        /* allocate space to hold an integer, and stick the address into
        the array of pointers. */

        someints[i] = (int *)malloc(sizeof(int));

        printf("setting *someints[%d] to %d...\n", i, i);

        /* here's how it works: "someints" is a pointer to the space in
        memory that holds the array; "someints[i]" is is a pointer to
        the space in memory that holds the i'th integer. To set or get
        the array, use "someints". To set or get an element in the array
        (pointers, not integers), use "someints[i]", and finally, to set
        or get the value of the i'th integer, stick a "*" in front of
        "someints[i]", which tells the compiler "I want, not the pointer
        value in someints[i], but rather the value of the thing that
        someints[i] points to." */

        *someints[i] = i;
    }

    printf("showing values...\n");
    for ( i = 0; i < NUM_INTS; i++ ) {
        printf("*someints[%d] = %d\n", i, *someints[i]);
    }

    for ( i = 0; i < NUM_INTS; i++ ) {
        free(someints[i]);
    }
    free(someints);

    printf("\n");
}

/*
    struct_pointer()

    struct_pointer() demonstrates how to allocate space for a
    structure, as well as how to reference the contents of the
    structure.
*/
void
struct_pointer ( void )
{
    pStruct somestruct;

    printf("Pointer to a structure\n");
    printf("allocating tStruct *somestruct...\n");
    somestruct = (pStruct)malloc(sizeof(tStruct));

    printf("setting somestruct...\n");

    /*

    the difference between accessing the elements of a static
    struct and a dynamic struct is the separator: "->" vs. ".".
    Just so you know:
        somestruct->anint
    and
        (*somestruct).anint
    and
        (tStruct *)(&somestruct)->anint
    are functionally identical.

    */

    somestruct->anint = 123;
    somestruct->anotherint = 234;

    printf("showing values...\n");
    printf("somestruct->anint is %d\n", somestruct->anint);
    printf("somestruct->anotherint is %d\n", somestruct->anotherint);

    free(somestruct);

    printf("\n");
}

/*
    struct_array_pointer()

    struct_array_pointer() demonstrates how to allocate space for an
    array of structures, as well as how to access the contents of each
    structure.
*/
void
struct_array_pointer ( void )
{
    int i;
    pStructArray somestructs;

    printf("Pointer to an array of structures\n");
    printf("allocating pStructArray somestructs...\n");
    somestructs = (pStructArray)malloc(sizeof(tStruct) * NUM_STRUCTS);

    printf("setting values...\n");
    for ( i = 0; i < NUM_STRUCTS; i++ ) {
        printf("setting tStruct %d...\n", i);

        /*

        this is really confusing: if this is a pointer operation,
        home come we use the period to access the struct members,
        instead of the "->" thingy? The answer is that the pointer
        is only talking about the array, not the structs. We're not
        using anything that points to a struct, just an array. Since
        array operations are handled as pointer operations anyway,
        this looks suspiciously like we're working with a statically
        declared array of structs.

        I have to admit that this was by far the hardest one to figure
        out, possibly because it's so simple. This one function took
        about four hours of fumfering to get it to compile and not
        cause a SIGSEGV. :-/ At one point i actually tried

            (int)(*(tStruct *)(*someints)[i].anint)

        Egad!

        */

        somestructs[i].anint = i;
        somestructs[i].anotherint = i + 69;
    }

    printf("showing values...\n");
    for ( i = 0; i < NUM_STRUCTS; i++ ) {
        printf("somestructs[%d].anint = %d\n", i, somestructs[i].anint);
        printf("somestructs[%d].anotherint = %d\n", i, somestructs[i].anotherint);
    }

    free(somestructs);

    printf("\n");
}

/*
    struct_ptr_array_pointer()

    struct_ptr_array_pointer() demonstrates how to allocate space for
    an array of pointers to structs. It also shows how to pass a pointer
    into a function, both by value and by reference. I'll explain what
    the difference is in the example functions below.

*/
void
struct_ptr_array_pointer ( void )
{
    int i;
    pStructPtrArray mystructs;

    printf("Pointer to an array of structures\n");

    /*

    Call a function, passing it the address of our uninitialized pointer.
    The function will allocate space for an array of pointers to structs,
    then allocate space for the structs and save the pointers in the array.
    Since we're passing the pointer by reference, which is to say we're
    passing in a pointer to our pointer, when the function returns, our
    pointer will point to the memory allocated by the function, which will
    contain the array of pointers.

    */

    make_struct_ptr_array_pointer( &mystructs );

    /*

    Now pass our pointer by value to a function which will display the
    contents of the structs. Unlike in the previous call, where we passed
    the address of our pointer, now we're passing the value, so that the
    function can find the stuff that out pointer points to.

    */

    show_struct_ptr_array_pointer( mystructs );

    for ( i = 0; i < NUM_INTS; i++ ) {
        free(mystructs[i]);
    }

    free(mystructs);

}

/*
    make_struct_ptr_array_pointer()

    make_struct_ptr_array_pointer() demonstrates how to allocate space
    for an array of pointers to structs, how to allocate space for the
    structs and how to access the struct members. Finally, this function
    shows how to set the value of an external pointer when it's address
    has been passed in.
*/
void
make_struct_ptr_array_pointer ( pStructPtrArray * somestructs )
{
    int i;
    pStructPtrArray localstructs;

    printf("allocating pStructPtrArray localstructs...\n");

    /*

    First, allocate some space for the array, saving the pointer in
    localstructs. We could skip using localstructs and just save the
    value in somestructs, but since somestructs is techincally declared
        tStruct *** somestruct
    the syntax for working with the struct members gets ugly.

    */

    localstructs = (pStructPtrArray)malloc(sizeof(pStruct) * NUM_INTS);

    for ( i = 0; i < NUM_INTS; i++ ) {
        printf("allocating localstructs[%d]...\n", i);
        localstructs[i] = (pStruct)malloc(sizeof(tStruct));

        printf("setting localstructs[%d]->anint to %d...\n", i, i);

        /*

        Ok, here we are again. Now why are we using the "->" thingy, when
        before we got away with using the period? Simple: just like when we
        were using a pointer to a single structure and we had to use "->",
        now, once the array is out of the way, we're still using a pointer
        to a structure, thus "->".

        If you want to use the ".", you just derefernce the pointer aspect of
        the array element so it produces a structure, rather than a pointer to
        a structure. Instead of
            localstructs[i]->anint
        we could use
            (*localstructs[i]).anint
        but that's two more characters to type and it's ugly as hell.

        */

        localstructs[i]->anint = i;
        printf("localstructs[%d]->anint = %d\n", i, localstructs[i]->anint);

        printf("setting localstructs[%d]->anotherint to %d...\n", i, i + 69);
        localstructs[i]->anotherint = i + 69;
        printf("localstructs[%d]->anotherint = %d\n", i, localstructs[i]->anotherint);
    }

    /*

    Now for the tricky part: somestructs is a pointer to, not an array
    of pointers, but to a pointer to an array of pointers. So, we stick a "*"
    on the front of somestructs to make the assignment store the value of
    localstructs (returned from malloc(), points to the array of pointers)
    into the variable mystructs declared by the calling function,
    struct_ptr_array_pointer(), pointed to by our local variable somestructs.

    */

    *somestructs = localstructs;

    printf("\n");
}

/*
    show_struct_ptr_array_pointer()

    show_struct_ptr_array_pointer() demonstrates how to access the pointers
    in an array of pointers, as well as the members of the structs the pointers
    point to. It also shows how to use a pointer passed into a function.
*/
void
show_struct_ptr_array_pointer ( pStructPtrArray somestructs )
{
    int i;

    printf("showing pStructPtrArray somestructs...\n");
    for ( i = 0; i < NUM_INTS; i++ ) {

        /*

        Nothing tricky here. From inside here, our parameter somestructs
        looks just like the calling function's local variable mystructs, so
        we access the array the same way.

        */

        printf("somestructs[%d]->anint = %d\n", i, somestructs[i]->anint);
        printf("somestructs[%d]->anotherint = %d\n", i, somestructs[i]->anotherint);
    }

    printf("\n");
}

int
main ( void )
{
    int_pointer();
    int_array_pointer();
    int_ptr_array_pointer();
    struct_pointer();
    struct_array_pointer();
    struct_ptr_array_pointer();

    return 0;
}
