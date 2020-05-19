/*********** ������ ��室� � �⠫쯨� ⥯�����⥫� ************/
/*10-06-09 ������� ��࠭�祭�� �� �᫮ ��������>1000 ��� �����*/
/*26-06-09 ����� ���ᨢ �����ᮢ ��� ���ମ� ind_prm_alm[8]    */
#include<math.h>

#define Max_conf             38 /*�᫮ ���䨣.��ࠬ��஢ �����*/
#define Max_select           100
#define Max_dyn              21 /*�᫮ �����.⨯�� �����*/
#define Max_dyn_massive      39 /*�᫮ �����.��ࠬ��஢ ����� ��� �����*/
#define Max_main             69 /*�᫮ ���䨣.��ࠬ��஢ �⠭樨*/
#define Max_select_main      58
#define Max_archive          7  /*�᫮ ��娢.��ࠬ��஢ �����*/
#define Max_arch_pnt         40 /*�᫮ ��娢.�祪 �⠭樨*/
#define Max_save             160
#define Max_arch_record      167 /*���� ����� ��娢 ����� � �����*/
#define Max_dyn_all          54  /*�᫮ �����.��ࠬ��஢ �����*/
#define Max_config_float     22  /*�᫮ ����⢨⥫��� ���䨣.��ࠬ��஢*/
#define Max_icp_prm          72  /*�᫮ ��ࠬ��஢ ����஥� ���㫥�*/
#define Max_exp_prm          60
#define Max_exp_dyn          40
#define Max_exp_const        20

struct modbus_config       Modbus;/*ࠧ��� � ����� ���䨣.��࠭���*/
const unsigned char size_conf[8]={129,129,129,129,240,0,216,235};
const unsigned char etl[8] = {1,2,4,8,16,32,64,128};
const unsigned char ind_prm_alm[8]={26,27,29,30,32,33,24,25};
const unsigned char typ_port[4] = {3,2,4,1};
unsigned char exp_dyn[Max_exp_dyn][5];
float exp_const[Max_exp_const];
unsigned char ind_accum[4]={1,2,4,6};
/*������ ��� �������, ������ � �� ��� ������� � ��,
  ������ �� �� ��� ������� �� ��*/
const unsigned char sel_units[3][2]={{6,7},{15,16},{12,19}};
/*���䨣���� ���� ��� �������୮� �ணࠬ��:
  [0]- �㭪� �ᯮ������ ��� ���,
  � [1] �� [5] ����� �㭪⮢ �������, ����� ����� ���� �ᯮ�짮����:
  1-��䨫� ���� ��⠭����,
  2-��⠭���� ���� � �६���,
  3-����ன�� ��娢��� �祪,
  4-����ன�� ���⮢,
  5-����ன�� Modbus,
  6-��䨫� ������� �窨,
  7-����ઠ ������� �窨,
  8-��� ����稪�� ������� �窨,
  9-��䨫� �������⥫쭮� �窨,
  10-����⠭�� ��� �窨,
  �᫨ ���祭�� �㭪�=0, ��᫥���� �� �ᯮ������ */
const unsigned char conf_menu[8][6]={
 {1,1,2,3,4,5},/*��騥 ��⠭����*/{1,6,7,8,0,0},/*��ࢠ� �窠*/
 {1,6,7,8,0,0},/*���� �窠*/   {1,6,7,8,0,0},/*����� �窠*/
 {1,6,7,8,0,0},/*������ �窠*/{1,9,10,0,0,0},/*��� �窠*/
 {1,11,0,0,0,0},/*���㫨 �/�*/    {0,0,0,0,0,0}/*१��*/};
/*[0]-��砫�� ����,
  [1]-ࠧ��� ᬥ饭��,
  [2]-�ਧ��� ��࠭���� � ���:>1- ��,2-����������,3-��।�����*/
const unsigned char main_dyn[Max_dyn][3]={
 {0,4,3},/*��९��*/      {4,4,3},/*�������� ���*/  {8,4,3},/*���������*/
 {12,4,3},/*���⭮���*/   {16,8,2},/*���室 ���ᮢ*/{24,8,2},/*���室 ����*/
 {32,8,2},/*���ࣨ�*/     {40,1,0},/*��⠫쯨�*/    {41,1,0},/*� ��⮪�*/
 {42,1,0},/*� ���७��*/{43,1,0},/*� ��������*/  {44,1,0},/*� ��客����*/
 {45,1,0},/*� ��������*/{46,1,0},/*��᫮ ������*/ {47,1,0},/*�離���� ���*/
 {48,1,0},/*�������*/    {49,1,0},/*������ �����*/ {50,1,0},/*� ��������*/
 {51,1,0},/*����.���.��.�*/{52,1,0},/*����.���.��.�*/{53,1,0}/*���ࣨ� ��.�*/
};
/*����.���.��ࠬ����[0]-��砫�� ����,[1]-������ ᬥ饭��,[2]-������ �����
[3]-������ ������,[4]-�ਧ��� �����������,[5]-�ਧ��� ����ન:1-��室��,>1-��室��
[6]-������:64-� ����⢥ �⢥�稪�,128-� ����⢥ �����稪�,192-���+��� ��
  [7]-�ਯ��,[8]-�ਧ��� ���⪨ ��ࠬ���*/
const unsigned char dyn_set[Max_dyn_massive][9]={
 {0,0,1,2,0,2,194,1,0},{4,0,2,2,0,3,194,1,0},{8,0,3,3,0,4,194,1,0},
 {12,0,4,8,0,1,194,0,0},{16,0,5,5,2,1,194,1,0},{16,1,5,13,2,0,66,0,1},
 {16,2,5,13,2,0,66,0,1},{16,3,5,13,2,0,66,0,1},{16,4,5,13,2,0,66,0,1},
 {16,5,5,13,2,0,66,0,1},{16,6,5,13,2,0,66,0,1},{24,0,6,4,2,1,66,1,0},
 {24,1,6,14,2,0,66,0,1},{24,2,6,14,2,0,66,0,1},{24,3,6,14,2,0,66,0,1},
 {24,4,6,14,2,0,66,0,1},{24,5,6,14,2,0,66,0,1},{24,6,6,14,2,0,66,0,1},
 {40,0,7,130,0,1,66,0,0},{32,0,37,129,2,0,66,1,0},{32,1,37,128,2,0,66,0,1},
 {32,2,37,128,2,0,66,0,1},{32,3,37,128,2,0,66,0,1},{32,4,37,128,2,0,66,0,1},
 {32,5,37,128,2,0,66,0,1},{32,6,37,128,2,0,66,0,1},{41,0,21,0,0,1,0,0,0},
 {42,0,22,0,0,1,0,0,0},{43,0,23,0,0,1,0,0,0},{44,0,24,0,0,1,0,0,0},
 {45,0,25,0,0,1,0,0,0},{46,0,26,0,0,1,0,0,0},{47,0,27,29,0,1,1,0,0},
 {48,0,28,10,0,1,1,0,0},{49,0,29,2,0,1,1,0,0},{50,0,30,0,0,1,1,0,0},
 {51,0,8,13,0,0,66,0,0},{52,0,9,14,0,0,66,0,0},{53,0,11,128,0,0,66,0,0},};
