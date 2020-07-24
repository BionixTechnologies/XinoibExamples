#ifndef TAG_LIST_H
#define TAG_LIST_H
#include <stdlib.h>
#include <string.h>
//Check if exit the epc in the list
u_int8_t existTagInList(u_int8_t *epc_to_check,u_int8_t epc_length);

//Add the epc to the list if not exist
void addTagToList(u_int8_t * epc,u_int8_t epc_length);

// Returns the size of the list
u_int16_t tagListLength();

// Print the epc tag 96 bits only
void printTagList();

// Restart the tag list to 0.
void resetTagList();

#endif