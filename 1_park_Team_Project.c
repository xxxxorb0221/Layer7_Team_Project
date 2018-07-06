#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<windows.h>

#define MAPSIZE 40
#define SPACE 0 // 빈공간
#define WALL 1 // 벽
#define BUSH 2 // 풀숲
#define GUN 3 // 총
#define POTION 5 //  포션
#define GINP 7 // 총을 먹은 상태의 플레이어 1
#define BINP 8 // 부쉬에 있는 상태의 플레이어 1
#define PLAYER 9 // 평상시 플레이어 1
#define GINP2 70 // 총을 먹은 상태의 플레이어2
#define BINP2 80 // 부쉬에 있는 상태의 플레이어 2
#define PLAYER2 90 // 평상시 플레이어 2
#define COL GetStdHandle(STD_OUTPUT_HANDLE) // 글자 색 지정

int playerX, playerY, playerX2, playerY2, flag = 0, flag2 = 0, gun_x, gun_y, potion_x, potion_y;
int p1 = 3; p2 = 3; // p1, p2 목숨
float ginpst, ginpst2;

int map[MAPSIZE][MAPSIZE] = { // 맵생성

	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },

{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },

};


void win_lose(); // 플레이어가 이겼을때 호출되는 함수
void print_infor(); // 플레이어의 목숨 정보를 출력하는 함수
void moveplayer(int dx, int dy); // p1의 이동함수
void moveplayer2(int dx, int dy); // p2의 이동함수
void player(); // p1 랜덤생성 함수
void player2(); // p2 랜덤생성 함수
void wall(); // 벽 랜던생성 함수
void gun(); // 총 랜덤생성 함수
void potion(); // 포션 랜덤생성 함수
void bush(); // 풀숲 랜덤생성 함수
void printmap(); // 맵을 출력하는 함수
void gotoxy(int x, int y); // 특정한 좌표로 이동하기 위해서 사용하는 함수
void p1_print(); // p1을 출력 해주는 함수
void bush_print(); // p1의 bush를 출력 해주는 함수
void space_print(); // p1의 space를 출력 해주는 함수
void binp_print(); // p1의 binp를 출력 해주는 함수
void p2_print(); // p2을 출력 해주는 함수
void bush2_print(); // p2의 bush를 출력 해주는 함수
void space2_print(); // p2의 space를 출력 해주는 함수
void binp2_print(); // p2의 binp를 출력 해주는 함수


