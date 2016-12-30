#ifndef _MAIN_
#define _MAIN_

class Mouse
{

public:
    int x;
    int y;
    int coin;
    void init(int x_en,int y_en);

};

void Mouse::init(int x_en, int y_en)
{

    x = x_en;
    y = y_en;
    coin = 0;

}

int read_input(char*input_file);
void route_find();
void printing();

#endif
