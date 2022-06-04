#include <string>

bool check_nonwhite(char c) {
	return c != ' ' && c != 0x0 && c != 0xd && c != 0xa;
}

bool check_letter(char c){
	return (c >= 'a' && c <= 'z') || (c >='A' && c <= 'Z');
}

bool check_number(char c){
	return c >= '0' && c <= '9';
}

bool check_special(char c){
	return c == '-' || c == '[' || c == ']' || c == '\\'
	    || c == '`' || c == '^' || c == '{' || c == '}';
}

bool check_chstring(char c){
	return c != ' ' && c != 0x7 && c != 0 && c != 0xd && c != 0xa && c != ',';
}

bool chech_user(const std::string &input, int &i){
	bool isCorrectName = false;
	
	for ( int j = i ; j < input.size(); ++j){
		if (check_nonwhite(input[j])){
			if (!isCorrectName){
				isCorrectName = true;
			}
			else {
				i = j;
				break;
			}
		}
	}
	return isCorrectName;
}

bool check_nick(const std::string &input, int &i){
	if (!check_letter(input[i]))
		return false;
	++i;
	while (input.size() > i &&
			(
		   		check_letter(input[i]) ||
		   		check_number(input[i]) ||
		   		check_special(input[i])
			)
		   )
		++i;
	return true;
}

bool check_mask(const std::string &input, int &i){
	if (input.size() > i + 1 && (input[i] == '#' || input[i] == '$') && check_chstring(input[i + 1])) {
		i += 2;
		return true;
	}
	return false;
}

bool check_channel(const std::string &input, int &i){
	if (input.size() > i + 1 && (input[i] == '#' || input[i] == '&') && check_chstring(input[i + 1])) {
		i += 2;
		return true;
	}
	return false;
}

bool check_servername(const std::string &input, int &i){
	return check_host(input, i);
}

bool check_host(const std::string &input, int &i){
	while (input.size() > i && !check_nonwhite(input[i]))
		++i;
	return true;
}

bool check_to(const std::string &input, int &i){
	if (check_channel(input, i))
		return true;
	int j = i;
	if (check_user(input, j) && input[j] == '@'){
		j += 1;
		if (check_servername(input, j)){
			i = j;
			return true;
		}
	}
	if (check_nick(input, i) || check_mask(input, i))
		return true;
}


int main(void) {return 0;}