/*[0]-������ �����,[1]-����� ��ࠬ���,[2]-���� ��砫��
⨯ ������:��ப�-0,����-1,������� �롮�-2,����.�롮�-3,�����.�᫮-4
[3]-⨯ ������,[4]-����� ��� ����⨯���,����-128 [5]-������ ������,
  [6]-��஫� ��� ��������� �㦥�:1,2-��������� �१ MMI ����������*/
unsigned char conf_main[Max_main][7]={
 {36 /*���� �⠭樨 (0)*/,1,1,1,128,0,1},{37 /*����� �� (1)*/,1,2,1,128,0,1},
 {38 /*��ନ��� ���� (2)*/,1,3,2,128,0,1},{39 /*���� MVS #1 (3)*/,1,4,1,128,0,1},
 {40 /*���� MVS #2 (4)*/,1,5,1,128,0,1},{41 /*���� MVS #3 (5)*/,1,6,1,128,0,1},
 {42 /*���� MVS #4 (6)*/,1,7,1,128,0,1},{45 /*���� ICP #1 (7)*/,1,8,1,128,0,1},
 {46 /*���� ICP #2 (8)*/,1,9,1,128,0,1},{47 /*���� ICP #3 (9)*/,1,10,1,128,0,1},
 {48 /*���� ICP #4 (10)*/,1,11,1,128,0,1},{43 /*���/���� (11)*/,1,12,3,128,0,2},
 {10 /*���� �� (12)*/,1,13,2,128,0,1},{52 /*��� ICP #1 (13)*/,1,14,2,128,0,1},
 {53 /*��� ICP #2 (14)*/,1,15,2,128,0,1},{54 /*��� ICP #3 (15)*/,1,16,2,128,0,1},
 {55 /*��� ICP #4 (16)*/,1,17,2,128,0,1},{58 /*������ (17)*/,1,18,7,128,0,2},
 {49 /*��஫� (18)*/,4,19,5,128,0,2},{59 /*����_1 (19)*/,2,23,6,0,0,2},
 {59/*����_2 (20)*/,2,25,6,1,0,2},{59 /*����_3 (21)*/,2,27,6,2,0,2},
 {59/*����_4 (22)*/,2,29,6,3,0,2},{60 /*���_1 (23)*/,4,31,8,0,0,2},
 {60 /*���_2 (24)*/,4,35,8,1,0,2},{60 /*���_3 (25)*/,4,39,8,2,0,2},
 {60 /*���_4 (26)*/,4,43,8,3,0,2},{60 /*���_5 (27)*/,4,47,8,4,0,2},
 {60 /*���_6 (28)*/,4,51,8,5,0,2},{60 /*���_7 (29)*/,4,55,8,6,0,2},
 {60 /*���_8 (30)*/,4,59,8,7,0,2},{60 /*���_9 (31)*/,4,63,8,8,0,2},
 {60 /*���_10 (32)*/,4,67,8,9,0,2},{60 /*���_11 (33)*/,4,71,8,10,0,2},
 {60 /*���_12 (34)*/,4,75,8,11,0,2},{60 /*���_13 (35)*/,4,79,8,12,0,2},
 {60 /*���_14 (63)*/,4,83,8,13,0,2},{60 /*���_15 (37)*/,4,87,8,14,0,2},
 {60 /*���_16 (38)*/,4,91,8,15,0,2},{60 /*���_17 (39)*/,4,95,8,16,0,2},
 {60 /*���_18 (40)*/,4,99,8,17,0,2},{60 /*���_19 (41)*/,4,103,8,18,0,2},
 {60 /*���_20 (42)*/,4,107,8,19,0,2},{60 /*���_21 (43)*/,4,111,8,20,0,2},
 {60 /*���_22 (44)*/,4,115,8,21,0,2},{60 /*���_23 (45)*/,4,119,8,22,0,2},
 {60 /*���_24 (46)*/,4,123,8,23,0,2},{60 /*���_25 (47)*/,4,127,8,24,0,2},
 {60 /*���_26 (48)*/,4,131,8,25,0,2},{60 /*���_27 (49)*/,4,135,8,26,0,2},
 {60 /*���_28 (50)*/,4,139,8,27,0,2},{60 /*���_29 (51)*/,4,143,8,28,0,2},
 {60 /*���_30 (52)*/,4,147,8,29,0,2},{60 /*���_31 (53)*/,4,151,8,30,0,2},
 {60 /*���_32 (54)*/,4,155,8,31,0,2},{60 /*���_33 (55)*/,4,159,8,32,0,2},
 {60 /*���_34 (56)*/,4,163,8,33,0,2},{60 /*���_35 (57)*/,4,167,8,34,0,2},
 {60 /*���_36 (58)*/,4,171,8,35,0,2},{60 /*���_37 (59)*/,4,175,8,36,0,2},
 {60 /*���_38 (60)*/,4,179,8,37,0,2},{60 /*���_39 (61)*/,4,183,8,38,0,2},
 {60 /*���_40 (62)*/,4,187,8,39,0,2},{35 /*��� (63)*/,10,191,10,128,0,1},
 {50 /*�����.����� (64)*/,20,201,0,128,0,1},{51/*�����.������ (65)*/,10,221,10,128,0,1},
 {44/*��஫� �����(66)*/,2,231,9,128,0,1},{72/*���ᮡ �����.����(67)*/,1,233,2,128,0,1},
 {74/*��ࠡ�⪠ �ਯ�(68)*/,1,234,2,128,0,1},
};
unsigned char main_select[Max_select_main]={
  9,2,3,0,51,52,  11,2,53,54,  13,7,55,56,57,58,35,36,116,
  14,7,55,56,57,58,35,36,116, 15,7,55,56,57,58,35,36,116,
  16,7,55,56,57,58,35,36,116, 12,2,43,44,   67,2,87,88, 68,2,0,1};
/*[0]-������ �����,[1]-����� ��ࠬ���,[2]-���� ��砫��
⨯ ������:��ப�-0,����-1,������� �롮�-2,����.�롮�-3,�����.�᫮-4
[3]-⨯ ������,[4]-����� ��� ����⨯���,����-128 [5]-������ ������,
  [6]-��஫� ��� ��������� �㦥�:1,2-��������� �१ MMI ����������*/
