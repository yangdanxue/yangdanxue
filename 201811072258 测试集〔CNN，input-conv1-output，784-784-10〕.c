#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


#define pixels						28		//MNIST���ݿ�ͼƬ������28*28
#define Padding_pixels				32		//����ͼƬ������32*32
#define ConvolutionKernel			5		//����ˣ���С��5*5
#define NeuronNumConvolution1       28		//���ͼƬ�󣬾��1�����߳�
#define NeuronNumOutput				10   	//�������Ԫ����

#define OldWeightPercentage			0.9   	//���򴫲�����Ȩ��ʱ��Ȩ��ռ��
#define NewWeightPercentage			0.1   	//���򴫲�����Ȩ��ʱ��Ȩ��ռ��

#define TrainTimes					1		//ѵ������
#define TestNumber					10000	//�ܲ���ͼƬ������
#define Memory						1		//��ס�ػ�����ÿ��ֵ������һ������еľ�������


int ReadPicData(unsigned char* data, int iNum);				//��ͼƬ�����ļ�

//д�ļ��������浱ǰ����Ȩ��
void WriteWeightInputToConvolution1Data();			
void WriteWeightConvolution1ToOutputData();		

//���ļ�������ȡ�ѱ���ĸ���Ȩ��
void ReadWeightInputToConvolution1Data();		
void ReadWeightConvolution1ToOutputData();			

//��ʼ������Ȩ��
void InitializationWeightInputToConvolution1();				
void InitializationWeightConvolution1ToOutput();			

int CalculateNetResult();			//��������������
float TestNet();					//��������
void TrainNet();					//ѡ����Ի�ѵ��

void CalculateNeuronValue();		//���������Ԫ��ֵ
void BackPropagation();				//���򴫲�������Ȩֵ
void ClearTarget();					//����Target[]

unsigned char iPicture[pixels][pixels] = {0};								//�����MNIST���ݿ�ͼƬ����
unsigned char Padding_iPicture[Padding_pixels][Padding_pixels] = {0};		//����5*5�Ĺ��������ڵ����MNIST���ݿ�ͼƬ����iPicture[y][x]��Χ�������Ϊ2��0ʱ���Ϳ��Ա�֤���ͼ�������ͼ��һ����
unsigned char Label;														//�����MNIST���ݿ��ǩ
unsigned char* p = &Label;

//�������ˣ�Ȩ�أ�
double WeightInputToConvolution1[(NeuronNumConvolution1 * ConvolutionKernel) * (NeuronNumConvolution1 * ConvolutionKernel)] = {0};									
double WeightConvolution1ToOutput[NeuronNumConvolution1 * NeuronNumConvolution1 * NeuronNumOutput] = {0};		

//���㷴�򴫲����Ȩ�ر����ı���
double OldWeightInputToConvolution1[(NeuronNumConvolution1 * ConvolutionKernel) * (NeuronNumConvolution1 * ConvolutionKernel)] = {0};								
double OldWeightConvolution1ToOutput[NeuronNumConvolution1 * NeuronNumConvolution1 * NeuronNumOutput] = {0};	

//������Ԫֵ
double NetConvolution1[NeuronNumConvolution1 * NeuronNumConvolution1] = {0};									
double NetOutput[NeuronNumOutput] = {0};																		

//���㼤���ֵ��Sigmoid������
double SigmoidConvolution1[NeuronNumConvolution1 * NeuronNumConvolution1] = {0};								
double SigmoidOutput[NeuronNumOutput] = {0};																	

//Ŀ�����ֵ
int target[NeuronNumOutput] = {0};																				

//�������ֵ
double Delta_Output[NeuronNumOutput] = {0};
double Delta_Convolution1[NeuronNumConvolution1 * NeuronNumConvolution1] = {0};

//�����---->���1���Ȩֵ����
double PD_WeightConvolution1ToOutput[NeuronNumConvolution1 * NeuronNumConvolution1 * NeuronNumOutput] = {0};
double PD_ErrorToSigmoidOutput[NeuronNumOutput] = {0};
double PD_SigmoidOutputToNetOutput[NeuronNumOutput] = {0};
double PD_ErrorToNetOutput[NeuronNumOutput] = {0};
double PD_NetOutputToWeightConvolution1ToOutput[NeuronNumOutput * NeuronNumConvolution1 * NeuronNumConvolution1] = {0};

