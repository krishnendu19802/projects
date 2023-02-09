#include <iostream>
#include <vector>
#include <utility>
using namespace std;
char arr[3][3];//2D array for storing the characters

void display()//function to display the tic-tac-toe board
{
    int i = 0, j = 0, k = 0, l = 0;
    for (i = 0; i < 5; i++)
    {
        cout << "\t\t\t\t\t";
        for (j = 0; j < 3; j++)
        {
            if (i % 2 == 1)
            {
                cout << "____ ";
                continue;
            }
            cout << " " << arr[k][l++];
            if (j != 2)
                cout << " | ";
        }
        if (i % 2 != 1)
        {
            ++k;
            l = 0;
        }
        cout << endl;
       
    }
}

void check(char a, char b, char c, int i)//checks if the three characters are same 
{
    if (a == b)
    {
        if (b == c)
        {
            cout << "player " << i << " has won" << endl;
            exit(0);
        }
    }
}

void conditions(int i)//checks if any player has won at any point of time
{
    check(arr[0][0], arr[0][1], arr[0][2], i);
    check(arr[0][0], arr[1][0], arr[2][0], i);
    check(arr[0][0], arr[1][1], arr[2][2], i);
    check(arr[1][0], arr[1][1], arr[1][2], i);
    check(arr[2][0], arr[2][1], arr[2][2], i);
    check(arr[2][0], arr[1][1], arr[0][2], i);
    check(arr[2][1], arr[1][1], arr[0][1], i);
    check(arr[2][2], arr[1][2], arr[0][2], i);
}

int main()
{
    int i, j, k = 1;
    vector<pair<int, int>> pos;//vector for relating the number displayed on the board with the row and column number
    pos.push_back({0, 0});
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
            pos.push_back({i, j});
    }
    
    k = 1;

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            arr[i][j] = (char)(k + 48);
            k++;
        }
    }
    k = 1;
    display();
    cout << endl;
    int val;
    pair<int, int> pr;
    for (i = 0; i < 9; i++)
    {
        val = i % 2;

        cout << "enter player " << val << " : ";
        cin >> k;
        if (k < 0 || k > 10)
        {
            i--;
            cout << "WRONG INPUT" << endl;//valid input is for 0-9(numbers displayed on the board)
            continue;
        }
        pr = pos[k];

        if (arr[pr.first][pr.second] != 'x' && arr[pr.first][pr.second] != 'o')//valid position only if it is empty
        {
            if (i % 2 == 0)
                arr[pr.first][pr.second] = 'x';
            else
                arr[pr.first][pr.second] = 'o';
        }
        else
        {
            cout << "overwrite not possible" << endl;
            i--;
        }
        cout << endl;
        display();
        conditions(val);
        cout << endl;
    }

    cout << "MATCH DRAWN" << endl;
}