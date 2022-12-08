NAME_FT = ircserv

FLAGS = -std=c++98 -MMD -Wall -Wextra -Werror# -g3
CC = c++

SRCS = main.cpp \
       TCPsocket.cpp \
       TCPserver.cpp \
       Channel.cpp \
       User.cpp \
       utils.cpp \

SRCS_DIR = src/

OBJS_DIR_FT = $(OBJS_DIR)/objs

OBJS_DIR = objs
LOGS_DIR = logfiles

INC = -Iinclude

OBJS_FT = $(addprefix $(OBJS_DIR_FT)/, $(SRCS:.cpp=.o))
DEPS_FT = $(addprefix $(OBJS_DIR_FT)/, $(SRCS:.cpp=.d))

define ascii
		#@echo "$(shell tput setaf 5)"
		#@echo "==============================================================="
		#printf "*   __ _                      _        _                      *\n"
		#printf "*  / _| |_     ___ ___  _ __ | |_ __ _(_)_ __   ___ _ __ ___  *\n"
		#printf "* | |_| __|   / __/ _ \| '_ \| __/ _\` | | '_ \ / _ \ '__/ __| *\n"
		#printf "* |  _| |_   | (_| (_) | | | | || (_| | | | | |  __/ |  \__ \ *\n"
		#printf "* |_|  \__|___\___\___/|_| |_|\__\__,_|_|_| |_|\___|_|  |___/ *\n"
		#printf "*                                                             *\n"
		#@echo "==============================================================="
endef

all: $(NAME_FT)

ascii:
	@clear
	$(call ascii)

$(NAME_FT): $(LOGS_DIR) $(OBJS_DIR_FT) $(OBJS_FT)
	@make -s ascii
	@echo -n "$(shell tput setaf 5) make:"
	@echo -n " Compiling executable [ $(NAME_FT) ] : "
	@$(CC) $(FLAGS) $(INC) -o $(NAME_FT) $(OBJS_FT) 
	@echo "[OK]$(shell tput sgr0)"

-include $(DEPS_FT)

$(OBJS_DIR_FT)/%.o: $(SRCS_DIR)/%.cpp Makefile
	@echo -n "$(shell tput setaf 5) make:"
	@echo -n " Generating object files $@ from $< : "
	@$(CC) $(FLAGS) $(INC) -c $< -o $@
	@echo "[OK]$(shell tput sgr0)"

$(LOGS_DIR):
	@make -s ascii
	@echo -n "$(shell tput setaf 5) make:"
	@echo -n " Creating log files destination directory /$(LOGS_DIR) : "
	@mkdir -p $(LOGS_DIR)
	@echo "[OK]$(shell tput sgr0)"


$(OBJS_DIR_FT):
	@make -s ascii
	@echo -n "$(shell tput setaf 5) make:"
	@echo -n " Creating objects destination directory /$(OBJS_DIR_FT) : "
	@mkdir -p $(OBJS_DIR_FT)
	@echo "[OK]$(shell tput sgr0)"

clean:
	@make -s ascii
	@echo -n "$(shell tput setaf 5) clean:"
	@echo -n "  Removing $(OBJS_DIR)/ directory : "
	@rm -rf $(OBJS_DIR)
	@echo "[OK]$(shell tput sgr0)"

fclean: clean
	@echo -n "$(shell tput setaf 5) fclean:"
	@echo -n " Removing executable [ $(NAME_FT) ]: "
	@rm -rf $(NAME_FT)
	@echo "[OK]"
	@echo -n "	 Removing $(LOGS_DIR)/ directory : "
	@rm -rf $(LOGS_DIR)
	@echo "[OK]$(shell tput sgr0)"

re: fclean all

.PHONY: all clean fclean