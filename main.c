#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char key[3];
    char value[100];
    struct Item *next;
    int index;
} Item;

typedef struct {
    Item* head;
    Item* tail;
    int size;
} Table;

int RInput(char *str, int op) {
    char *str1 = str;
    bool f = 1;
    while (*str) {
        if (*str < '0' || *str >'9')
            f = 0;
        if (*str == '-')
            f = 1;
        str++;
    }
    if (f)
        return atoi(str1);
    else {
        if (op == 0) {
            printf("Wrong input, try again\n");
            printf("Enter option: ");
        }
        else {
            printf("Wrong input, try again\n");
            printf("Enter value: ");
        }
        return -1;
    }
}

Table * Create() {
    Table * m = malloc(sizeof(Table));
    m->head = m->tail= NULL;
    m->size = 0;
    return m;
}

void GiveIndex(Table* t) {
    Item* temp = (Item *) t->head;
    for (int i = 0; i < t->size; i++) {
        temp->index = i;
        temp = (Item *) temp->next;
    }
}

Item* GetElement(Table* t, int n) {
    Item* temp = (Item *) t->head;
    for (int i = 0; i < t->size; i++) {
        if (n == i)
            return temp;
        temp = (Item *) temp->next;
    }
}

void PushBack(Table* t, char* key, char* value) {
    Item* new = malloc(sizeof(Item));
    strcpy(new->key, key);
    strcpy(new->value, value);
    new->next = NULL;
    Item *tmp = (Item *) t->tail;
    t->tail = new;
    if (t->head == NULL)
        t->head = t->tail;
    else
        tmp->next = (struct Item *) t->tail;
    t->size++;
    GiveIndex(t);
}

void PrintTable(Table* t) {
    Item* temp = (Item *) t->head;
    printf("Key | Value\n");
    for (int i = 0; i < t->size; i++) {
        printf("%s   %s\n", temp->key, temp->value);
        temp = (Item *) temp->next;
    }
}


void ShellSort(Table* t) {
    int n = t->size;
    for (int interval = n / 2; interval > 0; interval /= 2) {
        for (int i = interval; i < n; i += 1) {
            char temp2[3];
            char temp3[100];
            strcpy(temp2, GetElement(t, i)->key);
            strcpy(temp3, GetElement(t, i)->value);
            int j;
            for (j = i; j >= interval && strcmp(GetElement(t, j)->key, GetElement(t, j - interval)->key) < 0; j -= interval) {
                strcpy(GetElement(t, j)->key, GetElement(t, j - interval)->key);
                strcpy(GetElement(t, j)->value, GetElement(t, j - interval)->value);
            }
            strcpy(GetElement(t, j)->key, temp2);
            strcpy(GetElement(t, j)->value, temp3);
        }
    }
}

char* Search(Table* t, char* key) {
    int n = t->size;
    int low, high, middle;
    low = 0;
    high = n - 1;
    while (low <= high)
    {
        middle = (low + high) / 2;
        if (strcmp(key, GetElement(t, middle)->key) < 0)
            high = middle - 1;
        else if (strcmp(key, GetElement(t, middle)->key) > 0)
            low = middle + 1;
        else
            return GetElement(t, middle)->value;
    }
    return "No such element";
}


int main() {
    Table *t = Create();
    int op;
    char op1[] = "";
    char key1[3];
    char value1[100];
    printf("1. Add new element\n2. Print the table\n3. Sort\n4. BinSearch\n5. Exit\n");
    while (1) {
        printf("Enter option:");
        do {
            scanf("%s", op1);
            op = RInput(op1, 0);
        } while (op == -1);
        switch (op) {
            case 1:
                printf("Enter key and value:\n");
                scanf("%s", key1);
                scanf("%s", value1);
                PushBack(t, key1, value1);
                break;
            case 2:
                PrintTable(t);
                break;
            case 3:
                ShellSort(t);
                break;
            case 4:
                printf("Enter key of searching element: ");
                scanf("%s", key1);
                printf("%s\n", Search(t, key1));
                break;
            case 5:
                return 0;
            default:
                printf("No such option");
        }
    }
}
