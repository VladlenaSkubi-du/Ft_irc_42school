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
	// if (this->check_value_by_regexp(i) == 0) {
	// 	errors_management(CONFIG_VALUE_INVALID, this->regexp[i], 0);
	// 	exit(1);
	// }
	this->values[i].assign(value);
	std::cout << "\t" << this->keys[i] << " is " << this->values[i] << std::endl;
}

bool		ConfigValues::check_value_by_regexp(size_t index) {
	// int		j = -1;
	// int		k = -1;

	// while (++j != this->regexp[index].size()) {
	// 	if (this->values[index])
	// }
	if (this->regexp[index].empty()) {
		return (1);
	}
	return (0);
}