#pragma comment(lib, "ws2_32.lib")
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<winsock2.h>
#include<Windows.h>
#include<conio.h>

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
#define STRNULL 4 //문자열용 공백

char getKey();
char map[MAPSIZE][1000];
void win_lose(int);
void gotoxy(int, int);
void win_lose(); // 플레이어가 이겼을때 호출되는 함수
void print_infor(); // 플레이어의 목숨 정보를 출력하는 함수
void p1_print(); // p1을 출력 해주는 함수
void bush_print(); // p1의 bush를 출력 해주는 함수
void space_print(); // p1의 space를 출력 해주는 함수
void binp_print(); // p1의 binp를 출력 해주는 함수
void p2_print(); // p2을 출력 해주는 함수
void bush2_print(); // p2의 bush를 출력 해주는 함수
void space2_print(); // p2의 space를 출력 해주는 함수
void binp2_print(); // p2의 binp를 출력 해주는 함수

int p1 = 1, p2 = 1, status;
int main(int argc, char *argv[]) {
	SOCKET clientsock;
	WSADATA wsa;
	struct sockaddr_in sockinfo;

	if (argc != 3) {
		printf("Usage : %s <IP> <PORT> \n", argv[0]);
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)

		printf("초기화 실패\n");

	clientsock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (clientsock == INVALID_SOCKET)
		printf("소켓 생성 실패\n");

	memset(&sockinfo, 0, sizeof(sockinfo));

	sockinfo.sin_family = AF_INET;
	sockinfo.sin_port = htons(atoi(argv[2]));
	sockinfo.sin_addr.s_addr = inet_addr(argv[1]);

	if (connect(clientsock, (SOCKADDR*)&sockinfo, sizeof(sockinfo)) == SOCKET_ERROR)
		printf(" 서버 접속 실패\n");
	else
		printf("서버 접속 성공\n");
	Sleep(2000);
	system("cls");
	while (1) {
		char playerInput = getKey();

		if (playerInput >= 65 && playerInput <= 90)
			playerInput += 32;
		char buf[100] = "";
		buf[0] = playerInput;
		send(clientsock, buf, sizeof(buf), 0);
		for (int i = 0; i < MAPSIZE; i++) {
			recv(clientsock, map[i], sizeof(map[i]), 0);
		}
		recv(clientsock, buf, sizeof(buf), 0);
		p1 = atoi(buf);
		recv(clientsock, buf, sizeof(buf), 0);
		p2 = atoi(buf);
		for (int i = 0; i < MAPSIZE; i++) {
			int t = 0,cnt = 0;
			for (int j = 0; j < strlen(map[i]); j++) { // 맵 전체를 다 돈다
				if (map[i][j] == STRNULL) { //만약 분할되는 지점이라면,
					switch (t) { // 각 숫자에 따라서 다르게 값이 출력이 되도록 한다
						case WALL: printf("■"); break;
						case SPACE: printf("  "); break;
						case BUSH: SetConsoleTextAttribute(COL, 2); gotoxy(cnt++, i); printf("■"); SetConsoleTextAttribute(COL, 15); break;
						case GUN: SetConsoleTextAttribute(COL, 4); gotoxy(cnt++, i); printf("☞"); SetConsoleTextAttribute(COL, 15); break;
						case POTION: SetConsoleTextAttribute(COL, 3); gotoxy(cnt++, i); printf("♠"); SetConsoleTextAttribute(COL, 15); break;
						case GINP: SetConsoleTextAttribute(COL, 4); gotoxy(cnt++, i); printf("●"); SetConsoleTextAttribute(COL, 15); break;
						case BINP: SetConsoleTextAttribute(COL, 2); gotoxy(cnt++, i); printf("●"); SetConsoleTextAttribute(COL, 15); break;
						case PLAYER: SetConsoleTextAttribute(COL, 6); gotoxy(cnt++, i); printf("●"); SetConsoleTextAttribute(COL, 15); break;
						case GINP2 : SetConsoleTextAttribute(COL, 4); gotoxy(cnt++, i); printf("★"); SetConsoleTextAttribute(COL, 15); break;
						case BINP2 : SetConsoleTextAttribute(COL, 2); gotoxy(cnt++, i); printf("★"); SetConsoleTextAttribute(COL, 15); break;
						case PLAYER2: SetConsoleTextAttribute(COL, 6); gotoxy(cnt++, i); printf("★"); SetConsoleTextAttribute(COL, 15); break;
					}
					printf("%d ", t);
					t = 0;
				}
				else {
					t *= 10;
					t += map[i][j] - 48;
				}
			}
			system("pause");
		}
		print_infor(); // 플레이어 정보를 출력
		win_lose(); // 어떤 플레이어가 이겼는지 출력 안이겼으면 아무것도 출력 안함
	}
	closesocket(clientsock);
	WSACleanup();
}

char getKey()
{
	Sleep(10);
	if (kbhit()) // kbhit()이용해 입력값이 있는지 확인 
	{
		return getch();     // 입력값이 getch()로 char를 리턴해줌
	}
	return '\0'; // 입력값이 없으면 널 문자 리턴
}

void gotoxy(int x, int y) // 커서 이동 함수
{
	COORD Pos;
	Pos.X = x * 2;
	Pos.Y = y;
	SetConsoleCursorPosition(COL, Pos);
}
void print_infor() {
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
	}
}