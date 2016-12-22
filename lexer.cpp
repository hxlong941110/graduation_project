#include "lexer.h"

void get_outname(string inputname, string &outputname){ //得到输出文件名 
	
	string::size_type position = inputname.find(".");
	outputname = inputname.substr(0, position) + ".lexer";
} 

bool note_process(string &str, bool &noteflag,string &errmsg){  //预处理,删除字符串内注释 
	
	int p1=str.find("//");
   	int p2=str.find("/*");
   	int p3=str.find("*/");
   	if(noteflag){ //处于多行注释中 
   		if(p3==-1){
   			str="";
		}
   		else{  //表示该行代码中存在"*/" 
		 	noteflag=false; //标志后面的代码不属于多行注释中
			str=str.substr(p3+2);	   
		}			
	}
	else{
		  int minp=str.size();
		  if(~p1) minp=min(minp,p1);
		  if(~p2) minp=min(minp,p2);
		  if(~p3) minp=min(minp,p3);
		  if(minp==p3){
		  	errmsg=" \" */ \" cannot be matched";
		  	return false;
		  }
		  else if(minp==p2){
		    if(p3==-1){
		    	noteflag=true; //标志后面的代码属于多行注释中
				str=str.substr(0,p2);	
			}
			else{ //主要一定要加个空格 即将/**/替换成空格 
				str=str.substr(0,p2)+" "+str.substr(p3+2);	
				if(!note_process(str,noteflag,errmsg))
					return false;
				
			}
		  }
		  else if(minp==p1)
		  	str=str.substr(0,p1);
	}
	return true;
}

void print_to_file(string outputname ,vector<PIS> vTable){  //将二元组输入到中间文件中
	   ofstream outfile;
	   outfile.open(outputname);
	   if(outfile){
		   	for(auto c : vTable){
		   		outfile<<"("<<c.first<<" , "<<c.second<<")"<<endl;
		    }
		    outfile.close();
	   }
	   return;	
}
bool is_terminal_stage(int stage){ //判断是否为终结阶段

	if(stage==0||stage==4||stage==5||stage==11||stage==12||stage==14)
		return false;
	return true;
}

int character_type(char ch){ //判断当前字符的类型
		
	if(ch=='\t' || ch==' ' ||ch=='\n')	
		return 0;
	switch(ch){
		case '+':return 1;break;
		case '-':return 2;break;
		case '*':return 3;break;
		case '/':return 4;break; 
		case '%':return 5;break;
		case '>':return 6;break;
		case '<':return 7;break;
		case '=':return 8;break;
		case '!':return 9;break;
		case '&':return 10;break;
		case '|':return 11;break;
		case ',':return 12;break;
		case '(':return 13;break;
		case ')':return 14;break;
		case '{':return 15;break;
		case '}':return 16;break;
		case ';':return 17;break;
		case '.':return 18;break;
		default:break;
	}
	if('0'<=ch && ch<='9') return 19+ch-'0';
	if('a'<=ch && ch<='z') return 29+ch-'a';
	if('A'<=ch && ch<='Z') return 55+ch-'A';
	return -1;		
}
/***********************************************
	+	1		&&	15		}		29
	-	2		||	16		;		30
	*	3		<<	17		void	31
	/	4		>>	18		int		32
	%	5		=	19		main	33
	++	6		+=	20		double	34
	--	7		-=	21		if		35
	>	8		*=	22		else	36
	<	9		/=	23		for		37
	==	10		%=	24		do		38
	>=	11		,	25		while	39
	<=	12		(	26		标识符	40
	!=	13		)	27		整数	41
	!	14		{	28		小数	42 
************************************************/

