#include <stdio.h>
#include <stdlib.h>

#define BLACK_COLOR 10 //������ɫ
#define WHITE_COLOR 20 //������ɫ
#define BOARD_SIZE 14 //����������


void ChooseGameMode(); //ѡ����Ϸģʽ
void PeopleVSComputer(); //�˻���ս
void PeopleVSPeople(); //���˶�ս
void PeopleVSPeople_BlackPlay(); //���˶�ս_������
void PeopleVSPeople_WhitePlay(); //���˶�ս_������
void DisplayBoard();
void ResetBoardArray();
void PeopleVSComputer_PeopleBlackPlay(); //�˻���ս_�˳ֺ���
void PeopleVSComputer_PeopleWhitePlay(); //�˻���ս_�˳ְ���
void PeopleVSComputer_ComputerBlackPlay(); //�˻���ս_���ֺ���
void PeopleVSComputer_ComputerWhitePlay(); //�˻���ս_���ְ���
void WhoIsWinning();
void WhoIsWin_Horizon(); //ˮƽ�����ж���Ӯ
void WhoIsWin_Vertical(); //��ֱ�����ж���Ӯ
void WhoIsWin_OneThreeQuadrant(); //һ�����޷����ж���Ӯ
void WhoIsWin_TwoFourQuadrant(); //�������޷����ж���Ӯ
void Score_H(int, int, int); //������
void Score_V(int, int, int); //������
void Score_OT(int, int, int, int); //һ�����޴��
void Score_TF(int, int, int, int); //�������޴��
void getScope_H_Black(int Line, int BeginH, int EndH, int scope); //����º����ֱ���
void getScope_H_White(int Line, int BeginH, int EndH, int scope); //����չ�����ֱ���
void getScope_V_Black(int Column, int BeginV, int EndV, int scope); //����º����ֱ���
void getScope_V_White(int Column, int BeginV, int EndV, int scope); //����չ�����ֱ���
void getScope_OT_Black(int, int, int, int, int, int, int); //һ�����޶º����ֱ���
void getScope_OT_White(int, int, int, int, int, int, int); //һ�����޷�չ�����ֱ���
void getScope_TF_Black(int, int, int, int, int, int, int); //�������޶º����ֱ���
void getScope_TF_White(int, int, int, int, int, int, int); //�������޷�չ�����ֱ���
void CleanScore(); //�����
void MaxScore(); //������������
void IsOpposite_Black(); //�жϺ���X,Y���������Ƿ�淶
void IsOpposite_White(); //�жϰ���X,Y���������Ƿ�淶
void ChessRepeat_Black(); //�жϺ����Ƿ��ظ�����
void ChessRepeat_White(); //�жϰ����Ƿ��ظ�����
void ChessBeyondBoard_Black(); //�жϺ��������Ƿ񳬳�����
void ChessBeyondBoard_White(); //�жϰ��������Ƿ񳬳�����
void ChessShape(); //�趨������״������ǰ����������״�����ǡ�/������һ����������״��Բ�Ρ�/��
void BanHand_3_Horizon(int); //ˮƽ����x++��y++���жϺ������
void BanHand_3_Vertical(int); //��ֱ����x++��y++���жϺ������
void BanHand_3_OneThreeQuadrant(int, int); //һ�����޷���x++��y++���жϺ������
void BanHand_3_TwoFourQuadrant(int, int); //�������޷���x++��y--���жϺ������
void BanHand_4_Horizon(int); //ˮƽ����x++��y++���жϺ������
void BanHand_4_Vertical(int); //��ֱ����x++��y++���жϺ������
void BanHand_4_OneThreeQuadrant(int, int); //һ�����޷���x++��y++���жϺ������
void BanHand_4_TwoFourQuadrant(int, int); //�������޷���x++��y--���жϺ������
void GameOver(); //��Ϸ����


int ChessCount_H(int Line, int Color);	//�����������
int ChessCount_V(int Column, int Color);	//�����������
int ChessCount_OT(int Line, int Column, int Color); //һ�����޼�������
int ChessCount_TF(int Line, int Column, int Color); //�������޼�������
int CharToNum(char c); //��ĸת�����±�

struct Color SetColor(struct Color); //�趨������ɫ�������ɫ�Ľṹ�庯��

int Board[15][15];
//int x = 0, y = 0;
int xBlack = 0, yBlack = 0; //����������������꣺xBlack�����ꣻyBlack������
int xWhite = 0, yWhite = 0; //����������������꣺xWhite�����ꣻyWhite������
int xBlackLast = -1, yBlackLast = -1; //�����ϴ����ӵ�λ�����꣬�У�xBlackLast���У�yBlackLast
int xWhiteLast = -1, yWhiteLast = -1; //�����ϴ����ӵ�λ�����꣬�У�xWhiteLast���У�yWhiteLast

int count = 0; //������
int BeginH, EndH;//�������Ӵ�����ʼ�ͽ�β��־
int BeginV, EndV;//�������Ӵ�����ʼ�ͽ�β��־
int BeginOTx, BeginOTy, EndOTx, EndOTy;//һ���������Ӵ�����ʼ�ͽ�β��־
int BeginTFx, BeginTFy, EndTFx, EndTFy;//�����������Ӵ�����ʼ�ͽ�β��־

char xs[10] = {0};
char ys[10] = {0};


struct MAX //�趨���ֵ����ṹ��
{
	int Value;
	int x;
	int y;
};
struct MAX max;


struct Color //�趨������ɫ�������ɫ�Ľṹ��
{
	int iChangeColor; //�趨������ɫ
	int iChessColor; //�趨�����ɫ
};

struct Color sColor = {1, 0}; //sColor�ṹ����ÿ����Ա�ĳ�ֵ������iChangeColor = 1; iChessColor = 0


void main()
{
	system("color f0"); //f�׵ס�0����
	ChooseGameMode(); //ѡ����Ϸģʽ
}


//ѡ����Ϸģʽ
void ChooseGameMode() 
{
	int a;

	printf("*****��ӭ�������������*****\n\n");
	printf("���˻���ս�� or �����˶�ս��\n\n\n");
	printf("ѡ���˻���ս����������1\n");
	printf("ѡ�����˶�ս����������2\n");

	scanf("%d", &a);

	for (; ;)
	{
		//���³�ʼ����Ŀ�ģ����¿�ʼʱ�����������ֽ�����ң�����������ɫ�ļ�¼
		xBlack = 0;
		yBlack = 0;
		xWhite = 0;
		yWhite = 0;
		xBlackLast = -1; 
		yBlackLast = -1;
		xWhiteLast = -1;
		yWhiteLast = -1;
		sColor.iChangeColor = 1;
		sColor.iChessColor = 11;

		if (a == 1)
		{
			PeopleVSComputer(); //�˻���ս
		}
		else if (a == 2)
		{
			PeopleVSPeople(); //���˶�ս

		}
		else
		{
			printf("ѡ����Ч������������1����2��\n");

			scanf("%d", &a);
		}	
	}
}


//�˻���ս
void PeopleVSComputer() 
{
	int a;

	system("cls");

	printf("*****��ӭ�������������֮���˻���ս��ģʽ*****\n\n���ˡ� or ������\n\n\nѡ���ˡ񡿣�������1\nѡ�񡾻��񡿣�������2\n");

	scanf("%d", &a);

	for (; ;)
	{
		if (a == 1)
		{
			PeopleVSComputer_PeopleBlackPlay(); //�˳ֺ���
		}
		else if (a == 2)
		{
			printf("�����񡿹��ܴ����У�δ�����...\n����������1��\n");

			scanf("%d", &a);

			//ComputerBlackPlay(); //�������������ܴ����ƣ���������
			//PeopleWhitePlay(); //�˳ְ���
		}
		else
		{
			printf("ѡ����Ч������������1����2��\n");

			scanf("%d", &a);
		}	
	}
}


//���˶�ս
void PeopleVSPeople()
{
	char a;
	char as[10] = {0};

	system("cls");

	printf("*****��ӭ�������������֮�����˶�ս��ģʽ*****\n\nϵͳĬ�ϣ�\n�����1��\n�����2��\n\n������һ�ַ���ʼ����\n");

	scanf("%s", as); 

	a = atoi(as); 
	//atoi��ASCII��תint�ͺ������������������֣�ASCII���е������ַ�����0��Ӧʮ������48��������ת��int������
	//���������0-9�������ַ����򷵻�0


	for (; ;)
	{
		if (a >= 0 && a <= 10)
		{
			PeopleVSPeople_BlackPlay();
		}
		else
		{
			printf("ѡ����Ч��������������һ�ַ���\n");

			scanf("%s", as); 
		}	
	}
}


//��ʾ����
void DisplayBoard() //****��Ҫ�Ľ���Ӧ�ü�������
{	
	int i, j;

	for(j = BOARD_SIZE; j >= 0; j--)
		//for(j = 0; j <= BOARD_SIZE; j++)
	{
		printf("%2d", j+1);
		for(i = 0; i <= BOARD_SIZE; i++)
		{
			switch(Board[j][i] % 100)	//�����з�ֵ�����ʾ����
			{
			case 1:
				printf("��");
				break;

			case 2:
				printf("��");
				break;

			case 3:
				printf("��");
				break;

			case 4:
				printf("��");
				break;

			case 5:
				printf("��");
				break;

			case 6:
				printf("��");
				break;

			case 7:
				printf("��");
				break;

			case 8:
				printf("��");
				break;

			case 9:
				printf("��");
				break;

			case 10:
				printf("��");
				break;

			case 11:
				printf("��");
				break;

			case 20:
				printf("��");
				break;

			case 21:
				printf("��");
				break;
			}
			if (i == BOARD_SIZE)
			{
				printf("\n");
			}
		}
	}
	printf("   A B C D E F G H I J K L M N O\n");
}


//��������
void ResetBoardArray()
{
	int i, j; //j���У�i����

	Board[0][0] = 1;
	Board[0][BOARD_SIZE] = 2;
	Board[BOARD_SIZE][BOARD_SIZE] = 3;
	Board[BOARD_SIZE][0] = 4;

	for (j = 1; j <= 13; j++)
	{
		Board[j][0] = 5;
	}

	for (i = 1; i <= 13; i++)
	{
		Board[0][i] = 6;
	}

	for (j = 1; j <= 13; j++)
	{
		Board[j][BOARD_SIZE] = 7;
	}

	for (i = 1; i <= 13; i++)
	{
		Board[BOARD_SIZE][i] = 8;
	}

	for (j = 1; j <= 13; j++)
	{
		for (i = 1; i <= 13; i++)
		{
			Board[j][i] = 9;
		}
	}
}


//�˻���ս֮�˳֡�
void PeopleVSComputer_PeopleBlackPlay() 
{
	int j = 0, i = 0;

	system("cls");	//���֮ǰ����Ļ��ʾ��ʹ���ָ����λ��

	ResetBoardArray();
	DisplayBoard();

	while(yBlack >= 0 && yBlack <= BOARD_SIZE)	
	{
		while (0 <= xBlack && xBlack <= BOARD_SIZE)
		{
			//ys,xs�������ַ����������е��ַ����������ַ�������ʽ���档�������Ԫ�طֱ�洢�ַ����ĸ����ַ�
			scanf("%s %s", ys, xs); 

			//atoi��ASCII��תint�ͺ������������������֣�ASCII���е������ַ�����0��Ӧʮ������48��������ת��int������
			//���������0-9�������ַ����򷵻�0

			yBlack = atoi(ys); 
			xBlack = xs[0]; //�˾���˼�ǣ���xs����ĵ�0��Ԫ�ص�ֵ������xBlack

			IsOpposite_Black(/*yBlack, xBlack, BLACK_COLOR*/); //�жϺ���X,Y���������Ƿ�淶

			system("cls");
			DisplayBoard();

			yBlack -= 1; //������1��15��ת������0��14
			xBlack = CharToNum(xBlack);	//��������ת�����±꣬������ĸת������0��14

			ChessRepeat_Black(/*yBlack, xBlack, BLACK_COLOR*/);
			ChessBeyondBoard_Black(/*yBlack, xBlack, BLACK_COLOR*/);

			sColor = SetColor(sColor); //�趨������ɫ�������ɫ

			Board[yBlack][xBlack] = sColor.iChessColor;

			system("cls");	//���֮ǰ����Ļ��ʾ��ʹ���ָ����λ��
			DisplayBoard();

			ChessShape();

			WhoIsWinning();

			PeopleVSComputer_ComputerWhitePlay(); //���ְ������
		}
	}
}


//�˻���ս֮���֡�
void PeopleVSComputer_ComputerWhitePlay()
{
	if (Board[yBlack][xBlack] = 11)
	{
		MaxScore(); //���ֵ��ߵ�λ��

		xWhite = max.x;
		yWhite = max.y;
	}

	Board[max.y][max.x] = 21; //���жϼ����������λ���Ƿ���������/����߽磬֮���ٸ�ֵ

	sColor = SetColor(sColor);

	Board[yWhite][xWhite] = sColor.iChessColor;
	system("cls");	//���֮ǰ����Ļ��ʾ��ʹ���ָ����λ��
	DisplayBoard();

	ChessShape();

	WhoIsWinning();
}


//�˻���ս֮���֡�
void PeopleVSComputer_ComputerBlackPlay()
{
	;
}


//�˻���ս֮�˳֡�
void PeopleVSComputer_PeopleWhitePlay()
{
	;
}


//���˶�ս֮������
void PeopleVSPeople_BlackPlay()
{
	int j = 0, i = 0;

	system("cls");	//���֮ǰ����Ļ��ʾ��ʹ���ָ����λ��

	ResetBoardArray();
	DisplayBoard();

	while(yBlack >= 0 && yBlack <= BOARD_SIZE)	
	{
		while (0 <= xBlack && xBlack <= BOARD_SIZE)
		{
			//ys,xs�������ַ����������е��ַ����������ַ�������ʽ���档�������Ԫ�طֱ�洢�ַ����ĸ����ַ�
			scanf("%s %s", ys, xs); 

			//atoi��ASCII��תint�ͺ������������������֣�ASCII���е������ַ�����0��Ӧʮ������48��������ת��int������
			//���������0-9�������ַ����򷵻�0

			yBlack = atoi(ys); 
			xBlack = xs[0]; //�˾���˼�ǣ���xs����ĵ�0��Ԫ�ص�ֵ������xBlack

			IsOpposite_Black(/*yBlack, xBlack, BLACK_COLOR*/); //�жϺ���X,Y���������Ƿ�淶

			system("cls");
			DisplayBoard();

			yBlack -= 1; //������1��15��ת������0��14
			xBlack = CharToNum(xBlack);	//��������ת�����±꣬������ĸת������0��14

			ChessRepeat_Black(/*yBlack, xBlack, BLACK_COLOR*/);
			ChessBeyondBoard_Black(/*yBlack, xBlack, BLACK_COLOR*/);

			sColor = SetColor(sColor); //�趨������ɫ�������ɫ

			Board[yBlack][xBlack] = sColor.iChessColor;

			system("cls");	//���֮ǰ����Ļ��ʾ��ʹ���ָ����λ��
			DisplayBoard();

			ChessShape();

			WhoIsWinning();

			PeopleVSPeople_WhitePlay();
		}
	}
}


//���˶�ս֮������
void PeopleVSPeople_WhitePlay()
{
	int j = 0, i = 0;

	//ys,xs�������ַ����������е��ַ����������ַ�������ʽ���档�������Ԫ�طֱ�洢�ַ����ĸ����ַ�
	scanf("%s %s", ys, xs); 

	//atoi��ASCII��תint�ͺ������������������֣�ASCII���е������ַ�����0��Ӧʮ������48��������ת��int������
	//���������0-9�������ַ����򷵻�0

	yWhite = atoi(ys); 
	xWhite = xs[0]; //�˾���˼�ǣ���xs����ĵ�0��Ԫ�ص�ֵ������xWhite

	IsOpposite_White(); //�жϰ���X��Y�����Ƿ��䷴��

	system("cls");
	DisplayBoard();

	yWhite -= 1; //������1��15��ת������0��14
	xWhite = CharToNum(xWhite);	//��������ת�����±꣬������ĸת������0��14

	ChessRepeat_White(); //�жϰ����Ƿ��ظ�����
	ChessBeyondBoard_White(); //�жϰ��������Ƿ񳬳�����

	sColor = SetColor(sColor); //�趨������ɫ�������ɫ

	Board[yWhite][xWhite] = sColor.iChessColor;

	system("cls");	//���֮ǰ����Ļ��ʾ��ʹ���ָ����λ��
	DisplayBoard();

	ChessShape();

	WhoIsWinning();
}



////�жϺ���X,Y���������Ƿ�淶
void IsOpposite_Black()
{
	// (yBlack == 0)����Ϊatoi����������ķ�0-9�������ַ�����������Ϊ0
	// (xBlack < 58)����Ϊʮ���Ƶ�57��Ӧ���ַ�������9������ֻҪС�ڵ���9�ģ�������Ϊ���������
	while((yBlack == 0) || (xBlack < 58)) 
	{
		system("cls");
		DisplayBoard();
		printf("(X,Y)�������벻�淶�����������룡\nע�⣺���������˳��Ϊ�����֣���ĸ��\n");

		scanf("%s %s", ys, xs);
		yBlack = atoi(ys);
		xBlack = xs[0];
	}
}


//�жϺ����Ƿ��ظ�����
void ChessRepeat_Black()
{
	//�������λ���������ӣ�����������
	while ((Board[yBlack][xBlack] % 100) >=10) //ֻҪ�����Ӵ��󣬾Ͳ������½��У�ֱ��������ȷ������Ϊֹ
	{
		system("cls");
		DisplayBoard();
		printf("��λ���������ӣ�����������\n");

		scanf("%d %c", &yBlack, &xBlack);
		xBlack = CharToNum(xBlack);	//��������ת�����±�
		yBlack -= 1;
	}
}


//�жϺ��������Ƿ񳬳�����
void ChessBeyondBoard_Black()
{
	//�������λ���ѳ����̱߽磬����������
	while((yBlack > BOARD_SIZE) || (xBlack > BOARD_SIZE)) //ֻҪ�����Ӵ��󣬾Ͳ������½��У�ֱ��������ȷ������Ϊֹ
	{
		system("cls");
		DisplayBoard();
		printf("����λ���ѳ����̱߽磬���������룡\n");

		scanf("%d %c", &yBlack, &xBlack);
		xBlack = CharToNum(xBlack);	//��������ת�����±�
		yBlack -= 1;
	}
}


//�жϰ���X��Y�����Ƿ��䷴��-�˳ְ���ʱ���ã����ְ��岻��
void IsOpposite_White()
{
	// (yWhite == 0)����Ϊatoi����������ķ�0-9�������ַ�����������Ϊ0
	// (xWhite < 58)����Ϊʮ���Ƶ�57��Ӧ���ַ�������9������ֻҪС�ڵ���9�ģ�������Ϊ���������
	while((yWhite == 0) || (xWhite < 58)) 
	{
		system("cls");
		DisplayBoard();
		printf("(X,Y)�������벻�淶�����������룡\nע�⣺���������˳��Ϊ�����֣���ĸ��\n");

		scanf("%s %s", ys, xs);
		yWhite = atoi(ys);
		xWhite = xs[0];
	}
}


//�жϰ����Ƿ��ظ�����-�˳ְ���ʱ���ã����ְ��岻��
void ChessRepeat_White()
{
	//�������λ���������ӣ�����������
	while ((Board[yWhite][xWhite] % 100) >=10) //ֻҪ�����Ӵ��󣬾Ͳ������½��У�ֱ��������ȷ������Ϊֹ
	{
		system("cls");
		DisplayBoard();
		printf("��λ���������ӣ�����������\n");

		scanf("%d %c", &yWhite, &xWhite);
		xWhite = CharToNum(xWhite);	//��������ת�����±�
		yWhite -= 1;
	}
}


//�жϰ��������Ƿ񳬳�����-�˳ְ���ʱ���ã����ְ��岻��
void ChessBeyondBoard_White()
{
	//�������λ���ѳ����̱߽磬����������
	while((yWhite > BOARD_SIZE) || (xWhite > BOARD_SIZE)) //ֻҪ�����Ӵ��󣬾Ͳ������½��У�ֱ��������ȷ������Ϊֹ
	{
		system("cls");
		DisplayBoard();
		printf("����λ���ѳ����̱߽磬���������룡\n");

		scanf("%d %c", &yWhite, &xWhite);
		xWhite = CharToNum(xWhite);	//��������ת�����±�
		yWhite -= 1;
	}
} 



//�趨������ɫ�������ɫ
struct Color SetColor(struct Color sColor)  
{
	if (sColor.iChangeColor == 1)
	{
		sColor.iChessColor = 11;
		if (xBlackLast != -1 && yBlackLast != -1) //�жϺ�������Ƿ�����һ�����ӣ��������if���
		{
			Board[yBlackLast][xBlackLast] = 10; //��һ�������ɡ���Ϊ��
		}
		sColor.iChangeColor = 2; //******��ҽ���
	}
	else
	{
		sColor.iChessColor = 21;
		if (xWhiteLast != -1 && yWhiteLast != -1) //�жϰ�������Ƿ�����һ�����ӣ��������if���
		{
			Board[yWhiteLast][xWhiteLast] = 20; //��һ�������ɡ���Ϊ��
		}
		sColor.iChangeColor = 1; //******��ҽ���
	}
	//*****�����趨���������ɫ
	return sColor;
}


//�趨������״������ǰ����������״�����ǡ�/������һ����������״��Բ�Ρ�/��
void ChessShape()
{
	if (sColor.iChessColor == 11) //�ѵ�ǰ����λ�����긳��ǰһ��λ��
	{
		xBlackLast = xBlack;
		yBlackLast = yBlack;
	} 
	else
	{
		xWhiteLast = xWhite;
		yWhiteLast = yWhite;
	}
}


//�����������
int ChessCount_H(int Line, int Color)
{
	while(((Board[Line][BeginH] % 100) != Color) && ((Board[Line][BeginH] % 100) != Color + 1)) //�����Ǹ���ɫ���ӵĵ�
	{
		if (BeginH > BOARD_SIZE) //���߽���
		{
			EndH = BeginH;

			return 0;
		}
		BeginH ++;
	}

	EndH = BeginH + 1; //β���Ƶ�ʼ�����һλ

	//��ʼ��������
	while((Board[Line][EndH] % 100 == Color) || (Board[Line][EndH] % 100 == Color + 1))//+1���������ε�������ɫ
	{
		EndH ++;
	}


	//*******������������Ӵ��м���1���ո������*******

	//����[�񡡡�]��������ú������������ͬ��
	if (
		(EndH - BeginH == 1) 
		&& (Board[Line][EndH] % 100 <= 9) 
		&& ((Board[Line][EndH + 1] % 100 == Color) || (Board[Line][EndH + 1] % 100 == Color + 1)) 
		&& ((Board[Line][EndH + 2] % 100 != Color) && (Board[Line][EndH + 2] % 100 != Color + 1)) 
		)
	{
		EndH = EndH + 2;

		return EndH - BeginH - 1; //�������Ӵ�����
	}

	//����[��񡡡�]�����
	else if (
		(EndH - BeginH == 2) 
		&& (Board[Line][EndH] % 100 <= 9) 
		&& ((Board[Line][EndH + 1] % 100 == Color) || (Board[Line][EndH + 1] % 100 == Color + 1))
		&& ((Board[Line][EndH + 2] % 100 != Color) && (Board[Line][EndH + 2] % 100 != Color + 1)) 
		)
	{
		EndH = EndH + 2;

		return EndH - BeginH - 1; //�������Ӵ�����
	}

	//����[���񡡡�]�����
	else if (
		(EndH - BeginH == 3) 
		&& (Board[Line][EndH] % 100 <= 9) 
		&& ((Board[Line][EndH + 1] % 100 == Color) || (Board[Line][EndH + 1] % 100 == Color + 1))
		&& ((Board[Line][EndH + 2] % 100 != Color) && (Board[Line][EndH + 2] % 100 != Color + 1)) 
		)
	{
		EndH = EndH + 2;

		return EndH - BeginH - 1; //�������Ӵ�����
	}

	//����[�񡡡��]�����
	else if (
		(EndH - BeginH == 1) 
		&& (Board[Line][EndH] % 100 <= 9)
		&& ((Board[Line][EndH + 1] % 100 == Color) || (Board[Line][EndH + 1] % 100 == Color + 1))
		&& ((Board[Line][EndH + 2] % 100 == Color) || (Board[Line][EndH + 2] % 100 == Color + 1))
		&& ((Board[Line][EndH + 3] % 100 != Color) && (Board[Line][EndH + 3] % 100 != Color + 1)) 
		)
	{
		EndH = EndH + 3;

		return EndH - BeginH - 1; //�������Ӵ�����
	}

	//����[��񡡡��]�����
	else if (
		(EndH - BeginH == 2)
		&& (Board[Line][EndH] % 100 <= 9)
		&& ((Board[Line][EndH + 1] % 100 == Color) || (Board[Line][EndH + 1] % 100 == Color + 1))
		&& ((Board[Line][EndH + 2] % 100 == Color) || (Board[Line][EndH + 2] % 100 == Color + 1))
		&& ((Board[Line][EndH + 3] % 100 != Color) && (Board[Line][EndH + 3] % 100 != Color + 1)) 
		)
	{
		EndH = EndH + 3;

		return EndH - BeginH - 1; //�������Ӵ�����
	}

	//����[�񡡡���]�����
	else if (
		(EndH - BeginH == 1) 
		&& (Board[Line][EndH] % 100 <= 9)
		&& ((Board[Line][EndH + 1] % 100 == Color) || (Board[Line][EndH + 1] % 100 == Color + 1))
		&& ((Board[Line][EndH + 2] % 100 == Color) || (Board[Line][EndH + 2] % 100 == Color + 1))
		&& ((Board[Line][EndH + 3] % 100 == Color) || (Board[Line][EndH + 3] % 100 == Color + 1))
		&& ((Board[Line][EndH + 4] % 100 != Color) && (Board[Line][EndH + 4] % 100 != Color + 1)) 
		)
	{
		EndH = EndH + 4;

		return EndH - BeginH - 1; //�������Ӵ�����
	}

	return EndH - BeginH; //�������Ӵ�����
}


//�����������
int ChessCount_V(int Column, int Color)
{
	while(((Board[BeginV][Column] % 100) != Color) && ((Board[BeginV][Column] % 100) != Color + 1)) //�����Ǹ���ɫ���ӵĵ�
	{
		if (BeginV > BOARD_SIZE) //���߽���
		{
			EndV = BeginV;

			return 0;
		}
		BeginV++;
	}

	EndV = BeginV + 1; //β���Ƶ�ʼ�����һλ

	//��ʼ��������
	while((Board[EndV][Column] % 100 == Color) || (Board[EndV][Column] % 100 == Color + 1))//+1���������ε�������ɫ
	{
		EndV ++;
	}


	//*******������������Ӵ��м���1���ո������*******

	//����[�񡡡�]��������ú������������ͬ��
	if (
		(EndV - BeginV == 1) 
		&& (Board[EndV][Column] % 100 <= 9) 
		&& ((Board[EndV + 1][Column] % 100 == Color) || (Board[EndV + 1][Column] % 100 == Color + 1)) 
		&& ((Board[EndV + 2][Column] % 100 != Color) && (Board[EndV + 2][Column] % 100 != Color + 1)) 
		)
	{
		EndV = EndV + 2;

		return EndV - BeginV - 1; //�������Ӵ�����
	}

	//����[��񡡡�]�����
	else if (
		(EndV - BeginV == 2) 
		&& (Board[EndV][Column] % 100 <= 9) 
		&& ((Board[EndV + 1][Column] % 100 == Color) || (Board[EndV + 1][Column] % 100 == Color + 1))
		&& ((Board[EndV + 2][Column] % 100 != Color) && (Board[EndV + 2][Column] % 100 != Color + 1)) 
		)
	{
		EndV = EndV + 2;

		return EndV - BeginV - 1; //�������Ӵ�����
	}

	//����[���񡡡�]�����
	else if (
		(EndV - BeginV == 3) 
		&& (Board[EndV][Column] % 100 <= 9) 
		&& ((Board[EndV + 1][Column] % 100 == Color) || (Board[EndV + 1][Column] % 100 == Color + 1))
		&& ((Board[EndV + 2][Column] % 100 != Color) && (Board[EndV + 2][Column] % 100 != Color + 1)) 
		)
	{
		EndV = EndV + 2;

		return EndV - BeginV - 1; //�������Ӵ�����
	}

	//����[�񡡡��]�����
	else if (
		(EndV - BeginV == 1) 
		&& (Board[EndV][Column] % 100 <= 9) 
		&& ((Board[EndV + 1][Column] % 100 == Color) || (Board[EndV + 1][Column] % 100 == Color + 1))
		&& ((Board[EndV + 2][Column] % 100 == Color) || (Board[EndV + 2][Column] % 100 == Color + 1))
		&& ((Board[EndV + 3][Column] % 100 != Color) && (Board[EndV + 3][Column] % 100 != Color + 1)) 
		)
	{
		EndV = EndV + 3;

		return EndV - BeginV - 1; //�������Ӵ�����
	}

	//����[��񡡡��]�����
	else if (
		(EndV - BeginV == 2)
		&& (Board[EndV][Column] % 100 <= 9)
		&& ((Board[EndV + 1][Column] % 100 == Color) || (Board[EndV + 1][Column] % 100 == Color + 1))
		&& ((Board[EndV + 2][Column] % 100 == Color) || (Board[EndV + 2][Column] % 100 == Color + 1))
		&& ((Board[EndV + 3][Column] % 100 != Color) && (Board[EndV + 3][Column] % 100 != Color + 1)) 
		)
	{
		EndV = EndV + 3;

		return EndV - BeginV - 1; //�������Ӵ�����
	}

	//����[�񡡡���]�����
	else if (
		(EndV - BeginV == 1) 
		&& (Board[EndV][Column] % 100 <= 9)
		&& ((Board[EndV + 1][Column] % 100 == Color) || (Board[EndV + 1][Column] % 100 == Color + 1))
		&& ((Board[EndV + 2][Column] % 100 == Color) || (Board[EndV + 2][Column] % 100 == Color + 1))
		&& ((Board[EndV + 3][Column] % 100 == Color) || (Board[EndV + 3][Column] % 100 == Color + 1))
		&& ((Board[EndV + 4][Column] % 100 != Color) && (Board[EndV + 4][Column] % 100 != Color + 1)) 
		)
	{
		EndV = EndV + 4;

		return EndV - BeginV - 1; //�������Ӵ�����
	}

	return EndV - BeginV; //�������Ӵ�����
}


