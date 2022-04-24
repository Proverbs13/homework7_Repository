#include<stdio.h>
#include<stdlib.h>

typedef struct Node { //���Ḯ��Ʈ ����ü Node
	int key;
	struct Node* llink; //���ʳ�带 ����ų �ڱ���������ü ������ llink
	struct Node* rlink; //�����ʳ�带 ����ų �ڱ���������ü ������ rlink
} listNode; //��Ī listNode

typedef struct Head { //���Ḯ��Ʈ ����ü head
	struct Node* first; // Node�� ����ų ����ü
}headNode; //��Ī headNode

/* �Լ� ����Ʈ */
int initialize(headNode** h); // �������� , �����޸��Ҵ� , �ڼ��� ������ ���� ����
int freeList(headNode** h); //������ ���Ḯ��Ʈ ��� �����޸� ���� , �ڼ��� ������ ���� ����
//���������ͷ� �Ű������� �޵��� ����

int insertNode(headNode* h, int key);  //���Ḯ��Ʈ �� �Էµ� key���� ū �� �տ� ����߰�
int insertLast(headNode* h, int key);  //���Ḯ��Ʈ ������ ��ġ�� ����߰�
int insertFirst(headNode* h, int key); //���Ḯ��Ʈ ó����ġ ����߰�
int deleteNode(headNode* h, int key);  //�˻��� �����ִ� ��� ����
int deleteLast(headNode* h);  //���Ḯ��Ʈ ������ ��� ����
int deleteFirst(headNode* h); //���Ḯ��Ʈ ù ��� ����
int invertList(headNode* h);  // ���Ḯ��Ʈ �Ųٷ� ������
void printList(headNode* h);  // ���Ḯ��Ʈ ���

int main()
{
	printf("[----- [����] [2019038029] -----]\n");
	char command; //��� �Է¹��� command
	int key;      //����Ʈ�� ���� ���� key
	headNode* headnode=NULL; //head ����ü ������ headnode
	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");
		printf("Command = ");
		scanf(" %c", &command);

		switch(command) { //������� �Է¿� ���� ��� ����
		case 'z': case 'Z': 
			initialize(&headnode); //headnode��ü�� �ּҸ� ���� 
			// �Լ� ������ headnode�� ���� �����ϱ� ����
			// (headnode�� ����Ű�� ���� �޸� �����Ҵ��� ����)
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(&headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}
	}while(command != 'q' && command != 'Q');
	return 1;
}

// ����� �����޸��Ҵ�
int initialize(headNode** h) {	// headnode��ü�� �ּҰ� �޾ƿ�, �Լ����� *h=headnode �̴�
// ���������ʹ� �����ͺ����� �ּҰ��� ���� ������

	if(*h != NULL) // head��忡 ����ִ� ���� ������ �󸮽�Ʈ�� �ƴϹǷ� 
		freeList(h); // �Լ�ȣ���� �Ҵ�� �޸� ����

	*h = (headNode*)malloc(sizeof(headNode)); 
	// headnode�� ����Ű�� ������ headNode����ü ũ�� ��ŭ �����Ҵ� 
	(*h)->first = NULL;  // headnode�� first�� NULL ����Ŵ
	return 1; // �Լ����� 
}

//�����Ҵ� ����
int freeList(headNode** h){ // headnode��ü�� �ּҰ� �޾ƿ�, �Լ����� *h=headnode �̴�
	listNode* p = (*h)->first; //������ ��� ����ü������ 1 - �̵��ϴ� ����,���� ù���� ���
	listNode* prev = NULL;     //������ ��� ����ü������ 2 - ������ġ ���� ����
	//���Ḯ��Ʈ ������ ���� �޸� ����
	while(p != NULL) { //p��ü�� NULL�϶����� �ݺ�
		prev = p;      //prev�� p�� ����
		p = p->rlink;  //����Ű�� �������� �ٲ���
		free(prev);    //�����ص� prev��ġ �����޸� ����
	}
	free(*h); //����� �����޸� ����
	return 0; //�Լ�����
}

//����Ʈ ���
void printList(headNode* h) {
	int i = 0;   //�ε����� i 
	listNode* p; //����Ʈ�� �̵��ϸ� ����ҿ뵵�� ����Ʈ ������ p
	printf("\n---PRINT\n"); 
	if(h == NULL) { //����Ʈ�� ����ִ� ���� ������
		printf("Nothing to print....\n");
		return; //�Լ�����
	}
	p = h->first; //��尡 ����Ű�� ����Ʈ ù��� �ּ� �־���

	while(p != NULL) { //����Ʈ�� �������� ����ų �� ����
		printf("[ [%d]=%d ] ", i, p->key); //i�� ����Ʈ�� key�� ���
		p = p->rlink; //���� ����Ʈ�� �̵�
		i++;          //������ �ݺ����� �ѹ� �����ǰ� �ݺ��� �����
	}
	printf("  items = %d\n", i); //����Ʈ�� ��� ���� ���
}

