//Author hd7771

#include <iostream>
#include <cstddef>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>

#define err -1

const int USER_MODE = S_IRUSR | S_IWUSR | S_IXUSR;
const int RWX = O_RDWR;

typedef std::map<std::string , std::string> Vstr;
typedef std::map<std::string , std::string> Nstr;

int min(int a , int b){
	if(a < b) return a;
	return b;
}

enum Token_type {
	Token_default_type = 1,
	Token_identifier = 2,
	Token_number = 3,
	Token_string = 4
};

void err_sys(const char* s){
	perror(s);
	exit(1);
}

int Creat(const char* s , int mode){
	int fd;
	if((fd = open(s , O_RDWR | O_CREAT | O_TRUNC , mode)) < 0){
		err_sys("create error");
	}
	return fd;
}

const int MAXBUF = 1024;
char buf[MAXBUF];

void Write(int fd , const char* s , const int len){
	int pos = 0;
	while(pos < len){
		//std::cout<<len<<std::endl;
		int do_len = min(len - pos , MAXBUF);
		int r = write(fd , s + pos , do_len);
		if(r < 0) err_sys("write error");
		pos += do_len;
	}
}

int Read(int fd , char* s){
	int pos = 0;
	char tmp[5];
	while(1){
		int res = read(fd , tmp , 1);
		if(res < 0) err_sys("read error");
		if(tmp[0] == '\n' || res == 0) break;
		if(res != 0) s[pos ++] = tmp[0];
	}
	s[pos] = '\0';
	return pos;
}


int atoi(const char* s){
	int len = strlen(s);
	int ret = 0;
	for(int i = 0 ; i < len ; ++ i){
		ret *= 10;
		ret += s[i] - '0';
	}
	return ret;
}

char* itoa(const int x , char *res){
	int cur = 0;
	int ret[10];
	int tt = x;
	while(tt){
		ret[cur ++] = tt % 10;
		tt /= 10;
	}
	for(int i = 0 ; i < cur ; ++ i){
		res[i] = ret[cur - 1 - i] + '0';
	}
	if(cur == 0) res[cur ++] = '0';
	res[cur] = '\0';
	return (char* )res;
}

void dotc(char *s){
	int len = strlen(s);
	for(int i = 0 ; i < len ; ++ i){
		if(s[i] == '.')
			s[i] = '/';
		else if(s[i] == '|')
			s[i] = '.';
	}
}

std::string ctos(char *s){
	int len = strlen(s);
	std::string ret;
	for(int i = 0 ; i < len ; ++ i)
		ret += s[i];
	return ret;
}

void stoc(std::string s , char *c){
	int len = s.size();
	for(int i = 0 ; i < len ; ++ i){
		c[i] = s[i];
	}
	c[len] = '\0';
}
int stoi(std::string s){
	int ret = 0;
	int len = s.size();
	for(int i = 0 ; i < len ; ++ i){
		ret *= 10;
		ret += s[i] - '0';
	}
	return ret;
}

std::string itos(int x){
	if(x == 0) return "0";
	std::string tmp , ret;
	while(x){
		tmp += (x % 10) + '0';
		x /= 10;
	}
	for(int i = 0 ; i < (int)tmp.size() ; ++ i)
		ret += tmp[tmp.size() - 1 - i];
	return ret;
}

void preload(char *s){
	int len = strlen(s);
	int i;
	for(i = 0 ; i < len ; ++ i)
		if(s[i] != ' ' && s[i] != '\t') break;
	int j = i;
	for( ; j < len ; ++ j)
		s[j - i] = s[j];
	s[j - i] = '\0';
}

std::string getoption(std::string s , int pos){
	std::string ret;
	int len = s.size();
	for(int i = pos + 1 ; i < len ; ++ i){
		if(s[i] == '"') break;
		else ret += s[i];
	}
	return ret;
}

std::string getflag(std::string s , int pos){
	std::string ret;
	int len = s.size();
	for(int i = pos + 1 ; i < len ; ++ i){
		if(s[i] == '.' || s[i] == '{') break;
		else ret += s[i];
	}
	return ret;
}

void handle(Vstr now , int sfd){
	char buff[512];
	std::string res = "var node" + now["index"] + " = {\n";
	stoc(res , buff);
	//std::cout<<buff<<std::endl;
	Write(sfd , buff , strlen(buff));
	res = "\ttype : '"  + now["type"] + "' ,\n";
	stoc(res , buff);
	Write(sfd , buff , strlen(buff));
	res = "\tindex : " + now["index"] + ",\n";
	stoc(res , buff);
	Write(sfd , buff , strlen(buff));
	res = "\tvis : false,\n";
	stoc(res , buff);
	Write(sfd , buff , strlen(buff));
	if(now.count("value")){
		res = "\tvalue : '" + now["value"] + "' ,\n";
		stoc(res , buff);
		Write(sfd , buff , strlen(buff));
	}
	if(now.count("person")){
		res = "\tperson : '" + now["person"] + "' ,\n";
		stoc(res , buff);
		Write(sfd , buff , strlen(buff));
	}
	if(now.count("word")){
		res = "\tword : '" + now["word"] + "' ,\n";
		stoc(res , buff);
		Write(sfd , buff , strlen(buff));
	}
	if(now.count("flag1")){
		res = "\tflag1 : '" + now["flag1"] + "' ,\n";
		stoc(res , buff);
		Write(sfd , buff , strlen(buff));
	}
	if(now.count("flag2")){
		res = "\tflag2 : '" + now["flag2"] + "' ,\n";
		stoc(res , buff);
		Write(sfd , buff , strlen(buff));
	}
	if(now.count("op1")){
		res = "\top1 : '" + now["op1"] + "' ,\n";
		stoc(res , buff);
		Write(sfd , buff , strlen(buff));
	}
	if(now.count("op2")){
		res = "\top2 : '" + now["op2"] + "' ,\n";
		stoc(res , buff);
		Write(sfd , buff , strlen(buff));
	}
	res = "\tsons : new Array()\n";
	stoc(res , buff);
	Write(sfd , buff , strlen(buff));
	res = "};\n";
	stoc(res , buff);
	Write(sfd , buff , strlen(buff));
	res = "Vtree[" + now["index"] + "] = node" + now["index"] + ";\n";
	stoc(res , buff);
	Write(sfd , buff , strlen(buff));
}

void connect(Vstr now , Vstr nxt , int sfd){
	char buff[512];
	std::string a = "node" + now["index"];
	std::string res = a + ".sons.push(" + nxt["index"] + ");\n";
	stoc(res , buff);
	Write(sfd , buff , strlen(buff));
}
