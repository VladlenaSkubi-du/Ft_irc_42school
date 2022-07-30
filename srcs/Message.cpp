# include "Message.hpp"

Message::Message()
{
	_prefix = "";
	_command = "";
	_params = std::vector<std::string>();
}

Message::~Message() {}

void	Message::setup(std::string message)
{
	int	i;

	i = 0;
	if (message[i] == ':')
		parse_prefix(message, i);
	parse_command(message, i);
	parse_params(message, i);
}

void	Message::parse_prefix(std::string message, int &i)
{
	i = 1;
	while ((message[i] != '\r' && message[i] !=  '\n')  && message[i] != ' ')
		i++;
	if (i > 1)
		_prefix.append(&message[1], i - 1);
	while (message[i] == ' ')
		i++;
}

void	Message::parse_command(std::string message, int &i)
{
	int	j = i;

	while ((message[i] != '\r' && message[i] !=  '\n') && message[i] != ' ')
		i++;
	if (i > j)
		_command.append(&message[j], i - j);
	for (unsigned int k = 0; k < _command.size(); k++)
		_command[k] = toupper(_command[k]);
}

void	Message::parse_params(std::string message, int &i)
{
	int			j;
	std::string	s;

	while ((message[i] != '\r' && message[i] != '\n'))
	{
		while (message[i] == ' ')
			i++;
		j = i;
		if (message[i] == ':')
		{
			j++;
			while (message[i] != '\r' && message[i] !=  '\n')
				i++;
			_params.push_back(s.append(&message[j], i - j));
			return ;
		}
		while ((message[i] != '\r' && message[i] !=  '\n') && message[i] != ' ')
			i++;
		if (i > j)
			_params.push_back(s.append(&message[j], i - j));
		s.clear();
	}
}

std::string					Message::prefix() const { return _prefix; }

std::string					Message::command() const { return _command; }

std::vector<std::string>	Message::params() const { return _params; }

