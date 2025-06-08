#include <iostream>
using namespace std;

void Shadow(int point_1s[4][2]);

int endcheck();
int point_1s[4][2], point_2s[4][2];
int bomba1[4][2] = {0}, bomba2[4][2];
int n = 0;
int endchecker = endcheck();

void fallingPiece(float &timer, float &delay, int &colorNum, int &n)
{
    endchecker = endcheck();
    if (endchecker == 0)
    {
        if (timer > delay)
        {
            for (int i = 0; i < 4; i++)
            {
                delay = 0.3;
                if (i == 0)

                    point_2[i][0] = point_1[i][0];
                point_2[i][1] = point_1[i][1];
                point_1[i][1] += 1; // How much units downward
            }

            if (!anamoly())
            {
                for (int i = 0; i < 4; i++)
                {
                    gameGrid[point_2[i][1]][point_2[i][0]] = colorNum;
                }

                colorNum = 1 + rand() % 7;

                n = rand() % 7;
                //--- Un-Comment this Part When You Make BLOCKS array---//
                if (n < 7)
                {
                    for (int i = 0; i < 4; i++)
                    {
                        point_1[i][0] = BLOCKS[n][i] % 2;
                        point_1[i][1] = BLOCKS[n][i] / 2;
                    }
                }
            }

            timer = 0;
        }
    }

    else
    {
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                gameGrid[i][j] = 0;
                gameGrids[i][j] = 0;
            }
        }
    }
}

void horizontalmovement(int &delta_x)
{
    for (int i = 0; i < 4; i++)
    {
        point_2[i][0] = point_1[i][0];
        point_2[i][1] = point_1[i][1];
        // point_2s[i][0]=point_1s[i][0];
        // point_2s[i][1]=point_1s[i][1];
        // backup ^

        point_1[i][0] += delta_x;

        // point_1s[i][0]=point_1[i][0];
        // if(delta_x!=0)
        // point_1s[i][1]=BLOCKSs[n][i]/2;
    }
    delta_x = 0;

    if (!anamoly())
    {
        for (int i = 0; i < 4; i++)
        {
            point_1[i][0] = point_2[i][0];
            point_1[i][1] = point_2[i][1];
        }
    }
}

void rotation(bool &rotate)
{
    if (rotate == 1)
    {
        int x, y;

        for (int i = 0; i < 4; i++)
        {
            x = point_1[i][1] - point_1[1][1];
            y = point_1[i][0] - point_1[1][0];
            point_1[i][0] = point_1[1][0] - x;
            point_1[i][1] = point_1[1][1] + y;
        }

        rotate = 0;

        if (!anamoly())
        {
            for (int i = 0; i < 4; i++)
            {
                point_1[i][0] = point_2[i][0];
                point_1[i][1] = point_2[i][1];
            }
        }
    }
}

bool anamolys(int point_1s[4][2])
{
    for (int i = 0; i < 4; i++)
    {
        if (point_1s[i][0] < 0 || point_1s[i][0] >= N || point_1s[i][1] >= M - 1)
            return 0;
        else if (gameGrid[point_1s[i][1] + 1][point_1s[i][0]])
            return 0;
    }
    return 1;
}

void Shadow(int point_1s[4][2])
{
    int max = 0;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            point_1s[i][j] = point_1[i][j];
        }
    }

    while (anamolys(point_1s))
    {
        for (int i = 0; i < 4; i++)
        {
            point_1s[i][1]++;
        }
    }
}

void linecheck()
{
    int l = M - 1;
    int count;
    for (int i = M - 1; i > 0; i--)
    {
        count = 0;
        for (int j = 0; j < N; j++)
        {
            if (gameGrid[i][j])
            {
                count++;
            }
            gameGrid[l][j] = gameGrid[i][j];
        }
        if (count < N)
        {
            l--;
        }
    }
}

int endcheck()
{
    for (int i = 0; i < N; i++)
    {
        if (gameGrid[0][i] == 1)
        {
            return 1;
        }
    }
    return 0;
}

///*** YOUR FUNCTIONS END HERE ***///
/////////////////////////////////////