#include "ircserv.hpp"

ConfigValues::ConfigValues(void) {
	this->config_values_nb = CONFIG_VALUES_NB;
	//--
	this->keys[0].assign("PASSWORD");
	this->regexp[0].assign("");
	//--
	this->keys[1].assign("PORT");
	this->regexp[1].assign("Aa!\"#$%&\'()*+,-./:;<>=?@[]\\^_{}|~");
	//--
	size_t i = -1;
	while (++i < CONFIG_VALUES_NB) {
		this->values[i].assign("");
	}
}

ConfigValues::~ConfigValues(void) { }

std::string	ConfigValues::get_value_from_array(const char *key) {
	size_t	i = -1;
	while  (++i < this->config_values_nb) {
		if (this->keys[i].compare(key) == 0) {
			break ;
		}
	}
	return(values[i]);
}

void		ConfigValues::save_value_by_key(std::string key, std::string value) {
	if (key.empty()) {
		errors_management(CONFIG_KEY_EMPTY, "", 0);
		exit(1);
	}
	if (value.empty()) {
		errors_management(CONFIG_VALUE_EMPTY, key, 0);
		exit(1);
	}
	size_t	i = -1;
	while  (++i < this->config_values_nb) {
		if (this->keys[i].compare(key) == 0) {
			break ;
		}
	}
	if (i == this->config_values_nb) {
		errors_management(CONFIG_NOKEY, key, 0);
		exit(1);
	}
	if (this->values[i].empty() == 0) {
		errors_management(CONFIG_DOUBLICATE_KEY, this->keys[i], 0);
		exit(1);
	}
	if (this->check_value_by_regexp(i, value) == 0) {
		errors_management(CONFIG_VALUE_INVALID, this->regexp[i], 0);
		exit(1);
	}
	this->values[i].assign(value);
	std::cout << "\t" << this->keys[i] << " is " << this->values[i] << std::endl;
}

bool		ConfigValues::check_value_by_regexp(size_t index, std::string& value) {
	if (this->regexp[index].empty()) {
		return (1);
	}
	int		j = -1;
	int		k = -1;
	while (++j != this->regexp[index].size()) {
		while (++k != value.size()) {
			if (this->regexp[index][j] == 'A' && (value[k] >= 'A' && value[k] <= 'Z')) {
				return (0);
			}
			else if (this->regexp[index][j] == 'a' && (value[k] >= 'a' && value[k] <= 'z')) {
				return (0);
			}
			else if (this->regexp[index][j] == '0' && (value[k] >= '0' && value[k] <= '9')) {
				return (0);
			}
			if (this->values[index][k] == this->regexp[index][j]) {
				return (0);
			}
		}
		k = -1;
	}
	return (1);
}