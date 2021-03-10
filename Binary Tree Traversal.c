#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 100
#define MAX_STACK_SIZE 100
//����Ʈ�� ����ü ����
typedef struct node treePointer;
typedef struct node {
	int data;
	treePointer *leftChild;
	treePointer *rightChild;
};
//�������� �ʱ�ȭ
treePointer* queue[MAX_QUEUE_SIZE];
int rear = -1;
int front = -1;
//�Լ� ����
treePointer* create();
treePointer* insert(char c);
treePointer* copy(treePointer* original);
void inorder(treePointer* ptr);
void preorder(treePointer* ptr);
void levelOrder(treePointer* ptr);
void addq(treePointer* ptr);
treePointer* deleteq(int* front, int rear);
void queueFull();
void iterPostorder(treePointer* node);
void push(int* TOP, treePointer* node, treePointer** STACK);
treePointer* pop(int* TOP, treePointer** STACK);
void stackFull();

int main(void) {
	// ����Ʈ�� ����
	treePointer* root = create();
	treePointer* copied = NULL;
	printf("\nSelect the order type of printing binary tree\n");
	printf("	1: Copying\n	2: Preorder\n	3: Inorder\n	4: Postorder\n	5: Levelorder");
	printf("\n\nYour Input: ");
	char in = getchar();			//������� �Է¹޾� ������ ó����
	printf("\nResult: ");
	switch (in) {
	case '1': {
		copied = copy(root);		//����� Ʈ���� root�� copied�� �޴´�
		if (copied)					//copied�� ���� ��ȿ�ϴٸ�
			printf("���� �Ϸ�");	//���������� ���簡 �� ����
		else						//copied���� ���ٸ�
			printf("Copy Error");	//���翡 ������ ���̹Ƿ� �������� ���
		}						
		break;
	case '2': preorder(root);		//������ȸ(��ȯ��)
		break;
	case '3': inorder(root); 		//������ȸ(��ȯ��)
		break;
	case '4': iterPostorder(root);	//������ȸ(�ݺ���)
		break;
	case '5': levelOrder(root);		//����������ȸ(�ݺ���)
		break;
	default:
		printf("Error, input number must be in 1~5");	//���� �Է°��� �ƴ϶�� �����޼��� ���
	}
	printf("\n=============================\n**Input Anything to Exit**\n");
	while (getchar() != '\n');		//�Է¹��ۿ� ������ ���� ���
	int end = getchar();			//���� �Է½� ���α׷� ����
	if (end) {
		printf("\n===Program Ends, Thank You===\n");
		return 0;
	}
}
treePointer* create() {
	// ����Ʈ�� ����
	treePointer *root, *ptr, *rptr;//ptr�� root����� ���ʳ���� ������ ����Ű��, rptr�� ptr�� �������ڽ��� ����Ŵ
	root = insert('A');				//root �����Ϳ� �� ����
	root->leftChild = insert('B');	//root ��� ���� �ڽĿ� �� ����
	root->rightChild = insert('C');	//root ��� ������ �ڽĿ� �� ����
	ptr = root->leftChild;			//ptr=B (root ����� �����ڽ�)
	ptr->leftChild = insert('D');	//������(data=B) ���� �ڽ� �� ����
	ptr->rightChild = insert('E');	//������(data=B) ������ �ڽ� �� ����
	rptr = ptr->rightChild;			//rptr=E (�������� �������ڽ�)
	rptr->leftChild = insert('J');	//������(data=E) ���� �ڽ� �� ����
	ptr = ptr->leftChild;			//ptr=D (root����� �����ڽ��� �����ڽ�)
	rptr = ptr->rightChild;			//rptr=I (�������� �������ڽ�)
	ptr->leftChild = insert('H');	//������(data=D) ���� �ڽ� �� ����
	ptr->rightChild = insert('I');	//������(data=D) ������ �ڽ� �� ����
	ptr = root->rightChild;			//ptr=C (root�� ������ �ڽ�)
	ptr->leftChild = insert('F');	//������(data=C) ���� �ڽ� �� ����
	ptr->rightChild = insert('G');	//������(data=C) ������ �ڽ� �� ����
	rptr = ptr->rightChild;			//rptr=G (�������� �������ڽ�)
	ptr = ptr->leftChild;			//ptr=F (root�� �������ڽ��� �����ڽ�)
	ptr->rightChild = insert('K');	//������(data=F) ������ �ڽ� �� ����
	rptr->leftChild = insert('L');	//������ ������(data=G) ���� �ڽ� �� ����
	rptr->rightChild = insert('M');	//������ ������(data=M) ���� �ڽ� �� ����
	return root;
}
treePointer* insert(char c) {
	//��忡 �����Ͱ��� �����ϰ� �ش� ����� �����͸� ��ȯ��
	treePointer *ptr;
	ptr = (treePointer*)malloc(sizeof(treePointer));
	ptr->data = c;					//��忡 �� ����
	ptr->leftChild = NULL;			//������ ���(leaf node)�� �����ڽİ� ������ �ڽ��� NULL���̾���ϱ⿡ 
	ptr->rightChild = NULL;			//���� ���� ���Ե��� ���� ������ NULL�� ��������
	return ptr;						//���� ���Ե� ����� ������ ��ȯ
}
//Program 5.6: Copying a binary tree(p.212)
treePointer* copy(treePointer* original) {
	//�־��� Ʈ���� �����ϰ� ����� Ʈ���� treePointer�� ��ȯ��
	treePointer *temp;
	if (original) {
		temp = (treePointer*)malloc(sizeof(treePointer));
		temp->leftChild = copy(original->leftChild);
		temp->rightChild = copy(original->rightChild);
		temp->data = original->data;
		return temp;
	}
	return 0;
}
//Program 5.1: Traversal of a binary tree(p.207)
void inorder(treePointer* ptr) {
	if (ptr) {
		inorder(ptr->leftChild);
		printf("%c", ptr->data);
		inorder(ptr->rightChild);
	}
}
//Program 5.2: Preorder Traversal of a binary tree(p.208)
void preorder(treePointer* ptr) {
	if (ptr) {
		printf("%c", ptr->data);
		preorder(ptr->leftChild);
		preorder(ptr->rightChild);
	}
}
//Program 5.5: Level-order traversal(p.211)
void levelOrder(treePointer* ptr) {
	front = rear = 0;
	if (!ptr) return;					//����Ʈ��
	addq(ptr);							//ptr�� ����Ű�°� ť�� ����
	for (;;) {							//�ݺ��ϸ�
		ptr = deleteq(&front, rear);	//ť���� �ϳ��� �����ϰ� ptr�� �޾ƿ�
		if (ptr) {						//������ ���ڰ� �ϳ��� �ִٸ�
			printf("%c", ptr->data);	//������ ���ڰ� ����Ű�� ������ ���
			if (ptr->leftChild)			//������ ������ ���� �ڽ��� �ִٸ�
				addq(ptr->leftChild);	//���� �ڽ��� ť�� ����
			if (ptr->rightChild)		//������ ������ ������ �ڽ��� �ִٸ�
				addq(ptr->rightChild);	//������ �ڽ��� ť�� ����
		}
		else break;
	}
}
// Program 3.7: Add to a circular queue (p.118) 
void addq(treePointer* ptr) {
	/* add an item to the queue*/
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	if (front == rear)
		queueFull();				//ť�� �޸𸮰� full�� ��, �����޼��� ��� �� ����
	queue[rear] = ptr;
}
//Program 3.8: Delete from a circular queue(p.119)
treePointer* deleteq(int* front, int rear) {
	// remove front element from the queue
	if (*front == rear)				//����Ʈ��
		return NULL;
	*front = (*front + 1) % MAX_QUEUE_SIZE;
	return queue[(*front)];
}
void queueFull() {
	printf("\n<<Queue is full, cannot add element>>\n==========Program ends==========\n\n");
	exit(EXIT_FAILURE);
}
void iterPostorder(treePointer* node) {
	/* ���� ��ȸ */
	treePointer* stack[MAX_STACK_SIZE];					//���� �о���̸� ����� ����
	treePointer* temp[MAX_STACK_SIZE];					//(���� root�� �ƴ� ��)stack���� ���� ��µǴ� ���� ������ �ϴ� ���� temp
	int ST_first = 0;									//temp���ú��� ���� ��µǾ���� ������ ���ڸ�ŭ �� �����Ǵ� ����
	int top = -1;
	int tempTOP = -1;
	treePointer* print = NULL;
	treePointer* root = node;
	for (;;) {
		for (;node;node = node->leftChild) {			//���ʳ����� stack�� ����
			if ((root!=temp[tempTOP]) && (tempTOP > -1))//temp���ÿ� (root�� �ƴ�) ���� �������·� stack�� ���� push�Ǿ��ٸ�
				ST_first++;								//temp���� ���� ��µǾ���� ���ڰ� ���ÿ� ���ԵǾ��ٴ� ���̹Ƿ� �� ����
			push(&top, node, stack);
		}
		node = pop(&top, stack);						//���ÿ��� ���� ���� ���ڸ� pop
		if (ST_first && (tempTOP > -1))					//���ÿ��� ���� ��µǾ���� ���� �ϳ��� pop�����Ƿ� ST_first�� ����
			ST_first--;									
		if (!node) break;								//empty stack
		if (node->rightChild) {							//pop�� ������ �������ڽ��� �ִٸ� ���ڸ� temp���ÿ� ����
			push(&tempTOP, node, temp);	
			node = node->rightChild;	
		}
		else {											//����� �������ڽ��� ���ٸ�, �� ���
			printf("%c", node->data);	
			while (ST_first) {							//temp���ÿ� ���� �ִ�ä�� stack�� �׿��ٸ�, ���� ������ŭ ������ ����
				print=pop(&top, stack);					//stack���� �ϳ��� ������
				if ((node == (print->leftChild)) && (print->rightChild)) {	//������ ����� �����ڽ��� ��� ����� ����̰�, ������ ����� �������ڽ��� ������ 
					push(&top, print, stack);			//���� �������ڽ��� Ž������ �ʾҴٴ� ���̹Ƿ� ������ ���ÿ� �ٽ� �־��ش�
					break;
				}
				else{									//�׷��� �ʴٸ�(leaf����̰ų� �������ڽ��̾��� ���) temp���� �켱������ ���� ������ ���� ���
					printf("%c", print->data);
					ST_first--;
				}
			}
			if ((ST_first == 0) && (tempTOP > -1)) {	//���ÿ��� ��µǾ���� ���ڰ� ����, temp���ÿ� ���� ��尡 �ִٸ� �ϳ����� �����
				print = pop(&tempTOP, temp);
				printf("%c", print->data);						
				}
			node = NULL;
		}
	}
	for (;tempTOP > -1;){								//�ݺ��� ���� �� temp���ÿ� ���� ������ ���
		print = pop(&tempTOP, temp);
		printf("%c", print->data);		
	}
}
//Program 3.1: Add to a stack (p.111)
void push(int* TOP, treePointer* node, treePointer** STACK) {
	/* add an item to the LOCAL stack */
	if ((*TOP) >= MAX_STACK_SIZE - 1) {
		stackFull();
		return;
	}
	STACK[++(*TOP)] = node;
}
//Program 3.2: Delete from a stack (p.111)
treePointer* pop(int* TOP, treePointer** STACK) {
	/* delete and return the top element from the stack */
	if ((*TOP) == -1) 				//���� �������� Ȯ��
		return NULL;			//�����̶�� NULL��ȯ	
	return STACK[(*TOP)--];		//������ �ƴ϶�� ������ ���� ���� �ִ� ��� ����
}
void stackFull() {
	printf("\n<<Stack is full, cannot add element>>\n==========Program ends==========\n\n");
	exit(EXIT_FAILURE);
}