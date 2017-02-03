#include "Tokenizer.h"
Token_type Token::get_token_type(){
	return this->token_type;
}
size_t Token::get_line(){
	return this->line_number;
}
int main(){
	Token sample(1);
	std::cout<<sample.get_token_type()<<std::endl;
	return 0;
}