int main() {
	system("mode con cols=120 lines=41"); // 콘솔 창 크기 지정

	srand(time(NULL)); // 랜덤생성
	int i, j;
	char playerInput;
	bush();
	wall();
	player();
	player2();
	printmap(); // 위 함수로 맵의 값이 변경되고 마지막에 맵을 출력

	for (i = 0; i < MAPSIZE; i++)
	{
		for (j = 0; j < MAPSIZE; j++)
		{
			if (map[i][j] == 9) // 맵 전체를 돌다가 p1(9)가 있으면 그때의 i,j 좌표를 각각 y,x 변수에다가 저장
			{
				playerX = j;
				playerY = i;
			}
			if (map[i][j] == 90) { // 위와 같은 방법을 p2에 적용
				playerX2 = j;
				playerY2 = i;
			}
		}
	}

	float gunst = clock(), stpt = clock(), gunet, ginpet, ginpet2, etpt; // clock 함수 쓰기위한 변수들

	while (1) {

		print_infor(); // 플레이어 정보를 출력
		win_lose(); // 어떤 플레이어가 이겼는지 출력 안이겼으면 아무것도 출력 안함

		gunet = clock() - gunst; // 총이 일정시간마다 나오도록 변수 선언할때 clock 해주었고 지금 clock 한 값에 처음 clock 한 것을 빼준것을 저장한다
		etpt = clock() - stpt; // 총이 일정시간마다 나오도록 변수 선언할때 clock 해주었고 지금 clock 한 값에 처음 clock 한 것을 빼준것을 저장한다

		if ((int)gunet >= 300) { // 만약 처음시간~마지막시간이 15초 이상이면 그때 gun함수를 실행하고 다시실행되게끔 gunst를 초기화 해준다
			for (int i = 0; i < 2; i++) {
				gun();
				gunst = clock();
			}
		}
		if ((int)etpt >= 300) { // 만약 처음시간~마지막시간이 10초 이상이면 그때 potion함수를 실행하고 다시실행되게끔 stpt를 초기화 해준다
			potion();
			stpt = clock();
		}

		ginpet = clock() - ginpst; // 15초가 되면 총효과가 사라지게끔 한것 pinpst는 총을 먹었을때 아래코드에서 clock을 해주었다
		if ((int)ginpet >= 15000) { // 처음~마지막 간격이 15초이상이면 flag = 0 (총이 없는 상태) 로 하고 다시 ginpst 를 초기화 해준다
			flag = 0;
		}
		ginpet2 = clock() - ginpst2; // 위와 같은 방식을 p2 에게 적용
		if ((int)ginpet2 >= 15000) {
			flag2 = 0;
		}

		playerInput = getch(); // 입력받은것을 playerInput에다가 저장

		if (flag == 0) { // flag = 0 일때, 즉 총이 없는 상태일때
			if (playerInput == 'a')
				moveplayer(-1, 0);
			else if (playerInput == 'd')
				moveplayer(1, 0);
			else if (playerInput == 'w')
				moveplayer(0, -1);
			else if (playerInput == 's')
				moveplayer(0, 1);
		}
		else if (flag == 1) { // flag = 1 일때, 즉 총이 있는 상태일때
			if (playerInput == 'a')
				 moveplayer(-1, 0);
			else if (playerInput == 'd')
				 moveplayer(1, 0);
			else if (playerInput == 'w')
				 moveplayer(0, -1);
			else if (playerInput == 's')
				 moveplayer(0, 1);
			// else if (playerInput == 'g')
		         // shoot1(); 경현이가 제작한함수를 여기서 사용
			
		}
		if (flag2 == 0) { // 위와 같은 방법을 p2에 적용
			if (playerInput == 75)
				 moveplayer2(-1, 0);
			else if (playerInput == 77)
				 moveplayer2(1, 0);
			else if (playerInput == 72)
				 moveplayer2(0, -1);
			else if (playerInput == 80)
				 moveplayer2(0, 1);
		}
		else if (flag2 == 1) {
			if (playerInput == 75)
				 moveplayer2(-1, 0);
			else if (playerInput == 77)
				 moveplayer2(1, 0);
			else if (playerInput == 72)
				 moveplayer2(0, -1);
			else if (playerInput == 80)
				 moveplayer2(0, 1);
			// else if (playerInput == '32')
			     // shoot1(); 경현이가 제작한함수를 여기서 사용
			
		}
	}
	return 0;
}

