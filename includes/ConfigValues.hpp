#pragma once

#include <vector>
#include <string>
#include <cstdlib>

class ConfigValues {
	private:
		struct			config_value_ {
			std::string		keys_;
			std::string		regexp_;
			std::string		values_;
		};
	public:
		std::vector<struct config_value_>	config_values_;
		ConfigValues(void);
		~ConfigValues(void);
		const std::string& 	get_value_from_array(const char *key) const;
		void			    save_value_by_key(const std::string& key, const std::string& value);
		bool			    check_value_by_regexp(const size_t index, const std::string& value) const;
};


void		check_config_file(int argc, char *argv[], ConfigValues& config_values);