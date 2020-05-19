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

int MMI_addr = 0;
int page_MMI = 9;

/*
int page_mmi_0 = 0; //Чистый светлый экран
int page_mmi_1 = 1; //Чистый темный экран
int page_mmi_2 = 2; //ВРФ Учет природного газа*/
int page_mmi_3 = 3; //ВРФ Учет тепловой энергии
/*int page_mmi_4 = 4; //Учет алкогольной продукции
int page_mmi_5 = 5; //Управление резервуарами
int page_mmi_6 = 6; //Учет сырой нефти
int page_mmi_7 = 7; //ВРФ Учет расхода топлива
int page_mmi_8 = 8; //ООО Факом Технолоджиз  "ESC"Меню
int page_mmi_9 = 9; //ООО Факом Технолоджиз  "ESC"Меню
*/
unsigned char dis_buf[120];
unsigned char KeyBuf[50];

void KeyBoard();
void DisplayClear();
void DisplayMMI();
void MmiPuts(int y, int x, char *str);
int  MmiPrintf(int y, int x, char *format , ...);

int display = 0;
int str_dis=0;

unsigned char ver[] = "Версия N2 02.02.2020 YN";

#include "MD5.H"
#include "MD5C.C"