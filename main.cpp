#include <iostream>
#include <stack>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "main.h"

#define INPUT_FILE "maze.txt"

using namespace std;

int N;
int En_i,En_j,Ex_i,Ex_j;
int **map;
Mouse mouse;
int cond;
int speed = 200000;
stack<Mouse> mouse_route;

int main()
{

    read_input(INPUT_FILE);
    mouse.init(En_i, En_j);
    route_find();

    if(map)
        free(map);

    return 0;
}

void route_find()
{

    while(1) {

        if(cond == 1) {
            mouse_route.push(mouse);
        }

        printing();
        usleep(speed);

        //detect whether the mouse reach the exit
        if(mouse.x == Ex_i && mouse.y == Ex_j)
            break;

        //mouse search the road
        if(map[mouse.x][mouse.y - 1] == 0 || map[mouse.x][mouse.y - 1] == 2) {

            if(map[mouse.x][mouse.y - 1] == 2) {
                mouse.coin++;
                speed = (speed <= 50000) ? speed : speed - 50000;
            }

            map[mouse.x][mouse.y - 1] = 3;
            mouse.y--;
            cond=1;

        } else if(map[mouse.x + 1][mouse.y] == 0 || map[mouse.x + 1][mouse.y] == 2) {

            if(map[mouse.x + 1][mouse.y] == 2) {
                mouse.coin++;
                speed = (speed <= 50000) ? speed : speed - 50000;
            }

            map[mouse.x + 1][mouse.y] = 3;
            mouse.x++;
            cond=1;
        } else if(map[mouse.x][mouse.y + 1] == 0 || map[mouse.x][mouse.y + 1] == 2) {

            if(map[mouse.x][mouse.y + 1] == 2) {
                mouse.coin++;
                speed = (speed <= 50000) ? speed : speed - 50000;
            }

            map[mouse.x][mouse.y + 1] = 3;
            mouse.y++;
            cond=1;
        } else if(map[mouse.x - 1][mouse.y] == 0 || map[mouse.x - 1][mouse.y] == 2) {

            if(map[mouse.x - 1][mouse.y] == 2) {
                mouse.coin++;
                speed = (speed <= 50000) ? speed : speed - 50000;
            }

            map[mouse.x - 1][mouse.y] = 3;
            mouse.x--;
            cond=1;
        } else {

            mouse_route.pop();
            mouse.x = mouse_route.top().x;
            mouse.y = mouse_route.top().y;
            cond = 0;
        }
    }
    cout << mouse.coin << endl;
}

int read_input(char* input_file)
{

    FILE* input_fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;
    char *token;
    int arg[4];

    //open file
    input_fp = fopen(input_file, "r");

    //get N
    read = getline(&line, &len, input_fp);
    N = atoi(line);

    //get En(i,j) Ex(i,j)
    read = getline(&line, &len, input_fp);
    token = strtok(line," ");
    for( int i = 0; token != NULL && i <= 4 ; i++) {
        arg[i] = atoi(token);
        token = strtok(NULL, " ");
    }

    En_i = arg[0];
    En_j = arg[1];
    Ex_i = arg[2];
    Ex_j = arg[3];

    //get map
    int count = 0;

    map = (int**)malloc(sizeof(int*) * N);
    for(int i = 0; i < N; i++)
        map[i] = (int*)malloc(sizeof(int) * N);

    for(int i = 0; i < N; i++) {
        read = getline(&line, &len, input_fp);
        token = strtok(line, " ");
        for(int j = 0; j < N && token != NULL; j++) {
            map[j][i] = atoi(token);
            token = strtok(NULL, " ");
        }
    }
    return 0;
}

void printing()
{
    system("clear");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == En_j && j == En_i)
                cout << "\033[47m" << "\033[31m" << "S" << "\033[0m";
            else if (i == Ex_j && j == Ex_i)
                cout << "\033[47m" << "\033[32m" << "E" << "\033[0m";
            else if (i == mouse.y && j == mouse.x)
                cout << "\033[41m" << "\033[32m" << "@" << "\033[0m";
            else
                switch (map[j][i]) {
                case 0:
                    cout << "\033[47m \033[0m";
                    break;
                case 1:
                    cout << "\033[40m" << " " << "\033[0m";
                    break;
                case 2:
                    cout << "\033[37m" << "\033[43m" << "\033[1m" << "$" << "\033[0m";
                    break;
                case 3:
                    cout << "\033[45m" << " " << "\033[0m";
                    break;
                default:
                    cout<<" ";
                }
        }
        cout<<endl;
    }
}
