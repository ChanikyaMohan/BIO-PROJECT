#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


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

int comp (const void * elem1, const void * elem2) 
{
    int f = *((int*)elem1);
    int s = *((int*)elem2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}

int *constructSuffixArray(char *txt, int length)
{
    int i;
    struct suffix suffixes[length];
 
    printf("Suffixes of the given input\n");
    for ( i = 0; i < length; i++)
    {
        suffixes[i].index = i;
        suffixes[i].suff = (txt+i);
        printf("%d : %s\n",suffixes[i].index,suffixes[i].suff);
    }
 
    qsort(suffixes, length, sizeof(struct suffix), compare);
    
    printf("Suffix arrays after sorting\n");
    for (i = 0; i < length; i++)
    {
        printf("%d : %s\n",suffixes[i].index,suffixes[i].suff);
    }
    
    printf("\n");
    sa = (int *)malloc(length);
    for (i = 0; i < length; i++)
    {
        sa[i] = suffixes[i].index;
    }
    
    return sa;
}


void printSuffixArray(int a[], int length)
{
    int i;
    for( i = 0; i < length; i++){
        printf("%d\n",a[i]);    
    }
}

int found[],foundcount=0;
// A suffix array based search function to search a given pattern
// 'pat' in given text 'txt' using suffix array suffArr[]
void search(char *pat, char *txt, int *suffArr, int n)
{
    int m = strlen(pat); // get length of pattern, needed for strncmp()

    // Do simple binary search for the pat in txt using the
    // built suffix array
    int l = 0, r = n-1;  // Initilize left and right indexes
    while (l <= r)
    {
        // Compare pat with the middle suffix in suffix array
        int mid = l + (r - l)/2;
        int res = strncmp(pat, txt+suffArr[mid], m);
        int i;
        // If match found at the middle, print it and return
        if (res == 0)
        {
            //add the position on to array patternsearch
            found[foundcount]=suffArr[mid];
            foundcount++;
            
            printf("Pattern found at index %d - mid value %d\n",  suffArr[mid],mid);
            for(i=mid+1;i<=r;i++){
                if(strncmp(pat, txt+suffArr[i], m) == 0){
                    printf("Pattern found at index %d - mid value %d\n",  suffArr[i],i);
                    found[foundcount]=suffArr[i];
                    foundcount++;
                }
            }
            for(i=mid-1;i>=l;i--){
                if(strncmp(pat, txt+suffArr[i], m)==0){
                    printf("Pattern found at index %d - mid value %d\n",  suffArr[i],i);
                    found[foundcount]=suffArr[i];
                    foundcount++;
                }
            }
            return;
        }

        // Move to left half if pattern is alphabtically less than
        // the mid suffix
        if (res < 0) r = mid - 1;

        // Otherwise move to right half
        else l = mid + 1;
    }

    // We reach here if return statement in loop is not executed
    printf("Pattern not found\n");
}



//* ------ merge sort ------*//
// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[], int , int , int);
void mergeSort(int arr[], int , int);

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    /* create temp arrays */
    int L[n1], R[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 
/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;
 
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
 
        merge(arr, l, m, r);
    }
}

void checkForTandemRepeats(int patternlength){
    int i,arr[foundcount];
    int startprinted = 0;
    for(i=0;i<foundcount;i++){
        arr[i] = found[i];
        //printf("%d ",listarr[i]);
    }
    
    mergeSort(arr,0,foundcount-1);
    printf("Positions at which pattern found in increasing order:\n");
    for(i=0;i<foundcount;i++){
        printf("%d ",arr[i]);
    }
    printf("\nThe Tandem reapets are:\n");
    for(i=0;i<foundcount;i++){
        if( (arr[i+1]-arr[i]) == patternlength){
            if(!startprinted){
                printf("\nstart : %d",arr[i]);
                startprinted = 1;
            }
            printf(" - %d",arr[i+1]);
        } else {
            startprinted = 0;
        }
    }

}

int main()
{
    char txt[] = "nananabananacanananavanavdnananananananannnnanananananananannnnananananannnnnnanananananananananananan";
    char pattern[] = "na";
    
    int length = strlen(txt);
    int patternlength = strlen(pattern);

    clock_t begin = clock();
    int *sa = constructSuffixArray(txt,  length);
    clock_t end = clock();

    double time_spent_for_building = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("The generated suffix array indices for %s:\n", txt);
    printSuffixArray(sa, length);

    begin = clock();
    search(pattern,txt,sa,length);
    end = clock();

    double time_spent_for_searching = (double)(end - begin) / CLOCKS_PER_SEC;

    int i;
    for(i=0;i<foundcount;i++){
        printf("%d\n",found[i]);
    }

    begin = clock();
    checkForTandemRepeats(patternlength);
    end = clock();

    double time_spent_for_tandemrepeats = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("\nBuilding: %f - Searching: %f - tandemRepeats: %f",time_spent_for_building,time_spent_for_searching,time_spent_for_tandemrepeats);

    return 0;
}

