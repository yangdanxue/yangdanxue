#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define pixels						28		//ͼƬ������28*28
#define NeuronNumHidden				784		//���ز���Ԫ����
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
double WeightInputToHidden[NeuronNumHidden * pixels * pixels] = {0};		
double WeightHiddenToOutput[NeuronNumHidden * NeuronNumOutput] = {0};		

//���㷴�򴫲����Ȩ�ر����ı���
double OldWeightInputToHidden[NeuronNumHidden * pixels * pixels] = {0};		
double OldWeightHiddenToOutput[NeuronNumHidden * NeuronNumOutput] = {0};	

//����ƫ����
double Bias_Input = 0;
double Bias_Hidden = 0;

//������Ԫֵ
double NetHidden[NeuronNumHidden] = {0};	
double NetOutput[NeuronNumOutput] = {0};	

//���㼤���ֵ��Sigmoid������
double SigmoidHidden[NeuronNumHidden] = {0};
double SigmoidOutput[NeuronNumOutput] = {0};

int target[NeuronNumOutput] = {0};				//Ŀ�����ֵ
double ErrorOfOutput[NeuronNumOutput] = {0};	//ÿ���������Ԫ�����ֵ��ʵ�����ֵ��Ŀ��ֵ�Ĳ

//�������ֵ
double PD_ErrorToNetOutput[NeuronNumOutput] = {0};
double Delta_Output[NeuronNumOutput] = {0};
double PD_ErrorToNetHidden[NeuronNumHidden] = {0};
double Delta_Hidden[NeuronNumHidden] = {0};

//������---->������Ȩֵ����
double PD_WeightHiddenToOutput[NeuronNumHidden * NeuronNumOutput] = {0}; //��ƫ��
double PD_ErrorToSigmoidOutput[NeuronNumOutput] = {0};
double PD_SigmoidOutputToNetOutput[NeuronNumOutput] = {0};
double PD_NetOutputToWeightHiddenToOutput[NeuronNumHidden * NeuronNumOutput] = {0};

//�����---->�������Ȩֵ����
double PD_WeightInputToHidden[NeuronNumHidden * pixels * pixels] = {0};
double PD_SigmoidHiddenToNetHidden[NeuronNumHidden] = {0};
double PD_NetHiddenToWeightInputToHidden[NeuronNumHidden * pixels * pixels] = {0};
double PD_NetOutputToSigmoidHidden[NeuronNumHidden * NeuronNumOutput] = {0};

double LearningRate = 0.019; //ѧϰ����

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
	int iNum = 0; //�����-���ز�����Ԫ����

	FILE *fpReadItoH = fopen("d:\\WeightItoHData201810161953.wet","rb");
	FILE *fpReadHtoO = fopen("d:\\WeightHtoOData201810161953.wet","rb");
	if(fpReadItoH == NULL)
	{
		printf("WeightItoHData201810161953.wet�ļ������ڣ�\n");
		return;
	}
	if(fpReadHtoO == NULL)
	{
		printf("WeightHtoOData201810161953.wet�ļ������ڣ�\n");
		return;
	}

	//�����Ƕ����ݣ������������ݴ浽����WeightInputToHidden[NeuronNumHidden]��
	iNum = fread(WeightInputToHidden, sizeof(double), NeuronNumHidden * pixels * pixels, fpReadItoH);
	if(iNum != NeuronNumHidden * pixels * pixels)
	{
		printf("�����ݴ浽����WeightInputToHidden[NeuronNumHidden * pixels * pixels]���󣡣���\n");
	}
	printf("�������-���ز���Ȩ�����ݳɹ�\n");

	//�����Ƕ����ݣ������������ݴ浽����WeightHiddenToOutput[NeuronNumHidden * 10]��
	iNum = fread(WeightHiddenToOutput, sizeof(double), NeuronNumHidden * NeuronNumOutput, fpReadHtoO);
	if(iNum != NeuronNumHidden * NeuronNumOutput)
	{
		printf("�����ݴ浽����WeightHiddenToOutput[NeuronNumHidden * NeuronNumOutput]���󣡣���\n");
	}
	printf("�����ز�-�������Ȩ�����ݳɹ�\n");


	fclose(fpReadItoH);
	fclose(fpReadHtoO);

	return;
}


