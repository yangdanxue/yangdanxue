#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define pixels						28		//ͼƬ������28*28
#define NeuronNumHidden1			100		//����1����Ԫ����
#define NeuronNumHidden2			100		//����2����Ԫ����
#define NeuronNumOutput				10		//�������Ԫ����
#define TrainTimes					1	    //ѵ������
#define TestNumber					60000	//�ܲ���ͼƬ������
#define OldWeightPercentage			0.9   	//���򴫲�����Ȩ��ʱ��Ȩ��ռ��
#define NewWeightPercentage			0.1   	//���򴫲�����Ȩ��ʱ��Ȩ��ռ��

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

//����Ȩ��
double WeightInputToHidden1[pixels * pixels * NeuronNumHidden1] = {0};
double WeightHidden1ToHidden2[NeuronNumHidden1 * NeuronNumHidden2] = {0};
double WeightHidden2ToOutput[NeuronNumHidden2 * NeuronNumOutput] = {0};		

//���㷴�򴫲����Ȩ�ر����ı���
double OldWeightInputToHidden1[pixels * pixels * NeuronNumHidden1] = {0};
double OldWeightHidden1ToHidden2[NeuronNumHidden1 * NeuronNumHidden2] = {0};
double OldWeightHidden2ToOutput[NeuronNumHidden2 * NeuronNumOutput] = {0};	

//����ƫ����
double Bias_Input = 0;
double Bias_Hidden = 0;

//������Ԫֵ
double NetHidden1[NeuronNumHidden1] = {0};	
double NetHidden2[NeuronNumHidden2] = {0};	
double NetOutput[NeuronNumOutput] = {0};	

//���㼤���ֵ��Sigmoid������
double SigmoidHidden1[NeuronNumHidden1] = {0};
double SigmoidHidden2[NeuronNumHidden2] = {0};
double SigmoidOutput[NeuronNumOutput] = {0};

int target[NeuronNumOutput] = {0};				//Ŀ�����ֵ
double ErrorOfOutput[NeuronNumOutput] = {0};	//ÿ���������Ԫ�����ֵ��ʵ�����ֵ��Ŀ��ֵ�Ĳ

//�������ֵ
double PD_ErrorToNetOutput[NeuronNumOutput] = {0};
double Delta_Output[NeuronNumOutput] = {0};
double PD_ErrorToNetHidden2[NeuronNumHidden2] = {0};
double Delta_Hidden2[NeuronNumHidden2] = {0};
double PD_ErrorToNetHidden1[NeuronNumHidden1] = {0};
double Delta_Hidden1[NeuronNumHidden1] = {0};

//��2����---->������Ȩֵ����
double PD_WeightHidden2ToOutput[NeuronNumHidden2 * NeuronNumOutput] = {0};
double PD_ErrorToSigmoidOutput[NeuronNumOutput] = {0};
double PD_SigmoidOutputToNetOutput[NeuronNumOutput] = {0};
double PD_NetOutputToWeightHidden2ToOutput[NeuronNumHidden2 * NeuronNumOutput] = {0};

//����1��---->����2���Ȩֵ����
double PD_NetOutputToSigmoidHidden2[NeuronNumHidden2 * NeuronNumOutput] = {0};
double PD_WeightHidden1ToHidden2[NeuronNumHidden1 * NeuronNumHidden2] = {0};
double PD_SigmoidHidden2ToNetHidden2[NeuronNumHidden2] = {0};
double PD_NetHidden2ToWeightHidden1ToHidden2[NeuronNumHidden1 * NeuronNumHidden2] = {0};

//�����---->����1���Ȩֵ����
double PD_NetHidden2ToSigmoidHidden1[NeuronNumHidden1 * NeuronNumHidden2] = {0};
double PD_WeightInputToHidden1[pixels * pixels * NeuronNumHidden1] = {0};
double PD_SigmoidHidden1ToNetHidden1[NeuronNumHidden1] = {0};
double PD_NetHidden1ToWeightInputToHidden1[pixels * pixels * NeuronNumHidden1] = {0};

double LearningRate = 0.03; //ѧϰ����

int Correct = 0; //ʶ����ȷ��


