#include "main.h"
using namespace std;
int main(){
	string s = "	dialog.\"毛哥\".\"boy next door\"";
	int len = s.size();
	for(int i = 0 ; i < len ; ++ i)
		if(s[i] != ' ' && s[i] != '\t'){
			std::cout<<i<<" "<<s[i]<<std::endl;
			break;
		}
	return 0;
}
