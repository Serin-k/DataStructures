#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p,s) \
	if (!((p)=malloc(s))) { \
		printf(stderr, "Insufficient memory"); \
		exit(EXIT_FAILURE); \
	}

typedef struct listNode *listPointer;				//구조체 선언
typedef struct listNode {
	int data;
	listPointer link;
};

listPointer create2();							//함수 선언
void printList(listPointer first);
void insert(listPointer first, listPointer x);
listPointer invert(listPointer lead);

int main(void) {
	printf("\n    [Singular Linked List]\n\n=======2018130926 김세린=======\n\n");
	listPointer first = NULL;						//Creation (포인터 생성)
	MALLOC(first, sizeof(*first));			//Allocation (동적 메모리 할당)

	first = create2();						//생성한 연결리스트의 시작주소를 포인터 first로 받아줌
	printf("\n<노드 생성 후>\n");
	printList(first);						//출력

	insert(first, first);					//first가 가리키는 체인의 first 뒤에 인자 삽입 
	printf("\n<50 삽입 후>\n");
	printList(first);						//출력

	first = invert(first);					//first가 가리키는 체인을 역순으로 변환
	printf("\n<역순>\n");
	printList(first);						//출력

	printf("\n==========Thank You:)==========\n\n*Press Enter to Exit*\n");
	char end = getchar();					//엔터 입력시 프로그램 종료
	if (end == '\n')
		return 0;
}

/*Program 4.1 Create a two-node list*/
listPointer create2()
{ /*2개의 노드를 가진 연결 리스트의 생성*/
	listPointer first, second;
	MALLOC(first, sizeof(*first));			//메모리 할당
	MALLOC(second, sizeof(*second));		//메모리 할당
	second->link = NULL;					//마지막 노드(두 번째 노드)에는 링크값이 없음
	second->data = 20;						//마지막 노드(두 번째 노드)에 데이터값	입력	
	first->data = 10;						//첫 번째 노드에 데이터값 입력
	first->link = second;					//첫 번째 노드와 두 번째 노드 연결
	return first;
}

/*Program 4.2 Simple Insert into front of list*/
void insert(listPointer first, listPointer x)
{ /*data=50인 새로운 노드를 체인 first의 노드 x뒤에 삽입*/
	listPointer temp;
	MALLOC(temp, sizeof(*temp));			//삽입할 데이터공간
	temp->data = 50;						//데이터값 입력
	if (first) {							//no empty list
		temp->link = x->link;				//삽입할 데이터의 뒷부분 연결
		x->link = temp;						//삽입할 데이터의 앞부분 연결
	}
	else {									//empty list
		temp->link = NULL;
		first = temp;						//삽입한 데이터가 첫 노드가 됨
	}
}

/*Program 4.4 Printing*/
void printList(listPointer first) {
	for (; first; first = first->link)		//연결리스트를 따라가며 데이터를 하나씩 출력함
		printf("%d\n", first->data);
	printf("\n");
}

/*Program 4.16 Inverting a singly linked list*/
listPointer invert(listPointer lead)
{ /*lead 가 가리키고 있는 리스트를 역순으로 만든다*/
	listPointer middle, trail;
	middle = NULL;
	while (lead) {									
		trail = middle;						//middle의 값을 받으며 따라가는 변수 trail
		middle = lead;						//lead의 값을 받으며 따라가는 변수 middle
		lead = lead->link;					//while문 돌며 리스트의 끝까지 lead가 노드 하나씩 가리키게 됨
		middle->link = trail;				//middle이 가리키는 노드와 trail이 가리키는 노드를 연결
	}
	return middle;
}