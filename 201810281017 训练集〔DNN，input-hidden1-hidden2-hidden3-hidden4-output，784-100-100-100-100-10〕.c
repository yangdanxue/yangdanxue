#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define pixels						28		//ͼƬ������28*28
#define NeuronNumHidden1			100		//����1����Ԫ����
#define NeuronNumHidden2			100		//����2����Ԫ����
#define NeuronNumHidden3			100		//����3����Ԫ����
#define NeuronNumHidden4			100		//����4����Ԫ����
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
double WeightHidden3ToHidden4[NeuronNumHidden3 * NeuronNumHidden4] = {0};
double WeightHidden4ToOutput[NeuronNumHidden4 * NeuronNumOutput] = {0};		

//���㷴�򴫲����Ȩ�ر����ı���
double OldWeightInputToHidden1[pixels * pixels * NeuronNumHidden1] = {0};
double OldWeightHidden1ToHidden2[NeuronNumHidden1 * NeuronNumHidden2] = {0};
double OldWeightHidden2ToHidden3[NeuronNumHidden2 * NeuronNumHidden3] = {0};
double OldWeightHidden3ToHidden4[NeuronNumHidden3 * NeuronNumHidden4] = {0};
double OldWeightHidden4ToOutput[NeuronNumHidden4 * NeuronNumOutput] = {0};	

//����ƫ����
double Bias_Input = 0;
double Bias_Hidden = 0;

//������Ԫֵ
double NetHidden1[NeuronNumHidden1] = {0};	
double NetHidden2[NeuronNumHidden2] = {0};	
double NetHidden3[NeuronNumHidden3] = {0};	
double NetHidden4[NeuronNumHidden4] = {0};	
double NetOutput[NeuronNumOutput] = {0};	

//���㼤���ֵ��Sigmoid������
double SigmoidHidden1[NeuronNumHidden1] = {0};
double SigmoidHidden2[NeuronNumHidden2] = {0};
double SigmoidHidden3[NeuronNumHidden3] = {0};
double SigmoidHidden4[NeuronNumHidden4] = {0};
double SigmoidOutput[NeuronNumOutput] = {0};

int target[NeuronNumOutput] = {0};				//Ŀ�����ֵ
double ErrorOfOutput[NeuronNumOutput] = {0};	//ÿ���������Ԫ�����ֵ��ʵ�����ֵ��Ŀ��ֵ�Ĳ

//�������ֵ
double PD_ErrorToNetOutput[NeuronNumOutput] = {0};
double Delta_Output[NeuronNumOutput] = {0};
double PD_ErrorToNetHidden4[NeuronNumHidden4] = {0};
double Delta_Hidden4[NeuronNumHidden4] = {0};
double PD_ErrorToNetHidden3[NeuronNumHidden3] = {0};
double Delta_Hidden3[NeuronNumHidden3] = {0};
double PD_ErrorToNetHidden2[NeuronNumHidden2] = {0};
double Delta_Hidden2[NeuronNumHidden2] = {0};
double PD_ErrorToNetHidden1[NeuronNumHidden1] = {0};
double Delta_Hidden1[NeuronNumHidden1] = {0};

//����4��---->������Ȩֵ����
double PD_ErrorToSigmoidOutput[NeuronNumOutput] = {0};
double PD_SigmoidOutputToNetOutput[NeuronNumOutput] = {0};
double PD_NetOutputToWeightHidden4ToOutput[NeuronNumHidden4 * NeuronNumOutput] = {0};
double PD_WeightHidden4ToOutput[NeuronNumHidden4 * NeuronNumOutput] = {0};

//����3��---->����4���Ȩֵ����
double PD_NetOutputToSigmoidHidden4[NeuronNumHidden4 * NeuronNumOutput] = {0};
double PD_SigmoidHidden4ToNetHidden4[NeuronNumHidden4 * NeuronNumOutput] = {0};
double PD_NetHidden4ToWeightHidden3ToHidden4[NeuronNumHidden3 * NeuronNumHidden4] = {0};
double PD_WeightHidden3ToHidden4[NeuronNumHidden3 * NeuronNumHidden4] = {0};

