//Radan Mina-Gabriela, 314CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//functia allocate_int_matrix alocheaza dinamic memorie unei matrice cu valori
//int.
int **allocate_int_matrix(int n)
{
	int **matrix = (int **)malloc(n * sizeof(int *));
	if (!matrix) {
		fprintf(stderr, "Failed to allocate int matrix rows.\n");
		return NULL;
	}
	for (int i = 0; i < n; i++) {
		matrix[i] = (int *)malloc(n * sizeof(int));
		if (!matrix[i]) {
			fprintf(stderr, "Failed to allocate int matrix row %d.\n", i);
			for (int j = 0; j < i; j++) {
				free(matrix[j]);
			}
			free(matrix);
			return NULL;
		}
	}
	return matrix;
}

//functia free_int_matrix elibereaza memoria unei matrice cu valori int.
void free_int_matrix(int **matrix, int n)
{
	for (int i = 0; i < n; i++) {
		free(matrix[i]);
	}
	free(matrix);
}

//functia allocate_char_matrix alocheaza dinamic memorie unei matrice cu valori
//char.
char **allocate_char_matrix(int n, int m)
{
	char **matrix = (char **)malloc(n * sizeof(char *));
	if (!matrix) {
		fprintf(stderr, "Failed to allocate char matrix rows.\n");
		return NULL;
	}
	for (int i = 0; i < n; i++) {
		matrix[i] = (char *)calloc(m, sizeof(char));
		if (!matrix[i]) {
			fprintf(stderr, "Failed to allocate char matrix row %d.\n", i);
			for (int j = 0; j < i; j++) {
				free(matrix[j]);
			}
			free(matrix);
			return NULL;
		}
	}
	return matrix;
}

//functia free_char_matrix elibereaza memoria unei matrice cu valori char.
void free_char_matrix(char **matrix, int n)
{
	for (int i = 0; i < n; i++) {
		free(matrix[i]);
	}
	free(matrix);
}

//functia print_char_matrix afiseaza o matrice cu n linii si m coloane ce
//contine doar elemente char.
void print_char_matrix(char **matrix, int n, int m)
{
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			char c = matrix[i][j];
			if (c == '\0') {
				c = '0';
			}
			printf("%c ", c);
		}
		printf("\n");
	}
}

//functia num_of_ships calculeaza numarul de nave pentru amandoi jucatorii
//intr-un meci cu o tabla de n linii si m coloane.
int num_of_ships(int n, int m)
{
	int shinano, yamato, belfast, laffey, albacore;
	shinano = (n * m) / 70;
	yamato = (n * m) / 55;
	belfast = (n * m) / 40;
	laffey = (n * m) / 30;
	albacore = (n * m) / 20;
	return 2 * (shinano + yamato + belfast + laffey + albacore);
}

//functia check_if_spaces verifica daca o nava are destul spatii in sus sau in
//dreapta pentru a fi plasata pe tabla si returneaza 0 daca nu.
int check_if_spaces(int m, char dir, int x, int y, int ship, int valid)
{
	if (dir == 'H' && y > m - ship + 1) {
		valid = 0;
	}
	if (dir == 'V' && x < ship) {
		valid = 0;
	}
	return valid;
}

//functia check_if_no_ship verifica daca nu exista o alta nava amplasata deja
//pe spatiile pe care urmeaza sa fie pusa nava si returneaza 0 daca exista.
int check_if_no_ship(char **grid, int x, int y, int ship, char dir, int valid)
{
	if (valid == 1) {
		if (dir == 'H') {
			for (int i = 0; i <= ship - 1 && valid == 1; i++) {
				if (grid[x][y + i] != 0) {
					valid = 0;
				}
			}
		} else {
			for (int i = 0; i <= ship - 1 && valid == 1; i++) {
				if (grid[x - i][y] != 0) {
					valid = 0;
				}
			}
		}
	}
	return valid;
}

//functia check_if_in_grid verifica daca coordonatele varfului navei apartin
//tablei.
int check_if_in_grid(int n, int m, int x, int y, int valid)
{
	if (x < 1 || x > n || y < 1 || y > m) {
		valid = 0;
	}
	return valid;
}

//functia wrong_place_s verifica daca navele de tip Shinano pot fi amplasate
//pe tabla, folosind functiile check_if_spaces si check_if_no_ship, si, daca
//nu, afiseaza mesaj. Functia returneaza 0 daca nava nu poate fi amplasata in
//acel spatiu.
int wrong_place_s(char **grid, int m, char type, char dir, int x, int y,
				  int valid)
{
	if (type == 'S') {
		if (valid == 1) {
			valid = check_if_spaces(m, dir, x, y, 5, valid);
			valid = check_if_no_ship(grid, x, y, 5, dir, valid);
		}
		if (valid == 0 && dir == 'H') {
			printf("Nava Shinano nu poate fi amplasata orizontal"
				   " la coordonatele (%d, %d).\n", x, y);
		}
		if (valid == 0 && dir == 'V') {
			printf("Nava Shinano nu poate fi amplasata vertical"
				   " la coordonatele (%d, %d).\n", x, y);
		}
	}
	return valid;
}

//functia wrong_place_y verifica daca navele de tip Yamato pot fi amplasate
//pe tabla, folosind functiile check_if_spaces si check_if_no_ship, si, daca
//nu, afiseaza un mesaj. Functia returneaza 0 daca nava nu poate fi amplasata
//in acel spatiu.
int wrong_place_y(char **grid, int m, char type, char dir, int x, int y,
				  int valid)
{
	if (type == 'Y') {
		if (valid == 1) {
			valid = check_if_spaces(m, dir, x, y, 4, valid);
			valid = check_if_no_ship(grid, x, y, 4, dir, valid);
		}
		if (valid == 0 && dir == 'H') {
			printf("Nava Yamato nu poate fi amplasata orizontal"
				   " la coordonatele (%d, %d).\n", x, y);
		}
		if (valid == 0 && dir == 'V') {
			printf("Nava Yamato nu poate fi amplasata vertical"
				   " la coordonatele (%d, %d).\n", x, y);
		}
	}
	return valid;
}

//functia wrong_place_b verifica daca navele de tip Belfast pot fi amplasate
//pe tabla, folosind functiile check_if_spaces si check_if_no_ship, si, daca
//nu, afiseaza un mesaj. Functia returneaza 0 daca nava nu poate fi amplasata
//in acel spatiu.
int wrong_place_b(char **grid, int m, char type, char dir, int x, int y,
				  int valid)
{
	if (type == 'B') {
		if (valid == 1) {
			valid = check_if_spaces(m, dir, x, y, 3, valid);
			valid = check_if_no_ship(grid, x, y, 3, dir, valid);
		}
		if (valid == 0 && dir == 'H') {
			printf("Nava Belfast nu poate fi amplasata orizontal"
				   " la coordonatele (%d, %d).\n", x, y);
		}
		if (valid == 0 && dir == 'V') {
			printf("Nava Belfast nu poate fi amplasata vertical"
				   " la coordonatele (%d, %d).\n", x, y);
		}
	}
	return valid;
}

