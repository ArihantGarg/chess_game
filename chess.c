#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

//TODO: CHECK,CHECKMATE,DRAW,BETTER DISPLAY

int chessboard[8][8]={{12,13,14,15,16,14,13,12},
                      {11,11,11,11,11,11,11,11},
                      {0,0,0,0,0,0,0,0},
                      {0,0,0,0,0,0,0,0},
                      {0,0,0,0,0,0,0,0}, 
                      {0,0,0,0,0,0,0,0},
                      {1,1,1,1,1,1,1,1},
                      {2,3,4,5,6,4,3,2}};

int move_counter=1;

char name1[40],name2[40];

int number=218;    //Sum of pieces on board 

int row1,column1,row2,column2;    //Rows and columns for piece being moved

int numberofpieces=16;    //Number of pieces on chessboard

/* In array 'chessboard' , following pieces are denoted by these numbers :-
   
   WHITE-

   Pawn = 1
   Rook = 2
   Knight = 3
   Bishop = 4
   Queen = 5
   King = 6

   BLACK-

   Pawn = 11
   Rook = 12
   Knight = 13
   Bishop = 14
   Queen = 15
   King = 16

*/

/*For move_counter, 1 indicates white is making a move and 0 indicates black is making a move*/


int mod(int num)    //To find modulus of a number
{
    if(num>0)
        return num;
    else
        return (-num);    
}


void message_start()    //To get names of both players
{
    int i=0,j=0;
    char x=' ';

    printf("\n\tWELCOME\n\nEnter name of player 1:");
    do
    {
        name1[i++]=x;
        scanf("%c",&x);
    }
    while(x!='\n');

    x=' ';
        
    printf("\nEnter name of player 2:");
    do
    {
        name2[j++]=x;
        scanf("%c",&x);
    }
    while(x!='\n');

}


void message_toss()    //To decide who plays with white
{
    srand(time(0));

    int i=rand()%2;
    int j=0;
    
    printf("\n\n");

    if(i)
    {
        printf("\n\n%s plays with White\n",name1);           
    }    
    else
    {
        printf("\n\n%s plays with White\n",name2);
    }

    printf("\nTo enter move,first enter column(a to h) and then row(1 to 8),for example a8(no need to enter separately)\n");     

    printf("\nAlso you can enter initial and final square together,example 'e2 e4'\n");
}


int polarity()    //Returns 1 if invalid move,0 if valid
{
    if(move_counter)
    {
        if(chessboard[row2][column2]>=1 && chessboard[row2][column2]<=6)
            return 1;
    }
    else
    {
        if(chessboard[row2][column2]>=11 && chessboard[row2][column2]<=16)
            return 1;
    }

    return 0;
}


void pawn_promote()    //Promotes pawn
{
    int promote;

    printf("\nPawn promoted");
    printf("\nEnter 1 for queen,2 for rook,3 for bishop,4 for knight: ");
    scanf("%d",&promote);

    if(move_counter)
    {
        switch (promote)
        {
            case 1: 
            number=number+4;
            chessboard[row2][column2]=5;
            break;

            case 2:
            number=number+1;
            chessboard[row2][column2]=2;
            break;

            case 3:
            number=number+3;
            chessboard[row2][column2]=4;
            break;

            case 4:
            number=number+2;
            chessboard[row2][column2]=3;
            break;

            default:
            printf("\nIncorrect number\n");
            pawn_promote();
            break;

        }
    }
    else
    {
        switch (promote)
        {
            case 1:
            number=number+4;
            chessboard[row2][column2]=15;
            break;

            case 2:
            number=number+1;
            chessboard[row2][column2]=12;
            break;

            case 3:
            number=number+3;
            chessboard[row2][column2]=14;
            break;

            case 4:
            number=number+2;
            chessboard[row2][column2]=13;
            break;

            default:
            printf("\nIncorrect number\n");
            pawn_promote();
            break;

        }
    }

}


