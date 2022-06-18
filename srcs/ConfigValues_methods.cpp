#include "ircserv.hpp"

ConfigValues::ConfigValues(void) {
	struct config_value_ tmp;
	tmp.keys_.assign("PASSWORD");
	tmp.regexp_.assign("");
	tmp.values_.assign("");
	config_values_.push_back(tmp);
	//--
	tmp.keys_.assign("PORT");
	tmp.regexp_.assign("Aa!\"#$%&\'()*+,-./:;<>=?@[]\\^_{}|~");
	tmp.values_.assign("");
	config_values_.push_back(tmp);
	//--
	tmp.keys_.assign("HOSTNAME");
	tmp.regexp_.assign("Aa!\"#$%&\'()*+,-/:;<>=?@[]\\^_{}|~");
	tmp.values_.assign("127.0.0.1");
	config_values_.push_back(tmp);
}

ConfigValues::~ConfigValues(void) { }

const std::string&	ConfigValues::get_value_from_array(const char *key) const {
	for (size_t i = 0; i < config_values_.size(); i++ ) {
		if (config_values_[i].keys_.compare(key) == 0) {
			return (config_values_[i].values_);
		}
	}
	return(config_values_[0].values_); //TO DO exception
}

void		ConfigValues::save_value_by_key(const std::string& key, const std::string& value) {
	if (key.empty())
		exit(errors_management(CONFIG_KEY_EMPTY, "", USAGE_NOT_PRINTED));
	if (value.empty())
		exit(errors_management(CONFIG_VALUE_EMPTY, key, USAGE_NOT_PRINTED));
	size_t	i = 0;
	for ( ; i < config_values_.size(); i++ ) {
		if (config_values_[i].keys_.compare(key) == 0) {
			break ;
		}
	}
	// TO DO as exception:
	if (i == config_values_.size())
		exit(errors_management(CONFIG_NOKEY, key, USAGE_NOT_PRINTED));
	if (!check_value_by_regexp(i, value)) {
		std::cout << key << std::endl;
		exit(errors_management(CONFIG_VALUE_INVALID, config_values_[i].regexp_, USAGE_NOT_PRINTED));
	}
	config_values_[i].values_.assign(value);
	std::cout << "\t" << config_values_[i].keys_ << " is " << config_values_[i].values_ << std::endl;
}

bool		ConfigValues::check_value_by_regexp(const size_t index, const std::string& value) const {
	if (config_values_[index].regexp_.empty()) {
		return (true);
	}
	size_t		j = 0;
	size_t		k = 0;
	for ( ; j != config_values_[index].regexp_.size(); j++ ) {
		for (k = 0; k != value.size(); k++ ) {
            if ((config_values_[index].regexp_[j] == 'A' && value[k] >= 'A' && value[k] <= 'Z') ||
					(config_values_[index].regexp_[j] == 'a' && value[k] >= 'a' && value[k] <= 'z') ||
					(config_values_[index].regexp_[j] == '0' && value[k] >= '0' && value[k] <= '9') ||
                	(config_values_[index].values_[k] == config_values_[index].regexp_[j]))
				return false;
		}
	}
	return (true);
}