//һ�����޼�����������д��
int ChessCount_OT(int Line, int Column, int Color)
{
	while ((Column > BOARD_SIZE) || (Column < 0))//�����������̵Ĳ���
	{
		Column++;
		Line++;
	}
	BeginOTx = Column;
	BeginOTy = Line;

	while(((Board[BeginOTy][BeginOTx] % 100) != Color) 
		&&((Board[BeginOTy][BeginOTx] % 100) != Color + 1)) //�����Ǹ���ɫ���ӵĵ�
	{
		if ((BeginOTx > BOARD_SIZE) || (BeginOTy > BOARD_SIZE) || (BeginOTx < 0) || (BeginOTy < 0)) //���߽���
		{
			EndOTx = BeginOTx;
			EndOTy = BeginOTy;

			return 0;
		}
		BeginOTx ++;
		BeginOTy ++;
	}
	//����������������߽���ô�죿
	EndOTx = BeginOTx + 1; //β���Ƶ�ʼ�����һλ
	EndOTy = BeginOTy + 1; //β���Ƶ�ʼ�����һλ

	//��ʼ��������
	while((Board[EndOTy][EndOTx] % 100 == Color) || (Board[EndOTy][EndOTx] % 100 == Color + 1))//+1���������ε�������ɫ
	{
		EndOTx ++;
		EndOTy ++;
	}


	//*******������������Ӵ��м���1���ո������*******

	//����[�񡡡�]��������ú������������ͬ��
	if (
		(EndOTx - BeginOTx == 1) 
		&& (Board[EndOTy][EndOTx] % 100 <= 9) 
		&& ((Board[EndOTy + 1][EndOTx + 1] % 100 == Color) || (Board[EndOTy + 1][EndOTx + 1] % 100 == Color + 1)) 
		&& ((Board[EndOTy + 2][EndOTx + 2] % 100 != Color) && (Board[EndOTy + 2][EndOTx + 2] % 100 != Color + 1)) 
		)
	{
		EndOTx = EndOTx + 2;
		EndOTy = EndOTy + 2;

		return EndOTx - BeginOTx - 1; //�������Ӵ�����
	}

	//����[��񡡡�]�����
	else if (
		(EndOTx - BeginOTx == 2) 
		&& (Board[EndOTy][EndOTx] % 100 <= 9) 
		&& ((Board[EndOTy + 1][EndOTx + 1] % 100 == Color) || (Board[EndOTy + 1][EndOTx + 1] % 100 == Color + 1))
		&& ((Board[EndOTy + 2][EndOTx + 2] % 100 != Color) && (Board[EndOTy + 2][EndOTx + 2] % 100 != Color + 1)) 
		)
	{
		EndOTx = EndOTx + 2;
		EndOTy = EndOTy + 2;

		return EndOTx - BeginOTx - 1; //�������Ӵ�����
	}

	//����[���񡡡�]�����
	else if (
		(EndOTx - BeginOTx == 3) 
		&& (Board[EndOTy][EndOTx] % 100 <= 9) 
		&& ((Board[EndOTy + 1][EndOTx + 1] % 100 == Color) || (Board[EndOTy + 1][EndOTx + 1] % 100 == Color + 1))
		&& ((Board[EndOTy + 2][EndOTx + 2] % 100 != Color) && (Board[EndOTy + 2][EndOTx + 2] % 100 != Color + 1)) 
		)
	{
		EndOTx = EndOTx + 2;
		EndOTy = EndOTy + 2;

		return EndOTx - BeginOTx - 1; //�������Ӵ�����
	}

	//����[�񡡡��]�����
	else if (
		(EndOTx - BeginOTx == 1) 
		&& (Board[EndOTy][EndOTx] % 100 <= 9)
		&& ((Board[EndOTy + 1][EndOTx + 1] % 100 == Color) || (Board[EndOTy + 1][EndOTx + 1] % 100 == Color + 1))
		&& ((Board[EndOTy + 2][EndOTx + 2] % 100 == Color) || (Board[EndOTy + 2][EndOTx + 2] % 100 == Color + 1))
		&& ((Board[EndOTy + 3][EndOTx + 3] % 100 != Color) && (Board[EndOTy + 3][EndOTx + 3] % 100 != Color + 1)) 
		)
	{
		EndOTx = EndOTx + 3;
		EndOTy = EndOTy + 3;

		return EndOTx - BeginOTx - 1; //�������Ӵ�����
	}

	//����[��񡡡��]�����
	else if (
		(EndOTx - BeginOTx == 2)
		&& (Board[EndOTy][EndOTx] % 100 <= 9)
		&& ((Board[EndOTy + 1][EndOTx + 1] % 100 == Color) || (Board[EndOTy + 1][EndOTx + 1] % 100 == Color + 1))
		&& ((Board[EndOTy + 2][EndOTx + 2] % 100 == Color) || (Board[EndOTy + 2][EndOTx + 2] % 100 == Color + 1))
		&& ((Board[EndOTy + 3][EndOTx + 3] % 100 != Color) && (Board[EndOTy + 3][EndOTx + 3] % 100 != Color + 1)) 
		)
	{
		EndOTx = EndOTx + 3;
		EndOTy = EndOTy + 3;

		return EndOTx - BeginOTx - 1; //�������Ӵ�����
	}

	//����[�񡡡���]�����
	else if (
		(EndOTx - BeginOTx == 1) 
		&& (Board[EndOTy][EndOTx] % 100 <= 9)
		&& ((Board[EndOTy + 1][EndOTx + 1] % 100 == Color) || (Board[EndOTy + 1][EndOTx + 1] % 100 == Color + 1))
		&& ((Board[EndOTy + 2][EndOTx + 2] % 100 == Color) || (Board[EndOTy + 2][EndOTx + 2] % 100 == Color + 1))
		&& ((Board[EndOTy + 3][EndOTx + 3] % 100 == Color) || (Board[EndOTy + 3][EndOTx + 3] % 100 == Color + 1))
		&& ((Board[EndOTy + 4][EndOTx + 4] % 100 != Color) && (Board[EndOTy + 4][EndOTx + 4] % 100 != Color + 1)) 
		)
	{
		EndOTx = EndOTx + 4;
		EndOTy = EndOTy + 4;

		return EndOTx - BeginOTx - 1; //�������Ӵ�����
	}

	return EndOTx - BeginOTx; //�������Ӵ�����
}

//�������޼�����������д��
int ChessCount_TF(int Line, int Column, int Color)
{
	while (Column < 0) //�����������̵Ĳ��֣�������ࣩ
	{
		Column++;
		Line--;
	}
	BeginTFx = Column;
	BeginTFy = Line;

	while (Column > BOARD_SIZE) //�����������̵Ĳ��֣������Ҳࣩ
	{
		EndTFx = BeginTFx;
		EndTFy = BeginTFy;

		return 0;
	}


	while(((Board[BeginTFy][BeginTFx] % 100) != Color) 
		&& ((Board[BeginTFy][BeginTFx] % 100) != Color + 1)) //�����Ǹ���ɫ���ӵĵ�
	{
		if ((BeginTFx > BOARD_SIZE) || (BeginTFy > BOARD_SIZE) || (BeginTFx < 0) || (BeginTFy < 0)) //���߽���
		{
			EndTFx = BeginTFx;
			EndTFy = BeginTFy;

			return 0;
		}
		BeginTFx ++;
		BeginTFy --;
	}
	//����������������߽���ô�죿
	EndTFx = BeginTFx + 1; //β���Ƶ�ʼ�����һλ
	EndTFy = BeginTFy - 1; //β���Ƶ�ʼ�����һλ

	//��ʼ��������
	while((Board[EndTFy][EndTFx] % 100 == Color) || (Board[EndTFy][EndTFx] % 100 == Color + 1))//+1���������ε�������ɫ
	{
		EndTFx ++;
		EndTFy --;
	}


	//*******������������Ӵ��м���1���ո������*******

	//����[�񡡡�]��������ú������������ͬ��
	if (
		(EndTFx - BeginTFx == 1) 
		&& (Board[EndTFy][EndTFx] % 100 <= 9) 
		&& ((Board[EndTFy - 1][EndTFx + 1] % 100 == Color) || (Board[EndTFy - 1][EndTFx + 1] % 100 == Color + 1)) 
		&& ((Board[EndTFy - 2][EndTFx + 2] % 100 != Color) && (Board[EndTFy - 2][EndTFx + 2] % 100 != Color + 1)) 
		)
	{
		EndTFx = EndTFx + 2;
		EndTFy = EndTFy - 2;

		return EndTFx - BeginTFx - 1; //�������Ӵ�����
	}

	//����[��񡡡�]�����
	else if (
		(EndTFx - BeginTFx == 2) 
		&& (Board[EndTFy][EndTFx] % 100 <= 9) 
		&& ((Board[EndTFy - 1][EndTFx + 1] % 100 == Color) || (Board[EndTFy - 1][EndTFx + 1] % 100 == Color + 1))
		&& ((Board[EndTFy - 2][EndTFx + 2] % 100 != Color) && (Board[EndTFy - 2][EndTFx + 2] % 100 != Color + 1)) 
		)
	{
		EndTFx = EndTFx + 2;
		EndTFy = EndTFy - 2;

		return EndTFx - BeginTFx - 1; //�������Ӵ�����
	}

	//����[���񡡡�]�����
	else if (
		(EndTFx - BeginTFx == 3) 
		&& (Board[EndTFy][EndTFx] % 100 <= 9) 
		&& ((Board[EndTFy - 1][EndTFx + 1] % 100 == Color) || (Board[EndTFy - 1][EndTFx + 1] % 100 == Color + 1))
		&& ((Board[EndTFy - 2][EndTFx + 2] % 100 != Color) && (Board[EndTFy - 2][EndTFx + 2] % 100 != Color + 1)) 
		)
	{
		EndTFx = EndTFx + 2;
		EndTFy = EndTFy - 2;

		return EndTFx - BeginTFx - 1; //�������Ӵ�����
	}

	//����[�񡡡��]�����
	//(���ڶ��������жϵķ�����x++��y--�����ԣ�Ϊ������������޽����жϵ�forѭ��������ֻ��һ���ж����)
	else if (
		(EndTFx - BeginTFx == 1)
		&& (Board[EndTFy][EndTFx] % 100 <= 9)
		&& ((Board[EndTFy - 1][EndTFx + 1] % 100 == Color) || (Board[EndTFy - 1][EndTFx + 1] % 100 == Color + 1))
		&& ((Board[EndTFy - 2][EndTFx + 2] % 100 == Color) || (Board[EndTFy - 2][EndTFx + 2] % 100 == Color + 1))
		&& ((Board[EndTFy - 3][EndTFx + 3] % 100 != Color) && (Board[EndTFy - 3][EndTFx + 3] % 100 != Color + 1)) 
		)
	{
		EndTFx = EndTFx + 3;
		EndTFy = EndTFy - 3;

		return EndTFx - BeginTFx - 1; //�������Ӵ�����
	}

	//����[��񡡡��]�����
	else if (
		(EndTFx - BeginTFx == 2)
		&& (Board[EndTFy][EndTFx] % 100 <= 9)
		&& ((Board[EndTFy - 1][EndTFx + 1] % 100 == Color) || (Board[EndTFy - 1][EndTFx + 1] % 100 == Color + 1))
		&& ((Board[EndTFy - 2][EndTFx + 2] % 100 == Color) || (Board[EndTFy - 2][EndTFx + 2] % 100 == Color + 1))
		&& ((Board[EndTFy - 3][EndTFx + 3] % 100 != Color) && (Board[EndTFy - 3][EndTFx + 3] % 100 != Color + 1)) 
		)
	{
		EndTFx = EndTFx + 3;
		EndTFy = EndTFy - 3;

		return EndTFx - BeginTFx - 1; //�������Ӵ�����
	}

	//����[�񡡡���]�����
	//(���ڶ��������жϵķ�����x++��y--�����ԣ�Ϊ������������޽����жϵ�forѭ��������ֻ��һ���ж����)
	else if (
		(EndTFx - BeginTFx == 1)
		&& (Board[EndTFy][EndTFx] % 100 <= 9)
		&& ((Board[EndTFy - 1][EndTFx + 1] % 100 == Color) || (Board[EndTFy - 1][EndTFx + 1] % 100 == Color + 1))
		&& ((Board[EndTFy - 2][EndTFx + 2] % 100 == Color) || (Board[EndTFy - 2][EndTFx + 2] % 100 == Color + 1))
		&& ((Board[EndTFy - 3][EndTFx + 3] % 100 == Color) || (Board[EndTFy - 3][EndTFx + 3] % 100 == Color + 1)) 
		&& ((Board[EndTFy - 4][EndTFx + 4] % 100 != Color) && (Board[EndTFy - 4][EndTFx + 4] % 100 != Color + 1)) 
		)
	{
		EndTFx = EndTFx + 4;
		EndTFy = EndTFy - 4;

		return EndTFx - BeginTFx - 1; //�������Ӵ�����
	}

	return EndTFx - BeginTFx; //�������Ӵ�����
}


//������
void Score_H(int Line, int count, int Color) 
{
	if  ((Color == BLACK_COLOR) || (Color == BLACK_COLOR + 1)) //ͳ�ƺ������ӣ����¶���
	{
		switch(count)	//��ֱ�׼
		{
		case 1:	
			getScope_H_Black(Line, BeginH, EndH, 1000);
			break;

		case 2:	
			//����[�񡡡�]�����
			if (Board[Line][BeginH + 1] % 100 <= 9) 
			{
				getScope_H_Black(Line, BeginH, EndH, 2100);
				break;
			}

			getScope_H_Black(Line, BeginH, EndH, 2000);
			break;

		case 3:	
			//����[��񡡡�]�����
			if (Board[Line][BeginH + 2] % 100 <= 9) 
			{
				getScope_H_Black(Line, BeginH, EndH, 20000);
				break;
			}

			//����[�񡡡��]�����
			else if (Board[Line][BeginH + 1] % 100 <= 9) 
			{
				getScope_H_Black(Line, BeginH, EndH, 20000);
				break;
			}

			getScope_H_Black(Line, BeginH, EndH, 19000);
			break;

		case 4:	
			//����[���񡡡�]�����
			if (Board[Line][BeginH + 3] % 100 <= 9) 
			{
				getScope_H_Black(Line, BeginH, EndH, 210000);
				break;
			}

			//����[��񡡡��]�����
			else if (Board[Line][BeginH + 2] % 100 <= 9) 
			{
				getScope_H_Black(Line, BeginH, EndH, 210000);
				break;
			}

			//����[�񡡡���]�����
			else if (Board[Line][BeginH + 1] % 100 <= 9) 
			{
				getScope_H_Black(Line, BeginH, EndH, 210000);
				break;
			}

			getScope_H_Black(Line, BeginH, EndH, 200000);
			break;

		default:
			break;
		}
	}

	else //ͳ�ư������ӣ�����չ�Լ�
	{
		switch(count)	//��ֱ�׼
		{
		case 1:	
			getScope_H_White(Line, BeginH, EndH, 1200);
			break;

		case 2:	
			//����[�򡡡�]�����
			if (Board[Line][BeginH + 1] % 100 <= 9) 
			{
				getScope_H_White(Line, BeginH, EndH, 5000);
				break;
			}

			getScope_H_White(Line, BeginH, EndH, 5000);
			break;

		case 3:	
			//����[��򡡡�]�����
			if (Board[Line][BeginH + 2] % 100 <= 9) 
			{
				getScope_H_White(Line, BeginH, EndH, 28000);
				break;
			}

			//����[�򡡡��]�����
			else if (Board[Line][BeginH + 1] % 100 <= 9) 
			{
				getScope_H_White(Line, BeginH, EndH, 28000);
				break;
			}

			getScope_H_White(Line, BeginH, EndH, 28000);
			break;

		case 4:	
			//����[���򡡡�]�����
			if (Board[Line][BeginH + 3] % 100 <= 9) 
			{
				getScope_H_White(Line, BeginH, EndH, 5000000);
				break;
			}

			//����[��򡡡��]�����
			else if (Board[Line][BeginH + 2] % 100 <= 9) 
			{
				getScope_H_White(Line, BeginH, EndH, 5000000);
				break;
			}

			//����[�򡡡���]�����
			else if (Board[Line][BeginH + 1] % 100 <= 9) 
			{
				getScope_H_White(Line, BeginH, EndH, 5000000);
				break;
			}

			getScope_H_White(Line, BeginH, EndH, 5000000);
			break;

		default:
			break;
		}
	}
}


//������
void Score_V(int Column, int count, int Color) 
{
	if ((Color == BLACK_COLOR) || (Color == BLACK_COLOR + 1)) //ͳ�ƺ������ӣ����¶���
	{
		switch(count)	//��ֱ�׼
		{
		case 1:	
			getScope_V_Black(Column, BeginV, EndV, 1000);
			break;

		case 2:	
			//����[�񡡡�]�����
			if (Board[BeginV + 1][Column] % 100 <= 9) 
			{
				getScope_V_Black(Column, BeginV, EndV, 2100);
				break;
			}

			getScope_V_Black(Column, BeginV, EndV, 2000);
			break;
			//����Ӧ�ÿ���������֮���пո������

		case 3:	
			//����[��񡡡�]�����
			if (Board[BeginV + 2][Column] % 100 <= 9) 
			{
				getScope_V_Black(Column, BeginV, EndV, 20000);
				break;
			}

			//����[�񡡡��]�����
			else if (Board[BeginV + 1][Column] % 100 <= 9) 
			{
				getScope_V_Black(Column, BeginV, EndV, 20000);
				break;
			}

			getScope_V_Black(Column, BeginV, EndV, 19000);
			break;
			//����Ӧ�ÿ���������֮���пո������

		case 4:	
			//����[���񡡡�]�����
			if (Board[BeginV + 3][Column] % 100 <= 9) 
			{
				getScope_V_Black(Column, BeginV, EndV, 210000);
				break;
			}

			//����[��񡡡��]�����
			else if (Board[BeginV + 2][Column] % 100 <= 9) 
			{
				getScope_V_Black(Column, BeginV, EndV, 210000);
				break;
			}

			//����[�񡡡���]�����
			else if (Board[BeginV + 1][Column] % 100 <= 9) 
			{
				getScope_V_Black(Column, BeginV, EndV, 210000);
				break;
			}

			getScope_V_Black(Column, BeginV, EndV, 200000);
			break;
			//����Ӧ�ÿ���������֮���пո������

		default:
			break;
		}
	}

	else //ͳ�ư������ӣ�����չ�Լ�
	{
		switch(count)	//��ֱ�׼
		{
		case 1:	
			getScope_V_White(Column, BeginV, EndV, 1200);
			break;

		case 2:	
			//����[�򡡡�]�����
			if (Board[BeginV + 1][Column] % 100 <= 9) 
			{
				getScope_V_White(Column, BeginV, EndV, 5000);
				break;
			}

			getScope_V_White(Column, BeginV, EndV, 5000);
			break;

		case 3:	
			//����[��򡡡�]�����
			if (Board[BeginV + 2][Column] % 100 <= 9) 
			{
				getScope_V_White(Column, BeginV, EndV, 28000);
				break;
			}

			//����[�򡡡��]�����
			else if (Board[BeginV + 1][Column] % 100 <= 9) 
			{
				getScope_V_White(Column, BeginV, EndV, 28000);
				break;
			}

			getScope_V_White(Column, BeginV, EndV, 28000);
			break;

		case 4:	
			//����[���򡡡�]�����
			if (Board[BeginV + 3][Column] % 100 <= 9) 
			{
				getScope_V_White(Column, BeginV, EndV, 5000000);
				break;
			}

			//����[��򡡡��]�����
			else if (Board[BeginV + 2][Column] % 100 <= 9) 
			{
				getScope_V_White(Column, BeginV, EndV, 5000000);
				break;
			}

			//����[�򡡡���]�����
			else if (Board[BeginV + 1][Column] % 100 <= 9) 
			{
				getScope_V_White(Column, BeginV, EndV, 5000000);
				break;
			}

			getScope_V_White(Column, BeginV, EndV, 5000000);
			break;

		default:
			break;
		}
	}
}


//һ�����޴��
void Score_OT(int Line, int Column, int count, int Color) 
{
	if ((Color == BLACK_COLOR) || (Color == BLACK_COLOR + 1)) //ͳ�ƺ������ӣ����¶���
	{
		switch(count)	//��ֱ�׼
		{
		case 1:	
			getScope_OT_Black(Line, Column, BeginOTx, BeginOTy, EndOTx, EndOTy, 1000);
			break;

		case 2:	
			//����[�񡡡�]�����
			if (Board[BeginOTy + 1][BeginOTx + 1] % 100 <= 9) 
			{
				getScope_OT_Black(Line, Column, BeginOTx, BeginOTy, EndOTx, EndOTy, 2100);
				break;
			}

			getScope_OT_Black(Line, Column, BeginOTx, BeginOTy, EndOTx, EndOTy, 2000);
			break;

		case 3:	
			//����[��񡡡�]�����
			if (Board[BeginOTy + 2][BeginOTx + 2] % 100 <= 9) 
			{
				getScope_OT_Black(Line, Column, BeginOTx, BeginOTy, EndOTx, EndOTy, 20000);
				break;
			}

			//����[�񡡡��]�����
			else if (Board[BeginOTy + 1][BeginOTx + 1] % 100 <= 9) 
			{
				getScope_OT_Black(Line, Column, BeginOTx, BeginOTy, EndOTx, EndOTy, 20000);
				break;
			}

			getScope_OT_Black(Line, Column, BeginOTx, BeginOTy, EndOTx, EndOTy, 19000);
			break;

		case 4:	
			//����[���񡡡�]�����
			if (Board[BeginOTy + 3][BeginOTx + 3] % 100 <= 9) 
			{
				getScope_OT_Black(Line, Column, BeginOTx, BeginOTy, EndOTx, EndOTy, 210000);
				break;
			}

			//����[��񡡡��]�����
			else if (Board[BeginOTy + 2][BeginOTx + 2] % 100 <= 9) 
			{
				getScope_OT_Black(Line, Column, BeginOTx, BeginOTy, EndOTx, EndOTy, 210000);
				break;
			}

			//����[�񡡡���]�����
			else if (Board[BeginOTy + 1][BeginOTx + 1] % 100 <= 9) 
			{
				getScope_OT_Black(Line, Column, BeginOTx, BeginOTy, EndOTx, EndOTy, 210000);
				break;
			}

			getScope_OT_Black(Line, Column, BeginOTx, BeginOTy, EndOTx, EndOTy, 200000);
			break;

		default:
			break;
		}
	}

	else //ͳ�ư������ӣ�����չ�Լ�
	{
		switch(count)	//��ֱ�׼
		{
		case 1:	
			getScope_OT_White(Line, Column, BeginOTx, BeginOTy, EndOTx, EndOTy, 1200);			
			break;

		case 2:	
			//����[�򡡡�]�����
			if (Board[BeginOTy + 1][BeginOTx + 1] % 100 <= 9) 
			{
				getScope_OT_White(Line, Column, BeginOTx, BeginOTy, EndOTx, EndOTy, 5000);			
				break;
			}

			getScope_OT_White(Line, Column, BeginOTx, BeginOTy, EndOTx, EndOTy, 5000);			
			break;

		case 3:	
			//����[��򡡡�]�����
			if (Board[BeginOTy + 2][BeginOTx + 2] % 100 <= 9) 
			{
				getScope_OT_White(Line, Column, BeginOTx, BeginOTy, EndOTx, EndOTy, 28000);			
				break;
			}

			//����[�򡡡��]�����
			else if (Board[BeginOTy + 1][BeginOTx + 1] % 100 <= 9) 
			{
				getScope_OT_White(Line, Column, BeginOTx, BeginOTy, EndOTx, EndOTy, 28000);			
				break;
			}

			getScope_OT_White(Line, Column, BeginOTx, BeginOTy, EndOTx, EndOTy, 28000);			
			break;

		case 4:	
			//����[���򡡡�]�����
			if (Board[BeginOTy + 3][BeginOTx + 3] % 100 <= 9) 
			{
				getScope_OT_White(Line, Column, BeginOTx, BeginOTy, EndOTx, EndOTy, 5000000);			
				break;
			}

			//����[��򡡡��]�����
			else if (Board[BeginOTy + 2][BeginOTx + 2] % 100 <= 9) 
			{
				getScope_OT_White(Line, Column, BeginOTx, BeginOTy, EndOTx, EndOTy, 5000000);			
				break;
			}

			//����[�򡡡���]�����
			else if (Board[BeginOTy + 1][BeginOTx + 1] % 100 <= 9) 
			{
				getScope_OT_White(Line, Column, BeginOTx, BeginOTy, EndOTx, EndOTy, 5000000);			
				break;
			}

			getScope_OT_White(Line, Column, BeginOTx, BeginOTy, EndOTx, EndOTy, 5000000);			
			break;

		default:
			break;
		}
	}
}


//�������޴��
void Score_TF(int Line, int Column, int count, int Color) 
{
	if ((Color == BLACK_COLOR) || (Color == BLACK_COLOR + 1)) //ͳ�ƺ������ӣ����¶���
	{
		switch(count)	//��ֱ�׼
		{
		case 1:	
			getScope_TF_Black(Line, Column, BeginTFx, BeginTFy, EndTFx, EndTFy, 1000);
			break;

		case 2:	
			//����[�񡡡�]�����
			if (Board[BeginTFy - 1][BeginTFx + 1] % 100 <= 9) 
			{
				getScope_TF_Black(Line, Column, BeginTFx, BeginTFy, EndTFx, EndTFy, 2100);				
				break;
			}

			getScope_TF_Black(Line, Column, BeginTFx, BeginTFy, EndTFx, EndTFy, 2000);				
			break;

		case 3:	
			//����[��񡡡�]�����
			if (Board[BeginTFy - 2][BeginTFx + 2] % 100 <= 9) 
			{
				getScope_TF_Black(Line, Column, BeginTFx, BeginTFy, EndTFx, EndTFy, 20000);				
				break;
			}

			//����[�񡡡��]�����
			else if (Board[BeginTFy - 1][BeginTFx + 1] % 100 <= 9) 
			{
				getScope_TF_Black(Line, Column, BeginTFx, BeginTFy, EndTFx, EndTFy, 20000);				
				break;
			}

			getScope_TF_Black(Line, Column, BeginTFx, BeginTFy, EndTFx, EndTFy, 19000);				
			break;

		case 4:	
			//����[���񡡡�]�����
			if (Board[BeginTFy - 3][BeginTFx + 3] % 100 <= 9) 
			{
				getScope_TF_Black(Line, Column, BeginTFx, BeginTFy, EndTFx, EndTFy, 210000);				
				break;
			}

			//����[��񡡡��]�����
			else if (Board[BeginTFy - 2][BeginTFx + 2] % 100 <= 9) 
			{
				getScope_TF_Black(Line, Column, BeginTFx, BeginTFy, EndTFx, EndTFy, 210000);				
				break;
			}

			//����[�񡡡���]�����
			else if (Board[BeginTFy - 1][BeginTFx + 1] % 100 <= 9) 
			{
				getScope_TF_Black(Line, Column, BeginTFx, BeginTFy, EndTFx, EndTFy, 210000);				
				break;
			}

			getScope_TF_Black(Line, Column, BeginTFx, BeginTFy, EndTFx, EndTFy, 200000);				
			break;

		default:
			break;
		}
	}

	else //ͳ�ư������ӣ�����չ�Լ�
	{
		switch(count)	//��ֱ�׼
		{
		case 1:	
			getScope_TF_White(Line, Column, BeginTFx, BeginTFy, EndTFx, EndTFy, 1200);			
			break;

		case 2:	
			//����[�򡡡�]�����
			if (Board[BeginTFy - 1][BeginTFx + 1] % 100 <= 9) 
			{
				getScope_TF_White(Line, Column, BeginTFx, BeginTFy, EndTFx, EndTFy, 5000);			
				break;
			}

			getScope_TF_White(Line, Column, BeginTFx, BeginTFy, EndTFx, EndTFy, 5000);			
			break;

		case 3:	
			//����[��򡡡�]�����
			if (Board[BeginTFy - 2][BeginTFx + 2] % 100 <= 9) 
			{
				getScope_TF_White(Line, Column, BeginTFx, BeginTFy, EndTFx, EndTFy, 28000);			
				break;
			}

			//����[�򡡡��]�����
			else if (Board[BeginTFy - 1][BeginTFx + 1] % 100 <= 9) 
			{
				getScope_TF_White(Line, Column, BeginTFx, BeginTFy, EndTFx, EndTFy, 28000);			
				break;
			}

			getScope_TF_White(Line, Column, BeginTFx, BeginTFy, EndTFx, EndTFy, 28000);			
			break;

		case 4:	
			//����[���򡡡�]�����
			if (Board[BeginTFy - 3][BeginTFx + 3] % 100 <= 9) 
			{
				getScope_TF_White(Line, Column, BeginTFx, BeginTFy, EndTFx, EndTFy, 5000000);			
				break;
			}

			//����[��򡡡��]�����
			else if (Board[BeginTFy - 2][BeginTFx + 2] % 100 <= 9) 
			{
				getScope_TF_White(Line, Column, BeginTFx, BeginTFy, EndTFx, EndTFy, 5000000);			
				break;
			}

			//����[�򡡡���]�����
			else if (Board[BeginTFy - 1][BeginTFx + 1] % 100 <= 9) 
			{
				getScope_TF_White(Line, Column, BeginTFx, BeginTFy, EndTFx, EndTFy, 5000000);			
				break;
			}

			getScope_TF_White(Line, Column, BeginTFx, BeginTFy, EndTFx, EndTFy, 5000000);			
			break;

		default:
			break;
		}
	}
}