//����2��---->����3���Ȩֵ����
double PD_NetHidden3ToWeightHidden2ToHidden3[NeuronNumHidden2 * NeuronNumHidden3] = {0};
double PD_SigmoidHidden3ToNetHidden3[NeuronNumHidden3] = {0};
double PD_NetHidden4ToSigmoidHidden3[NeuronNumHidden3 * NeuronNumHidden4] = {0};
double PD_WeightHidden2ToHidden3[NeuronNumHidden2 * NeuronNumHidden3] = {0};

//����1��---->����2���Ȩֵ����
double PD_NetHidden3ToSigmoidHidden2[NeuronNumHidden2 * NeuronNumHidden3] = {0};
double PD_SigmoidHidden2ToNetHidden2[NeuronNumHidden2] = {0};
double PD_NetHidden2ToWeightHidden1ToHidden2[NeuronNumHidden1 * NeuronNumHidden2] = {0};
double PD_WeightHidden1ToHidden2[NeuronNumHidden1 * NeuronNumHidden2] = {0};

//�����---->����1���Ȩֵ����
double PD_NetHidden2ToSigmoidHidden1[NeuronNumHidden1 * NeuronNumHidden2] = {0};
double PD_SigmoidHidden1ToNetHidden1[NeuronNumHidden1] = {0};
double PD_NetHidden1ToWeightInputToHidden1[pixels * pixels * NeuronNumHidden1] = {0};
double PD_WeightInputToHidden1[pixels * pixels * NeuronNumHidden1] = {0};

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

	FILE *fpReadItoH1 = fopen("d:\\WeightItoH1Data201810281017.wet","rb");
	FILE *fpReadH1toH2 = fopen("d:\\WeightH1toH2Data201810281017.wet","rb");
	FILE *fpReadH2toH3 = fopen("d:\\WeightH2toH3Data201810281017.wet","rb");
	FILE *fpReadH3toH4 = fopen("d:\\WeightH3toH4Data201810281017.wet","rb");
	FILE *fpReadH4toO = fopen("d:\\WeightH4toOData201810281017.wet","rb");
	if(fpReadItoH1 == NULL)
	{
		printf("WeightItoH1Data201810281017.wet�ļ������ڣ�\n");
		return;
	}
	if(fpReadH1toH2 == NULL)
	{
		printf("WeightH1toH2Data201810281017.wet�ļ������ڣ�\n");
		return;
	}
	if(fpReadH2toH3 == NULL)
	{
		printf("WeightH2toH3Data201810281017.wet�ļ������ڣ�\n");
		return;
	}
	if(fpReadH3toH4 == NULL)
	{
		printf("WeightH3toH4Data201810281017.wet�ļ������ڣ�\n");
		return;
	}
	if(fpReadH4toO == NULL)
	{
		printf("WeightH4toOData201810281017.wet�ļ������ڣ�\n");
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

	//�����Ƕ����ݣ������������ݴ浽����WeightHidden3ToHidden4[m]��
	iNum = fread(WeightHidden3ToHidden4, sizeof(double), NeuronNumHidden3 * NeuronNumHidden4, fpReadH3toH4);
	if(iNum != NeuronNumHidden3 * NeuronNumHidden4)
	{
		printf("�����ݴ浽����WeightHidden3ToHidden4[NeuronNumHidden3 * NeuronNumHidden4]���󣡣���\n");
	}
	printf("������3��-����4����Ȩ�����ݳɹ�\n");

	//�����Ƕ����ݣ������������ݴ浽����WeightHidden4ToOutput[m]��
	iNum = fread(WeightHidden4ToOutput, sizeof(double), NeuronNumHidden4 * NeuronNumOutput, fpReadH4toO);
	if(iNum != NeuronNumHidden4 * NeuronNumOutput)
	{
		printf("�����ݴ浽����WeightHidden4ToOutput[NeuronNumHidden4 * NeuronNumOutput]���󣡣���\n");
	}
	printf("������4��-�������Ȩ�����ݳɹ�\n");

	fclose(fpReadItoH1);
	fclose(fpReadH1toH2);
	fclose(fpReadH2toH3);
	fclose(fpReadH3toH4);
	fclose(fpReadH4toO);

	return;
}


