//******************************************************************************
//
//  Author(s)...: Pashgan    http://ChipEnable.Ru   
//
//  Target(s)...: �����
//
//  Compiler....: �����
//
//  Description.: ������������� ������� ��������� ����������
//
//  Data........: 12.10.2011
//
//******************************************************************************
#ifndef KEYBOARD_H
#define KEYBOARD_H

//������ ��� ��������� ������������*********************************************

//�������� ������� ����������������
#ifndef F_CPU
#define F_CPU 1000000
#endif

//���������� ��� ����������
//���� ���������������� ��� �������
//����� ������ ���������� 3�4
#define KEYBOARD_4X4

//������������ �� ����� ����
//���� ���������������� - �� ��������� ������
//�� ����� ����������� ����� ������� ����������
//� ����������������� �����
//#define COMMON_BUS

//����, � �������� �����. ������
#define PORTX_ROW PORTD
#define PINX_ROW  PIND
#define DDRX_ROW  DDRD

//����, � �������� �����. �������
#define PORTX_COL PORTD
#define PINX_COL  PIND
#define DDRX_COL  DDRD

//������ ��, � ������� ���������� 
//������ ��������� ����������
#define PIN_ROW1 0
#define PIN_ROW2 1
#define PIN_ROW3 2
#define PIN_ROW4 3

//������ ��, � ������� ����������
//������� ��������� ����������
#define PIN_COL1 4
#define PIN_COL2 5
#define PIN_COL3 6
#define PIN_COL4 7

//���� ������
#define EVENT_NULL 0
#define EVENT_KEY0 '0'
#define EVENT_KEY1 '1'
#define EVENT_KEY2 '2'
#define EVENT_KEY3 '3'
#define EVENT_KEY4 '4'
#define EVENT_KEY5 '5'
#define EVENT_KEY6 '6'
#define EVENT_KEY7 '7'
#define EVENT_KEY8 '8'
#define EVENT_KEY9 '9'
#define EVENT_KEYA 'a'
#define EVENT_KEYB 'b'
#define EVENT_KEYC 'c'
#define EVENT_KEYD 'd'
#define EVENT_KEYZ 'e'
#define EVENT_KEYR 'f'

//���������������� �������******************************************************

void KEYB_Init(void);                  //�������������
void KEYB_ScanKeyboard(void);          //������������ ����������
unsigned char KEYB_GetKey(void);       //����� ��� ������� ������

#endif //KEYBOARD_H