#include "ALL.h"

///////////////////////////////////////////////////////////////////////////////////////////
int MmiPuts(int x, int y, char *str)
{
    if (TimeStamp > 5)
    {
        if (strlen(str)>15)
        {
            strncpy(half_one, str, 15);
            strcpy(half_too, (str + 15));
            if(!half_count)
            {
                sprintf(dis_buf,"$%02XGS%02X%02X%s",MMI_addr,x,y*8,half_one);
                SendCmdTo7000(ComPortICP,dis_buf,1);                
                ReceiveResponseFrom7000_ms(ComPortICP,KeyBuf,1000,1);
                memset(KeyBuf, 0, sizeof(KeyBuf));
                memset(dis_buf, 0, sizeof(dis_buf)); 
                *(long int *)&(TimeStamp)=0;
                half_count = 1;
                //printCom(ComPortHost,"\n=>!");
                return 1;
            }
            else
            {
                sprintf(dis_buf,"$%02XGS%02X%02X%s",MMI_addr,x+15,y*8,half_too);
                SendCmdTo7000(ComPortICP,dis_buf,1);                
                ReceiveResponseFrom7000_ms(ComPortICP,KeyBuf,1000,1);
                memset(KeyBuf, 0, sizeof(KeyBuf));
                memset(dis_buf, 0, sizeof(dis_buf)); 
                *(long int *)&(TimeStamp)=0;
                str_dis++;
                half_count=0;
                return 1;
            }            
        }
        else
        {
            sprintf(dis_buf,"$%02XGS%02X%02X%s",MMI_addr,x,y*8,str);
            SendCmdTo7000(ComPortICP,dis_buf,1);                
            ReceiveResponseFrom7000_ms(ComPortICP,KeyBuf,1000,1);
            //printCom(ComPortHost,"\n=>%s",KeyBuf);
            memset(KeyBuf, 0, sizeof(KeyBuf));
            memset(dis_buf, 0, sizeof(dis_buf)); 
            *(long int *)&(TimeStamp)=0;
            str_dis++;
            return 1;
        }
    }
    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////
char BufferMmiPrintf[128];
int  MmiPrintf(int x, int y, char *format , ...)
{
  va_list marker;
  va_start( marker, format);
  vsprintf(BufferMmiPrintf, format, marker);
  MmiPuts(x, y, BufferMmiPrintf);
  return (strlen(BufferMmiPrintf));
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void main (void)
{
    InitLib();
    //*(long int *)&(TimeStamp)=0;
    InstallCom(ComPortICP,9600L,8,0,1);

    while(!quit)
    {
        KeyBoard();
        DisplayMMI();

    }
    RestoreCom(ComPortICP);
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
void DisplayMMI()
{
    switch (display)
    {
    case 0:
        DisplayClear(page_mmi_2);
        display++;
        str_dis=0;
        break;
    case 1: 
        switch (str_dis) //формирует страницу
        {
        /*                        "---------------++++++++++++++" */  // Размер строки не должен превышать это поле
            case 0: DisplayClear(); str_dis++; break;
            case 1: MmiPuts(0,0,  "   Вычислитель расхода ВРФ  ");break;
            case 2: MmiPuts(0,1,  "    Учет тепловой энергии   ");break;
            case 3: MmiPrintf(0,3,"   %s",ver);break;    
            case 4: MmiPuts(0,5,  "   MD5 идет расчет...  ");break;
            case 5: MmiPuts(0,15,  "        ESC - возврат в меню");break;
            case 6: f_md5(1); display++; str_dis=0; break;
        }
        break;
    case 2:
        if(fl_md_fst)
        {
            switch (str_dis)
            {
            case 0: MmiPrintf(3,5,"MD5 (%s,%ld) = ", filename,lgth_fl); break;
            case 1: MmiPrintf(6,7,"%02x%02x%02x%02x%02x%02x%02x%02x", digest[0],digest[1],digest[2],digest[3],digest[4],digest[5],digest[6],digest[7]); break;
            case 2: MmiPrintf(6,8,"%02x%02x%02x%02x%02x%02x%02x%02x", digest[8],digest[9],digest[10],digest[11],digest[12],digest[13],digest[14],digest[15]); break;
            case 3: display++; str_dis=0; break;
            }
        }
    case 3:

        break;
    case 4:
        switch (str_dis) //формирует страницу
        {
        /*                        "---------------++++++++++++++" */  // Размер строки не должен превышать это поле
            case 0: MmiPuts(0,0,  "   Вычислитель расхода ВРФ  ");break;
            case 1: MmiPuts(0,1,  "    Учет тепловой энергии   ");break;
            case 2: MmiPuts(0,15, "        ESC - возврат в меню");break;
            case 3: quit=1; break;
        }
        break;
    }
}
//////////////////////////////////////////////////////////////////////////
void DisplayClear(int page)
{
    sprintf(dis_buf,"$%02XP%02X",MMI_addr,page);
    SendCmdTo7000(ComPortICP,dis_buf,1);
    ReceiveResponseFrom7000_ms(ComPortICP,KeyBuf,1000,1);
    memset(dis_buf, 0, sizeof(dis_buf));
    memset(KeyBuf, 0, sizeof(KeyBuf));
    *(long int *)&(TimeStamp)=0;
}
///////////////////////////////////////////////////////////////////////////
void KeyBoard()
{
    SendCmdTo7000(ComPortICP,"$01K",1);
    ReceiveResponseFrom7000_ms(ComPortICP,KeyBuf,100,1);
    //printCom(ComPortHost,"\n=>%s",KeyBuf);
    if(strlen(KeyBuf)>6)
    {
        if(KeyBuf[4] == '0' && KeyBuf[5] == '6')  //ESC
        {
            DisplayClear(page_mmi_2);
            display=4;
        }
    }
    memset(KeyBuf, 0, sizeof(KeyBuf));
}
//////////////////////////////////////////////////////////////////////////