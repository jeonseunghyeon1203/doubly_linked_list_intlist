#include <stdio.h>
#include <stdlib.h>
// ��� ����
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

// ���� ����: ����Ʈ�� ���۰� ��
Node* head = NULL;
Node* tail = NULL;

// ���ο� ��带 �����ϴ� �Լ�
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("�޸� �Ҵ� ����\n");
        exit(1);
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// ����Ʈ�� ������ �����ϴ� �Լ�
void insert(int data) {
    // ������ ��� ����
    Node* newNode = createNode(data);

    // ����Ʈ�� ����ִ� ���
    if (head == NULL) {
        head = tail = newNode;
    } else {
        // ������ ��ġ ã��
        Node* current = head;
        while (current != NULL) {  //�����Ҷ� ���� �ݺ�
            if (current->data == data) {
                // ������ �����Ͱ� �̹� �����ϸ� �������� ����
                free(newNode);
                return;
            }
            if (current->data > data) { //�������� �����Ͱ� �� �۴ٸ�
                break;
            }
            current = current->next;  //�������� �����Ͱ� �� ũ�ٸ� current�� �������� �ѱ�
        }

        // ��忡 �����ؾ� �ϴ� ��� //�������� �����Ͱ� ���� �۴ٸ�
        if (current == head) {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        } else if (current == NULL) {   //�������� �����Ͱ� ���� ũ�ٸ�
            // ���Ͽ� �����ؾ� �ϴ� ���
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        } else { // -><- newnode -><- current
            // �߰��� �����ؾ� �ϴ� ���
            newNode->prev = current->prev;
            newNode->next = current;
            current->prev->next = newNode;
            current->prev = newNode;
        }
    }
}

// ����Ʈ���� ������ �����ϴ� �Լ�
void delete(int data) {
    // ������ ��� ã��
    Node* current = head;
    while (current != NULL) { //current�� head���� ������ data�� numd�� ��ġ�ϴ� ��������
        if (current->data == data) {
            break;
        }
        current = current->next;
    }

    // ������ ��尡 ���� ���
    if (current == NULL) {
        printf("%d�� ����Ʈ�� �����ϴ�.\n", data);
        return;
    }

    // ������ ��尡 ����� ���
    if (current == head) {
        head = head->next;
        if (head != NULL) {  //head�� �������� �ִٸ�
            head->prev = NULL;  //head �������� prev�� null
        }
    } else {  //��尡 �ƴ϶��
        current->prev->next = current->next; //current�� prev�� next�� curent�� next��
        if (current != tail) {  //current�� ������ �ƴ϶��
            current->next->prev = current->prev;
        } else {   //current�� �����̶��
            tail = current->prev;
        }
    }

    free(current);
}

int main() {
    int choice, num;

    // �޴� ��� �� ����
    while(1){
        printf("(�޴�) 1. �����Է� 2. �������� 3. ����: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("����? ");
                scanf("%d", &num);
                insert(num);
                printf("����Ʈ: ( ");
                // ����Ʈ ���
                for (Node* current = head; current != NULL; current = current->next) {
                    printf("%d ", current->data);
                }
                printf(")\n");
                break;
            case 2:
                printf("����? ");
                scanf("%d", &num);
                delete(num);
                printf("����Ʈ: (");  //����Ʈ ��� current�� ������ ����
                for (Node* current = head; current != NULL; current = current->next) {
                    printf("%d ", current->data);
                }
                printf(")\n");
                break;
            case 3:
                printf("����Ʈ ����:(");   //����Ʈ ���� current�� ���Ϻ��ͽ���
                for(Node* current = tail;current !=NULL;current=current->prev) {
                        printf("%d ", current->data);
                }
                printf(")\n");
                return 0;
            default:
                printf("�߸��� �����Դϴ�.\n");
        }
    }
    return 0;
}
