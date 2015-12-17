#include <stdio.h>
#include <stdlib.h>

typedef struct house house;
struct house {
    int x;
    int y;
    int count; // how many times visited
    house* next;
};

void move(char, int*);
void house_free(house*);
int house_add(house**, int, int);
house* house_find(house*, int, int);

int main()
{
    char c; // character read from stdin
    house first = {0, 0, 1, NULL}; // first house
    house* h = &first;
    int m[2]; // movement coords
    int count; // how many times I've visited this house

    printf("%d%d%d\n", h->x, h->y, h->count);

    while ((c = fgetc(stdin)) != EOF) {
        move(c, m);
        if (m[0] + m[1] == 0) // {0, 0} Wait
            continue;
        count = house_add(&h, (h->x + m[0]), (h->y + m[1]));
        printf("%c %d:%d #%d\n", c, m[0], m[1], count);
    }

    // not using heap, not needed
    /* house_free(&h); */

    return 0;
}

/**
 * Maps arrow directions to matrix that can be added to house
 * coordinates
 */
void move(char direction, int *coords) {
    switch (direction) {
        case '^': // North
            coords[0] = 0;
            coords[1] = 1;
            break;
        case 'v': // South
            coords[0] = 0;
            coords[1] = -1;
            break;
        case '<': // West
            coords[0] = -1;
            coords[1] = 0;
            break;
        case '>': // East
            coords[0] = 1;
            coords[1] = 0;
            break;
        default: // Wait
            coords[0] = 0;
            coords[1] = 0;
            break;
    }
}

// unneeded because I use only stack memory so far
/* void house_free(house *first) */
/* { */
/*     house *curr, *head = first; */
/*     while ((curr = head) != NULL) { */
/*         head = head->next; */
/*         free(curr); */
/*     } */
/* } */

int house_add(house **first, int x, int y)
{
    puts("I'm here");
    int count = 0;
    house* f = *first;
    house* found = house_find(f, x, y);

    if (found) {
        puts("found");
        found->count++;
        return count;
    } else {
        puts("new");
        // suspicious if this lets me avoid malloc: XXX: looks like this needs to be redone with malloc
        house new = {x, y, 1, f};
        printf("new: %d:%d %zd\n", new.x, new.y, (size_t) new.next);
        // set first pointer to this one
        *first = &new;
        printf("updated first: %d:%d %zd.%zd\n", first.x, first.y, (size_t) first, (size_t) first.next);
        return 1;
    }
}

house* house_find(house *h, int x, int y)
{
    puts("finding");
    printf("finding %d:%d in %zd\n", x, y, (size_t) &h);
    int c = 0;

    house *i = h;

    while (i != NULL) {
        printf("checking %d:%d in %zd->%zd\n", i->x, i->y, (size_t) &i, (size_t) i->next);
        if (i->x == x && i->y == y)
            return i;

        i = i->next;
        c++;
        if (c > 4)
            break;
    }

    return NULL;
}