unsigned char conf_basic[Max_conf][7]={
 {1 /*����� �窨 (0)*/,1,0,2,128,0,1},{2 /*�롮� ᥭ� (1)*/,1,1,2,128,0,1},
 {3 /*�롮� ��९ (2)*/,1,2,2,128,0,1},{4 /*�롮� ���� (3)*/,1,3,2,128,0,1},
 {5 /*�롮� ⥬���� (4)*/,1,4,2,128,0,1},{6 /*�롮� �����९ (5)*/,1,5,2,128,0,1},
 {8 /*�롮� �।� (6)*/,1,6,2,128,0,1},{75/*��ફ �஬��(7)*/,1,7,2,128,0,1},
 {9 /*�������� ���� (8)*/,4,8,4,128,22,1},
 {11 /*������� ���� (9)*/,4,12,4,128,1,1},{12 /*���� ᥭ�� (10)*/,4,16,4,128,1,1},
 {13 /*���窠 (11)*/,4,20,4,128,2,1},{16 /*������ �஬�� (12)*/,4,24,4,128,1,1},
 {17 /*���客����� (13)*/,4,28,4,128,1,1},{18 /*��� � ���� (14)*/,4,32,4,128,11,1},
 {19 /*��� � ���� (15)*/,4,36,4,128,11,1},{20 /*��� � ���� (16)*/,4,40,4,128,11,1},
 {21 /*��� � ᥭ�� (17)*/,4,44,4,128,11,1},{22 /*��� � ᥭ�� (18)*/,4,48,4,128,11,1},
 {23 /*��� � ᥭ�� (19)*/,4,52,4,128,11,1},
 {7 /*����� ���ମ� (20)*/,1,56,3,128,0,2},{14 /*������ �࠭�� (21)*/,4,57,4,128,2,1},
 {15 /*������ �࠭�� (22)*/,4,61,4,128,2,1},{24 /*��� ��� ��室� (23)*/,4,65,4,128,5,1},
 {25 /*���� ��� ��室� (24)*/,4,69,4,128,5,1},{76 /*����१ ���(25)*/,4,73,4,128,5,1},
 {26 /*��� ��� ��� (26)*/,4,77,4,128,2,1},{27 /*���� ��� ��� (27)*/,4,81,4,128,2,1},
 {28 /*����१ ��� (28)*/,4,85,4,128,2,1},{29 /*��� ��� ���� (29)*/,4,89,4,128,2,1},
 {30 /*���� ��� ���� (30)*/,4,93,4,128,2,1},{31 /*����१ ���� (31)*/,4,97,4,128,2,1},
 {32 /*��� ��� ⥬� (32)*/,4,101,4,128,3,1},{33 /*���� ��� ⥬� (33)*/,4,105,4,128,3,1},
 {34 /*����� ⥬� (34)*/,4,109,4,128,3,1},{35 /*��� �����䨪�� (35)*/,10,113,10,128,0,1},
 {100 /*������ ��� (36)*/,4,123,4,128,30,1},
 {101 /*�롮� �室� ��室 (37)*/,1,127,2,128,0,1}
};
/*��ࠬ���� �롮�:�᫮ ����஢,����� ��ࠬ���,�᫮ ��ப,����� ��ப...*/
unsigned char conf_select[Max_select]={
  10,0,2,0,1, 1,12,2,3,4,5,6,7,8,9,10,11,12,13,
  2,13,14,15,16,17,18,19,20,21,22,23,24,25,26,
  3,13,14,15,16,17,18,19,20,21,22,23,24,25,26,
  4,13,14,15,16,17,18,117,118,119,120,121,122,25,26,
  5,13,0,15,16,17,18,19,20,21,22,23,24,25,26,
  6,2,41,42, 7,2,96,97, 20,4,45,46,47,48, 37,5,0,19,20,21,22};
/*[0]-������� ����७��
  [1]-��� ���� ��ࠬ��� � ᯨ᪥ �窨
  [2]-⨯ ��娢�஢����
  [3]-��� ��ࠬ���*/
/*��९��, ��������, ⥬������, ���⭮���, ����, ����, �ࣨ�*/
const unsigned char set_archive[Max_archive][4]={
  {2,0,3,1},{2,4,3,2},{3,8,3,3},{8,12,3,4},{13,16,2,5},
  {14,24,2,6},{128,32,2,37}};
unsigned char conf_icp[Max_icp_prm][7]={
  {65,1,0,12,0,0,2},{65,1,1,12,1,0,2},{65,1,2,12,2,0,2},{65,1,3,12,3,0,2},
  {65,1,4,12,4,0,2},{65,1,5,12,5,0,2},{65,1,6,12,6,0,2},{65,1,7,12,7,0,2},
  {65,1,8,12,8,0,2},{65,1,9,12,9,0,2},{65,1,10,12,10,0,2},
  {65,1,11,12,11,0,2},{65,1,12,12,12,0,2},{65,1,13,12,13,0,2},
  {65,1,14,12,14,0,2},{65,1,15,12,15,0,2},{66,4,16,4,0,0,1},
  {66,4,20,4,1,0,1},{66,4,24,4,2,0,1},{66,4,28,4,3,0,1},{66,4,32,4,4,0,1},
  {66,4,36,4,5,0,1},{66,4,40,4,6,0,1},{66,4,44,4,7,0,1},{66,4,48,4,8,0,1},
  {66,4,52,4,9,0,1},{66,4,56,4,10,0,1},{66,4,60,4,11,0,1},{66,4,64,4,12,0,1},
  {66,4,68,4,13,0,1},{66,4,72,4,14,0,1},{66,4,76,4,15,0,1},{67,4,80,4,0,0,1},
  {67,4,84,4,1,0,1},{67,4,88,4,2,0,1},{67,4,92,4,3,0,1},{67,4,96,4,4,0,1},
  {67,4,100,4,5,0,1},{67,4,104,4,6,0,1},{67,4,108,4,7,0,1},{67,4,112,4,8,0,1},
  {67,4,116,4,9,0,1},{67,4,120,4,10,0,1},{67,4,124,4,11,0,1},
  {67,4,128,4,12,0,1},{67,4,132,4,13,0,1},{67,4,136,4,14,0,1},{67,4,140,4,15,0,1},
  {77,1,144,12,0,0,2},{77,1,145,12,1,0,2},{77,1,146,12,2,0,2},{77,1,147,12,3,0,2},
  {77,1,148,12,4,0,2},{77,1,149,12,5,0,2},{77,1,150,12,6,0,2},{77,1,151,12,7,0,2},
  {78,4,152,4,0,0,1},{78,4,156,4,1,0,1},{78,4,160,4,2,0,1},{78,4,164,4,3,0,1},
  {78,4,168,4,4,0,1},{78,4,172,4,5,0,1},{78,4,176,4,6,0,1},{78,4,180,4,7,0,1},
  {79,4,184,4,0,0,1},{79,4,188,4,1,0,1},{79,4,192,4,2,0,1},{79,4,196,4,3,0,1},
  {79,4,200,4,4,0,1},{79,4,204,4,5,0,1},{79,4,208,4,6,0,1},{79,4,212,4,7,0,1},
};
unsigned char conf_exp[Max_exp_prm][5]={
 {68,4,0,14,0},{68,4,4,14,1},{68,4,8,14,2},{68,4,12,14,3},
 {68,4,16,14,4},{68,4,20,14,5},{68,4,24,14,6},{68,4,28,14,7},
 {68,4,32,14,8},{68,4,36,14,9},{68,4,40,14,10},{68,4,44,14,11},
 {68,4,48,14,12},{68,4,52,14,13},{68,4,56,14,14},{68,4,60,14,15},
 {68,4,64,14,16},{68,4,68,14,17},{68,4,72,14,18},{68,4,76,14,19},
 {68,4,80,14,20},{68,4,84,14,21},{68,4,88,14,22},{68,4,92,14,23},
 {68,4,96,14,24},{68,4,100,14,25},{68,4,104,14,26},{68,4,108,14,27},
 {68,4,112,14,28},{68,4,116,14,29},{68,4,120,14,30},{68,4,124,14,31},
 {68,4,128,14,32},{68,4,132,14,33},{68,4,136,14,34},{68,4,140,14,35},
 {68,4,144,14,36},{68,4,148,14,37},{68,4,152,14,38},{68,4,156,14,39},
 {73,4,160,4,0},{73,4,164,4,1},{73,4,168,4,2},{73,4,172,4,3},{73,4,176,4,4},
 {73,4,180,4,5},{73,4,184,4,6},{73,4,188,4,7},{73,4,192,4,8},{73,4,196,4,9},
 {73,4,200,4,10},{73,4,204,4,11},{73,4,208,4,12},{73,4,212,4,13},
 {73,4,216,4,14},{73,4,220,4,15},{73,4,224,4,16},{73,4,228,4,17},
 {73,4,232,4,18},{73,4,236,4,19}};
