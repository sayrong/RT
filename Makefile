# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/07 02:04:41 by cschoen           #+#    #+#              #
#    Updated: 2020/02/09 09:32:21 by cschoen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean fclean re norm fullnorm

NAME = RT

LIB_FT = libft.a
LIB_VEC = libvec.a

LFTDIR = ./libft/
VECDIR = ./libvec/
SRCDIR = ./src/
INCDIR = ./inc/
OBJDIR = ./obj/
BINDIR = ./bin/

LFTINC = $(LFTDIR)inc/
VECINC = $(VECDIR)inc/

LFTNAME = $(LFTDIR)$(LIB_FT)
VECNAME = $(VECDIR)$(LIB_VEC)
BINNAME = $(BINDIR)$(NAME)

LIBHEAD = $(LFTINC)libft.h $(LFTINC)ftprintf.h $(VECINC)libvec.h
INCNAME = $(INCDIR)rt.h $(INCDIR)macoskeys.h

SRCNAME = main.c ray_trace.c plane_init.c sphere_init.c deal_key.c error.c \
		intersection_init.c camera_init.c image_init.c color.c \
		cone.c cylinder.c list.c light.c shapeset_init.c validator.c \
		parser.c parse_functions.c parse_light.c parse_shape.c \
		anti_aliasing.c mouse_click.c cleaner.c

LFTSRCNAME = ft_strlen.c ft_strlcat.c ft_memcmp.c ft_atoi.c ft_isascii.c \
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

VECSRCNAME = v3_new.c v3_add.c v3_sub.c v3_scale.c v3_div.c v3_dot.c \
		v3_length_sq.c v3_length.c v3_norm.c v3_cross.c v2_set.c p2_set.c \
		v3_rot_x.c v3_rot_y.c v3_rot_z.c

LFTSRC = $(addprefix $(LFTDIR)src/, $(LFTSRCNAME))
PFTSRC = $(addprefix $(LFTDIR)src/libftprintf/, $(PFTSRCNAME))
VECSRC = $(addprefix $(VECDIR)src/, $(VECSRCNAME))
SRC = $(addprefix $(SRCDIR), $(SRCNAME))
OBJ = $(addprefix $(OBJDIR), $(SRCNAME:.c=.o))

INC = -I $(INCDIR) -I $(LFTINC) -I $(VECINC)

MACOS = -framework OpenGL -framework AppKit

VECINIT = -I $(VECDIR) -L $(VECDIR) -lvec -lm
LFTINIT = -I $(LFTDIR) -L $(LFTDIR) -lft
MLXINIT = -I /usr/local/include -L /usr/local/lib -lmlx $(MACOS)

GCC = gcc -Wall -Wextra -Werror -g

RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
PURPLE = \033[35m
CYAN = \033[36m
NONE = \033[0m

all: $(BINNAME)

$(BINNAME): $(OBJDIR) $(OBJ) $(LFTSRC) $(PFTSRC) $(VECSRC) $(INCNAME) $(LIBHEAD)
	@$(MAKE) -C $(LFTDIR)
	@printf "$(PURPLE)RT:\t$(YELLOW)%-35s$(GREEN)[done]$(NONE)\n" $(LIB_FT)
	@$(MAKE) -C $(VECDIR)
	@printf "$(PURPLE)RT:\t$(YELLOW)%-35s$(GREEN)[done]$(NONE)\n" $(LIB_VEC)
	@mkdir -p $(BINDIR)
	@printf "$(PURPLE)RT:\t$(BLUE)%-35s$(GREEN)[done]$(NONE)\n" $(BINDIR)
	@$(GCC) $(OBJ) $(MLXINIT) $(LFTINIT) $(VECINIT) -I $(INCDIR) -o $(BINNAME)
	@printf "$(PURPLE)RT:\t$(YELLOW)%-35s$(GREEN)[done]$(NONE)\n" $@

$(LIB_FT):
	@$(MAKE) -C $(LFTDIR)
	@printf "$(PURPLE)RT:\t$(YELLOW)%-35s$(GREEN)[done]$(NONE)\n" $@

$(LIB_VEC):
	@$(MAKE) -C $(VECDIR)
	@printf "$(PURPLE)RT:\t$(YELLOW)%-35s$(GREEN)[done]$(NONE)\n" $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@printf "$(PURPLE)RT:\t$(BLUE)%-35s$(GREEN)[done]$(NONE)\n" $@

$(OBJDIR)%.o: $(SRCDIR)%.c $(INCNAME)
	@$(GCC) -c $(INC) $< -o $@
	@printf "$(PURPLE)RT:\t$(CYAN)%-35s$(GREEN)[done]$(NONE)\n" $@

clean:
	@$(MAKE) -C $(LFTDIR) clean
	@$(MAKE) -C $(VECDIR) clean
	@rm -rf $(OBJDIR)
	@printf "$(PURPLE)RT:\t$(RED)%-35s$(GREEN)[done]$(NONE)\n" $@

fclean:
	@$(MAKE) -C $(LFTDIR) fclean
	@$(MAKE) -C $(VECDIR) fclean
	@rm -rf $(OBJDIR)
	@rm -rf $(BINDIR)
	@printf "$(PURPLE)RT:\t$(RED)%-35s$(GREEN)[done]$(NONE)\n" $@

re: fclean all

norm:
	@norminette $(INCDIR) $(SRCDIR)

fullnorm: norm
	@$(MAKE) -C $(LFTDIR) norm
	@$(MAKE) -C $(VECDIR) norm
