#pragma comment(lib, "ws2_32.lib") //���̺귯�� �ڵ����� �� ã�Ƽ� ã����
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<string.h>
#include <winsock2.h> // ���� ���
#include<windows.h>

#define MAPSIZE 40
#define SPACE 0 // �����
#define WALL 1 // ��
#define BUSH 2 // Ǯ��
#define GUN 3 // ��
#define POTION 5 //  ����
#define GINP 7 // ���� ���� ������ �÷��̾� 1
#define BINP 8 // �ν��� �ִ� ������ �÷��̾� 1
#define PLAYER 9 // ���� �÷��̾� 1
#define GINP2 70 // ���� ���� ������ �÷��̾�2
#define BINP2 80 // �ν��� �ִ� ������ �÷��̾� 2
#define PLAYER2 90 // ���� �÷��̾� 2
#define COL GetStdHandle(STD_OUTPUT_HANDLE) // ���� �� ����

int playerX, playerY, playerX2, playerY2, flag = 0, flag2 = 0, gun_x, gun_y, potion_x, potion_y;
int p1 = 3, p2 = 3; // p1, p2 ���
float ginpst, ginpst2;

int map[MAPSIZE][MAPSIZE] = { // �� ����

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


void win_lose(); // �÷��̾ �̰����� ȣ��Ǵ� �Լ�
void print_infor(); // �÷��̾��� ��� ������ ����ϴ� �Լ�
void moveplayer(int dx, int dy); // p1�� �̵��Լ�
void moveplayer2(int dx, int dy); // p2�� �̵��Լ�
void player(); // p1 �������� �Լ�
void player2(); // p2 �������� �Լ�
void bush(); // �ν� ����
void wall(); // �� �������� �Լ�
void gun(); // �� �������� �Լ�
void potion(); // ���� �������� �Լ�

int main(int argc, char *argv[]) {
	srand(time(NULL)); // ��������
	int i, j;
	char player1Input[10], player2Input[10];
	bush();
	wall();
	player();
	player2();
	float gunst = clock(), stpt = clock(), gunet, ginpet, ginpet2, etpt; // clock �Լ� �������� ������
	for (i = 0; i < MAPSIZE; i++)
	{
		for (j = 0; j < MAPSIZE; j++)
		{
			if (map[i][j] == 9) // �� ��ü�� ���ٰ� p1(9)�� ������ �׶��� i,j ��ǥ�� ���� y,x �������ٰ� ����
			{
				playerX = j;
				playerY = i;
			}
			if (map[i][j] == 90) { // ���� ���� ����� p2�� ����
				playerX2 = j;
				playerY2 = i;
			}
		}
	}
	SOCKET sock, clientsock1, clientsock2; // ���� ����ü ����
	WSADATA wsa;
	struct sockaddr_in sockinfo, client1info, client2info; //Ŭ�� 1, 2 ����ü ����

	int client1size, client2size;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		printf("�ʱ�ȭ ����\n");
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //����(����) ������

	if (sock == INVALID_SOCKET) // ���� ����
		printf("���� ���� ����\n");

	memset(&sockinfo, 0, sizeof(sockinfo));
	sockinfo.sin_family = AF_INET;
	sockinfo.sin_port = htons(3000); // ���� ��Ʈ
	sockinfo.sin_addr.s_addr = htonl(INADDR_ANY); // ���� �ּ�

	if (bind(sock, (SOCKADDR*)&sockinfo, sizeof(sockinfo)) == SOCKET_ERROR) // ���� ���ε�
		printf(" bind ���� ");

	if (listen(sock, 5) == SOCKET_ERROR)
		printf(" ��⿭ ���� ");

	client1size = sizeof(client1info);
	client2size = sizeof(client2info);

	clientsock1 = accept(sock, (SOCKADDR*)&client1info, &client1size);
	if (clientsock1 == INVALID_SOCKET)
		printf("1P Ŭ���̾�Ʈ ���� ���� ����\n");
	else
		printf("1P Ŭ���̾�Ʈ ���� ���� ����\n");

	clientsock2 = accept(sock, (SOCKADDR*)&client2info, &client2size);
	if (clientsock2 == INVALID_SOCKET)
		printf("2P Ŭ���̾�Ʈ ���� ���� ����\n");
	else
		printf("2P Ŭ���̾�Ʈ ���� ���� ����\n");

	while (1) {
		int st1, st2;
		st1 = recv(clientsock1, player1Input, sizeof(player1Input), 0);
		if (st1 == -1) {
			printf("1P Ŭ���̾�Ʈ �޼��� ���� ����\n");
			break;
		}
		else {
			printf("1P �Է� : %c\n", player1Input[0]);
		}
		st2 = recv(clientsock2, player2Input, sizeof(player2Input), 0);
		if (st2 == -1) {
			printf("2P Ŭ���̾�Ʈ �޼��� ���� ����\n");
			printf("2P �Է� : %s\n", player2Input);
			break;
		}
		else {
			printf("2P �Է� : %c\n", player2Input[0]);
		}
		// 1P �̵� ���� W, D, S, A // ������ �빮�ڷ� ����
		// 2P �̵� ���� ��, ��, ��, ��

		gunet = clock() - gunst; // ���� �����ð����� �������� ���� �����Ҷ� clock ���־��� ���� clock �� ���� ó�� clock �� ���� ���ذ��� �����Ѵ�
		etpt = clock() - stpt; // ���� �����ð����� �������� ���� �����Ҷ� clock ���־��� ���� clock �� ���� ó�� clock �� ���� ���ذ��� �����Ѵ�

		if ((int)gunet >= 300) { // ���� ó���ð�~�������ð��� 15�� �̻��̸� �׶� gun�Լ��� �����ϰ� �ٽý���ǰԲ� gunst�� �ʱ�ȭ ���ش�
			for (int i = 0; i < 2; i++) {
				gun();
				gunst = clock();
			}
		}
		if ((int)etpt >= 300) { // ���� ó���ð�~�������ð��� 10�� �̻��̸� �׶� potion�Լ��� �����ϰ� �ٽý���ǰԲ� stpt�� �ʱ�ȭ ���ش�
			potion();
			stpt = clock();
		}

		ginpet = clock() - ginpst; // 15�ʰ� �Ǹ� ��ȿ���� ������Բ� �Ѱ� pinpst�� ���� �Ծ����� �Ʒ��ڵ忡�� clock�� ���־���
		if ((int)ginpet >= 15000) { // ó��~������ ������ 15���̻��̸� flag = 0 (���� ���� ����) �� �ϰ� �ٽ� ginpst �� �ʱ�ȭ ���ش�
			flag = 0;
		}
		ginpet2 = clock() - ginpst2; // ���� ���� ����� p2 ���� ����
		if ((int)ginpet2 >= 15000) {
			flag2 = 0;
		}

		if (flag == 1 && (!strcmp(player1Input, "g"))) {
			// shoot1(); �����̰� �������Լ��� ���⼭ ���
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
		if (flag2 == 1 && player2Input[0] == 'g') { // ���� ���� ����� p2�� ����
			// shoot2(); �����̰� ������ �Լ��� ���⼭ ��� 
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

	if (map[playerY + dy][playerX + dx] == SPACE) { // ���� ��ġ�� �� �����϶�

		if (map[playerY][playerX] == PLAYER || map[playerY][playerX] == GINP) { // ���� PLAYER �ų� GINP�� �����϶� (Ǯ���� �ƴҶ�)
			map[playerY][playerX] = SPACE;
			playerX += dx; playerY += dy;
			if (flag == 0)
				map[playerY][playerX] = PLAYER;
			else if (flag == 1)
				map[playerY][playerX] = GINP;
		}

		else { // ���� BINP �����ϋ� (Ǯ���϶�)
			map[playerY][playerX] = BINP;
			playerX += dx; playerY += dy;
			if (flag == 0)
				map[playerY][playerX] = PLAYER;
			else if (flag == 1)
				map[playerY][playerX] = GINP;
		}
	}

	else if (map[playerY + dy][playerX + dx] == BUSH) { // ���� ��ġ�� Ǯ���϶�
		if (map[playerY][playerX] == PLAYER || map[playerY][playerX] == GINP) { // ���� PAYER �ų� GINP �� �����϶� (Ǯ���� �ƴҶ�)
			map[playerY][playerX] = SPACE;
			playerX += dx; playerY += dy;
			map[playerY][playerX] = BINP;
		}

		else { // ���� BINP�� �����϶� (Ǯ���϶�)
			map[playerY][playerX] = BUSH;
			playerX += dx; playerY += dy;
		}
	}
	else if (map[playerY + dy][playerX + dx] == GUN) { // ���� ��ġ�� ���϶�
		if (map[playerY][playerX] == PLAYER || map[playerY][playerX] == GINP) { // ���� PAYER �ų� GINP �� �����϶� (Ǯ���� �ƴҶ�)
			map[playerY][playerX] = SPACE;
		}
		else { // (Ǯ���϶�)
			map[playerY][playerX] = BUSH;
		}
		playerX += dx; playerY += dy;
		map[playerY][playerX] = GINP;

		flag = 1; // flag �� 1�� ����
		ginpst = clock(); // �ѸԾ����� ī���� ����
	}
	else if (map[playerY + dy][playerX + dx] == POTION) { // ���� ��ġ�� �����϶�
		if (map[playerY][playerX] == PLAYER || map[playerY][playerX] == GINP) { // ���� PAYER �ų� GINP �� �����϶� (Ǯ���� �ƴҶ�)
			map[playerY][playerX] = SPACE;
		}
		else { // (Ǯ���϶�)
			map[playerY][playerX] = BUSH;
		}
		playerX += dx; playerY += dy;
		if (flag == 0)
			map[playerY][playerX] = PLAYER;
		else if (flag == 1)
			map[playerY][playerX] = GINP;
		p1++; // ������ ������ p1 ����
	}
}

void moveplayer2(int dx, int dy) {

	if (map[playerY2 + dy][playerX2 + dx] == SPACE) { // ���� ��ġ�� �� �����϶�

		if (map[playerY2][playerX2] == PLAYER2 || map[playerY2][playerX2] == GINP2) { // ���� PLAYER �ų� GINP�� �����϶� (Ǯ���� �ƴҶ�)
			map[playerY2][playerX2] = SPACE;
			playerX2 += dx; playerY2 += dy;
			if (flag2 == 0)
				map[playerY2][playerX2] = PLAYER2;
			else if (flag2 == 1)
				map[playerY2][playerX2] = GINP2;
		}

		else { // ���� BINP �����ϋ� (Ǯ���϶�)
			map[playerY2][playerX2] = BUSH;
			playerX2 += dx; playerY2 += dy;
			if (flag2 == 0)
				map[playerY2][playerX2] = PLAYER2;
			else if (flag2 == 1)
				map[playerY2][playerX2] = GINP2;
		}
	}

	else if (map[playerY2 + dy][playerX2 + dx] == BUSH) { // ���� ��ġ�� Ǯ���϶�

		if (map[playerY2][playerX2] == PLAYER2 || map[playerY2][playerX2] == GINP2) { // ���� PAYER �ų� GINP �� �����϶� (Ǯ���� �ƴҶ�)
			map[playerY2][playerX2] = SPACE;
			playerX2 += dx; playerY2 += dy;
			map[playerY2][playerX2] = BINP2;
		}

		else { // ���� BINP�� �����϶� (Ǯ���϶�)

			map[playerY2][playerX2] = BUSH;
			playerX2 += dx; playerY2 += dy;
			map[playerY2][playerX2] = BINP2;
		}
	}
	else if (map[playerY2 + dy][playerX2 + dx] == GUN) { // ���� ��ġ�� ���϶�
		if (map[playerY2][playerX2] == PLAYER2 || map[playerY2][playerX2] == GINP2) { // ���� PAYER �ų� GINP �� �����϶� (Ǯ���� �ƴҶ�)
			map[playerY2][playerX2] = SPACE;
		}
		else { // (Ǯ���϶�)
			map[playerY2][playerX2] = BUSH;
		}
		map[playerY2][playerX2] = GINP2;

		flag2 = 1; // flag2 �� 1�� ����
		ginpst2 = clock(); // �ѸԾ����� ī���� ����
	}
	else if (map[playerY2 + dy][playerX2 + dx] == POTION) { // ���� ��ġ�� �����϶�
		if (map[playerY2][playerX2] == PLAYER2 || map[playerY2][playerX2] == GINP2) { // ���� PAYER �ų� GINP �� �����϶� (Ǯ���� �ƴҶ�)
			map[playerY2][playerX2] = SPACE;
		}
		else { // (Ǯ���϶�)
			map[playerY2][playerX2] = BUSH;
		}
		playerX2 += dx; playerY2 += dy;
		if (flag2 == 0)
			map[playerY2][playerX2] = PLAYER2;
		else if (flag2 == 1)
			map[playerY2][playerX2] = GINP2;

		p2++; // ������ ������ p2 ����
	}
}

void bush() { // Ǯ���� ���������� �ִ� �Լ�

	int i, j, k;
	srand(time(NULL)); // ������

	for (i = 0; i < 15; i++) { // Ǯ�� �� 15���� ����

		int random_x = (rand() % 33) + 1; // ������ ����ü�� �Ѿ�� �ʰ� ����
		int random_y = (rand() % 33) + 1; // ������ ����ü�� �Ѿ�� �ʰ� ����
		int dir = rand() % 2; // ���� �Ұ����� ���� �Ұ����� ����
		if (dir == 0) { // 0�϶�
			for (j = 0; j < 6; j++) {
				for (k = 0; k < 3; k++) {
					map[random_x + j][random_y + k] = 2; // ���� 3 * ���� 6ĭ�� Ǯ���� ���
				}
			}
		}
		else if (dir == 1) { // 1�϶�
			for (j = 0; j < 3; j++) {
				for (k = 0; k < 6; k++) {
					map[random_x + j][random_y + k] = 2; // ���� 6ĭ * ���� 3ĭ�� Ǯ���� ���
				}
			}
		}

	}
}

void wall() { // ���� ���������� �ִ� �Լ�

	int i, j, k, l = 0, ll = 0;
	srand(time(NULL)); // ������

	for (i = 0; i < 12; i++) {

		int random_x = (rand() % 31) + 1; // �� �ۿ� �������� �ʵ��� �صа�
		int random_y = (rand() % 31) + 1;// �� �ۿ� �������� �ʵ��� �صа�
		int dir = rand() % 4; // 4���� ���� ����
		if (dir == 0) {
			for (j = 0; j < 8; j++) {
				map[random_x + j][random_y] = 1; // ���η� 8ĭ ������
			}
		}
		else if (dir == 1) {
			for (j = 0; j < 8; j++) {
				map[random_x][random_y + j] = 1; // ���η� 8ĭ ������
			}
		}
		else if (dir == 2) {
			l = k = 0;
			for (j = 0; j < 4; j++) {
				for (k = 0; k < 2; k++) {
					map[random_x + l][random_y + ll] = 1; // ������� ��->�� ����
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
					map[random_x + l][random_y + ll] = 1; // ������� ��->�� ����
					l++;
				}
				ll--;
				l--;
			}
		}
	}
}

void gun() { // ���� ����ϴ� �Լ�

	int i;
	srand(time(NULL)); // ������

	while (1) {
		gun_x = (rand() % 38) + 1; // �� �ۿ� �������� �ʵ��� �صа�
		gun_y = (rand() % 38) + 1; // �� �ۿ� �������� �ʵ��� �صа�
		if (map[gun_y][gun_x] == SPACE) { // ������ ������϶��� ������ �ǵ�����
			map[gun_y][gun_x] = GUN;
			break;
		}
		else
			continue;
	}
}

void potion() { // ������ ����ϴ� �Լ�

	int i;
	srand(time(NULL)); // ������

	while (1) {
		potion_x = (rand() % 38) + 1; // �� �ۿ� �������� �ʵ��� �صа�
		potion_y = (rand() % 38) + 1; // �� �ۿ� �������� �ʵ��� �صа�
		if (map[potion_y][potion_x] == SPACE) { // ������ ������϶��� ������ �ǵ�����
			map[potion_y][potion_x] = POTION;
			break;
		}
		else
			continue;
	}
}

void player() { // p1 ���������� �ִ� �Լ�

	int i;
	srand(time(NULL));
	while (1) {
		int random_x = (rand() % 38) + 1;
		int random_y = (rand() % 38) + 1;
		if (map[random_y][random_x] == SPACE) { // ������� ����
			map[random_y][random_x] = PLAYER;
			break;
		}
		else
			continue;
	}

}

void player2() { // p2 ���������� �ִ� �Լ�

	int i;
	srand(time(NULL));
	while (1) {
		int random_x = (rand() % 38) + 1;
		int random_y = (rand() % 38) + 1;
		if (map[random_y][random_x] == SPACE) { // ������� ����
			map[random_y][random_x] = PLAYER2;
			break;
		}
		else
			continue;
	}

}