void moveplayer(int dx, int dy) {

	if (map[playerY + dy][playerX + dx] == SPACE) { // 다음 위치가 빈 공간일때

		if (map[playerY][playerX] == PLAYER || map[playerY][playerX] == GINP) { // 내가 PLAYER 거나 GINP인 상태일때 (풀숲이 아닐때)
			space_print(); // 빈공간 출력
			playerX += dx; playerY += dy;
			p1_print(); // 그다음 p1을 출력시킨다
			if (flag == 0)
				map[playerY][playerX] = PLAYER;
			else if (flag == 1)
				map[playerY][playerX] = GINP;
		}

		else { // 내가 BINP 상태일 (풀숲일때)
			bush_print(); // 풀숲을 출력한다
			playerX += dx; playerY += dy;
			p1_print(); // 그다음 p1을 출력시킨다
			if (flag == 0)
				map[playerY][playerX] = PLAYER;
			else if (flag == 1)
				map[playerY][playerX] = GINP;
		}
	}

	else if (map[playerY + dy][playerX + dx] == BUSH) { // 다음 위치가 풀숲일때

		if (map[playerY][playerX] == PLAYER || map[playerY][playerX] == GINP) { // 내가 PAYER 거나 GINP 인 상태일때 (풀숲이 아닐때)
			space_print(); // 빈 공간을 출력한다
			playerX += dx; playerY += dy;
			binp_print(); // 초록색 공을 출력한다
		}

		else { // 내가 BINP인 상태일때 (풀숲일때)
			
			bush_print(); // 풀숲을 출력한다
			playerX += dx; playerY += dy;
			binp_print(); // 초록색 공을 출력한다
		}
	}
	else if (map[playerY + dy][playerX + dx] == GUN) { // 다음 위치가 총일때
		if (map[playerY][playerX] == PLAYER || map[playerY][playerX] == GINP) { // 내가 PAYER 거나 GINP 인 상태일때 (풀숲이 아닐때)
			space_print(); // 빈공간을 출력한다
		}
		else { // (풀숲일때)
			bush_print(); // 풀숲을 출력한다
		}
		playerX += dx; playerY += dy;
		gotoxy(playerX, playerY);
		SetConsoleTextAttribute(COL, 4);
		printf("●");
		SetConsoleTextAttribute(COL, 15);
		map[playerY][playerX] = GINP;

		flag = 1; // flag 를 1로 변경
		ginpst = clock(); // 총먹었을때 카운터 시작
	}
	else if (map[playerY + dy][playerX + dx] == POTION) { // 다음 위치가 포션일때
		if (map[playerY][playerX] == PLAYER || map[playerY][playerX] == GINP) { // 내가 PAYER 거나 GINP 인 상태일때 (풀숲이 아닐때)
			space_print(); // 빈공간을 출력한다
		}
		else { // (풀숲일때)
			bush_print(); // 풀숲을 출력한다 
		}
		playerX += dx; playerY += dy;
		p1_print(); // p1을 출력한다
		if (flag == 0)
			map[playerY][playerX] = PLAYER;
		else if (flag == 1)
			map[playerY][playerX] = GINP;

		p1++; // 포션을 먹으면 p1 증가
	}
}

