#pragma comment(lib, "ws2_32.lib")
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<winsock2.h>
#include<Windows.h>
#include<conio.h>

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
#define STRNULL 4 //���ڿ��� ����

char getKey();
char map[MAPSIZE][1000];
void win_lose(int);
void gotoxy(int, int);
void win_lose(); // �÷��̾ �̰����� ȣ��Ǵ� �Լ�
void print_infor(); // �÷��̾��� ��� ������ ����ϴ� �Լ�
void p1_print(); // p1�� ��� ���ִ� �Լ�
void bush_print(); // p1�� bush�� ��� ���ִ� �Լ�
void space_print(); // p1�� space�� ��� ���ִ� �Լ�
void binp_print(); // p1�� binp�� ��� ���ִ� �Լ�
void p2_print(); // p2�� ��� ���ִ� �Լ�
void bush2_print(); // p2�� bush�� ��� ���ִ� �Լ�
void space2_print(); // p2�� space�� ��� ���ִ� �Լ�
void binp2_print(); // p2�� binp�� ��� ���ִ� �Լ�

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

		printf("�ʱ�ȭ ����\n");

	clientsock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (clientsock == INVALID_SOCKET)
		printf("���� ���� ����\n");

	memset(&sockinfo, 0, sizeof(sockinfo));

	sockinfo.sin_family = AF_INET;
	sockinfo.sin_port = htons(atoi(argv[2]));
	sockinfo.sin_addr.s_addr = inet_addr(argv[1]);

	if (connect(clientsock, (SOCKADDR*)&sockinfo, sizeof(sockinfo)) == SOCKET_ERROR)
		printf(" ���� ���� ����\n");
	else
		printf("���� ���� ����\n");
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
			for (int j = 0; j < strlen(map[i]); j++) { // �� ��ü�� �� ����
				if (map[i][j] == STRNULL) { //���� ���ҵǴ� �����̶��,
					switch (t) { // �� ���ڿ� ���� �ٸ��� ���� ����� �ǵ��� �Ѵ�
						case WALL: printf("��"); break;
						case SPACE: printf("  "); break;
						case BUSH: SetConsoleTextAttribute(COL, 2); gotoxy(cnt++, i); printf("��"); SetConsoleTextAttribute(COL, 15); break;
						case GUN: SetConsoleTextAttribute(COL, 4); gotoxy(cnt++, i); printf("��"); SetConsoleTextAttribute(COL, 15); break;
						case POTION: SetConsoleTextAttribute(COL, 3); gotoxy(cnt++, i); printf("��"); SetConsoleTextAttribute(COL, 15); break;
						case GINP: SetConsoleTextAttribute(COL, 4); gotoxy(cnt++, i); printf("��"); SetConsoleTextAttribute(COL, 15); break;
						case BINP: SetConsoleTextAttribute(COL, 2); gotoxy(cnt++, i); printf("��"); SetConsoleTextAttribute(COL, 15); break;
						case PLAYER: SetConsoleTextAttribute(COL, 6); gotoxy(cnt++, i); printf("��"); SetConsoleTextAttribute(COL, 15); break;
						case GINP2 : SetConsoleTextAttribute(COL, 4); gotoxy(cnt++, i); printf("��"); SetConsoleTextAttribute(COL, 15); break;
						case BINP2 : SetConsoleTextAttribute(COL, 2); gotoxy(cnt++, i); printf("��"); SetConsoleTextAttribute(COL, 15); break;
						case PLAYER2: SetConsoleTextAttribute(COL, 6); gotoxy(cnt++, i); printf("��"); SetConsoleTextAttribute(COL, 15); break;
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
		print_infor(); // �÷��̾� ������ ���
		win_lose(); // � �÷��̾ �̰���� ��� ���̰����� �ƹ��͵� ��� ����
	}
	closesocket(clientsock);
	WSACleanup();
}

char getKey()
{
	Sleep(10);
	if (kbhit()) // kbhit()�̿��� �Է°��� �ִ��� Ȯ�� 
	{
		return getch();     // �Է°��� getch()�� char�� ��������
	}
	return '\0'; // �Է°��� ������ �� ���� ����
}

void gotoxy(int x, int y) // Ŀ�� �̵� �Լ�
{
	COORD Pos;
	Pos.X = x * 2;
	Pos.Y = y;
	SetConsoleCursorPosition(COL, Pos);
}
void print_infor() {
	int i;
	gotoxy(43, 6);
	printf("������ �� �÷��̾� ���� �� ������"); // UI ����
	for (i = 7; i <= 32; i++) {
		gotoxy(43, i);
		printf("��                       ��");
	}
	gotoxy(43, 33);
	printf("��������������������������������������������������");
	gotoxy(46, 15);
	printf("P1 ��� : %d", p1); // p1 ��� ���
	gotoxy(46, 20);
	printf("P2 ��� : %d", p2); // p2 ��� ���
}

void win_lose() {
	int i;
	if (p1 == 0) { // p1�� ����� 0�̸�
		gotoxy(43, 6);
		printf("������ �� �÷��̾� ���� �� ������"); // UI ����
		for (i = 7; i <= 32; i++) {
			gotoxy(43, i);
			printf("��                       ��");
		}
		gotoxy(43, 33);
		printf("��������������������������������������������������");
		gotoxy(47, 19);
		printf("P2 Winner!!        "); // p2 �¸� ���
	}
	else if (p2 == 0) {
		gotoxy(43, 6);
		printf("������ �� �÷��̾� ���� �� ������"); // UI ����
		for (i = 7; i <= 32; i++) {
			gotoxy(43, i);
			printf("��                       ��");
		}
		gotoxy(43, 33);
		printf("��������������������������������������������������");
		gotoxy(47, 19);
		printf("P1 Winner!!        "); // p1 �¸� ���
	}
}