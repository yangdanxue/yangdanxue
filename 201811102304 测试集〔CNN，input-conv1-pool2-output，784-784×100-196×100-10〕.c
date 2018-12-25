#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


#define pixels						28		//ͼƬ������28*28
#define Padding_pixels				32		//����ͼƬ������32*32
#define ConvolutionKernel			5		//����ˣ���С��5*5
#define NeuronNumConvolution1       28		//���1����Ԫ����
#define NeuronNumSubsampling2       14		//�ػ�2����Ԫ����
#define Filter						2		//�ػ����������С
#define NeuronNumOutput				10   	//�������Ԫ����

#define NumConvolutionKernel		100		//���������

#define OldWeightPercentage			0.9   	//���򴫲�����Ȩ��ʱ��Ȩ��ռ��
#define NewWeightPercentage			0.1   	//���򴫲�����Ȩ��ʱ��Ȩ��ռ��

#define TrainTimes					1	    //ѵ������
#define TestNumber					10000	//�ܲ���ͼƬ������
#define Memory						1       //��ס�ػ�����ÿ��ֵ������һ������еľ�������


int ReadPicData(unsigned char* data, int iNum); //��ͼƬ�����ļ�

//д�ļ��������浱ǰ����Ȩ��
void WriteWeightInputToConvolution1Data();
void WriteWeightSubsampling2ToOutputData();

//���ļ�������ȡ�ѱ���ĸ���Ȩ��
void ReadWeightInputToConvolution1Data();
void ReadWeightSubsampling2ToOutputData();

//��ʼ������Ȩ��
void InitializationWeightInputToConvolution1();
void InitializationWeightSubsampling2ToOutput();

int CalculateNetResult();		//��������������
float TestNet();				//��������
void TrainNet();				//ѡ����Ի�ѵ��

void CalculateNeuronValue();	//���������Ԫ��ֵ
void BackPropagation();			//���򴫲�������Ȩֵ
void ClearTarget();				//����Target[]
void MaxPool();					//���ػ�

unsigned char iPicture[pixels][pixels] = {0};							//�����MNIST���ݿ�ͼƬ����
unsigned char Padding_iPicture[Padding_pixels][Padding_pixels] = {0};	//����5*5�Ĺ��������ڵ����MNIST���ݿ�ͼƬ����iPicture[y][x]��Χ�������Ϊ2��0ʱ���Ϳ��Ա�֤���ͼ�������ͼ��һ����
unsigned char Label;													//�����MNIST���ݿ��ǩ
unsigned char* p = &Label;

//�������ˣ�Ȩ�أ�
double WeightInputToConvolution1[ConvolutionKernel * ConvolutionKernel * NumConvolutionKernel] = {0};
double WeightRot180InputToConvolution1[ConvolutionKernel * ConvolutionKernel * NumConvolutionKernel] = {0};
double WeightSubsampling2ToOutput[NeuronNumSubsampling2 * NeuronNumSubsampling2 * NumConvolutionKernel * NeuronNumOutput] = {0};

//���㷴�򴫲����Ȩ�ر����ı���
double OldWeightInputToConvolution1[ConvolutionKernel * ConvolutionKernel * NumConvolutionKernel] = {0};
double OldWeightSubsampling2ToOutput[NeuronNumSubsampling2 * NeuronNumSubsampling2 * NumConvolutionKernel * NeuronNumOutput] = {0};

//������Ԫֵ
double NetConvolution1[NeuronNumConvolution1 * NeuronNumConvolution1 * NumConvolutionKernel] = {0};	
double NetSubsampling2[NeuronNumSubsampling2 * NeuronNumSubsampling2 * NumConvolutionKernel] = {0}; 
double NetOutput[NeuronNumOutput] = {0};

//���㼤���ֵ��Sigmoid������
double SigmoidConvolution1[NeuronNumConvolution1 * NeuronNumConvolution1 * NumConvolutionKernel] = {0};	
double SigmoidSubsampling2[NeuronNumSubsampling2 * NeuronNumSubsampling2 * NumConvolutionKernel] = {0};	
double SigmoidOutput[NeuronNumOutput] = {0};

//Ŀ�����ֵ
int target[NeuronNumOutput] = {0};

//�������ֵ
double Delta_Output[NeuronNumOutput] = {0};
double Delta_Subsampling2[NeuronNumSubsampling2 * NeuronNumSubsampling2 * NumConvolutionKernel] = {0};
double Delta_Convolution1[NeuronNumConvolution1 * NeuronNumConvolution1 * NumConvolutionKernel] = {0};

