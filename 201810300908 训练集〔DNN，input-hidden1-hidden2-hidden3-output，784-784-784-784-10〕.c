#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define pixels						28		//ͼƬ������28*28
#define NeuronNumHidden1			784		//����1����Ԫ����
#define NeuronNumHidden2			784		//����2����Ԫ����
#define NeuronNumHidden3			784		//����3����Ԫ����
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
double WeightHidden2ToHidden3[NeuronNumHidden2 * NeuronNumHidden3] = {0};
double WeightHidden3ToOutput[NeuronNumHidden3 * NeuronNumOutput] = {0};		

//���㷴�򴫲����Ȩ�ر����ı���
double OldWeightInputToHidden1[pixels * pixels * NeuronNumHidden1] = {0};
double OldWeightHidden1ToHidden2[NeuronNumHidden1 * NeuronNumHidden2] = {0};
double OldWeightHidden2ToHidden3[NeuronNumHidden2 * NeuronNumHidden3] = {0};
double OldWeightHidden3ToOutput[NeuronNumHidden3 * NeuronNumOutput] = {0};	

//����ƫ����
double Bias_Input = 0;
double Bias_Hidden = 0;

//������Ԫֵ
double NetHidden1[NeuronNumHidden1] = {0};	
double NetHidden2[NeuronNumHidden2] = {0};	
double NetHidden3[NeuronNumHidden3] = {0};	
double NetOutput[NeuronNumOutput] = {0};	

//���㼤���ֵ��Sigmoid������
double SigmoidHidden1[NeuronNumHidden1] = {0};
double SigmoidHidden2[NeuronNumHidden2] = {0};
double SigmoidHidden3[NeuronNumHidden3] = {0};
double SigmoidOutput[NeuronNumOutput] = {0};

int target[NeuronNumOutput] = {0};				//Ŀ�����ֵ
double ErrorOfOutput[NeuronNumOutput] = {0};	//ÿ���������Ԫ�����ֵ��ʵ�����ֵ��Ŀ��ֵ�Ĳ

//�������ֵ
double PD_ErrorToNetOutput[NeuronNumOutput] = {0};
double Delta_Output[NeuronNumOutput] = {0};
double PD_ErrorToNetHidden3[NeuronNumHidden3] = {0};
double Delta_Hidden3[NeuronNumHidden3] = {0};
double PD_ErrorToNetHidden2[NeuronNumHidden2] = {0};
double Delta_Hidden2[NeuronNumHidden2] = {0};
double PD_ErrorToNetHidden1[NeuronNumHidden1] = {0};
double Delta_Hidden1[NeuronNumHidden1] = {0};

//����3��---->������Ȩֵ����
double PD_WeightHidden3ToOutput[NeuronNumHidden3 * NeuronNumOutput] = {0};
double PD_ErrorToSigmoidOutput[NeuronNumOutput] = {0};
double PD_SigmoidOutputToNetOutput[NeuronNumOutput] = {0};
double PD_NetOutputToWeightHidden3ToOutput[NeuronNumHidden3 * NeuronNumOutput] = {0};

//����2��---->����3���Ȩֵ����
double PD_NetOutputToSigmoidHidden3[NeuronNumHidden3 * NeuronNumOutput] = {0};
double PD_SigmoidHidden3ToNetHidden3[NeuronNumHidden3] = {0};
double PD_NetHidden3ToWeightHidden2ToHidden3[NeuronNumHidden2 * NeuronNumHidden3] = {0};
double PD_WeightHidden2ToHidden3[NeuronNumHidden2 * NeuronNumHidden3] = {0};
double PD_NetHidden3ToSigmoidHidden2[NeuronNumHidden2 * NeuronNumHidden3] = {0};

//����1��---->����2���Ȩֵ����
double PD_WeightHidden1ToHidden2[NeuronNumHidden1 * NeuronNumHidden2] = {0};
double PD_SigmoidHidden2ToNetHidden2[NeuronNumHidden2] = {0};
double PD_NetHidden2ToWeightHidden1ToHidden2[NeuronNumHidden1 * NeuronNumHidden2] = {0};

