#include<stdio.h>	
#include<string.h>
#include<stdlib.h>	
#include<math.h>

#define MAX_TERMS 100

/* 영어영문학과 2018130926 김세린
0407 다항식의 합 구하기 */

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

	printf("\n-------2018130926 김세린-------\n\n  <Polynomial Addition>\n\nA(x) = %s\nB(x) = %s\n", Ax, Bx);
	/* 다항식 A(x)의 계수와 지수를 구조체terms에 분리 */
	starta = avail;
	Seperation(Ax);
	finisha = avail - 1;
	/* 다항식 B(x)의 계수와 지수를 구조체terms에 분리 */
	startb = avail;
	Seperation(Bx);
	finishb = avail - 1;
	/* 다항식 A(x)와 B(x) 덧셈 */
	padd(starta, finisha, startb, finishb, startd, finishd);
	/* 결과식을 하나의 문자열로 만들기 */
	for (int i = finishb + 1;i < avail;i++) {				//구조체에 저장된 지수와 계수를 꺼내와 하나의 문자열로 변형시킴.
		if (terms[i].coef != 1) {							//x의 지수가 1이 아닐 경우 지수를 숫자로 출력함. '1X'와 같이 출력되는 경우 방지
			_itoa(terms[i].coef, COEF, 10);					//지수의 문자열화
			COPY(COEF, Result);								//결과 배열에 지수를 복사해넣음
		}
		if (terms[i].expon != 0) {							//x의 계수가 0이 아닐 경우 X가 있는 항으로 출력함. 자연수가 '5X0'과 같이 출력되는 경우 방지
			COPY(X, Result);								//결과 배열에 X^을 복사해넣음
			_itoa(terms[i].expon, EXPON, 10);				//계수의 문자열화
			COPY(EXPON, Result);							//결과 배열에 계수를 복사해넣음
			COPY(oper, Result);								//결과 배열에 +를 복사해넣음
		}
		COEF[10] = "";										//구조체 배열의 다음 인자 읽기 위해 초기화
		EXPON[10] = "";
	}

	printf("\nResult = %s\n\n----------Thank You:)----------\n\n*Press Enter to Exit*\n", Result);		
	char end = getchar();									//결과값 출력 후 엔터 입력시 프로그램 종료
	if (end == '\n')
		return 0;
}




/* 결과 배열에 특정한 문자열을 복사해 넣는다.*/
void COPY(char* str, char* result) {
	int len;
	len = strlen(result);
	strcpy(result + len, str);
}

/* A(x)와 B(x)를 더하여 D(x)를 생성한다. */
void padd(int starta, int finisha, int startb, int finishb, int *startd, int *finishd) {		//Program 2.6 Polynomial Addition
	float coefficient;
	startd = &avail;
	while (starta <= finisha && startb <= finishb)
		switch (COMPARE(terms[starta].expon, terms[startb].expon)) {
		case -1:																				//a의 expon < b의 expon
			attach(terms[startb].coef, terms[startb].expon);
			startb++;
			break;
		case 0:																					//a의 expon = b의 expon
			coefficient = terms[starta].coef + terms[startb].coef;
			if (coefficient)
				attach(coefficient, terms[starta].expon);
			starta++;
			startb++;
			break;
		case 1:																					//a의 expon > b의 expon
			attach(terms[starta].coef, terms[starta].expon);
			starta++;
		}
	for (;starta <= finisha;starta++)															//A(x)의 나머지 항들을 첨가한다.
		attach(terms[starta].coef, terms[starta].expon);
	for (;startb <= finishb;startb++)															//B(x)의 나머지 항들을 첨가한다.
		attach(terms[startb].coef, terms[startb].expon);
	finishd = &avail - 1;
}

/* 새로운 항을 다항식에 첨가한다. */
void attach(float coefficient, int exponent) {
	if (avail >= MAX_TERMS) {
		fprintf(stderr, "항이 많음");
		exit(1);
	}
	terms[avail].coef = coefficient;	
	terms[avail++].expon = exponent;
}

/* 두 항의 계수를 비교한다. */
int COMPARE(int A_expon, int B_expon) {
	if (A_expon == B_expon)							//Ax계수 = Bx계수
		return 0;
	else if (A_expon > B_expon)						//Ax계수 > Bx계수
		return 1;
	else if (A_expon < B_expon)						//Ax계수 < Bx계수
		return -1;
}

/* 다항식의 지수와 계수를 구조체에 분리한다. */
void Seperation(char* Fx) {
	int i = 0, p = 0, End = 1;
	int num = 1;
	while (End) {													//다항식 Fx가 끝날 때까지 반복하며 분리한다.
		if (Fx[i] >= '0' && Fx[i] <= '9') {
			int fx = Fx[i] - 48;									//문자를 숫자로 바꿔줌
			if (p > 0)												//두자리 이상의 정수 처리를 위한 계산
				num = ((num * pow(10, p++)) + fx);
			else if (p == 0) {										//첫 번째 자리나, 한 자리 수의 입력을 받기 위함.
				num = fx;
				p++;
			}
		}
		else if (Fx[i] == 'X')
			(ptr + avail)->coef = num;								//지수를 구조체에 분리한다.			
		else if (Fx[i] == '^') {
			num = 1;												//계수의 계산이 끝나면 변수 num 초기화
			p = 0;
		}
		else if (Fx[i] == '+') {
			(ptr + avail++)->expon = num;							//계수를 구조체에 입력
			num = 1;												//지수의 계산이 끝나면 변수 num 초기화
			p = 0;
		}
		else {
			(ptr + avail++)->coef = num;							//나머지 자연수를 구조체에 입력
			End = 0;												//반복문 종료
		}
		i++;
	}
}