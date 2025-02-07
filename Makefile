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
MS_READY		= echo "🤖 $(GREEN)philo ready!$(RESET)"
CLEANING		= echo "💧 $(CYAN)Cleaning...$(RESET)"
CLEANED			= echo "💧 $(CYAN_BOLD)Successfully cleaned all object files!$(RESET)"
FCLEANING		= echo "🧼 $(BLUE)Deep cleaning...$(RESET)"
FCLEANED		= echo "🧼 $(BLUE_BOLD)Successfully cleaned all executable files!$(RESET)"
REMAKE			= echo "💡 $(GREEN)Successfully cleaned and rebuilt everything!$(RESET)"

NAME			= philo

SRCDIR			= srcs
OBJDIR			= objs
INCLUDE			= includes

CFLAGS			= -Wall -Wextra -Werror -I $(INCLUDE)

SRCS			=	$(SRCDIR)/assign_data_nums.c \
					$(SRCDIR)/free_and_destroy.c \
					$(SRCDIR)/init_data.c \
					$(SRCDIR)/philo.c \

OBJS			= $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@cc -c $(CFLAGS) $< -o $@

$(NAME): $(OBJS)
	@cc $(CFLAGS) $(OBJS) -o $(NAME)
	@$(OBJ_READY)
	@chmod 777 $(NAME)
	@$(MS_READY)

clean:
	@$(CLEANING)
	@rm -rf

fclean: clean
	@$(FCLEANING)
	@rm -rf $(NAME)
	@$(FCLEANED)

re:	fclean all
	@$(REMAKE)

.PHONY: all clean fclean re