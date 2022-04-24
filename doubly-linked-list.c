#include<stdio.h>
#include<stdlib.h>

typedef struct Node { //연결리스트 구조체 Node
	int key;
	struct Node* llink; //왼쪽노드를 가리킬 자기참조구조체 포인터 llink
	struct Node* rlink; //오른쪽노드를 가리킬 자기참조구조체 포인터 rlink
} listNode; //별칭 listNode

typedef struct Head { //연결리스트 구조체 head
	struct Node* first; // Node를 가리킬 구조체
}headNode; //별칭 headNode

/* 함수 리스트 */
int initialize(headNode** h); // 헤드노드생성 , 동적메모리할당 , 자세한 설명은 보고서 참조
int freeList(headNode** h); //헤드노드및 연결리스트 노드 동적메모리 해제 , 자세한 설명은 보고서 참조
//이중포인터로 매개변수를 받도록 만들어봄

int insertNode(headNode* h, int key);  //연결리스트 내 입력된 key보다 큰 값 앞에 노드추가
int insertLast(headNode* h, int key);  //연결리스트 마지막 위치에 노드추가
int insertFirst(headNode* h, int key); //연결리스트 처음위치 노드추가
int deleteNode(headNode* h, int key);  //검색한 값이있는 노드 삭제
int deleteLast(headNode* h);  //연결리스트 마지막 노드 삭제
int deleteFirst(headNode* h); //연결리스트 첫 노드 삭제
int invertList(headNode* h);  // 연결리스트 거꾸로 뒤집기
void printList(headNode* h);  // 연결리스트 출력