struct dynparams
{
  double dyn[Max_dyn_all];
  unsigned        cnt[3];
};
struct expandparams
{
  float        dyn[256];
  unsigned     cnt[3];
};
struct configparam
{
  unsigned char status;       /*�窠 ����祭� ��� �몫�祭�*/
  unsigned char sensor;       /*�롮� ᥭ��*/
  unsigned char s_diff;       /*�롮� ���筨�� ��९���*/
  unsigned char s_press;      /*�롮� ���筨�� ��������*/
  unsigned char s_tempr;      /*�롮� ���筨�� ⥬����*/
  unsigned char stack;        /*�롮� ���筨�� ���.��९���*/
  unsigned char s_flow;       /*�롮� ���筨�� ��室�*/
  unsigned char enable_alm;   /*ࠧ���� �����*/
  unsigned char media;        /*⨯ ⥯�����⥫�*/
  unsigned char cur_sens;     /*⥪�騩 ��९��稪*/
  unsigned char s_egle;
  float         interv;       /*��������.����*/
  float         pipe_size;    /*������� ����*/
  float         sens_size;    /*������� ᥭ��*/
  float         cut_flow;     /*���窠 ���.��室�*/
  float         hi_stack;     /**/
  float         lo_stack;     /**/
  float         radius;       /*ࠤ��� �஬�� �����*/
  float         rougness;     /*��客����� ����*/
  float         ka_pipe;      /*�����樥��� �ମ���७��*/
  float         kb_pipe;
  float         kc_pipe;
  float         ka_sens;
  float         kb_sens;
  float         kc_sens;
  float         borders[4][3];/*[0]-������,[1]-���孨�,[2]-����१��*/
  float         dry_factor;
  unsigned char tag[10];
  unsigned char flag;         /*䫠� ४�����樨*/
  unsigned char status_alm[4];/*⥪�饥 ���ﭨ� ���ମ�*/
};
struct station
{
  unsigned char task;        /*⨯ �蠥��� �����*/
  unsigned char addr;        /*���� ����஫���*/
  unsigned char contrh;       /*����ࠪ�� ��*/
  unsigned char mmi;         /*�ਬ������ �ନ���� ������*/
  unsigned char adr_mvs[4];  /*���� ᥭ�஢*/
  unsigned char adr_icp[4];  /*���� ���㫥�*/
  unsigned char autogo;      /*��⮯��室 �� ��⭥�/������ �६�*/
  unsigned char units;
  unsigned char typ_icp[4];  /*⨯ �����*/
  unsigned char passw[4];       /*��஫� �� ��������� ���䨣��樨*/
  unsigned char com[4][2]; /*����ன�� ���⮢*/
  unsigned char arch[Max_arch_pnt][4];   /*����ன�� ��娢��� �祪*/
  unsigned char tag[10];
  unsigned char phone[20];
  unsigned char at[10];
  unsigned char modbus;
  unsigned char set_com;                 /*ࠧ�襭�� �� ���4*/
  unsigned      passw_op;                /*��஫� ������*/
  unsigned char script;
};
struct modbus_config
{
  unsigned char mode;        /*0-Slave, 1-Host*/
  unsigned char protocol;    /*0-ASCII, 1-RTU*/
  unsigned char connect;     /*0-�⪫, 1-���2, 2-���3, 3-���1*/
  unsigned char delay;
  unsigned char rtu;
  unsigned char rtu_2;
  unsigned char flag;
};
/*** ��⠭���� ��� ���⪠ ���ମ� ��ࠬ��� ��� ����� ��� MVS *****/
unsigned char SetClearAlarmsPrm (float borders[],unsigned char status,
				 float value,unsigned char num_pnt,
				 unsigned char num_prm)
{ /*�����: 0-��� ���ମ�, 1-������, 2-���孨�*/
  /*��砫�� ���� ����ᮢ ���ମ� � ��� : 0�320 */
  const unsigned char num_alm[4][2]={{0,1},{2,3},{4,5},{6,7}};
  unsigned char flag,cr[4],j,buf_alm[16];
  if (borders[2]<=0.0 || (borders[1]-borders[0])<=0.0) {flag=2;goto M;}
  FormateEvent(buf_alm);buf_alm[13]=num_pnt;flag=0;
  if (status == 0  && value > borders[1])
  {status=2;flag=1;buf_alm[10]=1;buf_alm[14]=num_alm[num_prm][1];} else
  if (status == 2 && value<=(borders[1]-borders[2]))
  {status=0;flag=1;buf_alm[10]=0;buf_alm[14]=num_alm[num_prm][1];} else
  if (status == 0 && value < borders[0])
  {status=1;flag=1;buf_alm[10]=1;buf_alm[14]=num_alm[num_prm][0];} else
  if (status == 1 && value>= (borders[0]+borders[2]))
  {status=0;flag=1;buf_alm[10]=0;buf_alm[14]=num_alm[num_prm][0];}
  if (flag == 1)
  {
    ConvToBynare(value,cr); memcpy(buf_alm+6,cr,4);
    WriteEvent(buf_alm,1);
    X607_Write(390,32+num_pnt*4+num_prm,status);
  }
  M:return status;
}
/******** ��⠭���� ��� ���⪠ ���ମ� �窨 ���� ***************/
void  SetClearAlarms (struct configparam *cnf,struct dynparams bs,
		      unsigned char num_pnt)
{
  unsigned char i;
  for (i=0;i<3;i++) if ((cnf->enable_alm & etl[i]) > 0)
  cnf->status_alm[i]=SetClearAlarmsPrm(cnf->borders[i],cnf->status_alm[i],
		    bs.dyn[main_dyn[i][0]],num_pnt,i);
  if ((cnf->enable_alm & etl[3]) > 0) /*��� ���ᮢ��� ��室�*/
  cnf->status_alm[3]=SetClearAlarmsPrm(cnf->borders[3],cnf->status_alm[3],
		    bs.dyn[main_dyn[4][0]],num_pnt,3);
}
/******* ���樠������ ��ࠬ��஢ ��������: �⠭�� ***********/
void InitStationStruct (struct station *dv)
{
  unsigned char i;
  dv->task=ReadEEP(7,0);dv->addr=ReadEEP(7,1);
  dv->contrh=ReadEEP(7,2);dv->mmi=ReadEEP(7,3);
  for (i=0;i<4;i++) dv->adr_mvs[i]=ReadEEP(7,4+i);
  for (i=0;i<4;i++) dv->adr_icp[i]=ReadEEP(7,8+i);
  for (i=0;i<4;i++) dv->typ_icp[i]=ReadEEP(7,14+i);
  for (i=0;i<4;i++) dv->passw[i]=ReadEEP(7,19+i);
  dv->autogo=ReadEEP(7,12);dv->units=ReadEEP(7,13);
  dv->modbus=ReadEEP(7,18);
  for (i=0;i<4;i++)
  {dv->com[i][0]=ReadEEP(7,23+i*2);dv->com[i][1]=ReadEEP(7,24+i*2);}
  for (i=0;i<10;i++) dv->tag[i]=ReadEEP(7,191+i);
  for (i=0;i<20;i++) dv->phone[i]=ReadEEP(7,201+i);
  for (i=0;i<10;i++) dv->at[i]=ReadEEP(7,221+i);
  Modbus.mode=(dv->modbus & 16) >> 4;Modbus.delay=dv->modbus & 7;
  Modbus.protocol=(dv->modbus & 8) >> 3;
  Modbus.connect=(dv->modbus & 96) >> 5;dv->set_com=ReadEEP(7,233);
  dv->passw_op=ReadEEP(7,231)*256+ReadEEP(7,232);
  dv->script=ReadEEP(7,234);
}
/******* ���樠������ ��ࠬ��஢ ��娢� *************/
unsigned char InitArchive (struct station *dv)
{
  unsigned char i,k;k=0;
  for (i=0;i<Max_arch_pnt;i++)
  {
    dv->arch[i][0]=ReadEEP(7,31+i*4);dv->arch[i][1]=ReadEEP(7,32+i*4);
    dv->arch[i][2]=ReadEEP(7,33+i*4);dv->arch[i][3]=ReadEEP(7,34+i*4);
    if (dv->arch[i][0] != 0) k++;
  } return 7+k*4;
}
/******* ���樠������ ��������:���䨣���� ⥯������ **********/
void InitBasicStruct (unsigned char num,struct configparam *cnf)
{
  unsigned char i,j,cr[4];float buf[16];
  cnf->status=ReadEEP(num,0);cnf->sensor=ReadEEP(num,1);
  cnf->s_diff=ReadEEP(num,2);cnf->s_press=ReadEEP(num,3);
  cnf->s_tempr=ReadEEP(num,4);cnf->stack=ReadEEP(num,5);
  cnf->enable_alm=ReadEEP(num,56);cnf->media=ReadEEP(num,6);
  cnf->s_egle=ReadEEP(num,7);
  for (i=0;i<12;i++)
  { /*����祭�� �᭮���� ���䨣.��ࠬ��஢*/
    j=i*4;
    ConvToFloatVerify(&buf[i],ReadEEP(num,8+j),ReadEEP(num,9+j),
		      ReadEEP(num,10+j),ReadEEP(num,11+j));
  } cnf->interv=buf[0];cnf->pipe_size=buf[1];cnf->sens_size=buf[2];
  cnf->cut_flow=buf[3];cnf->radius=buf[4];cnf->rougness=buf[5];
  cnf->ka_pipe=buf[6];cnf->kb_pipe=buf[7];cnf->kc_pipe=buf[8];
  cnf->ka_sens=buf[9];cnf->kb_sens=buf[10];cnf->kc_sens=buf[11];
  for (i=0;i<14;i++)
  { /*����祭�� ��⠢�� ��ண� ��९��稪� � ��⠢�� ���ମ�*/
    j=i*4;
    ConvToFloatVerify(&buf[i],ReadEEP(num,57+j),ReadEEP(num,58+j),
		      ReadEEP(num,59+j),ReadEEP(num,60+j));
  } cnf->hi_stack=buf[0];cnf->lo_stack=buf[1];
  for (j=0;j<3;j++) cnf->borders[3][j]=buf[2+j];
  for (i=0;i<3;i++) for (j=0;j<3;j++) cnf->borders[i][j]=buf[5+i*3+j];
  for (i=0;i<10;i++) cnf->tag[i]=ReadEEP(num,113+i);
  ConvToFloatVerify(&buf[0],ReadEEP(num,123),ReadEEP(num,124),
		      ReadEEP(num,125),ReadEEP(num,126));
  cnf->dry_factor=buf[0]/100; cnf->s_flow=ReadEEP(num,127);
}
/*********** ���᫥��� ������⥫� �������� ��� **************/
float CalcAdiabatSteam (float temper,float press)
{
  double q,y,k1,k2,k3,dy1,dy2;
  q=(temper-200)/100;k1=1.31+q*(-0.012)+q*(q-1)*0.001/2;
  k2=1.292+q*(-0.004)+q*(q-1)*(-0.002)/2;
  k3=1.282+q*(-0.003)+q*(q-1)*(-0.001)/2;y=(press-1000)/4000;
  dy1=k2-k1;dy2=k3-k2-dy1;return k1+y*dy1+y*(y-1)*dy2/2;
}
/******** �஢�ઠ �ਭ� ���㡠� � ���४�� �᫨ +- 10% *******/
unsigned char VerifyAnnubar (unsigned char tp,float *annubar)
{
  const float d[8] = {4.394,9.297,21.742,31.369,49.53,14.986,
		      26.924,48.768};/*�।��� �ਭ� ���㡠�*/
  if ((*annubar > 1.1 * d[tp])||(*annubar < 0.9 * d[tp]))
  { *annubar=d[tp];return 1;} else return 0;
}
/******** ���᫥��� �����樥�� �����஢�� ���� ***************/
float BettaKoeff (float pipe,float annubar)
 {
   return 1.273239 * annubar / pipe;
 }