//functia wrong_place_l verifica daca navele de tip Laffey pot fi amplasate
//pe tabla, folosind functiile check_if_spaces si check_if_no_ship, si, daca
//nu, afiseaza un mesaj. Functia returneaza 0 daca nava nu poate fi amplasata
//in acel spatiu.
int wrong_place_l(char **grid, int m, char type, char dir, int x, int y,
				  int valid)
{
	if (type == 'L') {
		if (valid == 1) {
			valid = check_if_spaces(m, dir, x, y, 2, valid);
			valid = check_if_no_ship(grid, x, y, 2, dir, valid);
		}
		if (valid == 0 && dir == 'H') {
			printf("Nava Laffey nu poate fi amplasata orizontal"
				   " la coordonatele (%d, %d).\n", x, y);
		}
		if (valid == 0 && dir == 'V') {
			printf("Nava Laffey nu poate fi amplasata vertical"
				   " la coordonatele (%d, %d).\n", x, y);
		}
	}
	return valid;
}

//functia wrong_place_a verifica daca navele de tip Albacore pot fi amplasate
//pe tabla, verificand daca spatiul pe care vrea sa fie amplasata nava nu
//este deja ocupat de alta nava, si, daca nu, afiseaza un mesaj. Functia
//returneaza 0 daca nava nu poate fi amplasata in acel spatiu.
int wrong_place_a(char **grid, char type, char dir, int x, int y,
				  int valid)
{
	if (type == 'A') {
		if (dir == 'H') {
			if (valid == 0) {
				printf("Nava Albacore nu poate fi amplasata orizontal"
					   " la coordonatele (%d, %d).\n", x, y);
			} else {
				if (grid[x][y] != 0) {
					printf("Nava Albacore nu poate fi amplasata orizontal"
						   " la coordonatele (%d, %d).\n", x, y);
					valid = 0;
				}
			}
		}
		if (dir == 'V') {
			if (valid == 0) {
				printf("Nava Albacore nu poate fi amplasata vertical"
					   " la coordonatele (%d, %d).\n", x, y);
			} else {
				if (grid[x][y] != 0) {
					printf("Nava Albacore nu poate fi amplasata vertical"
						   " la coordonatele (%d, %d).\n", x, y);
					valid = 0;
				}
			}
		}
	}
	return valid;
}

//functia wrong_place verifica pentru niste coordonate x si y, pentru tipul
//de nava si pentru orientarea navei daca poate fi plasata pe tabla de joc
//si returneaza 1 daca da si 0 in caz contrar.
int wrong_place(char **grid, int n, int m, char type,
				char dir, int x, int y, int valid)
{
	valid = check_if_in_grid(n, m, x, y, valid);
	valid = wrong_place_s(grid, m, type, dir, x, y, valid);
	valid = wrong_place_y(grid, m, type, dir, x, y, valid);
	valid = wrong_place_b(grid, m, type, dir, x, y, valid);
	valid = wrong_place_l(grid, m, type, dir, x, y, valid);
	valid = wrong_place_a(grid, type, dir, x, y, valid);
	return valid;
}

//structura shipbow contine coordonatele x si y capatului unei nave, orientarea
//si lungimea acelei nave. In plus, retine si daca nava cu acel capat este
//scufundata sau nu.
typedef struct {
	int x;
	int y;
	char dir;
	int size;
	int sunk;
} shipbow;

//functia ship_bows salveaza coordonatele x si y, ale capatului unei nave,
//orientarea si lungimea acelei nave intr-un element de vector de struct.
//In plus schimba valoarea ce imi retine daca nava este scufundata sau nu in 0,
//nava fiind nescufundata la inceput.
void ship_bows(shipbow *bows, int *bows_num, int x, int y, char dir, char type)
{
	bows[*bows_num].x = x;
	bows[*bows_num].y = y;
	bows[*bows_num].dir = dir;
	bows[*bows_num].sunk = 0;
	switch (type) {
	case 'S':
		bows[*bows_num].size = 5;
		break;
	case 'Y':
		bows[*bows_num].size = 4;
		break;
	case 'B':
		bows[*bows_num].size = 3;
		break;
	case 'L':
		bows[*bows_num].size = 2;
		break;
	case 'A':
		bows[*bows_num].size = 1;
		break;
	}
	(*bows_num)++;
}

//functia if_shinano modifica tabla unui jucator plasand nava de tip Shinano
//in functie de orientarea ei, punand valoarea 5 pe tabla de joc in locul
//in care este amplasata.
void if_shinano(int m, char dir, int x, int y, char **grid_p1,
				char **grid_p2, int *count)
{
	if (dir == 'H' && y <= m - 4) {
		for (int i = 0; i < 5; i++) {
			if (*count % 2 == 0) {
				grid_p1[x][y + i] = '5';
			} else {
				grid_p2[x][y + i] = '5';
			}
		}
		(*count)++;
	}
	if (dir == 'V' && x >= 5) {
		for (int i = 0; i < 5; i++) {
			if (*count % 2 == 0) {
				grid_p1[x - i][y] = '5';
			} else {
				grid_p2[x - i][y] = '5';
			}
		}
		(*count)++;
	}
}

//functia if_yamato modifica tabla unui jucator plasand nava de tip Yamato
//in functie de orientarea ei, punand valoarea 4 pe tabla de joc in locul
//in care este amplasata.
void if_yamato(int m, char dir, int x, int y, char **grid_p1,
			   char **grid_p2, int *count)
{
	if (dir == 'H' && y <= m - 3) {
		for (int i = 0; i < 4; i++) {
			if (*count % 2 == 0) {
				grid_p1[x][y + i] = '4';
			} else {
				grid_p2[x][y + i] = '4';
			}
		}
		(*count)++;
	}
	if (dir == 'V' && x >= 4) {
		for (int i = 0; i < 4; i++) {
			if (*count % 2 == 0) {
				grid_p1[x - i][y] = '4';
			} else {
				grid_p2[x - i][y] = '4';
			}
		}
		(*count)++;
	}
}

//functia if_belfast modifica tabla unui jucator plasand nava de tip Belfast
//in functie de orientarea ei, punand valoarea 3 pe tabla de joc in locul
//in care este amplasata.
void if_belfast(int m, char dir, int x, int y, char **grid_p1,
				char **grid_p2, int *count)
{
	if (dir == 'H' && y <= m - 2) {
		for (int i = 0; i < 3; i++) {
			if (*count % 2 == 0) {
				grid_p1[x][y + i] = '3';
			} else {
				grid_p2[x][y + i] = '3';
			}
		}
		(*count)++;
	}
	if (dir == 'V' && x >= 3) {
		for (int i = 0; i < 3; i++) {
			if (*count % 2 == 0) {
				grid_p1[x - i][y] = '3';
			} else {
				grid_p2[x - i][y] = '3';
			}
		}
		(*count)++;
	}
}

