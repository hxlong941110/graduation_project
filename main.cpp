#include "lexer.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int main(int argc, char** argv) {
	
	string errmsg=""; //存储错误信息
	string line;   //存储行代码 
	string outputname; //中间文件输出名 
    string inputname="test.txt";  //代码文件名 
    bool noteflag=false;//标志该行代码是否是在多行注释中 
    bool flag=true;  //标志正确读取 
    vector<PIS> vTable;
    get_outname(inputname,outputname); //获取中间文件名
	//打开代码文件 
    ifstream icin;
    icin.open(inputname);
    int rowNo=0;
    //读取代码 
    while(getline(icin,line)&&flag){
    	int colNo = 0;
    	++rowNo;
    	if(note_process(line,noteflag,errmsg)&&line.size()>0){
			cout << line << endl;
    		if(!line.empty() && !lineAnalyse( line, colNo, errmsg, vTable ) )
				flag=false;
		}
		else if (line.size()>0)
			flag = false;
			
	}
    icin.close();
    print_to_file(outputname,vTable);
	if (flag)
		cout << "program ok" << endl;
	else
		errMsg(inputname, rowNo, errmsg);
	system("pause");
	return 0;
}


