#include "lexer.h"
void get_outname(string inputname, string &outputname) //得到输出文件名 
{
	string::size_type position = inputname.find(".");
	outputname = inputname.substr(0, position) + ".lexer";
} 
bool note_process(string &str, bool &noteflag,string &errmsg)  //预处理,删除字符串内注释 
{
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
