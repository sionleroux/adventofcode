#include <stdio.h>
#include <stdlib.h>
#include "house.h"

// private functions
static house* house_find(house*, int, int);
static house* house_last(house*);
static house* house_parent(house*, house*);
static void   house_pop(house*);

/**
 * Frees a list of houses from memory, starting at the provided house.
 */
void house_free(house *first) {
#if HOUSE_VERBOSE >= 2
    puts("free");
#endif
    house *curr, *head = first;
    while ((curr = head) != NULL) {
        head = head->next;
        free(curr);
    }
}

/**
 * Allocates memory for a house and initialises it with the provided X
 * and Y coordinates.
 * Expects two coordinates as integers.
 * Returns a pointer to the new house.
 */
house* house_init(int x, int y) {
#if HOUSE_VERBOSE >= 2
    puts("init");
#endif
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
void house_add(house *f, int x, int y) {
#if HOUSE_VERBOSE >= 2
    puts("add");
#endif
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
static house* house_find(house *h, int x, int y) {
#if HOUSE_VERBOSE >= 2
    puts("find");
#endif
    house *i = h;

    while (i != NULL) {

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
static house* house_last(house *h) {
#if HOUSE_VERBOSE >= 2
    puts("last");
#endif
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
static house* house_parent(house *f, house *t) {
#if HOUSE_VERBOSE >= 2
    puts("parent");
#endif
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
static void house_pop(house *parent) {
#if HOUSE_VERBOSE >= 2
    puts("pop");
#endif
    house *target = parent->next;
    parent->next = target->next;
    free(target);
}

/**
 * Strips houses with duplicate coordinates from a list of houses
 * leaving a list of unique houses which can easily be counted.
 * Expects a list of houses.
 * Operates on the provided list, so be careful what you pass it.
 */
void house_uniq(house *f) {
#if HOUSE_VERBOSE >= 2
    puts("uniq");
#endif
    house *i = f;
    house *d = NULL; // potential duplicate

    while (i != NULL) {

        // pop any duplicates further on in the list (next)
        while ((d = house_find(i->next, i->x, i->y)) != NULL) {
            house_pop(house_parent(f, d));
        }

        i = i->next;
    }
}

/**
 * Joins an array of house lists into a single list of houses by linking
 * each element's first house to the last house of the previous one.
 * Expects an array of house lists and the size of the array.
 */
house* house_join(house** h, int size) {
#if HOUSE_VERBOSE >= 2
    puts("join");
#endif
    house* l; // last house of previous

    for (int i = 1; i < size; ++i) {
        // link the house to the end of the previous
        l = house_last(h[i-1]);
        l->next = h[i];
    }

    return h[0];
}

/**
 * Counts the number of houses in a list of houses.
 * Expects a pointer to the first house in a list of houses.
 * Returns the number of unique houses.
 */
int house_count(house *h) {
#if HOUSE_VERBOSE >= 2
    puts("count");
#endif
    house *i = h;
    int c = 1; // number of houses

    while (i->next != NULL) {
        i = i->next;
        c++;
    }

    return c;
}

// vim:tw=72