//�����---->����1���Ȩֵ����
double PD_NetHidden2ToSigmoidHidden1[NeuronNumHidden1 * NeuronNumHidden2] = {0};
double PD_WeightInputToHidden1[pixels * pixels * NeuronNumHidden1] = {0};
double PD_SigmoidHidden1ToNetHidden1[NeuronNumHidden1] = {0};
double PD_NetHidden1ToWeightInputToHidden1[pixels * pixels * NeuronNumHidden1] = {0};

double LearningRate = 0.05; //ѧϰ����

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

	FILE *fpReadItoH1 = fopen("d:\\WeightItoH1Data201810300908.wet","rb");
	FILE *fpReadH1toH2 = fopen("d:\\WeightH1toH2Data201810300908.wet","rb");
	FILE *fpReadH2toH3 = fopen("d:\\WeightH2toH3Data201810300908.wet","rb");
	FILE *fpReadH3toO = fopen("d:\\WeightH3toOData201810300908.wet","rb");
	if(fpReadItoH1 == NULL)
	{
		printf("WeightItoH1Data201810300908.wet�ļ������ڣ�\n");
		return;
	}
	if(fpReadH1toH2 == NULL)
	{
		printf("WeightH1toH2Data201810300908.wet�ļ������ڣ�\n");
		return;
	}
	if(fpReadH2toH3 == NULL)
	{
		printf("WeightH2toH3Data201810300908.wet�ļ������ڣ�\n");
		return;
	}
	if(fpReadH3toO == NULL)
	{
		printf("WeightH3toOData201810300908.wet�ļ������ڣ�\n");
		return;
	}

	//�����Ƕ����ݣ������������ݴ浽����WeightInputToHidden1[m]��
	iNum = fread(WeightInputToHidden1, sizeof(double), pixels * pixels * NeuronNumHidden1, fpReadItoH1);
	if(iNum != pixels * pixels * NeuronNumHidden1)
	{
		printf("�����ݴ浽����WeightInputToHidden1[pixels * pixels * NeuronNumHidden1]���󣡣���\n");
	}
	printf("�������-����1����Ȩ�����ݳɹ�\n");

	//�����Ƕ����ݣ������������ݴ浽����WeightHidden1ToHidden2[m]��
	iNum = fread(WeightHidden1ToHidden2, sizeof(double), NeuronNumHidden1 * NeuronNumHidden2, fpReadH1toH2);
	if(iNum != NeuronNumHidden1 * NeuronNumHidden2)
	{
		printf("�����ݴ浽����WeightHidden1ToHidden2[NeuronNumHidden1 * NeuronNumHidden2]���󣡣���\n");
	}
	printf("������1��-����2����Ȩ�����ݳɹ�\n");

	//�����Ƕ����ݣ������������ݴ浽����WeightHidden2ToHidden3[m]��
	iNum = fread(WeightHidden2ToHidden3, sizeof(double), NeuronNumHidden2 * NeuronNumHidden3, fpReadH2toH3);
	if(iNum != NeuronNumHidden2 * NeuronNumHidden3)
	{
		printf("�����ݴ浽����WeightHidden2ToHidden3[NeuronNumHidden2 * NeuronNumHidden3]���󣡣���\n");
	}
	printf("������2��-����3����Ȩ�����ݳɹ�\n");

	//�����Ƕ����ݣ������������ݴ浽����WeightHidden3ToOutput[m]��
	iNum = fread(WeightHidden3ToOutput, sizeof(double), NeuronNumHidden3 * NeuronNumOutput, fpReadH3toO);
	if(iNum != NeuronNumHidden3 * NeuronNumOutput)
	{
		printf("�����ݴ浽����WeightHidden3ToOutput[NeuronNumHidden3 * NeuronNumOutput]���󣡣���\n");
	}
	printf("������3��-�������Ȩ�����ݳɹ�\n");

	fclose(fpReadItoH1);
	fclose(fpReadH1toH2);
	fclose(fpReadH2toH3);
	fclose(fpReadH3toO);

	return;
}