int main()
{
	printf("[----- [이찬] [2019038029] -----]\n");
	char command; //명령 입력받을 command
	int key;      //리스트에 넣을 내용 key
	headNode* headnode=NULL; //head 구조체 포인터 headnode
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

		switch(command) { //사용자의 입력에 따른 명령 실행
		case 'z': case 'Z': 
			initialize(&headnode); //headnode자체의 주소를 보냄 
			// 함수 내에서 headnode를 직접 조작하기 위해
			// (headnode가 가리키는 곳의 메모리 동적할당을 위해)
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

// 헤드노드 동적메모리할당
int initialize(headNode** h) {	// headnode자체의 주소값 받아옴, 함수에서 *h=headnode 이다
// 이중포인터는 포인터변수의 주소값을 갖는 포인터

	if(*h != NULL) // head노드에 들어있는 값이 있으면 빈리스트가 아니므로 
		freeList(h); // 함수호출해 할당된 메모리 해제

	*h = (headNode*)malloc(sizeof(headNode)); 
	// headnode가 가리키는 공간에 headNode구조체 크기 만큼 동적할당 
	(*h)->first = NULL;  // headnode의 first는 NULL 가리킴
	return 1; // 함수종료 
}

//동적할당 해제
int freeList(headNode** h){ // headnode자체의 주소값 받아옴, 함수에서 *h=headnode 이다
	listNode* p = (*h)->first; //해제용 노드 구조체포인터 1 - 이동하는 역할,현재 첫번쨰 노드
	listNode* prev = NULL;     //해제용 노드 구조체포인터 2 - 현재위치 해제 역할
	//연결리스트 노드들의 동적 메모리 해제
	while(p != NULL) { //p자체가 NULL일때까지 반복
		prev = p;      //prev에 p값 저장
		p = p->rlink;  //가리키는 다음노드로 바꿔줌
		free(prev);    //저장해둔 prev위치 동적메모리 해제
	}
	free(*h); //헤드노드 동적메모리 해제
	return 0; //함수종료
}

//리스트 출력
void printList(headNode* h) {
	int i = 0;   //인덱스용 i 
	listNode* p; //리스트를 이동하며 출력할용도의 리스트 포인터 p
	printf("\n---PRINT\n"); 
	if(h == NULL) { //리스트에 들어있는 것이 없으면
		printf("Nothing to print....\n");
		return; //함수종료
	}
	p = h->first; //헤드가 가리키는 리스트 첫노드 주소 넣어줌

	while(p != NULL) { //리스트가 마지막을 가리킬 때 까지
		printf("[ [%d]=%d ] ", i, p->key); //i번 리스트에 key값 출력
		p = p->rlink; //다음 리스트로 이동
		i++;          //마지막 반복에서 한번 증가되고 반복문 종료됨
	}
	printf("  items = %d\n", i); //리스트의 노드 개수 출력
}

//list 마지막에 key에 대한 노드를 추가
int insertLast(headNode* h, int key) {
	//내용 추가할 노드 생성후 동적할당
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;   //입력한 값 노드에 넣어줌
	node->rlink = NULL;//일단 노드의 링크들을
	node->llink = NULL;//NULL로 초기화 해둠
	//첫 노드 생성일 떄
	if (h->first == NULL){
		h->first = node; //헤드는 노드를 가리킴 
		return 0; //함수종료
	}
	//아닐 때 = 리스트 마지막 위치까지 찾아서 추가할 노드 연결 
	listNode* n = h->first; //검색용 리스트 구조체 포인터는 헤드가 가리키는것 가리킴 
	while(n->rlink != NULL) { //n의 다음연결이 NULL일때까지 반복, n자체가 마지막 노드위치일 때까지
		n = n->rlink; //다음노드 이동
	} 
	n->rlink = node; //추가전 마지막 노드위치였던 n뒤에 node연결
	node->llink = n; //node 의 llink는 추가전 마지막노드인 n가리킴
	return 0; //함수종료
}

//list의 마지막 노드 삭제
int deleteLast(headNode* h) {
	if (h->first == NULL) {     //빈 리스트라 삭제할 것이 없을 시
		printf("list is empty\n"); //안내문 출력 
		return 0; //함수종료
	}
	listNode* searchN = h->first;  //검색용 리스트 구조체 포인터
	
	//리스트 노드가 하나밖에 없을 때(헤드노드 제외)
	if (searchN->rlink== NULL){ 
		h->first = NULL;       //헤드 노드는 NULL 가리킴
		free(searchN);		   //searchN이 가리키는 위치의 연결이 끊어진 대상 노드의 동적 메모리 해제
		return 0;
	}
	// 아닐때
	while(searchN->rlink!= NULL) { //searchN의 다음 연결 = NULL 일때까지 반복,searchN이 마지막 노드일때 까지
		searchN = searchN->rlink; //searchN은 다음으로 넘어감
	} 
	searchN->llink->rlink=NULL; //searchN 의 이전노드의 rrlink는 NULL 가리킴
	free(searchN);     //이동한 마지막 노드 즉 searchN이 가리키는 위치 동적 메모리 해제
	return 0; //함수종료
}

//list 처음에 key에 대한 노드하나를 추가
int insertFirst(headNode* h, int key) {
	//내용 추가할 노드 생성후 동적할당
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key; //입력한 값 노드에 넣어줌
	node->llink=NULL; //일단 노드의 링크들을
	node->rlink=NULL; //NULL로 초기화 해둠

	if(h->first == NULL){//연결리스트가 현재 비어있는 상태라면
		h->first = node; //헤드노드는 노드를 카리키고
		return 0; //함수종료
	} // 비어있지 않으면 =>
	node->rlink = h->first; // 노드rlink는 헤드가 가리키던것 가리킴
	//node -> llink는 이미 NULL을 가리키고있음

	//새 노드 추가전에 헤드노드가 가리키던 노드의 llink를 node로 보내줘야 함
	listNode* beforeN = h->first; //beforeN 은 헤드가 원래 가리키던 노드
	beforeN->llink = node; 
	h->first =node; //헤드는 노드를 가리킴
	return 0; //함수종료
}

//list의 첫번째 노드 삭제
int deleteFirst(headNode* h) {
	if (h->first == NULL) {   //빈 리스트라 삭제할 것이 없을 시
		printf("list is empty\n"); //안내문 출력 
		return 0; //함수종료
	}
	listNode* p = h->first; //동적메모리 해제를 위한 구조체 포인터 p
	h->first = h->first->rlink; //첫번쨰 노드가 가리키던 것을 헤드노드가 가리키도록함
	h->first->llink=NULL; // 삭제후 첫번째 노드의 llink에 NULL 넣어줌
	free(p);  // p가 가리키는 위치의 연결이 끊어진 대상 노드의 동적 메모리 해제
	return 0; // 함수종료
}

//리스트의 링크를 역순으로 재 배치
int invertList(headNode* h) {
	if (h->first == NULL) {      //빈 리스트라 역순으로 바꿀 것이 없을 시
		printf("list is empty\n"); //안내문 출력 
		return 0; //함수종료
	}
	//구조체 포인터 3개 사용해 리스트 뒤집기
	listNode *lead  = h->first; //먼저 이동하는 구조체 포인터 
	listNode *middle = NULL; 
	listNode *trail = NULL;
	while(lead!=NULL){ //lead 노드자체가 = NULL 일때까지 반복 
		trail=middle;    //trail 이 middle로 이동 -> 첫루프에선 의미없음
		middle=lead;     //middle이 lead로 이동
		lead=lead->rlink; //lead는 다음으로 이동하고
		middle->rlink=trail;  //middle의 rlink는 trail을 가리킴,첫루프에서 middle은 NULL가리키게됨
		middle->llink=lead;   //middle의 llink는 lead을 가리킴
		//마지막에 lead가 NULL이 되면서 거꾸로 뒤집은 연결리스트의 llink은 NULL 가리킴 
	}
	//거꾸로 NULL을 향해 뒤집은 리스트에 헤드 노드 연결
	h->first=middle;
	return 0; //함수종료
}

//리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입
int insertNode(headNode* h, int key) {
	//내용 추가할 노드 생성후 동적할당
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key; //입력한 값 노드에 넣어줌
	node->llink=NULL; //일단 노드의 링크들을
	node->rlink=NULL; //NULL로 초기화 해둠

	//첫 노드 생성일때
	if (h->first==NULL){
		h->first=node; //헤드노드가 노드를 가리키게하고
		return 0;      //함수종료
	}

	//추가할 노드의 값이 원래있던 노드들의 값보다 작거나 같을때
	listNode* searchN = h->first;  //검색용 리스트 구조체 포인터

	//searchN가 다음으로 넘어가면서 searchN 자제가 마지막(NULL)일때까지 반복
	while (searchN!=NULL){        
		if(key <=searchN->key){    // 넣는값이 원래있던 리스트 값보다 작을 때 노드삽입
			if(h->first==searchN){ // 리스트 첫노드값보다 넣는값이 작을때 = h->first = node가 되야할 때
				h->first = node;      //헤드노드 뒤,
				node->rlink = searchN;//찾은 노드 앞으로 node 연결
				searchN->llink=node;  //찾은 노드의 llink를 node로 연결 
			}
			else{ //헤드다음위치는 아니지만 원래 리스트 노드들의 값보다는 작을 경우
				node->rlink = searchN; //노드 rlink는 추가전 찾은 노드의 앞으로 연결
				node->llink = searchN->llink;  //노드 llink는 찾은 노드의 앞으로
				searchN->llink->rlink = node;  //찾은 노드의 전노드 다음으로 node연결 
				searchN->llink = node; // 찾은노드의 llink 는 node로 연결
			}
			return 0; // 함수종료
		}
		searchN=searchN->rlink;	//searchN은 다음으로 넘어감
	}
	//추가할 노드의 값이 원래있던 모든 노드들의 값보다 클 때 마지막에 넣어줌
	insertLast(h, key); //마지막에 노드 넣는 함수 호출
	return 0; // 함수종료
}

//list에서 key에 대한 노드 삭제
int deleteNode(headNode* h, int key) {
	if (h->first == NULL) {      //빈 리스트라 삭제할 것이 없을 시
		printf("list is empty"); //안내문 출력 
		return 0; //함수종료
	}
	listNode* searchN = h->first;  //검색용 리스트 구조체 포인터
	
	while(searchN!= NULL) { //넘어간 노드자체 = NULL 일때까지 반복-마지막노드도 검사해야됨
		if (key==searchN->key){  //입력한 키값이 찾은 노드의 키값인 경우
			//리스트의 첫번째 노드를 삭제할 경우
			if (searchN==h->first){ 
				h->first=searchN->rlink; //헤드노드는 삭제할 노드가 가리키던것을 가리킴
				searchN->rlink->llink = NULL; //삭제할 노드 다음노드의 llink는 NULL가리킴
				free(searchN); //searchN이 가리키는 위치의 연결이 끊어진 대상 노드의 동적 메모리 해제
			}
			// 리스트 마지막 노드를 삭제할 경우
			else if(searchN->rlink==NULL){
				searchN->llink->rlink=NULL; //삭제할 노드의 이전노드는 삭제할 노드가 가리키던것을 가리킴
				free(searchN); //searchN이 가리키는 위치의 연결이 끊어진 대상 노드의 동적 메모리 해제
			}
			else{ //리스트의 중간노드 삭제할 경우
				searchN->rlink->llink=searchN->llink; // 삭제할 노드 다음노드의 llink는 삭제할노드의 llink 가리킴
				searchN->llink->rlink=searchN->rlink; // 삭제할 노드 이전노드의 rlink는 삭제할노드의 rlink 가리킴
				free(searchN); //searchN이 가리키는 위치의 연결이 끊어진 대상 노드의 동적 메모리 해제
			}
			return 0;
		}
		searchN = searchN->rlink;  //searchN은 다음으로 넘어감
	} 
	// 찾는 key값을 가진 노드가 없을때 
	printf("Your key is not in the list\n"); //안내문 출력
	return 0; //함수종료
}