#pragma once
#include <stdbool.h>

struct node;

typedef struct node Node;

struct road;

typedef struct road Road;

struct road
{
    int id;
    int cost;
    int from;
    int to;
    int color;
};

Road* init_road(int id, int cost, int from, int to);
void merge(Road* arr[], int l, int m, int r);
void mergeSort(Road* arr[], int l, int r);
void merge2(Road* arr[], int l, int m, int r);
void mergeSort2(Road* arr[], int l, int r);