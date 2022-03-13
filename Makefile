NAME			=	philo

LIBFT_PATH		=	libft/

SRCS_PATH		=	src/

BONUS_PATH		=	bonus/

HEADER_PATH		=	includes/

LIBFT			=	libft.a

SRCS_LST		=	main.c		parser.c	init.c\
					get_time.c

SRCS			=	$(addprefix $(SRCS_PATH), $(SRCS_LST))

HEADER			=	$(addprefix $(HEADER_PATH), philosophers.h)

OBJS			=	$(patsubst %.c, %.o, $(SRCS))

INCLUDES		=	-I$(HEADER_PATH) -I$(LIBFT_PATH)

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror $(INCLUDES)

RM				=	rm -f

.PHONY		:	all clean fclean re bonus

all			:	$(NAME)

%.o			:	%.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@
	
$(NAME)		:	$(OBJS) $(HEADER)
	$(MAKE) -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) -L$(LIBFT_PATH) -lft $(SRCS) -o $(NAME)

clean		:
	$(MAKE) clean -C $(LIBFT_PATH)
	$(RM) $(OBJS) 

fclean		:	clean
	$(MAKE) fclean -C $(LIBFT_PATH)
	$(RM) $(NAME)

re			:	fclean all