//I've used the answers of the exam - 2022 (quest. 4) for the basic structors of this class

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "AdptArray.h"


//define the struct
typedef struct AdptArray_
{
	int ArrSize;
	PElement* pElemArr;
	DEL_FUNC delFunc;
	COPY_FUNC copyFunc;
	PRINT_FUNC printFunc;
}AdptArray;

//create empty array
PAdptArray CreateAdptArray(COPY_FUNC copyFunc_, DEL_FUNC delFunc_, PRINT_FUNC printFunc_){
	PAdptArray pArr = (PAdptArray)malloc(sizeof(AdptArray));
	if (pArr == NULL)
		return NULL;
	pArr->ArrSize = 0;
	pArr->pElemArr = NULL;
	pArr->delFunc = delFunc_;
	pArr->copyFunc = copyFunc_;
	pArr->printFunc = printFunc_;
	return pArr;
}


Result SetAdptArrayAt(PAdptArray pArr, int idx, PElement pNewElem){
	PElement* newpElemArr;
	if (idx >= 0){      //check the index isn't negative
    	if (idx >= pArr->ArrSize){      //if index gte than array size
            newpElemArr = realloc(pArr->pElemArr, (idx + 1) * sizeof(PElement));
		    if (newpElemArr == NULL){   //check that the realloc wasn't failes
			    return FAIL;
            }
    		pArr->pElemArr = newpElemArr;
	    	for(int i = pArr->ArrSize; i <= idx ; i++){     //define the new elements to be null
                pArr->pElemArr[i]  = NULL;
            }
            pArr->ArrSize = idx + 1;        //define the new array size
    	}
        else if(pArr->pElemArr[idx] != NULL){   //if index smaller than array size, and the index elemnt isn't null
    	    pArr->delFunc(pArr->pElemArr[idx]); //the elemnt isn't null so we delete it
        }
        pArr->pElemArr[idx] = pArr->copyFunc(pNewElem); //and enter to the element the required new element
	    return SUCCESS;
    }
	return FAIL;    //is the index is negative it would fail
}

// delere the array
void DeleteAdptArray(PAdptArray pArr){
	if (pArr == NULL)   // if the array is empty return
		return;
	else{   // if the array isn't empty
        for(int i = 0; i < pArr->ArrSize; ++i){     //iterate the array
            if (pArr->pElemArr[i] != NULL){
            	pArr->delFunc(pArr->pElemArr[i]);   //delete each ement that isn't null
            }
    	}
	    free(pArr->pElemArr);   //free each element in the array
	    free(pArr);         //free the array
    }
}

//return copy of the element in the idx of the array
PElement GetAdptArrayAt(PAdptArray pArr, int idx){
    //check if the arr isn't null & the idx is smaller the the arr size & the element in idx place in the arr isn't null
	if(pArr != NULL && idx < pArr->ArrSize && pArr->pElemArr[idx] != NULL){
		return pArr->copyFunc(pArr->pElemArr[idx]); //return the required element
	}
	else{   //else the element in the idx of the array is null
		return NULL;
	}
}

//return the array size
int GetAdptArraySize(PAdptArray pArr){
	if (pArr == NULL){
		return -1;
	}
	else{
		return pArr->ArrSize;
	}
}

// print the elements in the array
void PrintDB(PAdptArray pArr){
	int i = GetAdptArraySize(pArr);
    if (i > 0){
        for(int j = 0 ; j < pArr->ArrSize ; j++){
            if(pArr->pElemArr[j] != NULL){
                pArr->printFunc(pArr->pElemArr[j]);
            }
        }
	}
	else {
		printf("NULL");
	}
}