//����º����ֱ���
void getScope_H_Black(int Line, int BeginH, int EndH, int scope) 
{
	//���˶������Ӷ���
	if (((Board[Line][BeginH - 1] % 100 == WHITE_COLOR) || (Board[Line][BeginH - 1] % 100 == WHITE_COLOR + 1) || (BeginH == 0))
		&&
		((Board[Line][EndH] % 100 == WHITE_COLOR) || (Board[Line][EndH] % 100 == WHITE_COLOR + 1) || (EndH - 1 == BOARD_SIZE)))
	{
		//����[�񡡡�]�����
		if ((Board[Line][BeginH + 1] % 100 <= 9)
			&& ((Board[Line][BeginH + 2] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 2] % 100 == BLACK_COLOR + 1))
			&& (Board[Line][BeginH + 3] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 1] += scope*1;
		}

		//����[��񡡡�]�����
		else if (((Board[Line][BeginH + 1] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 1] % 100 == BLACK_COLOR + 1))
			&& (Board[Line][BeginH + 2] % 100 <= 9) 
			&& ((Board[Line][BeginH + 3] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 3] % 100 == BLACK_COLOR + 1))
			&& (Board[Line][BeginH + 4] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 2] += scope*1;
		}

		//����[�񡡡��]�����
		else if ((Board[Line][BeginH + 1] % 100 <= 9)
			&& ((Board[Line][BeginH + 2] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 2] % 100 == BLACK_COLOR + 1))
			&& ((Board[Line][BeginH + 3] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 3] % 100 == BLACK_COLOR + 1))
			&& (Board[Line][BeginH + 4] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 1] += scope*1;
		}

		//����[���񡡡�]�����
		else if (((Board[Line][BeginH + 1] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 1] % 100 == BLACK_COLOR + 1))
			&& ((Board[Line][BeginH + 2] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 2] % 100 == BLACK_COLOR + 1))
			&& (Board[Line][BeginH + 3] % 100 <= 9)
			&& ((Board[Line][BeginH + 4] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 4] % 100 == BLACK_COLOR + 1))
			&& (Board[Line][BeginH + 5] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 3] += scope*10;
		}

		//����[��񡡡��]�����
		else if (((Board[Line][BeginH + 1] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 1] % 100 == BLACK_COLOR + 1))
			&& (Board[Line][BeginH + 2] % 100 <= 9)
			&& ((Board[Line][BeginH + 3] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 3] % 100 == BLACK_COLOR + 1))
			&& ((Board[Line][BeginH + 4] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 4] % 100 == BLACK_COLOR + 1))
			&& (Board[Line][BeginH + 5] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 2] += scope*10;
		}

		//����[�񡡡���]�����
		else if ((Board[Line][BeginH + 1] % 100 <= 9)
			&& ((Board[Line][BeginH + 2] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 2] % 100 == BLACK_COLOR + 1))
			&& ((Board[Line][BeginH + 3] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 3] % 100 == BLACK_COLOR + 1))
			&& ((Board[Line][BeginH + 4] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 4] % 100 == BLACK_COLOR + 1))
			&& (Board[Line][BeginH + 5] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 1] += scope*10;
		}

		return;
	}


	//���˾��ް���(==����û���ӣ���Ϊֻ�а��ӡ����ӡ�������״̬�����к��ӣ����ͳ�����Ӵ����Ӹ���)
	else if ((Board[Line][BeginH - 1] % 100 <= 9) && (Board[Line][EndH] % 100 <= 9) && (0 < BeginH) && (EndH - 1 < BOARD_SIZE))
	{
		//����[�񡡡�]�����
		if ((Board[Line][BeginH + 1] % 100 <= 9)
			&& ((Board[Line][BeginH + 2] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 2] % 100 == BLACK_COLOR + 1))
			&& (Board[Line][BeginH + 3] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 1] += scope*4;
		}

		//����[��񡡡�]�����
		else if (((Board[Line][BeginH + 1] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 1] % 100 == BLACK_COLOR + 1))
			&& (Board[Line][BeginH + 2] % 100 <= 9)  
			&& ((Board[Line][BeginH + 3] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 3] % 100 == BLACK_COLOR + 1))
			&& (Board[Line][BeginH + 4] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 2] += scope*4;
		}

		//����[�񡡡��]�����
		else if ((Board[Line][BeginH + 1] % 100 <= 9)
			&& ((Board[Line][BeginH + 2] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 2] % 100 == BLACK_COLOR + 1))
			&& ((Board[Line][BeginH + 3] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 3] % 100 == BLACK_COLOR + 1))
			&& (Board[Line][BeginH + 4] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 1] += scope*4;
		}

		//����[���񡡡�]�����
		else if (((Board[Line][BeginH + 1] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 1] % 100 == BLACK_COLOR + 1))
			&& ((Board[Line][BeginH + 2] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 2] % 100 == BLACK_COLOR + 1))
			&& (Board[Line][BeginH + 3] % 100 <= 9)
			&& ((Board[Line][BeginH + 4] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 4] % 100 == BLACK_COLOR + 1))
			&& (Board[Line][BeginH + 5] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 3] += scope*10;
		}

		//����[��񡡡��]�����
		else if (((Board[Line][BeginH + 1] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 1] % 100 == BLACK_COLOR + 1))
			&& (Board[Line][BeginH + 2] % 100 <= 9)
			&& ((Board[Line][BeginH + 3] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 3] % 100 == BLACK_COLOR + 1))
			&& ((Board[Line][BeginH + 4] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 4] % 100 == BLACK_COLOR + 1))
			&& (Board[Line][BeginH + 5] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 2] += scope*10;
		}

		//����[�񡡡���]�����
		else if ((Board[Line][BeginH + 1] % 100 <= 9)
			&& ((Board[Line][BeginH + 2] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 2] % 100 == BLACK_COLOR + 1))
			&& ((Board[Line][BeginH + 3] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 3] % 100 == BLACK_COLOR + 1))
			&& ((Board[Line][BeginH + 4] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 4] % 100 == BLACK_COLOR + 1))
			&& (Board[Line][BeginH + 5] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 1] += scope*10;
		}


		//[Begin - 1]���£�[End + 1]δ���� 
		if (((Board[Line][BeginH - 2] == WHITE_COLOR) || (Board[Line][BeginH - 2] == WHITE_COLOR + 1) || (BeginH - 1 == 0))
			&& 
			((Board[Line][EndH + 1] != WHITE_COLOR) && (Board[Line][EndH + 1] != WHITE_COLOR + 1) && (EndH != BOARD_SIZE)))
		{
			Board[Line][BeginH - 1] += scope*1;
			Board[Line][EndH] += scope*3;
		}

		//[Begin - 1]δ���£�[End + 1]���� 
		else if (((Board[Line][BeginH - 2] != WHITE_COLOR) && (Board[Line][BeginH - 2] != WHITE_COLOR + 1) && (BeginH - 1 != 0))
			&&
			((Board[Line][EndH + 1] == WHITE_COLOR) || (Board[Line][EndH + 1] == WHITE_COLOR + 1) || (EndH == BOARD_SIZE)))
		{
			Board[Line][BeginH - 1] += scope*3;
			Board[Line][EndH] += scope*1;
		}

		//[Begin - 1]��[End + 1]������
		else if (((Board[Line][BeginH - 2] == WHITE_COLOR) || (Board[Line][BeginH - 2] == WHITE_COLOR + 1) || (BeginH - 1 == 0))
			&&
			((Board[Line][EndH + 1] == WHITE_COLOR) || (Board[Line][EndH + 1] == WHITE_COLOR + 1) || (EndH == BOARD_SIZE)))
		{
			Board[Line][BeginH - 1] += scope*1;
			Board[Line][EndH] += scope*1;
		}

		else
		{
			Board[Line][BeginH - 1] += scope*4;
			Board[Line][EndH] += scope*4;
		}
	}


	//begin�˱����Ӷ£�ͬʱ��end���ް��� 
	else if (((Board[Line][BeginH - 1] % 100 == WHITE_COLOR) || (Board[Line][BeginH - 1] % 100 == WHITE_COLOR + 1) || (BeginH == 0)) 
		&& 
		((Board[Line][EndH] % 100 <= 9) && (EndH - 1 < BOARD_SIZE))) 
	{
		//����[�񡡡�]�����
		if ((Board[Line][BeginH + 1] % 100 <= 9)
			&& ((Board[Line][BeginH + 2] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 2] % 100 == BLACK_COLOR + 1))
			&& (Board[Line][BeginH + 3] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 1] += scope*2;
		}

		//����[��񡡡�]�����
		else if (((Board[Line][BeginH + 1] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 1] % 100 == BLACK_COLOR + 1))
			&& (Board[Line][BeginH + 2] % 100 <= 9) 
			&& ((Board[Line][BeginH + 3] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 3] % 100 == BLACK_COLOR + 1))
			&& (Board[Line][BeginH + 4] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 2] += scope*2;
		}

		//����[�񡡡��]�����
		else if ((Board[Line][BeginH + 1] % 100 <= 9)
			&& ((Board[Line][BeginH + 2] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 2] % 100 == BLACK_COLOR + 1))
			&& ((Board[Line][BeginH + 3] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 3] % 100 == BLACK_COLOR + 1))
			&& (Board[Line][BeginH + 4] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 1] += scope*2;
		}

		//����[���񡡡�]�����
		else if (((Board[Line][BeginH + 1] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 1] % 100 == BLACK_COLOR + 1))
			&& ((Board[Line][BeginH + 2] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 2] % 100 == BLACK_COLOR + 1))
			&& (Board[Line][BeginH + 3] % 100 <= 9)
			&& ((Board[Line][BeginH + 4] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 4] % 100 == BLACK_COLOR + 1))
			&& (Board[Line][BeginH + 5] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 3] += scope*10;
		}

		//����[��񡡡��]�����
		else if (((Board[Line][BeginH + 1] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 1] % 100 == BLACK_COLOR + 1))
			&& (Board[Line][BeginH + 2] % 100 <= 9)
			&& ((Board[Line][BeginH + 3] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 3] % 100 == BLACK_COLOR + 1))
			&& ((Board[Line][BeginH + 4] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 4] % 100 == BLACK_COLOR + 1))
			&& (Board[Line][BeginH + 5] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 2] += scope*10;
		}

		//����[�񡡡���]�����
		else if ((Board[Line][BeginH + 1] % 100 <= 9)
			&& ((Board[Line][BeginH + 2] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 2] % 100 == BLACK_COLOR + 1))
			&& ((Board[Line][BeginH + 3] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 3] % 100 == BLACK_COLOR + 1))
			&& ((Board[Line][BeginH + 4] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 4] % 100 == BLACK_COLOR + 1))
			&& (Board[Line][BeginH + 5] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 1] += scope*10;
		}

		//[End + 1]������ 
		if ((Board[Line][EndH + 1] == WHITE_COLOR) || (Board[Line][EndH + 1] == WHITE_COLOR + 1) || (EndH == BOARD_SIZE))
		{
			Board[Line][EndH] += scope*1;
		}

		else
		{
			Board[Line][EndH] += scope*2;
		}
	}


	//begin���ް��ӣ�ͬʱ��end�˱����Ӷ� 
	else if (((Board[Line][BeginH - 1] % 100 <= 9) && (0 < BeginH))
		&& 
		((Board[Line][EndH] % 100 == WHITE_COLOR) || (Board[Line][EndH] % 100 == WHITE_COLOR + 1) || (EndH - 1 == BOARD_SIZE))) 
	{
		//����[�񡡡�]�����
		if ((Board[Line][BeginH + 1] % 100 <= 9)
			&& ((Board[Line][BeginH + 2] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 2] % 100 == BLACK_COLOR + 1))
			&& (Board[Line][BeginH + 3] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 1] += scope*2;
		}

		//����[��񡡡�]�����
		else if (((Board[Line][BeginH + 1] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 1] % 100 == BLACK_COLOR + 1))
			&& (Board[Line][BeginH + 2] % 100 <= 9) 
			&& ((Board[Line][BeginH + 3] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 3] % 100 == BLACK_COLOR + 1))
			&& (Board[Line][BeginH + 4] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 2] += scope*2;
		}

		//����[�񡡡��]�����
		else if ((Board[Line][BeginH + 1] % 100 <= 9)
			&& ((Board[Line][BeginH + 2] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 2] % 100 == BLACK_COLOR + 1))
			&& ((Board[Line][BeginH + 3] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 3] % 100 == BLACK_COLOR + 1))
			&& (Board[Line][BeginH + 4] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 1] += scope*2;
		}

		//����[���񡡡�]�����
		else if (((Board[Line][BeginH + 1] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 1] % 100 == BLACK_COLOR + 1))
			&& ((Board[Line][BeginH + 2] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 2] % 100 == BLACK_COLOR + 1))
			&& (Board[Line][BeginH + 3] % 100 <= 9)
			&& ((Board[Line][BeginH + 4] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 4] % 100 == BLACK_COLOR + 1))
			&& (Board[Line][BeginH + 5] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 3] += scope*10;
		}

		//����[��񡡡��]�����
		else if (((Board[Line][BeginH + 1] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 1] % 100 == BLACK_COLOR + 1))
			&& (Board[Line][BeginH + 2] % 100 <= 9)
			&& ((Board[Line][BeginH + 3] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 3] % 100 == BLACK_COLOR + 1))
			&& ((Board[Line][BeginH + 4] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 4] % 100 == BLACK_COLOR + 1))
			&& (Board[Line][BeginH + 5] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 2] += scope*10;
		}

		//����[�񡡡���]�����
		else if ((Board[Line][BeginH + 1] % 100 <= 9)
			&& ((Board[Line][BeginH + 2] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 2] % 100 == BLACK_COLOR + 1))
			&& ((Board[Line][BeginH + 3] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 3] % 100 == BLACK_COLOR + 1))
			&& ((Board[Line][BeginH + 4] % 100 == BLACK_COLOR) || (Board[Line][BeginH + 4] % 100 == BLACK_COLOR + 1))
			&& (Board[Line][BeginH + 5] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 1] += scope*10;
		}

		//////[Begin - 1]������ 
		if ((Board[Line][BeginH - 2] == WHITE_COLOR) || (Board[Line][BeginH - 2] == WHITE_COLOR + 1) || (BeginH - 1 == 0))
		{
			Board[Line][BeginH - 1] += scope*1;
		}

		else
		{
			Board[Line][BeginH - 1] += scope*2;
		}
	}
}


//����չ�����ֱ���
void getScope_H_White(int Line, int BeginH, int EndH, int scope) 
{
	//���˶������Ӷ���
	if (((Board[Line][BeginH - 1] % 100 == BLACK_COLOR) || (Board[Line][BeginH - 1] % 100 == BLACK_COLOR + 1) || (BeginH == 0))
		&& 
		((Board[Line][EndH] % 100 == BLACK_COLOR) || (Board[Line][EndH] % 100 == BLACK_COLOR + 1) || (EndH - 1 == BOARD_SIZE)))
	{
		//����[�򡡡�]�����
		if ((Board[Line][BeginH + 1] % 100 <= 9)
			&& ((Board[Line][BeginH + 2] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 2] % 100 == WHITE_COLOR + 1))
			&& (Board[Line][BeginH + 3] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 1] += scope*1;
		}

		//����[��򡡡�]�����
		else if (((Board[Line][BeginH + 1] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 1] % 100 == WHITE_COLOR + 1))
			&& (Board[Line][BeginH + 2] % 100 <= 9) 
			&& ((Board[Line][BeginH + 3] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 3] % 100 == WHITE_COLOR + 1))
			&& (Board[Line][BeginH + 4] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 2] += scope*1;
		}

		//����[�򡡡��]�����
		else if ((Board[Line][BeginH + 1] % 100 <= 9)
			&& ((Board[Line][BeginH + 2] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 2] % 100 == WHITE_COLOR + 1))
			&& ((Board[Line][BeginH + 3] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 3] % 100 == WHITE_COLOR + 1))
			&& (Board[Line][BeginH + 4] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 1] += scope*1;
		}

		//����[���򡡡�]�����
		else if (((Board[Line][BeginH + 1] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 1] % 100 == WHITE_COLOR + 1))
			&& ((Board[Line][BeginH + 2] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 2] % 100 == WHITE_COLOR + 1))
			&& (Board[Line][BeginH + 3] % 100 <= 9)
			&& ((Board[Line][BeginH + 4] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 4] % 100 == WHITE_COLOR + 1))
			&& (Board[Line][BeginH + 5] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 3] += scope*10;
		}

		//����[��򡡡��]�����
		else if (((Board[Line][BeginH + 1] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 1] % 100 == WHITE_COLOR + 1))
			&&(Board[Line][BeginH + 2] % 100 <= 9)
			&& ((Board[Line][BeginH + 3] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 3] % 100 == WHITE_COLOR + 1))
			&& ((Board[Line][BeginH + 4] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 4] % 100 == WHITE_COLOR + 1))
			&& (Board[Line][BeginH + 5] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 2] += scope*10;
		}

		//����[�򡡡���]�����
		else if ((Board[Line][BeginH + 1] % 100 <= 9)
			&& ((Board[Line][BeginH + 2] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 2] % 100 == WHITE_COLOR + 1))
			&& ((Board[Line][BeginH + 3] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 3] % 100 == WHITE_COLOR + 1))
			&& ((Board[Line][BeginH + 4] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 4] % 100 == WHITE_COLOR + 1))
			&& (Board[Line][BeginH + 5] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 1] += scope*10;
		}

		return;
	}


	//���˾��޺���
	else if ((Board[Line][BeginH - 1] % 100 <= 9) && (Board[Line][EndH] % 100 <= 9) && (0 < BeginH) && (EndH - 1 < BOARD_SIZE))
	{
		//����[�򡡡�]�����
		if ((Board[Line][BeginH + 1] % 100 <= 9)
			&& ((Board[Line][BeginH + 2] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 2] % 100 == WHITE_COLOR + 1))
			&& (Board[Line][BeginH + 3] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 1] += scope*4;
		}

		//����[��򡡡�]�����
		else if (((Board[Line][BeginH + 1] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 1] % 100 == WHITE_COLOR + 1))
			&& (Board[Line][BeginH + 2] % 100 <= 9)  
			&& ((Board[Line][BeginH + 3] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 3] % 100 == WHITE_COLOR + 1))
			&& (Board[Line][BeginH + 4] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 2] += scope*4;
		}

		//����[�򡡡��]�����
		else if ((Board[Line][BeginH + 1] % 100 <= 9)
			&& ((Board[Line][BeginH + 2] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 2] % 100 == WHITE_COLOR + 1))
			&& ((Board[Line][BeginH + 3] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 3] % 100 == WHITE_COLOR + 1))
			&& (Board[Line][BeginH + 4] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 1] += scope*4;
		}

		//����[���򡡡�]�����
		else if (((Board[Line][BeginH + 1] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 1] % 100 == WHITE_COLOR + 1))
			&& ((Board[Line][BeginH + 2] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 2] % 100 == WHITE_COLOR + 1))
			&& (Board[Line][BeginH + 3] % 100 <= 9)
			&& ((Board[Line][BeginH + 4] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 4] % 100 == WHITE_COLOR + 1))
			&& (Board[Line][BeginH + 5] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 3] += scope*10;
		}

		//����[��򡡡��]�����
		else if (((Board[Line][BeginH + 1] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 1] % 100 == WHITE_COLOR + 1))
			&& (Board[Line][BeginH + 2] % 100 <= 9)
			&& ((Board[Line][BeginH + 3] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 3] % 100 == WHITE_COLOR + 1))
			&& ((Board[Line][BeginH + 4] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 4] % 100 == WHITE_COLOR + 1))
			&& (Board[Line][BeginH + 5] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 2] += scope*10;
		}

		//����[�򡡡���]�����
		else if ((Board[Line][BeginH + 1] % 100 <= 9)
			&& ((Board[Line][BeginH + 2] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 2] % 100 == WHITE_COLOR + 1))
			&& ((Board[Line][BeginH + 3] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 3] % 100 == WHITE_COLOR + 1))
			&& ((Board[Line][BeginH + 4] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 4] % 100 == WHITE_COLOR + 1))
			&& (Board[Line][BeginH + 5] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 1] += scope*10;
		}


		//[Begin - 1]���£�[End + 1]δ���� 
		if (((Board[Line][BeginH - 2] == BLACK_COLOR) || (Board[Line][BeginH - 2] == BLACK_COLOR + 1) || (BeginH - 1 == 0))
			&& 
			((Board[Line][EndH + 1] != BLACK_COLOR) && (Board[Line][EndH + 1] != BLACK_COLOR + 1) && (EndH != BOARD_SIZE)))
		{
			Board[Line][BeginH - 1] += scope*1;
			Board[Line][EndH] += scope*3;
		}

		//[Begin - 1]δ���£�[End + 1]���� 
		else if (((Board[Line][BeginH - 2] != BLACK_COLOR) && (Board[Line][BeginH - 2] != BLACK_COLOR + 1) && (BeginH - 1 != 0))
			&&
			((Board[Line][EndH + 1] == BLACK_COLOR) || (Board[Line][EndH + 1] == BLACK_COLOR + 1) || (EndH == BOARD_SIZE)))
		{
			Board[Line][BeginH - 1] += scope*3;
			Board[Line][EndH] += scope*1;
		}

		//[Begin - 1]��[End + 1]������
		else if (((Board[Line][BeginH - 2] == BLACK_COLOR) || (Board[Line][BeginH - 2] == BLACK_COLOR + 1) || (BeginH - 1 == 0))
			&&
			((Board[Line][EndH + 1] == BLACK_COLOR) || (Board[Line][EndH + 1] == BLACK_COLOR + 1) || (EndH == BOARD_SIZE)))
		{
			Board[Line][BeginH - 1] += scope*1;
			Board[Line][EndH] += scope*1;
		}

		else
		{
			Board[Line][BeginH - 1] += scope*4;
			Board[Line][EndH] += scope*4;
		}
	}


	//begin�˱����Ӷ£�ͬʱ��end���޺��� 
	else if (((Board[Line][BeginH - 1] % 100 == BLACK_COLOR) || (Board[Line][BeginH - 1] % 100 == BLACK_COLOR + 1) || (BeginH == 0))
		&& 
		((Board[Line][EndH] % 100 <= 9) && (EndH - 1 < BOARD_SIZE))) 
	{
		//����[�򡡡�]�����
		if ((Board[Line][BeginH + 1] % 100 <= 9)
			&& ((Board[Line][BeginH + 2] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 2] % 100 == WHITE_COLOR + 1))
			&& (Board[Line][BeginH + 3] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 1] += scope*2;
		}

		//����[��򡡡�]�����
		else if (((Board[Line][BeginH + 1] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 1] % 100 == WHITE_COLOR + 1))
			&& (Board[Line][BeginH + 2] % 100 <= 9) 
			&& ((Board[Line][BeginH + 3] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 3] % 100 == WHITE_COLOR + 1))
			&& (Board[Line][BeginH + 4] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 2] += scope*2;
		}

		//����[�򡡡��]�����
		else if ((Board[Line][BeginH + 1] % 100 <= 9)
			&& ((Board[Line][BeginH + 2] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 2] % 100 == WHITE_COLOR + 1))
			&& ((Board[Line][BeginH + 3] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 3] % 100 == WHITE_COLOR + 1))
			&& (Board[Line][BeginH + 4] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 1] += scope*2;
		}

		//����[���򡡡�]�����
		else if (((Board[Line][BeginH + 1] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 1] % 100 == WHITE_COLOR + 1))
			&& ((Board[Line][BeginH + 2] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 2] % 100 == WHITE_COLOR + 1))
			&& (Board[Line][BeginH + 3] % 100 <= 9)
			&& ((Board[Line][BeginH + 4] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 4] % 100 == WHITE_COLOR + 1))
			&& (Board[Line][BeginH + 5] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 3] += scope*10;
		}

		//����[��򡡡��]�����
		else if (((Board[Line][BeginH + 1] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 1] % 100 == WHITE_COLOR + 1))
			&& (Board[Line][BeginH + 2] % 100 <= 9)
			&& ((Board[Line][BeginH + 3] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 3] % 100 == WHITE_COLOR + 1))
			&& ((Board[Line][BeginH + 4] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 4] % 100 == WHITE_COLOR + 1))
			&& (Board[Line][BeginH + 5] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 2] += scope*10;
		}

		//����[�򡡡���]�����
		else if ((Board[Line][BeginH + 1] % 100 <= 9)
			&& ((Board[Line][BeginH + 2] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 2] % 100 == WHITE_COLOR + 1))
			&& ((Board[Line][BeginH + 3] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 3] % 100 == WHITE_COLOR + 1))
			&& ((Board[Line][BeginH + 4] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 4] % 100 == WHITE_COLOR + 1))
			&& (Board[Line][BeginH + 5] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 1] += scope*10;
		}

		//[End + 1]������ 
		if ((Board[Line][EndH + 1] == BLACK_COLOR) || (Board[Line][EndH + 1] == BLACK_COLOR + 1) || (EndH == BOARD_SIZE))
		{
			Board[Line][EndH] += scope*1;
		}

		else
		{
			Board[Line][EndH] += scope*2;
		}
	}


	//begin���޺��ӣ�ͬʱ��end�˱����Ӷ� 
	else if (((Board[Line][BeginH - 1] % 100 <= 9) && (0 < BeginH))
		&& 
		((Board[Line][EndH] % 100 == BLACK_COLOR) || (Board[Line][EndH] % 100 == BLACK_COLOR + 1) || (EndH - 1 == BOARD_SIZE))) 
	{
		//����[�򡡡�]�����
		if ((Board[Line][BeginH + 1] % 100 <= 9)
			&& ((Board[Line][BeginH + 2] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 2] % 100 == WHITE_COLOR + 1))
			&& (Board[Line][BeginH + 3] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 1] += scope*2;
		}

		//����[��򡡡�]�����
		else if (((Board[Line][BeginH + 1] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 1] % 100 == WHITE_COLOR + 1))
			&& (Board[Line][BeginH + 2] % 100 <= 9) 
			&& ((Board[Line][BeginH + 3] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 3] % 100 == WHITE_COLOR + 1))
			&& (Board[Line][BeginH + 4] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 2] += scope*2;
		}

		//����[�򡡡��]�����
		else if ((Board[Line][BeginH + 1] % 100 <= 9)
			&& ((Board[Line][BeginH + 2] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 2] % 100 == WHITE_COLOR + 1))
			&& ((Board[Line][BeginH + 3] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 3] % 100 == WHITE_COLOR + 1))
			&& (Board[Line][BeginH + 4] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 1] += scope*2;
		}

		//����[���򡡡�]�����
		else if (((Board[Line][BeginH + 1] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 1] % 100 == WHITE_COLOR + 1))
			&& ((Board[Line][BeginH + 2] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 2] % 100 == WHITE_COLOR + 1)) 
			&& (Board[Line][BeginH + 3] % 100 <= 9)
			&& ((Board[Line][BeginH + 4] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 4] % 100 == WHITE_COLOR + 1))
			&& (Board[Line][BeginH + 5] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 3] += scope*10;
		}

		//����[��򡡡��]�����
		else if (((Board[Line][BeginH + 1] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 1] % 100 == WHITE_COLOR + 1))
			&& (Board[Line][BeginH + 2] % 100 <= 9)
			&& ((Board[Line][BeginH + 3] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 3] % 100 == WHITE_COLOR + 1))
			&& ((Board[Line][BeginH + 4] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 4] % 100 == WHITE_COLOR + 1))
			&& (Board[Line][BeginH + 5] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 2] += scope*10;
		}

		//����[�򡡡���]�����
		else if ((Board[Line][BeginH + 1] % 100 <= 9)
			&& ((Board[Line][BeginH + 2] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 2] % 100 == WHITE_COLOR + 1))
			&& ((Board[Line][BeginH + 3] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 3] % 100 == WHITE_COLOR + 1))
			&& ((Board[Line][BeginH + 4] % 100 == WHITE_COLOR) || (Board[Line][BeginH + 4] % 100 == WHITE_COLOR + 1))
			&& (Board[Line][BeginH + 5] % 100 == Board[Line][EndH] % 100))
		{
			Board[Line][BeginH + 1] += scope*10;
		}

		//////[Begin - 1]������ 
		if ((Board[Line][BeginH - 2] == BLACK_COLOR) || (Board[Line][BeginH - 2] == BLACK_COLOR + 1) || (BeginH - 1 == 0))
		{
			Board[Line][BeginH - 1] += scope*1;
		}

		else
		{
			Board[Line][BeginH - 1] += scope*2;
		}
	}
}


