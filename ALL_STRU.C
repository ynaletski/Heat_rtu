struct comport
{
  unsigned char buf[256]; /*сєЇхЁ яЁш╕ьр*/
  unsigned char status; /*ёЄрЄєё т√яюыэхэш  юяхЁрЎшш:
			 0-шёїюфэюх,1-т сєЇхЁх хёЄ№ фрээ√х,2-яЁшэ Є сыюъ*/
  unsigned char index;  /*шэфхъё сєЇхЁр яЁш╕ьр*/
  unsigned char timer;  /*ёў╕Єўшъ тЁхьхээ√ї шэЄхЁтрыют*/
  unsigned char ta;     /*шэЄхЁтры Єрщь-рєЄр ъЁрЄэ√щ 50 ьёхъ*/
  unsigned char reinst;
  unsigned char ind_beg; /*шэфхъё эрўрыр сыюър, фы  ЄхъёЄ яЁюЄюъюыр*/
  unsigned char ind_end; /*шэфхъё ъюэЎр сыюър*/
};

struct mvs
{
  float data[21];              /*динамические параметры и зн.калибровки*/
  float avg[3];                /*усреднённые зн.дин.параметров*/
  unsigned char setup[13];     /*тег,адрес,статус,единицы*/
  unsigned char wait;           /*число временных интервалов паузы*/
  unsigned char evt;            /*событие*/
  unsigned char alm_enb;      /*алармы разрешены/запрещены*/
  float alm_set[3][3];         /* уставки для перепада:ниж,верх,гистер*/
  unsigned char alm_status[3];       /* факт регистрации аларма */
};
struct modul_rtd
{
  float         prm[6];            /*параметры до 6-х входов*/
  unsigned char status[4];
  unsigned char typ[6];
  unsigned char evt;
  unsigned char chanel;
};
struct modul_ai
{
  float         prm[8];            /*параметры до 8-ми каналов*/
  float         avg[8];            /*усредненные*/
  float         lo_brd[8];         /*нижняя граница диапазона*/
  float         hi_brd[8];         /*верхнняя граница диапазона*/
  float         alm_set[8][5];    /*уставки для каналов:нн,ниж,верх,вв,гистер,*/
  unsigned char units[8];
  unsigned char status[4];
  unsigned char evt;
  unsigned char alm_enb;           /*алармы разрешены/запрещены*/
  unsigned char alm_status[8];        /*факт регистрации аларма */
};
struct modul_ao
{
  float         prm[4];            /*параметры до 4-х каналов*/
  float         lo_brd[4];         /*нижняя граница диапазона*/
  float         hi_brd[4];         /*верхнняя граница диапазона*/
  unsigned char units[4];
  unsigned char status[6];
  unsigned char evt;
  unsigned char chnl;
};
struct modul_dio
{
  unsigned char inp;
  unsigned char out;
  unsigned char stat_out;
  unsigned char status[4];
  unsigned char evt;
};
struct modbus_host
{
  unsigned char num_pool;          /*порядковый номер запроса*/
  unsigned char stat_pool;         /*статус выполнения запроса*/
  unsigned char adr;               /*адрес внешнего устройства*/
  unsigned char func;              /*функция*/
  unsigned char count;             /*число регистров в запросе*/
  unsigned char status;            /*запрос включен,код ошибки*/
  unsigned      readr;             /*переадресатор*/
  unsigned char flag;            /*признак приостановки запросов*/
  unsigned      wait;            /*счётчик 50 мс интервалов*/
};
struct runtime
{
  unsigned char nmb;          /*порядковый номер модуля или датчика*/
  unsigned char nmb_icp;      /*порядковый номер модуля*/
  unsigned char ind;          /*для адресации модуля или датчика*/
  unsigned char pnl;          /*порядковый номер строки на табло*/
  unsigned char cnt_avg;      /*счётчик усреднений от датчиков*/
  unsigned char flg_err;      /*флажок визуализации ошибки*/
  unsigned char old_sec;
  unsigned char old_min;
  unsigned char old_hour;
  unsigned char old_month;
  unsigned char mmi;
};
struct in_table
{
  float      level[256];
  float     volume[256];
  float      meter[256];
  float       tank[256];
  float      press[256];
  unsigned        count;
};
struct out_table
{
  float      level[1024];
  float     volume[1024];
  float     factor[1024];
  unsigned        count;
};
struct gasquality
{
  float        density;
  float        methane;
  float        nitro;
  float        carbon;
  float        ethane;
  float        propane;
  float        n_but;
  float        i_but;
  float        n_pent;
  float        i_pent;
  float        hexane;
  float        hydrogen;
  float        carbon_m;
  float        helium;
  float        water;
  float        hydrosulf;
};
struct script
{
  double         accum;
  double	 argum;
  unsigned      count;
  unsigned char buf[6];
  unsigned      wait;
  unsigned char flag;
  unsigned     delay;
};
struct panel
{
  float          data[3];
  unsigned char  ind;
};