void moveplayer2(int dx, int dy) {

	if (map[playerY2 + dy][playerX2 + dx] == SPACE) { // 다음 위치가 빈 공간일때

		if (map[playerY2][playerX2] == PLAYER2 || map[playerY2][playerX2] == GINP2) { // 내가 PLAYER 거나 GINP인 상태일때 (풀숲이 아닐때)
			space2_print();
			playerX2 += dx; playerY2 += dy;
			p2_print();
			if (flag2 == 0)
				map[playerY2][playerX2] = PLAYER2;
			else if (flag2 == 1)
				map[playerY2][playerX2] = GINP2;
		}

		else { // 내가 BINP 상태일 (풀숲일때)
			bush2_print(); // 풀숲을 출력한다
			playerX2 += dx; playerY2 += dy;
			p2_print(); // 그다음 p2을 출력시킨다
			if (flag2 == 0)
				map[playerY2][playerX2] = PLAYER2;
			else if (flag2 == 1)
				map[playerY2][playerX2] = GINP2;
		}
	}

	else if (map[playerY2 + dy][playerX2 + dx] == BUSH) { // 다음 위치가 풀숲일때

		if (map[playerY2][playerX2] == PLAYER2 || map[playerY2][playerX2] == GINP2) { // 내가 PAYER 거나 GINP 인 상태일때 (풀숲이 아닐때)
			space2_print(); // 빈 공간을 출력한다
			playerX2 += dx; playerY2 += dy;
			binp2_print(); // 초록색 별을 출력한다
		}

		else { // 내가 BINP인 상태일때 (풀숲일때)

			bush2_print(); // 풀숲을 출력한다
			playerX2 += dx; playerY2 += dy;
			binp2_print(); // 초록색 별을 출력한다
		}
	}
	else if (map[playerY2 + dy][playerX2 + dx] == GUN) { // 다음 위치가 총일때
		if (map[playerY2][playerX2] == PLAYER2 || map[playerY2][playerX2] == GINP2) { // 내가 PAYER 거나 GINP 인 상태일때 (풀숲이 아닐때)
			space2_print(); // 빈공간을 출력한다
		}
		else { // (풀숲일때)
			bush2_print(); // 풀숲을 출력한다
		}
		playerX2 += dx; playerY2 += dy;
		gotoxy(playerX2, playerY2);
		SetConsoleTextAttribute(COL, 4);
		printf("★");
		SetConsoleTextAttribute(COL, 15);
		map[playerY2][playerX2] = GINP2;

		flag2 = 1; // flag2 를 1로 변경
		ginpst2 = clock(); // 총먹었을때 카운터 시작
	}
	else if (map[playerY2 + dy][playerX2 + dx] == POTION) { // 다음 위치가 포션일때
		if (map[playerY2][playerX2] == PLAYER2 || map[playerY2][playerX2] == GINP2) { // 내가 PAYER 거나 GINP 인 상태일때 (풀숲이 아닐때)
			space2_print(); // 빈공간을 출력한다
		}
		else { // (풀숲일때)
			bush2_print(); // 풀숲을 출력한다 
		}
		playerX2 += dx; playerY2 += dy;
		p1_print(); // p2을 출력한다
		if (flag2 == 0)
			map[playerY2][playerX2] = PLAYER2;
		else if (flag2 == 1)
			map[playerY2][playerX2] = GINP2;

		p2++; // 포션을 먹으면 p2 증가
	}
}


void gotoxy(int x, int y) // 커서 이동 함수
{
	COORD Pos;
	Pos.X = x * 2;
	Pos.Y = y;
	SetConsoleCursorPosition(COL, Pos);
}

void printmap() { // 맵을 출력하는 함수

	int i, j;

	for (i = 0; i < MAPSIZE; i++) {
		for (j = 0; j < MAPSIZE; j++) { // 맵 전체를 다 돈다
			switch (map[i][j]) { // 각 숫자에 따라서 다르게 값이 출력이 되도록 한다

			case WALL: printf("■"); break; 
			case SPACE: printf("  "); break;
			case BUSH: SetConsoleTextAttribute(COL, 2); printf("■"); SetConsoleTextAttribute(COL, 15); break;
			case GUN: SetConsoleTextAttribute(COL, 4); printf("☞"); SetConsoleTextAttribute(COL, 15); break;
			case PLAYER: SetConsoleTextAttribute(COL, 6); printf("●"); SetConsoleTextAttribute(COL, 15); break;
			case PLAYER2: SetConsoleTextAttribute(COL, 6); printf("★"); SetConsoleTextAttribute(COL, 15); break;
			}
		}
		printf("\n");
	}
}


void bush() { // 풀숲을 랜덤값으로 주는 함수

	int i, j, k;
	srand(time(NULL)); // 랜덤값

	for (i = 0; i < 15; i++) { // 풀숲 총 15개를 생성

		int random_x = (rand() % 33) + 1; // 범위가 맵전체를 넘어가지 않게 설정
		int random_y = (rand() % 33) + 1; // 범위가 맵전체를 넘어가지 않게 설정
		int dir = rand() % 2; // 세로 할것인지 가로 할것인지 결정
		if (dir == 0) { // 0일때
			for (j = 0; j < 6; j++) {
				for (k = 0; k < 3; k++) {
					map[random_x + j][random_y + k] = 2; // 가로 3 * 세로 6칸의 풀숲을 출력
				}
			}
		}
		else if (dir == 1) { // 1일때
			for (j = 0; j < 3; j++) {
				for (k = 0; k < 6; k++) {
					map[random_x + j][random_y + k] = 2; // 가로 6칸 * 세로 3칸의 풀숲을 출력
				}
			}
		}

	}
}