//functia if_laffey modifica tabla unui jucator plasand nava de tip Laffey
//in functie de orientarea ei, punand valoarea 2 pe tabla de joc in locul
//in care este amplasata.
void if_laffey(int m, char dir, int x, int y, char **grid_p1,
			   char **grid_p2, int *count)
{
	if (dir == 'H' && y <= m - 1) {
		for (int i = 0; i < 2; i++) {
			if (*count % 2 == 0) {
				grid_p1[x][y + i] = '2';
			} else {
				grid_p2[x][y + i] = '2';
			}
		}
		(*count)++;
	}
	if (dir == 'V' && x >= 2) {
		for (int i = 0; i < 2; i++) {
			if (*count % 2 == 0) {
				grid_p1[x - i][y] = '2';
			} else {
				grid_p2[x - i][y] = '2';
			}
		}
		(*count)++;
	}
}

//functia if_albacore modifica tabla unui jucator plasand nava de tip Albacore
//in functie de orientarea ei, punand valoarea 1 pe tabla de joc in locul
//in care este amplasata.
void if_albacore(int x, int y, char **grid_p1, char **grid_p2, int *count)
{
	if (*count % 2 == 0) {
		grid_p1[x][y] = '1';
	} else {
		grid_p2[x][y] = '1';
	}
	(*count)++;
}

//functia place_ships imi verifica tipul de nava si o amplaseaza pe tabla.
//Returneaza variabila count ce semnifica trecerea de la tura unui jucator
//la celalalt.
int place_ships(char **grid_p1, char **grid_p2, int m, char type, char dir,
				int x, int y, int count)
{
	if (type == 'S') {
		if_shinano(m, dir, x, y, grid_p1, grid_p2, &count);
	}
	if (type == 'Y') {
		if_yamato(m, dir, x, y, grid_p1, grid_p2, &count);
	}
	if (type == 'B') {
		if_belfast(m, dir, x, y, grid_p1, grid_p2, &count);
	}
	if (type == 'L') {
		if_laffey(m, dir, x, y, grid_p1, grid_p2, &count);
	}
	if (type == 'A') {
		if_albacore(x, y, grid_p1, grid_p2, &count);
	}
	return count;
}

//functia create_grids imi modifica tabla de joc al unui player, verificand
//daca coordonatele, directia si tipul citite creeaza o nava valida si daca da
//o plaseaza pe tabla, variabila count crescand si astfel incepand tura
//celuilalt jucator. Daca nu, variabila count nu creste si ramane tura acelui
//jucator.
void create_grids(int n, int m, char **grid_p1, char **grid_p2,
				  shipbow *bow_p1, shipbow *bow_p2)
{
	int ok = 0, count = 0, bows_num_p1 = 0, bows_num_p2 = 0;
	int total_ships = num_of_ships(n, m);
	while (ok == 0) {
		char type, dir;
		scanf(" %c %c", &type, &dir);
		int x, y, valid = 1;
		scanf("%d%d", &x, &y);
		if (count % 2 == 0) {
			valid = wrong_place(grid_p1, n, m, type, dir, x, y, valid);
		} else {
			valid = wrong_place(grid_p2, n, m, type, dir, x, y, valid);
		}
		if (valid == 1) {
			if (count % 2 == 0) {
				ship_bows(bow_p1, &bows_num_p1, x, y, dir, type);
			} else {
				ship_bows(bow_p2, &bows_num_p2, x, y, dir, type);
			}
			count = place_ships(grid_p1, grid_p2, m, type, dir, x, y,
								count);
		}
		if (count == total_ships) {
			ok = 1;
		}
	}
}

//structura game_info contine acuratetea, numarul de atacuri ratate, numarul
//de atacuri nimerite si numarul de nave pentru fiecare meci jucat.
typedef struct {
	float accuracy;
	int misses;
	int hits;
	int num_ships;
} game_info;

//functia if_miss verifica daca un atac a lovit un spatiu ce nu contine o nava,
//sau daca a lovit o bucata nelovita inainte ca nava sa fie distrusa din capat,
//sau daca a lovit o celula deja atacata.
void if_miss(char **grid, int x, int y, int count, int *miss)
{
	if (grid[x][y] == '\0') {
		grid[x][y] = 'M';
		printf("Jucatorul %d a ratat o lovitura la"
			   " coordonatele (%d, %d).\n", (count % 2 + 1), x, y);
		*miss = 1;
	} else {
		if (grid[x][y] == 'D') {
			grid[x][y] = 'X';
			printf("Jucatorul %d a ratat o lovitura la"
				   " coordonatele (%d, %d).\n", (count % 2 + 1), x, y);
			*miss = 1;
		} else {
			if (grid[x][y] == 'X' || grid[x][y] == 'M') {
				printf("Coordonatele (%d, %d) au fost deja"
					   " atacate de jucatorul %d.\n", x, y, (count % 2 + 1));
				*miss = 1;
			}
		}
	}
}

//functia verifica daca o celula este chiar capatul unei nave si returneaza
//indicele navei daca este si -1 daca nu este.
int if_bow(shipbow *bow_p, int total_ships, int x, int y)
{
	int bow = -1;
	for (int i = 0; i < total_ships / 2 && bow == -1; i++) {
		if (bow_p[i].sunk == 0 && x == bow_p[i].x && y == bow_p[i].y) {
			bow = i;
		}
	}
	return bow;
}

//functia print_destroy_message imi afiseaza mesajul de distrugere al unei nave.
void print_destroy_message(int type, char dir, int x, int y, int count)
{
	if (type == 1) {
		printf("Jucatorul %d a distrus o nava Albacore plasata intre "
				   "coordonatele (%d, %d) si (%d, %d).\n", (count % 2 + 1),
				   x, y, x, y);
	}
	if (dir == 'H') {
		switch (type) {
		case 2:
			printf("Jucatorul %d a distrus o nava Laffey plasata intre "
				   "coordonatele (%d, %d) si (%d, %d).\n", (count % 2 + 1),
				   x, y, x, y + 1);
			break;
		case 3:
			printf("Jucatorul %d a distrus o nava Belfast plasata intre "
				   "coordonatele (%d, %d) si (%d, %d).\n", (count % 2 + 1),
				   x, y, x, y + 2);
			break;
		case 4:
			printf("Jucatorul %d a distrus o nava Yamato plasata intre "
				   "coordonatele (%d, %d) si (%d, %d).\n",
				   (count % 2 + 1), x, y, x, y + 3);
			break;
		case 5:
			printf("Jucatorul %d a distrus o nava Shinano plasata intre "
				   "coordonatele (%d, %d) si (%d, %d).\n",
				   (count % 2 + 1), x, y, x, y + 4);
			break;
		}
	}
	if (dir == 'V') {
		switch (type) {
		case 2:
			printf("Jucatorul %d a distrus o nava Laffey plasata intre "
				   "coordonatele (%d, %d) si (%d, %d).\n", (count % 2 + 1),
				   x, y, x - 1, y);
			break;
		case 3:
			printf("Jucatorul %d a distrus o nava Belfast plasata intre "
				   "coordonatele (%d, %d) si (%d, %d).\n",
				   (count % 2 + 1), x, y, x - 2, y);
			break;
		case 4:
			printf("Jucatorul %d a distrus o nava Yamato plasata intre "
				   "coordonatele (%d, %d) si (%d, %d).\n",
				   (count % 2 + 1), x, y, x - 3, y);
			break;
		case 5:
			printf("Jucatorul %d a distrus o nava Shinano plasata intre "
				   "coordonatele (%d, %d) si (%d, %d).\n",
				   (count % 2 + 1), x, y, x - 4, y);
			break;
		}
	}
}

