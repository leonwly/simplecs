#ifndef LOG_H_
#define LOG_H_

#include <iostream>
#include <fstream>
#include "Func.h"
#include "LogConstant.h"
using namespace std;

class Logger{

private:
	string dbFile="../log/dbLog";
	ofstream dbLog;

	string regitFile="../log/regitLog";
	ofstream regitLog;
 
	string updatePasswdFile="../log/updatePasswdLog";
	ofstream updatePasswdLog;
	
	Logger(){
		Init();
	}
	void Init(){
		dbLog.open(dbFile.c_str());
		regitLog.open(regitFile.c_str());
		updatePasswdLog.open(updatePasswdFile.c_str());
	}
	Logger(Logger&)=delete;
	static Logger *instance;

public:
	static Logger *GetInstance(){
		if(nullptr==instance)	
			instance=new Logger();
		return instance;
	}	
	void Log(LogType type,Level level,string msg){
		string time=GetTimeNow();
		
		if(FATAL==level&&FATALFLAG){ 
			switch(type){
				case DBLog: 
					dbLog<<time<<" "<<" Fatal:"<<msg<<endl;
					break;
				case RegitLog:
					regitLog<<time<<" "<<" Fatal:"<<msg<<endl;
					break;
				case UpdatePasswdLog:
					updatePasswdLog<<time<<" "<<" Fatal:"<<msg<<endl;
			}
		}else if(ERROR==level&&ERRORFLAG){ 
			switch(type){
				case DBLog: 
					dbLog<<time<<" "<<" Error:"<<msg<<endl;
					break;
				case RegitLog:
					regitLog<<time<<" "<<" Error:"<<msg<<endl;
					break;
				case UpdatePasswdLog:
					updatePasswdLog<<time<<" "<<" Error:"<<msg<<endl;
			}
		}else if(WARN==level&&WARNFLAG){
			switch(type){
				case DBLog: 
					dbLog<<time<<" "<<" Warmming:"<<msg<<endl;
					break;
				case RegitLog:
					regitLog<<time<<" "<<" Warmming:"<<msg<<endl;
					break;
				case UpdatePasswdLog:
					updatePasswdLog<<time<<" "<<" Warmming:"<<msg<<endl;
			}
		}else if(INFO==level&&INFOFLAG){
			switch(type){
				case DBLog: 
					dbLog<<time<<" "<<" Info:"<<msg<<endl;
					break;
				case RegitLog:
					regitLog<<time<<" "<<" Info:"<<msg<<endl;
					break;
				case UpdatePasswdLog:
					updatePasswdLog<<time<<" "<<" Info:"<<msg<<endl;
			}
		}else if(DEBUG==level&&DEBUGFLAG){
			switch(type){
				case DBLog: 
					dbLog<<time<<" "<<" Debug:"<<msg<<endl;
					break;
				case RegitLog:
					regitLog<<time<<" "<<" Debug:"<<msg<<endl;
					break;
				case UpdatePasswdLog:
					updatePasswdLog<<time<<" "<<" Debug:"<<msg<<endl;
			}
		}
	}
	



};
Logger *Logger::instance;//=nullptr;

#endif 