/********* ���᫥��� �����樥�� ��⮪� �� ⨯� ���㡠� *******/
float AnnubarKoeff (float betta,unsigned char type)
 {
   const float c1[8] = {-0.8212,-1.3452,-1.43,-1.3416,-1.2613,-1.515,
			-1.492,-1.5856};
   const float c2[8] = {0.7269,0.92,1.265,1.2075,1.24,1.4229,1.4179,
			1.3318};
   double a,c,d; a=0.0;
   if (type == 0) a = c1[type] * betta + c2[type];
   else if (type < 8)
   {
     d = 1 - c2[type]*betta;c = d*d;c = sqrt(1 - c1[type]*c);a = d/c;
   } return a;
 }
/*** ���᫥��� �����.��⮪� �� ⨯� ����ࠣ��:䫠�楢��,㣫�� ***/
float CalcOrifNewC (float rein,float betta,float pipe,float b4,
		    unsigned char type)
{ /*������� ���� � �����*/
  double A,M1,M2,L1,L2;
  if (rein>1000)
  {
    switch (type)
    {
      case 0:L1=L2=0;break; /*㣫����*/
      case 1:L1=L2=0.0254/pipe;break;/*䫠�楢�*/
      case 2:L1=1;L2=0.47;break;/*����ࠤ����*/
    } A=pow(19000*betta/rein,0.8);M1=2*L2/(1-betta);
    if (pipe<0.07112) M2=0.011*(0.75-betta)*(2.8-pipe/0.0254);else M2=0;
    return 0.5961+0.0261*betta*betta-0.216*b4*b4+
	 0.000521*pow(1E6*betta/rein,0.7)+(0.0188+0.0063*A)*pow(betta,3.5)*
	 pow(1E6/rein,0.3)+(0.043+0.08*exp(-10*L1)-0.123*exp(-7*L1))*
	 (1-0.11*A)*b4/(1-b4)-0.031*(M1-0.8*pow(M1,1.1))*pow(betta,1.3)+M2;
  } else return 1.0;
}
/********* ���᫥��� ���ࠢ�� �� ���㯫���� �஬��**************/
/** ������� �����. � ࠤ��� � �,���������� ����.� ����� ****/
float CalcOrifNewEgle (double radius,float sensor,float interv,
		       float ps,float press,unsigned char stack)
{
  double rk,a;radius=radius/1E3;
  if (press <= ps) a=0.0002;else a=0.00019;
  if (stack == 0 && interv > 0)
     rk=a-(3.0/interv)*(a-radius)*(1-exp(-interv/3.0));
  if (stack == 1) rk=a-(a-radius)*exp(-interv/3.0);
  if ((rk <= 0.0004*sensor)||((rk/sensor+0.0007773)<0)) return 1.0;else
  return 0.9826+pow((rk/sensor+0.0007773),0.6);
}
/************ ���᫥��� �����.���७�� �� ����ࠣ�� **********/
float CalcOrifNewExpand (float diff,float press,double b4,float adiab)
{ /*��९�� � �������� � ��᪠���*/
  return 1-(0.351+0.256*b4+0.93*b4*b4)*(1-pow(1-diff/press,1/adiab));
}
/************** �믮���� ���㣫���� �� 楫��� ******************/
float RoundFloat (double value)
{
  float a,b;a=fabs(value);b=floor(a);if ((a-b)>=0.5) b=b+1;
  if (value < 0) b=-b;return b;
}
/************** ���㣫�� �� ���� ����� ࠧ�冷� **************/
float RoundToTwo (double value)
{
  int a;
  a=log10(value);
  if (a>1) value=RoundFloat(value/pow(10,a-1))*pow(10,a-1); else
  if (a>-2) value=RoundFloat(value*10)/10;else value=0.0; return value;
}
/********* ������ ���ࠢ�� �� ��客����� ���� ************/
float CalcOrifNewRougness (float rein,float betta,double pipe,
			   double rougness)
{ /*�� ࠧ���� � �����*/
  const double kf1[3][4]={{8.87,-3.7114,0.41841,0.0},
			  {6.7307,-5.5844,0.732485,0.0},
			  {-10.244,5.7094,-0.76477,0.0}};
  const double kf2[3][4]={{27.23,-11.458,1.6117,-0.07567},
			  {-25.928,12.426,-2.09397,0.106143},
			  {1.7622,-3.8765,1.05567,-0.076764}};
  const double kf3[3][4]={{16.5416,-6.60709,0.88147,-0.039226},
			  {322.594,-132.2,17.795,-0.799765},
			  {-92.029,37.935,-5.1885,0.23583}};
  const float pi=3.141592;
  double max,min,logrein,lj,lj1,kr,kd,Ash,A[3],avg;unsigned char i,k;
  float factor;
  factor=1.0;if (rein<=1000) goto M;
  logrein=log10(rein);rougness=rougness/1E3;
  for (i=0;i<3;i++) A[i]=0.0;avg=rougness/pi;
  if (rein>1E4 && rein<=1E5) for (i=0;i<3;i++) for (k=0;k<4;k++)
    A[i]=A[i]+kf1[i][k]*pow(logrein,k); else
  if (rein>1E5 && rein<=3E6) for (i=0;i<3;i++) for (k=0;k<4;k++)
    A[i]=A[i]+kf2[i][k]*pow(logrein,k); else
  if (rein>3E6 && rein<=1E8) for (i=0;i<3;i++) for (k=0;k<4;k++)
    A[i]=A[i]+kf3[i][k]*pow(logrein,k);
  if (rein<=1E4) max=0.718866*pow(betta,-3.887)+0.364; else
  if (rein>1E4 && betta<0.65) max=A[0]*pow(betta,A[1])+A[2]; else
  if (rein>1E4 && betta>=0.65) max=A[0]*pow(0.65,A[1])+A[2];
  if (max>=15) max=15*pipe/1E4;else {max=RoundToTwo(max);max=max*pipe/1E4;}
  if (rein < 3E6) min=0.0;else
  {
    if (betta<0.65) min=7.1592-12.387*betta-(2.0118-3.469*betta)*logrein+
		      (0.1382-0.23762*betta)*logrein*logrein; else
       min=-0.892353+0.24308*logrein-0.0162562*logrein*logrein;
    if (min <= 0) min=0;else {min=RoundFloat(min*1E3)/1E3;min=min*pipe/1E4;}
  }
  if (avg > max || avg < min)
  {
    Ash=rougness;kd=0.26954*rougness/pipe;kr=5.035/rein;
    lj=1.74-2*log10(2*Ash/pipe-37.36*log10(kd-kr*log10(kd+3.3333*kr))/rein);
    lj=pow(lj,-2.0);
    if (avg>max) {Ash=pi*max;kd=0.846784*max/pipe;}
    if (avg<min) {Ash=pi*min;kd=0.846784*min/pipe;}
    lj1=1.74-2*log10(2*Ash/pipe-37.36*log10(kd-kr*log10(kd+3.3333*kr))/rein);
    lj1=pow(lj1,-2.0);factor=1+5.22*pow(betta,3.5)*(lj-lj1);
  }
  M: return factor;
}
/************ ���᫥��� �����樥�� ���७�� ****************/
float YaKoeff (float betta,float diff,float press,float adiabat)
 {
   double expan;
   expan = (1 - betta) * (1 - betta) * 0.31424 - 0.09484;
   if (press > 0)
     return (1 - expan * diff / press / adiabat);else return 1.0;
 }
