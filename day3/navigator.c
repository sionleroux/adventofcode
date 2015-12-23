#include <stdio.h>
#include <stdlib.h>

typedef struct house house;
struct house {
    int x;
    int y;
    house* next;
};

void arrow_to_coords(char, int*);
void house_free(house*);
house* house_init(int, int);
void house_add(house*, int, int);
house* house_find(house*, int, int);
house* house_last(house*);
int house_count(house*, house*);
house* house_parent(house*, house*);
void house_pop(house*);
void house_uniq(house*);

int main()
{

    char c; // character read from stdin
    int santas = 2; // number of people walking
    int s = 0; // current santa
    int m[santas]; // movement coords
    house* h[santas];
    h[0] = house_init(0, 0); // starting house
    h[1] = house_init(0, 0); // starting house

    while ((c = fgetc(stdin)) != EOF) {
        arrow_to_coords(c, m);
        if (m[0] + m[1] == 0) // {0, 0} Wait
            continue;
        house_add(h[s], m[0], m[1]);

        // give each house to the next santa
        s++;
        if (s >= santas)
            s = 0;

    }

    printf("house count: %d\n", house_count(h[0], h[1]));

    house_free(h[0]);
    house_free(h[1]);

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

    h->next = NULL;
    h->x = x;
    h->y = y;

    return h;
}

/**
 * Adds a new house to the list of visited houses.
 * Expects a pointer to the first house in the list and the current
 * cooridinates.
 * Returns 1 if this house hasn't been visited before, otherwise 0.
 */
void house_add(house *f, int x, int y)
{
    house *last = house_last(f);
    last->next = house_init(last->x + x, last->y + y);
}

/**
 * Finds a house by cooridinates.
 * Expects a pointer to the first house in the list and integers for x
 * and y coordinates.
 * Returns a pointer to a house matching the provided coordinates or
 * NULL if not found.
 */
house* house_find(house *h, int x, int y)
{
    house *i = h;

    while (i != NULL) {
    house *i = h;

        if (i->x == x && i->y == y)
            return i;

        i = i->next;
    }

    return NULL;
}

/**
 * Returns a pointer to the last house in a list of houses.
 * Expects a pointer to the start of a list of houses.
 */
house* house_last(house *h)
{
    house *i = h;

    while (i->next != NULL)
        i = i->next;

    return i;
}

/**
 * Finds a house whose next member points to the given house, that is
 * the house's parent in the list.
 * Expects a pointer to a list of houses and a pointer to a target house
 * to search for in that list.
 * Returns the parent of the target house or NULL if not found.
 */
house* house_parent(house *f, house *t)
{
    house *i = f; // is this even necessary?

    while (i && i->next != t)
        i = i->next;

    return i;
}

/**
 * Pops a house out of the house list and destroys it.
 * Expects a pointer to the parent house, that is the house pointing to
 * the house to be popped, necessary because the list only links
 * forwards.
 */
void house_pop(house *parent)
{
    house *target = parent->next;
    parent->next = target->next;
    house_free(target);
}

/**
 * Strips houses with duplicate coordinates from a list of houses
 * leaving a list of unique houses which can easily be counted.
 * Expects a list of houses.
 * Operates on the provided list, so be careful what you pass it.
 */
void house_uniq(house *f)
{
    house *i = f;
    house *d; // potential duplicate

    while (i->next != NULL) {

        // pop any duplicates further on in the list (next)
        while ((d = house_find(i->next, i->x, i->y))) {
            house_pop(house_parent(f, d));
        }

        i = i->next;
    }
}

/**
 * Counts the number of houses in a list of houses.
 * Expects a pointer to the first house in a list of houses.
 * Returns the number of unique houses.
 */
int house_count(house *h, house *r)
{
    house *i = h;
    int c = 1; // number of houses

    // TODO: make this work with an array of any size
    // link the two house lists
    house *l = house_last(h);
    l->next = r;

    // strip duplicates from the long house list in place :-O
    house_uniq(h);

    while (i->next != NULL) {
        i = i->next;
        c++;
    }

    return c;
}

// vim:tw=72
