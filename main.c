//
//  main.c
//
//  Tristan Gonzalez, phone, a database program for keeping names and phone numbers
//  Copyright (c) 2013 Tristan Gonzalez. All rights reserved.
//  rgonzale@darkterminal.net
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "prototypes.h"

#define MAX_DATA 32

int main(int argc, char *argv[]) {

   int index;

   if (argc < 3 || argc > 6)
      die("ERROR 22: argc out of bounds");

   char *file = argv[1];
   char action = argv[2][1];
   char action2;

   Connection *conn = DatabaseLoad(file, &action);
   assert(conn != NULL);

   if (argc > 3 && action != 'f')
	   index = atoi(argv[3]);

   if (argv[2][0] == '-') {

	   switch(action) {
		   case 'c':
			   fprintf(stderr, "create\n");
			   DatabaseCreate(conn, &index);
			   DatabaseWrite(conn, file);
			   break;

		   case 'C':
			   fprintf(stderr, "Ncurses\n");
			   DatabaseNcurses(conn, file);
			   break;

		   case 'd':
			   fprintf(stderr, "delete\n");
			   if (argc == 3)
				   DeleteRecord(conn, NULL);
			   else
				   DeleteRecord(conn, &index);

			   DatabaseWrite(conn, file);
			   break;

		   case 'D':
			   fprintf(stderr, "DeleteShift\n");
			   if (argc == 3)
				   DeleteRecord(conn, NULL);
			   else
				   DeleteInsert(conn, &index);

			   DatabaseWrite(conn, file);
			   break;

		   case 'a':
			   fprintf(stderr, "add\n");
			   if (argc == 5)
				   AddRecord(conn, NULL, argv[3], argv[4]);
			   else
				   AddRecord(conn, &index, argv[4], argv[5]);

			   DatabaseWrite(conn, file);
			   break;

		   case 'A':
			   fprintf(stderr, "Arrange\n");
			   DatabaseArrange(conn);
			   DatabaseWrite(conn, file);
			   break;

		   case 'l':
			   fprintf(stderr, "list\n");
			   DatabaseList(conn, NULL);
			   break;

		   case 'r':
			   fprintf(stderr, "resize\n");
			   DatabaseResize(conn, &index);
			   DatabaseWrite(conn, file);
			   break;

		   case 'i':
			   fprintf(stderr, "import\n");
			   DatabaseImport(conn);
			   DatabaseWrite(conn, file);
			   break;

		   case 'I':
			   fprintf(stderr, "Insert\n");
			   AddInsert(conn, &index, argv[4], argv[5]);
			   DatabaseWrite(conn, file);
			   break;

		   case 'e':
			   fprintf(stderr, "export\n");
			   DatabaseExport(conn);
			   break;

		   case 's':
			   fprintf(stderr, "sort\n");
			   DatabaseSort(conn);
			   DatabaseWrite(conn, file);
			   break;

		   case 'f':
			   fprintf(stderr, "find\n");
			   DatabaseFind(conn, argv[3], NULL);
			   break;

		   case 'h':
			   fprintf(stderr, "help\n");
			   Usage();
			   break;

		   case 'n':
			   fprintf(stderr, "encrypt\n");
			   action2 = 'e';
			   Secrecy(conn, &action2);
			   DatabaseWrite(conn, file);
			   break;

		   case 'x':
			   fprintf(stderr, "decrypt\n");
			   action2 = 'd';
			   Secrecy(conn, &action2);
			   DatabaseWrite(conn, file);
			   break;

		   case 'S':
			   fprintf(stderr, "shell v0.1\n");
			   DatabaseShell(conn, file);
			   break;

		   default:
			   die("ERROR 127: default case");
	   }

	   DatabaseClose(conn);

   } else {
	   die("ERROR 133: Usage");
   }

   return 0;
}
