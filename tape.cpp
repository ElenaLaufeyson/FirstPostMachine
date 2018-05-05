#include "post.h"

/* 
    v
1110001000
*/

bool tape[TAPE_SIZE];
int tapePointer;
bool copyedTape[TAPE_SIZE];
int v;
bool ifLoadTape = false; //лента не загружена

//очистка ленты
void clearTape()
{
	for (int i=0; i < TAPE_SIZE; i++)
	{
		tape[i] = false;
	}
	tapePointer = TAPE_SIZE/2;
}

//загрузка ленты
void loadTape(char *ftape)
{
	char tmp[81];
	int lenghtOfString, ret;
	char n;
	FILE *in;
	v = -1;
	in = fopen(ftape, "rt");
	if (in == NULL)
	{
		printf("File %s not found \n", ftape);
		exit(-2);
	}
	clearTape();
	fgets(tmp, 80, in);
	lenghtOfString = strlen(tmp);
	for (int i=0; i<lenghtOfString; i++) 
	{
		if (tmp[i] == 'v') 
		{
			v = i;
			break;
		}
		if (tmp[i] != ' ') 
		{
			printf("Error in data file %s/ There are may be only spases or v \n", ftape);
			fclose(in);
			return;
		}
	}//end for
	if (v == -1) 
	{
		printf("Error in data file %s/ There are must be v \n", ftape);
		fclose(in);
		return;
	}
	do 
	{
		ret = fscanf(in, "%c", &n);
		if (ret == EOF) //конец файла
		{
			break;
		}
		if (ret != 1 || (n != '0' && n != '1')) 
		{
			printf("Error in data file %s/ There are must be only 0 and 1 \n", ftape);
			fclose(in);
			return;
		}
		if (n=='1') 
		{
			mark();
			right();
		}
		else 
		{
			unmark();
			right();
		}
	} while (!feof(in));
	fclose(in);
	tapePointer = TAPE_SIZE/2 + v;
	ifLoadTape = true;
	copyTape(tape, copyedTape);
}

//поставить метку
void mark() 
{
	tape[tapePointer] = true;
}

//снять метку
void unmark() 
{
	tape[tapePointer] = false;
}

//сдвиг вправо
void right()
{
	tapePointer++;
	if (tapePointer >= TAPE_SIZE)
	{
		printf("Error.No enable space on right size of the tape \n");
		tapePointer--;
		return;
	}
}

//сдвиг влево
void left()
{
	tapePointer--;
	if (tapePointer < 0)
	{
		printf("Error.No enable space on left size of the tape \n");
		tapePointer++;
		return;
	}
}

void copyTape(bool what[], bool whereTo[])
{
	for (int i=0; i < TAPE_SIZE; i++)
	{
		whereTo[i] = what[i];
	}
}

void RestoringTape()
{
	copyTape(copyedTape, tape);
	tapePointer = TAPE_SIZE/2 + v;
	printTape(stdout); 
}

void printTape(FILE *wherePrint)
{
	if (!ifLoadTape) 
		return;
	int delta = 30;
	fprintf(wherePrint, "%31c \n", 'v');
	for (int i = tapePointer - delta; i < tapePointer + delta; i++)
	{
		if (tape[i])
			fprintf(wherePrint, "1");
		else 
			fprintf(wherePrint, ".");
	}
	fprintf(wherePrint, "\n \n");
}