void main()
{
	int i = 0;
	float CorrectRate = 0;
	int MaxCorrect = 0;
	int times = 0;

	//RandomInitializationWeight();
	ReadWeightData();

	printf("ѧϰ���ʣ�%f\n" , LearningRate);

	CorrectRate = TestNet();
	printf("��ȷ����%d ��ȷ�ʣ�%.4f%%\n", Correct, CorrectRate * 100);

	//for (;;)
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
	int iNum = 0; //�����-����1������Ԫ����

	FILE *fpReadItoH1 = fopen("d:\\WeightItoH1Data201810191617.wet","rb");
	FILE *fpReadH1toH2 = fopen("d:\\WeightH1toH2Data201810191617.wet","rb");
	FILE *fpReadH2toO = fopen("d:\\WeightH2toOData201810191617.wet","rb");
	if(fpReadItoH1 == NULL)
	{
		printf("WeightItoH1Data201810191617.wet�ļ������ڣ�\n");
		return;
	}
	if(fpReadH1toH2 == NULL)
	{
		printf("WeightH1toH2Data201810191617.wet�ļ������ڣ�\n");
		return;
	}
	if(fpReadH2toO == NULL)
	{
		printf("WeightH2toOData201810191617.wet�ļ������ڣ�\n");
		return;
	}

	//�����Ƕ����ݣ������������ݴ浽����WeightInputToHidden11[m]��
	iNum = fread(WeightInputToHidden1, sizeof(double), pixels * pixels * NeuronNumHidden1, fpReadItoH1);
	if(iNum != pixels * pixels * NeuronNumHidden1)
	{
		printf("�����ݴ浽����WeightInputToHidden1[pixels * pixels * NeuronNumHidden1]���󣡣���\n");
	}
	printf("�������-����1����Ȩ�����ݳɹ�\n");

	//�����Ƕ����ݣ������������ݴ浽����WeightHidden11ToHidden12[m]��
	iNum = fread(WeightHidden1ToHidden2, sizeof(double), NeuronNumHidden1 * NeuronNumHidden2, fpReadH1toH2);
	if(iNum != NeuronNumHidden1 * NeuronNumHidden2)
	{
		printf("�����ݴ浽����WeightHidden1ToHidden2[NeuronNumHidden1 * NeuronNumHidden2]���󣡣���\n");
	}
	printf("������1��-����2����Ȩ�����ݳɹ�\n");

	//�����Ƕ����ݣ������������ݴ浽����WeightHidden2ToOutput[NeuronNumHidden * 10]��
	iNum = fread(WeightHidden2ToOutput, sizeof(double), NeuronNumHidden2 * NeuronNumOutput, fpReadH2toO);
	if(iNum != NeuronNumHidden2 * NeuronNumOutput)
	{
		printf("�����ݴ浽����WeightHidden2ToOutput[NeuronNumHidden2 * NeuronNumOutput]���󣡣���\n");
	}
	printf("������2��-�������Ȩ�����ݳɹ�\n");

	fclose(fpReadItoH1);
	fclose(fpReadH1toH2);
	fclose(fpReadH2toO);

	return;
}


//д�ļ�����������ǰ���õ�Ȩ��
void WriteWeightData()
{
	int iNum = 0;
	FILE *fpWriteInputToHidden1 = fopen("d:\\WeightItoH1Data201810191617.wet","wb+");
	FILE *fpWriteHidden1ToHidden2 = fopen("d:\\WeightH1toH2Data201810191617.wet","wb+");
	FILE *fpWriteHidden2ToOutput = fopen("d:\\WeightH2toOData201810191617.wet","wb+");
	if(fpWriteInputToHidden1 == NULL)
	{
		printf("����WeightItoH1Data201810191617.wet�ļ�ʧ�ܣ�\n");
		return 0;
	}
	if(fpWriteHidden1ToHidden2 == NULL)
	{
		printf("����WeightH1toH2Data201810191617.wet�ļ�ʧ�ܣ�\n");
		return 0;
	}
	if(fpWriteHidden2ToOutput == NULL)
	{
		printf("����WeightH2toOData201810191617.wet�ļ�ʧ�ܣ�\n");
		return 0;
	}

	//�������-����1����Ȩ��д�뵽WeightItoH1Data201810191617.wet�ļ���
	iNum = fwrite(WeightInputToHidden1, sizeof(double), pixels * pixels * NeuronNumHidden1, fpWriteInputToHidden1);
	if (iNum != pixels * pixels * NeuronNumHidden1)
	{
		printf("дWeightItoH1Data201810191617.wet�ļ�ʧ�ܣ�");
	}
	printf("���������-����1����Ȩ�������Ѿ�����\n");

	//����1��-����2����Ȩ��д�뵽WeightH1toH2Data201810191617.wet�ļ���
	iNum = fwrite(WeightHidden1ToHidden2, sizeof(double), NeuronNumHidden1 * NeuronNumHidden2, fpWriteHidden1ToHidden2);
	if (iNum != NeuronNumHidden1 * NeuronNumHidden2)
	{
		printf("дWeightH1toH2Data201810191617.wet�ļ�ʧ�ܣ�");
	}
	printf("��������1��-����2����Ȩ�������Ѿ�����\n");


	//������2��-�������Ȩ��д�뵽WeightH2toOData201810191617.wet�ļ���
	iNum = fwrite(WeightHidden2ToOutput, sizeof(double), NeuronNumHidden2 * NeuronNumOutput, fpWriteHidden2ToOutput);
	if (iNum != NeuronNumHidden2 * NeuronNumOutput)
	{		
		printf("дWeightH2toOData201810191617.wet�ļ�ʧ�ܣ�");
	}
	printf("��������2��-�������Ȩ�������Ѿ�����\n");

	fclose(fpWriteInputToHidden1);
	fclose(fpWriteHidden1ToHidden2);
	fclose(fpWriteHidden2ToOutput);
}


