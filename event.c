/*
 * hw8
 *
 * look for the @@@ sign in the code for new items.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "event.h"

static int currentEventNumber = 0;
static char eventStr[MAXEVENTS][BUFLEN];
const char *noPtr="(no event)\n";

/* set current event number to eventNumber */
void GotoEvent(int eventNumber) {
	/* check if eventNumber is within legal bound. warn if not. */
	if(eventNumber<0||eventNumber>=MAXEVENTS){
        printf("Event number %d is invalid.\n"
               "Please input eventNumber between 0~%d\n", eventNumber, MAXEVENTS-1);
    }
	/* otherwise, set currentEventNumber to eventNumber. */
	else
        currentEventNumber=eventNumber;
}

int CheckEventNum(int eventNumber){
    if(eventNumber>=-1&&
       eventNumber<MAXEVENTS)
        return 1;
    else
        return 0;
}

void ListAll(){
    int i;
    for(i=0; i<MAXEVENTS; i++){
        if(strcmp(eventStr[i], noPtr)!=0)
            printf(" %d: %s", i, eventStr[i]);
        }
}

/* print eventNumber's event string, or all events' event strings if
 * -1
 */
void ListEvent(int eventNumber) {
    /*check eventNumber range between -1(no input) and MAXEVENTS*/
    if(CheckEventNum(eventNumber)==0)
        printf("event #%d is out of range\n", eventNumber);

    /* check if eventNumber is -1. If so, do a for loop over all events,
	 * check if eventStr[i] is empty string; if not, print it. */
	else if(eventNumber==-1)
        ListAll();

    /* if eventNumber is not -1, then print the event string (of eventNumber) if
	 * it is not empty; otherwise, print "(no event)" instead of empty line.*/
	else
        printf(" %d: %s", eventNumber, eventStr[eventNumber]);

}

/* set the current event number's event string to evt if the current
 * event is not empty, or else report an error
 */
void AddEvent(char *evt) {
	/* if evt is an empty string, tell the user that Event description empty and
	 * is not added. */
    if(!strcmp(evt, noPtr))
        printf("Event description empty and is not added\n");

	/* otherwise, if the current event is not empty string, then tell the user
	 * that the event number exists, and event is not added. */
    else if(strcmp(eventStr[currentEventNumber], noPtr))
        printf("The event number(%d) exists, and event is not added.\n", currentEventNumber);
	/* in all other cases, string-copy from evt to the
	 * eventStr[currentEventNumber]
	 */
    else
        strcpy(eventStr[currentEventNumber], evt);
}

/* if eventNumber is not -1, then delete the eventNumber's event
 * string (set to empty string); otherwise, delete the current event
 * number's event
 */
void DeleteEvent(int eventNumber) {
	/* declare a local event number (say, call it e)
	 * and set it to either the current event number if the given event numbe is
	 * -1, or set it to the given event number otherwise (must be within range). */
    int e;
    if(eventNumber==-1)
        e=currentEventNumber;
    else if(CheckEventNum(eventNumber))
        e=eventNumber;
    else
        printf("event #%d is out of range\n", eventNumber);

	/* to delete, set the eventStr[e] entry to empty string */
	if(strcmp(eventStr[currentEventNumber], noPtr)==0)
        printf("event #%d empty\n", currentEventNumber);
    else
        sprintf(eventStr[e] ,noPtr);
}

/* print the help string */
void PrintHelp() {
	/* print not just last week's help string but also this week's commands */
	printf("goto n    : go to event #n\n");
    printf("list [n]  : list events #n, or current event if n is not specified\n");
    printf("add evt   : add description to current event number\n");
    printf("delete [n]: delete event #n, or current event if n is not provided\n");
    printf("quit      : exit the program\n");
    printf("help      : shows this command list\n");
    printf("move m n  : move an event from #m to #n\n");
    printf("moveto n  : move the current event to #n\n");
    printf("movefrom m: move event from #m to current event\n");
    printf("swap n    : swap current event with event #n\n");
    printf("find      : list events whose descriptions contain the string\n");
}

