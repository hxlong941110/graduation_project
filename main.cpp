#include "lexer.h"
#include<fstream>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int main(int argc, char** argv) {
	
	string errmsg; //�洢������Ϣ
	string line;   //�洢�д��� 
	string outputname; //�м��ļ������ 
    string inputname="test.txt";  //�����ļ��� 
    bool noteflag=false;//��־���д����Ƿ����ڶ���ע���� 
    
    get_outname(inputname,outputname); //��ȡ�м��ļ���
    
	//�򿪴����ļ� 
    ifstream icin;
    icin.open(inputname);
    
    //��ȡ���� 
    while(!icin.eof())
    {
    	getline(icin,line);
    	if(note_process(line,noteflag,errmsg)){
    		if(!line.empty())
    			cout<<line<<endl;
		}
    		
    	else{
    		cout<<"������Ϣ:"<<errmsg<<endl;
    		break;
		}
    		
	}
    icin.close();
	return 0;
}


