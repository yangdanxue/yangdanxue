#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define pixels				28			//ͼƬ������28*28
#define unit				10			//ÿһ����λ���ؼ��Ϲ���һ��Ȩ�أ���λ���ϵ����ش�С��10*10
#define NumWeight			28*28*10	//���ز���Ԫ������ÿһ����λ���ؼ��Ϲ���һ��Ȩ�أ����һ����Ԫ�����ظ�����
#define TrainTimes			1			//ѵ������
#define TestNumber			60000		//�ܲ���ͼƬ������


int ReadPicData(unsigned char* data, int iNum); //��ͼƬ�����ļ�

void WriteWeightData();				//������ǰ���õ�Ȩ��
void ReadWeightData();				//ʹ�ñ����Ȩ��
int CalculateNetResult();			//��������������
float TestNet();					//��������
void TrainNet();					//ѡ����Ի�ѵ��
void RandomInitializationWeight();	//�����ʼ����ֵ
void CalculateNeuronValue();		//���������Ԫ��ֵ
void BackPropagation();				//���򴫲�������Ȩֵ
void ClearTarget();					//����Target[]

unsigned char iPicture[pixels][pixels] = {0};	//�����MNIST���ݿ�ͼƬ����
unsigned char Label;							//�����MNIST���ݿ��ǩ
unsigned char* p = &Label;

double WeightInputToOutput[NumWeight] = {0};		//�������-����㡿֮������2����Ԫ���Ȩ��W
double OldWeightInputToOutput[NumWeight] =  {0};	//�������-����㡿֮������2����Ԫ��ľ�Ȩ��W��Ϊ�˷��򴫲����¾�Ȩ�ظ�ȡ0.25��0.75��

double NetsumOutput[10] = {0};		//�������Ԫ�������Ȩ��
double SigmoidOutput[10] = {0};		//�������Ԫ�������������(�˴��õ������Ϊsigmoid����)

int target[10] = {0};				//Ŀ�����ֵ
double EorrorOfOutput[10] = {0};	//ÿ���������Ԫ�����ֵ��ʵ�����ֵ��Ŀ��ֵ�Ĳ

//�����---->������Ȩֵ����
double PD_WeightInputToOutput[NumWeight] = {0}; //��ƫ��
double PD_EorrorToSigmoidOutput[10] = {0};
double PD_SigmoidOutputToNetsumOutput[10] = {0};
double PD_NetsumOutputToWeightInputToOutput[NumWeight] = {0};

float LearningRate = 0.0005; //ѧϰ����

int Correct = 0; //ʶ����ȷ��


void main()
{
	int a, i = 0;
	float CorrectRate;
	int MaxCorrect = 0;

	//RandomInitializationWeight();
	ReadWeightData();
	printf("ѧϰ���ʣ�%f\n" , LearningRate);

	CorrectRate = TestNet();

	printf("��ȷ����%d ��ȷ�ʣ�%.4f%%\n", Correct, CorrectRate * 100);

	//for ( ;  ; )
	//{
	//	i++;
	//	printf("��%d��ѵ����\n", i);

	//	TrainNet();//ѵ������

	//	CorrectRate = TestNet();
	//	printf("��ȷ����%d ��ȷ�ʣ�%.4f%%\n", Correct, CorrectRate * 100);

	//	if (MaxCorrect < Correct)
	//	{
	//		MaxCorrect = Correct;
	//		WriteWeightData();
	//	}
	//}
}

//���ļ�����ʹ�ñ����Ȩ��
void ReadWeightData()
{
	int iNum = 0; //�����-���������Ԫ����

	FILE *fpReadItoO = fopen("d:\\WeightItoOData201812202048.wet","rb");
	if(fpReadItoO == NULL)
	{
		printf("WeightItoOData201812202048.wet�ļ������ڣ�\n");
		return;
	}

	//�����Ƕ����ݣ������������ݴ浽����WeightInputToOutput[NumWeight]��
	iNum = fread(WeightInputToOutput, sizeof(double), NumWeight, fpReadItoO);
	if(iNum != NumWeight)
	{
		printf("�����ݴ浽����WeightInputToOutput[NumWeight]���󣡣���\n");
	}
	printf("�������-�������Ȩ�����ݳɹ�\n");

	fclose(fpReadItoO);

	return;
}