//���1��---->������Ȩֵ����
double PD_NetOutputToSigmoidConvolution1[NeuronNumConvolution1 * NeuronNumConvolution1 * NeuronNumOutput] = {0};
double PD_ErrorToNetConvolution1[NeuronNumConvolution1 * NeuronNumConvolution1] = {0};
double PD_SigmoidConvolution1ToNetConvolution1[NeuronNumConvolution1 * NeuronNumConvolution1] = {0};
double PD_WeightInputToConvolution1[(NeuronNumConvolution1 * ConvolutionKernel) * (NeuronNumConvolution1 * ConvolutionKernel)] = {0};


float LearningRate = 0.03;	//ѧϰ����

int Correct = 0;//ʶ����ȷ��


void main()
{
	float CorrectRate;
	int MaxCorrect = 0;
	int i = 0;

	ReadWeightInputToConvolution1Data();
	ReadWeightConvolution1ToOutputData();

	//InitializationWeightInputToConvolution1();
	//InitializationWeightConvolution1ToOutput();

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
	//		WriteWeightInputToConvolution1Data();
	//		WriteWeightConvolution1ToOutputData();
	//	}
	//}
}


//���ļ�����ʹ�ñ����[�����-���1��]Ȩ��
void ReadWeightInputToConvolution1Data()
{
	int iNum = 0; //��Ԫ����

	FILE *fpReadItoC1 = fopen("d:\\WeightItoC1Data201811072258.wet","rb");

	if(fpReadItoC1 == NULL)
	{
		printf("WeightItoC1Data201811072258.wet�ļ������ڣ�\n");
		return;
	}

	//�����Ƕ����ݣ������������ݴ浽����WeightInputToConvolution1[NeuronNumConvolution1]��
	iNum = fread(WeightInputToConvolution1, sizeof(double), (NeuronNumConvolution1 * ConvolutionKernel) * (NeuronNumConvolution1 * ConvolutionKernel), fpReadItoC1);
	if(iNum != (NeuronNumConvolution1 * ConvolutionKernel) * (NeuronNumConvolution1 * ConvolutionKernel))
	{
		printf("�����ݴ浽����WeightInputToConvolution1[(NeuronNumConvolution1 * ConvolutionKernel) * (NeuronNumConvolution1 * ConvolutionKernel)]���󣡣���\n");
	}
	printf("��[�����-���1��]���Ȩ�����ݳɹ�\n");

	fclose(fpReadItoC1);

	return;
}


//���ļ�����ʹ�ñ����[���1��-�����]Ȩ��
void ReadWeightConvolution1ToOutputData()
{
	int iNum = 0; //�����-���ز�����Ԫ����

	FILE *fpReadC1toO = fopen("d:\\WeightC1toOData201811072258.wet","rb");

	if(fpReadC1toO == NULL)
	{
		printf("WeightC1toOData201811072258.wet�ļ������ڣ�\n");
		return;
	}

	//�����Ƕ����ݣ������������ݴ浽����WeightConvolution1ToOutput[NeuronNumConvolution1 * NeuronNumConvolution1 * NeuronNumOutput]��
	iNum = fread(WeightConvolution1ToOutput, sizeof(double), NeuronNumConvolution1 * NeuronNumConvolution1 * NeuronNumOutput, fpReadC1toO);
	if(iNum != NeuronNumConvolution1 * NeuronNumConvolution1 * NeuronNumOutput)
	{
		printf("�����ݴ浽����WeightConvolution1ToOutput[NeuronNumConvolution1 * NeuronNumConvolution1 * NeuronNumOutput]���󣡣���\n");
	}
	printf("��[���1��-�����]���Ȩ�����ݳɹ�\n");

	fclose(fpReadC1toO);

	return;
}			


