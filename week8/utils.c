#include <stdio.h>
char flipChar(char c)
{
if ('a' <= c && c <= 'z') // a valid lowercase
    return 'z' - (c-'a') ; // c-’a’ is offset

if ('A' <= c && c <= 'Z') // a valid lowercase
    return 'Z' - (c-'A') ;

if ('0' <= c && c <= '9') // a valid lowercase
    return '9' - (c-'0') ;
return c; // wasn’t LC so leave alone
}

int approxEqual(float a, float reference, float tolerance){
    float lower = reference - tolerance;
    float upper = reference + tolerance;
    if(a >= lower && a <= upper){
        return 1;
    }
    return 0;
}
