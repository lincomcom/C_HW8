/*
 * hw8
 *
 *
 * Look for the @@@ signs for the places to modify.
 */
#include <stdio.h>
#include <string.h>
#include "event.h"

int main(int argc, char **argv) {
	char cmd[BUFLEN], buf[BUFLEN];
	int argoffset;
	InitTable();
	/*@@@try to open the file ".events" for reading */
	tryReadingEventsFile();
	while (1) {
		PrintPrompt();
		if (fgets(buf, BUFLEN, stdin) == NULL) {
			break; /* user typed ^D to indicate EOF */
		}
		if (sscanf(buf, "%s%n", cmd, &argoffset) != 1) {
			continue;
		}
		if (!strcmp(cmd, CMD_HELP)) {
			PrintHelp();
		} else if (!strcmp(cmd, CMD_GOTO)) {
			/* scan n */
			int eventNum = -1;
			if (sscanf(buf+argoffset, "%d", &eventNum) != 1) {
				fprintf(stderr, "usage: " CMD_GOTO " eventNumber\n");
			} else {
				GotoEvent(eventNum);
			}
		} else if (!strcmp(cmd, CMD_LIST)) {
			/* try to scanf */
			int eventNum = -1;
			sscanf(buf+argoffset, "%d", &eventNum);
			ListEvent(eventNum);
		} else if (!strcmp(cmd, CMD_ADD)) {
			for (; buf[argoffset] && buf[argoffset] <= ' '; argoffset++) {
			}
			AddEvent(buf+argoffset);
		} else if (!strcmp(cmd, CMD_DEL)) {
			int eventNum = -1;
			sscanf(buf+argoffset, "%d", &eventNum);
			DeleteEvent(eventNum);
		} else if (!strcmp(cmd, CMD_QUIT)) {
		    /*@@@try to open the file ".events" for writing */
		    trySavingEventsFile();
			break;
		} else if (!strcmp(cmd, CMD_MOVE)) { /* new code */
			int m, n;
			if (sscanf(buf+argoffset, "%d%d", &m, &n) != 2) {
				fprintf(stderr, "usage: " CMD_MOVE " m n\n");
				continue;
			}
			MoveEvent(m, n);
		} else if (!strcmp(cmd, CMD_MOVETO)) {
			int k;/* declare one int variable */
			/* scan one int. If did not get one, report error and continue */
			if (sscanf(buf+argoffset, "%d", &k) != 1){
                fprintf(stderr, "usage: " CMD_MOVE " k\n");
				continue;
			}
			/* otherwise, call MoveEvent, but from CurrentEventNumber() to the
			 * scanned integer. */
			else
                MoveEvent(CurrentEventNumber(), k);
		} else if (!strcmp(cmd, CMD_MOVEFROM)) {
			int p;/* declare one int variable */
			/* scan one int. If did not get one, report error and continue. */
			if (sscanf(buf+argoffset, "%d", &p) != 1){
                fprintf(stderr, "usage: " CMD_MOVE " n\n");
				continue;
			}
			/* otherwise, call MoveEvent, but from the scanned int to
			 * CurrentEventNumber() */
			else
                MoveEvent( p, CurrentEventNumber());
		} else if (!strcmp(cmd, CMD_SWAP)) {
			int m, n;
			/* scan two int variables */
			/* if did not get two ints, report error and continue */
			if (sscanf(buf+argoffset, "%d%d", &m, &n) != 2){
                fprintf(stderr, "usage: " CMD_MOVE " m n\n");
				continue;
			}
			else/* otherwise, call SwapEvent with those two ints */
                SwapEvents( m, n);
		} else if (!strcmp(cmd, CMD_FIND)) {
			/* get rid of newline */
			char *s = buf + argoffset;
			int len;
			while (*s && *s <= ' ') {
				s++;
			}

			len = strlen(s);
			if (s[len-1] == '\n') {
				s[len-1] = '\0';
			}
			FindEvent(s);
		} else {
			fprintf(stderr, "unknown command: %s\n", cmd);
		}
	}
	return 0;
}
