# Basic info

CC=clang++
RM=/bin/rm -rf
PRINTF=printf
MKDIR=mkdir -p


# ------------  PROJECT  ----------------------------------------------------- #

NAME :=	ircserv

# ------------  FLAGS  ------------------------------------------------------- #

FLAGS := -Wall# -Wextra -Werror
FLAGS += -std=c++98

# ------------  SOURCE FILES  ------------------------------------------------ #

# VALIDATOR_DIR := validator
# VALIDATOR := \
# 			$(VALIDATOR_DIR)/val_start.c \
# 			$(VALIDATOR_DIR)/val_errors.c \
# 			$(VALIDATOR_DIR)/val_help_funcs.c \
# 			$(VALIDATOR_DIR)/val_arguments.c \
# 			$(VALIDATOR_DIR)/val_first_filter.c \
# 			$(VALIDATOR_DIR)/val_second_filter.c \
# 			$(VALIDATOR_DIR)/val_second_filter_rooms.c \
# 			$(VALIDATOR_DIR)/val_save_rooms.c \
# 			$(VALIDATOR_DIR)/val_second_filter_links.c

# ALGORITHM_DIR := algorithm
# ALGORITHM := \
# 			$(ALGORITHM_DIR)/al_bellman_ford.c\
# 			$(ALGORITHM_DIR)/al_suurbale.c\
# 			$(ALGORITHM_DIR)/al_reverse_path.c\
# 			$(ALGORITHM_DIR)/al_edges.c\
# 			$(ALGORITHM_DIR)/al_paths.c\

SOURCES := main.cpp \
			error_management.cpp \
			check_config_file.cpp \
			ConfigValues_methods.cpp \
			MainServer_methods.cpp \

# ------------  DIRECTORIES  ------------------------------------------------- #

DIR_O := objs
DIR_S := srcs
INCLUDE_DIR = includes

# ------------  INCLUDE FILES  ----------------------------------------------- #

INCLUDES := \
			-I $(INCLUDE_DIR)

# ------------  FILEPATHS  --------------------------------------------------- #

SRCS := $(addprefix $(DIR_S)/,$(SOURCES))
OBJS := $(addprefix $(DIR_O)/,$(SOURCES:.cpp=.o))

# ------------  RULES  ------------------------------------------------------- #

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	@$(PRINTF) "\r\033[32;1mCompiling ircserv...\033[0m                                     \n"
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME)
	@$(PRINTF) "\r\033[32;1mircserv is ready\033[0m                                     \n"
	@$(PRINTF) "\033[?25h"

$(OBJS): $(DIR_O)/%.o: $(DIR_S)/%.cpp $(wildcard $(INCLUDE_DIR)/*.h) | $(DIR_O)
	@$(PRINTF) "\033[?25l"
	@$(PRINTF) "\r\033[34;1mNow compiling $@!                                    		\033[0m"
	@$(CC) $(FLAGS) -c $(INCLUDES) -o $@ $<

$(DIR_O):
	@$(MKDIR) $(DIR_O)

clean:
	@$(PRINTF) "\r\033[34mDeleting ircserv o-files\033[0m                                     \n"
	@$(RM) $(DIR_O)

fclean: clean
	@$(PRINTF) "\r\033[34mDeleting ircserv binary\033[0m                                     \n"
	@$(RM) $(NAME)

re: fclean all
