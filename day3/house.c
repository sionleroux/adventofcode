#include <stdio.h>
#include <stdlib.h>
#include "house.h"

// private functions
static house* house_find(house*, int, int);
static house* house_last(house*);
static house* house_parent(house*, house*);
static void   house_pop(house*);
static void   house_uniq(house*);

/**
 * Frees a list of houses from memory, starting at the provided house.
 */
void house_free(house *first) {
    puts("free");
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
    puts("init");
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
    puts("add");
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
    puts("find");
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
    puts("last");
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
    puts("parent");
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
    puts("pop");
    house *target = parent->next;
    if (target == NULL)
        puts("target is NULL");
    parent->next = target->next;
    free(target);
}

/**
 * Strips houses with duplicate coordinates from a list of houses
 * leaving a list of unique houses which can easily be counted.
 * Expects a list of houses.
 * Operates on the provided list, so be careful what you pass it.
 */
static void house_uniq(house *f) {
    puts("uniq");
    house *i = f;
    house *d = NULL; // potential duplicate

    while (i != NULL) {

        // pop any duplicates further on in the list (next)
        while ((d = house_find(i->next, i->x, i->y)) != NULL) {
            puts("find duplicate");
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
int house_count(house *h, house *r) {
    puts("count");
    house *i = h;
    int c = 1; // number of houses

    // TODO: make this work with an array of any size
    // TODO: out of scope of function
    // link the two house lists
    house *l = house_last(h);
    l->next = r;

    // TODO: out of scope of function
    // strip duplicates from the long house list in place :-O
    house_uniq(h);

    while (i->next != NULL) {
        i = i->next;
        c++;
    }

    return c;
}

// vim:tw=72