//list �������� key�� ���� ��带 �߰�
int insertLast(headNode* h, int key) {
	//���� �߰��� ��� ������ �����Ҵ�
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;   //�Է��� �� ��忡 �־���
	node->rlink = NULL;//�ϴ� ����� ��ũ����
	node->llink = NULL;//NULL�� �ʱ�ȭ �ص�
	//ù ��� ������ ��
	if (h->first == NULL){
		h->first = node; //���� ��带 ����Ŵ 
		return 0; //�Լ�����
	}
	//�ƴ� �� = ����Ʈ ������ ��ġ���� ã�Ƽ� �߰��� ��� ���� 
	listNode* n = h->first; //�˻��� ����Ʈ ����ü �����ʹ� ��尡 ����Ű�°� ����Ŵ 
	while(n->rlink != NULL) { //n�� ���������� NULL�϶����� �ݺ�, n��ü�� ������ �����ġ�� ������
		n = n->rlink; //������� �̵�
	} 
	n->rlink = node; //�߰��� ������ �����ġ���� n�ڿ� node����
	node->llink = n; //node �� llink�� �߰��� ����������� n����Ŵ
	return 0; //�Լ�����
}

//list�� ������ ��� ����
int deleteLast(headNode* h) {
	if (h->first == NULL) {     //�� ����Ʈ�� ������ ���� ���� ��
		printf("list is empty\n"); //�ȳ��� ��� 
		return 0; //�Լ�����
	}
	listNode* searchN = h->first;  //�˻��� ����Ʈ ����ü ������
	
	//����Ʈ ��尡 �ϳ��ۿ� ���� ��(����� ����)
	if (searchN->rlink== NULL){ 
		h->first = NULL;       //��� ���� NULL ����Ŵ
		free(searchN);		   //searchN�� ����Ű�� ��ġ�� ������ ������ ��� ����� ���� �޸� ����
		return 0;
	}
	// �ƴҶ�
	while(searchN->rlink!= NULL) { //searchN�� ���� ���� = NULL �϶����� �ݺ�,searchN�� ������ ����϶� ����
		searchN = searchN->rlink; //searchN�� �������� �Ѿ
	} 
	searchN->llink->rlink=NULL; //searchN �� ��������� rrlink�� NULL ����Ŵ
	free(searchN);     //�̵��� ������ ��� �� searchN�� ����Ű�� ��ġ ���� �޸� ����
	return 0; //�Լ�����
}

//list ó���� key�� ���� ����ϳ��� �߰�
int insertFirst(headNode* h, int key) {
	//���� �߰��� ��� ������ �����Ҵ�
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key; //�Է��� �� ��忡 �־���
	node->llink=NULL; //�ϴ� ����� ��ũ����
	node->rlink=NULL; //NULL�� �ʱ�ȭ �ص�

	if(h->first == NULL){//���Ḯ��Ʈ�� ���� ����ִ� ���¶��
		h->first = node; //������ ��带 ī��Ű��
		return 0; //�Լ�����
	} // ������� ������ =>
	node->rlink = h->first; // ���rlink�� ��尡 ����Ű���� ����Ŵ
	//node -> llink�� �̹� NULL�� ����Ű������

	//�� ��� �߰����� ����尡 ����Ű�� ����� llink�� node�� ������� ��
	listNode* beforeN = h->first; //beforeN �� ��尡 ���� ����Ű�� ���
	beforeN->llink = node; 
	h->first =node; //���� ��带 ����Ŵ
	return 0; //�Լ�����
}

//list�� ù��° ��� ����
int deleteFirst(headNode* h) {
	if (h->first == NULL) {   //�� ����Ʈ�� ������ ���� ���� ��
		printf("list is empty\n"); //�ȳ��� ��� 
		return 0; //�Լ�����
	}
	listNode* p = h->first; //�����޸� ������ ���� ����ü ������ p
	h->first = h->first->rlink; //ù���� ��尡 ����Ű�� ���� ����尡 ����Ű������
	h->first->llink=NULL; // ������ ù��° ����� llink�� NULL �־���
	free(p);  // p�� ����Ű�� ��ġ�� ������ ������ ��� ����� ���� �޸� ����
	return 0; // �Լ�����
}