//����º����ֱ���
void getScope_V_Black(int Column, int BeginV, int EndV, int scope) 
{
	//���˶������Ӷ���
	if (((Board[BeginV - 1][Column] % 100 == WHITE_COLOR) || (Board[BeginV - 1][Column] % 100 == WHITE_COLOR + 1) || (BeginV == 0))
		&&
		((Board[EndV][Column] % 100 == WHITE_COLOR) || (Board[EndV][Column] % 100 == WHITE_COLOR + 1) || (EndV - 1 == BOARD_SIZE)))
	{
		//����[�񡡡�]�����
		if ((Board[BeginV + 1][Column] % 100 <= 9)
			&& ((Board[BeginV + 2][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 2][Column] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginV + 3][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 1][Column] += scope*1;
		}

		//����[��񡡡�]�����
		else if (((Board[BeginV + 1][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 1][Column] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginV + 2][Column] % 100 <= 9) 
			&& ((Board[BeginV + 3][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 3][Column] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginV + 4][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 2][Column] += scope*1;
		}

		//����[�񡡡��]�����
		else if ((Board[BeginV + 1][Column] % 100 <= 9)
			&& ((Board[BeginV + 2][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 2][Column] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginV + 3][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 3][Column] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginV + 4][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 1][Column] += scope*1;
		}

		//����[���񡡡�]�����
		else if (((Board[BeginV + 1][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 1][Column] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginV + 2][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 2][Column] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginV + 3][Column] % 100 <= 9)
			&& ((Board[BeginV + 4][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 4][Column] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginV + 5][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 3][Column] += scope*10;
		}

		//����[��񡡡��]�����
		else if (((Board[BeginV + 1][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 1][Column] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginV + 2][Column] % 100 <= 9)
			&& ((Board[BeginV + 3][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 3][Column] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginV + 4][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 4][Column] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginV + 5][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 2][Column] += scope*10;
		}

		//����[�񡡡���]�����
		else if ((Board[BeginV + 1][Column] % 100 <= 9)
			&& ((Board[BeginV + 2][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 2][Column] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginV + 3][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 3][Column] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginV + 4][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 4][Column] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginV + 5][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 1][Column] += scope*10;
		}

		return;
	}


	//���˾��ް���(==����û���ӣ���Ϊֻ�а��ӡ����ӡ�������״̬�����к��ӣ����ͳ�����Ӵ����Ӹ���)
	else if ((Board[BeginV - 1][Column] % 100 <= 9) && (Board[EndV][Column] % 100 <= 9) && (0 < BeginV) && (EndV - 1 < BOARD_SIZE))
	{
		//����[�񡡡�]�����
		if ((Board[BeginV + 1][Column] % 100 <= 9)
			&& ((Board[BeginV + 2][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 2][Column] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginV + 3][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 1][Column] += scope*4;
		}

		//����[��񡡡�]�����
		else if (((Board[BeginV + 1][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 1][Column] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginV + 2][Column] % 100 <= 9)  
			&& ((Board[BeginV + 3][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 3][Column] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginV + 4][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 2][Column] += scope*4;
		}

		//����[�񡡡��]�����
		else if ((Board[BeginV + 1][Column] % 100 <= 9)
			&& ((Board[BeginV + 2][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 2][Column] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginV + 3][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 3][Column] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginV + 4][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 1][Column] += scope*4;
		}

		//����[���񡡡�]�����
		else if (((Board[BeginV + 1][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 1][Column] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginV + 2][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 2][Column] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginV + 3][Column] % 100 <= 9)
			&& ((Board[BeginV + 4][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 4][Column] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginV + 5][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 3][Column] += scope*10;
		}

		//����[��񡡡��]�����
		else if (((Board[BeginV + 1][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 1][Column] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginV + 2][Column] % 100 <= 9)
			&& ((Board[BeginV + 3][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 3][Column] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginV + 4][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 4][Column] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginV + 5][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 2][Column] += scope*10;
		}

		//����[�񡡡���]�����
		else if ((Board[BeginV + 1][Column] % 100 <= 9)
			&& ((Board[BeginV + 2][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 2][Column] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginV + 3][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 3][Column] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginV + 4][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 4][Column] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginV + 5][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 1][Column] += scope*10;
		}


		//[Begin - 1]���£�[End + 1]δ���� 
		if (((Board[BeginV - 2][Column] == WHITE_COLOR) || (Board[BeginV - 2][Column] == WHITE_COLOR + 1) || (BeginV - 1 == 0))
			&& 
			((Board[EndV + 1][Column] != WHITE_COLOR) && (Board[EndV + 1][Column] != WHITE_COLOR + 1) && (EndV != BOARD_SIZE)))
		{
			Board[BeginV - 1][Column] += scope*1;
			Board[EndV][Column] += scope*3;
		}


		//[Begin - 1]δ���£�[End + 1]���� 
		else if (((Board[BeginV - 2][Column] != WHITE_COLOR) && (Board[BeginV - 2][Column] != WHITE_COLOR + 1) && (BeginV - 1 != 0))
			&&
			((Board[EndV + 1][Column] == WHITE_COLOR) || (Board[EndV + 1][Column] == WHITE_COLOR + 1) || (EndV == BOARD_SIZE)))
		{
			Board[BeginV - 1][Column] += scope*3;
			Board[EndV][Column] += scope*1;
		}

		//[Begin - 1]��[End + 1]������
		else if (((Board[BeginV - 2][Column] == WHITE_COLOR) || (Board[BeginV - 2][Column] == WHITE_COLOR + 1) || (BeginV - 1 == 0))
			&&
			((Board[EndV + 1][Column] == WHITE_COLOR) || (Board[EndV + 1][Column] == WHITE_COLOR + 1) || (EndV == BOARD_SIZE)))
		{
			Board[BeginV - 1][Column] += scope*1;
			Board[EndV][Column] += scope*1;
		}

		else
		{
			Board[BeginV - 1][Column] += scope*4;
			Board[EndV][Column] += scope*4;
		}
	}


	//begin�˱����Ӷ£�ͬʱ��end���ް��� 
	else if (((Board[BeginV - 1][Column] % 100 == WHITE_COLOR) || (Board[BeginV - 1][Column] % 100 == WHITE_COLOR + 1) || (BeginV == 0)) 
		&& 
		((Board[EndV][Column] % 100 <= 9) && (EndV - 1 < BOARD_SIZE))) 
	{
		//����[�񡡡�]�����
		if ((Board[BeginV + 1][Column] % 100 <= 9)
			&& ((Board[BeginV + 2][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 2][Column] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginV + 3][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 1][Column] += scope*2;
		}

		//����[��񡡡�]�����
		else if (((Board[BeginV + 1][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 1][Column] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginV + 2][Column] % 100 <= 9) 
			&& ((Board[BeginV + 3][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 3][Column] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginV + 4][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 2][Column] += scope*2;
		}

		//����[�񡡡��]�����
		else if ((Board[BeginV + 1][Column] % 100 <= 9)
			&& ((Board[BeginV + 2][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 2][Column] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginV + 3][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 3][Column] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginV + 4][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 1][Column] += scope*2;
		}

		//����[���񡡡�]�����
		else if (((Board[BeginV + 1][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 1][Column] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginV + 2][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 2][Column] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginV + 3][Column] % 100 <= 9)
			&& ((Board[BeginV + 4][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 4][Column] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginV + 5][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 3][Column] += scope*10;
		}

		//����[��񡡡��]�����
		else if (((Board[BeginV + 1][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 1][Column] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginV + 2][Column] % 100 <= 9)
			&& ((Board[BeginV + 3][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 3][Column] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginV + 4][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 4][Column] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginV + 5][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 2][Column] += scope*10;
		}

		//����[�񡡡���]�����
		else if ((Board[BeginV + 1][Column] % 100 <= 9)
			&& ((Board[BeginV + 2][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 2][Column] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginV + 3][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 3][Column] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginV + 4][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 4][Column] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginV + 5][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 1][Column] += scope*10;
		}


		//[End + 1]������ 
		if ((Board[EndV + 1][Column] == WHITE_COLOR) || (Board[EndV + 1][Column] == WHITE_COLOR + 1) || (EndV == BOARD_SIZE))
		{
			Board[EndV][Column] += scope*1;
		}

		else
		{
			Board[EndV][Column] += scope*2;
		}
	}


	//begin���ް��ӣ�ͬʱ��end�˱����Ӷ� 
	else if (((Board[BeginV - 1][Column] % 100 <= 9) && (0 < BeginV))
		&& 
		((Board[EndV][Column] % 100 == WHITE_COLOR) || (Board[EndV][Column] % 100 == WHITE_COLOR + 1) || (EndV - 1 == BOARD_SIZE))) 
	{
		//����[�񡡡�]�����
		if ((Board[BeginV + 1][Column] % 100 <= 9)
			&& ((Board[BeginV + 2][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 2][Column] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginV + 3][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 1][Column] += scope*2;
		}

		//����[��񡡡�]�����
		else if (((Board[BeginV + 1][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 1][Column] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginV + 2][Column] % 100 <= 9) 
			&& ((Board[BeginV + 3][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 3][Column] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginV + 4][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 2][Column] += scope*2;
		}

		//����[�񡡡��]�����
		else if ((Board[BeginV + 1][Column] % 100 <= 9)
			&& ((Board[BeginV + 2][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 2][Column] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginV + 3][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 3][Column] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginV + 4][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 1][Column] += scope*2;
		}

		//����[���񡡡�]�����
		else if (((Board[BeginV + 1][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 1][Column] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginV + 2][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 2][Column] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginV + 3][Column] % 100 <= 9)
			&& ((Board[BeginV + 4][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 4][Column] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginV + 5][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 3][Column] += scope*10;
		}

		//����[��񡡡��]�����
		else if (((Board[BeginV + 1][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 1][Column] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginV + 2][Column] % 100 <= 9)
			&& ((Board[BeginV + 3][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 3][Column] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginV + 4][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 4][Column] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginV + 5][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 2][Column] += scope*10;
		}

		//����[�񡡡���]�����
		else if ((Board[BeginV + 1][Column] % 100 <= 9)
			&& ((Board[BeginV + 2][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 2][Column] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginV + 3][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 3][Column] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginV + 4][Column] % 100 == BLACK_COLOR) || (Board[BeginV + 4][Column] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginV + 5][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 1][Column] += scope*10;
		}

		//////[Begin - 1]������ 
		if ((Board[BeginV - 2][Column] == WHITE_COLOR) || (Board[BeginV - 2][Column] == WHITE_COLOR + 1) || (BeginV - 1 == 0))
		{
			Board[BeginV - 1][Column] += scope*1;
		}

		else
		{
			Board[BeginV - 1][Column] += scope*2;
		}
	}
}


//����չ�����ֱ���
void getScope_V_White(int Column, int BeginV, int EndV, int scope) 
{
	//���˶������Ӷ���
	if (((Board[BeginV - 1][Column] % 100 == BLACK_COLOR) || (Board[BeginV - 1][Column] % 100 == BLACK_COLOR + 1) || (BeginV == 0))
		&& 
		((Board[EndV][Column] % 100 == BLACK_COLOR) || (Board[EndV][Column] % 100 == BLACK_COLOR + 1) || (EndV - 1 == BOARD_SIZE)))
	{
		//����[�򡡡�]�����
		if ((Board[BeginV + 1][Column] % 100 <= 9)
			&& ((Board[BeginV + 2][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 2][Column] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginV + 3][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 1][Column] += scope*1;
		}

		//����[��򡡡�]�����
		else if (((Board[BeginV + 1][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 1][Column] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginV + 2][Column] % 100 <= 9) 
			&& ((Board[BeginV + 3][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 3][Column] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginV + 4][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 2][Column] += scope*1;
		}

		//����[�򡡡��]�����
		else if ((Board[BeginV + 1][Column] % 100 <= 9)
			&& ((Board[BeginV + 2][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 2][Column] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginV + 3][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 3][Column] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginV + 4][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 1][Column] += scope*1;
		}

		//����[���򡡡�]�����
		else if (((Board[BeginV + 1][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 1][Column] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginV + 2][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 2][Column] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginV + 3][Column] % 100 <= 9)
			&& ((Board[BeginV + 4][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 4][Column] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginV + 5][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 3][Column] += scope*10;
		}

		//����[��򡡡��]�����
		else if (((Board[BeginV + 1][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 1][Column] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginV + 2][Column] % 100 <= 9)
			&& ((Board[BeginV + 3][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 3][Column] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginV + 4][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 4][Column] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginV + 5][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 2][Column] += scope*10;
		}

		//����[�򡡡���]�����
		else if ((Board[BeginV + 1][Column] % 100 <= 9)
			&& ((Board[BeginV + 2][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 2][Column] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginV + 3][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 3][Column] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginV + 4][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 4][Column] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginV + 5][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 1][Column] += scope*10;
		}

		return;
	}


	//���˾��޺���
	else if ((Board[BeginV - 1][Column] % 100 <= 9) && (Board[EndV][Column] % 100 <= 9) && (0 < BeginV) && (EndV - 1 < BOARD_SIZE))
	{
		//����[�򡡡�]�����
		if ((Board[BeginV + 1][Column] % 100 <= 9)
			&& ((Board[BeginV + 2][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 2][Column] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginV + 3][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 1][Column] += scope*4;
		}

		//����[��򡡡�]�����
		else if (((Board[BeginV + 1][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 1][Column] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginV + 2][Column] % 100 <= 9)  
			&& ((Board[BeginV + 3][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 3][Column] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginV + 4][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 2][Column] += scope*4;
		}

		//����[�򡡡��]�����
		else if ((Board[BeginV + 1][Column] % 100 <= 9)
			&& ((Board[BeginV + 2][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 2][Column] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginV + 3][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 3][Column] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginV + 4][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 1][Column] += scope*4;
		}

		//����[���򡡡�]�����
		else if (((Board[BeginV + 1][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 1][Column] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginV + 2][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 2][Column] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginV + 3][Column] % 100 <= 9)
			&& ((Board[BeginV + 4][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 4][Column] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginV + 5][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 3][Column] += scope*10;
		}

		//����[��򡡡��]�����
		else if (((Board[BeginV + 1][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 1][Column] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginV + 2][Column] % 100 <= 9)
			&& ((Board[BeginV + 3][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 3][Column] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginV + 4][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 4][Column] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginV + 5][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 2][Column] += scope*10;
		}

		//����[�򡡡���]�����
		else if ((Board[BeginV + 1][Column] % 100 <= 9)
			&& ((Board[BeginV + 2][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 2][Column] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginV + 3][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 3][Column] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginV + 4][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 4][Column] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginV + 5][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 1][Column] += scope*10;
		}


		//[Begin - 1]���£�[End + 1]δ���� 
		if (((Board[BeginV - 2][Column] == BLACK_COLOR) || (Board[BeginV - 2][Column] == BLACK_COLOR + 1) || (BeginV - 1 == 0))
			&& 
			((Board[EndV + 1][Column] != BLACK_COLOR) && (Board[EndV + 1][Column] != BLACK_COLOR + 1) && (EndV != BOARD_SIZE)))
		{
			Board[BeginV - 1][Column] += scope*1;
			Board[EndV][Column] += scope*3;
		}


		//[Begin - 1]δ���£�[End + 1]���� 
		else if (((Board[BeginV - 2][Column] != BLACK_COLOR) && (Board[BeginV - 2][Column] != BLACK_COLOR + 1) && (BeginV - 1 != 0))
			&&
			((Board[EndV + 1][Column] == BLACK_COLOR) || (Board[EndV + 1][Column] == BLACK_COLOR + 1) || (EndV == BOARD_SIZE)))
		{
			Board[BeginV - 1][Column] += scope*3;
			Board[EndV][Column] += scope*1;
		}

		//[Begin - 1]��[End + 1]������
		else if (((Board[BeginV - 2][Column] == BLACK_COLOR) || (Board[BeginV - 2][Column] == BLACK_COLOR + 1) || (BeginV - 1 == 0))
			&&
			((Board[EndV + 1][Column] == BLACK_COLOR) || (Board[EndV + 1][Column] == BLACK_COLOR + 1) || (EndV == BOARD_SIZE)))
		{
			Board[BeginV - 1][Column] += scope*1;
			Board[EndV][Column] += scope*1;
		}

		else
		{
			Board[BeginV - 1][Column] += scope*4;
			Board[EndV][Column] += scope*4;
		}
	}


	//begin�˱����Ӷ£�ͬʱ��end���޺��� 
	else if (((Board[BeginV - 1][Column] % 100 == BLACK_COLOR) || (Board[BeginV - 1][Column] % 100 == BLACK_COLOR + 1) || (BeginV == 0)) 
		&& 
		((Board[EndV][Column] % 100 <= 9) && (EndV - 1 < BOARD_SIZE))) 
	{
		//����[�򡡡�]�����
		if ((Board[BeginV + 1][Column] % 100 <= 9)
			&& ((Board[BeginV + 2][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 2][Column] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginV + 3][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 1][Column] += scope*2;
		}

		//����[��򡡡�]�����
		else if (((Board[BeginV + 1][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 1][Column] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginV + 2][Column] % 100 <= 9) 
			&& ((Board[BeginV + 3][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 3][Column] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginV + 4][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 2][Column] += scope*2;
		}

		//����[�򡡡��]�����
		else if ((Board[BeginV + 1][Column] % 100 <= 9)
			&& ((Board[BeginV + 2][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 2][Column] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginV + 3][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 3][Column] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginV + 4][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 1][Column] += scope*2;
		}

		//����[���򡡡�]�����
		else if (((Board[BeginV + 1][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 1][Column] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginV + 2][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 2][Column] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginV + 3][Column] % 100 <= 9)
			&& ((Board[BeginV + 4][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 4][Column] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginV + 5][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 3][Column] += scope*10;
		}

		//����[��򡡡��]�����
		else if (((Board[BeginV + 1][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 1][Column] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginV + 2][Column] % 100 <= 9)
			&& ((Board[BeginV + 3][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 3][Column] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginV + 4][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 4][Column] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginV + 5][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 2][Column] += scope*10;
		}

		//����[�򡡡���]�����
		else if ((Board[BeginV + 1][Column] % 100 <= 9)
			&& ((Board[BeginV + 2][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 2][Column] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginV + 3][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 3][Column] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginV + 4][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 4][Column] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginV + 5][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 1][Column] += scope*10;
		}


		//[End + 1]������ 
		if ((Board[EndV + 1][Column] == BLACK_COLOR) || (Board[EndV + 1][Column] == BLACK_COLOR + 1) || (EndV == BOARD_SIZE))
		{
			Board[EndV][Column] += scope*1;
		}

		else
		{
			Board[EndV][Column] += scope*2;
		}
	}


	//begin���޺��ӣ�ͬʱ��end�˱����Ӷ� 
	else if (((Board[BeginV - 1][Column] % 100 <= 9) && (0 < BeginV)) 
		&& 
		((Board[EndV][Column] % 100 == BLACK_COLOR) || (Board[EndV][Column] % 100 == BLACK_COLOR + 1) || (EndV - 1 == BOARD_SIZE))) 
	{
		//����[�򡡡�]�����
		if ((Board[BeginV + 1][Column] % 100 <= 9)
			&& ((Board[BeginV + 2][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 2][Column] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginV + 3][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 1][Column] += scope*2;
		}

		//����[��򡡡�]�����
		else if (((Board[BeginV + 1][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 1][Column] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginV + 2][Column] % 100 <= 9) 
			&& ((Board[BeginV + 3][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 3][Column] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginV + 4][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 2][Column] += scope*2;
		}

		//����[�򡡡��]�����
		else if ((Board[BeginV + 1][Column] % 100 <= 9)
			&& ((Board[BeginV + 2][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 2][Column] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginV + 3][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 3][Column] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginV + 4][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 1][Column] += scope*2;
		}

		//����[���򡡡�]�����
		else if (((Board[BeginV + 1][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 1][Column] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginV + 2][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 2][Column] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginV + 3][Column] % 100 <= 9)
			&& ((Board[BeginV + 4][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 4][Column] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginV + 5][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 3][Column] += scope*10;
		}

		//����[��򡡡��]�����
		else if (((Board[BeginV + 1][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 1][Column] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginV + 2][Column] % 100 <= 9)
			&& ((Board[BeginV + 3][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 3][Column] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginV + 4][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 4][Column] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginV + 5][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 2][Column] += scope*10;
		}

		//����[�򡡡���]�����
		else if ((Board[BeginV + 1][Column] % 100 <= 9)
			&& ((Board[BeginV + 2][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 2][Column] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginV + 3][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 3][Column] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginV + 4][Column] % 100 == WHITE_COLOR) || (Board[BeginV + 4][Column] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginV + 5][Column] % 100 == Board[EndV][Column] % 100))
		{
			Board[BeginV + 1][Column] += scope*10;
		}


		//////[Begin - 1]������ 
		if ((Board[BeginV - 2][Column] == BLACK_COLOR) || (Board[BeginV - 2][Column] == BLACK_COLOR + 1) || (BeginV - 1 == 0))
		{
			Board[BeginV - 1][Column] += scope*1;
		}

		else
		{
			Board[BeginV - 1][Column] += scope*2;
		}
	}
}


//һ�����޶º����ֱ���
void getScope_OT_Black(int Line, int Column, int BeginOTx, int BeginOTy, int EndOTx, int EndOTy, int scope) 
{
	//���˶������Ӷ���
	if (((Board[BeginOTy - 1][BeginOTx - 1] % 100 == WHITE_COLOR) || (Board[BeginOTy - 1][BeginOTx - 1] % 100 == WHITE_COLOR + 1)
		|| (BeginOTy == 0) || (BeginOTx == 0))
		&& 
		((Board[EndOTy][EndOTx] % 100 == WHITE_COLOR) || (Board[EndOTy][EndOTx] % 100 == WHITE_COLOR + 1)
		|| (EndOTy - 1 == BOARD_SIZE) || (EndOTx - 1 == BOARD_SIZE)))
	{
		//����[�񡡡�]�����
		if ((Board[BeginOTy + 1][BeginOTx + 1] % 100 <= 9)
			&& ((Board[BeginOTy + 2][BeginOTx + 2] % 100 == BLACK_COLOR) || (Board[BeginOTy + 2][BeginOTx + 2] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginOTy + 3][BeginOTx + 3] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy + 1][BeginOTx + 1] += scope*1;
		}

		//����[��񡡡�]�����
		else if (((Board[BeginOTy + 1][BeginOTx + 1] % 100 == BLACK_COLOR) || (Board[BeginOTy + 1][BeginOTx + 1] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginOTy + 2][BeginOTx + 2] % 100 <= 9) 
			&& ((Board[BeginOTy + 3][BeginOTx + 3] % 100 == BLACK_COLOR) || (Board[BeginOTy + 3][BeginOTx + 3] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginOTy + 4][BeginOTx + 4] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy + 2][BeginOTx + 2] += scope*1;
		}

		//����[�񡡡��]�����
		else if ((Board[BeginOTy + 1][BeginOTx + 1] % 100 <= 9)
			&& ((Board[BeginOTy + 2][BeginOTx + 2] % 100 == BLACK_COLOR) || (Board[BeginOTy + 2][BeginOTx + 2] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginOTy + 3][BeginOTx + 3] % 100 == BLACK_COLOR) || (Board[BeginOTy + 3][BeginOTx + 3] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginOTy + 4][BeginOTx + 4] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy + 1][BeginOTx + 1] += scope*1;
		}

		//����[���񡡡�]�����
		else if (((Board[BeginOTy + 1][BeginOTx + 1] % 100 == BLACK_COLOR) || (Board[BeginOTy + 1][BeginOTx + 1] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginOTy + 2][BeginOTx + 2] % 100 == BLACK_COLOR) || (Board[BeginOTy + 2][BeginOTx + 2] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginOTy + 3][BeginOTx + 3] % 100 <= 9)
			&& ((Board[BeginOTy + 4][BeginOTx + 4] % 100 == BLACK_COLOR) || (Board[BeginOTy + 4][BeginOTx + 4] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginOTy + 5][BeginOTx + 5] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy + 3][BeginOTx + 3] += scope*10;
		}

		//����[��񡡡��]�����
		else if (((Board[BeginOTy + 1][BeginOTx + 1] % 100 == BLACK_COLOR) || (Board[BeginOTy + 1][BeginOTx + 1] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginOTy + 2][BeginOTx + 2] % 100 <= 9)
			&& ((Board[BeginOTy + 3][BeginOTx + 3] % 100 == BLACK_COLOR) || (Board[BeginOTy + 3][BeginOTx + 3] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginOTy + 4][BeginOTx + 4] % 100 == BLACK_COLOR) || (Board[BeginOTy + 4][BeginOTx + 4] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginOTy + 5][BeginOTx + 5] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy + 2][BeginOTx + 2] += scope*10;
		}

		//����[�񡡡���]�����
		else if ((Board[BeginOTy + 1][BeginOTx + 1] % 100 <= 9)
			&& ((Board[BeginOTy + 2][BeginOTx + 2] % 100 == BLACK_COLOR) || (Board[BeginOTy + 2][BeginOTx + 2] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginOTy + 3][BeginOTx + 3] % 100 == BLACK_COLOR) || (Board[BeginOTy + 3][BeginOTx + 3] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginOTy + 4][BeginOTx + 4] % 100 == BLACK_COLOR) || (Board[BeginOTy + 4][BeginOTx + 4] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginOTy + 5][BeginOTx + 5] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy + 1][BeginOTx + 1] += scope*10;
		}

		return;
	}


	//���˾��ް���(==����û���ӣ���Ϊֻ�а��ӡ����ӡ�������״̬�����к��ӣ����ͳ�����Ӵ����Ӹ���)
	else if ((Board[BeginOTy - 1][BeginOTx - 1] % 100 <= 9) && (Board[EndOTy][EndOTx] % 100 <= 9) 
		&& 
		(0 < BeginOTy) && (0 < BeginOTx) && (EndOTy - 1 < BOARD_SIZE) && (EndOTx - 1 < BOARD_SIZE))
	{
		//����[�񡡡�]�����
		if ((Board[BeginOTy + 1][BeginOTx + 1] % 100 <= 9)
			&& ((Board[BeginOTy + 2][BeginOTx + 2] % 100 == BLACK_COLOR) || (Board[BeginOTy + 2][BeginOTx + 2] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginOTy + 3][BeginOTx + 3] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy + 1][BeginOTx + 1] += scope*4;
		}

		//����[��񡡡�]�����
		else if (((Board[BeginOTy + 1][BeginOTx + 1] % 100 == BLACK_COLOR) || (Board[BeginOTy + 1][BeginOTx + 1] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginOTy + 2][BeginOTx + 2] % 100 <= 9)  
			&& ((Board[BeginOTy + 3][BeginOTx + 3] % 100 == BLACK_COLOR) || (Board[BeginOTy + 3][BeginOTx + 3] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginOTy + 4][BeginOTx + 4] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy + 2][BeginOTx + 2] += scope*4;
		}

		//����[�񡡡��]�����
		else if ((Board[BeginOTy + 1][BeginOTx + 1] % 100 <= 9)
			&& ((Board[BeginOTy + 2][BeginOTx + 2] % 100 == BLACK_COLOR) || (Board[BeginOTy + 2][BeginOTx + 2] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginOTy + 3][BeginOTx + 3] % 100 == BLACK_COLOR) || (Board[BeginOTy + 3][BeginOTx + 3] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginOTy + 4][BeginOTx + 4] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy + 1][BeginOTx + 1] += scope*4;
		}

		//����[���񡡡�]�����
		else if (((Board[BeginOTy + 1][BeginOTx + 1] % 100 == BLACK_COLOR) || (Board[BeginOTy + 1][BeginOTx + 1] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginOTy + 2][BeginOTx + 2] % 100 == BLACK_COLOR) || (Board[BeginOTy + 2][BeginOTx + 2] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginOTy + 3][BeginOTx + 3] % 100 <= 9)
			&& ((Board[BeginOTy + 4][BeginOTx + 4] % 100 == BLACK_COLOR) || (Board[BeginOTy + 4][BeginOTx + 4] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginOTy + 5][BeginOTx + 5] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy + 3][BeginOTx + 3] += scope*10;
		}

		//����[��񡡡��]�����
		else if (((Board[BeginOTy + 1][BeginOTx + 1] % 100 == BLACK_COLOR) || (Board[BeginOTy + 1][BeginOTx + 1] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginOTy + 2][BeginOTx + 2] % 100 <= 9)
			&& ((Board[BeginOTy + 3][BeginOTx + 3] % 100 == BLACK_COLOR) || (Board[BeginOTy + 3][BeginOTx + 3] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginOTy + 4][BeginOTx + 4] % 100 == BLACK_COLOR) || (Board[BeginOTy + 4][BeginOTx + 4] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginOTy + 5][BeginOTx + 5] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy + 2][BeginOTx + 2] += scope*10;
		}

		//����[�񡡡���]�����
		else if ((Board[BeginOTy + 1][BeginOTx + 1] % 100 <= 9)
			&& ((Board[BeginOTy + 2][BeginOTx + 2] % 100 == BLACK_COLOR) || (Board[BeginOTy + 2][BeginOTx + 2] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginOTy + 3][BeginOTx + 3] % 100 == BLACK_COLOR) || (Board[BeginOTy + 3][BeginOTx + 3] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginOTy + 4][BeginOTx + 4] % 100 == BLACK_COLOR) || (Board[BeginOTy + 4][BeginOTx + 4] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginOTy + 5][BeginOTx + 5] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy + 1][BeginOTx + 1] += scope*10;
		}


		//////////////////////////////[Begin - 1]���£�[End + 1]δ���� 
		if (((Board[BeginOTy - 2][BeginOTx - 2] == WHITE_COLOR) || (Board[BeginOTy - 2][BeginOTx - 2] == WHITE_COLOR + 1) 
			|| (BeginOTy - 1 == 0) || (BeginOTx - 1 == 0))
			&& 
			((Board[EndOTy + 1][EndOTx + 1] != WHITE_COLOR) && (Board[EndOTy + 1][EndOTx + 1] != WHITE_COLOR + 1) 
			&& (EndOTy != BOARD_SIZE) && (EndOTx != BOARD_SIZE)))
		{
			Board[BeginOTy - 1][BeginOTx - 1] += scope*1;
			Board[EndOTy][EndOTx] += scope*3;
		}


		//[Begin - 1]δ���£�[End + 1]���� 
		else if (((Board[BeginOTy - 2][BeginOTx - 2] != WHITE_COLOR) && (Board[BeginOTy - 2][BeginOTx - 2] != WHITE_COLOR + 1) 
			&& (BeginOTy - 1 != 0) && (BeginOTx - 1 != 0))
			&& 
			((Board[EndOTy + 1][EndOTx + 1] == WHITE_COLOR) || (Board[EndOTy + 1][EndOTx + 1] == WHITE_COLOR + 1) 
			|| (EndOTy == BOARD_SIZE) || (EndOTx == BOARD_SIZE)))
		{
			Board[BeginOTy - 1][BeginOTx - 1] += scope*3;
			Board[EndOTy][EndOTx] += scope*1;
		}

		//[Begin - 1]��[End + 1]������
		else if (((Board[BeginOTy - 2][BeginOTx - 2] == WHITE_COLOR) || (Board[BeginOTy - 2][BeginOTx - 2] == WHITE_COLOR + 1) 
			|| (BeginOTy - 1 == 0) || (BeginOTx - 1 == 0))
			&& 
			((Board[EndOTy + 1][EndOTx + 1] == WHITE_COLOR) || (Board[EndOTy + 1][EndOTx + 1] == WHITE_COLOR + 1) 
			|| (EndOTy == BOARD_SIZE) || (EndOTx == BOARD_SIZE)))
		{
			Board[BeginV - 1][Column] += scope*1;
			Board[EndV][Column] += scope*1;
		}

		else
		{
			Board[BeginOTy - 1][BeginOTx - 1] += scope*4;
			Board[EndOTy][EndOTx] += scope*4;
		}
	}


	//begin�˱����Ӷ£�ͬʱ��end���ް��� 
	else if (((Board[BeginOTy - 1][BeginOTx - 1] % 100 == WHITE_COLOR) || (Board[BeginOTy - 1][BeginOTx - 1] % 100 == WHITE_COLOR + 1)
		|| (BeginOTy == 0) || (BeginOTx == 0)) 
		&& 
		((Board[EndOTy][EndOTx] % 100 <= 9) && (EndOTy - 1 < BOARD_SIZE) && (EndOTx - 1 < BOARD_SIZE))) 
	{
		//����[�񡡡�]�����
		if ((Board[BeginOTy + 1][BeginOTx + 1] % 100 <= 9)
			&& ((Board[BeginOTy + 2][BeginOTx + 2] % 100 == BLACK_COLOR) || (Board[BeginOTy + 2][BeginOTx + 2] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginOTy + 3][BeginOTx + 3] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy][BeginOTx + 1] += scope*2;
		}

		//����[��񡡡�]�����
		else if (((Board[BeginOTy + 1][BeginOTx + 1] % 100 == BLACK_COLOR) || (Board[BeginOTy + 1][BeginOTx + 1] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginOTy + 2][BeginOTx + 2] % 100 <= 9) 
			&& ((Board[BeginOTy + 3][BeginOTx + 3] % 100 == BLACK_COLOR) || (Board[BeginOTy + 3][BeginOTx + 3] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginOTy + 4][BeginOTx + 4] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy + 2][BeginOTx + 2] += scope*2;
		}

		//����[�񡡡��]�����
		else if ((Board[BeginOTy + 1][BeginOTx + 1] % 100 <= 9)
			&& ((Board[BeginOTy + 2][BeginOTx + 2] % 100 == BLACK_COLOR) || (Board[BeginOTy + 2][BeginOTx + 2] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginOTy + 3][BeginOTx + 3] % 100 == BLACK_COLOR) || (Board[BeginOTy + 3][BeginOTx + 3] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginOTy + 4][BeginOTx + 4] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy + 1][BeginOTx + 1] += scope*2;
		}

		//����[���񡡡�]�����
		else if (((Board[BeginOTy + 1][BeginOTx + 1] % 100 == BLACK_COLOR) || (Board[BeginOTy + 1][BeginOTx + 1] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginOTy + 2][BeginOTx + 2] % 100 == BLACK_COLOR) || (Board[BeginOTy + 2][BeginOTx + 2] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginOTy + 3][BeginOTx + 3] % 100 <= 9)
			&& ((Board[BeginOTy + 4][BeginOTx + 4] % 100 == BLACK_COLOR) || (Board[BeginOTy + 4][BeginOTx + 4] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginOTy + 5][BeginOTx + 5] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy + 3][BeginOTx + 3] += scope*10;
		}

		//����[��񡡡��]�����
		else if (((Board[BeginOTy + 1][BeginOTx + 1] % 100 == BLACK_COLOR) || (Board[BeginOTy + 1][BeginOTx + 1] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginOTy + 2][BeginOTx + 2] % 100 <= 9)
			&& ((Board[BeginOTy + 3][BeginOTx + 3] % 100 == BLACK_COLOR) || (Board[BeginOTy + 3][BeginOTx + 3] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginOTy + 4][BeginOTx + 4] % 100 == BLACK_COLOR) || (Board[BeginOTy + 4][BeginOTx + 4] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginOTy + 5][BeginOTx + 5] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy + 2][BeginOTx + 2] += scope*10;
		}

		//����[�񡡡���]�����
		else if ((Board[BeginOTy + 1][BeginOTx + 1] % 100 <= 9)
			&& ((Board[BeginOTy + 2][BeginOTx + 2] % 100 == BLACK_COLOR) || (Board[BeginOTy + 2][BeginOTx + 2] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginOTy + 3][BeginOTx + 3] % 100 == BLACK_COLOR) || (Board[BeginOTy + 3][BeginOTx + 3] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginOTy + 4][BeginOTx + 4] % 100 == BLACK_COLOR) || (Board[BeginOTy + 4][BeginOTx + 4] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginOTy + 5][BeginOTx + 5] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy + 1][BeginOTx + 1] += scope*10;
		}


		//[End + 1]������ 
		if ((Board[EndOTy + 1][EndOTx + 1] == WHITE_COLOR) || (Board[EndOTy + 1][EndOTx + 1] == WHITE_COLOR + 1) 
			|| (EndOTy == BOARD_SIZE) || (EndOTx == BOARD_SIZE))
		{
			Board[EndOTy][EndOTx] += scope*1;
		}

		else
		{
			Board[EndOTy][EndOTx] += scope*2;
		}
	}


	//begin���ް��ӣ�ͬʱ��end�˱����Ӷ� 
	else if (((Board[BeginOTy - 1][BeginOTx - 1] % 100 <= 9) && (0 < BeginOTy) && (0 < BeginOTx)) 
		&& 
		((Board[EndOTy][EndOTx] % 100 == WHITE_COLOR) || (Board[EndOTy][EndOTx] % 100 == WHITE_COLOR + 1) 
		|| (EndOTy - 1 == BOARD_SIZE) || (EndOTx - 1 == BOARD_SIZE))) 
	{
		//����[�񡡡�]�����
		if ((Board[BeginOTy + 1][BeginOTx + 1] % 100 <= 9)
			&& ((Board[BeginOTy + 2][BeginOTx + 2] % 100 == BLACK_COLOR) || (Board[BeginOTy + 2][BeginOTx + 2] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginOTy + 3][BeginOTx + 3] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy + 1][BeginOTx + 1] += scope*2;
		}

		//����[��񡡡�]�����
		else if (((Board[BeginOTy + 1][BeginOTx + 1] % 100 == BLACK_COLOR) || (Board[BeginOTy + 1][BeginOTx + 1] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginOTy + 2][BeginOTx + 2] % 100 <= 9) 
			&& ((Board[BeginOTy + 3][BeginOTx + 3] % 100 == BLACK_COLOR) || (Board[BeginOTy + 3][BeginOTx + 3] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginOTy + 4][BeginOTx + 4] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy + 2][BeginOTx + 2] += scope*2;
		}

		//����[�񡡡��]�����
		else if ((Board[BeginOTy + 1][BeginOTx + 1] % 100 <= 9)
			&& ((Board[BeginOTy + 2][BeginOTx + 2] % 100 == BLACK_COLOR) || (Board[BeginOTy + 2][BeginOTx + 2] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginOTy + 3][BeginOTx + 3] % 100 == BLACK_COLOR) || (Board[BeginOTy + 3][BeginOTx + 3] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginOTy + 4][BeginOTx + 4] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy + 1][BeginOTx + 1] += scope*2;
		}

		//����[���񡡡�]�����
		else if (((Board[BeginOTy + 1][BeginOTx + 1] % 100 == BLACK_COLOR) || (Board[BeginOTy + 1][BeginOTx + 1] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginOTy + 2][BeginOTx + 2] % 100 == BLACK_COLOR) || (Board[BeginOTy + 2][BeginOTx + 2] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginOTy + 3][BeginOTx + 3] % 100 <= 9)
			&& ((Board[BeginOTy + 4][BeginOTx + 4] % 100 == BLACK_COLOR) || (Board[BeginOTy + 4][BeginOTx + 4] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginOTy + 5][BeginOTx + 5] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy + 3][BeginOTx + 3] += scope*10;
		}

		//����[��񡡡��]�����
		else if (((Board[BeginOTy + 1][BeginOTx + 1] % 100 == BLACK_COLOR) || (Board[BeginOTy + 1][BeginOTx + 1] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginOTy + 2][BeginOTx + 2] % 100 <= 9)
			&& ((Board[BeginOTy + 3][BeginOTx + 3] % 100 == BLACK_COLOR) || (Board[BeginOTy + 3][BeginOTx + 3] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginOTy + 4][BeginOTx + 4] % 100 == BLACK_COLOR) || (Board[BeginOTy + 4][BeginOTx + 4] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginOTy + 5][BeginOTx + 5] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy + 2][BeginOTx + 2] += scope*10;
		}

		//����[�񡡡���]�����
		else if ((Board[BeginOTy + 1][BeginOTx + 1] % 100 <= 9)
			&& ((Board[BeginOTy + 2][BeginOTx + 2] % 100 == BLACK_COLOR) || (Board[BeginOTy + 2][BeginOTx + 2] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginOTy + 3][BeginOTx + 3] % 100 == BLACK_COLOR) || (Board[BeginOTy + 3][BeginOTx + 3] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginOTy + 4][BeginOTx + 4] % 100 == BLACK_COLOR) || (Board[BeginOTy + 4][BeginOTx + 4] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginOTy + 5][BeginOTx + 5] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy + 1][BeginOTx + 1] += scope*10;
		}


		//////[Begin - 1]������ 
		if ((Board[BeginOTy - 2][BeginOTx - 2] == WHITE_COLOR) || (Board[BeginOTy - 2][BeginOTx - 2] == WHITE_COLOR + 1) 
			|| (BeginOTy - 1 == 0) || (BeginOTx - 1 == 0))
		{
			Board[BeginOTy - 1][BeginOTx - 1] += scope*1;
		}

		else
		{
			Board[BeginOTy - 1][BeginOTx - 1] += scope*2;
		}
	}
}


