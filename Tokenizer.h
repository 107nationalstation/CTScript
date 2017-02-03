#include "common.h"

class Token {
	public:
		Token() {}
		Token(size_t line){
			line_number = line;
			token_type = Token_default_type;
		}
		Token_type get_token_type();
		size_t get_line();
	private:
		Token_type token_type;
		size_t line_number;
};