void wall() { // 벽을 랜덤값으로 주는 함수

	int i, j, k, l = 0, ll = 0;
	srand(time(NULL)); // 랜덤값

	for (i = 0; i < 12; i++) {

		int random_x = (rand() % 31) + 1; // 맵 밖에 생성되지 않도록 해둔것
		int random_y = (rand() % 31) + 1;// 맵 밖에 생성되지 않도록 해둔것
		int dir = rand() % 4; // 4가지 경우로 나눔
		if (dir == 0) {
			for (j = 0; j < 8; j++) {
				map[random_x + j][random_y] = 1; // 세로로 8칸 벽생성
			}
		}
		else if (dir == 1) {
			for (j = 0; j < 8; j++) {
				map[random_x][random_y + j] = 1; // 가로로 8칸 벽생성
			}
		}
		else if (dir == 2) {
			l = k = 0;
			for (j = 0; j < 4; j++) {
				for (k = 0; k < 2; k++) {
					map[random_x + l][random_y + ll] = 1; // 지그재그 왼->오 방향
					l++;
				}
				ll++;
				l--;
			}
		}
		else if (dir == 3) {
			l = k = 0;
			for (j = 0; j < 4; j++) {
				for (k = 0; k < 2; k++) {
					map[random_x + l][random_y + ll] = 1; // 지그재그 오->왼 방향
					l++;
				}
				ll--;
				l--;
			}
		}
	}
}

void gun() { // 총을 출력하는 함수

	int i;
	srand(time(NULL)); // 랜덤값

	while (1) {
		gun_x = (rand() % 38) + 1; // 맵 밖에 생성되지 않도록 해둔것
		gun_y = (rand() % 38) + 1; // 맵 밖에 생성되지 않도록 해둔것
		if (map[gun_y][gun_x] == SPACE) { // 공간이 빈공간일때만 저장이 되도록함
			map[gun_y][gun_x] = 3;
			gotoxy(gun_x, gun_y);
			SetConsoleTextAttribute(COL, 4); printf("☞"); SetConsoleTextAttribute(COL, 15);
			break;
		}
		else
			continue;
	}
}

void potion() { // 포션을 출력하는 함수

	int i;
	srand(time(NULL)); // 랜덤값

	while (1) {
		potion_x = (rand() % 38) + 1; // 맵 밖에 생성되지 않도록 해둔것
		potion_y = (rand() % 38) + 1; // 맵 밖에 생성되지 않도록 해둔것
		if (map[potion_y][potion_x] == SPACE) { // 공간이 빈공간일때만 저장이 되도록함
			map[potion_y][potion_x] = 5;
			gotoxy(potion_x, potion_y);
			SetConsoleTextAttribute(COL, 3); printf("♠"); SetConsoleTextAttribute(COL, 15);
			break;
		}
		else
			continue;
	}
}

void player() { // p1 랜덤값으로 주는 함수

	int i;
	srand(time(NULL));
	while (1) {
		int random_x = (rand() % 38) + 1;
		int random_y = (rand() % 38) + 1;
		if (map[random_y][random_x] == SPACE) { // 빈공간일 때만
			map[random_y][random_x] = PLAYER;
			break;
		}
		else
			continue;
	}

}

void player2() { // p2 랜덤값으로 주는 함수

	int i;
	srand(time(NULL));
	while (1) {
		int random_x = (rand() % 38) + 1;
		int random_y = (rand() % 38) + 1;
		if (map[random_y][random_x] == SPACE) { // 빈공간일 때만
			map[random_y][random_x] = PLAYER2;
			break;
		}
		else
			continue;
	}

}

