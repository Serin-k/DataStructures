#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 100
#define MAX_STACK_SIZE 100
//이진트리 구조체 정의
typedef struct node treePointer;
typedef struct node {
	int data;
	treePointer *leftChild;
	treePointer *rightChild;
};
//전역변수 초기화
treePointer* queue[MAX_QUEUE_SIZE];
int rear = -1;
int front = -1;
//함수 선언
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
	// 이진트리 생성
	treePointer* root = create();
	treePointer* copied = NULL;
	printf("\nSelect the order type of printing binary tree\n");
	printf("	1: Copying\n	2: Preorder\n	3: Inorder\n	4: Postorder\n	5: Levelorder");
	printf("\n\nYour Input: ");
	char in = getchar();			//사용자의 입력받아 다음을 처리함
	printf("\nResult: ");
	switch (in) {
	case '1': {
		copied = copy(root);		//복사된 트리의 root를 copied로 받는다
		if (copied)					//copied의 값이 유효하다면
			printf("복사 완료");	//성공적으로 복사가 된 것임
		else						//copied값이 없다면
			printf("Copy Error");	//복사에 실패한 것이므로 오류임을 출력
		}						
		break;
	case '2': preorder(root);		//전위순회(순환문)
		break;
	case '3': inorder(root); 		//중위순회(순환문)
		break;
	case '4': iterPostorder(root);	//후위순회(반복문)
		break;
	case '5': levelOrder(root);		//레벨순서순회(반복문)
		break;
	default:
		printf("Error, input number must be in 1~5");	//정상 입력값이 아니라면 오류메세지 출력
	}
	printf("\n=============================\n**Input Anything to Exit**\n");
	while (getchar() != '\n');		//입력버퍼에 남겨진 내용 비움
	int end = getchar();			//엔터 입력시 프로그램 종료
	if (end) {
		printf("\n===Program Ends, Thank You===\n");
		return 0;
	}
}
treePointer* create() {
	// 이진트리 생성
	treePointer *root, *ptr, *rptr;//ptr은 root노드의 양쪽노드의 왼쪽을 가리키며, rptr은 ptr의 오른쪽자식을 가리킴
	root = insert('A');				//root 포인터에 값 삽입
	root->leftChild = insert('B');	//root 노드 왼쪽 자식에 값 삽입
	root->rightChild = insert('C');	//root 노드 오른쪽 자식에 값 삽입
	ptr = root->leftChild;			//ptr=B (root 노드의 왼쪽자식)
	ptr->leftChild = insert('D');	//포인터(data=B) 왼쪽 자식 값 삽입
	ptr->rightChild = insert('E');	//포인터(data=B) 오른쪽 자식 값 삽입
	rptr = ptr->rightChild;			//rptr=E (포인터의 오른쪽자식)
	rptr->leftChild = insert('J');	//포인터(data=E) 왼쪽 자식 값 삽입
	ptr = ptr->leftChild;			//ptr=D (root노드의 왼쪽자식의 왼쪽자식)
	rptr = ptr->rightChild;			//rptr=I (포인터의 오른쪽자식)
	ptr->leftChild = insert('H');	//포인터(data=D) 왼쪽 자식 값 삽입
	ptr->rightChild = insert('I');	//포인터(data=D) 오른쪽 자식 값 삽입
	ptr = root->rightChild;			//ptr=C (root의 오른쪽 자식)
	ptr->leftChild = insert('F');	//포인터(data=C) 왼쪽 자식 값 삽입
	ptr->rightChild = insert('G');	//포인터(data=C) 오른쪽 자식 값 삽입
	rptr = ptr->rightChild;			//rptr=G (포인터의 오른쪽자식)
	ptr = ptr->leftChild;			//ptr=F (root의 오른쪽자식의 왼쪽자식)
	ptr->rightChild = insert('K');	//포인터(data=F) 오른쪽 자식 값 삽입
	rptr->leftChild = insert('L');	//오른쪽 포인터(data=G) 왼쪽 자식 값 삽입
	rptr->rightChild = insert('M');	//오른쪽 포인터(data=M) 왼쪽 자식 값 삽입
	return root;
}
treePointer* insert(char c) {
	//노드에 데이터값을 삽입하고 해당 노드의 포인터를 반환함
	treePointer *ptr;
	ptr = (treePointer*)malloc(sizeof(treePointer));
	ptr->data = c;					//노드에 값 삽입
	ptr->leftChild = NULL;			//마지막 노드(leaf node)의 왼쪽자식과 오른쪽 자식은 NULL값이어야하기에 
	ptr->rightChild = NULL;			//아직 값이 삽입되지 않은 영역에 NULL값 삽입해줌
	return ptr;						//값이 삽입된 노드의 포인터 반환
}
//Program 5.6: Copying a binary tree(p.212)
treePointer* copy(treePointer* original) {
	//주어진 트리를 복사하고 복사된 트리의 treePointer를 반환함
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
	if (!ptr) return;					//공백트리
	addq(ptr);							//ptr이 가르키는걸 큐에 삽입
	for (;;) {							//반복하며
		ptr = deleteq(&front, rear);	//큐에서 하나를 삭제하고 ptr로 받아옴
		if (ptr) {						//삭제된 인자가 하나라도 있다면
			printf("%c", ptr->data);	//삭제된 인자가 가리키는 데이터 출력
			if (ptr->leftChild)			//삭제된 인자의 왼쪽 자식이 있다면
				addq(ptr->leftChild);	//왼쪽 자식을 큐에 삽입
			if (ptr->rightChild)		//삭제된 인자의 오른쪽 자식이 있다면
				addq(ptr->rightChild);	//오른쪽 자식을 큐에 삽입
		}
		else break;
	}
}
// Program 3.7: Add to a circular queue (p.118) 
void addq(treePointer* ptr) {
	/* add an item to the queue*/
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	if (front == rear)
		queueFull();				//큐의 메모리가 full일 때, 에러메세지 출력 후 종료
	queue[rear] = ptr;
}
//Program 3.8: Delete from a circular queue(p.119)
treePointer* deleteq(int* front, int rear) {
	// remove front element from the queue
	if (*front == rear)				//공백트리
		return NULL;
	*front = (*front + 1) % MAX_QUEUE_SIZE;
	return queue[(*front)];
}
void queueFull() {
	printf("\n<<Queue is full, cannot add element>>\n==========Program ends==========\n\n");
	exit(EXIT_FAILURE);
}
void iterPostorder(treePointer* node) {
	/* 후위 순회 */
	treePointer* stack[MAX_STACK_SIZE];					//값을 읽어들이며 저장될 스택
	treePointer* temp[MAX_STACK_SIZE];					//(값이 root가 아닐 때)stack보다 먼저 출력되는 것을 전제로 하는 스택 temp
	int ST_first = 0;									//temp스택보다 먼저 출력되어야할 스택의 인자만큼 값 증가되는 정수
	int top = -1;
	int tempTOP = -1;
	treePointer* print = NULL;
	treePointer* root = node;
	for (;;) {
		for (;node;node = node->leftChild) {			//왼쪽노드들을 stack에 쌓음
			if ((root!=temp[tempTOP]) && (tempTOP > -1))//temp스택에 (root가 아닌) 값이 남은상태로 stack에 값이 push되었다면
				ST_first++;								//temp보다 먼저 출력되어야할 인자가 스택에 삽입되었다는 뜻이므로 값 증가
			push(&top, node, stack);
		}
		node = pop(&top, stack);						//스택에서 가장 위의 인자를 pop
		if (ST_first && (tempTOP > -1))					//스택에서 먼저 출력되어야할 인자 하나를 pop했으므로 ST_first값 감소
			ST_first--;									
		if (!node) break;								//empty stack
		if (node->rightChild) {							//pop한 인자의 오른쪽자식이 있다면 인자를 temp스택에 삽입
			push(&tempTOP, node, temp);	
			node = node->rightChild;	
		}
		else {											//노드의 오른쪽자식이 없다면, 값 출력
			printf("%c", node->data);	
			while (ST_first) {							//temp스택에 값이 있는채로 stack이 쌓였다면, 쌓인 개수만큼 다음을 수행
				print=pop(&top, stack);					//stack에서 하나를 꺼내옴
				if ((node == (print->leftChild)) && (print->rightChild)) {	//꺼내온 노드의 왼쪽자식이 방금 출력한 노드이고, 꺼내온 노드의 오른쪽자식이 있을때 
					push(&top, print, stack);			//아직 오른쪽자식이 탐색되지 않았다는 뜻이므로 꺼내온 스택에 다시 넣어준다
					break;
				}
				else{									//그렇지 않다면(leaf노드이거나 오른쪽자식이었을 경우) temp보다 우선순위가 높은 스택의 인자 출력
					printf("%c", print->data);
					ST_first--;
				}
			}
			if ((ST_first == 0) && (tempTOP > -1)) {	//스택에서 출력되어야할 인자가 없고, temp스택에 남은 노드가 있다면 하나만을 출력함
				print = pop(&tempTOP, temp);
				printf("%c", print->data);						
				}
			node = NULL;
		}
	}
	for (;tempTOP > -1;){								//반복문 종료 후 temp스택에 남은 데이터 출력
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
	if ((*TOP) == -1) 				//공백 스택인지 확인
		return NULL;			//공백이라면 NULL반환	
	return STACK[(*TOP)--];		//공백이 아니라면 스택의 가장 위에 있는 요쇼 리턴
}
void stackFull() {
	printf("\n<<Stack is full, cannot add element>>\n==========Program ends==========\n\n");
	exit(EXIT_FAILURE);
}