//һ�����޷�չ�����ֱ���
void getScope_OT_White(int Line, int Column, int BeginOTx, int BeginOTy, int EndOTx, int EndOTy, int scope) 
{
	//���˶������Ӷ���
	if (((Board[BeginOTy - 1][BeginOTx - 1] % 100 == BLACK_COLOR) || (Board[BeginOTy - 1][BeginOTx - 1] % 100 == BLACK_COLOR + 1)
		|| (BeginOTy == 0) || (BeginOTx == 0))
		&& 
		((Board[EndOTy][EndOTx] % 100 == BLACK_COLOR) || (Board[EndOTy][EndOTx] % 100 == BLACK_COLOR + 1)
		|| (EndOTy - 1 == BOARD_SIZE) || (EndOTx - 1 == BOARD_SIZE)))
	{
		//����[�򡡡�]�����
		if ((Board[BeginOTy + 1][BeginOTx + 1] % 100 <= 9)
			&& ((Board[BeginOTy + 2][BeginOTx + 2] % 100 == WHITE_COLOR) || (Board[BeginOTy + 2][BeginOTx + 2] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginOTy + 3][BeginOTx + 3] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy + 1][BeginOTx + 1] += scope*1;
		}

		//����[��򡡡�]�����
		else if (((Board[BeginOTy + 1][BeginOTx + 1] % 100 == WHITE_COLOR) || (Board[BeginOTy + 1][BeginOTx + 1] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginOTy + 2][BeginOTx + 2] % 100 <= 9) 
			&& ((Board[BeginOTy + 3][BeginOTx + 3] % 100 == WHITE_COLOR) || (Board[BeginOTy + 3][BeginOTx + 3] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginOTy + 4][BeginOTx + 4] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy + 2][BeginOTx + 2] += scope*1;
		}

		//����[�򡡡��]�����
		else if ((Board[BeginOTy + 1][BeginOTx + 1] % 100 <= 9)
			&& ((Board[BeginOTy + 2][BeginOTx + 2] % 100 == WHITE_COLOR) || (Board[BeginOTy + 2][BeginOTx + 2] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginOTy + 3][BeginOTx + 3] % 100 == WHITE_COLOR) || (Board[BeginOTy + 3][BeginOTx + 3] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginOTy + 4][BeginOTx + 4] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy + 1][BeginOTx + 1] += scope*1;
		}

		//����[���򡡡�]�����
		else if (((Board[BeginOTy + 1][BeginOTx + 1] % 100 == WHITE_COLOR) || (Board[BeginOTy + 1][BeginOTx + 1] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginOTy + 2][BeginOTx + 2] % 100 == WHITE_COLOR) || (Board[BeginOTy + 2][BeginOTx + 2] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginOTy + 3][BeginOTx + 3] % 100 <= 9)
			&& ((Board[BeginOTy + 4][BeginOTx + 4] % 100 == WHITE_COLOR) || (Board[BeginOTy + 4][BeginOTx + 4] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginOTy + 5][BeginOTx + 5] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy + 3][BeginOTx + 3] += scope*10;
		}

		//����[��򡡡��]�����
		else if (((Board[BeginOTy + 1][BeginOTx + 1] % 100 == WHITE_COLOR) || (Board[BeginOTy + 1][BeginOTx + 1] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginOTy + 2][BeginOTx + 2] % 100 <= 9)
			&& ((Board[BeginOTy + 3][BeginOTx + 3] % 100 == WHITE_COLOR) || (Board[BeginOTy + 3][BeginOTx + 3] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginOTy + 4][BeginOTx + 4] % 100 == WHITE_COLOR) || (Board[BeginOTy + 4][BeginOTx + 4] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginOTy + 5][BeginOTx + 5] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy + 2][BeginOTx + 2] += scope*10;
		}

		//����[�򡡡���]�����
		else if ((Board[BeginOTy + 1][BeginOTx + 1] % 100 <= 9)
			&& ((Board[BeginOTy + 2][BeginOTx + 2] % 100 == WHITE_COLOR) || (Board[BeginOTy + 2][BeginOTx + 2] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginOTy + 3][BeginOTx + 3] % 100 == WHITE_COLOR) || (Board[BeginOTy + 3][BeginOTx + 3] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginOTy + 4][BeginOTx + 4] % 100 == WHITE_COLOR) || (Board[BeginOTy + 4][BeginOTx + 4] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginOTy + 5][BeginOTx + 5] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy + 1][BeginOTx + 1] += scope*10;
		}

		return;
	}


	//���˾��޺���(==����û���ӣ���Ϊֻ�а��ӡ����ӡ�������״̬�����к��ӣ����ͳ�����Ӵ����Ӹ���)
	else if ((Board[BeginOTy - 1][BeginOTx - 1] % 100 <= 9) && (Board[EndOTy][EndOTx] % 100 <= 9)
		&& (0 < BeginOTy) && (0 < BeginOTx) && (EndOTy - 1 < BOARD_SIZE) && (EndOTx - 1 < BOARD_SIZE))
	{
		//����[�򡡡�]�����
		if ((Board[BeginOTy + 1][BeginOTx + 1] % 100 <= 9)
			&& ((Board[BeginOTy + 2][BeginOTx + 2] % 100 == WHITE_COLOR) || (Board[BeginOTy + 2][BeginOTx + 2] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginOTy + 3][BeginOTx + 3] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy + 1][BeginOTx + 1] += scope*4;
		}

		//����[��򡡡�]�����
		else if (((Board[BeginOTy + 1][BeginOTx + 1] % 100 == WHITE_COLOR) || (Board[BeginOTy + 1][BeginOTx + 1] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginOTy + 2][BeginOTx + 2] % 100 <= 9)  
			&& ((Board[BeginOTy + 3][BeginOTx + 3] % 100 == WHITE_COLOR) || (Board[BeginOTy + 3][BeginOTx + 3] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginOTy + 4][BeginOTx + 4] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy + 2][BeginOTx + 2] += scope*4;
		}

		//����[�򡡡��]�����
		else if ((Board[BeginOTy + 1][BeginOTx + 1] % 100 <= 9)
			&& ((Board[BeginOTy + 2][BeginOTx + 2] % 100 == WHITE_COLOR) || (Board[BeginOTy + 2][BeginOTx + 2] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginOTy + 3][BeginOTx + 3] % 100 == WHITE_COLOR) || (Board[BeginOTy + 3][BeginOTx + 3] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginOTy + 4][BeginOTx + 4] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy + 1][BeginOTx + 1] += scope*4;
		}

		//����[���򡡡�]�����
		else if (((Board[BeginOTy + 1][BeginOTx + 1] % 100 == WHITE_COLOR) || (Board[BeginOTy + 1][BeginOTx + 1] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginOTy + 2][BeginOTx + 2] % 100 == WHITE_COLOR) || (Board[BeginOTy + 2][BeginOTx + 2] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginOTy + 3][BeginOTx + 3] % 100 <= 9)
			&& ((Board[BeginOTy + 4][BeginOTx + 4] % 100 == WHITE_COLOR) || (Board[BeginOTy + 4][BeginOTx + 4] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginOTy + 5][BeginOTx + 5] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy + 3][BeginOTx + 3] += scope*10;
		}

		//����[��򡡡��]�����
		else if (((Board[BeginOTy + 1][BeginOTx + 1] % 100 == WHITE_COLOR) || (Board[BeginOTy + 1][BeginOTx + 1] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginOTy + 2][BeginOTx + 2] % 100 <= 9)
			&& ((Board[BeginOTy + 3][BeginOTx + 3] % 100 == WHITE_COLOR) || (Board[BeginOTy + 3][BeginOTx + 3] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginOTy + 4][BeginOTx + 4] % 100 == WHITE_COLOR) || (Board[BeginOTy + 4][BeginOTx + 4] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginOTy + 5][BeginOTx + 5] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy + 2][BeginOTx + 2] += scope*10;
		}

		//����[�򡡡���]�����
		else if ((Board[BeginOTy + 1][BeginOTx + 1] % 100 <= 9)
			&& ((Board[BeginOTy + 2][BeginOTx + 2] % 100 == WHITE_COLOR) || (Board[BeginOTy + 2][BeginOTx + 2] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginOTy + 3][BeginOTx + 3] % 100 == WHITE_COLOR) || (Board[BeginOTy + 3][BeginOTx + 3] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginOTy + 4][BeginOTx + 4] % 100 == WHITE_COLOR) || (Board[BeginOTy + 4][BeginOTx + 4] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginOTy + 5][BeginOTx + 5] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy + 1][BeginOTx + 1] += scope*10;
		}


		//////////////////////////////[Begin - 1]���£�[End + 1]δ���� 
		if (((Board[BeginOTy - 2][BeginOTx - 2] == BLACK_COLOR) || (Board[BeginOTy - 2][BeginOTx - 2] == BLACK_COLOR + 1) 
			|| (BeginOTy - 1 == 0) || (BeginOTx - 1 == 0))
			&& 
			((Board[EndOTy + 1][EndOTx + 1] != BLACK_COLOR) && (Board[EndOTy + 1][EndOTx + 1] != BLACK_COLOR + 1) 
			&& (EndOTy != BOARD_SIZE) && (EndOTx != BOARD_SIZE)))
		{
			Board[BeginOTy - 1][BeginOTx - 1] += scope*1;
			Board[EndOTy][EndOTx] += scope*3;
		}


		//[Begin - 1]δ���£�[End + 1]���� 
		else if (((Board[BeginOTy - 2][BeginOTx - 2] != BLACK_COLOR) && (Board[BeginOTy - 2][BeginOTx - 2] != BLACK_COLOR + 1) 
			&& (BeginOTy - 1 != 0) && (BeginOTx - 1 != 0))
			&& 
			((Board[EndOTy + 1][EndOTx + 1] == BLACK_COLOR) || (Board[EndOTy + 1][EndOTx + 1] == BLACK_COLOR + 1) 
			|| (EndOTy == BOARD_SIZE) || (EndOTx == BOARD_SIZE)))
		{
			Board[BeginOTy - 1][BeginOTx - 1] += scope*3;
			Board[EndOTy][EndOTx] += scope*1;
		}

		//[Begin - 1]��[End + 1]������
		else if (((Board[BeginOTy - 2][BeginOTx - 2] == BLACK_COLOR) || (Board[BeginOTy - 2][BeginOTx - 2] == BLACK_COLOR + 1) 
			|| (BeginOTy - 1 == 0) || (BeginOTx - 1 == 0))
			&& 
			((Board[EndOTy + 1][EndOTx + 1] == BLACK_COLOR) || (Board[EndOTy + 1][EndOTx + 1] == BLACK_COLOR + 1) 
			|| (EndOTy == BOARD_SIZE) || (EndOTx == BOARD_SIZE)))
		{
			Board[BeginV - 1][Column] += scope*1;
			Board[EndV][Column] += scope*1;
		}

		else
		{
			Board[BeginOTy - 1][BeginOTx - 1] += scope*4;
			Board[EndOTy][EndOTx] += scope*4;
		}	}


	//begin�˱����Ӷ£�ͬʱ��end���޺��� 
	else if (((Board[BeginOTy - 1][BeginOTx - 1] % 100 == BLACK_COLOR) || (Board[BeginOTy - 1][BeginOTx - 1] % 100 == BLACK_COLOR + 1)
		|| (BeginOTy == 0) || (BeginOTx == 0)) 
		&& 
		((Board[EndOTy][EndOTx] % 100 <= 9) && (EndOTy - 1 < BOARD_SIZE) && (EndOTx - 1 < BOARD_SIZE))) 
	{
		//����[�򡡡�]�����
		if ((Board[BeginOTy + 1][BeginOTx + 1] % 100 <= 9)
			&& ((Board[BeginOTy + 2][BeginOTx + 2] % 100 == WHITE_COLOR) || (Board[BeginOTy + 2][BeginOTx + 2] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginOTy + 3][BeginOTx + 3] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy][BeginOTx + 1] += scope*2;
		}

		//����[��򡡡�]�����
		else if (((Board[BeginOTy + 1][BeginOTx + 1] % 100 == WHITE_COLOR) || (Board[BeginOTy + 1][BeginOTx + 1] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginOTy + 2][BeginOTx + 2] % 100 <= 9) 
			&& ((Board[BeginOTy + 3][BeginOTx + 3] % 100 == WHITE_COLOR) || (Board[BeginOTy + 3][BeginOTx + 3] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginOTy + 4][BeginOTx + 4] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy + 2][BeginOTx + 2] += scope*2;
		}

		//����[�򡡡��]�����
		else if ((Board[BeginOTy + 1][BeginOTx + 1] % 100 <= 9)
			&& ((Board[BeginOTy + 2][BeginOTx + 2] % 100 == WHITE_COLOR) || (Board[BeginOTy + 2][BeginOTx + 2] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginOTy + 3][BeginOTx + 3] % 100 == WHITE_COLOR) || (Board[BeginOTy + 3][BeginOTx + 3] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginOTy + 4][BeginOTx + 4] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy + 1][BeginOTx + 1] += scope*2;
		}

		//����[���򡡡�]�����
		else if (((Board[BeginOTy + 1][BeginOTx + 1] % 100 == WHITE_COLOR) || (Board[BeginOTy + 1][BeginOTx + 1] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginOTy + 2][BeginOTx + 2] % 100 == WHITE_COLOR) || (Board[BeginOTy + 2][BeginOTx + 2] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginOTy + 3][BeginOTx + 3] % 100 <= 9)
			&& ((Board[BeginOTy + 4][BeginOTx + 4] % 100 == WHITE_COLOR) || (Board[BeginOTy + 4][BeginOTx + 4] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginOTy + 5][BeginOTx + 5] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy + 3][BeginOTx + 3] += scope*10;
		}

		//����[��򡡡��]�����
		else if (((Board[BeginOTy + 1][BeginOTx + 1] % 100 == WHITE_COLOR) || (Board[BeginOTy + 1][BeginOTx + 1] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginOTy + 2][BeginOTx + 2] % 100 <= 9)
			&& ((Board[BeginOTy + 3][BeginOTx + 3] % 100 == WHITE_COLOR) || (Board[BeginOTy + 3][BeginOTx + 3] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginOTy + 4][BeginOTx + 4] % 100 == WHITE_COLOR) || (Board[BeginOTy + 4][BeginOTx + 4] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginOTy + 5][BeginOTx + 5] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy + 2][BeginOTx + 2] += scope*10;
		}

		//����[�򡡡���]�����
		else if ((Board[BeginOTy + 1][BeginOTx + 1] % 100 <= 9)
			&& ((Board[BeginOTy + 2][BeginOTx + 2] % 100 == WHITE_COLOR) || (Board[BeginOTy + 2][BeginOTx + 2] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginOTy + 3][BeginOTx + 3] % 100 == WHITE_COLOR) || (Board[BeginOTy + 3][BeginOTx + 3] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginOTy + 4][BeginOTx + 4] % 100 == WHITE_COLOR) || (Board[BeginOTy + 4][BeginOTx + 4] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginOTy + 5][BeginOTx + 5] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy + 1][BeginOTx + 1] += scope*10;
		}


		//[End + 1]������ 
		if ((Board[EndOTy + 1][EndOTx + 1] == BLACK_COLOR) || (Board[EndOTy + 1][EndOTx + 1] == BLACK_COLOR + 1) 
			|| (EndOTy == BOARD_SIZE) || (EndOTx == BOARD_SIZE))
		{
			Board[EndOTy][EndOTx] += scope*1;
		}

		else
		{
			Board[EndOTy][EndOTx] += scope*2;
		}
	}


	//begin���޺��ӣ�ͬʱ��end�˱����Ӷ� 
	else if (((Board[BeginOTy - 1][BeginOTx - 1] % 100 <= 9) && (0 < BeginOTy) && (0 < BeginOTx)) 
		&& 
		((Board[EndOTy][EndOTx] % 100 == BLACK_COLOR) || (Board[EndOTy][EndOTx] % 100 == BLACK_COLOR + 1)
		|| (EndOTy - 1 == BOARD_SIZE) || (EndOTx - 1 == BOARD_SIZE))) 
	{
		//����[�򡡡�]�����
		if ((Board[BeginOTy + 1][BeginOTx + 1] % 100 <= 9)
			&& ((Board[BeginOTy + 2][BeginOTx + 2] % 100 == WHITE_COLOR) || (Board[BeginOTy + 2][BeginOTx + 2] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginOTy + 3][BeginOTx + 3] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy + 1][BeginOTx + 1] += scope*2;
		}

		//����[��򡡡�]�����
		else if (((Board[BeginOTy + 1][BeginOTx + 1] % 100 == WHITE_COLOR) || (Board[BeginOTy + 1][BeginOTx + 1] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginOTy + 2][BeginOTx + 2] % 100 <= 9) 
			&& ((Board[BeginOTy + 3][BeginOTx + 3] % 100 == WHITE_COLOR) || (Board[BeginOTy + 3][BeginOTx + 3] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginOTy + 4][BeginOTx + 4] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy + 2][BeginOTx + 2] += scope*2;
		}

		//����[�򡡡��]�����
		else if ((Board[BeginOTy + 1][BeginOTx + 1] % 100 <= 9)
			&& ((Board[BeginOTy + 2][BeginOTx + 2] % 100 == WHITE_COLOR) || (Board[BeginOTy + 2][BeginOTx + 2] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginOTy + 3][BeginOTx + 3] % 100 == WHITE_COLOR) || (Board[BeginOTy + 3][BeginOTx + 3] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginOTy + 4][BeginOTx + 4] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy + 1][BeginOTx + 1] += scope*2;
		}

		//����[���򡡡�]�����
		else if (((Board[BeginOTy + 1][BeginOTx + 1] % 100 == WHITE_COLOR) || (Board[BeginOTy + 1][BeginOTx + 1] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginOTy + 2][BeginOTx + 2] % 100 == WHITE_COLOR) || (Board[BeginOTy + 2][BeginOTx + 2] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginOTy + 3][BeginOTx + 3] % 100 <= 9)
			&& ((Board[BeginOTy + 4][BeginOTx + 4] % 100 == WHITE_COLOR) || (Board[BeginOTy + 4][BeginOTx + 4] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginOTy + 5][BeginOTx + 5] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy + 3][BeginOTx + 3] += scope*10;
		}

		//����[��򡡡��]�����
		else if (((Board[BeginOTy + 1][BeginOTx + 1] % 100 == WHITE_COLOR) || (Board[BeginOTy + 1][BeginOTx + 1] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginOTy + 2][BeginOTx + 2] % 100 <= 9)
			&& ((Board[BeginOTy + 3][BeginOTx + 3] % 100 == WHITE_COLOR) || (Board[BeginOTy + 3][BeginOTx + 3] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginOTy + 4][BeginOTx + 4] % 100 == WHITE_COLOR) || (Board[BeginOTy + 4][BeginOTx + 4] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginOTy + 5][BeginOTx + 5] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy + 2][BeginOTx + 2] += scope*10;
		}

		//����[�򡡡���]�����
		else if ((Board[BeginOTy + 1][BeginOTx + 1] % 100 <= 9)
			&& ((Board[BeginOTy + 2][BeginOTx + 2] % 100 == WHITE_COLOR) || (Board[BeginOTy + 2][BeginOTx + 2] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginOTy + 3][BeginOTx + 3] % 100 == WHITE_COLOR) || (Board[BeginOTy + 3][BeginOTx + 3] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginOTy + 4][BeginOTx + 4] % 100 == WHITE_COLOR) || (Board[BeginOTy + 4][BeginOTx + 4] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginOTy + 5][BeginOTx + 5] % 100 == Board[EndOTy][EndOTx] % 100))
		{
			Board[BeginOTy + 1][BeginOTx + 1] += scope*10;
		}


		//////[Begin - 1]������ 
		if ((Board[BeginOTy - 2][BeginOTx - 2] == BLACK_COLOR) || (Board[BeginOTy - 2][BeginOTx - 2] == BLACK_COLOR + 1) 
			|| (BeginOTy - 1 == 0) || (BeginOTx - 1 == 0))
		{
			Board[BeginOTy - 1][BeginOTx - 1] += scope*1;
		}

		else
		{
			Board[BeginOTy - 1][BeginOTx - 1] += scope*2;
		}
	}
}


//�������޶º����ֱ���
void getScope_TF_Black(int Line, int Column, int BeginTFx, int BeginTFy, int EndTFx, int EndTFy, int scope) 
{
	//���˶������Ӷ���
	if (((Board[BeginTFy + 1][BeginTFx - 1] % 100 == WHITE_COLOR) || (Board[BeginTFy + 1][BeginTFx - 1] % 100 == WHITE_COLOR + 1)
		|| (BeginTFy == BOARD_SIZE) || (BeginTFx == 0))
		&& 
		((Board[EndTFy][EndTFx] % 100 == WHITE_COLOR) || (Board[EndTFy][EndTFx] % 100 == WHITE_COLOR + 1)
		|| (EndTFy + 1 == 0) || (EndTFx - 1 == BOARD_SIZE)))
	{
		//����[�񡡡�]�����
		if ((Board[BeginTFy - 1][BeginTFx + 1] % 100 <= 9)
			&& ((Board[BeginTFy - 2][BeginTFx + 2] % 100 == BLACK_COLOR) || (Board[BeginTFy - 2][BeginTFx + 2] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginTFy - 3][BeginTFx + 3] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy - 1][BeginTFx + 1] += scope*1;
		}

		//����[��񡡡�]�����
		else if (((Board[BeginTFy - 1][BeginTFx + 1] % 100 == BLACK_COLOR) || (Board[BeginTFy - 1][BeginTFx + 1] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginTFy - 2][BeginTFx + 2] % 100 <= 9) 
			&& ((Board[BeginTFy - 3][BeginTFx + 3] % 100 == BLACK_COLOR) || (Board[BeginTFy - 3][BeginTFx + 3] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginTFy - 4][BeginTFx + 4] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy - 2][BeginTFx + 2] += scope*1;
		}

		//����[�񡡡��]�����
		else if ((Board[BeginTFy - 1][BeginTFx + 1] % 100 <= 9)
			&& ((Board[BeginTFy - 2][BeginTFx + 2] % 100 == BLACK_COLOR) || (Board[BeginTFy - 2][BeginTFx + 2] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginTFy - 3][BeginTFx + 3] % 100 == BLACK_COLOR) || (Board[BeginTFy - 3][BeginTFx + 3] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginTFy - 4][BeginTFx + 4] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy - 1][BeginTFx + 1] += scope*1;
		}

		//����[���񡡡�]�����
		else if (((Board[BeginTFy - 1][BeginTFx + 1] % 100 == BLACK_COLOR) || (Board[BeginTFy - 1][BeginTFx + 1] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginTFy - 2][BeginTFx + 2] % 100 == BLACK_COLOR) || (Board[BeginTFy - 2][BeginTFx + 2] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginTFy - 3][BeginTFx + 3] % 100 <= 9)
			&& ((Board[BeginTFy - 4][BeginTFx + 4] % 100 == BLACK_COLOR) || (Board[BeginTFy - 4][BeginTFx + 4] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginTFy - 5][BeginTFx + 5] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy - 3][BeginTFx + 3] += scope*10;
		}

		//����[��񡡡��]�����
		else if (((Board[BeginTFy - 1][BeginTFx + 1] % 100 == BLACK_COLOR) || (Board[BeginTFy - 1][BeginTFx + 1] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginTFy - 2][BeginTFx + 2] % 100 <= 9)
			&& ((Board[BeginTFy - 3][BeginTFx + 3] % 100 == BLACK_COLOR) || (Board[BeginTFy - 3][BeginTFx + 3] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginTFy - 4][BeginTFx + 4] % 100 == BLACK_COLOR) || (Board[BeginTFy - 4][BeginTFx + 4] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginTFy - 5][BeginTFx + 5] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy - 2][BeginTFx + 2] += scope*10;
		}

		//����[�񡡡���]�����
		else if ((Board[BeginTFy - 1][BeginTFx + 1] % 100 <= 9)
			&& ((Board[BeginTFy - 2][BeginTFx + 2] % 100 == BLACK_COLOR) || (Board[BeginTFy - 2][BeginTFx + 2] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginTFy - 3][BeginTFx + 3] % 100 == BLACK_COLOR) || (Board[BeginTFy - 3][BeginTFx + 3] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginTFy - 4][BeginTFx + 4] % 100 == BLACK_COLOR) || (Board[BeginTFy - 4][BeginTFx + 4] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginTFy - 5][BeginTFx + 5] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy - 1][BeginTFx + 1] += scope*10;
		}

		return;
	}


	//���˾��ް���(==����û���ӣ���Ϊֻ�а��ӡ����ӡ�������״̬�����к��ӣ����ͳ�����Ӵ����Ӹ���)
	else if ((Board[BeginTFy + 1][BeginTFx - 1] % 100 <= 9) && (Board[EndTFy][EndTFx] % 100 <= 9)
		&& (BeginTFy < BOARD_SIZE) && (0 < BeginTFx) && (0 < EndTFy + 1) && (EndTFx - 1 < BOARD_SIZE))
	{
		//����[�񡡡�]�����
		if ((Board[BeginTFy - 1][BeginTFx + 1] % 100 <= 9)
			&& ((Board[BeginTFy - 2][BeginTFx + 2] % 100 == BLACK_COLOR) || (Board[BeginTFy - 2][BeginTFx + 2] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginTFy - 3][BeginTFx + 3] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy - 1][BeginTFx + 1] += scope*4;
		}

		//����[��񡡡�]�����
		else if (((Board[BeginTFy - 1][BeginTFx + 1] % 100 == BLACK_COLOR) || (Board[BeginTFy - 1][BeginTFx + 1] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginTFy - 2][BeginTFx + 2] % 100 <= 9)  
			&& ((Board[BeginTFy - 3][BeginTFx + 3] % 100 == BLACK_COLOR) || (Board[BeginTFy - 3][BeginTFx + 3] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginTFy - 4][BeginTFx + 4] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy - 2][BeginTFx + 2] += scope*4;
		}

		//����[�񡡡��]�����
		else if ((Board[BeginTFy - 1][BeginTFx + 1] % 100 <= 9)
			&& ((Board[BeginTFy - 2][BeginTFx + 2] % 100 == BLACK_COLOR) || (Board[BeginTFy - 2][BeginTFx + 2] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginTFy - 3][BeginTFx + 3] % 100 == BLACK_COLOR) || (Board[BeginTFy - 3][BeginTFx + 3] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginTFy - 4][BeginTFx + 4] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy - 1][BeginTFx + 1] += scope*4;
		}

		//����[���񡡡�]�����
		else if (((Board[BeginTFy - 1][BeginTFx + 1] % 100 == BLACK_COLOR) || (Board[BeginTFy - 1][BeginTFx + 1] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginTFy - 2][BeginTFx + 2] % 100 == BLACK_COLOR) || (Board[BeginTFy - 2][BeginTFx + 2] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginTFy - 3][BeginTFx + 3] % 100 <= 9)
			&& ((Board[BeginTFy - 4][BeginTFx + 4] % 100 == BLACK_COLOR) || (Board[BeginTFy - 4][BeginTFx + 4] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginTFy - 5][BeginTFx + 5] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy - 3][BeginTFx + 3] += scope*10;
		}

		//����[��񡡡��]�����
		else if (((Board[BeginTFy - 1][BeginTFx + 1] % 100 == BLACK_COLOR) || (Board[BeginTFy - 1][BeginTFx + 1] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginTFy - 2][BeginTFx + 2] % 100 <= 9)
			&& ((Board[BeginTFy - 3][BeginTFx + 3] % 100 == BLACK_COLOR) || (Board[BeginTFy - 3][BeginTFx + 3] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginTFy - 4][BeginTFx + 4] % 100 == BLACK_COLOR) || (Board[BeginTFy - 4][BeginTFx + 4] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginTFy - 5][BeginTFx + 5] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy - 2][BeginTFx + 2] += scope*10;
		}

		//����[�񡡡���]�����
		else if ((Board[BeginTFy - 1][BeginTFx + 1] % 100 <= 9)
			&& ((Board[BeginTFy - 2][BeginTFx + 2] % 100 == BLACK_COLOR) || (Board[BeginTFy - 2][BeginTFx + 2] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginTFy - 3][BeginTFx + 3] % 100 == BLACK_COLOR) || (Board[BeginTFy - 3][BeginTFx + 3] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginTFy - 4][BeginTFx + 4] % 100 == BLACK_COLOR) || (Board[BeginTFy - 4][BeginTFx + 4] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginTFy - 5][BeginTFx + 5] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy - 1][BeginTFx + 1] += scope*10;
		}


		//////////////////////////////[Begin - 1]���£�[End + 1]δ���� 
		if (((Board[BeginTFy + 2][BeginTFx - 2] == WHITE_COLOR) || (Board[BeginTFy + 2][BeginTFx - 2] == WHITE_COLOR + 1) 
			|| (BeginTFy + 1 == BOARD_SIZE) || (BeginTFx - 1 == 0))
			&& 
			((Board[EndTFy - 1][EndTFx + 1] != WHITE_COLOR) && (Board[EndTFy - 1][EndTFx + 1] != WHITE_COLOR + 1) 
			&& (EndTFy != 0) && (EndTFx != BOARD_SIZE)))
		{
			Board[BeginTFy + 1][BeginTFx - 1] += scope*1;
			Board[EndTFy][EndTFx] += scope*3;
		}


		//[Begin - 1]δ���£�[End + 1]���� 
		else if (((Board[BeginTFy + 2][BeginTFx - 2] != WHITE_COLOR) && (Board[BeginTFy + 2][BeginTFx - 2] != WHITE_COLOR + 1) 
			&& (BeginTFy + 1 != BOARD_SIZE) && (BeginTFx - 1 != 0))
			&& 
			((Board[EndTFy - 1][EndTFx + 1] == WHITE_COLOR) || (Board[EndTFy - 1][EndTFx + 1] == WHITE_COLOR + 1) 
			|| (EndTFy == 0) || (EndTFx == BOARD_SIZE)))
		{
			Board[BeginTFy + 1][BeginTFx - 1] += scope*3;
			Board[EndTFy][EndTFx] += scope*1;
		}

		//[Begin - 1]��[End + 1]������
		else if (((Board[BeginTFy + 2][BeginTFx - 2] == WHITE_COLOR) || (Board[BeginTFy + 2][BeginTFx - 2] == WHITE_COLOR + 1) 
			|| (BeginTFy + 1 == BOARD_SIZE) || (BeginTFx - 1 == 0))
			&& 
			((Board[EndTFy - 1][EndTFx + 1] == WHITE_COLOR) || (Board[EndTFy - 1][EndTFx + 1] == WHITE_COLOR + 1) 
			|| (EndTFy == 0) || (EndTFx == BOARD_SIZE)))
		{
			Board[BeginTFy + 1][BeginTFx - 1] += scope*1;
			Board[EndTFy][EndTFx] += scope*1;
		}

		else
		{
			Board[BeginTFy + 1][BeginTFx - 1] += scope*4;
			Board[EndTFy][EndTFx] += scope*4;
		}
	}


	//begin�˱����Ӷ£�ͬʱ��end���ް��� 
	else if (((Board[BeginTFy + 1][BeginTFx - 1] % 100 == WHITE_COLOR) || (Board[BeginTFy + 1][BeginTFx - 1] % 100 == WHITE_COLOR + 1)
		|| (BeginTFy == BOARD_SIZE) || (BeginTFx == 0)) 
		&& 
		((Board[EndTFy][EndTFx] % 100 <= 9) && (0 < EndTFy + 1) && (EndTFx - 1 < BOARD_SIZE))) 
	{
		//����[�񡡡�]�����
		if ((Board[BeginTFy - 1][BeginTFx + 1] % 100 <= 9)
			&& ((Board[BeginTFy - 2][BeginTFx + 2] % 100 == BLACK_COLOR) || (Board[BeginTFy - 2][BeginTFx + 2] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginTFy - 3][BeginTFx + 3] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy][BeginTFx + 1] += scope*2;
		}

		//����[��񡡡�]�����
		else if (((Board[BeginTFy - 1][BeginTFx + 1] % 100 == BLACK_COLOR) || (Board[BeginTFy - 1][BeginTFx + 1] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginTFy - 2][BeginTFx + 2] % 100 <= 9) 
			&& ((Board[BeginTFy - 3][BeginTFx + 3] % 100 == BLACK_COLOR) || (Board[BeginTFy - 3][BeginTFx + 3] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginTFy - 4][BeginTFx + 4] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy - 2][BeginTFx + 2] += scope*2;
		}

		//����[�񡡡��]�����
		else if ((Board[BeginTFy - 1][BeginTFx + 1] % 100 <= 9)
			&& ((Board[BeginTFy - 2][BeginTFx + 2] % 100 == BLACK_COLOR) || (Board[BeginTFy - 2][BeginTFx + 2] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginTFy - 3][BeginTFx + 3] % 100 == BLACK_COLOR) || (Board[BeginTFy - 3][BeginTFx + 3] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginTFy - 4][BeginTFx + 4] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy - 1][BeginTFx + 1] += scope*2;
		}

		//����[���񡡡�]�����
		else if (((Board[BeginTFy - 1][BeginTFx + 1] % 100 == BLACK_COLOR) || (Board[BeginTFy - 1][BeginTFx + 1] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginTFy - 2][BeginTFx + 2] % 100 == BLACK_COLOR) || (Board[BeginTFy - 2][BeginTFx + 2] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginTFy - 3][BeginTFx + 3] % 100 <= 9)
			&& ((Board[BeginTFy - 4][BeginTFx + 4] % 100 == BLACK_COLOR) || (Board[BeginTFy - 4][BeginTFx + 4] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginTFy - 5][BeginTFx + 5] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy - 3][BeginTFx + 3] += scope*10;
		}

		//����[��񡡡��]�����
		else if (((Board[BeginTFy - 1][BeginTFx + 1] % 100 == BLACK_COLOR) || (Board[BeginTFy - 1][BeginTFx + 1] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginTFy - 2][BeginTFx + 2] % 100 <= 9)
			&& ((Board[BeginTFy - 3][BeginTFx + 3] % 100 == BLACK_COLOR) || (Board[BeginTFy - 3][BeginTFx + 3] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginTFy - 4][BeginTFx + 4] % 100 == BLACK_COLOR) || (Board[BeginTFy - 4][BeginTFx + 4] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginTFy - 5][BeginTFx + 5] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy - 2][BeginTFx + 2] += scope*10;
		}

		//����[�񡡡���]�����
		else if ((Board[BeginTFy - 1][BeginTFx + 1] % 100 <= 9)
			&& ((Board[BeginTFy - 2][BeginTFx + 2] % 100 == BLACK_COLOR) || (Board[BeginTFy - 2][BeginTFx + 2] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginTFy - 3][BeginTFx + 3] % 100 == BLACK_COLOR) || (Board[BeginTFy - 3][BeginTFx + 3] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginTFy - 4][BeginTFx + 4] % 100 == BLACK_COLOR) || (Board[BeginTFy - 4][BeginTFx + 4] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginTFy - 5][BeginTFx + 5] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy - 1][BeginTFx + 1] += scope*10;
		}


		//[End + 1]������ 
		if ((Board[EndTFy - 1][EndTFx + 1] == WHITE_COLOR) || (Board[EndTFy - 1][EndTFx + 1] == WHITE_COLOR + 1) 
			|| (EndTFy == 0) || (EndTFx == BOARD_SIZE))
		{
			Board[EndTFy][EndTFx] += scope*1;
		}

		else
		{
			Board[EndTFy][EndTFx] += scope*2;
		}
	}


	//begin���ް��ӣ�ͬʱ��end�˱����Ӷ� 
	else if (((Board[BeginTFy + 1][BeginTFx - 1] % 100 <= 9) && (BeginTFy < BOARD_SIZE) && (0 < BeginTFx)) 
		&& 
		((Board[EndTFy][EndTFx] % 100 == WHITE_COLOR) || (Board[EndTFy][EndTFx] % 100 == WHITE_COLOR + 1)
		|| (EndTFy + 1 == 0) || (EndTFx - 1 == BOARD_SIZE))) 
	{
		//����[�񡡡�]�����
		if ((Board[BeginTFy - 1][BeginTFx + 1] % 100 <= 9)
			&& ((Board[BeginTFy - 2][BeginTFx + 2] % 100 == BLACK_COLOR) || (Board[BeginTFy - 2][BeginTFx + 2] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginTFy - 3][BeginTFx + 3] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy - 1][BeginTFx + 1] += scope*2;
		}

		//����[��񡡡�]�����
		else if (((Board[BeginTFy - 1][BeginTFx + 1] % 100 == BLACK_COLOR) || (Board[BeginTFy - 1][BeginTFx + 1] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginTFy - 2][BeginTFx + 2] % 100 <= 9) 
			&& ((Board[BeginTFy - 3][BeginTFx + 3] % 100 == BLACK_COLOR) || (Board[BeginTFy - 3][BeginTFx + 3] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginTFy - 4][BeginTFx + 4] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy - 2][BeginTFx + 2] += scope*2;
		}

		//����[�񡡡��]�����
		else if ((Board[BeginTFy - 1][BeginTFx + 1] % 100 <= 9)
			&& ((Board[BeginTFy - 2][BeginTFx + 2] % 100 == BLACK_COLOR) || (Board[BeginTFy - 2][BeginTFx + 2] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginTFy - 3][BeginTFx + 3] % 100 == BLACK_COLOR) || (Board[BeginTFy - 3][BeginTFx + 3] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginTFy - 4][BeginTFx + 4] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy - 1][BeginTFx + 1] += scope*2;
		}

		//����[���񡡡�]�����
		else if (((Board[BeginTFy - 1][BeginTFx + 1] % 100 == BLACK_COLOR) || (Board[BeginTFy - 1][BeginTFx + 1] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginTFy - 2][BeginTFx + 2] % 100 == BLACK_COLOR) || (Board[BeginTFy - 2][BeginTFx + 2] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginTFy - 3][BeginTFx + 3] % 100 <= 9)
			&& ((Board[BeginTFy - 4][BeginTFx + 4] % 100 == BLACK_COLOR) || (Board[BeginTFy - 4][BeginTFx + 4] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginTFy - 5][BeginTFx + 5] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy - 3][BeginTFx + 3] += scope*10;
		}

		//����[��񡡡��]�����
		else if (((Board[BeginTFy - 1][BeginTFx + 1] % 100 == BLACK_COLOR) || (Board[BeginTFy - 1][BeginTFx + 1] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginTFy - 2][BeginTFx + 2] % 100 <= 9)
			&& ((Board[BeginTFy - 3][BeginTFx + 3] % 100 == BLACK_COLOR) || (Board[BeginTFy - 3][BeginTFx + 3] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginTFy - 4][BeginTFx + 4] % 100 == BLACK_COLOR) || (Board[BeginTFy - 4][BeginTFx + 4] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginTFy - 5][BeginTFx + 5] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy - 2][BeginTFx + 2] += scope*10;
		}

		//����[�񡡡���]�����
		else if ((Board[BeginTFy - 1][BeginTFx + 1] % 100 <= 9)
			&& ((Board[BeginTFy - 2][BeginTFx + 2] % 100 == BLACK_COLOR) || (Board[BeginTFy - 2][BeginTFx + 2] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginTFy - 3][BeginTFx + 3] % 100 == BLACK_COLOR) || (Board[BeginTFy - 3][BeginTFx + 3] % 100 == BLACK_COLOR + 1))
			&& ((Board[BeginTFy - 4][BeginTFx + 4] % 100 == BLACK_COLOR) || (Board[BeginTFy - 4][BeginTFx + 4] % 100 == BLACK_COLOR + 1))
			&& (Board[BeginTFy - 5][BeginTFx + 5] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy - 1][BeginTFx + 1] += scope*10;
		}


		//////[Begin - 1]������ 
		if ((Board[BeginTFy + 2][BeginTFx - 2] == WHITE_COLOR) || (Board[BeginTFy + 2][BeginTFx - 2] == WHITE_COLOR + 1) 
			|| (BeginTFy + 1 == BOARD_SIZE) || (BeginTFx - 1 == 0))
		{
			Board[BeginTFy + 1][BeginTFx - 1] += scope*1;
		}

		else
		{
			Board[BeginTFy + 1][BeginTFx - 1] += scope*2;
		}
	}
}