//д�ļ�����������ǰ���õ�Ȩ��
void WriteWeightData()
{
	int iNum = 0;
	FILE *fpWriteInputToHidden = fopen("d:\\WeightItoHData201810161953.wet","wb+");
	FILE *fpWriteHiddenToOutput = fopen("d:\\WeightHtoOData201810161953.wet","wb+");
	if(fpWriteInputToHidden == NULL)
	{
		printf("����WeightItoHData201810161953.wet�ļ�ʧ�ܣ�\n");
		return 0;
	}
	if(fpWriteHiddenToOutput == NULL)
	{
		printf("����WeightHtoOData201810161953.wet�ļ�ʧ�ܣ�\n");
		return 0;
	}

	//�������-���ز���Ȩ��д�뵽WeightItoHData.wet�ļ���
	iNum = fwrite(WeightInputToHidden, sizeof(double), NeuronNumHidden * pixels * pixels, fpWriteInputToHidden);
	if (iNum != NeuronNumHidden * pixels * pixels)
	{
		printf("дWeightItoHData201810161953.wet�ļ�ʧ�ܣ�");
	}
	printf("���������-���ز���Ȩ�������Ѿ�����\n");


	//�����ز�-�������Ȩ��д�뵽WeightHtoOData.wet�ļ���
	iNum = fwrite(WeightHiddenToOutput, sizeof(double), NeuronNumHidden * NeuronNumOutput, fpWriteHiddenToOutput);
	if (iNum != NeuronNumHidden * NeuronNumOutput)
	{		
		printf("дWeightHtoOData201810161953.wet�ļ�ʧ�ܣ�");
	}
	printf("�������ز�-�������Ȩ�������Ѿ�����\n");

	fclose(fpWriteInputToHidden);
	fclose(fpWriteHiddenToOutput);
}


