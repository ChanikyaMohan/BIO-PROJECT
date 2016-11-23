#include <stdio.h>

int patternlength = 3;
int patterncount = 5;
int listarr[5] = {0,2,5,7,10};
void checkForTandemRepeats(){
	int i,arr[patterncount];
	int startprinted = 0;
	for(i=0;i<patterncount;i++){
		arr[i] = listarr[i];
		printf("%d ",arr[i]);
	}
	int start = 0,end = 0;
	for(i=0;i<patterncount;i++){
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

    checkForTandemRepeats(); 
   return 0;
}

