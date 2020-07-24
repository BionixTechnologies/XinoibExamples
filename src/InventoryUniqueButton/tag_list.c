#include <stdio.h>
#include "tag_list.h"
#define LISTSIZE 1000
u_int8_t tag_list[LISTSIZE][20];
u_int8_t list_length = 0;

//Check if exit the epc in the list
u_int8_t existTagInList(u_int8_t *epc_to_check,u_int8_t epc_length){
    int i=0,j=0;
    for (i=0;i<tagListLength();i++){
        for (j=11;j!=2;j--){
            if (epc_to_check[j] != tag_list[i][j])
                break;
        }
        if (j==2) return 1;
    }
    return 0;
}

//Add the epc to the list if not exist
void addTagToList(u_int8_t * epc,u_int8_t epc_length){
    if (tagListLength() < LISTSIZE){
        if (tagListLength == 0){
            memcpy(&tag_list[list_length][0],epc,epc_length);  
            list_length++;
        }else{
            if (!existTagInList(epc,epc_length)){
                memcpy(&tag_list[list_length][0],epc,epc_length); 
                list_length++;
            }
        }
    }
    
          
}

// Returns the size of the list
u_int16_t tagListLength(){
    return list_length;
}

// Print the epc tag 96 bits only
void printTagList(){
    int i=0,j=0;
    for (i=0;i<tagListLength();i++){
        for (j=0;j<12;j++){
            printf("%02X",tag_list[i][j]);
        }
       printf("\n");
    }
}

// Restart the tag list to 0.
void resetTagList(){
    list_length = 0;
}