//�����ʼ����ֵ(91.4967����Ȩ�أ�ȡ0.5)
void RandomInitializationWeight()
{
	int m, n = 0;

	for(m = 0; m < NeuronNumHidden * pixels * pixels; m++)
	{
		//WeightInputToHidden[m] = 0; //�������-���ز㡿֮������2����Ԫ���Ȩ��W
		WeightInputToHidden[m] = (rand()/(double)(RAND_MAX))/2000; //�������-����㡿֮������2����Ԫ���Ȩ��W
	}

	for(n = 0; n < NeuronNumHidden * NeuronNumOutput; n++)
	{
		//WeightHiddenToOutput[n] = 0; //�����ز�-����㡿֮������2����Ԫ���Ȩ��W
		WeightHiddenToOutput[n] = (rand()/(double)(RAND_MAX))/400; //�������-����㡿֮������2����Ԫ���Ȩ��W
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


	////////////////�������ز���Ԫ��ֵ////////////////
	for (m = 0; m < NeuronNumHidden; m++)
	{
		NetHidden[m] = 0;
	}

	for (m = 0; m < NeuronNumHidden; m++)
	{
		for(j = 0; j < pixels; j++)
		{
			for (i = 0; i < pixels; i++)
			{
				NetHidden[m] += iPicture[j][i] * WeightInputToHidden[m * pixels * pixels + (j * pixels + i)];
			}
		}
	}

	//for (m = 0; m < NeuronNumHidden; m++)
	//{
	//	NetHidden[m] = NetHidden[m] / 32;
	//}


	//for (m = 0; m < NeuronNumHidden; m++)
	//{
	//	NetHidden[m] = NetHidden[m] + Bias_Input * 1;
	//}


	////////////////�������ز�sigmoid����ֵ)////////////////
	for(m = 0; m < NeuronNumHidden; m++)
	{
		SigmoidHidden[m] = 1 / (1 + exp( - NetHidden[m]));
	}


	////////////////�����������Ԫ��ֵ////////////////
	for (n = 0; n < NeuronNumOutput; n++)
	{
		NetOutput[n] = 0;
	}

	for(n = 0; n < NeuronNumOutput; n++) //�������Ԫ����Ϊ10
	{
		for(m = 0; m < NeuronNumHidden; m++) //���ز���Ԫ����ΪNeuronNumHidden
		{
			NetOutput[n] += SigmoidHidden[m] * WeightHiddenToOutput[n * NeuronNumHidden + m]; //���ز�����������ԪҪһһ����
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


	//*****************���򴫲�����2.������---->������Ȩֵ���£���ʽ����*****************

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










	//NetOutput[m]---->WeightHiddenToOutput[m]
	for(n = 0; n < NeuronNumOutput; n++)
	{
		for(m = 0; m < NeuronNumHidden; m++)
		{
			PD_NetOutputToWeightHiddenToOutput[n * NeuronNumHidden + m] = SigmoidHidden[m]; //[m]��Ϊ[n * NeuronNumHidden + m]
		}
	}		

	for(n = 0; n < NeuronNumOutput; n++)
	{
		for(m = 0; m < NeuronNumHidden; m++)
		{
			//��ʽ������ƫ��
			PD_WeightHiddenToOutput[n * NeuronNumHidden + m] = Delta_Output[n] * PD_NetOutputToWeightHiddenToOutput[n * NeuronNumHidden + m];

			//��Ȩ�ر���0.9
			OldWeightHiddenToOutput[n * NeuronNumHidden + m] = WeightHiddenToOutput[n * NeuronNumHidden + m] * OldWeightPercentage; 

			//����WeightHiddenToOutput[n]��ֵ
			WeightHiddenToOutput[n * NeuronNumHidden + m] = WeightHiddenToOutput[n * NeuronNumHidden + m] - LearningRate * PD_WeightHiddenToOutput[n * NeuronNumHidden + m];

			//��Ȩ���Ǹ�����0.1
			WeightHiddenToOutput[n * NeuronNumHidden + m] = WeightHiddenToOutput[n * NeuronNumHidden + m] * NewWeightPercentage + OldWeightHiddenToOutput[n * NeuronNumHidden + m]; 
		}
	}	










	//****************���ز����Delta_Hidden****************
	for (temp = 0; temp < NeuronNumHidden; temp++)
	{
		PD_ErrorToNetHidden[temp] = 0;
	}

	for(m = 0; m < NeuronNumHidden; m++)
	{
		for(n = 0; n < NeuronNumOutput; n++)
		{
			//NetOutput[n]---->SigmoidHidden[n]
			PD_NetOutputToSigmoidHidden[n * NeuronNumHidden + m] = WeightHiddenToOutput[n * NeuronNumHidden + m];

			//SigmoidHidden[m]---->NetHidden[m]
			PD_SigmoidHiddenToNetHidden[m] = SigmoidHidden[m] * (1 - SigmoidHidden[m]);

			//Error[m]---->NetHidden[m]
			PD_ErrorToNetHidden[m] += Delta_Output[n] * PD_NetOutputToSigmoidHidden[n * NeuronNumHidden + m] * PD_SigmoidHiddenToNetHidden[m]; 

			//���������ֵ���������������Ԫֵ��ƫ��
			Delta_Hidden[m] = PD_ErrorToNetHidden[m];
		}
	}










	//*****************���򴫲�����3.�����---->�������Ȩֵ����*****************

	//NetHidden[n]---->WeightInputToHidden[n]
	for (m = 0; m < NeuronNumHidden; m++)
	{
		for(j = 0; j < pixels; j++)
		{
			for (i = 0; i < pixels; i++)
			{
				PD_NetHiddenToWeightInputToHidden[m * pixels * pixels + (j * pixels + i)] = iPicture[j][i];
			}
		}
	}


	for (m = 0; m < NeuronNumHidden; m++)
	{
		for(j = 0; j < pixels; j++)
		{
			for (i = 0; i < pixels; i++)
			{
				PD_WeightInputToHidden[m * pixels * pixels + (j * pixels + i)] = Delta_Hidden[m] * PD_NetHiddenToWeightInputToHidden[m * pixels * pixels + (j * pixels + i)];

				//��Ȩ�ر���0.9
				OldWeightInputToHidden[m * pixels * pixels + (j * pixels + i)] = WeightInputToHidden[m * pixels * pixels + (j * pixels + i)] * OldWeightPercentage;

				////����WeightInputToHidden[m]��ֵ
				WeightInputToHidden[m * pixels * pixels + (j * pixels + i)] = 
					WeightInputToHidden[m * pixels * pixels + (j * pixels + i)] - LearningRate * PD_WeightInputToHidden[m * pixels * pixels + (j * pixels + i)]; 

				//��Ȩ���Ǹ�����0.1
				WeightInputToHidden[m * pixels * pixels + (j * pixels + i)] = 
					WeightInputToHidden[m * pixels * pixels + (j * pixels + i)] * NewWeightPercentage + OldWeightInputToHidden[m * pixels * pixels + (j * pixels + i)];
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