#include <iostream>

#include <conio.h> //console input output library
#include <ctime>

#include "Snake.h"
#include "Food.h"

//define ukuran board
#define WIDTH 50
#define HEIGHT 25

using namespace std;

Snake snake ({WIDTH/2, HEIGHT/2}, 1); //berada di tengah area
Food food;

int score;

void board () //fungsi untuk membuat papan area
{
            COORD snake_pos = snake.get_pos();
            COORD food_pos = food.get_pos();

            vector <COORD> snake_body = snake.get_body();

            cout << "SCORE : " << score << "\n\n";

            for (int i=0; i<HEIGHT; i++) //banyak baris dalam satu area
            {
                cout << "\t\tM"; //tab agar posisi ke tengah
                for (int j=0; j<WIDTH-2; j++) //banyak kolom dalam satu area
                {
                    if(i==0||i==HEIGHT-1) cout << 'M';

                    else if (i==snake_pos.Y && j+1==snake_pos.X) cout << 'o'; //snake position and visual output
                    else if (i==food_pos.Y && j+1==food_pos.X) cout << '6'; //food position and visual output

                    else
                    {
                        bool isBodyPart = false;
                        for (int k=0; k<snake_body.size()-1; k++)
                        {
                            if(i==snake_body[k].Y && j+1==snake_body[k].X)
                            {
                                cout << 'o';
                                isBodyPart=true;
                                break;
                            }
                        }
                        if(!isBodyPart) cout << ' ';
                    }
                }
                cout << "M\n";
            }
}


int main()
{
   score = 0;
   srand(time(NULL));

   food.gen_food();

   char game_over = false;

   while(!game_over)
   {
       board();

       if(kbhit()) //keyboard button setting
       {
           switch(getch())
           {
               case 72 : snake.change_dir('u'); break; //72 ASCII dari arrow up
               case 75 : snake.change_dir('l'); break; //75 ASCII dari arrow left
               case 80 : snake.change_dir('d'); break; //80 ASCII dari arrow down
               case 77 : snake.change_dir('r'); break; //77 ASCII dari arrow right
           }
       }
       if(snake.collided()) game_over=true;
       if(snake.eaten(food.get_pos()))
       {
           food.gen_food();
           snake.grow();
           score=score+10;
       }

       snake.move_snake();

       SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});
   }
}
