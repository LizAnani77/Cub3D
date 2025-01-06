# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lizzieananifoli <lizzieananifoli@studen    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/02 13:08:55 by lanani-f          #+#    #+#              #
#    Updated: 2025/01/05 22:19:47 by lizzieanani      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BLUE_LIGHTER = \033[38;5;123m
BLUE_LIGHT = \033[36m
BLUE = \033[34m
BLUE_LIGHTER_DARK = \033[38;5;32m
BLUE_DARK = \033[38;5;24m
RESET = \033[0m


NAME = cub3D

SRC_PATH            =   src/
PARSING_DIR         =   $(SRC_PATH)parsing
CHECK_EXTENSION_DIR =   $(SRC_PATH)check_extension
MAP_DIR             =   $(SRC_PATH)map
RAYCASTING_DIR		=	$(SRC_PATH)raycasting
CONTROLS_DIR		=	$(SRC_PATH)controls
GAME_DIR			=	$(SRC_PATH)game
MINIMAP_DIR			=	$(SRC_PATH)minimap


SRCS_FILES  =   main.c \
                parsing/parsing.c parsing/utils_parsing.c \
                check_extension/cub_extension.c \
				check_file/parse_file.c check_file/utils_file.c check_file/check_valid_data_6elements.c \
                map/check_map.c \
				utils/errors.c utils/free.c \
				# ajout partie liz
				key_events.c \
				player_movement.c \
				player_rotation.c \
				clean.c \
				game_loop.c \
				init_ray.c \
				perform_dda.c \
				raycasting.c \
				vectors.c \
				minimap.c \
				minimap_utils.c \
				minimap_player.c 
				
SRCS        =   $(addprefix $(SRC_PATH), $(SRCS_FILES))

# Fichiers objets générés dans un dossier
OBJS_PATH   =   .objs/
OBJS        =   $(SRCS:$(SRC_PATH)%.c=$(OBJS_PATH)%.o)

# Include et libft
INC_PATH    =   include/
LIBFT_PATH  =   ./libft/
LIBFT_LIB   =   $(LIBFT_PATH)libft.a

CC          =   cc
CFLAGS      =   -Wall -Werror -Wextra -I$(INC_PATH) -I$(LIBFT_PATH) -g
LFLAGS      =   -L$(LIBFT_PATH) -lft -L$(MLX_PATH) -lmlx_Linux -lXext -lX11 -lm -lbsd -lft
RM          =   rm -rf

all: $(NAME)


$(NAME):    $(OBJS) $(LIBFT_LIB)
	@echo "$(BLUE_LIGHTER)╔═════════════════════════════════════════╗$(RESET)"
	@echo "$(BLUE_LIGHTER)║         Compiling $(NAME)...              ║$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "$(BLUE_LIGHTER)║  $(NAME) has been created successfully!   ║$(RESET)"
	@echo "$(BLUE_LIGHTER)╚═════════════════════════════════════════╝$(RESET)"
	
# Compilation des fichiers .c en .o dans .objs/
$(OBJS_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(dir $@) 
	$(CC) $(CFLAGS) -c $< -o $@
	
# Compilation de la libft
$(LIBFT_LIB):
	@make -C $(LIBFT_PATH) --silent

$(OBJS_PATH):
	@echo "$(BLUE_LIGHT)📁 Creating objects directory...$(RESET)"
	@mkdir -p $(OBJS_PATH)

# Nettoyage des objets
clean:
	$(RM) $(OBJS_PATH)
	@make clean -C $(LIBFT_PATH)
	@echo "$(BLUE_LIGHTER_DARK)🧹 Cleaning object files...$(RESET)"

# Nettoyage complet
fclean: clean
	$(RM) $(NAME)
	@make fclean -C $(LIBFT_PATH)
	@echo "$(BLUE_DARK)🗑️  Removing $(NAME)...$(RESET)"

# Recompilation complète
re: fclean all
	@echo "$(BLUE_DARK)📚 $(NAME) recompiled!$(RESET)"

.PHONY: all clean fclean re