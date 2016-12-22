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
typedef pair<int,string> PIS;   //存储二元组 

const int MAXLEN = 10000;   // 代码行数最大值 
const int LINEMAXLEN = 255; //代码每行字符数最大值 
const int WORDMAXLEN = 15;  //每个单词符号字符最大值 
const int PRECISION = 15;   //小数点精确位数 


void get_outname(string inputname, string &outputname); //得到输出文件名 

bool note_process(string &str, bool &noteflag,string &errmsg);  //预处理,删除字符串内注释 

void print_to_file(string outputname ,vector<PIS> vTable);  //将二元组输入到中间文件中
 
bool is_terminal_stage(int stage); //判断是否为终结阶段

int character_type(char ch); //判断当前字符的类型

void add_pair(string str, vector<PIS> &vTable);  //将得到的合法字符串加入到二元式序列中

bool excute( int &stage, char ch ); //阶段转换

bool lineAnalyse( string &line, int &colNo, string &errmsg, vector<PIS> &vTable ); //行代码词法分析

void errMsg( string filename, int rowNo,string errmsg );

bool stage_0 ( int &stage, int chtype );//(*从0-15共16个状态)
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
