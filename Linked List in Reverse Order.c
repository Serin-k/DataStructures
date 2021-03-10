#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p,s) \
	if (!((p)=malloc(s))) { \
		printf(stderr, "Insufficient memory"); \
		exit(EXIT_FAILURE); \
	}

typedef struct listNode *listPointer;				//����ü ����
typedef struct listNode {
	int data;
	listPointer link;
};

listPointer create2();							//�Լ� ����
void printList(listPointer first);
void insert(listPointer first, listPointer x);
listPointer invert(listPointer lead);

int main(void) {
	printf("\n    [Singular Linked List]\n\n=======2018130926 �輼��=======\n\n");
	listPointer first = NULL;						//Creation (������ ����)
	MALLOC(first, sizeof(*first));			//Allocation (���� �޸� �Ҵ�)

	first = create2();						//������ ���Ḯ��Ʈ�� �����ּҸ� ������ first�� �޾���
	printf("\n<��� ���� ��>\n");
	printList(first);						//���

	insert(first, first);					//first�� ����Ű�� ü���� first �ڿ� ���� ���� 
	printf("\n<50 ���� ��>\n");
	printList(first);						//���

	first = invert(first);					//first�� ����Ű�� ü���� �������� ��ȯ
	printf("\n<����>\n");
	printList(first);						//���

	printf("\n==========Thank You:)==========\n\n*Press Enter to Exit*\n");
	char end = getchar();					//���� �Է½� ���α׷� ����
	if (end == '\n')
		return 0;
}

/*Program 4.1 Create a two-node list*/
listPointer create2()
{ /*2���� ��带 ���� ���� ����Ʈ�� ����*/
	listPointer first, second;
	MALLOC(first, sizeof(*first));			//�޸� �Ҵ�
	MALLOC(second, sizeof(*second));		//�޸� �Ҵ�
	second->link = NULL;					//������ ���(�� ��° ���)���� ��ũ���� ����
	second->data = 20;						//������ ���(�� ��° ���)�� �����Ͱ�	�Է�	
	first->data = 10;						//ù ��° ��忡 �����Ͱ� �Է�
	first->link = second;					//ù ��° ���� �� ��° ��� ����
	return first;
}

/*Program 4.2 Simple Insert into front of list*/
void insert(listPointer first, listPointer x)
{ /*data=50�� ���ο� ��带 ü�� first�� ��� x�ڿ� ����*/
	listPointer temp;
	MALLOC(temp, sizeof(*temp));			//������ �����Ͱ���
	temp->data = 50;						//�����Ͱ� �Է�
	if (first) {							//no empty list
		temp->link = x->link;				//������ �������� �޺κ� ����
		x->link = temp;						//������ �������� �պκ� ����
	}
	else {									//empty list
		temp->link = NULL;
		first = temp;						//������ �����Ͱ� ù ��尡 ��
	}
}

/*Program 4.4 Printing*/
void printList(listPointer first) {
	for (; first; first = first->link)		//���Ḯ��Ʈ�� ���󰡸� �����͸� �ϳ��� �����
		printf("%d\n", first->data);
	printf("\n");
}

/*Program 4.16 Inverting a singly linked list*/
listPointer invert(listPointer lead)
{ /*lead �� ����Ű�� �ִ� ����Ʈ�� �������� �����*/
	listPointer middle, trail;
	middle = NULL;
	while (lead) {									
		trail = middle;						//middle�� ���� ������ ���󰡴� ���� trail
		middle = lead;						//lead�� ���� ������ ���󰡴� ���� middle
		lead = lead->link;					//while�� ���� ����Ʈ�� ������ lead�� ��� �ϳ��� ����Ű�� ��
		middle->link = trail;				//middle�� ����Ű�� ���� trail�� ����Ű�� ��带 ����
	}
	return middle;
}