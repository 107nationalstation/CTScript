#include "main.h"

typedef std::map<std::string , std::string> Vstr;
typedef std::map<std::string , std::string> Nstr;

std::vector<Vstr> Vtree[1000000];
int cur = 0 , top = 0;
int Stack[1000000];
int bracket[1000000];
Vstr init;


void dfs(Vstr now){
	std::cout<<stoi(now["index"])<<" "<<now["type"]<<std::endl;
	for(int i = 0 ; i < (int)Vtree[stoi(now["index"])].size() ; ++ i){
		Vstr nxt = Vtree[stoi(now["index"])][i];
		//std::cout<<stoi(now["index"])<<" "<<now["type"]<<std::endl;
		//std::cout<<stoi(nxt["index"])<<" "<<nxt["type"]<<std::endl;
		dfs(nxt);
	}
}

int main(){
	int sfd = open("test.txt" , RWX , USER_MODE);
	std::vector<std::string> opBg , opPerson , opWord , opLeftCharacter;
	std::string nBg , nPerson , nWord , nLeftCharacter;
	init["index"] = itos(++ cur);
	init["type"] = "init";
	Stack[top ++] = cur;
	while(1){
		int len = Read(sfd , readBuffer);
		preload(readBuffer);
		std::string sentense = ctos(readBuffer);
		//std::cout<<sentense<<std::endl;
		if(len == 0) break;
		if(strncmp(readBuffer , "left" , 4) == 0){
			if(strncmp((readBuffer + 5) , "clear" , 5) == 0){
				nLeftCharacter = "clear";
			}
			else{
				dotc(readBuffer);
				nLeftCharacter = "char" + ctos(readBuffer + 4);
			}
			Nstr nxt;
			nxt["type"] = "left";
			nxt["value"] = nLeftCharacter;
			nxt["index"] = itos(++ cur);
			Vtree[Stack[top - 1]].push_back(nxt);
			bracket[top] = 0;
			Stack[top ++] = cur;
		}
		else if(strncmp(readBuffer , "bg" , 2) == 0){
			dotc(readBuffer);
			nBg = ctos(readBuffer);
			Nstr nxt;
			nxt["type"] = "bg";
			nxt["value"] = nBg;
			nxt["index"] = itos(++ cur);
			Vtree[Stack[top - 1]].push_back(nxt);
			bracket[top] = 0;
			Stack[top ++] = cur;
		}
		else if(strncmp(readBuffer , "dialog" , 6) == 0){
			int i;
			for(i = 8 ; ; ++ i){
				if(readBuffer[i] == '"') break;
				else nPerson += readBuffer[i];
			}
			i += 3;
			for( ; ; ++ i){
				if(readBuffer[i] == '"') break;
				else nWord += readBuffer[i];
			}
			if(nPerson.size() != 0){
				nPerson = "【" + nPerson + "】";
			}
			if(nWord.size() != 0){
				nWord = "「 " + nWord + " 」";
			}
			Nstr nxt;
			nxt["type"] = "dialog";
			nxt["person"] = nPerson;
			nxt["word"] = nWord;
			nxt["index"] = itos(++ cur);
			Vtree[Stack[top - 1]].push_back(nxt);
			bracket[top] = 0;
			Stack[top ++] = cur;
		}
		else if(strncmp(readBuffer , "click" , 5) == 0){
			/*opBg.push_back(nBg);
			opPerson.push_back(nPerson);
			opWord.push_back(nWord);
			opLeftCharacter.push_back(nLeftCharacter);
			nBg.clear();
			nLeftCharacter.clear();
			nPerson.clear();
			nWord.clear();*/
			Nstr nxt;
			nxt["type"] = "stop";
			nxt["index"] = itos(++ cur);
			Vtree[Stack[top - 1]].push_back(nxt);
			bracket[top] = 0;
			Stack[top ++] = cur;
		}
		else if(strncmp(readBuffer , "option2" , 7) == 0){
			std::string op1 , op2;
			std::string flag1 , flag2;
			int len = sentense.size();
			int i;
			for(i = 0 ; i < len ; ++ i)
				if(sentense[i] == '"'){
					op1 = getoption(sentense , i);
					break;
				}
			for(++ i ; i < len ; ++ i)
				if(sentense[i] == '|'){
					flag1 = getflag(sentense , i);
					break;
				}
			for(++ i ; i < len ; ++ i)
				if(sentense[i] == '"'){
					op2 = getoption(sentense , i);
					break;
				}
			for(++ i ; i < len ; ++ i)
				if(sentense[i] == '|'){
					flag2 = getflag(sentense , i);
					break;
				}
			Nstr nxt;
			nxt["type"] = "option2";
			nxt["index"] = itos(++ cur);
			nxt["op1"] = op1;
			nxt["op2"] = op2;
			nxt["flag1"] = flag1;
			nxt["flag2"] = flag2;
			Vtree[Stack[top - 1]].push_back(nxt);
			bracket[top] = 0;
			Stack[top ++] = cur;
		}
		else if(strncmp(readBuffer , "option3" , 7) == 0){
			
		}
		else if(strncmp(readBuffer , "op" , 2) == 0){
			std::string flag = getflag(sentense , 2);
			Nstr nxt;
			nxt["type"] = "{";
			nxt["index"] = itos(++ cur);
			nxt["value"] = flag;
			Vtree[Stack[top - 1]].push_back(nxt);
			bracket[top] = 1;
			Stack[top ++] = cur;
		}
		else if(strncmp(readBuffer , "}" , 1) == 0){
			Nstr nxt;
			nxt["type"] = "}";
			nxt["index"] = itos(++ cur);
			Vtree[Stack[top - 1]].push_back(nxt);
			while(bracket[top - 1] != 1){
				top --;
			}
			top --;
		}
	}
	dfs(init);
	
	
	int end = opBg.size();
	for(int i = 0 ; i < end ; ++ i){
		char num[100];
		itoa(i , num);	
		
		nBg = "opBg[" + ctos(num) + "] = " + "'" + opBg[i] + "';\n";
		
		nPerson = "opPerson[" + ctos(num) + "] = " + "'" + opPerson[i] + "';\n";
		
		nWord = "opWord[" + ctos(num) + "] = " + "'" + opWord[i] + "';\n";
		
		nLeftCharacter = "opLeftCharacter[" + ctos(num) + "] = " + "'" + opLeftCharacter[i] + "';\n";
		
		//std::cout<<"---"<<i<<"---"<<std::endl;
		//std::cout<<nBg<<std::endl;
		//std::cout<<nPerson<<std::endl;
		//std::cout<<nWord<<std::endl;
		//std::cout<<nLeftCharacter<<std::endl;
		
		char cnBg[256] , cnPerson[256] , cnWord[256] , cnLeftCharacter[256];
		stoc(nBg , cnBg);stoc(nPerson , cnPerson);
		stoc(nWord , cnWord);stoc(nLeftCharacter , cnLeftCharacter);
		
		//if(nBg.size() != 0) Write(fd , cnBg , strlen(cnBg));
		//Write(fd , cnPerson , strlen(cnPerson));
		//Write(fd , cnWord , strlen(cnWord));
		//Write(fd , cnLeftCharacter , strlen(cnLeftCharacter));
	}
	
	return 0;
}