/* called once to initialize the array */
void InitTable() {
	/* use a loop to walk through all eventStr[i] entries and set each to empty
	 * string.*/
    int i;
    for(i=0; i<MAXEVENTS; i++){
        strcpy(eventStr[i], noPtr);
    }
}

/* prints the current event number and > */
void PrintPrompt() {
	/* this is a single printf statement that prints the current event number as a
	 * prompt */
	 printf("%d> ", currentEventNumber);
}

/* moves an event from #m to #n, but #m must be nonempty, #n must be empty */
void MoveEvent(int m, int n) {
	/* check if m and n are both within range. If not, print warning. */
	if(CheckEventNum(m)==0||
       CheckEventNum(n)==0){
        printf("event is out of range\n");
    }

    /* make sure the source (m) event is not empty; otherwise, report error */
    else if(!strcmp(eventStr[m], noPtr))
        printf("event %d is empty\n", m);

    /* make sure the destination (n) event is empty; otherwise, report error
     * if you are moving from an event to itself, just skip it.
     * otherwise, string-copy source to destination.
     * finally, set the source string buffer to empty string.
     * */
	else if(!strcmp(eventStr[n], noPtr)){
        if (m==n) return;
        else{
			strcpy(eventStr[n], eventStr[m]);
		}
		strcpy(eventStr[m], noPtr);
    }
	else
        printf("event %d is not empty\n", n);

}

/* get the current event number */
int CurrentEventNumber() {
	/* return the file-global variable for the current event number */
	return currentEventNumber;
}

/* swap two events m and n, whether they are empty */
void SwapEvents(int m, int n) {
	/* declare a temporary string buffer of BUFLEN size. */
	char temp[BUFLEN];
	/* first check if m and n are both in legal range. report if not. */
	if(CheckEventNum(m)==0||
       CheckEventNum(n)==0){
        printf("event is out of range\n");
    }
	/* if not swapping with itself, then copy one string to temp string
	 * buffer, overwite first event string with second string, then overwrite
	 * second string buffer with saved first one. */
    else if (m==n) return;
    else{
        strcpy( temp, eventStr[m]);
        strcpy( eventStr[m], eventStr[n]);
        strcpy( eventStr[n], temp);
    }
}

/* find events whose descriptions contain the string and list them. */
void FindEvent(char *evt) {
	/* use a for loop to compare all strings in array.
	 * if not empty and evt matches it, then call ListEvent to print it out. */

    int i;
    for(i=0; i<MAXEVENTS; i++){
        if(strcmp(eventStr[i], noPtr)!=0&&
           strstr(eventStr[i], evt)!=NULL)
            printf(" %d: %s", i, eventStr[i]);
        }


}
/*@@@try to open the file ".events" for reading */
void tryReadingEventsFile(){
    /*create a file pointer */
    FILE *fptr;
    /*initiate eventNum */
    int i=0;
    /*open a file*/
    fptr=fopen(".events.txt", "r");
    /*check there is a file pointer */
    if (fptr==NULL)
        return;
    /*get the currentEventNumber*/
    fscanf( fptr, "%d", &currentEventNumber);

    /*999 indicate end of file*/
    while(i!=999){
         /*get the EventNumber*/
        fscanf(fptr , "%d", &i);
        /*get the rest of the line*/
        fgets(eventStr[i], 100, fptr);
    }

    /*close a file*/
    fclose(fptr);

}

/*@@@try to open the file ".events" for writing */
int trySavingEventsFile(){
    /*create a file pointer */
    FILE *fptr;
    /*initiate eventNum */
    int i;
    /*open a file*/
    fptr=fopen(".events.txt", "w");
    /*save the currentEventNumber*/
    fprintf(fptr , "%d\n", currentEventNumber);
    /*save the events*/
    for(i=0; i<MAXEVENTS; i++){
        if(strcmp(eventStr[i], noPtr)!=0)
            fprintf(fptr , "%d%s", i, eventStr[i]);
        }
    /*save 999 to indicate end of file*/
    fprintf(fptr , "%d", 999);
    /*close a file*/
    fclose(fptr);
    return 0;
}
