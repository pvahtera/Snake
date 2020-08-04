#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;
bool gameOver;

// define our variables

const int width = 10; // field
const int height = 10; // field

int diff_selection = 2; // initial difficulty selection
int sleepy_time = 10; // set normal difficulty

int x, y, fruitX, fruitY, score; // head and fruit position

// directions, use enumerate to have a constant direction
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir; // holds the direction of the snake

// mechanism for growing the snake
// we need 2 arrays, 1st is x coord of the tail
// 2nd is y coordinate of the tail

//int tailX[100], tailY[100]; // coordinates, max len 100
//int nTail; // length of the tail

int tailX[100], tailY[100]; // coordinates, max len 100
int nTail; // length of the tail

void Setup()
{
    gameOver = false;
    dir = STOP; // don't move until we move the snake
    x = width / 2; // start from the middle
    y = height / 2; 
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Draw()
{
    
    

    system("cls");
    // printing the top wall
    for (int i = 0; i < width+2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#";
            if (i == y && j == x)
                cout << "O"; // define the head
            else if (i == fruitY && j == fruitX)
                cout << "F"; // define the fruit
            else
            {   // go through every element of the tail
                bool print = false;
                for (int k = 0; k < nTail; k++) 
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o"; // define tail
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }
                
            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width+2; i++)
        cout << "#";
    cout << endl;
   // system("color E4");
    cout << "Score: " << score << endl;

    if (score >= 50 && score <= 100) {
        cout << " \n";
        cout << "You go girl! \n";
    } else if (score >= 100 && score <= 150) {
        cout << " \n";
        cout << "Awesome job! \n";
    } else if (score >= 150 && score <= 200) {
        cout << " \n";
        cout << "Great work! \n";
    }
    else if (score > 200) {
        cout << " \n";
        cout << "LEGEND MODE ACTIVATED, YOU STUD! \n";
    }

}


void Input()
{
    if (_kbhit()) // if keyboard is hit
    {
        switch (_getch()) // get character pressed
        {
        case 'a':
            dir = LEFT;
            break;
        case 'w':
            dir = UP;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void Logic()
{
    // remember previous coordinates of the tail
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    // set the first elements to follow the head
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        //update
        prevX = prev2X;
        prevY = prev2Y;

    }

    switch (dir)
    {
    case LEFT:
        x--; // decrease the x-coodrinate
        break;
    case RIGHT:
        x++; // increase the x-coodrinate
        break;
    case UP:
        y--; // decrease the y-coodrinate
        break;
    case DOWN:
        y++; // increase the y-coodrinate
        break;
    default:
        break;
    }
    // set the wall barriers to logic
    // *** game over if head gets past the barrier
    //if (x > width || x < 0 || y > height || y < 0)
    //{
    //    gameOver = true;
    //}

    // *** snake passes over to the other side when hits the wall
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= width) y = 0; else if (y < 0) y = width - 1;

    // set a rule so we cannot hit ourselves
    // loop through all tail segments

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)

            gameOver = true;
            cout << " " << endl;
            //cout << "GAME OVER, BITCH! TRY AGAIN!!" << endl;
            cout << " " << endl;

    // increase our size if we eat the fruit
    // if the locations match
    if (x == fruitX && y == fruitY)
    {
        
        score += 10; // increase score if we eat the fruit
        fruitX = rand() % width; // relocate the fruit
        fruitY = rand() % height;
        nTail++;
    }

}

void youDied() {
    cout << "You died! \n";

    cout << "      _____    \n";
    cout << "    /      \\   \n";
    cout << "    | () () |  \n";
    cout << "    \\   ^  /   \n";
    cout << "      |||||    \n";
    cout << "      |||||    \n";

}



void menu() {

    bool repeat = true;
    int selection = 0; // initial menu selection

    while (repeat == true) {

        cout << endl;
        cout << " Please choose from the following options - \n";
        cout << " 1. Play Snake.\n";
        cout << " 2. Set difficulty.\n";
        cout << " 3. Exit.\n";
        cout << " ";
        cin >> selection;

        if (selection == 1) {
            cout << "starting snake \n";

            Setup();
            while (!gameOver)
            {
                //Setup();
                Sleep(sleepy_time);
                Draw();
                Input();
                Logic();
            }

            youDied();            
            gameOver = false;
            nTail = 0; // reset the tail - game won't work otherwise
        }

        else if (selection == 2) {
            cout << endl;
            cout << " Please choose the difficulty from the following options - \n";
            cout << " 1. Peace of cake.\n";
            cout << " 2. Normal.\n";
            cout << " 3. Super-hard.\n";
            cout << " ";
            cin >> diff_selection;
            cout << endl;

            string playerChose; // relates to diff setting

            if (diff_selection == 1) {
                playerChose = "Peace of cake - brave choice...not!";
                sleepy_time = 100;
            } else if (diff_selection == 2) {
                playerChose = "Normal";
                sleepy_time = 30;
            } else if (diff_selection == 3) {
                playerChose = "Super-hard - nice, respect!";
                sleepy_time = 1;
            } else {
                cout << "Unknown selection";
            }

            cout << " You chose " << playerChose << ", Good luck!" << endl;
            cout << " Going back to the main menu...\n";
            cout << " ";

        } else if (selection == 3) {
            cout << "  \n";
            cout << "Quitting the game...Thanks for playing! \n";
            repeat = false;
            gameOver = true;

        } else {
            cout << "  \n";
            cout << "Unknown command ";
            break;
        }

        
    }

}


int main()
{
    menu();
        
    return 0;



}