//functia destroy_ship modifica tabla de joc al jucatorului opus celui
//care a atacat  atunci cand jucatorul a lovit capatul unei nave. Schimba
//toate bucatile navei care nu au mai fost lovite in D.
void destroy_ship(char **grid, char dir, int x, int y, int ship)
{
	if (dir == 'H') {
		for (int i = 1; i < ship; i++) {
			if (grid[x][y + i] != 'X') {
				grid[x][y + i] = 'D';
			}
		}
	} else {
		for (int i = 1; i < ship; i++) {
			if (grid[x - i][y] != 'X') {
				grid[x - i][y] = 'D';
			}
		}
	}
}

//functia if_bow_true imi distruge nava atunci cnad este lovita in capat.
//Capatul devine pe tabla de joc X si bucatile navei care nu au mai fost
//atacate deja devin D. Acea nava este marcata acum ca scufundata. Este
//afisat si mesajul de distrugere.
void if_bow_true(char **grid, shipbow *bow_p, int bow, int x, int y,
				 int count, int *ships_p)
{
	int ship = grid[x][y] - '0';
	grid[x][y] = 'X';
	char dir = bow_p[bow].dir;
	switch (ship) {
	case 1:
		print_destroy_message(1, dir, x, y, count);
		break;
	case 2:
		destroy_ship(grid, dir, x, y, 2);
		print_destroy_message(2, dir, x, y, count);
		break;
	case 3:
		destroy_ship(grid, dir, x, y, 3);
		print_destroy_message(3, dir, x, y, count);
		break;
	case 4:
		destroy_ship(grid, dir, x, y, 4);
		print_destroy_message(4, dir, x, y, count);
		break;
	case 5:
		destroy_ship(grid, dir, x, y, 5);
		print_destroy_message(5, dir, x, y, count);
		break;
	}
	bow_p[bow].sunk = 1;
	(*ships_p)--;
}

//functia if_hit imi afiseaza un mesaj de lovire a unei parti ale unei nave si
//o marcheaza cu X pe tabla de joc.
void if_hit(char **grid_p, int x, int y, int count)
{
	switch (grid_p[x][y]) {
	case '2':
		printf("Jucatorul %d a lovit o nava Laffey la "
			   "coordonatele (%d, %d).\n", (count % 2 + 1), x, y);
		break;
	case '3':
		printf("Jucatorul %d a lovit o nava Belfast la "
			   "coordonatele (%d, %d).\n", (count % 2 + 1), x, y);
		break;
	case '4':
		printf("Jucatorul %d a lovit o nava Yamato la "
			   "coordonatele (%d, %d).\n", (count % 2 + 1), x, y);
		break;
	case '5':
		printf("Jucatorul %d a lovit o nava Shinano la "
			   "coordonatele (%d, %d).\n", (count % 2 + 1), x, y);
		break;
	}
	grid_p[x][y] = 'X';
}

//functia attack verifica daca atacul este ratat sau nimerit si il retine in
//vectorul de struct game_info. Returneaza numarul de nave ramas dupa atac.
int attack(char **grid_p, shipbow *bow_p, int total_ships, int ships_p,
		   int atac_x, int atac_y, int count, game_info *game_p, int num_game)
{
	int miss = 0;
	if_miss(grid_p, atac_x, atac_y, count, &miss);
	if (miss == 0) {
		game_p[num_game].hits++;
		int bow;
		bow = if_bow(bow_p, total_ships, atac_x, atac_y);
		if (bow != -1) {
			if_bow_true(grid_p, bow_p, bow, atac_x, atac_y,
						count, &ships_p);
		} else {
			if (grid_p[atac_x][atac_y] != '\0' &&
				grid_p[atac_x][atac_y] != 'X' &&
				grid_p[atac_x][atac_y] != 'M' &&
				grid_p[atac_x][atac_y] != 'D') {
				if_hit(grid_p, atac_x, atac_y, count);
			}
		}
	} else {
		game_p[num_game].misses++;
	}
	return ships_p;
}

//functia simulate_game imi citeste coordonatele atacurilor unui meci pana cand
//unul dintre jucatori ramane fara nave. daca jucatorul doi ramane fara nave
//functia returneaza 1, iar daca jucatorul unu ramane fara nave returneaza 2.
int simulate_game(int n, int m, char **grid_p1, char **grid_p2,
				  shipbow *bow_p1, shipbow *bow_p2, game_info *game_p1,
				  game_info *game_p2, int num_game)
{
	int total_ships = num_of_ships(n, m);
	int win1 = 0, win2 = 0;
	int ships_p1 = total_ships / 2, ships_p2 = total_ships / 2;
	int count = 0;
	while (win1 == 0 && win2 == 0) {
		int atac_x, atac_y;
		scanf("%d%d", &atac_x, &atac_y);
		if (count % 2 == 0) {
			ships_p2 = attack(grid_p2, bow_p2, total_ships, ships_p2,
							  atac_x, atac_y, count, game_p1, num_game);
			count++;
		} else {
			ships_p1 = attack(grid_p1, bow_p1, total_ships, ships_p1,
							  atac_x, atac_y, count, game_p2, num_game);
			count++;
		}
		if (ships_p2 == 0) {
			win1 = 1;
		}
		if (ships_p1 == 0) {
			win2 = 1;
		}
	}
	if (win1 == 1) {
		return 1;
	} else {
		return 2;
	}
}

//functia calc_tot_acc calculeaza si returneaza acuratetea totala pe toate
//meciurile.
float calc_tot_acc(game_info *game_p, int num_game)
{
	unsigned int all_ships_p = 0;
	float sum_acc_p = 0.0f;
	for (int i = 1; i <= num_game; i++) {
		sum_acc_p = (float)sum_acc_p + game_p[i].accuracy * game_p[i].num_ships;
		all_ships_p = all_ships_p + game_p[i].num_ships;
	}
	float total_acc_p;
	total_acc_p = (float)sum_acc_p / all_ships_p;
	return total_acc_p;
}

//structura statistics contine componentele statisticii pe care vrem sa o
//aflam pentru problema 2.
typedef struct {
	char player;
	char tip1;
	int A;
	float B;
	char *tip2;
} statistics;