void add_pair(string str, vector<PIS> &vTable){  //将得到的合法字符串加入到二元式序列中
	if(str=="+") vTable.push_back(make_pair(1,str));
	else if(str=="-") vTable.push_back(make_pair(2,str));
	else if(str=="*") vTable.push_back(make_pair(3,str));
	else if(str=="/") vTable.push_back(make_pair(4,str));
	else if(str=="%") vTable.push_back(make_pair(5,str));
	else if(str=="++") vTable.push_back(make_pair(6,str));
	else if(str=="--") vTable.push_back(make_pair(7,str));
	else if(str==">") vTable.push_back(make_pair(8,str));
	else if(str=="<") vTable.push_back(make_pair(9,str));
	else if(str=="==") vTable.push_back(make_pair(10,str));
	else if(str==">=") vTable.push_back(make_pair(11,str));
	else if(str=="<=") vTable.push_back(make_pair(12,str));
	else if(str=="!=") vTable.push_back(make_pair(13,str));
	else if(str=="!") vTable.push_back(make_pair(14,str));
	else if(str=="&&") vTable.push_back(make_pair(15,str));
	else if(str=="||") vTable.push_back(make_pair(16,str));
	else if(str=="<<") vTable.push_back(make_pair(17,str));
	else if(str==">>") vTable.push_back(make_pair(18,str));
	else if(str=="=") vTable.push_back(make_pair(19,str));
	else if(str=="+=") vTable.push_back(make_pair(20,str));
	else if(str=="-=") vTable.push_back(make_pair(21,str));
	else if(str=="*=") vTable.push_back(make_pair(22,str));
	else if(str=="/=") vTable.push_back(make_pair(23,str));
	else if(str=="%=") vTable.push_back(make_pair(24,str));
	else if(str==",") vTable.push_back(make_pair(25,str));
	else if(str==")") vTable.push_back(make_pair(26,str));
	else if(str=="(") vTable.push_back(make_pair(27,str));
	else if(str=="{") vTable.push_back(make_pair(28,str));
	else if(str=="}") vTable.push_back(make_pair(29,str));
	else if(str==";") vTable.push_back(make_pair(30,str));
	else if(str=="void") vTable.push_back(make_pair(31,str));
	else if(str=="int") vTable.push_back(make_pair(32,str));
	else if(str=="main") vTable.push_back(make_pair(33,str));
	else if(str=="double") vTable.push_back(make_pair(34,str));
	else if(str=="if") vTable.push_back(make_pair(35,str));
	else if(str=="else") vTable.push_back(make_pair(36,str));
	else if(str=="for") vTable.push_back(make_pair(37,str));
	else if(str=="do") vTable.push_back(make_pair(38,str));
	else if(str=="while") vTable.push_back(make_pair(39,str));
	else if(('a'<=str[0] && str[0]<='z')||('A'<=str[0] && str[0]<='Z')){
			vTable.push_back(make_pair(40,str));
	} 
	else if(!str.find(".")){
		vTable.push_back(make_pair(41,str));
	} 
	else{
		vTable.push_back(make_pair(42,str));
	}
	return; 			
}

bool excute( int &stage, char ch ){ //阶段转换
 	 int chtype=character_type(ch);
 	 bool flag=true;
 	 switch(stage){
 	 	case 0:flag=stage_0(stage,chtype);break;
 	 	case 1:flag=stage_1(stage,chtype);break;
 	 	case 2:flag=stage_2(stage,chtype);break;
 	 	case 3:flag=stage_3(stage,chtype);break;
 	 	case 4:flag=stage_4(stage,chtype);break;
 	 	case 5:flag=stage_5(stage,chtype);break;
 	 	case 6:flag=stage_6(stage,chtype);break;
 	 	case 7:flag=stage_7(stage,chtype);break;
 	 	case 8:flag=stage_8(stage,chtype);break;
 	 	case 9:flag=stage_9(stage,chtype);break;
 	 	case 10:flag=stage_10(stage,chtype);break;
 	 	case 11:flag=stage_11(stage,chtype);break;
 	 	case 12:flag=stage_12(stage,chtype);break;
 	 	case 13:flag=stage_13(stage,chtype);break;
 	 	case 14:flag=stage_14(stage,chtype);break;
 	 	case 15:flag=stage_15(stage,chtype);break;
 	 	default:return false;
	  }
	  return flag;
}

