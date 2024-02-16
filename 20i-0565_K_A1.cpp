#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
#define DEFAULT_CORE_ID 0 

//Ashraf 

int desiredCoreId = DEFAULT_CORE_ID;

void setAffinity(pthread_t thread, int coreId) {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(coreId, &cpuset);

    int result = pthread_setaffinity_np(thread, sizeof(cpu_set_t), &cpuset);
    if (result != 0) {
        fprintf(stderr, "Error setting CPU affinity: %d\n", result);
    }
}

typedef struct Node {
    int data;
    struct Node* next;
} Node;

void printLinkedList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

Node* merge(Node* left, Node* right) {
    if (left == NULL) {
        return right;
    }
    if (right == NULL) {
        return left;
    }

    Node* result = NULL;

    if (left->data <= right->data) {
        result = left;
        result->next = merge(left->next, right);
    } else {
        result = right;
        result->next = merge(left, right->next);
    }

    return result;
}

Node* mergeSort(Node* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    Node* slow = head;
    Node* fast = head->next;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    Node* secondHalf = slow->next;
    slow->next = NULL;

    head = mergeSort(head);
    secondHalf = mergeSort(secondHalf);

    return merge(head, secondHalf);
}


void readRollNumbers(FILE* inputFile, int* Numbers, int num) {
    if (inputFile == NULL || Numbers == NULL) {
        fprintf(stderr, "Error: inputFile or Numbers pointer is NULL\n");
        return;
    }

    for (int i = 0; i < num; i++) {
        if (fscanf(inputFile, "%d", &Numbers[i]) != 1) {
            fprintf(stderr, "Error reading number from file\n");
            return;
        }
    }
}

void addRollNumbersToList(Node** head, int* Numbers, int num) {
    if (head == NULL || Numbers == NULL || num <= 0) {
        fprintf(stderr, "Error: Invalid input\n");
        return;
    }

    Node* current = *head;
    Node* newNode;

    if (*head == NULL) {
        *head = (Node*)malloc(sizeof(Node));
        (*head)->data = Numbers[0];
        (*head)->next = NULL;
        current = *head;
    }

    while (current->next != NULL) {
        current = current->next;
    }

    for (int i = 1; i < num; i++) {
        newNode = (Node*)malloc(sizeof(Node));
        newNode->data = Numbers[i];
        newNode->next = NULL;
        current->next = newNode;
        current = newNode;
    }
}

typedef struct {
    Node** head;    
    int start;      
    int end;        
} ThreadData;

void* addRollNumbersToListParallel(void* arg) {
    ThreadData* data = (ThreadData*)arg;

    *(data->head) = mergeSort(*(data->head));

    pthread_exit(NULL);
}

void* mergeSortParallel(void* arg) {
    ThreadData* data = (ThreadData*)arg;

    if (*(data->head) == NULL || (*(data->head))->next == NULL) {
        pthread_exit(NULL);
    }

    setAffinity(pthread_self(), desiredCoreId);
    
    Node* slow = *(data->head);
    Node* fast = (*(data->head))->next;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    Node* secondHalf = slow->next;
    slow->next = NULL;

    ThreadData secondHalfData;
    secondHalfData.head = &secondHalf;

    mergeSortParallel((void*)data);

    pthread_t tid;
    pthread_create(&tid, NULL, mergeSortParallel, (void*)&secondHalfData);

    pthread_join(tid, NULL);

    pthread_mutex_lock(&mutex); 
    *(data->head) = merge(*(data->head), secondHalf);
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    char* filename = argv[1];
    FILE* inputFile = fopen(filename, "r");
    if (inputFile == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return 1;
    }

    int num;
    if (fscanf(inputFile, "%d", &num) != 1 || num <= 0) {
        fprintf(stderr, "Error: Invalid number of elements in file\n");
        fclose(inputFile);
        return 1;
    }

    int* Numbers = (int*)malloc(num * sizeof(int));
    if (Numbers == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        fclose(inputFile);
        return 1;
    }
    readRollNumbers(inputFile, Numbers, num);
    fclose(inputFile);

    printf("Unsorted array:\n");
    for (int i = 0; i < num; i++) {
        printf("%d ", Numbers[i]);
    }
    printf("\n\n");

    Node* head = NULL;
    addRollNumbersToList(&head, Numbers, num);

    Node* sortedSerial = mergeSort(head);

    printf("Sorted serial list:\n");
    printLinkedList(sortedSerial);
    printf("\n");

    ThreadData mergeSortData;
    mergeSortData.head = &head;
    pthread_t tid;
    pthread_create(&tid, NULL, mergeSortParallel, (void*)&mergeSortData);
    pthread_join(tid, NULL);
    Node* sortedParallel = *mergeSortData.head;

    printf("Sorted parallel list:\n");
    printLinkedList(sortedParallel);
    printf("\n");


    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(Numbers);

    pthread_mutex_destroy(&mutex); // Destroy mutex
    return 0;
}
