#include "ALL.h"

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
///////////////////////////////////////////////////////////////////////////////////////////
void MmiPuts(int y, int x, char *str)
{
    sprintf(dis_buf,"$%02XT%X%02X%s",MMI_addr,y,x,str);
    SendCmdTo7000(ComPortICP,dis_buf,1);                
    ReceiveResponseFrom7000_ms(ComPortICP,KeyBuf,1000,1);
    //printCom(ComPortHost,"\n=>%s",KeyBuf);
    memset(KeyBuf, 0, sizeof(KeyBuf));
    memset(dis_buf, 0, sizeof(dis_buf)); 
}
///////////////////////////////////////////////////////////////////////////////////////////
char BufferMmiPrintf[128];
int  MmiPrintf(int y, int x, char *format , ...)
{
  va_list marker;
  va_start( marker, format);
  vsprintf(BufferMmiPrintf, format, marker);
  MmiPuts(y, x, BufferMmiPrintf);
  return (strlen(BufferMmiPrintf));
}
//////////////////////////////////////////////////////////////////////////
void DisplayMMI()
{
    switch (display)
    {
    case 0:
        DisplayClear(page_MMI);
        display++;
        break;
    case 1: 
        MmiPrintf(2,3, "%s",ver);
        display++;
        break;
    case 2:
        MmiPuts(3,1, "MD5 идет расчет...");
        display++;
        break;
    case 3:
        if(fl_md_fst==0) f_md5(1);
        else {display++;}
        break;
    case 4:
        MmiPrintf(3,1, "MD5 (%s,%ld)=", filename,lgth_fl);
        display++;
        break;
    case 5:
        MmiPrintf(4,6, "%02x%02x%02x%02x%02x%02x%02x%02x", digest[0],digest[1],digest[2],digest[3],digest[4],digest[5],digest[6],digest[7]);
        display++;
        break;
    case 6:
        MmiPrintf(5,6, "%02x%02x%02x%02x%02x%02x%02x%02x", digest[8],digest[9],digest[10],digest[11],digest[12],digest[13],digest[14],digest[15]);
        display++;
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
    //*(long int *)&(TimeStamp)=0;
}
///////////////////////////////////////////////////////////////////////////
void KeyBoard()
{
    SendCmdTo7000(ComPortICP,"$00K",1);
    ReceiveResponseFrom7000_ms(ComPortICP,KeyBuf,100,1);
    //printCom(ComPortHost,"\n=>%s",KeyBuf);
    if(strlen(KeyBuf)>6)
    {
        if(KeyBuf[4] == '0' && KeyBuf[5] == '6') 
        {
            DisplayClear(page_mmi_3);
            quit = 1;
        }
    }
    memset(KeyBuf, 0, sizeof(KeyBuf));
}