//д�ļ�����������ǰ���õ�Ȩ��
void WriteWeightData()
{
	int iNum = 0;
	FILE *fpWriteInputToHidden1 = fopen("d:\\WeightItoH1Data201810281017.wet","wb+");
	FILE *fpWriteHidden1ToHidden2 = fopen("d:\\WeightH1toH2Data201810281017.wet","wb+");
	FILE *fpWriteHidden2ToHidden3 = fopen("d:\\WeightH2toH3Data201810281017.wet","wb+");
	FILE *fpWriteHidden3ToHidden4 = fopen("d:\\WeightH3toH4Data201810281017.wet","wb+");
	FILE *fpWriteHidden4ToOutput = fopen("d:\\WeightH4toOData201810281017.wet","wb+");
	if(fpWriteInputToHidden1 == NULL)
	{
		printf("����WeightItoH1Data201810281017.wet�ļ�ʧ�ܣ�\n");
		return 0;
	}
	if(fpWriteHidden1ToHidden2 == NULL)
	{
		printf("����WeightH1toH2Data201810281017.wet�ļ�ʧ�ܣ�\n");
		return 0;
	}
	if(fpWriteHidden2ToHidden3 == NULL)
	{
		printf("����WeightH2toH3Data201810281017.wet�ļ�ʧ�ܣ�\n");
		return 0;
	}
	if(fpWriteHidden3ToHidden4 == NULL)
	{
		printf("����WeightH3toH4Data201810281017.wet�ļ�ʧ�ܣ�\n");
		return 0;
	}
	if(fpWriteHidden4ToOutput == NULL)
	{
		printf("����WeightH4toOData201810281017.wet�ļ�ʧ�ܣ�\n");
		return 0;
	}

	//�������-����1����Ȩ��д�뵽WeightItoH1Data201810281017.wet�ļ���
	iNum = fwrite(WeightInputToHidden1, sizeof(double), pixels * pixels * NeuronNumHidden1, fpWriteInputToHidden1);
	if (iNum != pixels * pixels * NeuronNumHidden1)
	{
		printf("дWeightItoH1Data201810281017.wet�ļ�ʧ�ܣ�");
	}
	printf("���������-����1����Ȩ�������Ѿ�����\n");

	//������1��-����2����Ȩ��д�뵽WeightH1toH2Data201810281017.wet�ļ���
	iNum = fwrite(WeightHidden1ToHidden2, sizeof(double), NeuronNumHidden1 * NeuronNumHidden2, fpWriteHidden1ToHidden2);
	if (iNum != NeuronNumHidden1 * NeuronNumHidden2)
	{
		printf("дWeightH1toH2Data201810281017.wet�ļ�ʧ�ܣ�");
	}
	printf("��������1��-����2����Ȩ�������Ѿ�����\n");

	//������2��-����3����Ȩ��д�뵽WeightH2toH3Data201810281017.wet�ļ���
	iNum = fwrite(WeightHidden2ToHidden3, sizeof(double), NeuronNumHidden2 * NeuronNumHidden3, fpWriteHidden2ToHidden3);
	if (iNum != NeuronNumHidden2 * NeuronNumHidden3)
	{
		printf("дWeightH2toH3Data201810281017.wet�ļ�ʧ�ܣ�");
	}
	printf("��������2��-����3����Ȩ�������Ѿ�����\n");

	//������3��-����4����Ȩ��д�뵽WeightH3toH4Data201810281017.wet�ļ���
	iNum = fwrite(WeightHidden3ToHidden4, sizeof(double), NeuronNumHidden3 * NeuronNumHidden4, fpWriteHidden3ToHidden4);
	if (iNum != NeuronNumHidden3 * NeuronNumHidden4)
	{
		printf("дWeightH3toH4Data201810281017.wet�ļ�ʧ�ܣ�");
	}
	printf("��������2��-����3����Ȩ�������Ѿ�����\n");

	//������4��-�������Ȩ��д�뵽WeightH4toOData201810281017.wet�ļ���
	iNum = fwrite(WeightHidden4ToOutput, sizeof(double), NeuronNumHidden4 * NeuronNumOutput, fpWriteHidden4ToOutput);
	if (iNum != NeuronNumHidden4 * NeuronNumOutput)
	{		
		printf("дWeightH4toOData201810281017.wet�ļ�ʧ�ܣ�");
	}
	printf("��������4��-�������Ȩ�������Ѿ�����\n");

	fclose(fpWriteInputToHidden1);
	fclose(fpWriteHidden1ToHidden2);
	fclose(fpWriteHidden2ToHidden3);
	fclose(fpWriteHidden3ToHidden4);
	fclose(fpWriteHidden4ToOutput);
}


