#include "lexer.h"
void get_outname(string inputname, string &outputname) //�õ�����ļ��� 
{
	string::size_type position = inputname.find(".");
	outputname = inputname.substr(0, position) + ".lexer";
} 
bool note_process(string &str, bool &noteflag,string &errmsg)  //Ԥ����,ɾ���ַ�����ע�� 
{
   	int p1=str.find("//");
   	int p2=str.find("/*");
   	int p3=str.find("*/");
   	if(noteflag){ //���ڶ���ע���� 
   		if(p3==-1){
   			str="";
		}
   		else{  //��ʾ���д����д���"*/" 
		 	noteflag=false; //��־����Ĵ��벻���ڶ���ע����
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
		    	noteflag=true; //��־����Ĵ������ڶ���ע����
				str=str.substr(0,p2);	
			}
			else{ //��Ҫһ��Ҫ�Ӹ��ո� ����/**/�滻�ɿո� 
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