//�������޷�չ�����ֱ���
void getScope_TF_White(int Line, int Column, int BeginTFx, int BeginTFy, int EndTFx, int EndTFy, int scope) 
{
	//���˶������Ӷ���
	if (((Board[BeginTFy + 1][BeginTFx - 1] % 100 == BLACK_COLOR) || (Board[BeginTFy + 1][BeginTFx - 1] % 100 == BLACK_COLOR + 1)
		|| (BeginTFy == BOARD_SIZE) || (BeginTFx == 0))
		&& 
		((Board[EndTFy][EndTFx] % 100 == BLACK_COLOR) || (Board[EndTFy][EndTFx] % 100 == BLACK_COLOR + 1)
		|| (EndTFy + 1 == 0) || (EndTFx - 1 == BOARD_SIZE)))
	{
		//����[�򡡡�]�����
		if ((Board[BeginTFy - 1][BeginTFx + 1] % 100 <= 9)
			&& ((Board[BeginTFy - 2][BeginTFx + 2] % 100 == WHITE_COLOR) || (Board[BeginTFy - 2][BeginTFx + 2] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginTFy - 3][BeginTFx + 3] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy - 1][BeginTFx + 1] += scope*1;
		}

		//����[��򡡡�]�����
		else if (((Board[BeginTFy - 1][BeginTFx + 1] % 100 == WHITE_COLOR) || (Board[BeginTFy - 1][BeginTFx + 1] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginTFy - 2][BeginTFx + 2] % 100 <= 9) 
			&& ((Board[BeginTFy - 3][BeginTFx + 3] % 100 == WHITE_COLOR) || (Board[BeginTFy - 3][BeginTFx + 3] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginTFy - 4][BeginTFx + 4] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy - 2][BeginTFx + 2] += scope*1;
		}

		//����[�򡡡��]�����
		else if ((Board[BeginTFy - 1][BeginTFx + 1] % 100 <= 9)
			&& ((Board[BeginTFy - 2][BeginTFx + 2] % 100 == WHITE_COLOR) || (Board[BeginTFy - 2][BeginTFx + 2] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginTFy - 3][BeginTFx + 3] % 100 == WHITE_COLOR) || (Board[BeginTFy - 3][BeginTFx + 3] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginTFy - 4][BeginTFx + 4] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy - 1][BeginTFx + 1] += scope*1;
		}

		//����[���򡡡�]�����
		else if (((Board[BeginTFy - 1][BeginTFx + 1] % 100 == WHITE_COLOR) || (Board[BeginTFy - 1][BeginTFx + 1] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginTFy - 2][BeginTFx + 2] % 100 == WHITE_COLOR) || (Board[BeginTFy - 2][BeginTFx + 2] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginTFy - 3][BeginTFx + 3] % 100 <= 9)
			&& ((Board[BeginTFy - 4][BeginTFx + 4] % 100 == WHITE_COLOR) || (Board[BeginTFy - 4][BeginTFx + 4] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginTFy - 5][BeginTFx + 5] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy - 3][BeginTFx + 3] += scope*10;
		}

		//����[��򡡡��]�����
		else if (((Board[BeginTFy - 1][BeginTFx + 1] % 100 == WHITE_COLOR) || (Board[BeginTFy - 1][BeginTFx + 1] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginTFy - 2][BeginTFx + 2] % 100 <= 9)
			&& ((Board[BeginTFy - 3][BeginTFx + 3] % 100 == WHITE_COLOR) || (Board[BeginTFy - 3][BeginTFx + 3] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginTFy - 4][BeginTFx + 4] % 100 == WHITE_COLOR) || (Board[BeginTFy - 4][BeginTFx + 4] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginTFy - 5][BeginTFx + 5] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy - 2][BeginTFx + 2] += scope*10;
		}

		//����[�򡡡���]�����
		else if ((Board[BeginTFy - 1][BeginTFx + 1] % 100 <= 9)
			&& ((Board[BeginTFy - 2][BeginTFx + 2] % 100 == WHITE_COLOR) || (Board[BeginTFy - 2][BeginTFx + 2] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginTFy - 3][BeginTFx + 3] % 100 == WHITE_COLOR) || (Board[BeginTFy - 3][BeginTFx + 3] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginTFy - 4][BeginTFx + 4] % 100 == WHITE_COLOR) || (Board[BeginTFy - 4][BeginTFx + 4] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginTFy - 5][BeginTFx + 5] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy - 1][BeginTFx + 1] += scope*10;
		}

		return;
	}


	//���˾��޺���(==����û���ӣ���Ϊֻ�к��ӡ����ӡ�������״̬�����к��ӣ����ͳ�����Ӵ����Ӹ���)
	else if ((Board[BeginTFy + 1][BeginTFx - 1] % 100 <= 9) && (Board[EndTFy][EndTFx] % 100 <= 9)
		&& (BeginTFy < BOARD_SIZE) && (0 < BeginTFx) && (0 < EndTFy + 1) && (EndTFx - 1 < BOARD_SIZE))
	{
		//����[�򡡡�]�����
		if ((Board[BeginTFy - 1][BeginTFx + 1] % 100 <= 9)
			&& ((Board[BeginTFy - 2][BeginTFx + 2] % 100 == WHITE_COLOR) || (Board[BeginTFy - 2][BeginTFx + 2] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginTFy - 3][BeginTFx + 3] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy - 1][BeginTFx + 1] += scope*4;
		}

		//����[��򡡡�]�����
		else if (((Board[BeginTFy - 1][BeginTFx + 1] % 100 == WHITE_COLOR) || (Board[BeginTFy - 1][BeginTFx + 1] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginTFy - 2][BeginTFx + 2] % 100 <= 9)  
			&& ((Board[BeginTFy - 3][BeginTFx + 3] % 100 == WHITE_COLOR) || (Board[BeginTFy - 3][BeginTFx + 3] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginTFy - 4][BeginTFx + 4] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy - 2][BeginTFx + 2] += scope*4;
		}

		//����[�򡡡��]�����
		else if ((Board[BeginTFy - 1][BeginTFx + 1] % 100 <= 9)
			&& ((Board[BeginTFy - 2][BeginTFx + 2] % 100 == WHITE_COLOR) || (Board[BeginTFy - 2][BeginTFx + 2] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginTFy - 3][BeginTFx + 3] % 100 == WHITE_COLOR) || (Board[BeginTFy - 3][BeginTFx + 3] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginTFy - 4][BeginTFx + 4] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy - 1][BeginTFx + 1] += scope*4;
		}

		//����[���򡡡�]�����
		else if (((Board[BeginTFy - 1][BeginTFx + 1] % 100 == WHITE_COLOR) || (Board[BeginTFy - 1][BeginTFx + 1] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginTFy - 2][BeginTFx + 2] % 100 == WHITE_COLOR) || (Board[BeginTFy - 2][BeginTFx + 2] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginTFy - 3][BeginTFx + 3] % 100 <= 9)
			&& ((Board[BeginTFy - 4][BeginTFx + 4] % 100 == WHITE_COLOR) || (Board[BeginTFy - 4][BeginTFx + 4] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginTFy - 5][BeginTFx + 5] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy - 3][BeginTFx + 3] += scope*10;
		}

		//����[��򡡡��]�����
		else if (((Board[BeginTFy - 1][BeginTFx + 1] % 100 == WHITE_COLOR) || (Board[BeginTFy - 1][BeginTFx + 1] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginTFy - 2][BeginTFx + 2] % 100 <= 9)
			&& ((Board[BeginTFy - 3][BeginTFx + 3] % 100 == WHITE_COLOR) || (Board[BeginTFy - 3][BeginTFx + 3] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginTFy - 4][BeginTFx + 4] % 100 == WHITE_COLOR) || (Board[BeginTFy - 4][BeginTFx + 4] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginTFy - 5][BeginTFx + 5] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy - 2][BeginTFx + 2] += scope*10;
		}

		//����[�򡡡���]�����
		else if ((Board[BeginTFy - 1][BeginTFx + 1] % 100 <= 9)
			&& ((Board[BeginTFy - 2][BeginTFx + 2] % 100 == WHITE_COLOR) || (Board[BeginTFy - 2][BeginTFx + 2] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginTFy - 3][BeginTFx + 3] % 100 == WHITE_COLOR) || (Board[BeginTFy - 3][BeginTFx + 3] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginTFy - 4][BeginTFx + 4] % 100 == WHITE_COLOR) || (Board[BeginTFy - 4][BeginTFx + 4] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginTFy - 5][BeginTFx + 5] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy - 1][BeginTFx + 1] += scope*10;
		}


		//////////////////////////////[Begin - 1]���£�[End + 1]δ���� 
		if (((Board[BeginTFy + 2][BeginTFx - 2] == BLACK_COLOR) || (Board[BeginTFy + 2][BeginTFx - 2] == BLACK_COLOR + 1) 
			|| (BeginTFy + 1 == BOARD_SIZE) || (BeginTFx - 1 == 0))
			&& 
			((Board[EndTFy - 1][EndTFx + 1] != BLACK_COLOR) && (Board[EndTFy - 1][EndTFx + 1] != BLACK_COLOR + 1) 
			&& (EndTFy != 0) && (EndTFx != BOARD_SIZE)))
		{
			Board[BeginTFy + 1][BeginTFx - 1] += scope*1;
			Board[EndTFy][EndTFx] += scope*3;
		}


		//[Begin - 1]δ���£�[End + 1]���� 
		else if (((Board[BeginTFy + 2][BeginTFx - 2] != BLACK_COLOR) && (Board[BeginTFy + 2][BeginTFx - 2] != BLACK_COLOR + 1) 
			&& (BeginTFy + 1 != BOARD_SIZE) && (BeginTFx - 1 != 0))
			&& 
			((Board[EndTFy - 1][EndTFx + 1] == BLACK_COLOR) || (Board[EndTFy - 1][EndTFx + 1] == BLACK_COLOR + 1) 
			|| (EndTFy == 0) || (EndTFx == BOARD_SIZE)))
		{
			Board[BeginTFy + 1][BeginTFx - 1] += scope*3;
			Board[EndTFy][EndTFx] += scope*1;
		}

		//[Begin - 1]��[End + 1]������
		else if (((Board[BeginTFy + 2][BeginTFx - 2] == BLACK_COLOR) || (Board[BeginTFy + 2][BeginTFx - 2] == BLACK_COLOR + 1) 
			|| (BeginTFy + 1 == BOARD_SIZE) || (BeginTFx - 1 == 0))
			&& 
			((Board[EndTFy - 1][EndTFx + 1] == BLACK_COLOR) || (Board[EndTFy - 1][EndTFx + 1] == BLACK_COLOR + 1) 
			|| (EndTFy == 0) || (EndTFx == BOARD_SIZE)))
		{
			Board[BeginTFy + 1][BeginTFx - 1] += scope*1;
			Board[EndTFy][EndTFx] += scope*1;
		}

		else
		{
			Board[BeginTFy + 1][BeginTFx - 1] += scope*4;
			Board[EndTFy][EndTFx] += scope*4;
		}
	}


	//begin�˱����Ӷ£�ͬʱ��end���޺��� 
	else if (((Board[BeginTFy + 1][BeginTFx - 1] % 100 == BLACK_COLOR) || (Board[BeginTFy + 1][BeginTFx - 1] % 100 == BLACK_COLOR + 1)
		|| (BeginTFy == BOARD_SIZE) || (BeginTFx == 0)) 
		&& 
		((Board[EndTFy][EndTFx] % 100 <= 9) && (0 < EndTFy + 1) && (EndTFx - 1 < BOARD_SIZE))) 
	{
		//����[�򡡡�]�����
		if ((Board[BeginTFy - 1][BeginTFx + 1] % 100 <= 9)
			&& ((Board[BeginTFy - 2][BeginTFx + 2] % 100 == WHITE_COLOR) || (Board[BeginTFy - 2][BeginTFx + 2] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginTFy - 3][BeginTFx + 3] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy][BeginTFx + 1] += scope*2;
		}

		//����[��򡡡�]�����
		else if (((Board[BeginTFy - 1][BeginTFx + 1] % 100 == WHITE_COLOR) || (Board[BeginTFy - 1][BeginTFx + 1] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginTFy - 2][BeginTFx + 2] % 100 <= 9) 
			&& ((Board[BeginTFy - 3][BeginTFx + 3] % 100 == WHITE_COLOR) || (Board[BeginTFy - 3][BeginTFx + 3] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginTFy - 4][BeginTFx + 4] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy - 2][BeginTFx + 2] += scope*2;
		}

		//����[�򡡡��]�����
		else if ((Board[BeginTFy - 1][BeginTFx + 1] % 100 <= 9)
			&& ((Board[BeginTFy - 2][BeginTFx + 2] % 100 == WHITE_COLOR) || (Board[BeginTFy - 2][BeginTFx + 2] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginTFy - 3][BeginTFx + 3] % 100 == WHITE_COLOR) || (Board[BeginTFy - 3][BeginTFx + 3] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginTFy - 4][BeginTFx + 4] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy - 1][BeginTFx + 1] += scope*2;
		}

		//����[���򡡡�]�����
		else if (((Board[BeginTFy - 1][BeginTFx + 1] % 100 == WHITE_COLOR) || (Board[BeginTFy - 1][BeginTFx + 1] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginTFy - 2][BeginTFx + 2] % 100 == WHITE_COLOR) || (Board[BeginTFy - 2][BeginTFx + 2] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginTFy - 3][BeginTFx + 3] % 100 <= 9)
			&& ((Board[BeginTFy - 4][BeginTFx + 4] % 100 == WHITE_COLOR) || (Board[BeginTFy - 4][BeginTFx + 4] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginTFy - 5][BeginTFx + 5] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy - 3][BeginTFx + 3] += scope*10;
		}

		//����[��򡡡��]�����
		else if (((Board[BeginTFy - 1][BeginTFx + 1] % 100 == WHITE_COLOR) || (Board[BeginTFy - 1][BeginTFx + 1] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginTFy - 2][BeginTFx + 2] % 100 <= 9)
			&& ((Board[BeginTFy - 3][BeginTFx + 3] % 100 == WHITE_COLOR) || (Board[BeginTFy - 3][BeginTFx + 3] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginTFy - 4][BeginTFx + 4] % 100 == WHITE_COLOR) || (Board[BeginTFy - 4][BeginTFx + 4] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginTFy - 5][BeginTFx + 5] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy - 2][BeginTFx + 2] += scope*10;
		}

		//����[�򡡡���]�����
		else if ((Board[BeginTFy - 1][BeginTFx + 1] % 100 <= 9)
			&& ((Board[BeginTFy - 2][BeginTFx + 2] % 100 == WHITE_COLOR) || (Board[BeginTFy - 2][BeginTFx + 2] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginTFy - 3][BeginTFx + 3] % 100 == WHITE_COLOR) || (Board[BeginTFy - 3][BeginTFx + 3] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginTFy - 4][BeginTFx + 4] % 100 == WHITE_COLOR) || (Board[BeginTFy - 4][BeginTFx + 4] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginTFy - 5][BeginTFx + 5] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy - 1][BeginTFx + 1] += scope*10;
		}



		//[End + 1]������ 
		if ((Board[EndTFy - 1][EndTFx + 1] == BLACK_COLOR) || (Board[EndTFy - 1][EndTFx + 1] == BLACK_COLOR + 1) 
			|| (EndTFy == 0) || (EndTFx == BOARD_SIZE))
		{
			Board[EndTFy][EndTFx] += scope*1;
		}

		else
		{
			Board[EndTFy][EndTFx] += scope*2;
		}
	}


	//begin���޺��ӣ�ͬʱ��end�˱����Ӷ� 
	else if (((Board[BeginTFy + 1][BeginTFx - 1] % 100 <= 9) && (BeginTFy < BOARD_SIZE) && (0 < BeginTFx)) 
		&& 
		((Board[EndTFy][EndTFx] % 100 == BLACK_COLOR) || (Board[EndTFy][EndTFx] % 100 == BLACK_COLOR + 1)
		|| (EndTFy + 1 == 0) || (EndTFx - 1 == BOARD_SIZE))) 
	{
		//����[�򡡡�]�����
		if ((Board[BeginTFy - 1][BeginTFx + 1] % 100 <= 9)
			&& ((Board[BeginTFy - 2][BeginTFx + 2] % 100 == WHITE_COLOR) || (Board[BeginTFy - 2][BeginTFx + 2] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginTFy - 3][BeginTFx + 3] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy - 1][BeginTFx + 1] += scope*2;
		}

		//����[��򡡡�]�����
		else if (((Board[BeginTFy - 1][BeginTFx + 1] % 100 == WHITE_COLOR) || (Board[BeginTFy - 1][BeginTFx + 1] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginTFy - 2][BeginTFx + 2] % 100 <= 9) 
			&& ((Board[BeginTFy - 3][BeginTFx + 3] % 100 == WHITE_COLOR) || (Board[BeginTFy - 3][BeginTFx + 3] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginTFy - 4][BeginTFx + 4] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy - 2][BeginTFx + 2] += scope*2;
		}

		//����[�򡡡��]�����
		else if ((Board[BeginTFy - 1][BeginTFx + 1] % 100 <= 9)
			&& ((Board[BeginTFy - 2][BeginTFx + 2] % 100 == WHITE_COLOR) || (Board[BeginTFy - 2][BeginTFx + 2] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginTFy - 3][BeginTFx + 3] % 100 == WHITE_COLOR) || (Board[BeginTFy - 3][BeginTFx + 3] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginTFy - 4][BeginTFx + 4] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy - 1][BeginTFx + 1] += scope*2;
		}

		//����[���򡡡�]�����
		else if (((Board[BeginTFy - 1][BeginTFx + 1] % 100 == WHITE_COLOR) || (Board[BeginTFy - 1][BeginTFx + 1] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginTFy - 2][BeginTFx + 2] % 100 == WHITE_COLOR) || (Board[BeginTFy - 2][BeginTFx + 2] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginTFy - 3][BeginTFx + 3] % 100 <= 9)
			&& ((Board[BeginTFy - 4][BeginTFx + 4] % 100 == WHITE_COLOR) || (Board[BeginTFy - 4][BeginTFx + 4] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginTFy - 5][BeginTFx + 5] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy - 3][BeginTFx + 3] += scope*10;
		}

		//����[��򡡡��]�����
		else if (((Board[BeginTFy - 1][BeginTFx + 1] % 100 == WHITE_COLOR) || (Board[BeginTFy - 1][BeginTFx + 1] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginTFy - 2][BeginTFx + 2] % 100 <= 9)
			&& ((Board[BeginTFy - 3][BeginTFx + 3] % 100 == WHITE_COLOR) || (Board[BeginTFy - 3][BeginTFx + 3] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginTFy - 4][BeginTFx + 4] % 100 == WHITE_COLOR) || (Board[BeginTFy - 4][BeginTFx + 4] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginTFy - 5][BeginTFx + 5] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy - 2][BeginTFx + 2] += scope*10;
		}

		//����[�򡡡���]�����
		else if ((Board[BeginTFy - 1][BeginTFx + 1] % 100 <= 9)
			&& ((Board[BeginTFy - 2][BeginTFx + 2] % 100 == WHITE_COLOR) || (Board[BeginTFy - 2][BeginTFx + 2] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginTFy - 3][BeginTFx + 3] % 100 == WHITE_COLOR) || (Board[BeginTFy - 3][BeginTFx + 3] % 100 == WHITE_COLOR + 1))
			&& ((Board[BeginTFy - 4][BeginTFx + 4] % 100 == WHITE_COLOR) || (Board[BeginTFy - 4][BeginTFx + 4] % 100 == WHITE_COLOR + 1))
			&& (Board[BeginTFy - 5][BeginTFx + 5] % 100 == Board[EndTFy][EndTFx] % 100))
		{
			Board[BeginTFy - 1][BeginTFx + 1] += scope*10;
		}


		//////[Begin - 1]������ 
		if ((Board[BeginTFy + 2][BeginTFx - 2] == BLACK_COLOR) || (Board[BeginTFy + 2][BeginTFx - 2] == BLACK_COLOR + 1) 
			|| (BeginTFy + 1 == BOARD_SIZE) || (BeginTFx - 1 == 0))
		{
			Board[BeginTFy + 1][BeginTFx - 1] += scope*1;
		}

		else
		{
			Board[BeginTFy + 1][BeginTFx - 1] += scope*2;
		}
	}
}


void WhoIsWinning()
{
	int x = 0, y = 0; //���̵ĺ�������

	CleanScore();

	WhoIsWin_Horizon(); // һ��һ��ѭ���ж�

	WhoIsWin_Vertical(); // һ��һ��ѭ���ж�

	WhoIsWin_OneThreeQuadrant(); // һ������ѭ���жϣ���д��

	WhoIsWin_TwoFourQuadrant(); // ��������ѭ���жϣ���д��
}


