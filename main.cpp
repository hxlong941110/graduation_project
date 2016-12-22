#include "lexer.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int main(int argc, char** argv) {
	
	string errmsg=""; //�洢������Ϣ
	string line;   //�洢�д��� 
	string outputname; //�м��ļ������ 
    string inputname="test.txt";  //�����ļ��� 
    bool noteflag=false;//��־���д����Ƿ����ڶ���ע���� 
    bool flag=true;  //��־��ȷ��ȡ 
    vector<PIS> vTable;
    get_outname(inputname,outputname); //��ȡ�м��ļ���
	//�򿪴����ļ� 
    ifstream icin;
    icin.open(inputname);
    int rowNo=0;
    //��ȡ���� 
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


