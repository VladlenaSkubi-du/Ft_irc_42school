#include <fstream>
#include <sstream>
#include "ConfigValues.hpp"
#include "debug.hpp"


static void		parse_config_file(std::ifstream& config_file, ConfigValues& config_values) {
	std::string line;
	while (std::getline(config_file, line))
	{
		if (line[0] != '#') {
			std::size_t pos = line.find('=');
			if (pos == std::string::npos)
				exit(errors_management(CONFIG_WRONG_FORMAT, line, USAGE_PRINTED));
			std::string key = line.substr(0, pos);
			std::string value = line.substr(pos + 1, line.size() - pos - 1);
			config_values.save_value_by_key(key, value);
		}
	}
}

void	check_config_file(int argc, char *argv[], ConfigValues& config_values) {
	if (argc < 2)
		exit(errors_management(CONFIG_NOFILE, "", USAGE_PRINTED));
	else if (argc > 2)
		exit(errors_management(CONFIG_DOUPLICATE_FILE, "", USAGE_PRINTED));
	std::ifstream config_file;
	config_file.open(argv[1], std::ifstream::in);
	if (!config_file)
		exit(errors_management(CONFIG_CANT_OPEN, argv[1], USAGE_NOT_PRINTED));
	parse_config_file(config_file, config_values);
	config_file.close();
}