//ˮƽ�����ж���Ӯ
void WhoIsWin_Horizon()
{
	int x = 0, y = 0; //���̵ĺ�������

	for(y = 0; y <= BOARD_SIZE; y++)
	{
		//"BeginH = EndH + 1"�����������������
		for (BeginH = 0, EndH = 0; (BeginH <= BOARD_SIZE) && (EndH <= BOARD_SIZE); BeginH = EndH + 1)
		{
			count = ChessCount_H(y, BLACK_COLOR);

			//���ֵĹ涨���ڷ����������ͬʱ�γɣ�����ʧЧ���ڷ�ʤ�����ԣ�ֻҪ������������ֶ����뿼��
			if (count == 5)
			{
				printf("�����ʤ��\n");
				GameOver();
			}

			Score_H(y, count, BLACK_COLOR);//����ԭ�򣺷�ֹ�жϽ��ֺ󣬽�������countֵ��Ϊ���ֵ�countֵ������û�а�������������ֵ���
		}


		//�ж��������ֵ�˼·��
		//******* 1����򵥵������������Σ�����2�����������������ӣ��Һ���һ������ͬʱ�γ��������������ӱ���Ϊ����������ͬ�Ĺ����ӡ�
		//******* 2�����ԣ�ֻ�����ж�����1���������Ƿ��������ӣ����У����漴�ж�(yBlack, xBlack)���ڵ��������������Ƿ��������ӡ�
		//******* 3����Ϊ���������˳��������-����-��һ��-����ķ���ͳ����������
		//******* 4������ֻ������һ��һ���жϵ��ص㣬���жϳ�1�����������������Ӻ������ж�����3�������Ƿ��������Ӽ��ɡ�


		//��֤(yBlack, xBlack)���������ֵĵ�һ����
		if (EndH - 1 <= BOARD_SIZE)
		{
			BeginH = xBlack - 4;
			EndH = xBlack - 4;

			count = ChessCount_H(yBlack, BLACK_COLOR); //����������

			//���������ӵ����˾��ް��ӣ��Ҳ��������̱�Ե
			if ((count == 3)
				&& (Board[yBlack][BeginH - 1] % 100 != WHITE_COLOR) 
				&& (Board[yBlack][BeginH - 1] % 100 != WHITE_COLOR + 1)
				&& (Board[yBlack][EndH] % 100 != WHITE_COLOR) 
				&& (Board[yBlack][EndH] % 100 != WHITE_COLOR + 1)
				&& (BeginH != 0) && (BeginH != BOARD_SIZE) 
				&& (EndH - 1 != 0) && (EndH - 1 != BOARD_SIZE) 
				&& (yBlack != 0) && (yBlack != BOARD_SIZE)) 
			{
				BanHand_3_Vertical(y); //��ֱ����x++��y++���жϺ������

				BanHand_3_OneThreeQuadrant(x, y); //һ�����޷���x++��y++���жϺ������

				BanHand_3_TwoFourQuadrant(x, y); //�������޷���x++��y--���жϺ������
			}

			else if ((count == 4)
				&& 
				(((Board[yBlack][BeginH - 1] % 100 != WHITE_COLOR) 
				&& (Board[yBlack][BeginH - 1] % 100 != WHITE_COLOR + 1))
				|| 
				((Board[yBlack][EndH] % 100 != WHITE_COLOR) 
				&& (Board[yBlack][EndH] % 100 != WHITE_COLOR + 1))))
			{
				BanHand_4_Vertical(y); //��ֱ����x++��y++���жϺ������

				BanHand_4_OneThreeQuadrant(x, y); //һ�����޷���x++��y++���жϺ������

				BanHand_4_TwoFourQuadrant(x, y); //�������޷���x++��y--���жϺ������
			}

			else if (count > 5)
			{
				printf("���峤���������ʤ��\n");
				GameOver();
			}

			else
			{
				continue;
			}
		}
	}

	for(y = 0; y <= BOARD_SIZE; y++)
	{
		//"BeginH = EndH + 1"�����������������
		for (BeginH = 0, EndH = 0; (BeginH <= BOARD_SIZE) && (EndH <= BOARD_SIZE); BeginH = EndH + 1)
		{
			count = ChessCount_H(y, WHITE_COLOR);
			if (count == 5)
			{					
				printf("�����ʤ��\n");
				GameOver();
			}
			Score_H(y, count, WHITE_COLOR);
		}
	}
}


//��ֱ�����ж���Ӯ
void WhoIsWin_Vertical()
{
	int x = 0, y = 0; //���̵ĺ�������

	for(x = 0; x <= BOARD_SIZE; x++)
	{
		//[BeginV = EndV + 1]:���㵱ǰ�е�����������ĺ���������
		for (BeginV = 0, EndV = 0; (BeginV <= BOARD_SIZE) && (EndV <= BOARD_SIZE); BeginV = EndV + 1)
		{
			count = ChessCount_V(x, BLACK_COLOR);


			if (count == 5) //�ڷ����������ͬʱ�γɣ�����ʧЧ���ڷ�ʤ����Ϸ����
			{					
				printf("�����ʤ��\n");
				GameOver();
			}
			//����ԭ�򣺷�ֹ�жϽ��ֺ󣬽�������countֵ��Ϊ���ֵ�countֵ������û�а�������������ֵ���
			Score_V(x, count, BLACK_COLOR);
		}

		//��֤(yBlack, xBlack)���������ֵĵ�һ����
		if (EndV - 1 <= BOARD_SIZE)
		{
			BeginV = yBlack - 4;
			EndV = yBlack - 4;

			count = ChessCount_V(xBlack, BLACK_COLOR);

			//���������ӵ����˾��ް��ӣ��Ҳ��������̱�Ե���ڶ���������
			//�����һ������(yBlack, xBlack)�����������Ľ��㴦
			if ((count == 3)
				&& (Board[BeginV - 1][xBlack] % 100 != WHITE_COLOR) 
				&& (Board[BeginV - 1][xBlack] % 100 != WHITE_COLOR + 1)
				&& (Board[EndV][xBlack] % 100 != WHITE_COLOR) 
				&& (Board[EndV][xBlack] % 100 != WHITE_COLOR + 1)
				&& (BeginV != 0) && (BeginV != BOARD_SIZE) 
				&& (EndV - 1 != 0) && (EndV - 1 != BOARD_SIZE) 
				&& (xBlack != 0) && (xBlack != BOARD_SIZE)) 
			{
				BanHand_3_Horizon(x); //ˮƽ����x++��y++���жϺ������

				BanHand_3_OneThreeQuadrant(x, y); //һ�����޷���x++��y++���жϺ������

				BanHand_3_TwoFourQuadrant(x, y); //�������޷���x++��y--���жϺ������
			}

			else if ((count == 4)
				&& 
				(((Board[BeginV - 1][xBlack] % 100 != WHITE_COLOR) 
				&& (Board[BeginV - 1][xBlack] % 100 != WHITE_COLOR + 1))
				|| 
				((Board[EndV][xBlack] % 100 != WHITE_COLOR) 
				&& (Board[EndV][xBlack] % 100 != WHITE_COLOR + 1))))
			{
				BanHand_4_Horizon(x); //ˮƽ����x++��y++���жϺ������

				BanHand_4_OneThreeQuadrant(x, y); //һ�����޷���x++��y++���жϺ������

				BanHand_4_TwoFourQuadrant(x, y); //�������޷���x++��y--���жϺ������
			}

			else if (count > 5)
			{
				printf("���峤���������ʤ��\n");
				GameOver();
			}

			else
			{
				continue;
			}
		}
	}



	for(x = 0; x <= BOARD_SIZE; x++)
	{
		//"BeginV = EndV + 1"�����������������
		for (BeginV = 0, EndV = 0; (BeginV <= BOARD_SIZE) && (EndV <= BOARD_SIZE); BeginV = EndV + 1)
		{
			count = ChessCount_V(x, WHITE_COLOR);
			if (count == 5)
			{					
				printf("�����ʤ��\n");
				GameOver();
			}
			Score_V(x, count, WHITE_COLOR);
		}
	}
}


//һ�����޷����ж���Ӯ
void WhoIsWin_OneThreeQuadrant() //һ�����޷����ж���Ӯ
{
	int x = 0, y = 0; //���̵ĺ�������

	for(x = -14, y = 0; (x <= BOARD_SIZE) && (0 <= y); x++) //x++��y++������һ�ж�
	{
		for (BeginOTx = x, BeginOTy = y, EndOTx = x, EndOTy = y; 
			(-14 <= BeginOTx) && (BeginOTx <= BOARD_SIZE) 
			&& 
			(-14 <= EndOTx) && (EndOTx <= BOARD_SIZE) 
			&& 
			(0 <= BeginOTy) && (BeginOTy <= BOARD_SIZE)  
			&& 
			(0 <= EndOTy) && (EndOTy <= BOARD_SIZE);
		(BeginOTx = EndOTx + 1), (BeginOTy = EndOTy + 1)) //β���Ƶ�ʼ�����һλ
		{
			count = ChessCount_OT(BeginOTy, BeginOTx, BLACK_COLOR);

			if (count == 5)
			{					
				printf("�����ʤ��\n");
				GameOver();
			}
			//����ԭ�򣺷�ֹ�жϽ��ֺ󣬽�������countֵ��Ϊ���ֵ�countֵ������û�а�������������ֵ��֣��Ӷ�������������߷ִ�
			Score_OT(BeginOTy, BeginOTx, count, BLACK_COLOR);
		}


		if ((EndOTx - 1 <= BOARD_SIZE) && (EndOTy - 1 <= BOARD_SIZE))
		{
			BeginOTx = xBlack - 4; 
			BeginOTy = yBlack - 4; 
			EndOTx = xBlack - 4; 
			EndOTy = yBlack - 4;

			count = ChessCount_OT(BeginOTy, BeginOTx, BLACK_COLOR);

			//һ�����޷��������ӵ����˾��ް��ӣ��Ҳ��������̱�Ե
			if ((count == 3)
				&& (Board[BeginOTy - 1][BeginOTx - 1] % 100 != WHITE_COLOR) 
				&& (Board[BeginOTy - 1][BeginOTx - 1] % 100 != WHITE_COLOR + 1)
				&& (Board[EndOTy][EndOTx] % 100 != WHITE_COLOR) 
				&& (Board[EndOTy][EndOTx] % 100 != WHITE_COLOR + 1)
				&& (BeginOTy != 0) && (BeginOTy != BOARD_SIZE) 
				&& (BeginOTx != 0) && (BeginOTx != BOARD_SIZE)
				&& (EndOTy - 1 != 0) && (EndOTy - 1 != BOARD_SIZE)  
				&& (EndOTx - 1 != 0) && (EndOTx - 1 != BOARD_SIZE))
			{
				BanHand_3_Horizon(x); //ˮƽ����x++��y++���жϺ������

				BanHand_3_Vertical(y); //��ֱ����x++��y++���жϺ������

				BanHand_3_TwoFourQuadrant(x, y); //�������޷���x++��y--���жϺ������
			}

			else if ((count == 4)
				&& 
				(((Board[BeginOTy - 1][BeginOTx - 1] % 100 != WHITE_COLOR) 
				&& (Board[BeginOTy - 1][BeginOTx - 1] % 100 != WHITE_COLOR + 1))
				|| 
				((Board[EndOTy][EndOTx] % 100 != WHITE_COLOR) 
				&& (Board[EndOTy][EndOTx] % 100 != WHITE_COLOR + 1))))
			{
				BanHand_4_Horizon(x); //ˮƽ����x++��y++���жϺ������

				BanHand_4_Vertical(y); //��ֱ����x++��y++���жϺ������

				BanHand_4_TwoFourQuadrant(x, y); //�������޷���x++��y--���жϺ������
			}

			else if (count > 5)
			{
				printf("���峤���������ʤ��\n");
				GameOver();
			}

			else
			{
				continue;
			}
		}
	}


	for(x = -14, y = 0; (x <= BOARD_SIZE) && (y >= 0); x++)
	{
		for (BeginOTx = x, BeginOTy = y, EndOTx = x, EndOTy = y; 
			(-14 <= BeginOTx) && (BeginOTx <= BOARD_SIZE) 
			&& 
			(-14 <= EndOTx) && (EndOTx <= BOARD_SIZE) 
			&& 
			(0 <= BeginOTy) && (BeginOTy <= BOARD_SIZE)  
			&& 
			(0 <= EndOTy) && (EndOTy <= BOARD_SIZE);
		(BeginOTx = EndOTx + 1), (BeginOTy = EndOTy + 1)) //β���Ƶ�ʼ�����һλ
		{
			count = ChessCount_OT(BeginOTy, BeginOTx, WHITE_COLOR);
			if (count == 5)
			{					
				printf("�����ʤ��\n");
				GameOver();
			}

			Score_OT(BeginOTy, BeginOTx, count, WHITE_COLOR);
		}
	}
}


//�������޷����ж���Ӯ
void WhoIsWin_TwoFourQuadrant()
{
	int x = 0, y = 0; //���̵ĺ�������

	for(x = -14, y = BOARD_SIZE; (x <= BOARD_SIZE) && (y >= 0); x++) //x++��y--������һ�ж�
	{
		for (BeginTFx = x, BeginTFy = y, EndTFx = x, EndTFy = y; 
			(-14 <= BeginTFx) && (BeginTFx <= BOARD_SIZE) 
			&& 
			(-14 <= EndTFx) && (EndTFx <= BOARD_SIZE) 
			&& 
			(0 <= BeginTFy) && (BeginTFy <= BOARD_SIZE)
			&& 
			(0 <= EndTFy) && (EndTFy <= BOARD_SIZE);
		(BeginTFx = EndTFx + 1), (BeginTFy = EndTFy - 1)) //β���Ƶ�ʼ�����һλ
		{
			count = ChessCount_TF(BeginTFy, BeginTFx, BLACK_COLOR);

			//�������޷��������ӵ����˾��ް��ӣ��Ҳ��������̱�Ե����һ��������
			if (count == 5)			
			{					
				printf("�����ʤ��\n");
				GameOver();
			}
			//����ԭ�򣺷�ֹ�жϽ��ֺ󣬽�������countֵ��Ϊ���ֵ�countֵ������û�а�������������ֵ��֣��Ӷ�������������߷ִ�
			Score_TF(BeginTFy, BeginTFx, count, BLACK_COLOR);
		}


		if ((EndTFx - 1 <= BOARD_SIZE) && (0 <= EndTFy + 1))
		{
			BeginTFx = xBlack - 4;
			BeginTFy = yBlack + 4;
			EndTFx = xBlack - 4;
			EndTFy = yBlack + 4;

			count = ChessCount_TF(BeginTFy, BeginTFx, BLACK_COLOR);

			//�������޷��������ӵ����˾��ް��ӣ��Ҳ��������̱�Ե
			if ((count == 3) 
				&& (Board[BeginTFy + 1][BeginTFx - 1] % 100 != WHITE_COLOR) 
				&& (Board[BeginTFy + 1][BeginTFx - 1] % 100 != WHITE_COLOR + 1)
				&& (Board[EndTFy][EndTFx] % 100 != WHITE_COLOR) 
				&& (Board[EndTFy][EndTFx] % 100 != WHITE_COLOR + 1)
				&& (BeginTFy != 0) && (BeginTFy != BOARD_SIZE) 
				&& (BeginTFx != 0) && (BeginTFx != BOARD_SIZE)
				&& (EndTFy + 1 != 0) && (EndTFy + 1 != BOARD_SIZE) 
				&& (EndTFx - 1 != 0) && (EndTFx - 1 != BOARD_SIZE))
			{
				BanHand_3_Horizon(x); //ˮƽ����x++��y++���жϺ������

				BanHand_3_Vertical(y); //��ֱ����x++��y++���жϺ������

				BanHand_3_OneThreeQuadrant(x, y); //һ�����޷���x++��y++���жϺ������
			}

			else if ((count == 4) 
				&& 
				(((Board[BeginTFy + 1][BeginTFx - 1] % 100 != WHITE_COLOR) 
				&& (Board[BeginTFy + 1][BeginTFx - 1] % 100 != WHITE_COLOR + 1))
				|| 
				((Board[EndTFy][EndTFx] % 100 != WHITE_COLOR) 
				&& (Board[EndTFy][EndTFx] % 100 != WHITE_COLOR + 1))))
			{
				BanHand_4_Horizon(x); //ˮƽ����x++��y++���жϺ������

				BanHand_4_Vertical(y); //��ֱ����x++��y++���жϺ������

				BanHand_4_OneThreeQuadrant(x, y); //һ�����޷���x++��y++���жϺ������
			}

			else if (count > 5)
			{
				printf("���峤���������ʤ��\n");
				GameOver();
			}

			else
			{
				continue;
			}
		}
	}



	for(x = -14, y = BOARD_SIZE; (x <= BOARD_SIZE) && (y >= 0); x++)
	{
		for (BeginTFx = x, BeginTFy = y, EndTFx = x, EndTFy = y; 
			(-14 <= BeginTFx) && (BeginTFx <= BOARD_SIZE) 
			&& 
			(-14 <= EndTFx) && (EndTFx <= BOARD_SIZE) 
			&& 
			(0 <= BeginTFy) && (BeginTFy <= BOARD_SIZE)
			&& 
			(0 <= EndTFy) && (EndTFy <= BOARD_SIZE);
		(BeginTFx = EndTFx + 1), (BeginTFy = EndTFy - 1)) //β���Ƶ�ʼ�����һλ
		{
			count = ChessCount_TF(BeginTFy, BeginTFx, WHITE_COLOR);
			if (count == 5)
			{					
				printf("�����ʤ��\n");
				GameOver();
			}

			Score_TF(BeginTFy, BeginTFx, count, WHITE_COLOR);
		}
	}
}


void CleanScore()
{
	int x, y;
	for (y = 0; y < 15; y++)
	{
		for (x = 0; x < 15; x++)
		{
			Board[y][x] %= 100;
		}
	}

}


void MaxScore()
{
	int x = 0;
	int y = 0;

	max.Value = max.x = max.y = 0;

	for (y = 0; y < 15; y++)
	{
		for (x = 0; x < 15; x++)
		{
			if (Board[y][x] > max.Value)
			{
				max.Value = Board[y][x];
				max.x = x;
				max.y = y;
			}
		}
	}
}


//��ĸת�����±�
int CharToNum(char c)
{
	if(c >= 'A' && c <= 'O')
	{
		return c - 'A';
	}
	else if(c >= 'a' && c <= 'o')
	{
		return c - 'a';
	}
}


//��Ϸ����
void GameOver()
{
	int a;

	printf("\n\n�Ƿ����¿�ʼһ����������ģ�\n\n��������1\n��������2\n");

	scanf("%d", &a);

	for (; ;)
	{
		if (a == 1)
		{
			system("cls");	//���֮ǰ����Ļ��ʾ��ʹ���ָ����λ��

			ChooseGameMode();
		}
		else if (a == 2)
		{
			system("cls");	//���֮ǰ����Ļ��ʾ��ʹ���ָ����λ��
			break;
		}
		else
		{
			printf("ѡ����Ч��������������ߣ�\n");

			scanf("%d", &a);
		}
	}	
	printf("GAME OVER!!!\n");
}



//�ж��������ֵ�˼·��
//******* 1����򵥵������������Σ�����2�����������������ӣ��Һ���һ������ͬʱ�γ��������������ӱ���Ϊ����������ͬ�Ĺ����ӡ�
//******* 2�����ԣ�ֻ�����ж�����1���������Ƿ��������ӣ����У����漴�ж�(yBlack, xBlack)���ڵ��������������Ƿ��������ӡ�
//******* 3����Ϊ���������˳��������-����-��һ��-����ķ���ͳ����������
//******* 4������ֻ������һ��һ���жϵ��ص㣬���жϳ�1�����������������Ӻ������ж�����3�������Ƿ��������Ӽ��ɡ�


//ˮƽ����x++��y++���жϺ������
void BanHand_3_Horizon(int Column)
{
	//���Ǳ߽����Ƶ�˼·���������̺����Ӵ��ı������򣨴������ң��������ϣ������������ϣ������������£���ֻ���β�˱߽�������Ƽ��ɣ���ʼ�߼�ʹ����Ե�ˣ�ͳ��������ʱҲ������
	if (EndH - 1 <= BOARD_SIZE)
	{
		BeginH = xBlack - 4;
		EndH = xBlack - 4;

		count = ChessCount_H(yBlack, BLACK_COLOR); //����������

		//�������������˾��ް��ӣ��Ҳ��������̱�Ե
		if (
			(count == 3)
			&& (Board[yBlack][BeginH - 1] % 100 != WHITE_COLOR) 
			&& (Board[yBlack][BeginH - 1] % 100 != WHITE_COLOR + 1)
			&& (Board[yBlack][EndH] % 100 != WHITE_COLOR) 
			&& (Board[yBlack][EndH] % 100 != WHITE_COLOR + 1)
			&& (BeginH != 0) && (BeginH != BOARD_SIZE) 
			&& (EndH - 1 != 0) && (EndH - 1 != BOARD_SIZE) 
			&& (yBlack != 0) && (yBlack != BOARD_SIZE)) 
		{
			//��ֱ�����ж��Ƿ��е����������ġ�
			if (EndV - 1 <= BOARD_SIZE)
			{
				BeginV = yBlack - 4;
				EndV = yBlack - 4;

				count = ChessCount_V(xBlack, BLACK_COLOR);

				if ((count == 4)
					&& 
					(((Board[BeginV - 1][xBlack] % 100 != WHITE_COLOR) 
					&& (Board[BeginV - 1][xBlack] % 100 != WHITE_COLOR + 1))
					|| 
					((Board[EndV][xBlack] % 100 != WHITE_COLOR) 
					&& (Board[EndV][xBlack] % 100 != WHITE_COLOR + 1)))) 
				{
					printf("�˲�����Ϊ���������֣������ʤ��\n");
					GameOver();
					return;
				}
			}


			//һ�����޷����ж��Ƿ��е����������ġ�
			else if ((EndOTx - 1 <= BOARD_SIZE) && (EndOTy - 1 <= BOARD_SIZE))
			{
				BeginOTx = xBlack - 4;
				BeginOTy = yBlack - 4;
				EndOTx = xBlack - 4;
				EndOTy = yBlack - 4;

				count = ChessCount_OT(BeginOTy, BeginOTx, BLACK_COLOR);

				//�����ӵ�����ֻ����һ���ް���
				if ((count == 4) 
					&& 
					(((Board[BeginOTy - 1][BeginOTx - 1] % 100 != WHITE_COLOR) 
					&& (Board[BeginOTy - 1][BeginOTx - 1] % 100 != WHITE_COLOR + 1))
					|| 
					((Board[EndOTy][EndOTx] % 100 != WHITE_COLOR) 
					&& (Board[EndOTy][EndOTx] % 100 != WHITE_COLOR + 1))))
				{
					printf("�˲�����Ϊ���������֣������ʤ��\n");
					GameOver();
					return;
				}
			}


			//�������޷����ж��Ƿ��е����������ġ�
			else if ((EndTFx - 1 <= BOARD_SIZE) && (0 <= EndTFy + 1))
			{
				BeginTFx = xBlack - 4;
				BeginTFy = yBlack + 4;
				EndTFx = xBlack - 4;
				EndTFy = yBlack + 4;

				count = ChessCount_TF(BeginTFy, BeginTFx, BLACK_COLOR);

				//�������޷��������ӵ����˾��ް��ӣ��Ҳ��������̱�Ե
				if ((count == 4) 
					&& 
					(((Board[BeginTFy + 1][BeginTFx - 1] % 100 != WHITE_COLOR) 
					&& (Board[BeginTFy + 1][BeginTFx - 1] % 100 != WHITE_COLOR + 1))
					||
					((Board[EndTFy][EndTFx] % 100 != WHITE_COLOR) 
					&& (Board[EndTFy][EndTFx] % 100 != WHITE_COLOR + 1))))
				{
					printf("�˲�����Ϊ���������֣������ʤ��\n");
					GameOver();
					return;
				}
			}


			//���޵����������ġ������ж�Ϊ��������
			printf("�˲�����Ϊ�������֣������ʤ��\n");
			GameOver();
			return;
		}
	}
}



//ˮƽ����x++��y++���жϺ������
void BanHand_4_Horizon(int Column)
{
	//���Ǳ߽����Ƶ�˼·���������̺����Ӵ��ı������򣨴������ң��������ϣ������������ϣ������������£���ֻ���β�˱߽�������Ƽ��ɣ���ʼ�߼�ʹ����Ե�ˣ�ͳ��������ʱҲ������
	if (EndH - 1 <= BOARD_SIZE)
	{
		BeginH = xBlack - 4;
		EndH = xBlack - 4;

		count = ChessCount_H(yBlack, BLACK_COLOR); //����������

		//�����ӵ�����ֻ����һ���ް���
		if (
			(count == 4)
			&& 
			(((Board[yBlack][BeginH - 1] % 100 != WHITE_COLOR) 
			&& (Board[yBlack][BeginH - 1] % 100 != WHITE_COLOR + 1))
			|| 
			((Board[yBlack][EndH] % 100 != WHITE_COLOR) 
			&& (Board[yBlack][EndH] % 100 != WHITE_COLOR + 1)))
			)
		{
			//��ֱ�����ж��Ƿ��е�������������
			if (EndV - 1 <= BOARD_SIZE)
			{
				BeginV = yBlack - 4;
				EndV = yBlack - 4;

				count = ChessCount_V(xBlack, BLACK_COLOR);

				if ((count == 3)
					&& (Board[BeginV - 1][xBlack] % 100 != WHITE_COLOR) 
					&& (Board[BeginV - 1][xBlack] % 100 != WHITE_COLOR + 1)
					&& (Board[EndV][xBlack] % 100 != WHITE_COLOR) 
					&& (Board[EndV][xBlack] % 100 != WHITE_COLOR + 1)
					&& (BeginV != 0) && (BeginV != BOARD_SIZE) 
					&& (EndV - 1 != 0) && (EndV - 1 != BOARD_SIZE) 
					&& (xBlack != 0) && (xBlack != BOARD_SIZE)
					) 
				{
					printf("�˲�����Ϊ���������֣������ʤ��\n");
					GameOver();
					return;

				}
			}


			//һ�����޷����ж��Ƿ��е�������������
			if ( (EndOTx - 1 <= BOARD_SIZE) && (EndOTy - 1 <= BOARD_SIZE))
			{
				BeginOTx = xBlack - 4;
				BeginOTy = yBlack - 4;
				EndOTx = xBlack - 4;
				EndOTy = yBlack - 4;

				count = ChessCount_OT(BeginOTy, BeginOTx, BLACK_COLOR);

				//һ�����޷��������ӵ����˾��ް��ӣ��Ҳ��������̱�Ե
				if ((count == 3) 
					&& (Board[BeginOTy - 1][BeginOTx - 1] % 100 != WHITE_COLOR) 
					&& (Board[BeginOTy - 1][BeginOTx - 1] % 100 != WHITE_COLOR + 1)
					&& (Board[EndOTy][EndOTx] % 100 != WHITE_COLOR) 
					&& (Board[EndOTy][EndOTx] % 100 != WHITE_COLOR + 1)
					&& (BeginOTy != 0) && (BeginOTy != BOARD_SIZE) 
					&& (BeginOTx != 0) && (BeginOTx != BOARD_SIZE)
					&& (EndOTy - 1 != 0) && (EndOTy - 1 != BOARD_SIZE)  
					&& (EndOTx - 1 != 0) && (EndOTx - 1 != BOARD_SIZE))
				{
					printf("�˲�����Ϊ���������֣������ʤ��\n");
					GameOver();
					return;
				}
			}


			//�������޷����ж��Ƿ��е�������������
			if ((EndTFx - 1 <= BOARD_SIZE) && (0 <= EndTFy + 1))
			{
				BeginTFx = xBlack - 4;
				BeginTFy = yBlack + 4;
				EndTFx = xBlack - 4;
				EndTFy = yBlack + 4;

				count = ChessCount_TF(BeginTFy, BeginTFx, BLACK_COLOR);

				//�������޷��������ӵ����˾��ް��ӣ��Ҳ��������̱�Ե
				if ((count == 3) 
					&& (Board[BeginTFy + 1][BeginTFx - 1] % 100 != WHITE_COLOR) 
					&& (Board[BeginTFy + 1][BeginTFx - 1] % 100 != WHITE_COLOR + 1)
					&& (Board[EndTFy][EndTFx] % 100 != WHITE_COLOR) 
					&& (Board[EndTFy][EndTFx] % 100 != WHITE_COLOR + 1)
					&& (BeginTFy != 0) && (BeginTFy != BOARD_SIZE) 
					&& (BeginTFx != 0) && (BeginTFx != BOARD_SIZE)
					&& (EndTFy + 1 != 0) && (EndTFy + 1 != BOARD_SIZE) 
					&& (EndTFx - 1 != 0) && (EndTFx - 1 != BOARD_SIZE))
				{
					printf("�˲�����Ϊ���������֣������ʤ��\n");
					GameOver();
					return;
				}
			}


			//���޵������������������ж�Ϊ���Ľ���
			printf("�˲�����Ϊ���Ľ��֣������ʤ��\n");
			GameOver();
			return;
		}
	}
}



//��ֱ����x++��y++���жϺ������
void BanHand_3_Vertical(int Line)
{
	//////for (
	//////	(BeginV = yBlack - 4, EndV = yBlack - 4) && (EndV - 1 <= BOARD_SIZE); 
	//////	(BeginV <= yBlack + 4) && (BeginV <= BOARD_SIZE) && (EndV - 1 <= yBlack + 4) && (EndV - 1 <= BOARD_SIZE); 
	//////BeginV = EndV + 1)
	//////{


	if (EndV - 1 <= BOARD_SIZE)
	{
		BeginV = yBlack - 4;
		EndV = yBlack - 4;



		count = ChessCount_V(xBlack, BLACK_COLOR);

		//���������ӵ����˾��ް��ӣ��Ҳ��������̱�Ե���ڶ���������
		//�����һ������(yBlack, xBlack)�����������Ľ��㴦
		if ((count == 3)
			&& (Board[BeginV - 1][xBlack] % 100 != WHITE_COLOR) 
			&& (Board[BeginV - 1][xBlack] % 100 != WHITE_COLOR + 1)
			&& (Board[EndV][xBlack] % 100 != WHITE_COLOR) 
			&& (Board[EndV][xBlack] % 100 != WHITE_COLOR + 1)
			&& (BeginV != 0) && (BeginV != BOARD_SIZE) 
			&& (EndV - 1 != 0) && (EndV - 1 != BOARD_SIZE) 
			&& (xBlack != 0) && (xBlack != BOARD_SIZE)) 
		{
			//ˮƽ�����ж��Ƿ��е����������ġ�
			for ((BeginH = xBlack - 4, EndH = xBlack - 4) && (EndH - 1 <= BOARD_SIZE); 
				(BeginH <= xBlack + 4) && (BeginH <= BOARD_SIZE) && (EndH - 1 <= xBlack + 4) && (EndH - 1 <= BOARD_SIZE); 
				BeginH = EndH + 1)
			{
				count = ChessCount_H(yBlack, BLACK_COLOR); //����������

				if ((count == 4)
					&& 
					(((Board[yBlack][BeginH - 1] % 100 != WHITE_COLOR) 
					&& (Board[yBlack][BeginH - 1] % 100 != WHITE_COLOR + 1))
					|| 
					((Board[yBlack][EndH] % 100 != WHITE_COLOR) 
					&& (Board[yBlack][EndH] % 100 != WHITE_COLOR + 1))))
				{
					printf("�˲�����Ϊ���������֣������ʤ��\n");
					GameOver();
					return;
				}

				else
				{
					continue;
				}
			}


			//һ�����޷����ж��Ƿ��е����������ġ�
			for (
				(BeginOTx = xBlack - 4, BeginOTy = yBlack - 4, EndOTx = xBlack - 4, EndOTy = yBlack - 4) && (EndOTx - 1 <= BOARD_SIZE) && (EndOTy - 1 <= BOARD_SIZE); 
				(BeginOTx <= xBlack + 4) && (BeginOTy <= yBlack + 4) && (EndOTx - 1 <= xBlack + 4) && (EndOTy - 1 <= yBlack + 4) && (EndOTx - 1 <= BOARD_SIZE) && (EndOTy - 1 <= BOARD_SIZE); 
			BeginOTx = EndOTx + 1, BeginOTy = EndOTy + 1)
			{
				count = ChessCount_OT(BeginOTy, BeginOTx, BLACK_COLOR);

				//�����ӵ�����ֻ����һ���ް���
				if ((count == 4) 
					&& 
					(((Board[BeginOTy - 1][BeginOTx - 1] % 100 != WHITE_COLOR) 
					&& (Board[BeginOTy - 1][BeginOTx - 1] % 100 != WHITE_COLOR + 1))
					|| 
					((Board[EndOTy][EndOTx] % 100 != WHITE_COLOR) 
					&& (Board[EndOTy][EndOTx] % 100 != WHITE_COLOR + 1))))
				{
					printf("�˲�����Ϊ���������֣������ʤ��\n");
					GameOver();
					return;
				}

				else
				{
					continue;
				}
			}


			//�������޷����ж��Ƿ��е����������ġ�
			for (
				(BeginTFx = xBlack - 4, BeginTFy = yBlack + 4, EndTFx = xBlack - 4, EndTFy = yBlack + 4) && (EndTFx - 1 <= BOARD_SIZE) && (0 <= EndTFy + 1); 
				(BeginTFx <= xBlack + 4) && (EndTFx - 1 <= BOARD_SIZE) && (0 <= EndTFy + 1); 
			BeginTFx = EndTFx + 1, BeginTFy = EndTFy - 1)
			{
				count = ChessCount_TF(BeginTFy, BeginTFx, BLACK_COLOR);

				//�������޷��������ӵ����˾��ް��ӣ��Ҳ��������̱�Ե
				if ((count == 4) 
					&& 
					(((Board[BeginTFy + 1][BeginTFx - 1] % 100 != WHITE_COLOR) 
					&& (Board[BeginTFy + 1][BeginTFx - 1] % 100 != WHITE_COLOR + 1))
					||
					((Board[EndTFy][EndTFx] % 100 != WHITE_COLOR) 
					&& (Board[EndTFy][EndTFx] % 100 != WHITE_COLOR + 1))))
				{
					printf("�˲�����Ϊ���������֣������ʤ��\n");
					GameOver();
					return;
				}

				else
				{
					continue;
				}
			}

			//���޵����������ġ������ж�Ϊ��������
			printf("�˲�����Ϊ�������֣������ʤ��\n");
			GameOver();
			return;
		}
	}
}