//functia separate_text imi separa statistica citita si de calculat la
//problema 2 si returneaza prin variabila de tip statistics.
statistics separate_text(char *text)
{
	statistics message;
	message.tip2 = (char *)calloc(4, sizeof(char));
	if (!message.tip2) {
		fprintf(stderr, "Failed to allocate tip2.\n");
		exit(EXIT_FAILURE);
	}
	message.player = text[0];
	message.tip1 = text[1];
	message.A = 100 * (text[2] - '0') + 10 * (text[3] - '0') + text[4] - '0';
	char *X = (char *)malloc(7 * sizeof(char));
	if (!X) {
		fprintf(stderr, "Failed to allocate temporary buffer X.\n");
		free(message.tip2);
		exit(EXIT_FAILURE);
	}
	strncpy(X, text + 5, 6);
	X[6] = '\0';
	message.B = atof(X);
	free(X);
	strncpy(message.tip2, text + 11, 3);
	message.tip2[3] = '\0';
	return message;
}

//functia sort_game_for_min imi sorteaza vectorul de tip game_info cu toate
//informatiile despre fiecare meci in functie de impactul pe care il are asupra
//acuratetei totale finale. Meciurile care au cel mai mare impact sunt puse la
//inceputul vectorului.
void sort_game_for_min(game_info *vector, int n)
{
	for (int i = 1; i < n; i++) {
		for (int j = i + 1; j <= n; j++) {
			float gain_i = (100.0f - vector[i].accuracy) * vector[i].num_ships;
			float gain_j = (100.0f - vector[j].accuracy) * vector[j].num_ships;
			if (gain_i < gain_j) {
				game_info aux = vector[i];
				vector[i] = vector[j];
				vector[j] = aux;
			}
		}
	}
}

//functia sort_game_for_max imi sorteaza vectorul de tip game_info cu toate
//informatiile despre fiecare meci in functie de impactul pe care il are asupra
//acuratetei totale finale. Meciurile care au cel mai mare impact sunt puse la
//finalul vectorului.
void sort_game_for_max(game_info *vector, int n)
{
	for (int i = 1; i < n; i++) {
		for (int j = i + 1; j <= n; j++) {
			if (vector[i].accuracy * vector[i].num_ships > vector[j].accuracy *
				vector[j].num_ships) {
				game_info aux = vector[i];
				vector[i] = vector[j];
				vector[j] = aux;
			}
		}
	}
}

//functia write_stat imi scrie statistica finala intr-un sir de caractere.
void write_stat(float shown, int minmax, char *stat)
{
	snprintf(stat, 12, "0%.2f.%d", shown, minmax);
}

//functia task_2_and_4 indeplineste cerintele 2 si 4 de la problema 2. Pentru
//cazul in care vrem sa calculam numarul minim de lovituri, verificam daca
//acuratetea meciului este mai mica decat cea cu care vrem sa o comparam. Daca
//este mai mica atunci marim cu 1 numarul de atacuri nimerite si scadem cu 1
//atacurile ratate si recalculam acuratetea. Numaram si cate lovituri trebuie
//modificate pentru a putea afisa statistica la sfarsit. Se repeta pana cand
//acuratetea este mai mare sau egala cu valoarea cu care o comparam. La sfarsit,
//salvam statistica intr-un sir de caractere stat. Pentru cazul in care vrem sa
//calculam numarul maxim de lovituri, verificam daca acuratetea meciului este
//mai mare decat cea cu care vrem sa o comparam. Daca este mai mare atunci
//marim cu 1 numarul de atacuri ratate si scadem cu 1 atacurile nimerite
//recalculam acuratetea. Numaram si cate lovituri trebuie modificate pentru a
//putea afisa statistica la sfarsit. Se repeta pana cand acuratetea este mai
//mica sau egala cu valoarea cu care o comparam. La sfarsit, salvam statistica
//intr-un sir de caractere stat.
void task_2_and_4(game_info *game_p, statistics message, char *stat)
{
	game_info copy = game_p[message.A];
	if (strcmp(message.tip2, "MIN") == 0) {
		int min_miss = 0;
		while (1) {
			if (copy.accuracy >= message.B) {
				break;
			}
			copy.misses--;
			copy.hits++;
			min_miss++;
			copy.accuracy = (float)copy.hits / (copy.hits + copy.misses) * 100;
		}
		float shown_acc = game_p[message.A].accuracy;
		shown_acc = (int)(shown_acc * 100) / 100.0;
		write_stat(shown_acc, min_miss, stat);
	} else {
		int max_miss = 0;
		while (1) {
			if (copy.accuracy <= message.B) {
				break;
			}
			copy.misses++;
			copy.hits--;
			max_miss++;
			copy.accuracy = (float)copy.hits / (copy.hits + copy.misses) * 100;
			if (copy.accuracy <= message.B) {
				max_miss--;
				break;
			}
		}
		float shown_acc = game_p[message.A].accuracy;
		shown_acc = (int)(shown_acc * 100) / 100.0;
		write_stat(shown_acc, max_miss, stat);
	}
}

