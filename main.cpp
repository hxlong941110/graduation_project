#include "lexer.h"
#include<fstream>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int main(int argc, char** argv) {
	
	string errmsg; //存储错误信息
	string line;   //存储行代码 
	string outputname; //中间文件输出名 
    string inputname="test.txt";  //代码文件名 
    bool noteflag=false;//标志该行代码是否是在多行注释中 
    
    get_outname(inputname,outputname); //获取中间文件名
    
	//打开代码文件 
    ifstream icin;
    icin.open(inputname);
    
    //读取代码 
    while(!icin.eof())
    {
    	getline(icin,line);
    	if(note_process(line,noteflag,errmsg)){
    		if(!line.empty())
    			cout<<line<<endl;
		}
    		
    	else{
    		cout<<"错误信息:"<<errmsg<<endl;
    		break;
		}
    		
	}
    icin.close();
	return 0;
}


