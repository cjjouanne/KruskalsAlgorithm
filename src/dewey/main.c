#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "node.h"


int main(int argc, char** argv)
{
    // Revisamos los argumentos
    if(argc != 3) {
        printf("Modo de uso: %s <network.txt> <output.txt>\n", argv[0]);
        return 1;
    }

    FILE *input_file = fopen(argv[1], "r");
    /* Abrimos el archivo de output */
    FILE *output_file = fopen(argv[2], "w");

    int n_clients;
    int n_disrtibutors;
    int n_roads;
    fscanf(input_file, "%d", &n_clients);
    fscanf(input_file, "%d", &n_disrtibutors);
    fscanf(input_file, "%d", &n_roads);
    int n_lines = n_roads;
    int id;

    id = 0;

    int cost = 0;

    int total_nodes = n_clients + n_disrtibutors;
    int visited[total_nodes];

    for (int i = 0; i < total_nodes; i++)
    {
        if (i >= n_clients)
        {
            visited[i] = total_nodes;
        }
        else
        {
            visited[i] = i;
        }
    }

    Road* roads[n_roads];

    while (n_lines)
    {
        /* Disminuimos en 1 el número de líneas por leer */
        n_lines--;

        /* Leemos la instrucción */
        int from;
        int to;
        int cost;
        fscanf(input_file, "%d", &from);
        fscanf(input_file, "%d", &to);
        fscanf(input_file, "%d", &cost);
        Road* road = init_road(id, cost, from, to);
        roads[id] = road;
        id += 1;
    }
    mergeSort(roads, 0, n_roads - 1);
    
    for(int i = 0; i < n_roads; i++)
    {
        int from = roads[i]->from;
        int to = roads[i]->to;
        if (visited[from] != visited[to])
        {
            roads[i]->color = 1;
            cost += roads[i] -> cost;
            int updating;
            if (visited[from]>visited[to])
            {
                updating = visited[to];
                for (int i=0;i<total_nodes;i++)
                {
                    if(visited[i]==updating)
                    {
                        visited[i]=visited[from];
                    }
                }
            }
            else
            {
                updating = visited[from];
                for (int i=0;i<total_nodes;i++)
                {
                    if(visited[i]==updating)
                    {
                        visited[i]=visited[to];
                    }
                }
            }
        }
    }

    mergeSort2(roads, 0, n_roads - 1);

    fprintf(output_file, "%d\n", cost);
    for (int i = 0; i < n_roads; i++)
    {
        if (roads[i]->color == 1)
        {
            fprintf(output_file, "%d\n", roads[i]->id);
        }
    }

    for (int i = 0; i < n_roads; i++)
    {
        free(roads[i]);
    }
    

    // Terminamos exitosamente
    fclose(input_file);
    fclose(output_file);

    return 0;
}