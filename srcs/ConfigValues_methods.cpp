#include "ircserv.hpp"

ConfigValues::ConfigValues(void) {
	this->config_values_nb = CONFIG_VALUES_NB;
	//--
	this->keys[0].assign("PASSWORD");
	this->regexp[0].assign("");
	this->values[0].assign("");
	//--
	this->keys[1].assign("PORT");
	this->regexp[1].assign("Aa!\"#$%&\'()*+,-./:;<>=?@[]\\^_{}|~");
	this->values[1].assign("");
	//--
	this->keys[2].assign("HOSTNAME");
	this->regexp[2].assign("Aa!\"#$%&\'()*+,-/:;<>=?@[]\\^_{}|~");
	this->values[2].assign("127.0.0.1");
}

ConfigValues::~ConfigValues(void) { }

std::string	ConfigValues::get_value_from_array(const char *key) {
	size_t	i;
	for (i = 0; i < this->config_values_nb; i++ ) {
		if (this->keys[i].compare(key) == 0) {
			break ;
		}
	}
	return(this->values[i]);
}

void		ConfigValues::save_value_by_key(std::string key, std::string value) {
	if (key.empty())
		exit(errors_management(CONFIG_KEY_EMPTY, "", USAGE_NOT_PRINTED));
	if (value.empty())
		exit(errors_management(CONFIG_VALUE_EMPTY, key, USAGE_NOT_PRINTED));
	size_t	i;
	for (i = 0; i < this->config_values_nb; i++ ) {
		if (this->keys[i].compare(key) == 0) {
			break ;
		}
	}
	if (i == this->config_values_nb)
		exit(errors_management(CONFIG_NOKEY, key, USAGE_NOT_PRINTED));
	if (!this->check_value_by_regexp(i, value))
		exit(errors_management(CONFIG_VALUE_INVALID, this->regexp[i], USAGE_NOT_PRINTED));
	this->values[i].assign(value);
	std::cout << "\t" << this->keys[i] << " is " << this->values[i] << std::endl;
}

bool		ConfigValues::check_value_by_regexp(size_t index, std::string& value) {
	if (this->regexp[index].empty()) {
		return (true);
	}
	size_t		j;
	size_t		k;
	for (j = 0; j != this->regexp[index].size(); j++ ) {
		for (k = 0; k != value.size(); k++ ) {
            if ((this->regexp[index][j] == 'A' && value[k] >= 'A' && value[k] <= 'Z') ||
					(this->regexp[index][j] == 'a' && value[k] >= 'a' && value[k] <= 'z') ||
					(this->regexp[index][j] == '0' && value[k] >= '0' && value[k] <= '9') ||
                	(this->values[index][k] == this->regexp[index][j]))
				return false;
		}
	}
	return (true);
}