int sum_rowcol()    //Sum of elements along row or column
{
    int sum=0,count=mod(row2+column2-row1-column1);

    if(row2==row1)
    {
        if(column2>column1)
        {
            while(--count)
            {
                sum=sum+chessboard[row2][column2-count];
            }
        }
        else
        {
            while(--count)
            {
                sum=sum+chessboard[row1][column1-count];
            }
        }  
    }
    else
    {
        if(row2>row1)
        {
            while(--count)
            {
                sum=sum+chessboard[row2-count][column2];
            }
        }
        else
        {
            while(--count)
            {
                sum=sum+chessboard[row1-count][column1];
            }
        }
    }

    return sum;
}


int sum_diagonal()    //Sum of element along diagonal
{
    int sum=0,slope=(row2-row1)/(column2-column1),count=mod(column2-column1);

    while(--count)
    {
        if (column2>column1)
        {
            sum=sum+chessboard[row2-slope*count][column2-count];
        }
        else
        {
            sum=sum+chessboard[row1-slope*count][column1-count];
        }
    }

    return sum;
}


int validmove()    //Checks if move is valid(Returns 1 if invalid,0 if valid)
{
    if(row1<0 || row2<0 || column1<0 || column2<0)
        return 1;

    if(row1>7 || row2>7 || column1>7 || column2>7)
        return 1;

    if(row2==row1 && column2==column1)
        return 1;    


    if(move_counter)    //WHITE
    {
        switch (chessboard[row1][column1])
        {
            case 1:
            if(chessboard[row2][column2])
            {
                if(row1-row2==1 && mod(column1-column2)==1)
                    return 0;       
            }
            else
            {
                if(column1==column2)
                {
                    if(row1-row2==1)
                        return 0;
                    else if(row1-row2==2 && row1==6)
                        return 0;    
                }
            }
            break;

            
            case 2:
            if(row2==row1 || column2==column1)
                return sum_rowcol();
            break;

            
            case 3:
            if(mod(row2-row1)==2 && mod(column2-column1)==1)
                return 0;
            if(mod(row2-row1)==1 && mod(column2-column1)==2)
                return 0;
            break;
            
            case 4:
            if(mod((column2-column1)/(row2-row1))==1)
                return sum_diagonal();
            break;
            

            case 5:
            if(row2==row1 || column2==column1)
                return sum_rowcol();
            else if(mod((column2-column1)/(row2-row1))==1)
                return sum_diagonal();
            break;

            
            case 6:
            if(mod(row2-row1)<=1 &&mod(column2-column1)<=1)
                return 0;
            break;

            
            default:
            return 1;
            break;
        }
    }
    else    //BLACK
    {
        switch (chessboard[row1][column1])
        {
            case 11:
            if(chessboard[row2][column2])
            {
                if(row2-row1==1 && mod(column1-column2)==1)
                    return 0;
            }
            else
            {
                if(column1==column2)
                {
                    if(row2-row1==1)
                        return 0;    
                    else if(row2-row1==2 && row1==1)
                        return 0;    
                }
            }
            break;

            
            case 12:
            if(row2==row1 || column2==column1)
                return sum_rowcol();
            break;

            
            case 13:
            if(mod(row2-row1)==2 && mod(column2-column1)==1)
                return 0;
            if(mod(row2-row1)==1 && mod(column2-column1)==2)
                return 0;    
            break;

            
            case 14:
            if(mod((column2-column1)/(row2-row1))==1)
                return sum_diagonal();
            break;


            case 15:
            if(mod((column2-column1)/(row2-row1))==1)
                return sum_diagonal();
            else if(row2==row1 || column2==column1)
                return sum_rowcol();
            break;

            
            case 16:
            if(mod(row2-row1)<=1 &&mod(column2-column1)<=1)
                return 0;
            break;

            
            default:
            return 1;
            break;
        }
    }

    return 1;

}


int check()    //Checks if player is in check    //LATER[3]
{
    return 0;

}


int checkmate()    //Checks if player is checkmated    //LATER[5]
{
    return 0;
}


