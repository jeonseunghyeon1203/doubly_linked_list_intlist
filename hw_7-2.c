#include <stdio.h>
#include <stdlib.h>
// 노드 정의
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

// 전역 변수: 리스트의 시작과 끝
Node* head = NULL;
Node* tail = NULL;

// 새로운 노드를 생성하는 함수
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("메모리 할당 오류\n");
        exit(1);
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// 리스트에 정수를 삽입하는 함수
void insert(int data) {
    // 삽입할 노드 생성
    Node* newNode = createNode(data);

    // 리스트가 비어있는 경우
    if (head == NULL) {
        head = tail = newNode;
    } else {
        // 삽입할 위치 찾기
        Node* current = head;
        while (current != NULL) {  //정렬할때 까지 반복
            if (current->data == data) {
                // 동일한 데이터가 이미 존재하면 삽입하지 않음
                free(newNode);
                return;
            }
            if (current->data > data) { //넣을려는 데이터가 더 작다면
                break;
            }
            current = current->next;  //넣을려는 데이터가 더 크다면 current의 다음으로 넘김
        }

        // 헤드에 삽입해야 하는 경우 //넣을려는 데이터가 제일 작다면
        if (current == head) {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        } else if (current == NULL) {   //넣을려는 데이터가 제일 크다면
            // 테일에 삽입해야 하는 경우
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        } else { // -><- newnode -><- current
            // 중간에 삽입해야 하는 경우
            newNode->prev = current->prev;
            newNode->next = current;
            current->prev->next = newNode;
            current->prev = newNode;
        }
    }
}

// 리스트에서 정수를 삭제하는 함수
void delete(int data) {
    // 삭제할 노드 찾기
    Node* current = head;
    while (current != NULL) { //current는 head부터 시작해 data와 numd이 일치하는 순간까지
        if (current->data == data) {
            break;
        }
        current = current->next;
    }

    // 삭제할 노드가 없는 경우
    if (current == NULL) {
        printf("%d는 리스트에 없습니다.\n", data);
        return;
    }

    // 삭제할 노드가 헤드인 경우
    if (current == head) {
        head = head->next;
        if (head != NULL) {  //head의 다음값이 있다면
            head->prev = NULL;  //head 다음값의 prev는 null
        }
    } else {  //헤드가 아니라면
        current->prev->next = current->next; //current의 prev의 next는 curent의 next로
        if (current != tail) {  //current가 테일이 아니라면
            current->next->prev = current->prev;
        } else {   //current가 테일이라면
            tail = current->prev;
        }
    }

    free(current);
}

int main() {
    int choice, num;

    // 메뉴 출력 및 선택
    while(1){
        printf("(메뉴) 1. 정수입력 2. 정수삭제 3. 종료: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("정수? ");
                scanf("%d", &num);
                insert(num);
                printf("리스트: ( ");
                // 리스트 출력
                for (Node* current = head; current != NULL; current = current->next) {
                    printf("%d ", current->data);
                }
                printf(")\n");
                break;
            case 2:
                printf("정수? ");
                scanf("%d", &num);
                delete(num);
                printf("리스트: (");  //리스트 출력 current는 헤드부터 시작
                for (Node* current = head; current != NULL; current = current->next) {
                    printf("%d ", current->data);
                }
                printf(")\n");
                break;
            case 3:
                printf("리스트 역순:(");   //리스트 역순 current는 테일부터시작
                for(Node* current = tail;current !=NULL;current=current->prev) {
                        printf("%d ", current->data);
                }
                printf(")\n");
                return 0;
            default:
                printf("잘못된 선택입니다.\n");
        }
    }
    return 0;
}