double PD_ErrorToNetOutput[NeuronNumOutput] = {0};
double PD_ErrorToNetSubsampling2[NeuronNumSubsampling2 * NeuronNumSubsampling2 * NumConvolutionKernel] = {0};
double PD_ErrorToNetConvolution1[NeuronNumConvolution1 * NeuronNumConvolution1 * NumConvolutionKernel] = {0};

//�����---->�ػ�2���Ȩֵ����
double PD_ErrorToSigmoidOutput[NeuronNumOutput] = {0};
double PD_WeightSubsampling2ToOutput[NeuronNumSubsampling2 * NeuronNumSubsampling2 * NumConvolutionKernel * NeuronNumOutput] = {0};
double PD_SigmoidOutputToNetOutput[NeuronNumOutput] = {0};
double PD_NetOutputToWeightSubsampling2ToOutput[NeuronNumOutput * NumConvolutionKernel * NeuronNumSubsampling2 * NeuronNumSubsampling2] = {0};

//�ػ�2��---->���1���Ȩֵ����
double PD_NetOutputToSigmoidSubsampling2[NeuronNumOutput * NumConvolutionKernel * NeuronNumSubsampling2 * NeuronNumSubsampling2] = {0};
double PD_SigmoidSubsampling2ToNetSubsampling2[NeuronNumSubsampling2 * NeuronNumSubsampling2 * NumConvolutionKernel] = {0};

double upsample_Delta_Subsampling2[NeuronNumConvolution1 * NeuronNumConvolution1 * NumConvolutionKernel] = {0};

double PD_SigmoidConvolution1ToNetConvolution1[NeuronNumConvolution1 * NeuronNumConvolution1 * NumConvolutionKernel] = {0};

//���1��---->������Ȩֵ����
double PD_WeightInputToConvolution1[ConvolutionKernel * ConvolutionKernel * NumConvolutionKernel] = {0};


//�趨���ػ�ֵ������ṹ������
struct MAXPool 
{
	double Value;
	int NumK;
	int x;
	int y;
	int i;
	int j;
};
struct MAXPool max[NeuronNumSubsampling2 * NeuronNumSubsampling2 * NumConvolutionKernel] = {0};


float LearningRate = 0.005;	//ѧϰ����

int Correct = 0;			//ʶ����ȷ��


void main()
{
	float CorrectRate;
	int MaxCorrect = 0;
	int i = 0;

	ReadWeightInputToConvolution1Data();
	ReadWeightSubsampling2ToOutputData();

	//InitializationWeightInputToConvolution1();
	//InitializationWeightSubsampling2ToOutput();

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
	//		WriteWeightSubsampling2ToOutputData();
	//	}
	//}
}


//���ļ�����ʹ�ñ����[�����-���1��]Ȩ��
void ReadWeightInputToConvolution1Data()
{
	int iNum = 0; //��Ԫ����

	FILE *fpReadItoC1 = fopen("d:\\WeightItoC1Data201811102304.wet","rb");

	if(fpReadItoC1 == NULL)
	{
		printf("WeightItoC1Data201811102304.wet�ļ������ڣ�\n");
		return;
	}

	//�����Ƕ����ݣ������������ݴ浽����WeightInputToConvolution1[NeuronNumConvolution1]��
	iNum = fread(WeightInputToConvolution1, sizeof(double), ConvolutionKernel * ConvolutionKernel * NumConvolutionKernel, fpReadItoC1);
	if(iNum != ConvolutionKernel * ConvolutionKernel * NumConvolutionKernel)
	{
		printf("�����ݴ浽����WeightInputToConvolution1[ConvolutionKernel * ConvolutionKernel * NumConvolutionKernel]���󣡣���\n");
	}
	printf("��[�����-���1��]���Ȩ�����ݳɹ�\n");

	fclose(fpReadItoC1);

	return;
}