//д�ļ�����������ǰ���õ�Ȩ��
void WriteWeightData()
{
	int iNum = 0;
	FILE *fpWriteInputToHidden1 = fopen("d:\\WeightItoH1Data201810300908.wet","wb+");
	FILE *fpWriteHidden1ToHidden2 = fopen("d:\\WeightH1toH2Data201810300908.wet","wb+");
	FILE *fpWriteHidden2ToHidden3 = fopen("d:\\WeightH2toH3Data201810300908.wet","wb+");
	FILE *fpWriteHidden3ToOutput = fopen("d:\\WeightH3toOData201810300908.wet","wb+");
	if(fpWriteInputToHidden1 == NULL)
	{
		printf("����WeightItoH1Data201810300908.wet�ļ�ʧ�ܣ�\n");
		return 0;
	}
	if(fpWriteHidden1ToHidden2 == NULL)
	{
		printf("����WeightH1toH2Data201810300908.wet�ļ�ʧ�ܣ�\n");
		return 0;
	}
	if(fpWriteHidden2ToHidden3 == NULL)
	{
		printf("����WeightH2toH3Data201810300908.wet�ļ�ʧ�ܣ�\n");
		return 0;
	}
	if(fpWriteHidden3ToOutput == NULL)
	{
		printf("����WeightH3toOData201810300908.wet�ļ�ʧ�ܣ�\n");
		return 0;
	}

	//�������-����1����Ȩ��д�뵽WeightItoH1Data201810300908.wet�ļ���
	iNum = fwrite(WeightInputToHidden1, sizeof(double), pixels * pixels * NeuronNumHidden1, fpWriteInputToHidden1);
	if (iNum != pixels * pixels * NeuronNumHidden1)
	{
		printf("дWeightItoH1Data201810300908.wet�ļ�ʧ�ܣ�");
	}
	printf("���������-����1����Ȩ�������Ѿ�����\n");

	//������1��-����2����Ȩ��д�뵽WeightH1toH2Data201810300908.wet�ļ���
	iNum = fwrite(WeightHidden1ToHidden2, sizeof(double), NeuronNumHidden1 * NeuronNumHidden2, fpWriteHidden1ToHidden2);
	if (iNum != NeuronNumHidden1 * NeuronNumHidden2)
	{
		printf("дWeightH1toH2Data201810300908.wet�ļ�ʧ�ܣ�");
	}
	printf("��������1��-����2����Ȩ�������Ѿ�����\n");

	//������2��-����3����Ȩ��д�뵽WeightH2toH3Data201810300908.wet�ļ���
	iNum = fwrite(WeightHidden2ToHidden3, sizeof(double), NeuronNumHidden2 * NeuronNumHidden3, fpWriteHidden2ToHidden3);
	if (iNum != NeuronNumHidden2 * NeuronNumHidden3)
	{
		printf("дWeightH2toH3Data201810300908.wet�ļ�ʧ�ܣ�");
	}
	printf("��������2��-����3����Ȩ�������Ѿ�����\n");

	//������3��-�������Ȩ��д�뵽WeightH3toOData201810300908.wet�ļ���
	iNum = fwrite(WeightHidden3ToOutput, sizeof(double), NeuronNumHidden3 * NeuronNumOutput, fpWriteHidden3ToOutput);
	if (iNum != NeuronNumHidden3 * NeuronNumOutput)
	{		
		printf("дWeightH3toOData201810300908.wet�ļ�ʧ�ܣ�");
	}
	printf("��������3��-�������Ȩ�������Ѿ�����\n");

	fclose(fpWriteInputToHidden1);
	fclose(fpWriteHidden1ToHidden2);
	fclose(fpWriteHidden2ToHidden3);
	fclose(fpWriteHidden3ToOutput);
}


