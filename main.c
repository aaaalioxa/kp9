#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "table.h"

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
    return NULL;
}

void PushBack(Table* t, int num, char let, char* value) {
    Item* new = malloc(sizeof(Item));
    strcpy(new->value, value);
    new->key.letter = let;
    new->key.number = num;
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
        printf("----|-----------------------------\n");
        printf("%d %c | %s\n", temp->key.number, temp->key.letter, temp->value);
        temp = (Item *) temp->next;
    }
}

void ShellSort(Table *t)
{
    int n = t->size;
    int i, j, k;
    char tmpVal[100];
    int tmpNum;
    char tmpLet;
    for (i = n / 2; i > 0; i = i / 2)
    {
        for (j = i; j < n; j++)
        {
            for(k = j - i; k >= 0; k = k - i)
            {
                if ((GetElement(t, k + i)->key.number > GetElement(t, k)->key.number) || ((GetElement(t, k + i)->key.number == GetElement(t, k)->key.number) && ((GetElement(t, k + i)->key.letter > GetElement(t, k)->key.letter))))
                    break;
                else
                {
                    strcpy(tmpVal, GetElement(t, k)->value);
                    tmpNum = GetElement(t, k)->key.number;
                    tmpLet = GetElement(t, k)->key.letter;
                    strcpy(GetElement(t, k)->value, GetElement(t, k + i)->value);
                    GetElement(t, k)->key.number = GetElement(t, k + i)->key.number;
                    GetElement(t, k)->key.letter = GetElement(t, k + i)->key.letter;
                    strcpy(GetElement(t, k + i)->value, tmpVal);
                    GetElement(t, k + i)->key.number = tmpNum;
                    GetElement(t, k + i)->key.letter = tmpLet;
                }
            }
        }
    }
}

char* Search(Table* t, int num, char let) {
    int n = t->size;
    int low, high, middle;
    low = 0;
    high = n - 1;
    char key[2];
    char tempKey[2];
    key[0] = (char)num;
    key[1] = let;
    while (low <= high)
    {
        middle = (low + high) / 2;
        tempKey[0] = (char)GetElement(t, middle)->key.number;
        tempKey[1] = GetElement(t, middle)->key.letter;
        if ((num < GetElement(t, middle)->key.number) || ((num == GetElement(t, middle)->key.number) && (let < GetElement(t, middle)->key.letter)))
            high = middle - 1;
        else if (num > GetElement(t, middle)->key.number)
            low = middle + 1;
        else if ((num == GetElement(t, middle)->key.number) && (let > GetElement(t, middle)->key.letter)) {
            low = middle + 1;
        }
        else if ((num == GetElement(t, middle)->key.number) && (let == GetElement(t, middle)->key.letter))
            return GetElement(t, middle)->value;
    }
    return "No such element";
}


int main() {
    Table *t = Create();
    FILE *in = fopen("input.txt", "r");
    int op;
    char op1[] = "";
    char letter = ' ', letter1;
    int num, num1;
    char value1[100];
    int i = 0;
    printf("1. Print the table\n2. Sort\n3. BinSearch\n4. Exit\n");
    while (!feof(in)) {
        fscanf(in,"%d", &num);
        fseek(in, 1, SEEK_CUR);
        fscanf(in ,"%c", &letter);
        fseek(in, 1, SEEK_CUR);
        fscanf(in, "%c", &value1[i]);
        while (value1[i] != '\n' && !feof(in)) {
            i++;
            fscanf(in, "%c", &value1[i]);
        }
        value1[i] = '\0';
        i = 0;
        PushBack(t, num, letter, value1);
        if (feof(in))
            break;
        memset(value1,'\0',100);
    }
    while (1) {
        printf("Enter option:");
        do {
            scanf("%s", op1);
            op = RInput(op1, 0);
        } while (op == -1);
        switch (op) {
            case 1:
                PrintTable(t);
                break;
            case 2:
                ShellSort(t);
                break;
            case 3:
                printf("Enter key of searching element: ");
                scanf("%d", &num1);
                scanf("%s", &letter1);
                printf("%s\n", Search(t, num1, letter1));
                break;
            case 4:
                return 0;
            default:
                printf("No such option");
        }
    }
}
