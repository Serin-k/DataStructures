#include<stdio.h>	
#include<string.h>
#include<stdlib.h>	
#include<math.h>

#define MAX_TERMS 100

/* ������а� 2018130926 �輼��
0407 ���׽��� �� ���ϱ� */

/* Definition of Global Functions */
void padd(int starta, int finisha, int startb, int finishb, int *startd, int *finishd);
void attach(float coefficient, int exponent);
int COMPARE(int A_expon, int B_expon);
void COPY(char* str, char* result);
void Seperation(char*Fx);

/* Definition of Global Variables */
typedef struct {
	float coef;
	int expon;
} polynomial;
polynomial terms[MAX_TERMS];
polynomial *ptr = terms;
int avail = 0;

int main(void) {
	/* Definition of Local Variables */
	int starta = 0, finisha = 0, startb = 0, finishb = 0, *startd = 0, *finishd = 0;
	char X[10] = "X^", oper[10] = "+", COEF[100] = "", EXPON[100] = "";
	char Ax[MAX_TERMS] = "3X^5+2X^2+4";
	char Bx[MAX_TERMS] = "X^4+10X^3+3X^2+1";
	char Result[MAX_TERMS] = "";

	printf("\n-------2018130926 �輼��-------\n\n  <Polynomial Addition>\n\nA(x) = %s\nB(x) = %s\n", Ax, Bx);
	/* ���׽� A(x)�� ����� ������ ����üterms�� �и� */
	starta = avail;
	Seperation(Ax);
	finisha = avail - 1;
	/* ���׽� B(x)�� ����� ������ ����üterms�� �и� */
	startb = avail;
	Seperation(Bx);
	finishb = avail - 1;
	/* ���׽� A(x)�� B(x) ���� */
	padd(starta, finisha, startb, finishb, startd, finishd);
	/* ������� �ϳ��� ���ڿ��� ����� */
	for (int i = finishb + 1;i < avail;i++) {				//����ü�� ����� ������ ����� ������ �ϳ��� ���ڿ��� ������Ŵ.
		if (terms[i].coef != 1) {							//x�� ������ 1�� �ƴ� ��� ������ ���ڷ� �����. '1X'�� ���� ��µǴ� ��� ����
			_itoa(terms[i].coef, COEF, 10);					//������ ���ڿ�ȭ
			COPY(COEF, Result);								//��� �迭�� ������ �����س���
		}
		if (terms[i].expon != 0) {							//x�� ����� 0�� �ƴ� ��� X�� �ִ� ������ �����. �ڿ����� '5X0'�� ���� ��µǴ� ��� ����
			COPY(X, Result);								//��� �迭�� X^�� �����س���
			_itoa(terms[i].expon, EXPON, 10);				//����� ���ڿ�ȭ
			COPY(EXPON, Result);							//��� �迭�� ����� �����س���
			COPY(oper, Result);								//��� �迭�� +�� �����س���
		}
		COEF[10] = "";										//����ü �迭�� ���� ���� �б� ���� �ʱ�ȭ
		EXPON[10] = "";
	}

	printf("\nResult = %s\n\n----------Thank You:)----------\n\n*Press Enter to Exit*\n", Result);		
	char end = getchar();									//����� ��� �� ���� �Է½� ���α׷� ����
	if (end == '\n')
		return 0;
}




/* ��� �迭�� Ư���� ���ڿ��� ������ �ִ´�.*/
void COPY(char* str, char* result) {
	int len;
	len = strlen(result);
	strcpy(result + len, str);
}

/* A(x)�� B(x)�� ���Ͽ� D(x)�� �����Ѵ�. */
void padd(int starta, int finisha, int startb, int finishb, int *startd, int *finishd) {		//Program 2.6 Polynomial Addition
	float coefficient;
	startd = &avail;
	while (starta <= finisha && startb <= finishb)
		switch (COMPARE(terms[starta].expon, terms[startb].expon)) {
		case -1:																				//a�� expon < b�� expon
			attach(terms[startb].coef, terms[startb].expon);
			startb++;
			break;
		case 0:																					//a�� expon = b�� expon
			coefficient = terms[starta].coef + terms[startb].coef;
			if (coefficient)
				attach(coefficient, terms[starta].expon);
			starta++;
			startb++;
			break;
		case 1:																					//a�� expon > b�� expon
			attach(terms[starta].coef, terms[starta].expon);
			starta++;
		}
	for (;starta <= finisha;starta++)															//A(x)�� ������ �׵��� ÷���Ѵ�.
		attach(terms[starta].coef, terms[starta].expon);
	for (;startb <= finishb;startb++)															//B(x)�� ������ �׵��� ÷���Ѵ�.
		attach(terms[startb].coef, terms[startb].expon);
	finishd = &avail - 1;
}

/* ���ο� ���� ���׽Ŀ� ÷���Ѵ�. */
void attach(float coefficient, int exponent) {
	if (avail >= MAX_TERMS) {
		fprintf(stderr, "���� ����");
		exit(1);
	}
	terms[avail].coef = coefficient;	
	terms[avail++].expon = exponent;
}

/* �� ���� ����� ���Ѵ�. */
int COMPARE(int A_expon, int B_expon) {
	if (A_expon == B_expon)							//Ax��� = Bx���
		return 0;
	else if (A_expon > B_expon)						//Ax��� > Bx���
		return 1;
	else if (A_expon < B_expon)						//Ax��� < Bx���
		return -1;
}

/* ���׽��� ������ ����� ����ü�� �и��Ѵ�. */
void Seperation(char* Fx) {
	int i = 0, p = 0, End = 1;
	int num = 1;
	while (End) {													//���׽� Fx�� ���� ������ �ݺ��ϸ� �и��Ѵ�.
		if (Fx[i] >= '0' && Fx[i] <= '9') {
			int fx = Fx[i] - 48;									//���ڸ� ���ڷ� �ٲ���
			if (p > 0)												//���ڸ� �̻��� ���� ó���� ���� ���
				num = ((num * pow(10, p++)) + fx);
			else if (p == 0) {										//ù ��° �ڸ���, �� �ڸ� ���� �Է��� �ޱ� ����.
				num = fx;
				p++;
			}
		}
		else if (Fx[i] == 'X')
			(ptr + avail)->coef = num;								//������ ����ü�� �и��Ѵ�.			
		else if (Fx[i] == '^') {
			num = 1;												//����� ����� ������ ���� num �ʱ�ȭ
			p = 0;
		}
		else if (Fx[i] == '+') {
			(ptr + avail++)->expon = num;							//����� ����ü�� �Է�
			num = 1;												//������ ����� ������ ���� num �ʱ�ȭ
			p = 0;
		}
		else {
			(ptr + avail++)->coef = num;							//������ �ڿ����� ����ü�� �Է�
			End = 0;												//�ݺ��� ����
		}
		i++;
	}
}