#include "post.h"

int main(int argc, char *args[]) 
{
	int pointMenu;
	if (argc != 4) 
	{
		printf("post.exe ftape.txt fcom.txt out.txt \n");
		return -1;
	}
	do
	{ 
		pointMenu = menu(7);
		switch (pointMenu)
		{
			case 1: loadTape(args[1]);
					printTape(stdout);
					break;
			case 2: loadCommands(args[2]);
					printCommandsList();
					break;
			case 3: printTape(stdout);
					printCommandsList();
					break;
			case 4: run(args[3], false);
					break;
			case 5: run(args[3], true);
					break;
			case 6: RestoringTape();
					break;

			case 7: break;
		}
	} while (pointMenu != 7);
	printf ("\n See you later :3 \n \n \n");
	return 0;
}