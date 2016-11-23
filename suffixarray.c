#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct suffix
{
    int index;
    char *suff;
};

int *sa;

int compare(const void * s1, const void * s2)
{ 
  struct suffix *a = (struct suffix *)s1;
  struct suffix *b = (struct suffix *)s2;    
  return strcmp(a->suff, b->suff) < 0? 0 : 1;
}

int *constructSuffixArray(char *txt, int length)
{

    struct suffix suffixes[length];
 
    printf("Suffixes of the given input\n");
    for (int i = 0; i < length; i++)
    {
        suffixes[i].index = i;
        suffixes[i].suff = (txt+i);
        printf("%d : %s\n",suffixes[i].index,suffixes[i].suff);
    }
 
    qsort(suffixes, length, sizeof(struct suffix), compare);
    
    printf("Suffix arrays after sorting\n");
    for (int i = 0; i < length; i++)
    {
        printf("%d : %s\n",suffixes[i].index,suffixes[i].suff);
    }
    
    printf("\n");
    sa = (int *)malloc(length);
    for (int i = 0; i < length; i++)
    {
        sa[i] = suffixes[i].index;
    }
    
    return sa;
}


void printSuffixArray(int a[], int length)
{
    for(int i = 0; i < length; i++){
        printf("%d\n",a[i]);    
    }
}

int main()
{
    char txt[] = "banana";
    int length = strlen(txt);
    int *sa = constructSuffixArray(txt,  length);
    printf("The generated suffix array indices for %s:\n", txt);
    printSuffixArray(sa, length);
    return 0;
}