//���ļ�����ʹ�ñ����[�ػ�2��-�����]Ȩ��
void ReadWeightSubsampling2ToOutputData()
{
	int iNum = 0; //�����-���ز�����Ԫ����

	FILE *fpReadS2toO = fopen("d:\\WeightS2toOData201811102304.wet","rb");

	if(fpReadS2toO == NULL)
	{
		printf("WeightS2toOData201811102304.wet�ļ������ڣ�\n");
		return;
	}

	//�����Ƕ����ݣ������������ݴ浽����WeightSubsampling2ToOutput[NeuronNumSubsampling2 * NeuronNumOutput]��
	iNum = fread(WeightSubsampling2ToOutput, sizeof(double), NeuronNumSubsampling2 * NeuronNumSubsampling2 * NumConvolutionKernel * NeuronNumOutput, fpReadS2toO);
	if(iNum != NeuronNumSubsampling2 * NeuronNumSubsampling2 * NumConvolutionKernel * NeuronNumOutput)
	{
		printf("�����ݴ浽����WeightSubsampling2ToOutput[NeuronNumSubsampling2 * NeuronNumSubsampling2 * NumConvolutionKernel * NeuronNumOutput]���󣡣���\n");
	}
	printf("��[�ػ�2��-�����]���Ȩ�����ݳɹ�\n");

	fclose(fpReadS2toO);

	return;
}			


//д�ļ�����������ǰ���õ�[�����-���1��]Ȩ��
void WriteWeightInputToConvolution1Data()
{
	int iNum = 0;
	FILE *fpWriteInputToConvolution1 = fopen("d:\\WeightItoC1Data201811102304.wet","wb+");

	if(fpWriteInputToConvolution1 == NULL)
	{
		printf("����WeightItoC1Data201811102304.wet�ļ�ʧ�ܣ�\n");
		return;
	}

	//�������-���1����Ȩ��д�뵽WeightItoC1Data201811102304.wet�ļ���
	iNum = fwrite(WeightInputToConvolution1, sizeof(double), ConvolutionKernel * ConvolutionKernel * NumConvolutionKernel, fpWriteInputToConvolution1);
	if (iNum != ConvolutionKernel * ConvolutionKernel * NumConvolutionKernel)
	{
		printf("дWeightItoC1Data201811102304.wet�ļ�ʧ�ܣ�");
	}
	printf("���������-���1����Ȩ�������Ѿ�����\n");

	fclose(fpWriteInputToConvolution1);
}


//д�ļ�����������ǰ���õ�[�ػ�2��-�����]Ȩ��
void WriteWeightSubsampling2ToOutputData()
{
	int iNum = 0;
	FILE *fpWriteSubsampling2ToOutput = fopen("d:\\WeightS2toOData201811102304.wet","wb+");

	if(fpWriteSubsampling2ToOutput == NULL)
	{
		printf("����WeightS2toOData201811102304.wet�ļ�ʧ�ܣ�\n");
		return;
	}

	//���ػ�2��-�������Ȩ��д�뵽WeightS2toOData201811102304.wet�ļ���
	iNum = fwrite(WeightSubsampling2ToOutput, sizeof(double), NeuronNumSubsampling2 * NeuronNumSubsampling2 * NumConvolutionKernel * NeuronNumOutput, fpWriteSubsampling2ToOutput);
	if (iNum != NeuronNumSubsampling2 * NeuronNumSubsampling2 * NumConvolutionKernel * NeuronNumOutput)
	{		
		printf("дWeightS2toOData201811102304.wet�ļ�ʧ�ܣ�");
	}
	printf("���гػ�2��-�������Ȩ�������Ѿ�����\n");

	fclose(fpWriteSubsampling2ToOutput);
}			


//�����ʼ��[�����-���1��]Ȩ��
void InitializationWeightInputToConvolution1()
{
	int m = 0;
	int n = 0;

	for(m = 0; m < ConvolutionKernel * ConvolutionKernel * NumConvolutionKernel; m++)
	{
		//WeightInputToConvolution1[m] = 0.5/2000; //�������-���1�㡿֮������2����Ԫ���Ȩ��W
		WeightInputToConvolution1[m] = (rand()/(double)(RAND_MAX))/1000; //�������-���1�㡿֮������2����Ԫ���Ȩ��W
		//WeightInputToConvolution1[m] = 0; //�������-���1�㡿֮������2����Ԫ���Ȩ��W
		//WeightInputToConvolution1[m] = -0.008001877380; //89.9467%��Ȩ�ص���λ��
		//WeightInputToConvolution1[m] = 0.078278135; //89.9467%��Ȩ�ص�ƽ����
	}
}