//д�ļ�����������ǰ���õ�[�����-���1��]Ȩ��
void WriteWeightInputToConvolution1Data()
{
	int iNum = 0;
	FILE *fpWriteInputToConvolution1 = fopen("d:\\WeightItoC1Data201811072258.wet","wb+");

	if(fpWriteInputToConvolution1 == NULL)
	{
		printf("����WeightItoC1Data201811072258.wet�ļ�ʧ�ܣ�\n");
		return;
	}

	//�������-���1����Ȩ��д�뵽WeightItoC1Data201811072258.wet�ļ���
	iNum = fwrite(WeightInputToConvolution1, sizeof(double), (NeuronNumConvolution1 * ConvolutionKernel) * (NeuronNumConvolution1 * ConvolutionKernel), fpWriteInputToConvolution1);
	if (iNum != (NeuronNumConvolution1 * ConvolutionKernel) * (NeuronNumConvolution1 * ConvolutionKernel))
	{
		printf("дWeightItoC1Data201811072258.wet�ļ�ʧ�ܣ�");
	}
	printf("���������-���1����Ȩ�������Ѿ�����\n");

	fclose(fpWriteInputToConvolution1);
}


//д�ļ�����������ǰ���õ�[���1��-�����]Ȩ��
void WriteWeightConvolution1ToOutputData()
{
	int iNum = 0;
	FILE *fpWriteConvolution1ToOutput = fopen("d:\\WeightC1toOData201811072258.wet","wb+");

	if(fpWriteConvolution1ToOutput == NULL)
	{
		printf("����WeightC1toOData201811072258.wet�ļ�ʧ�ܣ�\n");
		return;
	}

	//�����1��-�������Ȩ��д�뵽WeightC1toOData201811072258.wet�ļ���
	iNum = fwrite(WeightConvolution1ToOutput, sizeof(double), NeuronNumConvolution1 * NeuronNumConvolution1 * NeuronNumOutput, fpWriteConvolution1ToOutput);
	if (iNum != NeuronNumConvolution1 * NeuronNumConvolution1 * NeuronNumOutput)
	{		
		printf("дWeightC1toOData201811072258.wet�ļ�ʧ�ܣ�");
	}
	printf("���о��1��-�������Ȩ�������Ѿ�����\n");

	fclose(fpWriteConvolution1ToOutput);
}			


//�����ʼ��[�����-���1��]Ȩ��
void InitializationWeightInputToConvolution1()
{
	int m = 0;

	for(m = 0; m < (NeuronNumConvolution1 * ConvolutionKernel) * (NeuronNumConvolution1 * ConvolutionKernel); m++) //���1���ÿ����Ԫ�������ɲ�ͬ�ľ���˾���õ��ġ�����784������ˣ�ÿ������5*5��Ԫ�أ�
	{
		WeightInputToConvolution1[m] = (rand()/(double)(RAND_MAX))/1000;		
		//WeightInputToConvolution1[m] = 0;									
		//WeightInputToConvolution1[m] = 1023.9754277741900000;				//78.0700%��Ȩ�ص�ƽ����
		//WeightInputToConvolution1[m] = -0.1964562163147680;				//78.0700%��Ȩ�ص���λ��
	}
}