//д�ļ�����������ǰ���õ�Ȩ��
void WriteWeightData()
{
	int iNum = 0;
	FILE *fpWriteInputToOutput = fopen("d:\\WeightItoOData201812202048.wet","wb+");
	if(fpWriteInputToOutput == NULL)
	{
		printf("����WeightItoOData201812202048.wet�ļ�ʧ�ܣ�\n");
		return 0;
	}

	//�������-�������Ȩ��д�뵽WeightItoOData201812202048.wet�ļ���
	iNum = fwrite(WeightInputToOutput, sizeof(double), NumWeight, fpWriteInputToOutput);
	if (iNum != NumWeight)
	{
		printf("дWeightItoOData201812202048.wet�ļ�ʧ�ܣ�");
	}
	printf("���������-�������Ȩ�������Ѿ�����\n");

	fclose(fpWriteInputToOutput);
}

//�����ʼ����ֵ
void RandomInitializationWeight()
{
	int m = 0;

	srand((unsigned int)time(NULL)); //��ϵͳʱ�����������

	for(m = 0; m < NumWeight; m++)
	{
		WeightInputToOutput[m] = (rand()/(double)(RAND_MAX))/20000; //�������-����㡿֮������2����Ԫ���Ȩ��W

		if (WeightInputToOutput[m] == 0)
		{
			WeightInputToOutput[m] = (rand()/(double)(RAND_MAX))/20000; //�������-����㡿֮������2����Ԫ���Ȩ��W
		}
	}
}

//ѵ����Ԫ����
void TrainNet()
{
	int i = 0;
	int m = 0;

	for (i = 0; i < TestNumber; i++)
	{
		ReadPicData(iPicture, p, i);

		for (m = 0; m < TrainTimes; m++)
		{
			CalculateNeuronValue(); //������Ԫ��ֵ	
			BackPropagation();
		}
	}
}

//�ܲ�������
float TestNet()
{
	int i, result = 0;
	float CorrectRate = 0; 
	Correct = 0;

	for(i = 0; i < TestNumber; i++)
	{
		ReadPicData(iPicture, p, i);

		if ((result = CalculateNetResult()) == Label)
		{	
			Correct++;
		}
	}

	return CorrectRate = (((float)Correct) / TestNumber);//ʶ����
}

int ReadPicData(unsigned char* data, unsigned char* p, int iNum)
{
	int iCheck = 0;

	FILE *fp_image = fopen("d:\\train-images.idx", "rb");//�����������(b)�ļ�train-images.idx����ֻ��(r)�ķ�ʽ�򿪣�
	FILE *fp_label = fopen("d:\\train-labels.idx", "rb");//�����
	//FILE *fp_image = fopen("d:\\t10k_images.idx", "rb");//�����������(b)�ļ�t10k-images.idx����ֻ��(r)�ķ�ʽ�򿪣�
	//FILE *fp_label = fopen("d:\\t10k_labels.idx", "rb");//�����
	if (!fp_image || !fp_label) 
		return 1;

	fseek(fp_image, 16, SEEK_SET);//���ļ���ʼλ��ƫ��16�ֽڣ���λ�������ݿ�ʼ
	fseek(fp_image, iNum * pixels*pixels, SEEK_CUR);//�����ļ����ݵ�λ�ôӵ�ǰ����ƶ�iNum��ͼ����fread���õ�Ч���Ƕ���iNum - 1��ͼ
	iCheck = fread(data, sizeof(char), pixels * pixels, fp_image);//���ļ�(fp_image)�ж�(pixels * pixels)�ֽ�������һ�Σ���data��
	if (iCheck != pixels * pixels)
	{
		printf("��ͼƬ�ļ�ʧ�ܣ�");
	}

	fseek(fp_label, 8, SEEK_SET);//���ļ���ʼλ��ƫ��8�ֽڣ���λ��ǩ����
	fseek(fp_label, iNum, SEEK_CUR);//���ļ���ǰλ��ƫ��iNum�ֽڣ���λ��ǩ����
	iCheck = fread(p, 1, 1, fp_label);
	if (iCheck != 1)
	{
		printf("��Label�ļ�ʧ�ܣ�");
	}

	fclose(fp_image);
	fclose(fp_label);

	return 0;
}