/*** ⥬�����ୠ� ���४�� ������� ���� �� ⨯� ���ਠ�� ****/
float ThermoCorrect (float diametr,float temper,float factor_a,
		    float factor_b,float factor_c)
{
   double fctr;
   fctr = 1E-6 *(factor_a+1E-3*temper*factor_b-
       1E-6*temper*temper*factor_c);return diametr*(1+fctr*(temper-20));
}
/******** ���᫥��� �������� ����饭�� ���ﭮ�� ��� *************/
float CalcPS (float abstemp)
{
  double t1,ksi,ksi3,pk;
  t1=abstemp/647.14;ksi=1-t1;if (ksi<0) ksi=0.0;ksi3=ksi*ksi*ksi;
  pk=(-7.85823*ksi+1.83991*pow(ksi,1.5)-11.7811*ksi3+
      22.6705*pow(ksi,3.5)-15.9393*ksi*ksi3+1.77516*pow(ksi,7.5))/t1;
  return 22064*exp(pk);
}
/************** ���᫥��� ���⭮�� ����**************************/
float CalcDensityWater (float abstemp,float press)
{
  double t1,t2,t3,t4,t5,t6,pi1,pi2,ksi,ksi3,z,value;
  t1=abstemp/647.14;t2=t1*t1;t3=t2*t1;t4=t3*t1;t5=t4*t1;t6=t5*t1;
  pi1=press/22.064/1000;pi2=pi1*pi1;
  z=114.332*t1-431.6382+706.5474/t1-641.9127/t2+349.4417/t3-
      113.8191/t4+20.5199/t5-1.578507/t6+
      pi1*(-3.117072+6.589303/t1-5.210142/t2+1.819096/t3-0.2365448/t4)+
      pi2*(-6.417443*t1+19.84842-24.00174/t1+14.21655/t2-4.13194/t3
	   +0.4721637/t4);
  if (z > 0) value=1000/z;else value=1000; return value;
}
/************** ���᫥��� ���⭮�� ���**************************/
float CalcDensitySteam (float abstemp,float press)
{
  double t1,t2,t3,t4,t5,t6,pi1,pi2,pi3,pi4,ksi,ksi3,z,value;
  t1=abstemp/647.14;t2=t1*t1;t3=t2*t1;t4=t3*t1;t5=t4*t1;t6=t5*t1;
  pi1=press/22.064/1000;pi2=pi1*pi1;pi3=pi2*pi1;pi4=pi3*pi1;
  z=1+pi1*(0.4409392/t1-1.386598/t2+1.380501/t3-0.7644377/t4)+
       pi2*(56.40548/t1-297.0161/t2+617.8258/t3-634.747/t4
	    +322.8009/t5-65.45004/t6)+
       pi3*(149.3651/t1-895.0375/t2+2123.035/t3-2488.625/t4
	    +1439.213/t5-327.7709/t6)+
       pi4*(151.1386-967.3387/t1+2478.739/t2-3178.106/t3
	    +2038.512/t4-523.2041/t5);
  if (z > 0) value=73.874969*pi1/t1/z;else value=1; return value;
}
/********** ���᫥��� �離��� ����   ************************/
float CalcViscosity (float temper)
{
  return 0.00186/(1+0.037*temper+0.000221*temper*temper)*1E3;
}
/********** ���᫥��� �離��� ���   ************************/
float CalcViscositySteam (float temper,float density)
{
  double mu,mu1,ro;
  mu1=80.4+0.407*temper;ro=density/1000;
  if (temper <= 300) mu=mu1-ro*(1858-5.9*temper);else
  mu=mu1+ro*353+ro*ro*676.5+ro*ro*ro*102.1;
  return mu/1E4;
}
/********** ���᫥��� �⠫쯨� ����      ***********************/
float CalcEntalphyWater (float abstemp,float press)
{
  double tay,tay2,tay3,tay4,pp,pp2;
  tay=abstemp/647.14;tay2=tay*tay;tay3=tay2*tay;tay4=tay3*tay;
  pp=press/22064;pp2=pp*pp;
  return 7809.096*tay-13868.72+12725.22/tay-6370.893/tay2+
	   1595.86/tay3-159.9064/tay4+pp*9.488789/tay+
	   pp2*(-148.1135*tay+224.3027-111.4602/tay+18.15823/tay2);
}
/********** ���᫥��� �⠫쯨� ��� *******************************/
float CalcEntalphySteam (float abstemp,float press)
{
  double tay,tay2,tay3,tay4,tay5,pp,pp2,pp3,pp4;
  tay=abstemp/647.14;tay2=tay*tay;tay3=tay2*tay;tay4=tay3*tay;
  tay5=tay4*tay;pp=press/22064;pp2=pp*pp;pp3=pp2*pp;pp4=pp3*pp;
  return 10258.8-20231.3/tay+24702.8/tay2-16307.3/tay3+
	   5579.31/tay4-777.285/tay5+pp*(-355.878/tay+817.288/tay2-
	   845.84/tay3)-pp2*(160.276/tay3)+
	   pp3*(-95607.5/tay+443740/tay2-767668/tay3+587261/tay4-
	   167657/tay5)+pp4*(22542.2/tay2-84140.2/tay3+104198/tay4-
	   42886.7/tay5);
}
/********* ���᫥��� ����������� ��室� ��� ���㡠� **********/
float CalcFlowRate (double pipe_m,float diff_p,float density,
		    float Ya,float Ka,float cut_flow)
{
  double flow;
  if (diff_p>=cut_flow*1000 && density>0)
  flow= 0.7853981634 * Ka * Ya * pipe_m * pipe_m * 3.6 *
	sqrt(2 * diff_p * density); else flow= 0.0; return flow;
}
/************** ���᫥��� ᪮��� ��⮪� ***********************/
float CalcVelosity (double pipe_m,float flow,float density)
{
  float value;
  if (density > 0) value=1.2732396*flow/pipe_m/pipe_m/density;
  else value=0.0;return  value;
}
/************* ���᫥��� �᫠ �������� ��� ���㡠� **********/
float CalcReinAnnubar (float sens_m,float velosity,float density,
		       float visc)
{
  float value;
  if (visc > 0) value=sens_m*velosity*density/visc;else value=0;
  return value;
}
/*****************************************************************/
/******** ���᫥��� ��� ��ࠬ��஢ ��室� *********************/
  /*0-��९��*/       /*4-�������� ���*/   /*8-���������*/
  /*12-���⭮���*/     /*16-���室 ���ᮢ*/  /*24-���室 ����*/
  /*40-��⠫쯨�*/     /*32-���ࣨ� �����*/
  /*41-� ��⮪�*/
  /*42-� ���७��*/  /*43-� ��������*/  /*44-� ��客����*/
  /*45-� ��������*/  /*46-��᫮ ������*/ /*47-�離���� ���*/
  /*48-�������*/      /*49-������ �����*/ /*50-� ��������*/
