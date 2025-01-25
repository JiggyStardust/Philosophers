# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saaraniemela <saaraniemela@student.42.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/18 13:06:45 by sniemela          #+#    #+#              #
#    Updated: 2025/01/25 11:38:26 by saaraniemel      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



CFLAGS = -Wall -Werror -Wextra
CC = cc

NAME = libft.a

SOURCES = ft_atoi.c \
		  ft_bzero.c \
		  ft_calloc.c \
		  ft_isalnum.c \
		  ft_isalpha.c \
		  ft_isascii.c \
		  ft_isdigit.c \
		  ft_isprint.c \
		  ft_itoa.c \
		  ft_memchr.c \
		  ft_memcmp.c \
		  ft_memcpy.c \
		  ft_memmove.c \
		  ft_memset.c \
		  ft_putchar_fd.c \
		  ft_putendl_fd.c \
		  ft_putnbr_fd.c \
		  ft_putstr_fd.c \
		  ft_split.c \
		  ft_strchr.c \
		  ft_strdup.c \
		  ft_striteri.c \
		  ft_strjoin.c \
		  ft_strlcat.c \
		  ft_strlcpy.c \
		  ft_strlen.c \
		  ft_strmapi.c \
		  ft_strncmp.c \
		  ft_strndup.c \
		  ft_strnstr.c \
		  ft_strrchr.c \
		  ft_strtrim.c \
		  ft_substr.c \
		  ft_tolower.c \
		  ft_toupper.c \
		  ft_printf.c \
		  ft_putnbr.c \
		  ft_puthexadec.c \
		  get_next_line.c 

BON_SRCS = ft_lstadd_back_bonus.c \
		   ft_lstadd_front_bonus.c \
		   ft_lstclear_bonus.c \
		   ft_lstdelone_bonus.c \
		   ft_lstiter_bonus.c \
		   ft_lstlast_bonus.c \
		   ft_lstmap_bonus.c \
		   ft_lstnew_bonus.c \
		   ft_lstsize_bonus.c

OBJS = $(SOURCES:.c=.o)
OBJS_BONUS = $(BON_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

bonus: .bonus

.bonus: $(OBJS) $(OBJS_BONUS)
	ar rcs $(NAME) $(OBJS) $(OBJS_BONUS)
	@touch .bonus

clean:
	rm -f $(OBJS) $(OBJS_BONUS) .bonus

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus

