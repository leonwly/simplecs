#include <iostream>
#include <unistd.h>
#include "LogInterface.h"
using namespace std;

void logMsg(int i){
			string s="hello,log";
			s=s+" from thread"+IntToStr(i);
			Log(DBLog,FATAL,s);
			Log(LanuchLog,ERROR,s);
			Log(RegitLog,WARN,s);
			Log(UpdatePasswdLog,INFO,s);
			Log(ResultLog,DEBUG,s);
			Log(GetResultLog,DEBUG,s);

}

int main(){
			vector<thread> ths;
			for(int i=0;i<10;i++){
				ths.push_back(thread{logMsg,i});
			}
			for(auto &t:ths)
				t.join();
			LogFileClose();
			cout<<"log end!"<<endl;
			exit(0);
}
