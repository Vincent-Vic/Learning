/******************************************************
    > File Name: WinApiHelper.c
    > Author: Vincent·Vic
    > Mail: Vincent-Vic@qq.com
    > Created by Vincent·Vic on 2018/3/27.
    > Functional： Windows API Help implementation
*******************************************************/

#include "WinApiHelper.h"

/**
 * Global window handle
 */
HANDLE  std_win_handle=0;

void setWinHandle()
{
    if(std_win_handle==0)
    {
        /**
         * Get the standard output handle
         */
        std_win_handle=GetStdHandle(STD_OUTPUT_HANDLE);
    }
}
void setTitle(char *Title)
{
    SetConsoleTitle(TEXT(Title));
}

void setWinSize(int Width, int Heigth)
{

    /**
     * The point of the distance is defined.
     * The size area of the form (starting point - end)
     */
    SMALL_RECT RECT={0,0,Width-1,Heigth-1};
    // Buffer zone
    COORD coord={Width,Heigth};
    //Get a form handle
    setWinHandle();
    //Setting the buffer zone
    SetConsoleScreenBufferSize(std_win_handle,coord);
    //Setting the size of the form
    SetConsoleWindowInfo(std_win_handle,TRUE,&RECT);
}

void setCurrsorPosition(int x, int y)
{
    COORD pos={x,y};
    setWinHandle();
    SetConsoleCursorPosition(std_win_handle,pos);
}

void setColor(int Color)
{
    setWinHandle();
    SetConsoleTextAttribute(std_win_handle,Color);
}

void drawHline(int x, int y, int Color, int letter, int len)
{
    setCurrsorPosition(x,y);
    setColor(Color);
    int i;
    for(i=0;i<len;i++)
    {
        printf("%c",letter);
    }
}

void drawVline(int x, int y, int Color, int letter, int len)
{
    setCurrsorPosition(x,y);
    setColor(Color);
    int i;
    for(i=0;i<len;i++){
        printf("%c",letter);
        setCurrsorPosition(x,++y);
    }
}

void PrintText(char *txt, int size)
{
    char format[30]="%-";
    char sizebuf[5];
    itoa(size, sizebuf,10);
    strcat(format,sizebuf);
    strcat(format,"s");
    printf(format,txt);
}

void fillText(int x, int y, int Color, int letter, int Width, int Heigth)
{
    setWinHandle();
    DWORD relen;
    int i;
    for(i=0;i<Heigth;i++){  //Filling block
        COORD coord={x,y++};
        //Fill one line
        FillConsoleOutputAttribute(std_win_handle,Color,Width,coord,&relen);
        FillConsoleOutputCharacter(std_win_handle,letter,Width,coord,&relen);
    }

}

char ReadChar()
{
    char rech=0;
    if(kbhit())
    {
        rech=getch();
    }
    return rech;
}

void disableCurrsor()
{
    CONSOLE_CURSOR_INFO Cursot_info;
    Cursot_info.bVisible=FALSE;
    Cursot_info.dwSize=1;
    SetConsoleCursorInfo(std_win_handle,&Cursot_info);
}

void PlayGameSound(char *sound)
{
    PlaySound(TEXT(sound), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

void StopGameSound()
{
    PlaySound(NULL,NULL,SND_FILENAME);
}