void p1_print() { // p1을 출력해주는 함수
	gotoxy(playerX, playerY);
	if (flag == 0) {
		SetConsoleTextAttribute(COL, 6);
		printf("●"); // 총을 안먹은 상태일때는 노란색
		SetConsoleTextAttribute(COL, 15);
	}
	else if (flag == 1) {
		SetConsoleTextAttribute(COL, 4);
		printf("●"); // 총을 먹은 상태일때는 빨간색
		SetConsoleTextAttribute(COL, 15);
	}
}

void bush_print() {
	SetConsoleTextAttribute(COL, 2);
	gotoxy(playerX, playerY);
	printf("■"); // 풀을 출력을 해준다
	SetConsoleTextAttribute(COL, 15);
	map[playerY][playerX] = BUSH;
}

void space_print() {
	gotoxy(playerX, playerY);
	printf("  "); // 빈공간을 출력을 해준다
	map[playerY][playerX] = SPACE;
}

void binp_print() {
	gotoxy(playerX, playerY);
	SetConsoleTextAttribute(COL, 2);
	printf("●"); // 초록색 공을 출력
	SetConsoleTextAttribute(COL, 15);
	map[playerY][playerX] = BINP;
}

void p2_print() {
	gotoxy(playerX2, playerY2);
	if (flag2 == 0) { // p2을 출력해주는 함수
		SetConsoleTextAttribute(COL, 6);
		printf("★"); // 총을 안먹은 상태일때는 노란색
		SetConsoleTextAttribute(COL, 15);
	}
	else if (flag2 == 1) {
		SetConsoleTextAttribute(COL, 4);
		printf("★"); // 총을 먹은 상태일때는 빨간색
		SetConsoleTextAttribute(COL, 15);
	}
}

void bush2_print() {
	SetConsoleTextAttribute(COL, 2);
	gotoxy(playerX2, playerY2);
	printf("■"); // 풀을 출력을 해준다
	SetConsoleTextAttribute(COL, 15);
	map[playerY2][playerX2] = BUSH;
}

void space2_print() {
	gotoxy(playerX2, playerY2);
	printf("  "); // 빈공간을 출력을 해준다
	map[playerY2][playerX2] = SPACE;
}

void binp2_print() {
	gotoxy(playerX2, playerY2);
	SetConsoleTextAttribute(COL, 2);
	printf("★"); // 초록색 별을 출력
	SetConsoleTextAttribute(COL, 15);
	map[playerY2][playerX2] = BINP2;
}

void print_infor(){
	int i;
	gotoxy(43, 6);
	printf("┏━━ ┃ 플레이어 정보 ┃ ━━┓"); // UI 구현
	for (i = 7; i <= 32; i++) {
		gotoxy(43, i);
		printf("┃                       ┃");
	}
	gotoxy(43, 33);
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━┛");
	gotoxy(46, 15);
	printf("P1 목숨 : %d", p1); // p1 목숨 출력
	gotoxy(46, 20);
	printf("P2 목숨 : %d", p2); // p2 목숨 출력
}

void win_lose() {
	int i;
	if (p1 == 0) { // p1의 목숨이 0이면
		gotoxy(43, 6);
		printf("┏━━ ┃ 플레이어 정보 ┃ ━━┓"); // UI 구현
		for (i = 7; i <= 32; i++) {
			gotoxy(43, i);
			printf("┃                       ┃");
		}
		gotoxy(43, 33);
		printf("┗━━━━━━━━━━━━━━━━━━━━━━━┛");
		gotoxy(47, 19);
		printf("P2 Winner!!        "); // p2 승리 출력
		exit(0);
	}
	else if (p2 == 0) {
		gotoxy(43, 6);
		printf("┏━━ ┃ 플레이어 정보 ┃ ━━┓"); // UI 구현
		for (i = 7; i <= 32; i++) {
			gotoxy(43, i);
			printf("┃                       ┃");
		}
		gotoxy(43, 33);
		printf("┗━━━━━━━━━━━━━━━━━━━━━━━┛");
		gotoxy(47, 19);
		printf("P1 Winner!!        "); // p1 승리 출력
		exit(0);
	}
}
