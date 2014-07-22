/*
 * event.h - for hw8
 */
#ifndef __EVENT_H__
#define __EVENT_H__

#define BUFLEN 100 /* total number of chars per line */
#define MAXEVENTS 100 /* total number of events */

/* macros for the command names */
#define CMD_HELP "help"
#define CMD_GOTO "goto"
#define CMD_LIST "list"
#define CMD_ADD  "add"
#define CMD_DEL  "delete"
#define CMD_QUIT "quit"

#define CMD_MOVE     "move"
#define CMD_MOVETO   "moveto"
#define CMD_MOVEFROM "movefrom"
#define CMD_SWAP     "swap"
#define CMD_FIND     "find"


/* set current event number to eventNumber */
void GotoEvent(int eventNumber);

/* print eventNumber's event string, or all events' event strings if
 * -1
 */
void ListEvent(int eventNumber);

/* set the current event number's event string to evt if the current
 * event is not empty, or else report an error
 */
void AddEvent(char *evt);

/* if eventNumber is not -1, then delete the eventNumber's event
 * string (set to empty string); otherwise, delete the current event
 * number's event
 */
void DeleteEvent(int eventNumber);

/* print the help string */
void PrintHelp();

/* called once to initialize the array */
void InitTable();

/* prints the current event number and > */
void PrintPrompt();

/* moves an event from #m to #n, but #m must be nonempty, #n must be empty */
void MoveEvent(int m, int n);

/* get the current event number */
int CurrentEventNumber();

/* swap two events m and n, whether they are empty */
void SwapEvents(int m, int n);

/* find events whose descriptions contain the string and list them. */
void FindEvent(char *evt);

/*@@@try to open the file ".events" for reading */
void tryReadingEventsFile();

/*@@@try to open the file ".events" for writing */
int trySavingEventsFile();

#endif /* __EVENT_H__ */