//�����ʼ��[���1��-�����]Ȩ��
void InitializationWeightConvolution1ToOutput()
{
	int m = 0;

	for(m = 0; m < NeuronNumConvolution1 * NeuronNumConvolution1 * NeuronNumOutput; m++)
	{
		WeightConvolution1ToOutput[m] = (rand()/(double)(RAND_MAX))/200;			
		//WeightConvolution1ToOutput[m] = 0;										
		//WeightConvolution1ToOutput[m] = -0.3302111820947480;						//78.0700%��Ȩ�ص�ƽ����
		//WeightConvolution1ToOutput[m] = -0.3983054846310040;						//78.0700%��Ȩ�ص���λ��
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


//��ȡMINST���ݼ�
int ReadPicData(unsigned char* data, unsigned char* p, int iNum)
{
	int iCheck = 0;

	//FILE *fp_image = fopen("d:\\train-images.idx", "rb");//�����������(b)�ļ�train-images.idx����ֻ��(r)�ķ�ʽ�򿪣�
	//FILE *fp_label = fopen("d:\\train-labels.idx", "rb");//�����
	FILE *fp_image = fopen("d:\\t10k_images.idx", "rb");//�����������(b)�ļ�t10k-images.idx����ֻ��(r)�ķ�ʽ�򿪣�
	FILE *fp_label = fopen("d:\\t10k_labels.idx", "rb");//�����
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
	int x, y = 0;
	int xC1, yC1 = 0;
	int m, n = 0;
	int o = 0;


	//����ܹ�������� ����> ���1�� ����> �����

	////////////////������1����Ԫ��ֵ////////////////
	for(yC1 = 0; yC1 < NeuronNumConvolution1; yC1++)
	{
		for (xC1 = 0; xC1 < NeuronNumConvolution1; xC1++)
		{
			NetConvolution1[yC1 * NeuronNumConvolution1 + xC1] = 0;
		}
	}


	//��iPicture[y][x]��Χ�����2Ȧ0������Ϊ��ͼ���Ե������������в��ý��٣�Ϊ�˲������˺ܶ�ͼ���Ե����Ϣ����ͼ��������֮ǰ������ͼ���Ե��0����ͼ����䡣
	//����5*5�Ĺ������������Ϊ2ʱ���Ϳ��Ա�֤���ͼ�������ͼ��һ����
	for(y = 0; y < Padding_pixels; y++)
	{
		for (x = 0; x < Padding_pixels; x++)
		{
			Padding_iPicture[y][x] = 0; 
		}
	}

	for(y = 2, j = 0; y < pixels + 2, j < pixels; y++, j++)
	{
		for (x = 2, i = 0; x < pixels + 2, i < pixels; x++, i++)
		{
			Padding_iPicture[y][x] = iPicture[j][i]; 
		}
	}


	for(yC1 = 0, n = 0; yC1 < NeuronNumConvolution1, n < NeuronNumConvolution1 * ConvolutionKernel; yC1++, n = n + ConvolutionKernel)
	{
		for (xC1 = 0, m = 0; xC1 < NeuronNumConvolution1, m < NeuronNumConvolution1 * ConvolutionKernel; xC1++, m = m + ConvolutionKernel)
		{
			for(j = 0; j < ConvolutionKernel; j++)
			{
				for (i = 0; i < ConvolutionKernel; i++)
				{
					NetConvolution1[yC1 * NeuronNumConvolution1 + xC1] += Padding_iPicture[yC1 + j][xC1 + i] * WeightInputToConvolution1[(n + j) * NeuronNumConvolution1 * ConvolutionKernel + (m + i)];
				}
			}
		}
	}


	////////////////������1��ļ����ֵ////////////////
	for(yC1 = 0; yC1 < NeuronNumConvolution1; yC1++)
	{
		for (xC1 = 0; xC1 < NeuronNumConvolution1; xC1++)
		{
			SigmoidConvolution1[yC1 * NeuronNumConvolution1 + xC1] = 1 / (1 + exp( - NetConvolution1[yC1 * NeuronNumConvolution1 + xC1])); 
		}
	}





	////////////////�����������Ԫ��ֵ////////////////
	for (o = 0; o < NeuronNumOutput; o++)
	{
		NetOutput[o] = 0;
	}

	for(o = 0; o < NeuronNumOutput; o++) //�������Ԫ����ΪNeuronNumOutput
	{
		for(yC1 = 0; yC1 < NeuronNumConvolution1; yC1++)
		{
			for (xC1 = 0; xC1 < NeuronNumConvolution1; xC1++)
			{
				NetOutput[o] += 
					SigmoidConvolution1[yC1 * NeuronNumConvolution1 + xC1] * 
					WeightConvolution1ToOutput[o * NeuronNumConvolution1 * NeuronNumConvolution1 + (yC1 * NeuronNumConvolution1 + xC1)]; //���1������������ԪҪһһ����ȫ���У�
			}
		}
	}


	////////////////���������sigmoid����ֵ////////////////
	for(o = 0; o < NeuronNumOutput; o++)
	{
		SigmoidOutput[o] = 1 / (1 + exp( - NetOutput[o]));
	}
}


//���򴫲�
void BackPropagation()
{
	int i, j = 0;					
	int x, y = 0;					
	int m, n = 0;
	int temp = 0;
	int c, d, s, t = 0;

	ClearTarget();
	target[Label] = 1; //Ŀ�����ֵ


	//**************************�����---->���1���Ȩֵ���£�ȫ���ӣ�**************************

	//****************��������Delta_Output****************
	for(m = 0; m < NeuronNumOutput; m++)
	{
		////////////Error[m]---->SigmoidOutput[m]
		PD_ErrorToSigmoidOutput[m] = - (target[m] - SigmoidOutput[m]) / 5; 

		////////////SigmoidOutput[m]---->NetOutput[m]
		PD_SigmoidOutputToNetOutput[m] = SigmoidOutput[m] * (1 - SigmoidOutput[m]); 

		////////////Error[m]---->NetOutput[m]
		PD_ErrorToNetOutput[m] = PD_ErrorToSigmoidOutput[m] * PD_SigmoidOutputToNetOutput[m]; 

		//���������ֵ���������������Ԫֵ��ƫ��
		Delta_Output[m] = PD_ErrorToNetOutput[m];
	}

	////////////NetOutput[n]---->WeightConvolution1ToOutput[n]
	for(m = 0; m < NeuronNumOutput; m++)
	{
		for(y = 0; y < NeuronNumConvolution1; y++)
		{
			for(x = 0; x < NeuronNumConvolution1; x++)
			{
				PD_NetOutputToWeightConvolution1ToOutput[m * NeuronNumConvolution1 * NeuronNumConvolution1 + (y * NeuronNumConvolution1 + x)] = SigmoidConvolution1[y * NeuronNumConvolution1 + x];
			}
		}
	}

	for(m = 0; m < NeuronNumOutput; m++)
	{
		for(y = 0; y < NeuronNumConvolution1; y++)
		{
			for(x = 0; x < NeuronNumConvolution1; x++)
			{
				////////////��ʽ������ƫ��
				PD_WeightConvolution1ToOutput[m * NeuronNumConvolution1 * NeuronNumConvolution1 + (y * NeuronNumConvolution1 + x)] = 
					Delta_Output[m] * PD_NetOutputToWeightConvolution1ToOutput[m * NeuronNumConvolution1 * NeuronNumConvolution1 + (y * NeuronNumConvolution1 + x)];

				//��Ȩ�ر���0.9
				OldWeightConvolution1ToOutput[m * NeuronNumConvolution1 * NeuronNumConvolution1 + (y * NeuronNumConvolution1 + x)] = 
					WeightConvolution1ToOutput[m * NeuronNumConvolution1 * NeuronNumConvolution1 + (y * NeuronNumConvolution1 + x)] * OldWeightPercentage; 

				////////////����WeightConvolution1ToOutput[m]��ֵ
				WeightConvolution1ToOutput[m * NeuronNumConvolution1 * NeuronNumConvolution1 + (y * NeuronNumConvolution1 + x)] = 
					WeightConvolution1ToOutput[m * NeuronNumConvolution1 * NeuronNumConvolution1 + (y * NeuronNumConvolution1 + x)] - LearningRate * PD_WeightConvolution1ToOutput[m * NeuronNumConvolution1 * NeuronNumConvolution1 + (y * NeuronNumConvolution1 + x)];

				//��Ȩ���Ǳ���0.1*��+0.9*��
				WeightConvolution1ToOutput[m * NeuronNumConvolution1 * NeuronNumConvolution1 + (y * NeuronNumConvolution1 + x)] = 
					WeightConvolution1ToOutput[m * NeuronNumConvolution1 * NeuronNumConvolution1 + (y * NeuronNumConvolution1 + x)] * NewWeightPercentage + 
					OldWeightConvolution1ToOutput[m * NeuronNumConvolution1 * NeuronNumConvolution1 + (y * NeuronNumConvolution1 + x)]; 
			}
		}
	}










	//**************************���1��---->����㣨δ�漰Ȩֵ��**************************
	for(temp = 0; temp < NeuronNumConvolution1 * NeuronNumConvolution1; temp++)
	{
		PD_ErrorToNetConvolution1[temp] = 0;
	}

	//****************���1�����Delta_Convolution1****************
	for(y = 0; y < NeuronNumConvolution1; y++)
	{
		for(x = 0; x < NeuronNumConvolution1; x++)
		{
			for(m = 0; m < NeuronNumOutput; m++)
			{
				//NetOutput[n]---->SigmoidConvolution1[n]
				PD_NetOutputToSigmoidConvolution1[m * NeuronNumConvolution1 * NeuronNumConvolution1 + (y * NeuronNumConvolution1 + x)] = 
					WeightConvolution1ToOutput[m * NeuronNumConvolution1 * NeuronNumConvolution1 + (y * NeuronNumConvolution1 + x)];

				//SigmoidConvolution1[n]---->NetConvolution1[n]
				PD_SigmoidConvolution1ToNetConvolution1[y * NeuronNumConvolution1 + x] = SigmoidConvolution1[y * NeuronNumConvolution1 + x] * (1 - SigmoidConvolution1[y * NeuronNumConvolution1 + x]);

				////////////Error[n]---->NetConvolution1[n]
				PD_ErrorToNetConvolution1[y * NeuronNumConvolution1 + x] += 
					Delta_Output[m] * 
					PD_NetOutputToSigmoidConvolution1[m * NeuronNumConvolution1 * NeuronNumConvolution1 + (y * NeuronNumConvolution1 + x)] * 
					PD_SigmoidConvolution1ToNetConvolution1[y * NeuronNumConvolution1 + x];

				//���1������ֵ�������Ծ��1����Ԫֵ��ƫ��
				Delta_Convolution1[y * NeuronNumConvolution1 + x] = PD_ErrorToNetConvolution1[y * NeuronNumConvolution1 + x];
			}
		}
	}










	//**************************���1��---->����㣨����ˣ���Ȩֵ����**************************
	for (temp = 0; temp < (NeuronNumConvolution1 * ConvolutionKernel) * (NeuronNumConvolution1 * ConvolutionKernel); temp++) 
	{
		PD_WeightInputToConvolution1[temp] = 0;
	}


	for(t = 0, n = 0; t < NeuronNumConvolution1, n < NeuronNumConvolution1 * ConvolutionKernel; t++, n = n + ConvolutionKernel) 
	{
		for (s = 0, m = 0; s < NeuronNumConvolution1, m < NeuronNumConvolution1 * ConvolutionKernel; s++, m = m + ConvolutionKernel) 
		{
			for(d = 0; d < ConvolutionKernel; d++)
			{
				for (c = 0; c < ConvolutionKernel; c++)
				{
					PD_WeightInputToConvolution1[(n + d) * (NeuronNumConvolution1 * ConvolutionKernel) + (m + c)] = Delta_Convolution1[t * NeuronNumConvolution1 + s] * Padding_iPicture[t + d][s + c]; 
				}
			}
		}
	}



	for(n = 0; n < NeuronNumConvolution1 * ConvolutionKernel; n = n + ConvolutionKernel) 
	{
		for (m = 0; m < NeuronNumConvolution1 * ConvolutionKernel; m = m + ConvolutionKernel) 
		{
			for(d = 0; d < ConvolutionKernel; d++)
			{
				for (c = 0; c < ConvolutionKernel; c++)
				{
					//��Ȩ�ر���0.9
					OldWeightInputToConvolution1[(n + d) * (NeuronNumConvolution1 * ConvolutionKernel) + (m + c)] = 
						WeightInputToConvolution1[(n + d) * (NeuronNumConvolution1 * ConvolutionKernel) + (m + c)] * OldWeightPercentage; 

					////////////����WeightInputToConvolution1[m]��ֵ
					WeightInputToConvolution1[(n + d) * (NeuronNumConvolution1 * ConvolutionKernel) + (m + c)] = 
						WeightInputToConvolution1[(n + d) * (NeuronNumConvolution1 * ConvolutionKernel) + (m + c)] - LearningRate * PD_WeightInputToConvolution1[(n + d) * (NeuronNumConvolution1 * ConvolutionKernel) + (m + c)];

					//��Ȩ���Ǳ���0.1*��+0.9*��
					WeightInputToConvolution1[(n + d) * (NeuronNumConvolution1 * ConvolutionKernel) + (m + c)] = 
						WeightInputToConvolution1[(n + d) * (NeuronNumConvolution1 * ConvolutionKernel) + (m + c)] * NewWeightPercentage + OldWeightInputToConvolution1[(n + d) * (NeuronNumConvolution1 * ConvolutionKernel) + (m + c)]; 
				}
			}
		}
	}
}


//����Target[]
void ClearTarget()
{
	int i = 0;

	for (i = 0; i < NeuronNumOutput; i++)
	{
		target[i] = 0;
	}
}

//��������ʶ����
int CalculateNetResult()
{
	int i = 0, result = 0; 
	CalculateNeuronValue(); //������Ԫ��ֵ	

	for (i = 1; i < NeuronNumOutput; i++)
	{
		if (SigmoidOutput[result] < SigmoidOutput[i])
		{
			result = i;
		}
	}

	return result;//ʶ����
}