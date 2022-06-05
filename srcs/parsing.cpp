#include <string>

class MessageProcessor {
	private:
		const std::string input;
	public:
		bool check_nonwhite(char c);
		bool check_letter(char c);
		bool check_number(char c);
		bool check_special(char c);
		bool check_chstring(char c);
		bool check_user(int &i);
		bool check_nick(int &i);
		bool check_mask(int &i);
		bool check_channel(int &i);
		bool check_servername(int &i);
		bool check_host(int &i);
		bool check_to(int &i);
		bool check_target(int &i);
		bool check_crlf(char c);
		bool check_nospcrlfcl(char c);
		bool check_trailing(int &i);
		bool check_middle(int &i);
		bool check_params(int &i);
};

bool MessageProcessor::check_nonwhite(char c) {
	return c != ' ' && c != 0x0 && c != 0xd && c != 0xa;
}

bool MessageProcessor::check_letter(char c) {
	return (c >= 'a' && c <= 'z') || (c >='A' && c <= 'Z');
}

bool MessageProcessor::check_number(char c) {
	return c >= '0' && c <= '9';
}

bool MessageProcessor::check_special(char c) {
	return c == '-' || c == '[' || c == ']' || c == '\\'
	    || c == '`' || c == '^' || c == '{' || c == '}';
}

bool MessageProcessor::check_chstring(char c){
	return c != ' ' && c != 0x7 && c != 0 && c != 0xd && c != 0xa && c != ',';
}

bool MessageProcessor::check_user(int &i) {
	bool isCorrectName = false;
	
	for ( int j = i ; j < this->input.size(); ++j) {
		if (this->MessageProcessor::check_nonwhite(this->input[j])) {
			if (!isCorrectName) {
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

bool MessageProcessor::check_nick(int &i) {
	if (!this->MessageProcessor::check_letter(this->input[i]))
		return false;
	++i;
	while (this->input.size() > i &&
			(
		   		this->MessageProcessor::check_letter(this->input[i]) ||
		   		this->MessageProcessor::check_number(this->input[i]) ||
		   		this->MessageProcessor::check_special(this->input[i])
			)
		   )
		++i;
	return true;
}

bool MessageProcessor::check_mask(int &i) {
	if (this->input.size() > i + 1 && (this->input[i] == '#' || this->input[i] == '$') &&
		this->MessageProcessor::check_chstring(this->input[i + 1])) {
		i += 2;
		return true;
	}
	return false;
}

bool MessageProcessor::check_channel(int &i) {
	if (this->input.size() > i + 1 && (this->input[i] == '#' || this->input[i] == '&') &&
		this->MessageProcessor::check_chstring(this->input[i + 1])) {
		i += 2;
		return true;
	}
	return false;
}

bool MessageProcessor::check_servername(int &i){
	return this->MessageProcessor::check_host(i);
}

bool MessageProcessor::check_host(int &i) {
	while (this->input.size() > i && !this->MessageProcessor::check_nonwhite(this->input[i]))
		++i;
	return true;
}

bool MessageProcessor::check_to(int &i) {
	if (this->MessageProcessor::check_channel(i))
		return true;
	int j = i;
	if (this->MessageProcessor::check_user(j) && this->input[j] == '@') {
		j += 1;
		if (this->MessageProcessor::check_servername(j)) {
			i = j;
			return true;
		}
	}
	if (this->MessageProcessor::check_nick(i) || this->MessageProcessor::check_mask(i))
		return true;
	return false;
}

bool MessageProcessor::check_target(int &i) {
	bool isTargetCorrect = false;
	while (this->input.size() > i) {
		if (!isTargetCorrect) {
			if (this->MessageProcessor::check_to(i))
				isTargetCorrect = true;
			else
				break;
		}
		else {
			int j = i;
			if (this->input[j++] == ',' && this->MessageProcessor::check_to(j))
				i = j;
			else
				break;
		}
	}
	return isTargetCorrect;
}

bool MessageProcessor::check_crlf(char c) {
	return c == 0xd || c == 0xa;
}

bool MessageProcessor::check_nospcrlfcl(char c) {
	return (c >= 0x1 && c <= 0x9 ||
		    c >= 0xb && c <= 0xc ||
		    c >= 0xe && c <= 0x1f ||
		    c >= 0x21 && c <= 0x39 ||
		    c >= 0x3b && c <= 0xff);
}

bool MessageProcessor::check_trailing(int &i) {
	while (this->input[i] == ':' || this->input[i] == ' ' || this->MessageProcessor::check_nospcrlfcl(this->input[i]))
		++i;
}

bool MessageProcessor::check_middle(int &i) {
	bool isMiddleCorrect = false;
	while (this->input.size() > i) {
		if (!isMiddleCorrect) {
			if (this->MessageProcessor::check_nospcrlfcl(i))
				isMiddleCorrect = true;
			else
				break;
		}
		else {
			int j = i;
			if (this->input[j++] == ',' && this->MessageProcessor::check_to(j))
				i = j;
			else
				break;
		}
	}
	return isMiddleCorrect;
}

bool MessageProcessor::check_params(int &i) {
	bool isParamsCorrect = false;
	int j, z = 0;
	for (j = 0; j <= 14; ++j) {
		z = i;
		if (this->input[z] == ' '  && this->MessageProcessor::check_middle(z))
			i = z;
		else
			break;
	}
	z = i;
	if (this->input.size() > z + 1 &&
		this->input[z] == ' ' && 
		(this->input[z + 1] == ':' || j == 14) &&
		this->MessageProcessor::check_trailing(z))
		z = i;
	else
		isParamsCorrect = false;
	return isParamsCorrect;
}

bool MessageProcessor::check_params(int &i) {


int main(void) {return 0;}