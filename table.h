
#ifndef KP99_TABLE_H
#define KP99_TABLE_H

typedef struct Key{
    int number;
    char letter;
} Key;

typedef struct {
    Key key;
    char value[100];
    struct Item *next;
    int index;
} Item;

typedef struct {
    Item* head;
    Item* tail;
    int size;
} Table;

#endif //KP99_TABLE_H
