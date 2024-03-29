NAME_FT =  ft_containers
NAME_STD =  std_containers
NAME_42_FT = subject_ft
NAME_42_STD = subject_std

FLAGS = -std=c++98 -MMD -Wall -Wextra -Werror -g3 -D DEBUG
CC = c++

SRCS = main.cpp
SRCS42 = subject_main.cpp


OBJS_DIR_FT = $(OBJS_DIR)/obj_ft
OBJS_DIR_STD = $(OBJS_DIR)/obj_std
OBJS_DIR_42FT = $(OBJS_DIR)/obj_ft
OBJS_DIR_42STD = $(OBJS_DIR)/obj_std

OBJS_DIR = objects
LOGS_DIR = logfiles

INC = -Iinclude

OBJS_FT = $(addprefix $(OBJS_DIR_FT)/, $(SRCS:.cpp=.o))
OBJS_STD = $(addprefix $(OBJS_DIR_STD)/, $(SRCS:.cpp=.o))
OBJS_42FT = $(addprefix $(OBJS_DIR_42FT)/, $(SRCS42:.cpp=.o))
OBJS_42STD = $(addprefix $(OBJS_DIR_42STD)/, $(SRCS42:.cpp=.o))



DEPS_FT = $(addprefix $(OBJS_DIR_FT)/, $(SRCS:.cpp=.d))
DEPS_STD = $(addprefix $(OBJS_DIR_STD)/, $(SRCS:.cpp=.d))
DEPS_42FT = $(addprefix $(OBJS_42DIR_FT)/, $(SRCS42:.cpp=.d))
DEPS_42STD = $(addprefix $(OBJS_42DIR_STD)/, $(SRCS42:.cpp=.d))


define ascii
		@echo "$(shell tput setaf 5)"
		@echo "==============================================================="
		printf "*                       FT_CONTAINERS                         *\n"
		@echo "==============================================================="
endef

all: $(NAME_FT) $(NAME_STD) $(NAME_42_FT) $(NAME_42_STD)

ascii:
	@clear
	$(call ascii)

$(NAME_FT): $(LOGS_DIR) $(OBJS_DIR_FT) $(OBJS_FT)
	@make -s ascii
	@echo -n "$(shell tput setaf 5) make:"
	@echo -n " Compiling executable [ $(NAME_FT) ] : "
	@$(CC) $(FLAGS) $(INC) -o $(NAME_FT) $(OBJS_FT) 
	@echo "[OK]$(shell tput sgr0)"

$(NAME_STD): $(OBJS_DIR_STD) $(OBJS_STD)
	@make -s ascii
	@echo -n "$(shell tput setaf 5) make:"
	@echo -n " Compiling executable [ $(NAME_STD) ] : "
	@$(CC) $(FLAGS) $(INC) -o $(NAME_STD) $(OBJS_STD) 
	@echo "[OK]$(shell tput sgr0)"

$(NAME_42_FT): $(LOGS_DIR) $(OBJS_42DIR_FT) $(OBJS_42FT)
	@make -s ascii
	@echo -n "$(shell tput setaf 5) make:"
	@echo -n " Compiling executable [ $(NAME_42_FT) ] : "
	@$(CC) $(FLAGS) $(INC) -o $(NAME_42_FT) $(OBJS_42FT) 
	@echo "[OK]$(shell tput sgr0)"

$(NAME_42_STD): $(OBJS_42DIR_STD) $(OBJS_42STD)
	@make -s ascii
	@echo -n "$(shell tput setaf 5) make:"
	@echo -n " Compiling executable [ $(NAME_42_STD) ] : "
	@$(CC) $(FLAGS) $(INC) -o $(NAME_42_STD) $(OBJS_42STD) 
	@echo "[OK]$(shell tput sgr0)"


-include $(DEPS_FT) $(DEPS_STD)

$(OBJS_DIR_FT)/%.o: %.cpp Makefile
	@echo -n "$(shell tput setaf 5) make:"
	@echo -n " Generating object files $@ from $< : "
	@$(CC) $(FLAGS) $(INC) -c $< -o $@
	@echo "[OK]$(shell tput sgr0)"

$(OBJS_DIR_STD)/%.o: %.cpp Makefile
	@echo -n "$(shell tput setaf 5) make:"
	@echo -n " Generating object files $@ from $< : "
	@$(CC) $(FLAGS) $(INC) -c $< -D=STD -o $@
	@echo "[OK]$(shell tput sgr0)"

$(OBJS_42DIR_FT)/%.o: %.cpp Makefile
	@echo -n "$(shell tput setaf 5) make:"
	@echo -n " Generating object files $@ from $< : "
	@$(CC) $(FLAGS) $(INC) -c $< -o $@
	@echo "[OK]$(shell tput sgr0)"

$(OBJS_42DIR_STD)/%.o: %.cpp Makefile
	@echo -n "$(shell tput setaf 5) make:"
	@echo -n " Generating object files $@ from $< : "
	@$(CC) $(FLAGS) $(INC) -c $< -D=STD -o $@
	@echo "[OK]$(shell tput sgr0)"


$(LOGS_DIR):
	@make -s ascii
	@echo -n "$(shell tput setaf 5) make:"
	@echo -n " Creating objects destination directory /$(LOGS_DIR) : "
	@mkdir -p $(LOGS_DIR)
	@echo "[OK]$(shell tput sgr0)"


$(OBJS_DIR_FT):
	@make -s ascii
	@echo -n "$(shell tput setaf 5) make:"
	@echo -n " Creating objects destination directory /$(OBJS_DIR_FT) : "
	@mkdir -p $(OBJS_DIR_FT)
	@echo "[OK]$(shell tput sgr0)"

$(OBJS_DIR_STD):
	@make -s ascii
	@echo -n "$(shell tput setaf 5) make:"
	@echo -n " Creating objects destination directory /$(OBJS_DIR_STD) : "
	@mkdir -p $(OBJS_DIR_STD)
	@echo "[OK]$(shell tput sgr0)"

$(OBJS_42DIR_FT):
	@make -s ascii
	@echo -n "$(shell tput setaf 5) make:"
	@echo -n " Creating objects destination directory /$(OBJS_42DIR_FT) : "
	@mkdir -p $(OBJS_42DIR_FT)
	@echo "[OK]$(shell tput sgr0)"

$(OBJS_42DIR_STD):
	@make -s ascii
	@echo -n "$(shell tput setaf 5) make:"
	@echo -n " Creating objects destination directory /$(OBJS_42DIR_STD) : "
	@mkdir -p $(OBJS_42DIR_STD)
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
	@echo -n "	 Removing executable [ $(NAME_STD) ]: "
	@rm -rf $(NAME_STD)
	@echo "[OK]"
	@echo -n " Removing executable [ $(NAME_42_FT) ]: "
	@rm -rf $(NAME_42_FT)
	@echo "[OK]"
	@echo -n "	 Removing executable [ $(NAME_42_STD) ]: "
	@rm -rf $(NAME_42_STD)
	@echo "[OK]"
	@echo -n "	 Removing $(LOGS_DIR)/ directory : "
	@rm -rf $(LOGS_DIR)
	@echo "[OK]$(shell tput sgr0)"

re: fclean all

.PHONY: all clean fclean