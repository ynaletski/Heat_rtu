#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <dos.h>
#include <io.h>
#include <time.h>
#include <sys\types.h>
#include <sys\timeb.h>
#include"7188xa.h"

#define TimeStamp  *TimeTicks

//int ComPortHost=4;
int ComPortICP=1;

int quit=0;
//01.05.2020 YN -----\\//-----
int MMI_addr = 1; //was: int MMI_addr = 0;
//------------- -----//\\-----
int page_mmi_2 = 2; //чистая страница
unsigned char dis_buf[120];
unsigned char KeyBuf[50];

void KeyBoard();
void DisplayClear();
void DisplayMMI();

int display = 0;
int str_dis=0;

char half_one[15];
char half_too[15];
int half_count=0;

unsigned char ver[] = "Версия 01  Май.2020";

#include "MD5.H"
#include "MD5C.C"