//�����ʼ����ֵ
void RandomInitializationWeight()
{
	int wi1, w12, w23, w34, w4o = 0;

	for(wi1 = 0; wi1 < pixels * pixels * NeuronNumHidden1; wi1++)
	{
		//WeightInputToHidden1[wi1] = (rand()/(double)(RAND_MAX))/100000;
		//WeightInputToHidden1[wi1] = 0.0006160119842780; //�����189����201810231517����λ��*10
		//WeightInputToHidden1[wi1] = 0.0000616011984278; //�����189����201810231517����λ��
		WeightInputToHidden1[wi1] = 0.0017540410310992; //�����189����201810231517��ƽ����
	}

	for(w12 = 0; w12 < NeuronNumHidden1 * NeuronNumHidden2; w12++)
	{
		//WeightInputToHidden1[m] = (rand()/(double)(RAND_MAX))/500;
		//WeightHidden1ToHidden2[w12] = 0.3941045692040610; //�����189����201810231517����λ��*10
		//WeightHidden1ToHidden2[w12] = 0.0394104569204061; //�����189����201810231517����λ��
		WeightHidden1ToHidden2[w12] = 0.0243395676808447; //�����189����201810231517��ƽ����
	} 


	for(w23 = 0; w23 < NeuronNumHidden2 * NeuronNumHidden3; w23++)
	{
		//WeightInputToHidden1[m] = (rand()/(double)(RAND_MAX))/500;
		//WeightHidden2ToHidden3[w23] = 0.4152185613955350; //�����189����201810231517����λ��*10
		//WeightHidden2ToHidden3[w23] = 0.0415218561395535; //�����189����201810231517����λ��
		WeightHidden2ToHidden3[w23] = 0.0184187868549414; //�����189����201810231517��ƽ����
	}

	for(w34 = 0; w34 < NeuronNumHidden3 * NeuronNumHidden4; w34++)
	{
		//WeightInputToHidden1[m] = (rand()/(double)(RAND_MAX))/500;
		//WeightHidden3ToHidden4[w34] = 0.4363325535870090; //���ݡ����189����201810231517������λ����h1-h2�Ĳ�Ȳh2-h3��*10
		//WeightHidden3ToHidden4[w34] = 0.0436332553587009; //���ݡ����189����201810231517������λ����h1-h2�Ĳ�Ȳh2-h3��
		WeightHidden3ToHidden4[w34] = 0.0184187868549414; //���ݡ����189����201810231517����ƽ������h1-h2�Ĳ�Ȳh2-h3��
	}

	for(w4o = 0; w4o < NeuronNumHidden4 * NeuronNumOutput; w4o++)
	{
		//WeightInputToHidden1[m] = (rand()/(double)(RAND_MAX))/500;
		//WeightHidden4ToOutput[w4o] = -1.4015852321395100; //�����189����201810231517����λ��*10
		//WeightHidden4ToOutput[w4o] = -0.1401585232139510; //�����189����201810231517����λ��
		WeightHidden4ToOutput[w4o] = -0.1264533357735950; //�����189����201810231517��ƽ����
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
	int h1, h2, h3, h4, o = 0;


	////////////////��������1����Ԫ��ֵ////////////////
	for (h1 = 0; h1 < NeuronNumHidden1; h1++)
	{
		NetHidden1[h1] = 0;
	}

	for (h1 = 0; h1 < NeuronNumHidden1; h1++)
	{
		for(j = 0; j < pixels; j++)
		{
			for (i = 0; i < pixels; i++)
			{
				NetHidden1[h1] += iPicture[j][i] * WeightInputToHidden1[h1 * pixels * pixels + (j * pixels + i)];
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
	for(h1 = 0; h1 < NeuronNumHidden1; h1++)
	{
		SigmoidHidden1[h1] = 1 / (1 + exp( - NetHidden1[h1]));
	}










	////////////////��������2����Ԫ��ֵ////////////////
	for (h2 = 0; h2 < NeuronNumHidden2; h2++)
	{
		NetHidden2[h2] = 0;
	}

	for (h2 = 0; h2 < NeuronNumHidden2; h2++)
	{
		for (h1 = 0; h1 < NeuronNumHidden1; h1++)
		{
			NetHidden2[h2] += SigmoidHidden1[h1] * WeightHidden1ToHidden2[h2 * NeuronNumHidden1 + h1];
		}
	}

	////////////////��������2��sigmoid����ֵ)////////////////
	for(h2 = 0; h2 < NeuronNumHidden2; h2++)
	{
		SigmoidHidden2[h2] = 1 / (1 + exp( - NetHidden2[h2]));
	}










	////////////////��������3����Ԫ��ֵ////////////////
	for (h3 = 0; h3 < NeuronNumHidden3; h3++)
	{
		NetHidden3[h3] = 0;
	}

	for (h3 = 0; h3 < NeuronNumHidden3; h3++)
	{
		for (h2 = 0; h2 < NeuronNumHidden2; h2++)
		{
			NetHidden3[h3] += SigmoidHidden2[h2] * WeightHidden2ToHidden3[h3 * NeuronNumHidden2 + h2];
		}
	}

	////////////////��������3��sigmoid����ֵ)////////////////
	for(h3 = 0; h3 < NeuronNumHidden3; h3++)
	{
		SigmoidHidden3[h3] = 1 / (1 + exp( - NetHidden3[h3]));
	}










	////////////////��������4����Ԫ��ֵ////////////////
	for (h4 = 0; h4 < NeuronNumHidden4; h4++)
	{
		NetHidden4[h4] = 0;
	}

	for (h4 = 0; h4 < NeuronNumHidden4; h4++)
	{
		for (h3 = 0; h3 < NeuronNumHidden3; h3++)
		{
			NetHidden4[h4] += SigmoidHidden3[h3] * WeightHidden3ToHidden4[h4 * NeuronNumHidden3 + h3];
		}
	}

	////////////////��������4��sigmoid����ֵ)////////////////
	for(h4 = 0; h4 < NeuronNumHidden4; h4++)
	{
		SigmoidHidden4[h4] = 1 / (1 + exp( - NetHidden4[h4]));
	}










	////////////////�����������Ԫ��ֵ////////////////
	for (o = 0; o < NeuronNumOutput; o++)
	{
		NetOutput[o] = 0;
	}

	for(o = 0; o < NeuronNumOutput; o++) //�������Ԫ����Ϊ10
	{
		for(h4 = 0; h4 < NeuronNumHidden4; h4++) //���ز���Ԫ����ΪNeuronNumHidden3
		{
			NetOutput[o] += SigmoidHidden4[h4] * WeightHidden4ToOutput[o * NeuronNumHidden4 + h4]; //���ز�����������ԪҪһһ����
		}
	}

	//for(n = 0; n < NeuronNumOutput; n++) //�������Ԫ����Ϊ10
	//{
	//	NetOutput[n] = NetOutput[n] + Bias_Hidden * 1;
	//}

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
	int h1, h2, h3, h4, o = 0;

	ClearTarget();
	target[Label] = 1; //Ŀ�����ֵ


	//****************��������Delta_Output****************
	for(o = 0; o < NeuronNumOutput; o++)
	{
		//Error[total]---->SigmoidOutput[o]
		PD_ErrorToSigmoidOutput[o] = - (target[o] - SigmoidOutput[o]); 

		//SigmoidOutput[o]---->NetOutput[o]
		PD_SigmoidOutputToNetOutput[o] = SigmoidOutput[o] * (1 - SigmoidOutput[o]); 

		//Error[o]---->NetOutput[o]
		PD_ErrorToNetOutput[o] = PD_ErrorToSigmoidOutput[o] * PD_SigmoidOutputToNetOutput[o]; 

		//���������ֵ���������������Ԫֵ��ƫ��
		Delta_Output[o] = PD_ErrorToNetOutput[o];
	}		









	//****************����WeightHidden4ToOutput****************
	for(o = 0; o < NeuronNumOutput; o++)
	{
		for(h4 = 0; h4 < NeuronNumHidden4; h4++)
		{
			//NetOutput---->WeightHidden4ToOutput
			PD_NetOutputToWeightHidden4ToOutput[o * NeuronNumHidden4 + h4] = SigmoidHidden4[h4];
		}
	}		

	for(o = 0; o < NeuronNumOutput; o++)
	{
		for(h4 = 0; h4 < NeuronNumHidden4; h4++)
		{
			//��ʽ������ƫ��
			PD_WeightHidden4ToOutput[o * NeuronNumHidden4 + h4] = Delta_Output[o] * PD_NetOutputToWeightHidden4ToOutput[o * NeuronNumHidden4 + h4];

			//��Ȩ�ر���0.9
			OldWeightHidden4ToOutput[o * NeuronNumHidden4 + h4] = WeightHidden4ToOutput[o * NeuronNumHidden4 + h4] * OldWeightPercentage; 

			//����WeightHidden4ToOutput[o]��ֵ
			WeightHidden4ToOutput[o * NeuronNumHidden4 + h4] = WeightHidden4ToOutput[o * NeuronNumHidden4 + h4] - LearningRate * PD_WeightHidden4ToOutput[o * NeuronNumHidden4 + h4];

			//��Ȩ���Ǹ�����0.1
			WeightHidden4ToOutput[o * NeuronNumHidden4 + h4] = WeightHidden4ToOutput[o * NeuronNumHidden4 + h4] * NewWeightPercentage + OldWeightHidden4ToOutput[o * NeuronNumHidden4 + h4]; 
		}
	}	










	//****************����4�����Delta_Hidden4****************
	for (h4 = 0; h4 < NeuronNumHidden4; h4++)
	{
		PD_ErrorToNetHidden4[h4] = 0;
	}

	for(h4 = 0; h4 < NeuronNumHidden4; h4++)
	{
		for(o = 0; o < NeuronNumOutput; o++)
		{
			//NetOutput---->SigmoidHidden4
			PD_NetOutputToSigmoidHidden4[o * NeuronNumHidden4 + h4] = WeightHidden4ToOutput[o * NeuronNumHidden4 + h4];

			//SigmoidHidden4---->NetHidden4
			PD_SigmoidHidden4ToNetHidden4[h4] = SigmoidHidden4[h4] * (1 - SigmoidHidden4[h4]);

			//Error---->NetHidden4
			PD_ErrorToNetHidden4[h4] += Delta_Output[o] * PD_NetOutputToSigmoidHidden4[o * NeuronNumHidden4 + h4] * PD_SigmoidHidden4ToNetHidden4[h4]; 

			//���������ֵ���������������Ԫֵ��ƫ��
			Delta_Hidden4[h4] = PD_ErrorToNetHidden4[h4];
		}
	}










	//****************����WeightHidden3ToHidden4****************
	for(h4 = 0; h4 < NeuronNumHidden4; h4++)
	{
		for(h3 = 0; h3 < NeuronNumHidden3; h3++)
		{
			//NetHidden4---->WeightHidden3ToHidden4
			PD_NetHidden4ToWeightHidden3ToHidden4[h4 * NeuronNumHidden3 + h3] = SigmoidHidden3[h3];
		}
	}		

	for(h4 = 0; h4 < NeuronNumHidden4; h4++)
	{
		for(h3 = 0; h3 < NeuronNumHidden3; h3++)
		{
			//��ʽ������ƫ��
			PD_WeightHidden3ToHidden4[h4 * NeuronNumHidden3 + h3] = Delta_Hidden4[h4] * PD_NetHidden4ToWeightHidden3ToHidden4[h4 * NeuronNumHidden3 + h3];

			//��Ȩ�ر���0.9
			OldWeightHidden3ToHidden4[h4 * NeuronNumHidden3 + h3] = WeightHidden3ToHidden4[h4 * NeuronNumHidden3 + h3] * OldWeightPercentage; 

			//����WeightHidden3ToHidden4[h4]��ֵ
			WeightHidden3ToHidden4[h4 * NeuronNumHidden3 + h3] = WeightHidden3ToHidden4[h4 * NeuronNumHidden3 + h3] - LearningRate * PD_WeightHidden3ToHidden4[h4 * NeuronNumHidden3 + h3];

			//��Ȩ���Ǹ�����0.1
			WeightHidden3ToHidden4[h4 * NeuronNumHidden3 + h3] = WeightHidden3ToHidden4[h4 * NeuronNumHidden3 + h3] * NewWeightPercentage + OldWeightHidden3ToHidden4[h4 * NeuronNumHidden3 + h3]; 
		}
	}	










	//****************����3�����Delta_Hidden3****************
	for (h3 = 0; h3 < NeuronNumHidden3; h3++)
	{
		PD_ErrorToNetHidden3[h3] = 0;
	}

	for(h3 = 0; h3 < NeuronNumHidden3; h3++)
	{
		for(h4 = 0; h4 < NeuronNumHidden4; h4++)
		{
			//NetHidden4---->SigmoidHidden3
			PD_NetHidden4ToSigmoidHidden3[h4 * NeuronNumHidden3 + h3] = WeightHidden3ToHidden4[h4 * NeuronNumHidden3 + h3];

			//SigmoidHidden3---->NetHidden3
			PD_SigmoidHidden3ToNetHidden3[h3] = SigmoidHidden3[h3] * (1 - SigmoidHidden3[h3]);

			//Error---->NetHidden3
			PD_ErrorToNetHidden3[h3] += Delta_Hidden4[h4] * PD_NetHidden4ToSigmoidHidden3[h4 * NeuronNumHidden3 + h3] * PD_SigmoidHidden3ToNetHidden3[h3]; 

			//���������ֵ���������������Ԫֵ��ƫ��
			Delta_Hidden3[h3] = PD_ErrorToNetHidden3[h3];
		}
	}










	//****************����WeightHidden2ToHidden3****************
	for(h3 = 0; h3 < NeuronNumHidden3; h3++)
	{
		for(h2 = 0; h2 < NeuronNumHidden2; h2++)
		{
			//NetHidden3---->WeightHidden2ToHidden3
			PD_NetHidden3ToWeightHidden2ToHidden3[h3 * NeuronNumHidden2 + h2] = SigmoidHidden2[h2];
		}
	}		

	for(h3 = 0; h3 < NeuronNumHidden3; h3++)
	{
		for(h2 = 0; h2 < NeuronNumHidden2; h2++)
		{
			//��ʽ������ƫ��
			PD_WeightHidden2ToHidden3[h3 * NeuronNumHidden2 + h2] = Delta_Hidden3[h3] * PD_NetHidden3ToWeightHidden2ToHidden3[h3 * NeuronNumHidden2 + h2];

			//��Ȩ�ر���0.9
			OldWeightHidden2ToHidden3[h3 * NeuronNumHidden2 + h2] = WeightHidden2ToHidden3[h3 * NeuronNumHidden2 + h2] * OldWeightPercentage; 

			//����WeightHidden2ToHidden3��ֵ
			WeightHidden2ToHidden3[h3 * NeuronNumHidden2 + h2] = WeightHidden2ToHidden3[h3 * NeuronNumHidden2 + h2] - LearningRate * PD_WeightHidden2ToHidden3[h3 * NeuronNumHidden2 + h2];

			//��Ȩ���Ǹ�����0.1
			WeightHidden2ToHidden3[h3 * NeuronNumHidden2 + h2] = WeightHidden2ToHidden3[h3 * NeuronNumHidden2 + h2] * NewWeightPercentage + OldWeightHidden2ToHidden3[h3 * NeuronNumHidden2 + h2]; 
		}
	}	










	//****************����2�����Delta_Hidden2****************
	for (h2 = 0; h2 < NeuronNumHidden2; h2++)
	{
		PD_ErrorToNetHidden2[h2] = 0;
	}

	for(h2 = 0; h2 < NeuronNumHidden2; h2++)
	{
		for(h3 = 0; h3 < NeuronNumHidden3; h3++)
		{
			//NetHidden3---->SigmoidHidden2
			PD_NetHidden3ToSigmoidHidden2[h3 * NeuronNumHidden2 + h2] = WeightHidden2ToHidden3[h3 * NeuronNumHidden2 + h2];

			//SigmoidHidden2---->NetHidden2
			PD_SigmoidHidden2ToNetHidden2[h2] = SigmoidHidden2[h2] * (1 - SigmoidHidden2[h2]);

			//Error---->NetHidden2
			PD_ErrorToNetHidden2[h2] += Delta_Hidden3[h3] * PD_NetHidden3ToSigmoidHidden2[h3 * NeuronNumHidden2 + h2] * PD_SigmoidHidden2ToNetHidden2[h2]; 

			//���������ֵ���������������Ԫֵ��ƫ��
			Delta_Hidden2[h2] = PD_ErrorToNetHidden2[h2];
		}
	}










	//****************����WeightHidden1ToHidden2****************
	for(h2 = 0; h2 < NeuronNumHidden2; h2++)
	{
		for(h1 = 0; h1 < NeuronNumHidden1; h1++)
		{
			//NetHidden2---->WeightHidden1ToHidden2
			PD_NetHidden2ToWeightHidden1ToHidden2[h2 * NeuronNumHidden1 + h1] = SigmoidHidden1[h1];
		}
	}		

	for(h2 = 0; h2 < NeuronNumHidden2; h2++)
	{
		for(h1 = 0; h1 < NeuronNumHidden1; h1++)
		{
			//��ʽ������ƫ��
			PD_WeightHidden1ToHidden2[h2 * NeuronNumHidden1 + h1] = Delta_Hidden2[h2] * PD_NetHidden2ToWeightHidden1ToHidden2[h2 * NeuronNumHidden1 + h1];

			//��Ȩ�ر���0.9
			OldWeightHidden1ToHidden2[h2 * NeuronNumHidden1 + h1] = WeightHidden1ToHidden2[h2 * NeuronNumHidden1 + h1] * OldWeightPercentage; 

			//����WeightHidden1ToHidden2[h2]��ֵ
			WeightHidden1ToHidden2[h2 * NeuronNumHidden1 + h1] = WeightHidden1ToHidden2[h2 * NeuronNumHidden1 + h1] - LearningRate * PD_WeightHidden1ToHidden2[h2 * NeuronNumHidden1 + h1];

			//��Ȩ���Ǹ�����0.1
			WeightHidden1ToHidden2[h2 * NeuronNumHidden1 + h1] = WeightHidden1ToHidden2[h2 * NeuronNumHidden1 + h1] * NewWeightPercentage + OldWeightHidden1ToHidden2[h2 * NeuronNumHidden1 + h1]; 
		}
	}	










	//****************����1�����Delta_Hidden1****************
	for (h1 = 0; h1 < NeuronNumHidden1; h1++)
	{
		PD_ErrorToNetHidden1[h1] = 0;
	}

	for(h1 = 0; h1 < NeuronNumHidden1; h1++)
	{
		for(h2 = 0; h2 < NeuronNumHidden2; h2++)
		{
			//NetHidden2---->SigmoidHidden1
			PD_NetHidden2ToSigmoidHidden1[h2 * NeuronNumHidden1 + h1] = WeightHidden1ToHidden2[h2 * NeuronNumHidden1 + h1];

			//SigmoidHidden1---->NetHidden1
			PD_SigmoidHidden1ToNetHidden1[h1] = SigmoidHidden1[h1] * (1 - SigmoidHidden1[h1]);

			//Error---->NetHidden1
			PD_ErrorToNetHidden1[h1] += Delta_Hidden2[h2] * PD_NetHidden2ToSigmoidHidden1[h2 * NeuronNumHidden1 + h1] * PD_SigmoidHidden1ToNetHidden1[h1]; 

			//���������ֵ���������������Ԫֵ��ƫ��
			Delta_Hidden1[h1] = PD_ErrorToNetHidden1[h1];
		}
	}










	//****************����WeightInputToHidden1****************
	for (h1 = 0; h1 < NeuronNumHidden1; h1++)
	{
		for(j = 0; j < pixels; j++)
		{
			for (i = 0; i < pixels; i++)
			{
				//NetHidden1---->WeightInputToHidden1
				PD_NetHidden1ToWeightInputToHidden1[h1 * pixels * pixels + (j * pixels + i)] = iPicture[j][i];
			}
		}
	}


	for (h1 = 0; h1 < NeuronNumHidden1; h1++)
	{
		for(j = 0; j < pixels; j++)
		{
			for (i = 0; i < pixels; i++)
			{
				PD_WeightInputToHidden1[h1 * pixels * pixels + (j * pixels + i)] = Delta_Hidden1[h1] * PD_NetHidden1ToWeightInputToHidden1[h1 * pixels * pixels + (j * pixels + i)];

				//��Ȩ�ر���0.9
				OldWeightInputToHidden1[h1 * pixels * pixels + (j * pixels + i)] = WeightInputToHidden1[h1 * pixels * pixels + (j * pixels + i)] * OldWeightPercentage;

				////����WeightInputToHidden1��ֵ
				WeightInputToHidden1[h1 * pixels * pixels + (j * pixels + i)] = 
					WeightInputToHidden1[h1 * pixels * pixels + (j * pixels + i)] - LearningRate * PD_WeightInputToHidden1[h1 * pixels * pixels + (j * pixels + i)]; 

				//��Ȩ���Ǹ�����0.1
				WeightInputToHidden1[h1 * pixels * pixels + (j * pixels + i)] = 
					WeightInputToHidden1[h1 * pixels * pixels + (j * pixels + i)] * NewWeightPercentage + OldWeightInputToHidden1[h1 * pixels * pixels + (j * pixels + i)];
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