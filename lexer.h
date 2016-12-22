#ifndef LEXER
#define LEXER
 
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include <cstring>
#include <algorithm>
#include<fstream>
#include <cstdio>

using namespace	std;
typedef pair<int,string> PIS;   //�洢��Ԫ�� 

const int MAXLEN = 10000;   // �����������ֵ 
const int LINEMAXLEN = 255; //����ÿ���ַ������ֵ 
const int WORDMAXLEN = 15;  //ÿ�����ʷ����ַ����ֵ 
const int PRECISION = 15;   //С���㾫ȷλ�� 


void get_outname(string inputname, string &outputname); //�õ�����ļ��� 

bool note_process(string &str, bool &noteflag,string &errmsg);  //Ԥ����,ɾ���ַ�����ע�� 

void print_to_file(string outputname ,vector<PIS> vTable);  //����Ԫ�����뵽�м��ļ���
 
bool is_terminal_stage(int stage); //�ж��Ƿ�Ϊ�ս�׶�

int character_type(char ch); //�жϵ�ǰ�ַ�������

void add_pair(string str, vector<PIS> &vTable);  //���õ��ĺϷ��ַ������뵽��Ԫʽ������

bool excute( int &stage, char ch ); //�׶�ת��

bool lineAnalyse( string &line, int &colNo, string &errmsg, vector<PIS> &vTable ); //�д���ʷ�����

void errMsg( string filename, int rowNo,string errmsg );

bool stage_0 ( int &stage, int chtype );//(*��0-15��16��״̬)
bool stage_1 ( int &stage, int chtype );
bool stage_2 ( int &stage, int chtype );
bool stage_3 ( int &stage, int chtype );
bool stage_4 ( int &stage, int chtype );
bool stage_5 ( int &stage, int chtype );
bool stage_6 ( int &stage, int chtype );
bool stage_7 ( int &stage, int chtype );
bool stage_8 ( int &stage, int chtype );
bool stage_9 ( int &stage, int chtype );
bool stage_10( int &stage, int chtype );
bool stage_11( int &stage, int chtype );
bool stage_12( int &stage, int chtype );
bool stage_13( int &stage, int chtype );
bool stage_14( int &stage, int chtype );
bool stage_15( int &stage, int chtype );

 
 



 

#endif
