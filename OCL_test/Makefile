NAME = test

RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
PURPLE = \033[35m
CYAN = \033[36m
NONE = \033[0m

all: $(NAME)

$(NAME): test.c
	@gcc -g -Wall -Werror -Wextra test.c -framework OpenCL -o test
	@printf "$(PURPLE)OpenCL:\t$(YELLOW)%-25s$(GREEN)[done]$(NONE)\n" $@

fclean:
	@rm -rf $(NAME)
	@printf "$(PURPLE)OpenCL:\t$(RED)%-25s$(GREEN)[done]$(NONE)\n" $@

re: fclean all
