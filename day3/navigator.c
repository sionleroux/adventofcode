#include <stdio.h>
#include <stdlib.h>

typedef struct house house;
struct house {
    int x;
    int y;
    int count; // how many times visited
    house* next;
};

void arrow_to_coords(char, int*);
void house_free(house*);
house* house_init(int, int);
house* house_add(house*, int, int);
house* house_find(house*, int, int);
house* house_last(house*);
int house_count(house*);

int main()
{

    char c; // character read from stdin
    int m[2]; // movement coords
    house* h = house_init(0, 0);
    house* l; // current house I'm at aka last house

    printf("init %d:%d #%d\n", h->x, h->y, h->count);

    while ((c = fgetc(stdin)) != EOF) {
        arrow_to_coords(c, m);
        if (m[0] + m[1] == 0) // {0, 0} Wait
            continue;
        house_add(h, (h->x + m[0]), (h->y + m[1]));
        l = house_last(h);
        printf("%c %d:%d #%d\n", c, l->x, l->y, l->count);
    }

    printf("house count: %d\n", house_count(h));

    house_free(h);

    return 0;
}

/**
 * Maps arrow directions to matrix that can be added to house
 * coordinates.
 */
void arrow_to_coords(char direction, int *coords) {
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
void house_free(house *first)
{
    house *curr, *head = first;
    while ((curr = head) != NULL) {
        head = head->next;
        free(curr);
    }
}

house* house_init(int x, int y)
{
    house *h = malloc(sizeof(house));

    h->count = 1;
    h->next = NULL;
    h->x = x;
    h->y = y;

    return h;
}

/**
 * Adds a new house to the list of visited houses.
 * Expects a pointer to the first house in the list and the current
 * cooridinates.
 * Returns a pointer to the last house.
 */
house* house_add(house *f, int x, int y)
{
    /* puts("I'm here"); */
    house *found = house_find(f, x, y);
    house *last;

    if (found) {
        printf("found ");
        found->count++;
        return found;
    } else {
        printf("new ");
        last = house_last(f);
        last->next = house_init(last->x + x, last->y + y);
        /* printf("last: %d:%d %zd\n", last->x, last->y, (size_t) last->next); */

        //XXX DEBUG
        last = house_last(f);
        /* printf("last: %d:%d %zd\n", last->x, last->y, (size_t) last->next); */
        /* printf("updated first: %d:%d %zd.%zd\n", first.x, first.y, (size_t) first, (size_t) first.next); */

        return last;
    }
}

house* house_find(house *h, int x, int y)
{
    /* puts("finding"); */
    /* printf("finding %d:%d in %zd\n", x, y, (size_t) &h); */
    int c = 0;

    house *i = h;

    while (i != NULL) {
        /* printf("checking %d:%d in %zd->%zd\n", i->x, i->y, (size_t) &i, (size_t) i->next); */
        if (i->x == x && i->y == y)
            return i;

        i = i->next;
        c++;
        /* if (c > 4) // XXX temp break stop overflow soon */
        /*     break; */
    }

    return NULL;
}

house* house_last(house *h)
{
    house *i = h;

    while (i->next != NULL)
        i = i->next;

    return i;
}

int house_count(house *h)
{
    house *i = h;
    int c = 1; // number of houses

    while (i->next != NULL) {
        i = i->next;
        c++;
    }

    return c;
}