//������Ԫ��ֵ
void CalculateNeuronValue()
{
	int i, j = 0;					
	int m = 0;

	////////////////�����������Ԫ��ֵ////////////////
	for (m = 0; m < 10; m++)
	{
		NetsumOutput[m] = 0;
	}

	for(m = 0; m < 10; m++) //�������Ԫ����Ϊ10
	{
		for(j = 0; j < pixels; j++)
		{
			for (i = 0; i < pixels; i++)
			{
				NetsumOutput[m] += iPicture[j][i] * WeightInputToOutput[m * pixels * pixels + (j * pixels + i)]; //���������������Ԫȫ����
			}
		}
	}

	////////////////���������sigmoid����ֵ////////////////
	for(m = 0; m < 10; m++)
	{
		SigmoidOutput[m] = 1 / (1 + exp( - NetsumOutput[m]));
	}
}

//���򴫲�
void BackPropagation()
{
	int i, j = 0;					
	int m, n = 0;

	ClearTarget();
	target[Label] = 1; //Ŀ�����ֵ


	//*****************���򴫲�����2.�����---->������Ȩֵ���£���ʽ����*****************
	//////////��֪��Ȩ�ز���WeightInputToOutput[m]�������������˶���Ӱ�죬��������������WeightInputToOutput[m]��ƫ�����

	for(m = 0; m < 10; m++)
	{
		//SigmoidOutput[m]�������������˶���Ӱ��
		PD_EorrorToSigmoidOutput[m] = - (target[m] - SigmoidOutput[m]) / 5; 

		//out_o[m]---->NetsumOutput[m]
		PD_SigmoidOutputToNetsumOutput[m] = SigmoidOutput[m] * (1 - SigmoidOutput[m]); 
	}		

	//NetsumOutput[n]---->WeightInputToOutput[n]
	for(m = 0; m < 10; m++)
	{
		for(j = 0; j < pixels; j++)
		{
			for(i = 0; i < pixels; i++)
			{
				PD_NetsumOutputToWeightInputToOutput[m * pixels * pixels + (j * pixels + i)] = iPicture[j][i];
			}
		}
	}		

	for(m = 0; m < 10; m++)
	{
		for(j = 0; j < pixels; j++)
		{
			for(i = 0; i < pixels; i++)
			{
				//��ʽ������ƫ��
				PD_WeightInputToOutput[m * pixels * pixels + (j * pixels + i)] = 
					PD_EorrorToSigmoidOutput[m] * 
					PD_SigmoidOutputToNetsumOutput[m] * 
					PD_NetsumOutputToWeightInputToOutput[m * pixels * pixels + (j * pixels + i)];

				//��Ȩ�ر���0.75
				OldWeightInputToOutput[m * pixels * pixels + (j * pixels + i)] = WeightInputToOutput[m * pixels * pixels + (j * pixels + i)] * 0.9; 

				//����WeightInputToOutput[m]��ֵ
				WeightInputToOutput[m * pixels * pixels + (j * pixels + i)] = 
					WeightInputToOutput[m * pixels * pixels + (j * pixels + i)] - LearningRate * PD_WeightInputToOutput[m * pixels * pixels + (j * pixels + i)];

				//��Ȩ���Ǹ�����0.25
				WeightInputToOutput[m * pixels * pixels + (j * pixels + i)] = 
					WeightInputToOutput[m * pixels * pixels + (j * pixels + i)] * 0.1 + OldWeightInputToOutput[m * pixels * pixels + (j * pixels + i)]; 
			}
		}
	}		
}


//����Target[]
void ClearTarget()
{
	int i = 0;

	for (i = 0; i < 10; i++)
	{
		target[i] = 0;
	}
}


//��������ʶ����
int CalculateNetResult()
{
	int i = 0, result = 0; 
	CalculateNeuronValue(); //������Ԫ��ֵ	

	for (i = 1; i < 10; i++)
	{
		if (SigmoidOutput[result] < SigmoidOutput[i])
		{
			result = i;
		}
	}

	return result;//ʶ����
}