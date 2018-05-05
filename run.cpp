#include "post.h"

//bool step = true - пошагово, а false - сразу

void run(char *fout, bool step)
{	
	char save;
	bool needFile = false;
	FILE *out;
	char currentCommand; //текущая команда
	int i = 0; //индекс текущей команды (номер команды - 1)
	int maxNumberOfCommands = 100; //максимально возможное количество шагов
	int currentNumberOfCommands = 0;
	int key; //код возвращаемой клавиши

	if (!ifLoadTape || !ifLoadCommand) 
	{
		printf("Error! Commands (or tape) wasn't uploaded! \n");
		printTape(stdout);
		printCommandsList();
		return;
	}
	printf("Save to file? [y-yes, any - no] \n");
	scanf(" %c", &save);
	if (save == 'y')
	{
		needFile = true;
		out = fopen(fout, "wt");
		if (out == NULL)
		{
			printf("File %s can not be open \n", fout);
			exit(-4);
		}
	}
	if (step)
	{
		printf("Space - next step, Esc - exit, Enter - run to end\n\n");
	}
	printTape(stdout);
	if (needFile)
		printTape(out);
	
	while (1)
	{
		printf("%s \n", commands[i].commandString);
		if (needFile)
			fprintf(out, "%s \n", commands[i].commandString);
		currentCommand = commands[i].command;
		switch(currentCommand)
		{
			case '1':	mark();
						break;
			case '0':	unmark();
						break;
			case '<':	left();
						break;
			case '>':	right();
						break;
		}
		if (currentCommand != '.' && currentCommand != '?')
		{
			printTape(stdout);
			if (needFile)
				printTape(out);
		}
		else if (currentCommand == '.')
		{
			printf("\n \n STOP \n \n ");
			if (needFile)
				fprintf(out, "\n \n STOP \n \n ");
			break;
		}

		i = commands[i].condition1;
		if (currentCommand == '?')
		{
			if (tape[tapePointer] == true)
				i = commands[i].condition2;
			
		}
		i--;
		currentNumberOfCommands++;
		if (currentNumberOfCommands > maxNumberOfCommands)
		{
			printf("Exceeded maxNumberOfCommands %d \n", maxNumberOfCommands);
			if (needFile)
				fprintf(out, "Exceeded maxNumberOfCommands %d \n", maxNumberOfCommands);
			break;
		}
		if (step)
		{
			do {
				key = getch();
				if (key == SPACE)
					break;
				if (key == ESC)
				{
					printf("Aborted by user \n \n \n");
					if (needFile)
					{
						fprintf(out, "Aborted by user \n \n \n");
						fclose(out);
					}
					return;
				}
				if (key == ENTER)
					step = false;
			} while (key != ENTER);
		}
	}//end while
	if (needFile)
		fclose(out);
}