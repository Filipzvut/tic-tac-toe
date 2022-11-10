#include "tic-tac-toe.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define X 3
#define Y 4
void tisktabulky();
void hrac(int alaha);
void zandani(int a);
int restart();
int kok(int a);
int obsazene(int a);
int vyhra();
int finvyhra(int win);
void bot();
using namespace std;
int pomocnou;
int lolx = 0;
int loly = 0;
int menu = 0;
int obtiznost = 0;
int znovu;
int rst = 0;
char space[Y][X] = { ' ',' ',' ',
					' ',' ',' ',
					' ',' ',' ',
					'f', 'f', 'f', }; //nevyuzite promenne pro kkt


int main()
{
start:
	printf("\n	Vyber herni rezim:");
	printf("\n\n	1. Multiplayer\n");
	printf("	2. Singleplayer vs bot\n\n	");
	scanf("%d", &menu);

	if (menu == 2)
	{
		system("cls");
		printf("\n	Vyber obtiznost:");
		printf("\n\n	1. Easy\n");
		printf("	2. Hard\n");
		printf("	3. Hard af\n\n	");									//vylepsit boty
		scanf("%d", &obtiznost);										//undo tlacitko
	}

stejne:
	getchar();
	if (obtiznost == 3)
		space[1][1] = 'X';


	system("cls");
	printf("\n			Zacina hrac s O O O\n");
	tisktabulky();

	for (int a = 0; a != 9 || (a != 7 && obtiznost == 3); a++)
	{

		lolx = 0;
		loly = 0;
		if ((menu == 2 && a % 2 == 0 && (obtiznost == 1 || obtiznost == 3)) || menu == 1)
		{
			printf("\n	Zadej dalsi bod:  ");
			scanf_s("%d %d", &lolx, &loly);
			--lolx;
			--loly;
		}
		else
		{
			if ((menu == 2 && a % 2 != 0 && obtiznost == 2) || menu == 1)
			{
				printf("\n	Zadej dalsi bod:  ");
				scanf("%d %d", &lolx, &loly);
				--lolx;
				--loly;
			}

			bot();

		}
		a = kok(a);

		if (space[loly][lolx] == ' ')
			zandani(a);
		else
			a = obsazene(a);



		system("cls");
		hrac(a);
		tisktabulky();
		if (a == 8)
		{
			system("cls");
			printf("\n		Nikdo nevyhral ojojoj xd!!");
			printf("\n		Nevadi zkuste to znovu :o");
			tisktabulky();
		}
		finvyhra(a);
		if (finvyhra(a) == 1)
			break;
		if (finvyhra(a) == 3)
			goto stejne;
	}

	getchar();
	getchar();

	if (restart() == 1)
		goto start;
	if (restart() == 3)
		goto stejne;

	return 0;

}



void tisktabulky()
{

	printf("\n\n		           1    2    3	(x) \n");
	printf("			  -------------\n");
	printf("			1 | %c | %c | %c |\n", space[0][0], space[0][1], space[0][2]);
	printf("	bod		  -------------\n");
	printf("	zadejte		2 | %c | %c | %c |\n", space[1][0], space[1][1], space[1][2]);
	printf("	ve tvaru	  -------------\n");
	printf("	x y		3 | %c | %c | %c |\n", space[2][0], space[2][1], space[2][2]);
	printf("			  -------------\n	               (y)\n\n");

}

void hrac(int alaha)
{
	if (alaha % 2 == 0)
		printf("\n			Hraje player_1 s X X X\n");
	else
		printf("\n			Hraje player_2 s O O O\n");
}

int kok(int a)
{
	while (lolx < 0 || lolx > 3 || loly < 0 || loly > 3)			// kdyby byl nekdo kok a zadal spatnou hodnotu
	{
		lolx = 1;
		loly = 2;
		system("cls");
		printf("\n\n\n\n\n			zadal si spatnou hodnotu lol :)");
		_sleep(1500);
		pomocnou = 1;
		a--;
	}
	return a;
}


int obsazene(int a)
{
	if (pomocnou != 1)
	{
		printf("\n			pole je obsazene!!!!!");
		pomocnou = 0;
		_sleep(1500);
		a--;
		return (a);
	}
}

void zandani(int a)
{
	if (a % 2 != 0)
	{
		space[loly][lolx] = 'X';
	}
	else
		space[loly][lolx] = 'O';
}


int vyhra()
{
	if (space[0][0] == space[0][1] && space[0][1] == space[0][2] && space[0][0] != ' ')				//1.x
		return 1;

	if (space[1][0] == space[1][1] && space[1][1] == space[1][2] && space[1][0] != ' ')		//2.x
		return 1;

	if (space[2][0] == space[2][1] && space[2][1] == space[2][2] && space[2][0] != ' ')		//3.x
		return 1;

	if (space[0][0] == space[1][0] && space[1][0] == space[2][0] && space[0][0] != ' ')		//1.y
		return 1;

	if (space[0][1] == space[1][1] && space[1][1] == space[2][1] && space[0][1] != ' ')		//2.y
		return 1;

	if (space[0][2] == space[1][2] && space[1][2] == space[2][2] && space[0][2] != ' ')		//3.y
		return 1;

	if (space[0][0] == space[1][1] && space[1][1] == space[2][2] && space[0][0] != ' ')		//1. uhlopricka
		return 1;

	if (space[0][2] == space[1][1] && space[1][1] == space[2][0] && space[0][2] != ' ')		//2. uhlopricka
		return 1;

	return 0;
}


int finvyhra(int win)
{

	if (win % 2 != 0 && vyhra() == 1)
	{
		system("cls");
		printf("\n		Vyhral player_1 s X X X  !!!!!!!!!!!!!!\n");
		tisktabulky();
		printf("\n		Vyhral player_1 s X X X  !!!!!!!!!!!!!!\n");
		return 1;
	}
	if (win % 2 == 0 && vyhra() == 1)
	{
		system("cls");
		printf("\n		Vyhral player_2 s O O O  !!!!!!!!!!!!!!\n");
		tisktabulky();
		printf("\n		Vyhral player_2 s O O O  !!!!!!!!!!!!!!\n");
		return 1;

	}
	return 0;
}

int restart()
{
	for (int a = 0; a < 3; a++)
	{
		space[a][0] = ' ';
		space[a][1] = ' ';
		space[a][2] = ' ';
	}
	int vrt;
	system("cls");

	if (rst == 0)
	{
		printf("\n\n\n		1.	restart hry\n");
		printf("		2.	konec hry\n");
		scanf("%d", &vrt);
		system("cls");
		if (vrt == 1)
		{
			printf("\n\n\n		1.	stejne nastaveni\n");
			printf("		2.	zmenit nastaveni\n");
			scanf("%d", &znovu);
			system("cls");
			rst = 1;

			if (znovu == 2)
				return 1;
			if (znovu == 1)
				return 3;
		}
		else
			return 0;
	}
	else
	{
		rst = 0;
		if (znovu == 2)
			return 1;
		if (znovu == 1)
			return 3;
	}

}

void bot()
{
znovu:
	_sleep(200);
	lolx = rand() % 3 + 0;
	loly = rand() % 3 + 0;
	if (space[loly][lolx] != ' ')
		goto znovu;

}