int checkdraw()    //Checks if game is drawn    //IMPROVE FOR STALEMATE[3]
{
    switch(numberofpieces)    //Draw by insufficient pieces
    {
        case 2:
        return 1;
        break;

        case 3:
        switch(number)
        {
            case 24:
            return 1;
            break;

            case 25:
            return 1;
            break;

            case 34:
            return 1;
            break;

            case 35:
            return 1;
            break;

            default:
            return 1;
            break;
        }
        break;

        default:
        return 0;
        break;
    }

    return 0;

}


void display_board()    //White - capital letters,Black - small letters,using horse instead of knight //LATER[3]
{
    int i=0,j=0;
    printf("\n");

    for(i=0;i<8;i++)
    {
        printf(" %d \t",8-i);

        for(j=0;j<8;j++)
        {
            switch(chessboard[i][j])
            {
                case 0:
                printf(" -");
                break;

                case 1:
                printf(" P");
                break;

                case 2:
                printf(" R");
                break;

                case 3:
                printf(" H");
                break;
                
                case 4:
                printf(" B");
                break;

                case 5:
                printf(" Q");
                break;

                case 6:
                printf(" K");
                break;

                case 11:
                printf(" p");
                break;

                case 12:
                printf(" r");
                break;

                case 13:
                printf(" h");
                break;

                case 14:
                printf(" b");
                break;

                case 15:
                printf(" q");
                break;

                case 16:
                printf(" k");
                break;

                default:
                break;           

            }
        }

        printf("\n");

    }

    printf("\n\n\t a b c d e f g h \n");

    printf("\n");

}

int flag=0;    //LATER REMOVE[5]

void game()    //Game logic    
{

    display_board();

    if(move_counter)
    {
        printf("\n\n White has to move\n");
        if(check())
            printf("Note:White is in check\n");
    }
    else
    {
        printf("\n\n Black has to move\n");
        if(check())
            printf("Note:Black is in check\n");
    }    


    while(1)
    {
        char x[2];

        printf("\nChoose initial square and final square: ");
        scanf("%s",x);

        row1=x[1];
        row1=row1-49;
        row1=7-row1;
        column1=x[0];
        column1=column1-97;

        printf(" \b");
        scanf("%s",x);

        row2=x[1];
        row2=row2-49;
        row2=7-row2;
        column2=x[0];
        column2=column2-97;

        int temp1,temp2,temp3;
        
        temp1=validmove()+polarity();
        if(temp1)
        {
            printf("\n Invalid move");
            display_board();
            continue;
        }
        
        temp2=chessboard[row2][column2];    //Temporarily stores value
        number=number-temp2;
        chessboard[row2][column2]=chessboard[row1][column1];
        chessboard[row1][column1]=0;
        
        if(temp2==6 || temp2==16)
            flag=1;

        if(temp2)
            numberofpieces--;

        temp3=check();
        if(temp3)
        {
            printf("\n Invalid move");
            chessboard[row1][column1]=chessboard[row2][column2];
            chessboard[row2][column2]=temp2;
            number=number+temp2;

            if(temp2)
                numberofpieces++;

            display_board();
            flag=0;

            continue;
        }

        break;

    }

    if(chessboard[row2][column2]%10 == 1 && row2%7 == 0)
    {
        pawn_promote();
    }   

    if(move_counter)
        move_counter=0;
    else
        move_counter=1;
    
}


void message_end()    //Win or Draw message    //LATER REMOVE FLAG[5]
{
    if(checkmate()||flag)    
    {

        if(move_counter)
        {
            printf("\n\n\t wins the game\n");
        }
        else
        {
            printf("\n\n\tWhite wins the game\n");
        }

    }    
    else
    {
        printf("\n\n\tGame ends in a draw\n");
    }

}




int main()    //REMOVE FLAG[5]
{
    message_start();

    message_toss();

    while(checkmate()+checkdraw()==0)        
    {
        game();
        if(flag)
            break;
    }

    message_end();

    return 0;
}