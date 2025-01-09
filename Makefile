# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lanani-f <lanani-f@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/02 13:08:55 by lanani-f          #+#    #+#              #
#    Updated: 2025/01/09 14:52:01 by lanani-f         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
BLUE_LIGHTER = \033[38;5;123m
BLUE_LIGHT = \033[36m
BLUE = \033[34m
BLUE_LIGHTER_DARK = \033[38;5;32m
BLUE_DARK = \033[38;5;24m
RESET = \033[0m

# Program name
NAME = cub3D

# Directories
SRC_PATH 	= src/
PARSING_DIR = $(SRC_PATH)parsing/
GAME_DIR 	= $(SRC_PATH)game/
RAY_DIR 	= $(SRC_PATH)raycasting/
UTILS_DIR 	= $(SRC_PATH)utils/
MAP_DIR		= $(SRC_PATH)map/
CTRL_DIR	= $(SRC_PATH)controls/

# Source files
PARSING_FILES = parsing_1.c parsing_2.c utils_parsing.c parse_map.c texture_utils_1.c texture_utils_2.c

GAME_FILES = game_init.c game_loop.c texture_handler.c

RAY_FILES = raycasting.c init_ray.c perform_dda.c vectors.c

CTRL_FILES = key_events.c player_movement.c player_rotation.c

MAP_FILES = minimap.c minimap_utils.c minimap_player.c check_map.c

UTILS_FILES = utils.c errors.c free.c clean.c

SRCS_FILES = main.c \
			$(addprefix parsing/, $(PARSING_FILES)) \
			$(addprefix game/, $(GAME_FILES)) \
			$(addprefix raycasting/, $(RAY_FILES)) \
			$(addprefix controls/, $(CTRL_FILES)) \
			$(addprefix map/, $(MAP_FILES)) \
			$(addprefix utils/, $(UTILS_FILES))

SRCS = $(addprefix $(SRC_PATH), $(SRCS_FILES))

# Object files
OBJS_PATH = .objs/
OBJS = $(SRCS:$(SRC_PATH)%.c=$(OBJS_PATH)%.o)

# Libraries and includes
INC_PATH = include/
LIBFT_PATH = ./libft/
LIBFT_LIB = $(LIBFT_PATH)libft.a
MLX_PATH = ./mlx_linux/
MLX_LIB = $(MLX_PATH)libmlx_Linux.a

# Compiler and flags
CC = cc
CFLAGS = -Wall -Werror -Wextra -I$(INC_PATH) -I$(LIBFT_PATH) -I$(MLX_PATH) -g
LFLAGS = -L$(LIBFT_PATH) -lft -L$(MLX_PATH) -lmlx_Linux -lXext -lX11 -lm -lbsd
RM = rm -rf

# Rules
all: $(NAME)

$(NAME): $(LIBFT_LIB) $(MLX_LIB) $(OBJS)
	@echo "$(BLUE_LIGHTER)╔═════════════════════════════════════════╗$(RESET)"
	@echo "$(BLUE_LIGHTER)║           Compiling $(NAME)...            ║$(RESET)"
	@$(CC) $(OBJS) $(LFLAGS) -o $(NAME)
	@echo "$(BLUE_LIGHTER)║  $(NAME) has been created successfully!   ║$(RESET)"
	@echo "$(BLUE_LIGHTER)╚═════════════════════════════════════════╝$(RESET)"

# Object files compilation
$(OBJS_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# Libraries compilation
$(LIBFT_LIB):
	@make -C $(LIBFT_PATH)

$(MLX_LIB):
	@make -C $(MLX_PATH)

clean:
	$(RM) $(OBJS_PATH)
	@make clean -C $(LIBFT_PATH)
	@make clean -C $(MLX_PATH)
	@echo "$(BLUE_LIGHTER_DARK)🧹 Cleaning object files...$(RESET)"

fclean: clean
	$(RM) $(NAME)
	@make fclean -C $(LIBFT_PATH)
	@echo "$(BLUE_DARK)🗑️  Removing $(NAME)...$(RESET)"

re: fclean all
	@echo "$(BLUE_DARK)📚 $(NAME) recompiled!$(RESET)"

.PHONY: all clean fclean re