//functia task_1_and_3 indeplineste cerintele 1 si 3 de la problema 2. Pentru
//cazul in care vrem sa calculam numarul minim de meciuri, sortam informatiile
//despre meciuri si apoi verificam daca acuratetea totala este mai mica decat
//cea cu care vrem sa o comparam. Daca este mai mica atunci modificam
//acuratetea pentru meciul cu cel mai mare impact asupra acuratetei finale la
//100. Repetam pana cand devine mai mare decat acuratetea finala si salvam
//statistica intr-un sir de caractere stat. Pentru cazul in care vrem sa
//calculam numarul maxim de meciuri, sortam informatiile despre meciuri si apoi
//verificam daca acuratetea totala este mai mare decat cea cu care vrem sa o
//comparam. Daca este mai mare atunci modificam acuratetea pentru meciul cu cel
//mai mic impact asupra acuratetei finale la 0. Repetam pana cand devine mai
//mica decat acuratetea finala si salvam statistica intr-un sir de caractere
//stat.
void task_1_and_3(game_info *game_p, statistics message, int num_game,
				  char *stat)
{
	game_info *copy = malloc((num_game + 1) * sizeof(game_info));
	if (!copy) {
		fprintf(stderr, "Failed to allocate copy of game_info.\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 1; i <= num_game; i++) {
		copy[i] = game_p[i];
	}
	float total_acc_p = calc_tot_acc(game_p, num_game);
	float copy_total_acc_p = total_acc_p;
	if (strcmp(message.tip2, "MIN") == 0) {
		sort_game_for_min(copy, num_game);
		int min_game = 0;
		for (int i = 1; i <= num_game && copy_total_acc_p <
			 message.B; i++) {
			min_game++;
			copy[i].accuracy = 100.0f;
			copy_total_acc_p = calc_tot_acc(copy, num_game);
		}
		float shown_total = total_acc_p;
		shown_total = (int)(shown_total * 100) / 100.0;
		write_stat(shown_total, min_game, stat);
	} else {
		sort_game_for_max(copy, num_game);
		int max_game = 0;
		while (1) {
			if (copy_total_acc_p <= message.B) {
				break;
			}
			max_game++;
			copy[max_game].accuracy = 0.0f;
			copy_total_acc_p = calc_tot_acc(copy, num_game);
			if (copy_total_acc_p <= message.B) {
				max_game--;
				break;
			}
		}
		float shown_total = total_acc_p;
		shown_total = (int)(shown_total * 100) / 100.0;
		write_stat(shown_total, max_game, stat);
	}
	free(copy);
}

//functia gen_alphabet imi creeaza alfabetul pentru problema 3.
void gen_alphabet(char *alphabet)
{
	int count = 0;
	for (char c = '0'; c <= '9'; c++) {
		alphabet[count] = c;
		count++;
	}
	for (char c = 'A'; c <= 'Z'; c++) {
		alphabet[count] = c;
		count++;
	}
	alphabet[36] = '.';
	alphabet[37] = '\0';
}

//functia to_number imi returneaza numarul ce corespunde caracterului in
//alfabetul creat.
int to_number(char *alphabet, char letter)
{
	for (int i = 0; i < (int)strlen(alphabet); i++) {
		if (letter == alphabet[i])
			return i;
	}
	return -1;
}

//functia to_letter imi returneaza caracterul caruia ii corespunde numarul in
//alfabetul creat.
char to_letter(char *alphabet, int number)
{
	for (int i = 0; i < (int)strlen(alphabet); i++) {
		if (number == i)
			return alphabet[i];
	}
	return '?';
}

//functia det_3 returneaza determinantul unei matrice de ordin 3.
int det_3(int **m)
{
	int det;
	det = m[0][0] * m[1][1] * m[2][2] + m[1][0] * m[2][1] * m[0][2] +
		  m[0][1] * m[1][2] * m[2][0] - (m[0][2] * m[1][1] * m[2][0] +
		  m[0][0] * m[2][1] * m[1][2] + m[1][0] * m[0][1] * m[2][2]);
	return det;
}

//functia det_2 returneaza determinantul unei matrice de ordin 2.
int det_2(int **m)
{
	int det;
	det = m[0][0] * m[1][1] - m[0][1] * m[1][0];
	return det;
}

//functia det_1 returneaza determinantul unei matrice de ordin 1.
int det_1(int **m)
{
	int det;
	det = m[0][0];
	return det;
}

//functia message_to_column transforma un mesaj intr-un vector ce contine
//numarul ce ii corespunde fiecarui caracter in alfabetul creat.
void message_to_column(char *alphabet, char *message, int *message_v, int len)
{
	for (int i = 0; i < len; i++) {
		int number = to_number(alphabet, message[i]);
		message_v[i] = number;
	}
}

//functia key_to_matrix transforma cheia primita intr-o matrice ce contine
//numarul ce ii corespunde fiecarui caracter in aflabetul in creat.
void key_to_matrix(char *alphabet, char *key, int **key_m, int len_m)
{
	int count = 0;
	for (int i = 0; i < len_m; i++) {
		for (int j = 0; j < len_m; j++) {
			int number = to_number(alphabet, key[count]);
			count++;
			key_m[i][j] = number;
		}
	}
}

//functia multiply_m_v imi inmulteste o matrice patratica cu o matrice coloana.
void multiply_m_v(int **m, int *v, int size, int *result)
{
	for (int i = 0; i < size; i++) {
		result[i] = 0;
		for (int j = 0; j < size; j++) {
			result[i] = result[i] + m[i][j] * v[j];
		}
	}
}

//functia mod returneaza a mod m.
int mod(int a, int m)
{
	int r = a % m;
	if (r < 0) {
		r += m;
	}
	return r;
}

//functia mod_vect_elem imi aplica functia mod pe fiecare element al unui
//vector.
void mod_vect_elem(int *v, int size, int k)
{
	for (int i = 0; i < size; i++) {
		v[i] =  mod(v[i], k);
	}
}

//functia encode_block urmeaza pasii problemei 3 pentru codificarea unui bloc
//de lungime 3, 2 sau 1.
void encode_block(char *alphabet, char *message, char *key,
				  int len_m, char *en_mess)
{
	int *mess_v = (int *)malloc(len_m * sizeof(int));
	if (!mess_v) {
		fprintf(stderr, "Failed to allocate mess_v.\n"); exit(EXIT_FAILURE);
	}
	int **key_m = allocate_int_matrix(len_m);
	int *result = (int *)malloc(len_m * sizeof(int));
	if (!result) {
		fprintf(stderr, "Failed to allocate result.\n"); exit(EXIT_FAILURE);
	}
	message_to_column(alphabet, message, mess_v, len_m);
	key_to_matrix(alphabet, key, key_m, len_m);
	multiply_m_v(key_m, mess_v, len_m, result);
	mod_vect_elem(result, len_m, strlen(alphabet));
	for (int i = 0; i < len_m; i++) {
		en_mess[i] = to_letter(alphabet, result[i]);
	}
	en_mess[len_m] = '\0';
	free(mess_v);
	free_int_matrix(key_m, len_m);
	free(result);
}

//functia modular_inverse reprezinta algoritmul lui Euclid extins.
int modular_inverse(int a, int k)
{
	int k0 = k;
	int t, q;
	int x0 = 0, x1 = 1;
	while (a > 1) {
		q = a / k;
		t = k;
		k = a % k;
		a = t;
		t = x0;
		x0 = x1 - q * x0;
		x1 = t;
	}
	if (x1 < 0) {
		x1 = x1 + k0;
	}
	return x1;
}

//functia matrix_minor imi calculeaza minorul unei matrice.
void matrix_minor(int **m, int size, int line, int col, int **minor)
{
	int count_i = 0;
	for (int i = 0; i < size; i++) {
		int count_j = 0;
		if (i != line) {
			for (int j = 0; j < size; j++) {
				if (j != col) {
					minor[count_i][count_j] = m[i][j];
					count_j++;
				}
			}
			count_i++;
		}
	}
}

//functia power_of_minus imi returneazz 1 daca puterea lui 1, i + j, este para,
//sau -1 daca este impara.
int power_of_minus1(int i, int j)
{
	if ((i + j) % 2 == 0) {
		return 1;
	} else {
		return -1;
	}
}

//functia transpose imi transpune liniile cu coloanele unei matrice.
void transpose(int **m, int size)
{
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			int aux = m[i][j];
			m[i][j] = m[j][i];
			m[j][i] = aux;
		}
	}
}

