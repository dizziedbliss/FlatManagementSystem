#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "flats.h"
#include "functions.h"

extern flat flats;

//Creates memory space for owner field and returns a memory location
Owner* createOwner(){
    Owner* x = (Owner *)malloc(sizeof(Owner));
    memset(x, 0, sizeof(char) * 100); 
    if(x == NULL){
        printf("Memory allocation failed");
        exit(1);
    }
    return x;
}

//Reads the file (data.csv) and saves it to the memory (residence array)
void read_file() {
    FILE *file = fopen(dataset, "r");
    if (file == NULL) {
        printf("error: couldn't open the file\n");
        return;
    }
    char header[150];
    fgets(header, sizeof(header), file);
    char line[500];
    char status[15];

    while (fgets(line, sizeof(line), file)) { 
        int i=0;
        while(line[i]!=','){
            status[i]= line[i];
            i++;
        }
        status[i] = '\0';

        if(strcmp(status, "Booked")==0){
            flats.owner = createOwner(); 

            if (sscanf(line, "%9[^,],%9[^,],%9[^,],%d,%49[^,],%49[^,],%f,%f,%f,%s", flats.status, flats.ID, flats.type, &flats.price, flats.owner->name, flats.owner->o_info, &flats.owner->paid, &flats.owner->balance, &flats.owner->due, flats.owner->date) == 10) {
                if (current >= size) {
                    printf("Error: Exceeded maximum residence capacity\n");
                    break;
                    }
            residence[current++] = flats; // increasing the current value (from 0 (in dsa.c file)) till the loop ends... (It'll store the total number of Lines in the file and, residence array will move to the next structure element to save the data)
            }
        }
        
        else if (strcmp(status, "Available")==0){
            if (sscanf(line, "%9[^,],%9[^,],%9[^,],%d", flats.status, flats.ID, flats.type, &flats.price) == 4) {
                if (current >= size) {
                    printf("Error: Exceeded maximum residence capacity\n");
                    break;
                    }
            flats.owner = NULL;
            residence[current++] = flats;
            }
        }
        
        else {
            printf("Failed to parse line: %s\n", line);
            printf("line: %s\n", line); //upon error reading the file, it'll just print this
        }
    }
    fclose(file);
    printf("\nLoading the main menu...\n");
}
//This one will overwrite the whole thing (i mean the file) - ie., we're using it in the end of the program to save the data that we fetched/edited during the runtime... so, we'll be erasing the previous data in .csv file and rewrite everything that we've inside the memory (residence array)
void write_file(){
    FILE *file = fopen(dataset, "w");
        if (file == NULL){
            printf("error: couldn't open the file");
            return;
        }
    fprintf(file, "Status,Flat ID,Type,Price,Owner Name,Contact Info,Amount Paid So Far,Remaining Balance,Next Monthly Installment,Due Date\n");
    char line[500];
    for(int i=0; i<current; i++){
        if(strcmp(residence[i].status, "Booked")==0){
            sprintf(line, "%s,%s,%s,%d,%s,%s,%.2f,%.2f,%.2f,%s\n",residence[i].status, residence[i].ID, residence[i].type, residence[i].price, residence[i].owner->name, residence[i].owner->o_info, residence[i].owner->paid, residence[i].owner->balance, residence[i].owner->due, residence[i].owner->date);


            fwrite(line, sizeof(char), strlen(line), file);
            free(residence[i].owner);
        }
        else if(strcmp(residence[i].status, "Available")==0){
            sprintf(line, "%s,%s,%s,%d,%p\n",residence[i].status, residence[i].ID, residence[i].type, residence[i].price, residence[i].owner);

            fwrite(line, sizeof(char), strlen(line), file);
        }
        else{
            printf("\nwriting error at %d\n", i);
        }
    }
    fclose(file);

}

//ver 3.0.0 stable