//��ֱ����x++��y++���жϺ������
void BanHand_4_Vertical(int Line)
{
	//////for (
	//////	(BeginV = yBlack - 4, EndV = yBlack - 4) && (EndV - 1 <= BOARD_SIZE); 
	//////	(BeginV <= yBlack + 4) && (BeginV <= BOARD_SIZE) && (EndV - 1 <= yBlack + 4) && (EndV - 1 <= BOARD_SIZE); 
	//////BeginV = EndV + 1)
	//////{

	if (EndV - 1 <= BOARD_SIZE)
	{
		BeginV = yBlack - 4;
		EndV = yBlack - 4;


		count = ChessCount_V(xBlack, BLACK_COLOR);

		//�����ӵ�����ֻ����һ���ް���
		//�����һ������(yBlack, xBlack)�����������Ľ��㴦
		if (
			(count == 4)
			&& 
			(((Board[BeginV - 1][xBlack] % 100 != WHITE_COLOR) 
			&& (Board[BeginV - 1][xBlack] % 100 != WHITE_COLOR + 1))
			|| 
			((Board[EndV][xBlack] % 100 != WHITE_COLOR) 
			&& (Board[EndV][xBlack] % 100 != WHITE_COLOR + 1)))
			) 
		{
			//ˮƽ�����ж��Ƿ��е�������������
			for (
				(BeginH = xBlack - 4, EndH = xBlack - 4) && (EndH - 1 <= BOARD_SIZE); 
				(BeginH <= xBlack + 4) && (BeginH <= BOARD_SIZE) && (EndH - 1 <= xBlack + 4) && (EndH - 1 <= BOARD_SIZE); 
			BeginH = EndH + 1)
			{
				count = ChessCount_H(yBlack, BLACK_COLOR); //����������

				//�������������˾��ް��ӣ��Ҳ��������̱�Ե
				if (
					(count == 3)
					&& (Board[yBlack][BeginH - 1] % 100 != WHITE_COLOR) 
					&& (Board[yBlack][BeginH - 1] % 100 != WHITE_COLOR + 1)
					&& (Board[yBlack][EndH] % 100 != WHITE_COLOR) 
					&& (Board[yBlack][EndH] % 100 != WHITE_COLOR + 1)
					&& (BeginH != 0) && (BeginH != BOARD_SIZE) 
					&& (EndH - 1 != 0) && (EndH - 1 != BOARD_SIZE) 
					&& (yBlack != 0) && (yBlack != BOARD_SIZE))
				{
					printf("�˲�����Ϊ���������֣������ʤ��\n");
					GameOver();
					return;
				}

				else
				{
					continue;
				}
			}


			//һ�����޷����ж��Ƿ��е�������������
			for (
				(BeginOTx = xBlack - 4, BeginOTy = yBlack - 4, EndOTx = xBlack - 4, EndOTy = yBlack - 4) && (EndOTx - 1 <= BOARD_SIZE) && (EndOTy - 1 <= BOARD_SIZE); 
				(BeginOTx <= xBlack + 4) && (BeginOTy <= yBlack + 4) && (EndOTx - 1 <= xBlack + 4) && (EndOTy - 1 <= yBlack + 4) && (EndOTx - 1 <= BOARD_SIZE) && (EndOTy - 1 <= BOARD_SIZE); 
			BeginOTx = EndOTx + 1, BeginOTy = EndOTy + 1)
			{
				count = ChessCount_OT(BeginOTy, BeginOTx, BLACK_COLOR);

				//һ�����޷��������ӵ����˾��ް��ӣ��Ҳ��������̱�Ե
				if ((count == 3) 
					&& (Board[BeginOTy - 1][BeginOTx - 1] % 100 != WHITE_COLOR) 
					&& (Board[BeginOTy - 1][BeginOTx - 1] % 100 != WHITE_COLOR + 1)
					&& (Board[EndOTy][EndOTx] % 100 != WHITE_COLOR) 
					&& (Board[EndOTy][EndOTx] % 100 != WHITE_COLOR + 1)
					&& (BeginOTy != 0) && (BeginOTy != BOARD_SIZE) 
					&& (BeginOTx != 0) && (BeginOTx != BOARD_SIZE)
					&& (EndOTy - 1 != 0) && (EndOTy - 1 != BOARD_SIZE)  
					&& (EndOTx - 1 != 0) && (EndOTx - 1 != BOARD_SIZE))
				{
					printf("�˲�����Ϊ���������֣������ʤ��\n");
					GameOver();
					return;
				}

				else
				{
					continue;
				}
			}


			//�������޷����ж��Ƿ��е�������������
			for (
				(BeginTFx = xBlack - 4, BeginTFy = yBlack + 4, EndTFx = xBlack - 4, EndTFy = yBlack + 4) && (EndTFx - 1 <= BOARD_SIZE) && (0 <= EndTFy + 1); 
				(BeginTFx <= xBlack + 4) && (EndTFx - 1 <= BOARD_SIZE) && (0 <= EndTFy + 1); 
			BeginTFx = EndTFx + 1, BeginTFy = EndTFy - 1)
			{
				count = ChessCount_TF(BeginTFy, BeginTFx, BLACK_COLOR);

				//�������޷��������ӵ����˾��ް��ӣ��Ҳ��������̱�Ե
				if ((count == 3) 
					&& (Board[BeginTFy + 1][BeginTFx - 1] % 100 != WHITE_COLOR) 
					&& (Board[BeginTFy + 1][BeginTFx - 1] % 100 != WHITE_COLOR + 1)
					&& (Board[EndTFy][EndTFx] % 100 != WHITE_COLOR) 
					&& (Board[EndTFy][EndTFx] % 100 != WHITE_COLOR + 1)
					&& (BeginTFy != 0) && (BeginTFy != BOARD_SIZE) 
					&& (BeginTFx != 0) && (BeginTFx != BOARD_SIZE)
					&& (EndTFy + 1 != 0) && (EndTFy + 1 != BOARD_SIZE) 
					&& (EndTFx - 1 != 0) && (EndTFx - 1 != BOARD_SIZE))
				{
					printf("�˲�����Ϊ���������֣������ʤ��\n");
					GameOver();
					return;
				}

				else
				{
					continue;
				}
			}


			//���޵������������������ж�Ϊ���Ľ���
			printf("�˲�����Ϊ���Ľ��֣������ʤ��\n");
			GameOver();
			return;

		}
	}
}



//һ�����޷���x++��y++���жϺ������
void BanHand_3_OneThreeQuadrant(int Column, int Line)
{
	//////////for (
	//////////	(BeginOTx = xBlack - 4,BeginOTy = yBlack - 4, EndOTx = xBlack - 4, EndOTy = yBlack - 4) && (EndOTx - 1 <= BOARD_SIZE) && (EndOTy - 1 <= BOARD_SIZE); 
	//////////	(BeginOTx <= xBlack + 4) && (BeginOTy <= yBlack + 4) && (EndOTx - 1 <= xBlack + 4) && (EndOTy - 1 <= yBlack + 4) && (EndOTx - 1 <= BOARD_SIZE) && (EndOTy - 1 <= BOARD_SIZE); 
	//////////BeginOTx = EndOTx + 1, BeginOTy = EndOTy + 1)

	if ((EndOTx - 1 <= BOARD_SIZE) && (EndOTy - 1 <= BOARD_SIZE))
	{
		BeginOTx = xBlack - 4;
		BeginOTy = yBlack - 4;
		EndOTx = xBlack - 4;
		EndOTy = yBlack - 4; 


		count = ChessCount_OT(BeginOTy, BeginOTx, BLACK_COLOR);

		//һ�����޷��������ӵ����˾��ް��ӣ��Ҳ��������̱�Ե
		if ((count == 3) 
			&& (Board[BeginOTy - 1][BeginOTx - 1] % 100 != WHITE_COLOR) 
			&& (Board[BeginOTy - 1][BeginOTx - 1] % 100 != WHITE_COLOR + 1)
			&& (Board[EndOTy][EndOTx] % 100 != WHITE_COLOR) 
			&& (Board[EndOTy][EndOTx] % 100 != WHITE_COLOR + 1)
			&& (BeginOTy != 0) && (BeginOTy != BOARD_SIZE) 
			&& (BeginOTx != 0) && (BeginOTx != BOARD_SIZE)
			&& (EndOTy - 1 != 0) && (EndOTy - 1 != BOARD_SIZE)  
			&& (EndOTx - 1 != 0) && (EndOTx - 1 != BOARD_SIZE))
		{
			//ˮƽ�����ж��Ƿ��е����������ġ�
			for ((BeginH = xBlack - 4, EndH = xBlack - 4) && (EndH - 1 <= BOARD_SIZE); 
				(BeginH <= xBlack + 4) && (BeginH <= BOARD_SIZE) && (EndH - 1 <= xBlack + 4) && (EndH - 1 <= BOARD_SIZE); 
				BeginH = EndH + 1)
			{
				count = ChessCount_H(yBlack, BLACK_COLOR); //����������

				if ((count == 4)
					&& 
					(((Board[yBlack][BeginH - 1] % 100 != WHITE_COLOR) 
					&& (Board[yBlack][BeginH - 1] % 100 != WHITE_COLOR + 1))
					|| 
					((Board[yBlack][EndH] % 100 != WHITE_COLOR) 
					&& (Board[yBlack][EndH] % 100 != WHITE_COLOR + 1))))
				{
					printf("�˲�����Ϊ���������֣������ʤ��\n");
					GameOver();
					return;
				}

				else
				{
					continue;
				}
			}


			//��ֱ�����ж��Ƿ��е����������ġ�
			for (
				(BeginV = yBlack - 4, EndV = yBlack - 4) && (EndV - 1 <= BOARD_SIZE); 
				(BeginV <= yBlack + 4) && (BeginV <= BOARD_SIZE) && (EndV - 1 <= yBlack + 4) && (EndV - 1 <= BOARD_SIZE); 
			BeginV = EndV + 1)
			{
				count = ChessCount_V(xBlack, BLACK_COLOR);

				if (
					(count == 4)
					&& 
					(((Board[BeginV - 1][xBlack] % 100 != WHITE_COLOR) 
					&& (Board[BeginV - 1][xBlack] % 100 != WHITE_COLOR + 1))
					|| 
					((Board[EndV][xBlack] % 100 != WHITE_COLOR) 
					&& (Board[EndV][xBlack] % 100 != WHITE_COLOR + 1)))
					) 
				{
					printf("�˲�����Ϊ���������֣������ʤ��\n");
					GameOver();
					return;
				}

				else
				{
					continue;
				}
			}


			//�������޷����ж��Ƿ��е����������ġ�
			for (
				(BeginTFx = xBlack - 4, BeginTFy = yBlack + 4, EndTFx = xBlack - 4, EndTFy = yBlack + 4) && (EndTFx - 1 <= BOARD_SIZE) && (0 <= EndTFy + 1); 
				(BeginTFx <= xBlack + 4) && (EndTFx - 1 <= BOARD_SIZE) && (0 <= EndTFy + 1); 
			BeginTFx = EndTFx + 1, BeginTFy = EndTFy - 1)
			{
				count = ChessCount_TF(BeginTFy, BeginTFx, BLACK_COLOR);

				//�������޷��������ӵ����˾��ް��ӣ��Ҳ��������̱�Ե
				if (
					(count == 4) 
					&& 
					(((Board[BeginTFy + 1][BeginTFx - 1] % 100 != WHITE_COLOR) 
					&& (Board[BeginTFy + 1][BeginTFx - 1] % 100 != WHITE_COLOR + 1))
					||
					((Board[EndTFy][EndTFx] % 100 != WHITE_COLOR) 
					&& (Board[EndTFy][EndTFx] % 100 != WHITE_COLOR + 1)))
					)
				{
					printf("�˲�����Ϊ���������֣������ʤ��\n");
					GameOver();
					return;
				}

				else
				{
					continue;
				}
			}

			//���޵����������ġ������ж�Ϊ��������
			printf("�˲�����Ϊ�������֣������ʤ��\n");
			GameOver();
			return;
		}

		//////else
		//////{
		//////	continue;
		//////}
	}
}


//һ�����޷���x++��y++���жϺ������
void BanHand_4_OneThreeQuadrant(int Column, int Line)
{
	//////////for (
	//////////	(BeginOTx = xBlack - 4, BeginOTy = yBlack - 4, EndOTx = xBlack - 4, EndOTy = yBlack - 4) && (EndOTx - 1 <= BOARD_SIZE) && (EndOTy - 1 <= BOARD_SIZE); 
	//////////	(BeginOTx <= xBlack + 4) && (BeginOTy <= yBlack + 4) && (EndOTx - 1 <= xBlack + 4) && (EndOTy - 1 <= yBlack + 4) && (EndOTx - 1 <= BOARD_SIZE) && (EndOTy - 1 <= BOARD_SIZE); 
	//////////BeginOTx = EndOTx + 1, BeginOTy = EndOTy + 1)
	//////////{


	if ((EndOTx - 1 <= BOARD_SIZE) && (EndOTy - 1 <= BOARD_SIZE))
	{
		BeginOTx = xBlack - 4;
		BeginOTy = yBlack - 4;
		EndOTx = xBlack - 4;
		EndOTy = yBlack - 4; 

		count = ChessCount_OT(BeginOTy, BeginOTx, BLACK_COLOR);

		//�����ӵ�����ֻ����һ���ް���
		if (
			(count == 4) 
			&& 
			(((Board[BeginOTy - 1][BeginOTx - 1] % 100 != WHITE_COLOR) 
			&& (Board[BeginOTy - 1][BeginOTx - 1] % 100 != WHITE_COLOR + 1))
			|| 
			((Board[EndOTy][EndOTx] % 100 != WHITE_COLOR) 
			&& (Board[EndOTy][EndOTx] % 100 != WHITE_COLOR + 1)))
			)
		{
			//ˮƽ�����ж��Ƿ��е�������������
			for (
				(BeginH = xBlack - 4, EndH = xBlack - 4) && (EndH - 1 <= BOARD_SIZE); 
				(BeginH <= xBlack + 4) && (BeginH <= BOARD_SIZE) && (EndH - 1 <= xBlack + 4) && (EndH - 1 <= BOARD_SIZE); 
			BeginH = EndH + 1)
			{
				count = ChessCount_H(yBlack, BLACK_COLOR); //����������

				//�������������˾��ް��ӣ��Ҳ��������̱�Ե
				if (
					(count == 3)
					&& (Board[yBlack][BeginH - 1] % 100 != WHITE_COLOR) 
					&& (Board[yBlack][BeginH - 1] % 100 != WHITE_COLOR + 1)
					&& (Board[yBlack][EndH] % 100 != WHITE_COLOR) 
					&& (Board[yBlack][EndH] % 100 != WHITE_COLOR + 1)
					&& (BeginH != 0) && (BeginH != BOARD_SIZE) 
					&& (EndH - 1 != 0) && (EndH - 1 != BOARD_SIZE) 
					&& (yBlack != 0) && (yBlack != BOARD_SIZE))
				{
					printf("�˲�����Ϊ���������֣������ʤ��\n");
					GameOver();
					return;
				}

				else
				{
					continue;
				}
			}



			//��ֱ�����ж��Ƿ��е�������������
			for (
				(BeginV = yBlack - 4, EndV = yBlack - 4) && (EndV - 1 <= BOARD_SIZE); 
				(BeginV <= yBlack + 4) && (BeginV <= BOARD_SIZE) && (EndV - 1 <= yBlack + 4) && (EndV - 1 <= BOARD_SIZE); 
			BeginV = EndV + 1)
			{
				count = ChessCount_V(xBlack, BLACK_COLOR);

				if ((count == 3)
					&& (Board[BeginV - 1][xBlack] % 100 != WHITE_COLOR) 
					&& (Board[BeginV - 1][xBlack] % 100 != WHITE_COLOR + 1)
					&& (Board[EndV][xBlack] % 100 != WHITE_COLOR) 
					&& (Board[EndV][xBlack] % 100 != WHITE_COLOR + 1)
					&& (BeginV != 0) && (BeginV != BOARD_SIZE) 
					&& (EndV - 1 != 0) && (EndV - 1 != BOARD_SIZE) 
					&& (xBlack != 0) && (xBlack != BOARD_SIZE)
					) 
				{
					printf("�˲�����Ϊ���������֣������ʤ��\n");
					GameOver();
					return;
				}

				else
				{
					continue;
				}
			}


			//�������޷����ж��Ƿ��е�������������
			for (
				(BeginTFx = xBlack - 4, BeginTFy = yBlack + 4, EndTFx = xBlack - 4, EndTFy = yBlack + 4) && (EndTFx - 1 <= BOARD_SIZE) && (0 <= EndTFy + 1); 
				(BeginTFx <= xBlack + 4) && (EndTFx - 1 <= BOARD_SIZE) && (0 <= EndTFy + 1); 
			BeginTFx = EndTFx + 1, BeginTFy = EndTFy - 1)
			{
				count = ChessCount_TF(BeginTFy, BeginTFx, BLACK_COLOR);

				//�������޷��������ӵ����˾��ް��ӣ��Ҳ��������̱�Ե
				if ((count == 3) 
					&& (Board[BeginTFy + 1][BeginTFx - 1] % 100 != WHITE_COLOR) 
					&& (Board[BeginTFy + 1][BeginTFx - 1] % 100 != WHITE_COLOR + 1)
					&& (Board[EndTFy][EndTFx] % 100 != WHITE_COLOR) 
					&& (Board[EndTFy][EndTFx] % 100 != WHITE_COLOR + 1)
					&& (BeginTFy != 0) && (BeginTFy != BOARD_SIZE) 
					&& (BeginTFx != 0) && (BeginTFx != BOARD_SIZE)
					&& (EndTFy + 1 != 0) && (EndTFy + 1 != BOARD_SIZE) 
					&& (EndTFx - 1 != 0) && (EndTFx - 1 != BOARD_SIZE))
				{
					printf("�˲�����Ϊ���������֣������ʤ��\n");
					GameOver();
					return;
				}

				else
				{
					continue;
				}
			}


			//���޵������������������ж�Ϊ���Ľ���
			printf("�˲�����Ϊ���Ľ��֣������ʤ��\n");
			GameOver();
			return;
		}
	}
}


//�������޷���x++��y--���жϺ������
void BanHand_3_TwoFourQuadrant(int Column, int Line)
{
	/////���Ǳ߽����Ƶ�˼·���������̺����Ӵ��ı������򣨴������ң��������ϣ������������ϣ������������£���ֻ���β�˱߽�������Ƽ��ɣ���ʼ�߼�ʱ����Ե�ˣ�ͳ��������ʱҲ������

	//forѭ���ı��ʽ2ֻ������(BeginTFx <= xBlack + 4)����δ����(BeginTFy = yBlack - 4)������Ϊy��x�ı�������һ�£�š�ţ���ì�ܣ�
	//��y��x�仯���仯����������Ϊ��������д�����ʽ2��


	//////////for (
	//////////	(BeginTFx = xBlack - 4, BeginTFy = yBlack + 4, EndTFx = xBlack - 4, EndTFy = yBlack + 4) && (EndTFx - 1 <= BOARD_SIZE) && (0 <= EndTFy + 1); 
	//////////	(BeginTFx <= xBlack + 4) && (EndTFx - 1 <= BOARD_SIZE) && (0 <= EndTFy + 1); 
	//////////BeginTFx = EndTFx + 1, BeginTFy = EndTFy - 1)
	//////////{

	if ((EndTFx - 1 <= BOARD_SIZE) && (0 <= EndTFy + 1))
	{
		BeginTFx = xBlack - 4;
		BeginTFy = yBlack + 4;
		EndTFx = xBlack - 4;
		EndTFy = yBlack + 4;


		count = ChessCount_TF(BeginTFy, BeginTFx, BLACK_COLOR);

		//�������޷��������ӵ����˾��ް��ӣ��Ҳ��������̱�Ե
		if ((count == 3) 
			&& (Board[BeginTFy + 1][BeginTFx - 1] % 100 != WHITE_COLOR) 
			&& (Board[BeginTFy + 1][BeginTFx - 1] % 100 != WHITE_COLOR + 1)
			&& (Board[EndTFy][EndTFx] % 100 != WHITE_COLOR) 
			&& (Board[EndTFy][EndTFx] % 100 != WHITE_COLOR + 1)
			&& (BeginTFy != 0) && (BeginTFy != BOARD_SIZE) 
			&& (BeginTFx != 0) && (BeginTFx != BOARD_SIZE)
			&& (EndTFy + 1 != 0) && (EndTFy + 1 != BOARD_SIZE) 
			&& (EndTFx - 1 != 0) && (EndTFx - 1 != BOARD_SIZE))
		{
			//ˮƽ�����ж��Ƿ��е����������ġ�
			for ((BeginH = xBlack - 4, EndH = xBlack - 4) && (EndH - 1 <= BOARD_SIZE); 
				(BeginH <= xBlack + 4) && (BeginH <= BOARD_SIZE) && (EndH - 1 <= xBlack + 4) && (EndH - 1 <= BOARD_SIZE); 
				BeginH = EndH + 1)
			{
				count = ChessCount_H(yBlack, BLACK_COLOR); //����������

				if ((count == 4)
					&& 
					(((Board[yBlack][BeginH - 1] % 100 != WHITE_COLOR) 
					&& (Board[yBlack][BeginH - 1] % 100 != WHITE_COLOR + 1))
					|| 
					((Board[yBlack][EndH] % 100 != WHITE_COLOR) 
					&& (Board[yBlack][EndH] % 100 != WHITE_COLOR + 1))))
				{
					printf("�˲�����Ϊ���������֣������ʤ��\n");
					GameOver();
					return;
				}

				else
				{
					continue;
				}
			}


			//��ֱ�����ж��Ƿ��е����������ġ�
			for (
				(BeginV = yBlack - 4, EndV = yBlack - 4) && (EndV - 1 <= BOARD_SIZE); 
				(BeginV <= yBlack + 4) && (BeginV <= BOARD_SIZE) && (EndV - 1 <= yBlack + 4) && (EndV - 1 <= BOARD_SIZE); 
			BeginV = EndV + 1)
			{
				count = ChessCount_V(xBlack, BLACK_COLOR);

				if (
					(count == 4)
					&& 
					(((Board[BeginV - 1][xBlack] % 100 != WHITE_COLOR) 
					&& (Board[BeginV - 1][xBlack] % 100 != WHITE_COLOR + 1))
					|| 
					((Board[EndV][xBlack] % 100 != WHITE_COLOR) 
					&& (Board[EndV][xBlack] % 100 != WHITE_COLOR + 1)))
					) 
				{
					printf("�˲�����Ϊ���������֣������ʤ��\n");
					GameOver();
					return;
				}

				else
				{
					continue;
				}
			}


			//һ�����޷����ж��Ƿ��е����������ġ�
			for (
				(BeginOTx = xBlack - 4, BeginOTy = yBlack - 4, EndOTx = xBlack - 4, EndOTy = yBlack - 4) && (EndOTx - 1 <= BOARD_SIZE) && (EndOTy - 1 <= BOARD_SIZE); 
				(BeginOTx <= xBlack + 4) && (BeginOTy <= yBlack + 4) && (EndOTx - 1 <= xBlack + 4) && (EndOTy - 1 <= yBlack + 4) && (EndOTx - 1 <= BOARD_SIZE) && (EndOTy - 1 <= BOARD_SIZE); 
			BeginOTx = EndOTx + 1, BeginOTy = EndOTy + 1)
			{
				count = ChessCount_OT(BeginOTy, BeginOTx, BLACK_COLOR);

				//�����ӵ�����ֻ����һ���ް���
				if (
					(count == 4) 
					&& 
					(((Board[BeginOTy - 1][BeginOTx - 1] % 100 != WHITE_COLOR) 
					&& (Board[BeginOTy - 1][BeginOTx - 1] % 100 != WHITE_COLOR + 1))
					|| 
					((Board[EndOTy][EndOTx] % 100 != WHITE_COLOR) 
					&& (Board[EndOTy][EndOTx] % 100 != WHITE_COLOR + 1)))
					)
				{
					printf("�˲�����Ϊ���������֣������ʤ��\n");
					GameOver();
					return;
				}

				else
				{
					continue;
				}
			}

			//���޵����������ġ������ж�Ϊ��������
			printf("�˲�����Ϊ�������֣������ʤ��\n");
			GameOver();
			return;
		}
	}
} 



//�������޷���x++��y--���жϺ������
void BanHand_4_TwoFourQuadrant(int Column, int Line)
{
	/////���Ǳ߽����Ƶ�˼·���������̺����Ӵ��ı������򣨴������ң��������ϣ������������ϣ������������£���ֻ���β�˱߽�������Ƽ��ɣ���ʼ�߼�ʱ����Ե�ˣ�ͳ��������ʱҲ������

	//forѭ���ı��ʽ2ֻ������(BeginTFx <= xBlack + 4)����δ����(BeginTFy = yBlack - 4)������Ϊy��x�ı�������һ�£�š�ţ���ì�ܣ�
	//��y��x�仯���仯����������Ϊ��������д�����ʽ2��


	//////////for (
	//////////	(BeginTFx = xBlack - 4, BeginTFy = yBlack + 4, EndTFx = xBlack - 4, EndTFy = yBlack + 4) && (EndTFx - 1 <= BOARD_SIZE) && (0 <= EndTFy + 1); 
	//////////	(BeginTFx <= xBlack + 4) && (EndTFx - 1 <= BOARD_SIZE) && (0 <= EndTFy + 1); 
	//////////BeginTFx = EndTFx + 1, BeginTFy = EndTFy - 1)
	//////////{

	if ((EndTFx - 1 <= BOARD_SIZE) && (0 <= EndTFy + 1))
	{
		BeginTFx = xBlack - 4;
		BeginTFy = yBlack + 4;
		EndTFx = xBlack - 4;
		EndTFy = yBlack + 4;


		count = ChessCount_TF(BeginTFy, BeginTFx, BLACK_COLOR);

		//�������޷��������ӵ����˾��ް��ӣ��Ҳ��������̱�Ե
		if (
			(count == 4) 
			&& 
			(((Board[BeginTFy + 1][BeginTFx - 1] % 100 != WHITE_COLOR) 
			&& (Board[BeginTFy + 1][BeginTFx - 1] % 100 != WHITE_COLOR + 1))
			||
			((Board[EndTFy][EndTFx] % 100 != WHITE_COLOR) 
			&& (Board[EndTFy][EndTFx] % 100 != WHITE_COLOR + 1)))
			)
		{
			//ˮƽ�����ж��Ƿ��е�������������
			for (
				(BeginH = xBlack - 4, EndH = xBlack - 4) && (EndH - 1 <= BOARD_SIZE); 
				(BeginH <= xBlack + 4) && (BeginH <= BOARD_SIZE) && (EndH - 1 <= xBlack + 4) && (EndH - 1 <= BOARD_SIZE); 
			BeginH = EndH + 1)
			{
				count = ChessCount_H(yBlack, BLACK_COLOR); //����������

				//�������������˾��ް��ӣ��Ҳ��������̱�Ե
				if (
					(count == 3)
					&& (Board[yBlack][BeginH - 1] % 100 != WHITE_COLOR) 
					&& (Board[yBlack][BeginH - 1] % 100 != WHITE_COLOR + 1)
					&& (Board[yBlack][EndH] % 100 != WHITE_COLOR) 
					&& (Board[yBlack][EndH] % 100 != WHITE_COLOR + 1)
					&& (BeginH != 0) && (BeginH != BOARD_SIZE) 
					&& (EndH - 1 != 0) && (EndH - 1 != BOARD_SIZE) 
					&& (yBlack != 0) && (yBlack != BOARD_SIZE))
				{
					printf("�˲�����Ϊ���������֣������ʤ��\n");
					GameOver();
					return;
				}

				else
				{
					continue;
				}
			}



			//��ֱ�����ж��Ƿ��е�������������
			for (
				(BeginV = yBlack - 4, EndV = yBlack - 4) && (EndV - 1 <= BOARD_SIZE); 
				(BeginV <= yBlack + 4) && (BeginV <= BOARD_SIZE) && (EndV - 1 <= yBlack + 4) && (EndV - 1 <= BOARD_SIZE); 
			BeginV = EndV + 1)
			{
				count = ChessCount_V(xBlack, BLACK_COLOR);

				if ((count == 3)
					&& (Board[BeginV - 1][xBlack] % 100 != WHITE_COLOR) 
					&& (Board[BeginV - 1][xBlack] % 100 != WHITE_COLOR + 1)
					&& (Board[EndV][xBlack] % 100 != WHITE_COLOR) 
					&& (Board[EndV][xBlack] % 100 != WHITE_COLOR + 1)
					&& (BeginV != 0) && (BeginV != BOARD_SIZE) 
					&& (EndV - 1 != 0) && (EndV - 1 != BOARD_SIZE) 
					&& (xBlack != 0) && (xBlack != BOARD_SIZE)
					) 
				{
					printf("�˲�����Ϊ���������֣������ʤ��\n");
					GameOver();
					return;
				}

				else
				{
					continue;
				}
			}


			//һ�����޷����ж��Ƿ��е�������������
			for (
				(BeginOTx = xBlack - 4, BeginOTy = yBlack - 4, EndOTx = xBlack - 4, EndOTy = yBlack - 4) && (EndOTx - 1 <= BOARD_SIZE) && (EndOTy - 1 <= BOARD_SIZE); 
				(BeginOTx <= xBlack + 4) && (BeginOTy <= yBlack + 4) && (EndOTx - 1 <= xBlack + 4) && (EndOTy - 1 <= yBlack + 4) && (EndOTx - 1 <= BOARD_SIZE) && (EndOTy - 1 <= BOARD_SIZE); 
			BeginOTx = EndOTx + 1, BeginOTy = EndOTy + 1)
			{
				count = ChessCount_OT(BeginOTy, BeginOTx, BLACK_COLOR);

				//һ�����޷��������ӵ����˾��ް��ӣ��Ҳ��������̱�Ե
				if ((count == 3) 
					&& (Board[BeginOTy - 1][BeginOTx - 1] % 100 != WHITE_COLOR) 
					&& (Board[BeginOTy - 1][BeginOTx - 1] % 100 != WHITE_COLOR + 1)
					&& (Board[EndOTy][EndOTx] % 100 != WHITE_COLOR) 
					&& (Board[EndOTy][EndOTx] % 100 != WHITE_COLOR + 1)
					&& (BeginOTy != 0) && (BeginOTy != BOARD_SIZE) 
					&& (BeginOTx != 0) && (BeginOTx != BOARD_SIZE)
					&& (EndOTy - 1 != 0) && (EndOTy - 1 != BOARD_SIZE)  
					&& (EndOTx - 1 != 0) && (EndOTx - 1 != BOARD_SIZE))
				{
					printf("�˲�����Ϊ���������֣������ʤ��\n");
					GameOver();
					return;
				}

				else
				{
					continue;
				}
			}


			//���޵������������������ж�Ϊ���Ľ���
			printf("�˲�����Ϊ���Ľ��֣������ʤ��\n");
			GameOver();
			return;
		}
	}
}