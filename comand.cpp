#include "post.h"

/* 

1.	<2
2.	?1,3
3.	>4
4.	1 5
5.	.

*/

COMMAND commands[COMMAND_SIZE];
int numberOfCommands;
bool ifLoadCommand;

//очистка списка команд
void clearCommands()
{
	for (int i=0; i < COMMAND_SIZE; i++)
	{
		commands[i].number = commands[i].condition1 = commands[i].condition2 = -1;
		commands[i].command = commands[i].commandString[0] = '\0';
	}
	numberOfCommands = 0;
}

void printCommandsList()
{
	printf("\n \n");
	for (int i=0; i < numberOfCommands; i++)
	{
		printf("%s \n", commands[i].commandString);
	}
	printf("\n \n");
}

//загрузка команд
void loadCommands(char *fcom)
{
	int ret, number, condition1, condition2, length, i;
	char command;
	const char *commandTypes = "<>?10";
	FILE *in;
	in = fopen(fcom, "rt");
	if (in == NULL)
	{
		printf("File %s not found \n", fcom);
		exit(-3);
	}
	clearCommands();
	do
	{
		ret = fscanf(in, " %d. %c %d", &number, &command, &condition1);
		if (ret == EOF)
			break;
		if (number <= 0 || number >= COMMAND_SIZE || condition1 <= 0 || condition1 >= COMMAND_SIZE)
		{
			printf("Error in %s file. There may be only commands from [1..%d] interval \n", fcom, COMMAND_SIZE);
			fclose(in);
			return;
		}
		numberOfCommands++;
		//проверка последовательности введенных команд
		if (numberOfCommands != number)
		{
			printf("Error in %s file. Command numbers must be in order \n", fcom);
			fclose(in);
			return;
		}
		commands[number-1].number = number;
		commands[number-1].command = command;
		commands[number-1].condition1 = condition1;
		if (ret == 2 && command == '.')
		{
			sprintf(commands[number-1].commandString, "%d. %c", number, command);
			break;
		}
		if (ret != 3)
		{
			printf("Error in %s file. Command must have a certain structure \n", fcom);
			fclose(in);
			return;
		}
		length = strlen(commandTypes);
		for (i=0; i < length; i++)
		{
			if (command == commandTypes[i])
				break;
		}
		if (i == length)
		{
			printf("Error in %s file. Сommand does not exist \n", fcom);
			fclose(in);
			return;
		}
		condition2 = -1;
		if (command == '?')
		{
			ret = fscanf(in, ",%d", &condition2);
			if (ret != 1 || condition2 <= 0 || condition2 >= COMMAND_SIZE || condition2 == condition1)
			{
				printf("Error in %s file. Wrong condition2 \n", fcom);
				fclose(in);
				return;
			}
			commands[number-1].condition2 = condition2;
		}
		if (condition2 != -1)
			sprintf(commands[number-1].commandString, "%d. %c %d,%d", number, command, condition1, condition2);
		else 
			sprintf(commands[number-1].commandString, "%d. %c %d", number, command, condition1);
	} while(!feof(in));
	fclose(in);
	if (commands[numberOfCommands-1].command != '.')
	{
		printf("Error in %s file. No stop-command - . in last command \n", fcom);
		return;
	}
	ifLoadCommand = true;
}