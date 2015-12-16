#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct house house;
struct house {
    int x;
    int y;
    int count; // how many times visited
    house* next;
};

void house_free(house*);
int house_add(house*);
bool house_find(int, int);

int main()
{
    char c; // character read from stdin
    house h = {0, 0, 0, NULL}; // fisrt house

    printf("%d%d%d\n", h.x, h.y, h.count);

    do {
        c = fgetc(stdin);
        putchar(c);
    } while (c != EOF);

    return 0;
}

void house_free(house *first)
{
    house *curr, *head = first;
    while ((curr = head) != NULL) {
        head = head->next;
        free(curr);
    }
}

int house_add(house *first)
{
    int count = 0;
    bool found = house_find(first->x, first->y);

    if (found) {
        // return early if house already visited
        return count;
    } else {
        // allocate memory
        // add first house to this one's next
        // set first pointer to this one
        return 0;
    }
}

bool house_find(int x, int y)
{
    // return true if x and y match an existing house
    // possibly this doesn't need its own function
    // possibly should return the matched house's pointer
    return true;
}
