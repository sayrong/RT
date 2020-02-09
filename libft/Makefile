# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/07 02:14:29 by cschoen           #+#    #+#              #
#    Updated: 2020/02/09 09:34:27 by cschoen          ###   ########.fr        #
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
		get_next_line.c ft_itoa_base.c ft_printf.c ft_del.c ft_dlstnew.c \
		ft_dlstdel.c ft_dlstdelone.c ft_dlstsplit.c ft_dlstargv.c ft_dlstlen.c

PFTSRCNAME = validator.c parser.c parse_addition.c parse_flag.c \
		parse_width.c parse_precision.c parse_length.c parse_type.c color.c \
		choose_type.c print_wchar.c print_indent.c print_d.c print_u.c \
		print_o.c print_x.c print_f.c print_c.c print_s.c print_p.c \
		print_percent.c print_other.c calculator.c calculate_f.c cleaner.c

OBJNAME = $(SRCNAME:.c=.o)
PFTOBJNAME = $(PFTSRCNAME:.c=.o)
INCNAME = libft.h ftprintf.h

SRCDIR = ./src/
PFTSRCDIR = ./src/libftprintf/
OBJDIR = ./obj/
PFTOBJDIR = ./obj/libftprintf/
INCDIR = ./inc/

SRC = $(addprefix $(SRCDIR), $(SRCNAME))
PFTSRC = $(addprefix $(PFTSRCDIR), $(PFTSRCNAME))
OBJ = $(addprefix $(OBJDIR), $(OBJNAME))
PFTOBJ = $(addprefix $(PFTOBJDIR), $(PFTOBJNAME))
INC = $(addprefix $(INCDIR), $(INCNAME))

RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
PURPLE = \033[35m
CYAN = \033[36m
NONE = \033[0m

all: $(NAME)

$(NAME): $(INC) $(OBJDIR) $(OBJ) $(PFTOBJDIR) $(PFTOBJ)
	@ar rc $(NAME) $(OBJ) $(PFTOBJ)
	@ranlib $(NAME)
	@printf "$(PURPLE)Libft:\t$(YELLOW)%-35s$(GREEN)[done]$(NONE)\n" $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@printf "$(PURPLE)Libft:\t$(BLUE)%-35s$(GREEN)[done]$(NONE)\n" $@

$(PFTOBJDIR):
	@mkdir -p $(PFTOBJDIR)
	@printf "$(PURPLE)Libft:\t$(BLUE)%-35s$(GREEN)[done]$(NONE)\n" $@

$(OBJDIR)%.o:$(SRCDIR)%.c $(INC)
	@$(GCC) -c -I $(INCDIR) $< -o $@
	@printf "$(PURPLE)Libft:\t$(CYAN)%-35s$(GREEN)[done]$(NONE)\n" $@

$(PFTOBJDIR)%.o:$(PFTSRCDIR)%.c $(INC)
	@$(GCC) -c -I $(INCDIR) $< -o $@
	@printf "$(PURPLE)Libft:\t$(CYAN)%-35s$(GREEN)[done]$(NONE)\n" $@

clean:
	@/bin/rm -rf $(OBJDIR)
	@printf "$(PURPLE)Libft:\t$(RED)%-35s$(GREEN)[done]$(NONE)\n" $@

fclean:
	@/bin/rm -rf $(OBJDIR)
	@/bin/rm -rf $(NAME)
	@printf "$(PURPLE)Libft:\t$(RED)%-35s$(GREEN)[done]$(NONE)\n" $@

re: fclean all

norm:
	@norminette $(INCDIR) $(SRCDIR)