/******************************************************************/
unsigned char CalcFlowMain (struct configparam Prm,struct dynparams *Bs)
 {
    double pipe_m,sens_m,b4;
    float tabs,B,d_pa,E,c_10e6,ru_10e6,re_zvz,re_new,c_new,ru_new,p_pa;
    float d_water,d_steam,e_water,e_steam;
    unsigned char result,media,step;
    result=0;
    if ((Prm.pipe_size<=0)||(Prm.sens_size<=0)) if (Prm.sensor<11) result=1;
    if ((Bs->dyn[4]<=0)||(Bs->dyn[8]<=0)||(Bs->dyn[4]>=5500)||
       (Bs->dyn[0]>=101)||(Bs->dyn[8]>500))  result=result+4;
    if (result>0) {Bs->dyn[16]=Bs->dyn[24]=0;goto M;}
    tabs=Bs->dyn[8]+273.15; d_pa=Bs->dyn[0]*1E3; p_pa=Bs->dyn[4]*1E3;
    if ((Prm.sensor>2)&&(Prm.sensor<11))
       if (VerifyAnnubar (Prm.sensor-3,& Prm.sens_size)==1) result=result+8;
    Bs->dyn[49]=CalcPS(tabs);
    Prm.pipe_size= ThermoCorrect(Prm.pipe_size,Bs->dyn[8],Prm.ka_pipe,
			       Prm.kb_pipe,Prm.kc_pipe);
    Prm.sens_size= ThermoCorrect(Prm.sens_size,Bs->dyn[8],Prm.ka_sens,
			       Prm.kb_sens,Prm.kc_sens);
    pipe_m=Prm.pipe_size/1E3;
    d_water=CalcDensityWater(tabs,Bs->dyn[49]+0.1);
    d_steam=CalcDensitySteam(tabs,Bs->dyn[49]-0.1);
    e_steam=CalcEntalphySteam(tabs,Bs->dyn[49]-0.1);
    e_water=CalcEntalphyWater(tabs,Bs->dyn[49]+0.1);
    if (Bs->dyn[4]<Bs->dyn[49])
    {
      media=1;
      Bs->dyn[50]=CalcAdiabatSteam(Bs->dyn[8],Bs->dyn[4]);
      Bs->dyn[47]=CalcViscositySteam(Bs->dyn[8],Bs->dyn[12]);
      Bs->dyn[40]=CalcEntalphySteam(tabs,Bs->dyn[4]);
      Bs->dyn[12]=CalcDensitySteam(tabs,Bs->dyn[4]);
    } else if ((Bs->dyn[4]*0.95)<=Bs->dyn[49])
    {
      Bs->dyn[47]=0.0153;
      if (Prm.dry_factor>=0 && Prm.dry_factor<1)
      {
	Bs->dyn[12]=d_steam/(d_steam/d_water*(1-Prm.dry_factor)+
		    Prm.dry_factor);
	Bs->dyn[40]=e_steam*Prm.dry_factor+e_water*(1-Prm.dry_factor);
      } else
      { Bs->dyn[12]=d_steam; Bs->dyn[40]=e_steam;}
      media=1; Bs->dyn[50]=1.3;
    } else
    {
      Bs->dyn[40]=CalcEntalphyWater(tabs,Bs->dyn[4]);
      Bs->dyn[12]=CalcDensityWater(tabs,Bs->dyn[4]);
      Bs->dyn[47]=CalcViscosity(Bs->dyn[8]);Bs->dyn[50]=0;media=0;
    }
    if (media != Prm.media) result=(result & 0xb)+2;
    if (Prm.sensor==11)                   /*���᫥��� ����.��室� ��� ����.*/
    {
      Bs->dyn[16]=Bs->dyn[24]*Bs->dyn[12]/1E3;
    } else
    if ((Prm.sensor>2)&&(Prm.sensor<11))
    {
       B= BettaKoeff(Prm.pipe_size,Prm.sens_size);
       Bs->dyn[41]= AnnubarKoeff(B,Prm.sensor-3);
       if (Bs->dyn[4]*0.95<=Bs->dyn[49])
       Bs->dyn[42]= YaKoeff(B,Bs->dyn[0],Bs->dyn[4],Bs->dyn[50]);else
       Bs->dyn[42]=1.0;
       Bs->dyn[16]= CalcFlowRate(pipe_m,d_pa,Bs->dyn[12],Bs->dyn[42],
				 Bs->dyn[41],Prm.cut_flow);
       Bs->dyn[48]=CalcVelosity(pipe_m,Bs->dyn[16]/3.6,Bs->dyn[12]);
       Bs->dyn[46]=CalcReinAnnubar(Prm.sens_size,Bs->dyn[48],
				   Bs->dyn[12],Bs->dyn[47]);
    } else
    if (Prm.sensor<3 && Bs->dyn[0]>=Prm.cut_flow && Bs->dyn[12]>0)
    {
       B=Prm.sens_size/Prm.pipe_size;
       if ((B > 0.75)||(B < 0.2)) {result=result+8;goto M;} b4=B*B*B*B;
       sens_m=Prm.sens_size/1E3;E=1/sqrt(1-b4);
       Bs->dyn[43]=CalcOrifNewEgle(Prm.radius,sens_m,Prm.interv,Bs->dyn[49],Bs->dyn[4],
		       Prm.s_egle);
       if (Bs->dyn[4]<=Bs->dyn[49])
       Bs->dyn[42]=CalcOrifNewExpand (d_pa,p_pa,b4,Bs->dyn[50]);else
       Bs->dyn[42]=1;
       c_10e6=CalcOrifNewC(1E6,B,pipe_m,b4,Prm.sensor);
       ru_10e6=CalcOrifNewRougness(1E6,B,pipe_m,Prm.rougness);
       re_zvz=c_10e6*ru_10e6*sens_m*Prm.sens_size*E*Bs->dyn[43]*
	    Bs->dyn[42]*sqrt(2*d_pa*Bs->dyn[12])/Prm.pipe_size/
	    (Bs->dyn[47]/1E3);re_new=re_zvz;step=1;
       M2:c_new=CalcOrifNewC(re_new,B,pipe_m,b4,Prm.sensor);
       ru_new=CalcOrifNewRougness(re_new,B,pipe_m,Prm.rougness);
       Bs->dyn[46]=c_new*ru_new*re_zvz/c_10e6/ru_10e6;
       if (Bs->dyn[46]>1000)
       if (fabs((Bs->dyn[46]-re_new)/Bs->dyn[46]) > 1E-4) if (step<=5)
       {re_new=Bs->dyn[46];step++;goto M2;}
       Bs->dyn[45]=0;Bs->dyn[44]=ru_new;Bs->dyn[41]=c_new*E;
       Bs->dyn[16]=2.82743337*sens_m*sens_m*Bs->dyn[41]*Bs->dyn[44]*
		   Bs->dyn[43]*Bs->dyn[42]*sqrt(2*d_pa*Bs->dyn[12]);
       Bs->dyn[48]=CalcVelosity(pipe_m,Bs->dyn[16]/3.6,Bs->dyn[12]);
    }
    if (Bs->dyn[12]>0) Bs->dyn[24]=Bs->dyn[16]*1E3/(Bs->dyn[12]);
   M: return result;
}
/******** �ନ஢���� ��娢��� ����� �� ⨯� ��娢� � �窠� ***/
unsigned char FormateArchive (struct station dv,struct dynparams bs[],
			  unsigned char typ_arc,unsigned char buf[],
			  struct expandparams exp)
{
  unsigned char i,j,ind_pnt,cr[4];float value;ind_pnt=0;
 /* printf(" begin "); */
  for (i=0;i<Max_arch_pnt;i++)
  if (dv.arch[i][0] !=0 && dv.arch[i][1]<4 && dv.arch[i][3]<7)
  {
    /*printf(" point %d %d %d %d",dv.arch[i][0],dv.arch[i][1],dv.arch[i][2],dv.arch[i][3]);*/
    value=0.0;
    switch (dv.arch[i][0])
    { case 1:if (dv.arch[i][2]<Max_dyn_all)
	     switch (dv.arch[i][3])
	     {
	       case 1:value=bs[dv.arch[i][1]].dyn[dv.arch[i][2]];break;
	       case 2:
	       switch (typ_arc)
	       {
		 case 0:value=bs[dv.arch[i][1]].dyn[dv.arch[i][2]+2];break;
		 case 1:value=bs[dv.arch[i][1]].dyn[dv.arch[i][2]+1];break;
		 case 2:value=bs[dv.arch[i][1]].dyn[dv.arch[i][2]+7];break;
	       } break;
	       case 3:
		 value=bs[dv.arch[i][1]].dyn[dv.arch[i][2]+typ_arc+1];break;
	       case 4: case 6:
		 value=bs[dv.arch[i][1]].dyn[dv.arch[i][2]+dv.arch[i][3]];break;
	     } break;
      case 2:switch (dv.arch[i][3])
	     {
	       case 1:value=exp.dyn[dv.arch[i][2]];break;
	       case 2:
	       switch (typ_arc)
	       {
		 case 0:value=exp.dyn[dv.arch[i][2]+2];break;
		 case 1:value=exp.dyn[dv.arch[i][2]+1];break;
		 case 2:value=exp.dyn[dv.arch[i][2]+7];break;
	       } break;
	       case 3:
		 value=exp.dyn[dv.arch[i][2]+typ_arc+1];break;
	       case 4: case 6:
		 value=exp.dyn[dv.arch[i][2]+dv.arch[i][3]];break;
	     }
	     break;
    } ConvToBynare(value,cr);
      for (j=0;j<4;j++) buf[7+ind_pnt*4+j]=cr[j];ind_pnt++;
  } return ind_pnt;
}