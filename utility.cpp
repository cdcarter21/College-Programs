/* --------------------------------------------------------------------
    Developer---Cole Carter
    Course------CS2233 Data Structures & Algorithms
    Project-----Pointer Practice
    Due---------September 13, 2022
----------------------------------------------------------------------*/

/*fills n elements of an array that pointer p is pointing to with the value v by traversing
the array through a for loop and assigning v into each element.*/
void arrayFill(int *p, int n, int v)
{
    for(int i = 0; i < n; i++)
    {
        *(p + i) = v;
    }
}
/*reverses n elements of an array by using the pointer p along with another pointer q and
a holding variable to swap the values of the pointers as p moves up and q moves down.*/
void arrayReverse(int *p, int n)
{
    int *q = p + (n-1);
    int hold = *p;
    while (p < q)
    {
        hold = *p;
        *p = *q;
        *q = hold;
        p++;
        q--;
    }
}
/*copies n consecutive elements of an array by having the element p is pointing to contain
the value of what q is pointing to as they each move up by one.*/
 void arrayCopy(int *p, int n, int *q)
{
    for (int i = 0; i < n; i++)
    {
        *p = *q; 
        p++;
        q++;
    }
}
/*checks to see if n consecutive elements of an array being pointed to by p and q are equal
by seeing if the dereferenced values of p and q are equal as they each move up by one.*/
bool arrayEqual(int *p, int n, int *q)
{
    for (int i = 0; i < n; i++)
    {
        if (*p != *q)
            return false;
        p++;
        q++;
    }
    return true;
}