//����Ʈ�� ��ũ�� �������� �� ��ġ
int invertList(headNode* h) {
	if (h->first == NULL) {      //�� ����Ʈ�� �������� �ٲ� ���� ���� ��
		printf("list is empty\n"); //�ȳ��� ��� 
		return 0; //�Լ�����
	}
	//����ü ������ 3�� ����� ����Ʈ ������
	listNode *lead  = h->first; //���� �̵��ϴ� ����ü ������ 
	listNode *middle = NULL; 
	listNode *trail = NULL;
	while(lead!=NULL){ //lead �����ü�� = NULL �϶����� �ݺ� 
		trail=middle;    //trail �� middle�� �̵� -> ù�������� �ǹ̾���
		middle=lead;     //middle�� lead�� �̵�
		lead=lead->rlink; //lead�� �������� �̵��ϰ�
		middle->rlink=trail;  //middle�� rlink�� trail�� ����Ŵ,ù�������� middle�� NULL����Ű�Ե�
		middle->llink=lead;   //middle�� llink�� lead�� ����Ŵ
		//�������� lead�� NULL�� �Ǹ鼭 �Ųٷ� ������ ���Ḯ��Ʈ�� llink�� NULL ����Ŵ 
	}
	//�Ųٷ� NULL�� ���� ������ ����Ʈ�� ��� ��� ����
	h->first=middle;
	return 0; //�Լ�����
}

//����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ����
int insertNode(headNode* h, int key) {
	//���� �߰��� ��� ������ �����Ҵ�
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key; //�Է��� �� ��忡 �־���
	node->llink=NULL; //�ϴ� ����� ��ũ����
	node->rlink=NULL; //NULL�� �ʱ�ȭ �ص�

	//ù ��� �����϶�
	if (h->first==NULL){
		h->first=node; //����尡 ��带 ����Ű���ϰ�
		return 0;      //�Լ�����
	}

	//�߰��� ����� ���� �����ִ� ������ ������ �۰ų� ������
	listNode* searchN = h->first;  //�˻��� ����Ʈ ����ü ������

	//searchN�� �������� �Ѿ�鼭 searchN ������ ������(NULL)�϶����� �ݺ�
	while (searchN!=NULL){        
		if(key <=searchN->key){    // �ִ°��� �����ִ� ����Ʈ ������ ���� �� ������
			if(h->first==searchN){ // ����Ʈ ù��尪���� �ִ°��� ������ = h->first = node�� �Ǿ��� ��
				h->first = node;      //����� ��,
				node->rlink = searchN;//ã�� ��� ������ node ����
				searchN->llink=node;  //ã�� ����� llink�� node�� ���� 
			}
			else{ //��������ġ�� �ƴ����� ���� ����Ʈ ������ �����ٴ� ���� ���
				node->rlink = searchN; //��� rlink�� �߰��� ã�� ����� ������ ����
				node->llink = searchN->llink;  //��� llink�� ã�� ����� ������
				searchN->llink->rlink = node;  //ã�� ����� ����� �������� node���� 
				searchN->llink = node; // ã������� llink �� node�� ����
			}
			return 0; // �Լ�����
		}
		searchN=searchN->rlink;	//searchN�� �������� �Ѿ
	}
	//�߰��� ����� ���� �����ִ� ��� ������ ������ Ŭ �� �������� �־���
	insertLast(h, key); //�������� ��� �ִ� �Լ� ȣ��
	return 0; // �Լ�����
}

//list���� key�� ���� ��� ����
int deleteNode(headNode* h, int key) {
	if (h->first == NULL) {      //�� ����Ʈ�� ������ ���� ���� ��
		printf("list is empty"); //�ȳ��� ��� 
		return 0; //�Լ�����
	}
	listNode* searchN = h->first;  //�˻��� ����Ʈ ����ü ������
	
	while(searchN!= NULL) { //�Ѿ �����ü = NULL �϶����� �ݺ�-��������嵵 �˻��ؾߵ�
		if (key==searchN->key){  //�Է��� Ű���� ã�� ����� Ű���� ���
			//����Ʈ�� ù��° ��带 ������ ���
			if (searchN==h->first){ 
				h->first=searchN->rlink; //������ ������ ��尡 ����Ű������ ����Ŵ
				searchN->rlink->llink = NULL; //������ ��� ��������� llink�� NULL����Ŵ
				free(searchN); //searchN�� ����Ű�� ��ġ�� ������ ������ ��� ����� ���� �޸� ����
			}
			// ����Ʈ ������ ��带 ������ ���
			else if(searchN->rlink==NULL){
				searchN->llink->rlink=NULL; //������ ����� �������� ������ ��尡 ����Ű������ ����Ŵ
				free(searchN); //searchN�� ����Ű�� ��ġ�� ������ ������ ��� ����� ���� �޸� ����
			}
			else{ //����Ʈ�� �߰���� ������ ���
				searchN->rlink->llink=searchN->llink; // ������ ��� ��������� llink�� �����ҳ���� llink ����Ŵ
				searchN->llink->rlink=searchN->rlink; // ������ ��� ��������� rlink�� �����ҳ���� rlink ����Ŵ
				free(searchN); //searchN�� ����Ű�� ��ġ�� ������ ������ ��� ����� ���� �޸� ����
			}
			return 0;
		}
		searchN = searchN->rlink;  //searchN�� �������� �Ѿ
	} 
	// ã�� key���� ���� ��尡 ������ 
	printf("Your key is not in the list\n"); //�ȳ��� ���
	return 0; //�Լ�����
}