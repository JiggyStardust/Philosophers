RESET 			= \033[0;39m
ORANGE 			= \e[1m\e[38;5;202m
YELLOW 			= \033[0;93m
YELLOW_BOLD		= \033[1;93m
GREEN			= \033[1;92m
CYAN 			= \033[0;96m
CYAN_BOLD 		= \033[1;96m
BLUE 			= \033[0;94m
BLUE_BOLD 		= \033[1;94m

OBJ_READY		= echo "📥 $(ORANGE)Compiled philo files!$(RESET)"
COMP_LIBFT		= echo "📝 $(YELLOW)Compiling Libft...$(RESET)"
LIBFT_READY		= echo "📝 $(YELLOW_BOLD)Libft compiled!$(RESET)"
MS_READY		= echo "🤖 $(GREEN)philo ready!$(RESET)"
CLEANING		= echo "💧 $(CYAN)Cleaning...$(RESET)"
CLEANED			= echo "💧 $(CYAN_BOLD)Successfully cleaned all object files!$(RESET)"
FCLEANING		= echo "🧼 $(BLUE)Deep cleaning...$(RESET)"
FCLEANED		= echo "🧼 $(BLUE_BOLD)Successfully cleaned all executable files!$(RESET)"
REMAKE			= echo "💡 $(GREEN)Successfully cleaned and rebuilt everything!$(RESET)"

NAME			= philo

SRCDIR			= srcs
OBJDIR			= objs
LIBDIR			= libft
INCLUDE			= includes

CFLAGS			= -Wall -Wextra -Werror -I $(INCLUDE)
LIBFT			= $(LIBDIR)/libft.a

SRCS			= $(SRCDIR)/main.c \

OBJS			= $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(COMP_LIBFT)
	@make -s -C $(LIBDIR) > /dev/null
	@$(LIBFT_READY)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@cc -c $(CFLAGS) $< -o $@

$(NAME): $(OBJS)
	@cc $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@$(OBJ_READY)
	@chmod 777 $(NAME)
	@$(MS_READY)

clean:
	@$(CLEANING)
	@rm -rf $(OBJDIR)
	@make clean -s -C $(LIBDIR)
	@$(CLEANED)

fclean: clean
	@$(FCLEANING)
	@rm -rf $(NAME)
	@make fclean -s -C $(LIBDIR)
	@rm -rf libft.a
	@$(FCLEANED)

re:	fclean all
	@$(REMAKE)

.PHONY: all clean fclean re libft