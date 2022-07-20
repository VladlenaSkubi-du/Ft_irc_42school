#include "IrcServer.hpp"
#include "ConfigValues.hpp"
#include "debug.hpp"

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
	for (std::size_t i = 0; i < config_values_.size(); i++ ) {
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
	std::size_t	i = 0;
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
		exit(errors_management(CONFIG_VALUE_INVALID, config_values_[i].regexp_ + " in value [" + value + "]", USAGE_NOT_PRINTED));
	}
	config_values_[i].values_.assign(value);
	std::cout << "\t" << config_values_[i].keys_ << " is " << config_values_[i].values_ << std::endl;
}

bool		ConfigValues::check_value_by_regexp(const std::size_t index, const std::string& value) const {
	if (config_values_[index].regexp_.empty())
		return true;
	for (std::size_t j = 0; j != config_values_[index].regexp_.size(); j++) {
		const std::string &regexp = config_values_[index].regexp_;
		for (std::size_t k = 0; k != value.size(); k++ ) {
			unsigned char c = value[k];
            if ((regexp[j] == 'A' && std::isupper(c)) ||
					(regexp[j] == 'a' && std::islower(c)) ||
					(regexp[j] == '0' && std::isdigit(c)) ||
                	(regexp[j] == value[k]))
				return false;
		}
	}
	return true;
}