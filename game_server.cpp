#pragma comment(lib, "ws2_32.lib") //라이브러리 자동으로 못 찾아서 찾아줌
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<string.h>
#include <winsock2.h> // 소켓 통신
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
int p1 = 3, p2 = 3; // p1, p2 목숨
float ginpst, ginpst2;

int map[MAPSIZE][MAPSIZE] = { // 맵 생성

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
void bush(); // 부쉬 랜덤
void wall(); // 벽 랜던생성 함수
void gun(); // 총 랜덤생성 함수
void potion(); // 포션 랜덤생성 함수

int main(int argc, char *argv[]) {
	srand(time(NULL)); // 랜덤생성
	int i, j;
	char player1Input[10], player2Input[10];
	bush();
	wall();
	player();
	player2();
	float gunst = clock(), stpt = clock(), gunet, ginpet, ginpet2, etpt; // clock 함수 쓰기위한 변수들
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
	SOCKET sock, clientsock1, clientsock2; // 소켓 구조체 선언
	WSADATA wsa;
	struct sockaddr_in sockinfo, client1info, client2info; //클라 1, 2 구조체 선언

	int client1size, client2size;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		printf("초기화 실패\n");
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //소켓(서버) 생성자

	if (sock == INVALID_SOCKET) // 생성 실패
		printf("소켓 생성 실패\n");

	memset(&sockinfo, 0, sizeof(sockinfo));
	sockinfo.sin_family = AF_INET;
	sockinfo.sin_port = htons(3000); // 서버 포트
	sockinfo.sin_addr.s_addr = htonl(INADDR_ANY); // 서버 주소

	if (bind(sock, (SOCKADDR*)&sockinfo, sizeof(sockinfo)) == SOCKET_ERROR) // 소켓 바인딩
		printf(" bind 실패 ");

	if (listen(sock, 5) == SOCKET_ERROR)
		printf(" 대기열 실패 ");

	client1size = sizeof(client1info);
	client2size = sizeof(client2info);

	clientsock1 = accept(sock, (SOCKADDR*)&client1info, &client1size);
	if (clientsock1 == INVALID_SOCKET)
		printf("1P 클라이언트 소켓 연결 실패\n");
	else
		printf("1P 클라이언트 소켓 연결 성공\n");

	clientsock2 = accept(sock, (SOCKADDR*)&client2info, &client2size);
	if (clientsock2 == INVALID_SOCKET)
		printf("2P 클라이언트 소켓 연결 실패\n");
	else
		printf("2P 클라이언트 소켓 연결 성공\n");

	while (1) {
		int st1, st2;
		st1 = recv(clientsock1, player1Input, sizeof(player1Input), 0);
		if (st1 == -1) {
			printf("1P 클라이언트 메세지 수신 실패\n");
			break;
		}
		else {
			printf("1P 입력 : %c\n", player1Input[0]);
		}
		st2 = recv(clientsock2, player2Input, sizeof(player2Input), 0);
		if (st2 == -1) {
			printf("2P 클라이언트 메세지 수신 실패\n");
			printf("2P 입력 : %s\n", player2Input);
			break;
		}
		else {
			printf("2P 입력 : %c\n", player2Input[0]);
		}
		// 1P 이동 방향 W, D, S, A // 무조건 대문자로 들어옴
		// 2P 이동 방향 ↑, →, ↓, ←

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

		if (flag == 1 && (!strcmp(player1Input, "g"))) {
			// shoot1(); 경현이가 제작한함수를 여기서 사용
		}
		else {
			if (player1Input[0] == 'a')
				moveplayer(-1, 0);
			else if (player1Input[0] == 'd')
				moveplayer(1, 0);
			else if (player1Input[0] == 'w')
				moveplayer(0, -1);
			else if (player1Input[0] == 's')
				moveplayer(0, 1);

		}
		if (flag2 == 1 && player2Input[0] == 'g') { // 위와 같은 방법을 p2에 적용
			// shoot2(); 경현이가 제작한 함수를 여기서 사용 
		}
		else {
			if (player2Input[0] == 'a')
				moveplayer2(-1, 0);
			else if (player2Input[0] == 'd')
				moveplayer2(1, 0);
			else if (player2Input[0] == 'w')
				moveplayer2(0, -1);
			else if (player2Input[0] == 's')
				moveplayer2(0, 1);

		}
		for (int i = 0; i < MAPSIZE; i++) {
			char buf[1000] = { 0, };
			int cnt = 0;
			for (int j = 0; j < MAPSIZE; j++) {
				if (map[i][j] >= 0 && map[i][j] <= 9) {
					buf[cnt++] = map[i][j] + 48;
					buf[cnt++] = 4 + 48;
				}
				else {
					buf[cnt++] = map[i][j] / 10 + 48;
					buf[cnt++] = map[i][j] % 10 + 48;
					buf[cnt++] = 4 + 48;
				}
			}
			printf("i : %s\n", buf);
			send(clientsock1, buf, sizeof(buf), 0);
			send(clientsock2, buf, sizeof(buf), 0);
		}
		char buf1[20] = { 0, }, buf2[20] = { 0, };
		itoa(p1, buf1, 10);
		itoa(p2, buf2, 10);
		printf("p1 : %s, p2 : %s", buf1, buf2);
		send(clientsock1, buf1, sizeof(buf1), 0);
		send(clientsock1, buf2, sizeof(buf2), 0);
		send(clientsock2, buf1, sizeof(buf1), 0);
		send(clientsock2, buf2, sizeof(buf2), 0);
	}
	closesocket(clientsock1);
	closesocket(clientsock2);
	closesocket(sock);
	WSACleanup();
}
void moveplayer(int dx, int dy) {

	if (map[playerY + dy][playerX + dx] == SPACE) { // 다음 위치가 빈 공간일때

		if (map[playerY][playerX] == PLAYER || map[playerY][playerX] == GINP) { // 내가 PLAYER 거나 GINP인 상태일때 (풀숲이 아닐때)
			map[playerY][playerX] = SPACE;
			playerX += dx; playerY += dy;
			if (flag == 0)
				map[playerY][playerX] = PLAYER;
			else if (flag == 1)
				map[playerY][playerX] = GINP;
		}

		else { // 내가 BINP 상태일떄 (풀숲일때)
			map[playerY][playerX] = BINP;
			playerX += dx; playerY += dy;
			if (flag == 0)
				map[playerY][playerX] = PLAYER;
			else if (flag == 1)
				map[playerY][playerX] = GINP;
		}
	}

	else if (map[playerY + dy][playerX + dx] == BUSH) { // 다음 위치가 풀숲일때
		if (map[playerY][playerX] == PLAYER || map[playerY][playerX] == GINP) { // 내가 PAYER 거나 GINP 인 상태일때 (풀숲이 아닐때)
			map[playerY][playerX] = SPACE;
			playerX += dx; playerY += dy;
			map[playerY][playerX] = BINP;
		}

		else { // 내가 BINP인 상태일때 (풀숲일때)
			map[playerY][playerX] = BUSH;
			playerX += dx; playerY += dy;
		}
	}
	else if (map[playerY + dy][playerX + dx] == GUN) { // 다음 위치가 총일때
		if (map[playerY][playerX] == PLAYER || map[playerY][playerX] == GINP) { // 내가 PAYER 거나 GINP 인 상태일때 (풀숲이 아닐때)
			map[playerY][playerX] = SPACE;
		}
		else { // (풀숲일때)
			map[playerY][playerX] = BUSH;
		}
		playerX += dx; playerY += dy;
		map[playerY][playerX] = GINP;

		flag = 1; // flag 를 1로 변경
		ginpst = clock(); // 총먹었을때 카운터 시작
	}
	else if (map[playerY + dy][playerX + dx] == POTION) { // 다음 위치가 포션일때
		if (map[playerY][playerX] == PLAYER || map[playerY][playerX] == GINP) { // 내가 PAYER 거나 GINP 인 상태일때 (풀숲이 아닐때)
			map[playerY][playerX] = SPACE;
		}
		else { // (풀숲일때)
			map[playerY][playerX] = BUSH;
		}
		playerX += dx; playerY += dy;
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
			map[playerY2][playerX2] = SPACE;
			playerX2 += dx; playerY2 += dy;
			if (flag2 == 0)
				map[playerY2][playerX2] = PLAYER2;
			else if (flag2 == 1)
				map[playerY2][playerX2] = GINP2;
		}

		else { // 내가 BINP 상태일떄 (풀숲일때)
			map[playerY2][playerX2] = BUSH;
			playerX2 += dx; playerY2 += dy;
			if (flag2 == 0)
				map[playerY2][playerX2] = PLAYER2;
			else if (flag2 == 1)
				map[playerY2][playerX2] = GINP2;
		}
	}

	else if (map[playerY2 + dy][playerX2 + dx] == BUSH) { // 다음 위치가 풀숲일때

		if (map[playerY2][playerX2] == PLAYER2 || map[playerY2][playerX2] == GINP2) { // 내가 PAYER 거나 GINP 인 상태일때 (풀숲이 아닐때)
			map[playerY2][playerX2] = SPACE;
			playerX2 += dx; playerY2 += dy;
			map[playerY2][playerX2] = BINP2;
		}

		else { // 내가 BINP인 상태일때 (풀숲일때)

			map[playerY2][playerX2] = BUSH;
			playerX2 += dx; playerY2 += dy;
			map[playerY2][playerX2] = BINP2;
		}
	}
	else if (map[playerY2 + dy][playerX2 + dx] == GUN) { // 다음 위치가 총일때
		if (map[playerY2][playerX2] == PLAYER2 || map[playerY2][playerX2] == GINP2) { // 내가 PAYER 거나 GINP 인 상태일때 (풀숲이 아닐때)
			map[playerY2][playerX2] = SPACE;
		}
		else { // (풀숲일때)
			map[playerY2][playerX2] = BUSH;
		}
		map[playerY2][playerX2] = GINP2;

		flag2 = 1; // flag2 를 1로 변경
		ginpst2 = clock(); // 총먹었을때 카운터 시작
	}
	else if (map[playerY2 + dy][playerX2 + dx] == POTION) { // 다음 위치가 포션일때
		if (map[playerY2][playerX2] == PLAYER2 || map[playerY2][playerX2] == GINP2) { // 내가 PAYER 거나 GINP 인 상태일때 (풀숲이 아닐때)
			map[playerY2][playerX2] = SPACE;
		}
		else { // (풀숲일때)
			map[playerY2][playerX2] = BUSH;
		}
		playerX2 += dx; playerY2 += dy;
		if (flag2 == 0)
			map[playerY2][playerX2] = PLAYER2;
		else if (flag2 == 1)
			map[playerY2][playerX2] = GINP2;

		p2++; // 포션을 먹으면 p2 증가
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
			map[gun_y][gun_x] = GUN;
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
			map[potion_y][potion_x] = POTION;
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