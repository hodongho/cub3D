# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yehyun <yehyun@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/19 15:49:02 by yehyun            #+#    #+#              #
#    Updated: 2022/09/27 08:54:35 by yehyun           ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
NAME_BONUS = cub3d_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror
DFLAG = -g2 -fsanitize=address
FRAMEWORK = -framework OpenGL -framework AppKit
RM = rm -f

MLXDIR = mlx/
LIBDIR = libft/
SRC_DIR = srcs/
SRC_BONUS_DIR = srcs_bonus/

SRC = main.c parser.c utils.c parser_utils.c doubly_list.c map.c
SRC_BONUS = 

SRCS = $(addprefix $(SRC_DIR), $(SRC))
OBJS = $(SRCS:.c=.o)

SRCS_BONUS = $(addprefix $(SRC_BONUS_DIR), $(SRC_BONUS))
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@make -C $(MLXDIR)
	@make -C $(LIBDIR)
	@$(CC) $(DFLAG) $(CFLAGS) -L$(MLXDIR) -lmlx -L$(LIBDIR) -lft $(FRAMEWORK) $^ -o $@

%.o : %.c
	@$(CC) $(DFLAG) $(CFLAGS) -Imlx -c $< -o $@

clean :
	@make clean -C $(MLXDIR)
	@make clean -C $(LIBDIR)
	@$(RM) $(OBJS) $(OBJS_BONUS)

fclean :
	@make clean -C $(MLXDIR)
	@make fclean -C $(LIBDIR)
	@$(RM) $(OBJS) $(OBJS_BONUS) $(NAME) $(NAME_BONUS)

re :
	@make fclean
	@make all

bonus : $(NAME_BONUS)

$(NAME_BONUS) : $(OBJS_BONUS)
	@make -C $(MLXDIR)
	@make -C $(LIBDIR)
	@$(CC) $(CFLAGS) -L$(MLXDIR) -lmlx -L$(LIBDIR) -lft $(FRAMEWORK) $^ -o $@

.PHONY : all bonus clean fclean re