//functia calc_adjunct imi calculeaza adjuncta unei matrice.
void calc_adjunct(int **m, int size, int **adjunct)
{
	if (size == 1) {
		adjunct[0][0] = 1;
		return;
	}
	int **minor = allocate_int_matrix(size - 1);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			matrix_minor(m, size, i, j, minor);
			int det;
			if (size == 3) {
				det = det_2(minor);
			} else {
				det = det_1(minor);
			}
			adjunct[i][j] = power_of_minus1(i, j) * det;
		}
	}
	free_int_matrix(minor, size - 1);
	transpose(adjunct, size);
}

//functia multiply_matrix_elem imi inmulteste fiecare element dintr-o matrice
//cu un numar x.
void multiply_matrix_elem(int **m, int size, int x)
{
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			m[i][j] = m[i][j] * x;
		}
	}
}

//functia mod_matrix_elem imi aplica functia mod asupra fiecarui element
//dintr-o matrice.
void mod_matrix_elem(int **m, int size, int k)
{
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			m[i][j] = mod(m[i][j], k);
		}
	}
}

//functia decode_block urmeaza pasii problemei 3 pentru decodificare unui bloc
//de lungime 3, 2 sau 1.
void decode_block(char *alphabet, char *en_mess, char *key, int len_m,
				  char *message)
{
	int *en_mess_v = (int *)malloc(len_m * sizeof(int));
	if (!en_mess_v) {
		fprintf(stderr, "Failed to allocate en_mess_v.\n"); exit(EXIT_FAILURE);
	}
	int **key_m = allocate_int_matrix(len_m);
	message_to_column(alphabet, en_mess, en_mess_v, len_m);
	key_to_matrix(alphabet, key, key_m, len_m);
	int det;
	if (len_m == 3) {
		det = det_3(key_m);
	} else {
		if (len_m == 2) {
			det = det_2(key_m);
		} else {
			det = det_1(key_m);
		}
	}
	det = mod(det, strlen(alphabet));
	int x = modular_inverse(det, (int)strlen(alphabet));
	int **adjunct = allocate_int_matrix(len_m);
	calc_adjunct(key_m, len_m, adjunct);
	multiply_matrix_elem(adjunct, len_m, x);
	mod_matrix_elem(adjunct, len_m, strlen(alphabet));
	int *result = (int *)malloc(len_m * sizeof(int));
	if (!result) {
		fprintf(stderr, "Failed to allocate result.\n"); exit(EXIT_FAILURE);
	}
	multiply_m_v(adjunct, en_mess_v, len_m, result);
	mod_vect_elem(result, len_m, strlen(alphabet));
	for (int i = 0; i < len_m; i++) {
		message[i] = to_letter(alphabet, result[i]);
	}
	message[len_m] = '\0';
	free(en_mess_v);
	free_int_matrix(key_m, len_m);
	free_int_matrix(adjunct, len_m);
	free(result);
}

//functia decode_text imi decodifica un mesaj pe blocuri de cate 3 caractere,
//apoi de cate 2 sau de cate 1 si imi salveaza in decod_stat mesajul
//decodificat.
void decode_text(char *key, char *text, char *alphabet, char *decod_stat)
{
	int len = strlen(text);
	int index = 0;
	int pos = 0;
	while (index + 3 <= len) {
		char *block = (char *)malloc(4 * sizeof(char));
		if (!block) {
			fprintf(stderr, "Failed to allocate block.\n");
			exit(EXIT_FAILURE);
		}
		strncpy(block, text + index, 3);
		block[3] = '\0';
		char *out = (char *)malloc(4 * sizeof(char));
		if (!out) {
			fprintf(stderr, "Failed to allocate out.\n");
			exit(EXIT_FAILURE);
		}
		decode_block(alphabet, block, key, strlen(block), out);
		strcpy(decod_stat + pos, out);
		pos = pos + 3;
		index = index + 3;
		free(block);
		free(out);
	}
	if (len - index == 2) {
		char *block = (char *)malloc(3 * sizeof(char));
		if (!block) {
			fprintf(stderr, "Failed to allocate block.\n");
			exit(EXIT_FAILURE);
		}
		strncpy(block, text + index, 2);
		block[2] = '\0';
		char *key2 = (char *)malloc(5 * sizeof(char));
		if (!key2) {
			fprintf(stderr, "Failed to allocate key2.\n");
			exit(EXIT_FAILURE);
		}
		strncpy(key2, key, 4);
		key2[4] = '\0';
		char *out = (char *)malloc(3 * sizeof(char));
		if (!out) {
			fprintf(stderr, "Failed to allocate out.\n");
			exit(EXIT_FAILURE);
		}
		decode_block(alphabet, block, key2, strlen(block), out);
		strcpy(decod_stat + pos, out);
		pos = pos + 2;
		free(block);
		free(key2);
		free(out);
	}
	if (len - index == 1) {
		char *block = (char *)malloc(2 * sizeof(char));
		if (!block) {
			fprintf(stderr, "Failed to allocate block.\n");
			exit(EXIT_FAILURE);
		}
		block[0] = text[index];
		block[1] = '\0';
		char *key1 = (char *)malloc(2 * sizeof(char));
		if (!key1) {
			fprintf(stderr, "Failed to allocate key1.\n");
			exit(EXIT_FAILURE);
		}
		key1[0] = key[0];
		key1[1] = '\0';
		char *out = (char *)malloc(2 * sizeof(char));
		if (!out) {
			fprintf(stderr, "Failed to allocate out.\n");
			exit(EXIT_FAILURE);
		}
		decode_block(alphabet, block, key1, strlen(block), out);
		strcpy(decod_stat + pos, out);
		pos = pos + 1;
		free(block);
		free(key1);
		free(out);
	}
	decod_stat[pos] = '\0';
}