//�����ʼ����ֵ
void RandomInitializationWeight()
{
	int m, n, k = 0;

	for(m = 0; m < pixels * pixels * NeuronNumHidden1; m++)
	{
		//WeightInputToHidden1[m] = 0;
		WeightInputToHidden1[m] = (rand()/(double)(RAND_MAX))/2000;
	}

	for(k = 0; k < NeuronNumHidden1 * NeuronNumHidden2; k++)
	{
		//WeightHidden1ToHidden2[k] = 0;
		WeightHidden1ToHidden2[k] = (rand()/(double)(RAND_MAX))/400;
	}

	for(n = 0; n < NeuronNumHidden2 * NeuronNumOutput; n++)
	{
		//WeightHidden2ToOutput[n] = 0;
		WeightHidden2ToOutput[n] = (rand()/(double)(RAND_MAX))/400;
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
	int m, n = 0;


	////////////////��������1����Ԫ��ֵ////////////////
	for (m = 0; m < NeuronNumHidden1; m++)
	{
		NetHidden1[m] = 0;
	}

	for (m = 0; m < NeuronNumHidden1; m++)
	{
		for(j = 0; j < pixels; j++)
		{
			for (i = 0; i < pixels; i++)
			{
				NetHidden1[m] += iPicture[j][i] * WeightInputToHidden1[m * pixels * pixels + (j * pixels + i)];
			}
		}
	}

	//for (m = 0; m < NeuronNumHidden1; m++)
	//{
	//	NetHidden1[m] = NetHidden1[m] / 32;
	//}


	//for (m = 0; m < NeuronNumHidden1; m++)
	//{
	//	NetHidden1[m] = NetHidden1[m] + Bias_Input * 1;
	//}


	////////////////��������1��sigmoid����ֵ)////////////////
	for(m = 0; m < NeuronNumHidden1; m++)
	{
		SigmoidHidden1[m] = 1 / (1 + exp( - NetHidden1[m]));
	}










	////////////////��������2����Ԫ��ֵ////////////////
	for (n = 0; n < NeuronNumHidden2; n++)
	{
		NetHidden2[n] = 0;
	}

	for (n = 0; n < NeuronNumHidden2; n++)
	{
		for (m = 0; m < NeuronNumHidden1; m++)
		{
			NetHidden2[n] += SigmoidHidden1[m] * WeightHidden1ToHidden2[n * NeuronNumHidden1 + m];
		}
	}

	////////////////��������2��sigmoid����ֵ)////////////////
	for(n = 0; n < NeuronNumHidden2; n++)
	{
		SigmoidHidden2[n] = 1 / (1 + exp( - NetHidden2[n]));
	}










	////////////////�����������Ԫ��ֵ////////////////
	for (n = 0; n < NeuronNumOutput; n++)
	{
		NetOutput[n] = 0;
	}

	for(n = 0; n < NeuronNumOutput; n++) //�������Ԫ����Ϊ10
	{
		for(m = 0; m < NeuronNumHidden2; m++) //���ز���Ԫ����ΪNeuronNumHidden2
		{
			NetOutput[n] += SigmoidHidden2[m] * WeightHidden2ToOutput[n * NeuronNumHidden2 + m]; //���ز�����������ԪҪһһ����
		}
	}

	//for(n = 0; n < NeuronNumOutput; n++) //�������Ԫ����Ϊ10
	//{
	//	NetOutput[n] = NetOutput[n] + Bias_Hidden * 1;
	//}

	////////////////���������sigmoid����ֵ////////////////
	for(n = 0; n < NeuronNumOutput; n++)
	{
		SigmoidOutput[n] = 1 / (1 + exp( - NetOutput[n]));
	}
}

//���򴫲�
void BackPropagation()
{
	int i, j = 0;					
	int m, n = 0;
	int temp = 0;

	ClearTarget();
	target[Label] = 1; //Ŀ�����ֵ


	//****************��������Delta_Output****************
	for(n = 0; n < NeuronNumOutput; n++)
	{
		//Error[total]---->SigmoidOutput[n]
		PD_ErrorToSigmoidOutput[n] = - (target[n] - SigmoidOutput[n]); 

		//SigmoidOutput[n]---->NetOutput[n]
		PD_SigmoidOutputToNetOutput[n] = SigmoidOutput[n] * (1 - SigmoidOutput[n]); 

		//Error[n]---->NetOutput[n]
		PD_ErrorToNetOutput[n] = PD_ErrorToSigmoidOutput[n] * PD_SigmoidOutputToNetOutput[n]; 

		//���������ֵ���������������Ԫֵ��ƫ��
		Delta_Output[n] = PD_ErrorToNetOutput[n];
	}		









	//****************����WeightHidden2ToOutput****************
	for(n = 0; n < NeuronNumOutput; n++)
	{
		for(m = 0; m < NeuronNumHidden2; m++)
		{
			//NetOutput[m]---->WeightHidden2ToOutput[m]
			PD_NetOutputToWeightHidden2ToOutput[n * NeuronNumHidden2 + m] = SigmoidHidden2[m];
		}
	}		

	for(n = 0; n < NeuronNumOutput; n++)
	{
		for(m = 0; m < NeuronNumHidden2; m++)
		{
			//��ʽ������ƫ��
			PD_WeightHidden2ToOutput[n * NeuronNumHidden2 + m] = Delta_Output[n] * PD_NetOutputToWeightHidden2ToOutput[n * NeuronNumHidden2 + m];

			//��Ȩ�ر���0.9
			OldWeightHidden2ToOutput[n * NeuronNumHidden2 + m] = WeightHidden2ToOutput[n * NeuronNumHidden2 + m] * OldWeightPercentage; 

			//����WeightHidden2ToOutput[n]��ֵ
			WeightHidden2ToOutput[n * NeuronNumHidden2 + m] = WeightHidden2ToOutput[n * NeuronNumHidden2 + m] - LearningRate * PD_WeightHidden2ToOutput[n * NeuronNumHidden2 + m];

			//��Ȩ���Ǹ�����0.1
			WeightHidden2ToOutput[n * NeuronNumHidden2 + m] = WeightHidden2ToOutput[n * NeuronNumHidden2 + m] * NewWeightPercentage + OldWeightHidden2ToOutput[n * NeuronNumHidden2 + m]; 
		}
	}	










	//****************����2�����Delta_Hidden2****************
	for (temp = 0; temp < NeuronNumHidden2; temp++)
	{
		PD_ErrorToNetHidden2[temp] = 0;
	}

	for(m = 0; m < NeuronNumHidden2; m++)
	{
		for(n = 0; n < NeuronNumOutput; n++)
		{
			//NetOutput[n]---->SigmoidHidden2[n]
			PD_NetOutputToSigmoidHidden2[n * NeuronNumHidden2 + m] = WeightHidden2ToOutput[n * NeuronNumHidden2 + m];

			//SigmoidHidden2[m]---->NetHidden2[m]
			PD_SigmoidHidden2ToNetHidden2[m] = SigmoidHidden2[m] * (1 - SigmoidHidden2[m]);

			//Error[m]---->NetHidden2[m]
			PD_ErrorToNetHidden2[m] += Delta_Output[n] * PD_NetOutputToSigmoidHidden2[n * NeuronNumHidden2 + m] * PD_SigmoidHidden2ToNetHidden2[m]; 

			//���������ֵ���������������Ԫֵ��ƫ��
			Delta_Hidden2[m] = PD_ErrorToNetHidden2[m];
		}
	}










	//****************����WeightHidden1ToHidden2****************
	for(n = 0; n < NeuronNumHidden2; n++)
	{
		for(m = 0; m < NeuronNumHidden1; m++)
		{
			//NetHidden2[m]---->WeightHidden1ToHidden2[m]
			PD_NetHidden2ToWeightHidden1ToHidden2[n * NeuronNumHidden1 + m] = SigmoidHidden1[m];
		}
	}		

	for(n = 0; n < NeuronNumHidden2; n++)
	{
		for(m = 0; m < NeuronNumHidden1; m++)
		{
			//��ʽ������ƫ��
			PD_WeightHidden1ToHidden2[n * NeuronNumHidden1 + m] = Delta_Hidden2[n] * PD_NetHidden2ToWeightHidden1ToHidden2[n * NeuronNumHidden1 + m];

			//��Ȩ�ر���0.9
			OldWeightHidden1ToHidden2[n * NeuronNumHidden1 + m] = WeightHidden1ToHidden2[n * NeuronNumHidden1 + m] * OldWeightPercentage; 

			//����WeightHidden1ToHidden2[n]��ֵ
			WeightHidden1ToHidden2[n * NeuronNumHidden1 + m] = WeightHidden1ToHidden2[n * NeuronNumHidden1 + m] - LearningRate * PD_WeightHidden1ToHidden2[n * NeuronNumHidden1 + m];

			//��Ȩ���Ǹ�����0.1
			WeightHidden1ToHidden2[n * NeuronNumHidden1 + m] = WeightHidden1ToHidden2[n * NeuronNumHidden1 + m] * NewWeightPercentage + OldWeightHidden1ToHidden2[n * NeuronNumHidden1 + m]; 
		}
	}	










	//****************����1�����Delta_Hidden1****************
	for (temp = 0; temp < NeuronNumHidden1; temp++)
	{
		PD_ErrorToNetHidden1[temp] = 0;
	}

	for(m = 0; m < NeuronNumHidden1; m++)
	{
		for(n = 0; n < NeuronNumHidden2; n++)
		{
			//NetHidden2[n]---->SigmoidHidden1[n]
			PD_NetHidden2ToSigmoidHidden1[n * NeuronNumHidden1 + m] = WeightHidden1ToHidden2[n * NeuronNumHidden1 + m];

			//SigmoidHidden1[m]---->NetHidden1[m]
			PD_SigmoidHidden1ToNetHidden1[m] = SigmoidHidden1[m] * (1 - SigmoidHidden1[m]);

			//Error[m]---->NetHidden1[m]
			PD_ErrorToNetHidden1[m] += Delta_Hidden2[n] * PD_NetHidden2ToSigmoidHidden1[n * NeuronNumHidden1 + m] * PD_SigmoidHidden1ToNetHidden1[m]; 

			//���������ֵ���������������Ԫֵ��ƫ��
			Delta_Hidden1[m] = PD_ErrorToNetHidden1[m];
		}
	}










	//****************����WeightInputToHidden1****************
	for (m = 0; m < NeuronNumHidden1; m++)
	{
		for(j = 0; j < pixels; j++)
		{
			for (i = 0; i < pixels; i++)
			{
				//NetHidden1[n]---->WeightInputToHidden1[n]
				PD_NetHidden1ToWeightInputToHidden1[m * pixels * pixels + (j * pixels + i)] = iPicture[j][i];
			}
		}
	}


	for (m = 0; m < NeuronNumHidden1; m++)
	{
		for(j = 0; j < pixels; j++)
		{
			for (i = 0; i < pixels; i++)
			{
				PD_WeightInputToHidden1[m * pixels * pixels + (j * pixels + i)] = Delta_Hidden1[m] * PD_NetHidden1ToWeightInputToHidden1[m * pixels * pixels + (j * pixels + i)];

				//��Ȩ�ر���0.9
				OldWeightInputToHidden1[m * pixels * pixels + (j * pixels + i)] = WeightInputToHidden1[m * pixels * pixels + (j * pixels + i)] * OldWeightPercentage;

				////����WeightInputToHidden1[m]��ֵ
				WeightInputToHidden1[m * pixels * pixels + (j * pixels + i)] = 
					WeightInputToHidden1[m * pixels * pixels + (j * pixels + i)] - LearningRate * PD_WeightInputToHidden1[m * pixels * pixels + (j * pixels + i)]; 

				//��Ȩ���Ǹ�����0.1
				WeightInputToHidden1[m * pixels * pixels + (j * pixels + i)] = 
					WeightInputToHidden1[m * pixels * pixels + (j * pixels + i)] * NewWeightPercentage + OldWeightInputToHidden1[m * pixels * pixels + (j * pixels + i)];
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