bool lineAnalyse( string &line, int &colNo, string &errmsg, vector<PIS> &vTable ){//行代码词法分析
	  int len=line.size(); //行语句的长度 
	  int stage=0;    //状态初始值 
	  int per_col=0; //存储访问字符的开始位置 
	  string str=""; //存储字符 
	  bool flag=true;
	  while(colNo<len){
	  	per_col=colNo; 
		stage=0;
		str="";
		while(colNo<len && colNo-per_col+1<=WORDMAXLEN){
			flag=excute(stage,line[colNo]); //进行状态转换 
			if(!flag) break;  //如果不能读入字符，则退出
			if (character_type(line[colNo]) > 0) //判断读入的字符是否是空格或者Tab
				str += line[colNo];
			colNo++;
		}
		if(!is_terminal_stage(stage)){
			if (str.size() == 0) str+= line[colNo];
			errmsg = "\""+str +"\""+ " is illegal.";
			return false;
		}
		add_pair(str,vTable);   
	  }
	  return true;
}

void errMsg( string filename, int rowNo,string errmsg ) { //输出错误原因
	cout << filename << ":第" << rowNo << "行:error:" << errmsg << endl;
    return ;
}
bool stage_0 ( int &stage, int chtype ){//(*从0-15共16个状态)
	if(chtype==0) stage=0;
	else if(chtype==3||chtype==4||chtype==5||chtype==8||chtype==9)
		stage=1;
	else if(chtype==6) stage=2;
	else if(chtype==7) stage=3;
	else if(chtype==10) stage=4;
	else if(chtype==11) stage=5;
	else if (29 <= chtype && chtype <= 80) stage = 6;  
	else if (chtype == 1)  stage = 7;
	else if (chtype == 2)  stage = 8;
	else if (19 <= chtype && chtype <= 28) stage = 9;
	else if (chtype == 18) stage = 14;
	else if (12 <= chtype && chtype <= 17) stage = 15;
	else return false;
	return true;
}

bool stage_1 ( int &stage, int chtype ){
	if(chtype==8) stage=15;
	else return false;
	return true;
}

bool stage_2 ( int &stage, int chtype ){
	if(chtype==6||chtype==8) stage=15;
	else return false;
	return true;
}

bool stage_3 ( int &stage, int chtype ){
	if(chtype==7||chtype==8) stage=15;
	else return false;
	return true;
}
bool stage_4 ( int &stage, int chtype ){
	if(chtype==10) stage=15;
	else return false;
	return true;
}
bool stage_5 ( int &stage, int chtype ){
	if(chtype==1) stage=15;
	else return false;
	return true;
}
bool stage_6 ( int &stage, int chtype ){
	if(19<=chtype && chtype<=80) stage=6;
	else return false;
	return true;
}
bool stage_7 ( int &stage, int chtype ){
	if(chtype==1 || chtype==8) stage=15;
	else return false;
	return true;
}
bool stage_8 ( int &stage, int chtype ){
	if(chtype==2 || chtype==8) stage=15;
	else return false;
	return true;
}
bool stage_9 ( int &stage, int chtype ){
	if (chtype == 33 || chtype == 59) stage = 11;
	else if (chtype == 18) stage = 10;
	else if (19 <= chtype && chtype <= 28) stage = 9;
	else return false;
	return true;
}
bool stage_10(int &stage, int chtype) {
	if (chtype == 33 || chtype == 59) stage = 11;
	else if (19 <= chtype && chtype <= 28) stage = 10;
	else return false;
	return true;
}
bool stage_11(int &stage, int chtype) {
	if (19 <= chtype && chtype <= 28) stage = 13;
	else if (chtype == 1 || chtype == 2) stage = 12;
	else return false;
	return true;
}
bool stage_12(int &stage, int chtype) {
	if (19 <= chtype && chtype <= 28) stage = 13;
	else return false;
	return true;
}
bool stage_13(int &stage, int chtype) {
	if (19 <= chtype && chtype <= 28) stage = 13;
	else return false;
	return true;
}
bool stage_14(int &stage, int chtype) {
	if (19 <= chtype && chtype <= 28) stage = 10;
	else return false;
	return true;
}
bool stage_15(int &stage, int chtype) {
	return false;
}