//�����ʼ��[�ػ�2��-�����]Ȩ��
void InitializationWeightSubsampling2ToOutput()
{
	int m = 0;

	for(m = 0; m < NeuronNumSubsampling2 * NeuronNumSubsampling2 * NumConvolutionKernel * NeuronNumOutput; m++)
	{
		//WeightSubsampling2ToOutput[m] = 0; //���ػ�2��-����㡿֮������2����Ԫ���Ȩ��W
		WeightSubsampling2ToOutput[m] = (rand()/(double)(RAND_MAX))/20000; //���ػ�2��-����㡿֮������2����Ԫ���Ȩ��W
		//WeightSubsampling2ToOutput[m] = -0.065319700309; ///89.9467%��Ȩ�ص���λ��
		//WeightSubsampling2ToOutput[m] = -0.060853877; ///89.9467%��Ȩ�ص�ƽ����
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
	int n = 0;
	int temp = 0;
	int NumK = 0;


	//*********************************************����ܹ�������� ����> ���1�� ����> �ػ�2�� ����> �����*********************************************//

	////////////////������1����Ԫ��ֵ////////////////
	for(NumK = 0; NumK < NumConvolutionKernel; NumK++)
	{
		for(y = 0; y < NeuronNumConvolution1; y++)
		{
			for (x = 0; x < NeuronNumConvolution1; x++)
			{
				NetConvolution1[NumK * NeuronNumConvolution1 * NeuronNumConvolution1 + (y * NeuronNumConvolution1 + x)] = 0;
			}
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


	for(NumK = 0; NumK < NumConvolutionKernel; NumK++)
	{
		for(y = 0; y < NeuronNumConvolution1; y++)
		{
			for (x = 0; x < NeuronNumConvolution1; x++)
			{
				for(j = 0; j < ConvolutionKernel; j++)
				{
					for (i = 0; i < ConvolutionKernel; i++)
					{
						NetConvolution1[NumK * NeuronNumConvolution1 * NeuronNumConvolution1 + (y * NeuronNumConvolution1 + x)] += 
							Padding_iPicture[y + j][x + i] * WeightInputToConvolution1[NumK * ConvolutionKernel * ConvolutionKernel + (j * ConvolutionKernel + i)];
					}
				}
			}
		}
	}


	////////////////������1��ļ����ֵ////////////////
	for(NumK = 0; NumK < NumConvolutionKernel; NumK++)
	{
		for(y = 0; y < NeuronNumConvolution1; y++)
		{
			for (x = 0; x < NeuronNumConvolution1; x++)
			{
				SigmoidConvolution1[NumK * NeuronNumConvolution1 * NeuronNumConvolution1 + (y * NeuronNumConvolution1 + x)] = 
					1 / (1 + exp( - NetConvolution1[NumK * NeuronNumConvolution1 * NeuronNumConvolution1 + (y * NeuronNumConvolution1 + x)])); 
			}
		}
	}


	////////////////����ػ�2����Ԫ��ֵ////////////////
	for (temp = 0; temp < NeuronNumSubsampling2 * NeuronNumSubsampling2 * NumConvolutionKernel; temp++)
	{
		NetSubsampling2[temp] = 0;
	}

	for(NumK = 0; NumK < NumConvolutionKernel; NumK++)
	{
		for(y = 0; y < NeuronNumSubsampling2; y++)
		{
			for (x = 0; x < NeuronNumSubsampling2; x++)
			{
				max[NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x)].Value = 0;
				max[NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x)].NumK = 0;
				max[NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x)].x = 0;
				max[NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x)].y = 0;
				max[NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x)].i = 0;
				max[NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x)].j = 0;

				for(j = 0; j < Filter; j++)
				{
					for (i = 0; i < Filter; i++)
					{
						//���ÿ2*2�������е����ֵ����ɳػ���
						if (SigmoidConvolution1[NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + ((y * Filter + j) * NeuronNumConvolution1 + (x * Filter + i))] > 
							max[NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x)].Value)
						{
							max[NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x)].Value = 
								SigmoidConvolution1[NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + ((y * Filter + j) * NeuronNumConvolution1 + (x * Filter + i))];
							max[NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x)].NumK = NumK;
							max[NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x)].x = x;
							max[NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x)].y = y;
							max[NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x)].i = i;
							max[NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x)].j = j;
						}
					}
				}
				NetSubsampling2[NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x)] = 
					SigmoidConvolution1[(max[NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x)].NumK) * NeuronNumSubsampling2 * NeuronNumSubsampling2 + 
					(
					(max[NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x)].y * Filter + 
					max[NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x)].j) * NeuronNumConvolution1 + 
					(max[NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x)].x * Filter + 
					max[NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x)].i)
					)
					]; 
			}
		}
	}


	////////////////����ػ�2��ļ����////////////////
	for(NumK = 0; NumK < NumConvolutionKernel; NumK++)
	{
		for(y = 0; y < NeuronNumSubsampling2; y++)
		{
			for (x = 0; x < NeuronNumSubsampling2; x++)
			{
				SigmoidSubsampling2[NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x)] = 
					NetSubsampling2[NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x)];
			}
		}
	}


	////////////////�����������Ԫ��ֵ////////////////
	for (n = 0; n < NeuronNumOutput; n++)
	{
		NetOutput[n] = 0;
	}

	for(n = 0; n < NeuronNumOutput; n++) //�������Ԫ����ΪNeuronNumOutput
	{
		for(NumK = 0; NumK < NumConvolutionKernel; NumK++)
		{
			for(y = 0; y < NeuronNumSubsampling2; y++)
			{
				for (x = 0; x < NeuronNumSubsampling2; x++)
				{
					NetOutput[n] += 
						SigmoidSubsampling2[NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x)] * 
						WeightSubsampling2ToOutput[n * NeuronNumSubsampling2 * NeuronNumSubsampling2 * NumConvolutionKernel + (NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x))];
				}
			}
		}
	}


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
	int x, y = 0;					
	int m = 0;
	int temp = 0;
	int c, d, s, t = 0;
	int NumK = 0;

	ClearTarget();
	target[Label] = 1; //Ŀ�����ֵ


	//**************************��������Delta_Output**************************
	for(m = 0; m < NeuronNumOutput; m++)
	{
		//Error[m]---->SigmoidOutput[m]
		PD_ErrorToSigmoidOutput[m] = - (target[m] - SigmoidOutput[m]) / 5; 

		//SigmoidOutput[m]---->NetOutput[m]
		PD_SigmoidOutputToNetOutput[m] = SigmoidOutput[m] * (1 - SigmoidOutput[m]); 

		//Error[m]---->NetOutput[m]
		PD_ErrorToNetOutput[m] = PD_ErrorToSigmoidOutput[m] * PD_SigmoidOutputToNetOutput[m]; 

		//���������ֵ���������������Ԫֵ��ƫ��
		Delta_Output[m] = PD_ErrorToNetOutput[m];
	}

	//NetOutput[n]---->WeightSubsampling2ToOutput[n]
	for(m = 0; m < NeuronNumOutput; m++)
	{
		for(NumK = 0; NumK < NumConvolutionKernel; NumK++)
		{
			for(y = 0; y < NeuronNumSubsampling2; y++)
			{
				for(x = 0; x < NeuronNumSubsampling2; x++)
				{
					PD_NetOutputToWeightSubsampling2ToOutput[m * NeuronNumSubsampling2 * NeuronNumSubsampling2 * NumConvolutionKernel + (NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x))] = 
						SigmoidSubsampling2[NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x)];
				}
			}
		}
	}



	//**************************�����---->�ػ�2���Ȩֵ���£���ʽ���򣩣�ȫ����**************************
	for(m = 0; m < NeuronNumOutput; m++)
	{
		for(NumK = 0; NumK < NumConvolutionKernel; NumK++)
		{
			for(y = 0; y < NeuronNumSubsampling2; y++)
			{
				for(x = 0; x < NeuronNumSubsampling2; x++)
				{
					////////////��ʽ������ƫ��
					PD_WeightSubsampling2ToOutput[m * NeuronNumSubsampling2 * NeuronNumSubsampling2 * NumConvolutionKernel + (NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x))] = 
						Delta_Output[m] * 
						PD_NetOutputToWeightSubsampling2ToOutput[m * NeuronNumSubsampling2 * NeuronNumSubsampling2 * NumConvolutionKernel + (NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x))];

					//��Ȩ�ر���OldWeightPercentage
					OldWeightSubsampling2ToOutput[m * NeuronNumSubsampling2 * NeuronNumSubsampling2 * NumConvolutionKernel + (NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x))] = 
						WeightSubsampling2ToOutput[m * NeuronNumSubsampling2 * NeuronNumSubsampling2 * NumConvolutionKernel + (NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x))] * OldWeightPercentage; 

					////////////����WeightSubsampling2ToOutput[m]��ֵ
					WeightSubsampling2ToOutput[m * NeuronNumSubsampling2 * NeuronNumSubsampling2 * NumConvolutionKernel + (NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x))] = 
						WeightSubsampling2ToOutput[m * NeuronNumSubsampling2 * NeuronNumSubsampling2 * NumConvolutionKernel + (NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x))] - 
						LearningRate * PD_WeightSubsampling2ToOutput[m * NeuronNumSubsampling2 * NeuronNumSubsampling2 * NumConvolutionKernel + (NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x))];

					//��Ȩ���Ǳ���NewWeightPercentage*��+OldWeightPercentage*��
					WeightSubsampling2ToOutput[m * NeuronNumSubsampling2 * NeuronNumSubsampling2 * NumConvolutionKernel + (NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x))] = 
						WeightSubsampling2ToOutput[m * NeuronNumSubsampling2 * NeuronNumSubsampling2 * NumConvolutionKernel + (NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x))] * NewWeightPercentage + 
						OldWeightSubsampling2ToOutput[m * NeuronNumSubsampling2 * NeuronNumSubsampling2 * NumConvolutionKernel + (NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x))]; 
				}
			}
		}
	}



	//**************************�ػ�2�����Delta_Subsampling2**************************
	for(temp = 0; temp < NeuronNumSubsampling2 * NeuronNumSubsampling2 * NumConvolutionKernel; temp++)
	{
		PD_ErrorToNetSubsampling2[temp] = 0;
	}

	for(NumK = 0; NumK < NumConvolutionKernel; NumK++)
	{
		for(y = 0; y < NeuronNumSubsampling2; y++)
		{
			for(x = 0; x < NeuronNumSubsampling2; x++)
			{
				for(m = 0; m < NeuronNumOutput; m++)
				{
					//NetOutput[n]---->SigmoidSubsampling2[n]
					PD_NetOutputToSigmoidSubsampling2[m * NeuronNumSubsampling2 * NeuronNumSubsampling2 * NumConvolutionKernel + (NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x))] = 
						WeightSubsampling2ToOutput[m * NeuronNumSubsampling2 * NeuronNumSubsampling2 * NumConvolutionKernel + (NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x))];

					//SigmoidSubsampling2[n]---->NetSubsampling2[n]
					PD_SigmoidSubsampling2ToNetSubsampling2[NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x)] = 1;

					//Error[n]---->NetSubsampling2[n]
					PD_ErrorToNetSubsampling2[NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x)] += 
						Delta_Output[m] * 
						PD_NetOutputToSigmoidSubsampling2[m * NeuronNumSubsampling2 * NeuronNumSubsampling2 * NumConvolutionKernel + (NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x))] * 
						PD_SigmoidSubsampling2ToNetSubsampling2[NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x)];

					//�ػ�2������ֵ�������Գػ�2����Ԫֵ��ƫ��
					Delta_Subsampling2[NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x)] = 
						PD_ErrorToNetSubsampling2[NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x)];
				}
			}
		}
	}



	//**************************�ѳػ�2������ֵά�Ȼ�ԭ����һ�㣨���1�㣩�����ֵά�ȡ������������ÿ4���е�������ֵ�⣬����λ�ò�0**************************
	for(NumK = 0; NumK < NumConvolutionKernel; NumK++)
	{
		for(y = 0; y < NeuronNumSubsampling2; y++)
		{
			for (x = 0; x < NeuronNumSubsampling2; x++)
			{
				for(j = 0; j < Filter; j++)
				{
					for (i = 0; i < Filter; i++)
					{
						upsample_Delta_Subsampling2[NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + ((y * Filter + j) * NeuronNumConvolution1 + (x * Filter + i))] = 0;

						upsample_Delta_Subsampling2[max[NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x)].NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + 
							((max[NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x)].y * Filter + 
							max[NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x)].j) * NeuronNumConvolution1 + 
							(max[NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x)].x * Filter + 
							max[NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x)].i))] = 
							Delta_Subsampling2[NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + (y * NeuronNumSubsampling2 + x)];
					}
				}
			}
		}
	}



	//**************************���1�����Delta_Convolution1**************************
	for(NumK = 0; NumK < NumConvolutionKernel; NumK++)
	{
		for(y = 0; y < NeuronNumSubsampling2; y++)
		{
			for (x = 0; x < NeuronNumSubsampling2; x++)
			{
				for(j = 0; j < Filter; j++)
				{
					for (i = 0; i < Filter; i++)
					{
						//SigmoidConvolution1---->NetConvolution1
						PD_SigmoidConvolution1ToNetConvolution1[NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + ((y * Filter + j) * NeuronNumConvolution1 + (x * Filter + i))] =
							SigmoidConvolution1[NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + ((y * Filter + j) * NeuronNumConvolution1 + (x * Filter + i))] * 
							(1 - SigmoidConvolution1[NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + ((y * Filter + j) * NeuronNumConvolution1 + (x * Filter + i))]); 

						//���1��(�ػ�2���ǰһ��)�����ֵ�ģ��Գػ�2������ֵ����upsample��ԭ * ���1��ļ���ֵ����Ԫֵ��ƫ��
						PD_ErrorToNetConvolution1[NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + ((y * Filter + j) * NeuronNumConvolution1 + (x * Filter + i))] = 
							//�Գػ�2������ֵ����upsample��ԭ
							upsample_Delta_Subsampling2[NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + ((y * Filter + j) * NeuronNumConvolution1 + (x * Filter + i))] * 
							//���1��ļ���ֵ����Ԫֵ��ƫ��
							PD_SigmoidConvolution1ToNetConvolution1[NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + ((y * Filter + j) * NeuronNumConvolution1 + (x * Filter + i))];

						//���1�����Delta_Convolution1
						Delta_Convolution1[NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + ((y * Filter + j) * NeuronNumConvolution1 + (x * Filter + i))] = 
							PD_ErrorToNetConvolution1[NumK * NeuronNumSubsampling2 * NeuronNumSubsampling2 + ((y * Filter + j) * NeuronNumConvolution1 + (x * Filter + i))];
					}
				}
			}
		}
	}


	//**************************���1��---->����㣨����ˣ���Ȩֵ����**************************
	for (temp = 0; temp < ConvolutionKernel * ConvolutionKernel * NumConvolutionKernel; temp++) 
	{
		PD_WeightInputToConvolution1[temp] = 0;
	}

	for(NumK = 0; NumK < NumConvolutionKernel; NumK++)
	{
		for(t = 0; t < ConvolutionKernel; t++)
		{
			for (s = 0; s < ConvolutionKernel; s++)
			{
				for(d = 0; d < NeuronNumConvolution1; d++)
				{
					for (c = 0; c < NeuronNumConvolution1; c++)
					{
						PD_WeightInputToConvolution1[NumK * ConvolutionKernel * ConvolutionKernel + (t * ConvolutionKernel + s)] += 
							Padding_iPicture[t + d][s + c] * 
							Delta_Convolution1[NumK * NeuronNumConvolution1 * NeuronNumConvolution1 + (d * NeuronNumConvolution1 + c)];
					}
				}
			}
		}
	}

	for(NumK = 0; NumK < NumConvolutionKernel; NumK++)
	{
		for(t = 0; t < ConvolutionKernel; t++)
		{
			for (s = 0; s < ConvolutionKernel; s++)
			{
				//��Ȩ�ر���OldWeightPercentage
				OldWeightInputToConvolution1[NumK * ConvolutionKernel * ConvolutionKernel + (t * ConvolutionKernel + s)] = 
					WeightInputToConvolution1[NumK * ConvolutionKernel * ConvolutionKernel + (t * ConvolutionKernel + s)] * OldWeightPercentage; 

				////////////����WeightInputToConvolution1[m]��ֵ
				WeightInputToConvolution1[NumK * ConvolutionKernel * ConvolutionKernel + (t * ConvolutionKernel + s)] = 
					WeightInputToConvolution1[NumK * ConvolutionKernel * ConvolutionKernel + (t * ConvolutionKernel + s)] - 
					LearningRate * PD_WeightInputToConvolution1[NumK * ConvolutionKernel * ConvolutionKernel + (t * ConvolutionKernel + s)];

				//��Ȩ���Ǳ���NewWeightPercentage*��+OldWeightPercentage*��
				WeightInputToConvolution1[NumK * ConvolutionKernel * ConvolutionKernel + (t * ConvolutionKernel + s)] = 
					WeightInputToConvolution1[NumK * ConvolutionKernel * ConvolutionKernel + (t * ConvolutionKernel + s)] * NewWeightPercentage + 
					OldWeightInputToConvolution1[NumK * ConvolutionKernel * ConvolutionKernel + (t * ConvolutionKernel + s)]; 
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