# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/07 02:14:29 by cschoen           #+#    #+#              #
#    Updated: 2019/10/13 15:21:58 by cschoen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
GCC = gcc -Wall -Wextra -Werror -g
SRCNAME = ft_strlen.c ft_strlcat.c ft_memcmp.c ft_atoi.c ft_isascii.c \
		ft_isprint.c ft_tolower.c ft_toupper.c ft_isalnum.c ft_isalpha.c \
		ft_isdigit.c ft_strcmp.c ft_strncmp.c ft_strdup.c ft_strchr.c \
		ft_strrchr.c ft_strstr.c ft_strnstr.c ft_strcat.c ft_strncat.c \
		ft_strcpy.c ft_strncpy.c ft_bzero.c ft_memset.c ft_memchr.c \
		ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memalloc.c ft_memdel.c \
		ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c \
		ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c \
		ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_itoa.c ft_putchar.c \
		ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c ft_putstr_fd.c \
		ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c \
		ft_lstadd.c ft_lstiter.c ft_lstmap.c ft_abs.c ft_dabs.c ft_strrev.c \
		ft_lstlen.c ft_lstsplit.c ft_lstabi.c ft_wordcnt.c ft_strstrsplit.c \
		get_next_line.c

OBJNAME = $(SRCNAME:.c=.o)
INCNAME = libft.h

SRCDIR = ./src/
OBJDIR = ./obj/
INCDIR = ./inc/

SRC = $(addprefix $(SRCDIR), $(SRCNAME))
OBJ = $(addprefix $(OBJDIR), $(OBJNAME))
INC = $(addprefix $(INCDIR), $(INCNAME))

RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
PURPLE = \033[35m
CYAN = \033[36m
NONE = \033[0m

all: $(NAME)

$(NAME): $(INC) $(OBJDIR) $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@printf "$(PURPLE)Libft:\t$(YELLOW)%-25s$(GREEN)[done]$(NONE)\n" $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@printf "$(PURPLE)Libft:\t$(BLUE)%-25s$(GREEN)[done]$(NONE)\n" $@

$(OBJDIR)%.o:$(SRCDIR)%.c $(INC)
	@$(GCC) -c -I $(INCDIR) $< -o $@
	@printf "$(PURPLE)Libft:\t$(CYAN)%-25s$(GREEN)[done]$(NONE)\n" $@

clean:
	@/bin/rm -rf $(OBJDIR)
	@printf "$(PURPLE)Libft:\t$(RED)%-25s$(GREEN)[done]$(NONE)\n" $@

fclean:
	@/bin/rm -rf $(OBJDIR)
	@/bin/rm -rf $(NAME)
	@printf "$(PURPLE)Libft:\t$(RED)%-25s$(GREEN)[done]$(NONE)\n" $@

re: fclean all

norm:
	@norminette $(INCDIR) $(SRCDIR)
