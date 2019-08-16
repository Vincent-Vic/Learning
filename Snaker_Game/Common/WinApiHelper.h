/******************************************************
    > File Name: WinApiHelper.h
    > Author: Vincent·Vic
    > Mail: Vincent-Vic@qq.com
    > Created by Vincent·Vic on 2018/3/27.
    > Functional： Windows API Help declaration
*******************************************************/

#ifndef RERTO_SNAKER_WINAPIHELPER_H
#define RERTO_SNAKER_WINAPIHELPER_H
#pragma comment (lib,"User32.lib")
#include <tchar.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <mmsystem.h>
/**
 * Setting up the title
 * @param Title
 */
void setTitle(char *Title);
/**
 *  Setting window size needs to be implemented by setWindowInfo, and window handle is also needed.
 * @param Width
 * @param Heigth
 */
void setWinSize(int Width,int Heigth);
/**
 * Set the cursor position in the console
 * @param x
 * @param y
 */
void setCurrsorPosition(int x,int y);
/**
 * Setting color
 * @param Color
 */
void setColor(int Color);
/**
 * Draw a cross line
 * @param x
 * @param y
 * @param Color
 * @param letter：character
 * @param len
 */
void drawHline(int x,int y,int Color,int letter,int len);
/**
 * Draw a vertical
 * @param x
 * @param y
 * @param Color
 * @param letter 字符
 * @param len
 */
void drawVline(int x,int y,int Color,int letter,int len);
/**
 * Text output
 * @param txt
 * @param size
 */
void PrintText(char* txt,int size);
/**
 * Character filling
 * @param x
 * @param y
 * @param Color
 * @param letter
 * @param Width
 * @param Heigth
 */
void  fillText(int x,int y,int Color,int letter,int Width,int Heigth);

/**
 * Read a character from the keyboard
 * @return
 */
char ReadChar();

/**
 * hide cursor
 */
void disableCurrsor();

/**
 * Sound part playback function
 * @param sound
 */
void PlayGameSound(char* sound);

/**
 *Sound partial stop function
 */
void StopGameSound();
#endif //RERTO_SNAKER_WINAPIHELPER_H