//functia encode_text imi codifica un mesaj pe blocuri de cate 3 caractere,
//apoi de cate 2 sau de cate 1 si imi salveaza in encod_stat mesajul
//decodificat.
void encode_text(char *key, char *text, char *alphabet, char *encod_stat)
{
	int len = strlen(text);
	int index = 0;
	int pos = 0;
	while (index + 3 <= len) {
		char *block = (char *)malloc(4 * sizeof(char));
		if (!block) {
			fprintf(stderr, "Failed to allocate block.\n");
			exit(EXIT_FAILURE);
		}
		strncpy(block, text + index, 3);
		block[3] = '\0';
		char *out = (char *)malloc(4 * sizeof(char));
		if (!out) {
			fprintf(stderr, "Failed to allocate out.\n");
			exit(EXIT_FAILURE);
		}
		encode_block(alphabet, block, key, strlen(block), out);
		strcpy(encod_stat + pos, out);
		pos = pos + 3;
		index = index + 3;
		free(block);
		free(out);
	}
	if (len - index == 2) {
		char *block = (char *)malloc(3 * sizeof(char));
		if (!block) {
			fprintf(stderr, "Failed to allocate block.\n");
			exit(EXIT_FAILURE);
		}
		strncpy(block, text + index, 2);
		block[2] = '\0';
		char *key2 = (char *)malloc(5 * sizeof(char));
		if (!key2) {
			fprintf(stderr, "Failed to allocate key2.\n");
			exit(EXIT_FAILURE);
		}
		strncpy(key2, key, 4);
		key2[4] = '\0';
		char *out = (char *)malloc(3 * sizeof(char));
		if (!out) {
			fprintf(stderr, "Failed to allocate out.\n");
			exit(EXIT_FAILURE);
		}
		encode_block(alphabet, block, key2, strlen(block), out);
		strcpy(encod_stat + pos, out);
		pos = pos + 2;
		free(block);
		free(key2);
		free(out);
	}
	if (len - index == 1) {
		char *block = (char *)malloc(2 * sizeof(char));
		if (!block) {
			fprintf(stderr, "Failed to allocate block.\n");
			exit(EXIT_FAILURE);
		}
		block[0] = text[index];
		block[1] = '\0';
		char *key1 = (char *)malloc(2 * sizeof(char));
		if (!key1) {
			fprintf(stderr, "Failed to allocate key1.\n");
			exit(EXIT_FAILURE);
		}
		key1[0] = key[0];
		key1[1] = '\0';
		char *out = (char *)malloc(2 * sizeof(char));
		if (!out) {
			fprintf(stderr, "Failed to allocate out.\n");
			exit(EXIT_FAILURE);
		}
		encode_block(alphabet, block, key1, strlen(block), out);
		strcpy(encod_stat + pos, out);
		pos = pos + 1;
		free(block);
		free(key1);
		free(out);
	}
	encod_stat[pos] = '\0';
}

//functia prob2and3_onegame rezolva problemele 2 si 3 pentru cerintele 2 si 4.
void prob2and3_onegame(int num_game, game_info *game_p, char *stat,
					   statistics message, char *key, char *alphabet)
{
	if (message.A > num_game) {
		printf("Nu exista date pentru meciul cerut.\n");
	} else {
		task_2_and_4(game_p, message, stat);
		if (strcmp(key, "-") == 0) {
			printf("%s\n", stat);
			free(stat);
		} else {
			char *encoded_stat = (char *)malloc(12 * sizeof(char));
			encode_text(key, stat, alphabet, encoded_stat);
			printf("%s\n", encoded_stat);
			free(encoded_stat);
			free(stat);
		}
	}
}

//functia prob2and3_allgames rezolva problemele 2 si 3 pentru cerintele 1 si 3.
void prob2and3_allgames(int num_game, game_info *game_p, char *stat,
						statistics message, char *key, char *alphabet)
{
	task_1_and_3(game_p, message, num_game, stat);
	if (strcmp(key, "-") == 0) {
		printf("%s\n", stat);
		free(stat);
	} else {
		char *encoded_stat = (char *)malloc(12 * sizeof(char));
		encode_text(key, stat, alphabet, encoded_stat);
		printf("%s\n", encoded_stat);
		free(encoded_stat);
		free(stat);
	}
}

//functia prob2an3 rezolva problemele 2 si 3.
void prob2and3(char *text, int num_game, game_info *game_p1,
			   game_info *game_p2, char *key, char *alphabet)
{
	char *stat = (char *)malloc(12 * sizeof(char));
	statistics message = separate_text(text);
	if (message.player == 'O') {
		if (message.tip1 == 'U') {
			prob2and3_onegame(num_game, game_p1, stat, message, key,
							  alphabet);
		} else {
			prob2and3_allgames(num_game, game_p1, stat, message, key,
							   alphabet);
		}
	} else {
		if (message.tip1 == 'U') {
			prob2and3_onegame(num_game, game_p2, stat, message, key,
							  alphabet);
		} else {
			prob2and3_allgames(num_game, game_p2, stat, message, key,
							   alphabet);
		}
	}
	free(message.tip2);
}

int main(void)
{
	int j = 0;
	if (scanf("%d", &j) != 1 || j <= 0) {
		fprintf(stderr, "Failed to read number of games\n");
		return EXIT_FAILURE;
	}
	game_info *game_p1 = (game_info *)calloc(j + 1, sizeof(game_info));
	game_info *game_p2 = (game_info *)calloc(j + 1, sizeof(game_info));
	if (!game_p1 || !game_p2) {
		fprintf(stderr, "Memory allocation failed for game info.\n");
		free(game_p1);
		free(game_p2);
		return EXIT_FAILURE;
	}
	int num_game = 0;
	while (j >= 1) {
		num_game++;
		int n, m;
		scanf("%d%d", &n, &m);
		int total_ships = num_of_ships(n, m);
		game_p1[num_game].num_ships = total_ships / 2;
		game_p2[num_game].num_ships = total_ships / 2;
		char **grid_p1 = allocate_char_matrix(n + 1, m + 1);
		char **grid_p2 = allocate_char_matrix(n + 1, m + 1);
		if (!grid_p1 || !grid_p2) {
			fprintf(stderr, "Failed to allocate grids.\n");
			return EXIT_FAILURE;
		}
		shipbow *bow_p1 = (shipbow *)calloc(total_ships / 2, sizeof(shipbow));
		shipbow *bow_p2 = (shipbow *)calloc(total_ships / 2, sizeof(shipbow));
		create_grids(n, m, grid_p1, grid_p2, bow_p1, bow_p2);
		print_char_matrix(grid_p1, n, m);
		printf("\n");
		print_char_matrix(grid_p2, n, m);
		int win;
		win = simulate_game(n, m, grid_p1, grid_p2, bow_p1, bow_p2, game_p1,
							game_p2, num_game);
		free(bow_p1);
		free(bow_p2);
		free_char_matrix(grid_p1, n + 1);
		free_char_matrix(grid_p2, n + 1);
		game_p1[num_game].accuracy = (float)game_p1[num_game].hits /
									 (game_p1[num_game].hits +
									 game_p1[num_game].misses) * 100;
		game_p2[num_game].accuracy = (float)game_p2[num_game].hits /
									 (game_p2[num_game].hits +
									 game_p2[num_game].misses) * 100;
		if (win == 1) {
			printf("Jucatorul 1 a castigat.\n");
		} else {
			printf("Jucatorul 2 a castigat.\n");
		}
		j--;
	}
	char *key = (char *)malloc(10 * sizeof(char));
	char *alphabet = (char *)malloc(38 * sizeof(char));
	gen_alphabet(alphabet);
	scanf(" %9s", key);
	if (strcmp(key, "Q") != 0) {
		char *text = (char *)malloc(16 * sizeof(char));
		scanf(" %15s", text);
		while (strcmp(text, "Q") != 0) {
			if (strcmp(key, "-") != 0) {
				char *copy = (char *)malloc(16 * sizeof(char));
				decode_text(key, text, alphabet, copy);
				strcpy(text, copy);
				free(copy);
			}
			prob2and3(text, num_game, game_p1, game_p2, key, alphabet);
			scanf(" %15s", text);
		}
		free(text);
	}
	free(alphabet);
	free(key);
	free(game_p1);
	free(game_p2);
	return 0;
}
