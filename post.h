#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define TAPE_SIZE 100
#define COMMAND_SIZE 100
#define ENTER 13
#define ESC 27
#define SPACE 32

int menu(int lastPoint);
void clearTape();
void loadTape(char *ftape);
void mark();
void unmark();
void right();
void left();
void copyTape (bool what[], bool whereTo[]);
void RestoringTape();
void printTape(FILE *wherePrint);

struct COMMAND 
{
	int number, condition1, condition2;
	char command;
	char commandString[21];
};

void clearCommands();
void printCommandsList();
void loadCommands(char *fcom);

void run(char *fout, bool step);
extern bool ifLoadCommand;
extern bool ifLoadTape;
extern COMMAND commands[COMMAND_SIZE];
extern bool tape[TAPE_SIZE];
extern int tapePointer;