//�����ʼ����ֵ
void RandomInitializationWeight()
{
	int m, n, k = 0;

	for(m = 0; m < pixels * pixels * NeuronNumHidden1; m++)
	{
		WeightInputToHidden1[m] = (rand()/(double)(RAND_MAX))/10000;
	}

	for(k = 0; k < NeuronNumHidden1 * NeuronNumHidden2; k++)
	{
		WeightHidden1ToHidden2[k] = (rand()/(double)(RAND_MAX))/100;
	}

	for(k = 0; k < NeuronNumHidden2 * NeuronNumHidden3; k++)
	{
		WeightHidden2ToHidden3[k] = (rand()/(double)(RAND_MAX))/100;
	}

	for(n = 0; n < NeuronNumHidden3 * NeuronNumOutput; n++)
	{
		WeightHidden3ToOutput[n] = (rand()/(double)(RAND_MAX))/100;
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
	int s, t = 0;


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










	////////////////��������3����Ԫ��ֵ////////////////
	for (s = 0; s < NeuronNumHidden3; s++)
	{
		NetHidden3[s] = 0;
	}

	for (s = 0; s < NeuronNumHidden3; s++)
	{
		for (n = 0; n < NeuronNumHidden2; n++)
		{
			NetHidden3[s] += SigmoidHidden2[n] * WeightHidden2ToHidden3[s * NeuronNumHidden2 + n];
		}
	}

	////////////////��������3��sigmoid����ֵ)////////////////
	for(s = 0; s < NeuronNumHidden3; s++)
	{
		SigmoidHidden3[s] = 1 / (1 + exp( - NetHidden3[s]));
	}










	////////////////�����������Ԫ��ֵ////////////////
	for (t = 0; t < NeuronNumOutput; t++)
	{
		NetOutput[t] = 0;
	}

	for(t = 0; t < NeuronNumOutput; t++) //�������Ԫ����Ϊ10
	{
		for(s = 0; s < NeuronNumHidden3; s++) //���ز���Ԫ����ΪNeuronNumHidden3
		{
			NetOutput[t] += SigmoidHidden3[s] * WeightHidden3ToOutput[t * NeuronNumHidden3 + s]; //���ز�����������ԪҪһһ����
		}
	}

	//for(n = 0; n < NeuronNumOutput; n++) //�������Ԫ����Ϊ10
	//{
	//	NetOutput[n] = NetOutput[n] + Bias_Hidden * 1;
	//}

	////////////////���������sigmoid����ֵ////////////////
	for(t = 0; t < NeuronNumOutput; t++)
	{
		SigmoidOutput[t] = 1 / (1 + exp( - NetOutput[t]));
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









	//****************����WeightHidden3ToOutput****************
	for(n = 0; n < NeuronNumOutput; n++)
	{
		for(m = 0; m < NeuronNumHidden3; m++)
		{
			//NetOutput[m]---->WeightHidden3ToOutput[m]
			PD_NetOutputToWeightHidden3ToOutput[n * NeuronNumHidden3 + m] = SigmoidHidden3[m];
		}
	}		

	for(n = 0; n < NeuronNumOutput; n++)
	{
		for(m = 0; m < NeuronNumHidden3; m++)
		{
			//��ʽ������ƫ��
			PD_WeightHidden3ToOutput[n * NeuronNumHidden3 + m] = Delta_Output[n] * PD_NetOutputToWeightHidden3ToOutput[n * NeuronNumHidden3 + m];

			//��Ȩ�ر���0.9
			OldWeightHidden3ToOutput[n * NeuronNumHidden3 + m] = WeightHidden3ToOutput[n * NeuronNumHidden3 + m] * OldWeightPercentage; 

			//����WeightHidden3ToOutput[n]��ֵ
			WeightHidden3ToOutput[n * NeuronNumHidden3 + m] = WeightHidden3ToOutput[n * NeuronNumHidden3 + m] - LearningRate * PD_WeightHidden3ToOutput[n * NeuronNumHidden3 + m];

			//��Ȩ���Ǹ�����0.1
			WeightHidden3ToOutput[n * NeuronNumHidden3 + m] = WeightHidden3ToOutput[n * NeuronNumHidden3 + m] * NewWeightPercentage + OldWeightHidden3ToOutput[n * NeuronNumHidden3 + m]; 
		}
	}	










	//****************����3�����Delta_Hidden3****************
	for (temp = 0; temp < NeuronNumHidden3; temp++)
	{
		PD_ErrorToNetHidden3[temp] = 0;
	}

	for(m = 0; m < NeuronNumHidden3; m++)
	{
		for(n = 0; n < NeuronNumOutput; n++)
		{
			//NetOutput[n]---->SigmoidHidden3[n]
			PD_NetOutputToSigmoidHidden3[n * NeuronNumHidden3 + m] = WeightHidden3ToOutput[n * NeuronNumHidden3 + m];

			//SigmoidHidden3[m]---->NetHidden3[m]
			PD_SigmoidHidden3ToNetHidden3[m] = SigmoidHidden3[m] * (1 - SigmoidHidden3[m]);

			//Error[m]---->NetHidden3[m]
			PD_ErrorToNetHidden3[m] += Delta_Output[n] * PD_NetOutputToSigmoidHidden3[n * NeuronNumHidden3 + m] * PD_SigmoidHidden3ToNetHidden3[m]; 

			//���������ֵ���������������Ԫֵ��ƫ��
			Delta_Hidden3[m] = PD_ErrorToNetHidden3[m];
		}
	}










	//****************����WeightHidden2ToHidden3****************
	for(n = 0; n < NeuronNumHidden3; n++)
	{
		for(m = 0; m < NeuronNumHidden2; m++)
		{
			//NetHidden3[m]---->WeightHidden2ToHidden3[m]
			PD_NetHidden3ToWeightHidden2ToHidden3[n * NeuronNumHidden2 + m] = SigmoidHidden2[m];
		}
	}		

	for(n = 0; n < NeuronNumHidden3; n++)
	{
		for(m = 0; m < NeuronNumHidden2; m++)
		{
			//��ʽ������ƫ��
			PD_WeightHidden2ToHidden3[n * NeuronNumHidden2 + m] = Delta_Hidden3[n] * PD_NetHidden3ToWeightHidden2ToHidden3[n * NeuronNumHidden2 + m];

			//��Ȩ�ر���0.9
			OldWeightHidden2ToHidden3[n * NeuronNumHidden2 + m] = WeightHidden2ToHidden3[n * NeuronNumHidden2 + m] * OldWeightPercentage; 

			//����WeightHidden2ToHidden3[n]��ֵ
			WeightHidden2ToHidden3[n * NeuronNumHidden2 + m] = WeightHidden2ToHidden3[n * NeuronNumHidden2 + m] - LearningRate * PD_WeightHidden2ToHidden3[n * NeuronNumHidden2 + m];

			//��Ȩ���Ǹ�����0.1
			WeightHidden2ToHidden3[n * NeuronNumHidden2 + m] = WeightHidden2ToHidden3[n * NeuronNumHidden2 + m] * NewWeightPercentage + OldWeightHidden2ToHidden3[n * NeuronNumHidden2 + m]; 
		}
	}	










	//****************����2�����Delta_Hidden2****************
	for (temp = 0; temp < NeuronNumHidden2; temp++)
	{
		PD_ErrorToNetHidden2[temp] = 0;
	}

	for(m = 0; m < NeuronNumHidden2; m++)
	{
		for(n = 0; n < NeuronNumHidden3; n++)
		{
			//NetHidden3[n]---->SigmoidHidden2[n]
			PD_NetHidden3ToSigmoidHidden2[n * NeuronNumHidden2 + m] = WeightHidden2ToHidden3[n * NeuronNumHidden2 + m];

			//SigmoidHidden2[m]---->NetHidden2[m]
			PD_SigmoidHidden2ToNetHidden2[m] = SigmoidHidden2[m] * (1 - SigmoidHidden2[m]);

			//Error[m]---->NetHidden2[m]
			PD_ErrorToNetHidden2[m] += Delta_Hidden3[n] * PD_NetHidden3ToSigmoidHidden2[n * NeuronNumHidden2 + m] * PD_SigmoidHidden2ToNetHidden2[m]; 

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