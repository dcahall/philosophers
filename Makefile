NAME			=	philo

BONUS			=	bonus

LIBFT_PATH		=	libft/

SRCS_PATH		=	mandatory/

BONUS_PATH		=	bonus/

HEADER_PATH		=	includes/

LIBFT			=	libft.a

SRCS_LST		=	main.c			parser.c			init.c\
					utils.c			philo_work.c	

B_SRCS_LST		=	main_bonus.c	parser_bonus.c		init_bonus.c\
					utils_bonus.c	philo_work_bonus.c

SRCS			=	$(addprefix $(SRCS_PATH), $(SRCS_LST))

B_SRCS			=	$(addprefix $(BONUS_PATH), $(B_SRCS_LST))

HEADER			=	$(addprefix $(HEADER_PATH), philosophers.h)

OBJS			=	$(patsubst %.c, %.o, $(SRCS))

B_OBJS			=	$(patsubst %.c, %.o, $(B_SRCS))

INCLUDES		=	-I$(HEADER_PATH) -I$(LIBFT_PATH)

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror $(INCLUDES)

RM				=	rm -f

.PHONY		:	all clean fclean re bonus

all			:	$(NAME)
	
$(NAME)		:	$(OBJS) $(HEADER)
	$(MAKE) -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) -L$(LIBFT_PATH) -lft $(SRCS) -o $(NAME)

bonus		:	$(BONUS)

$(BONUS)	:	$(B_OBJS) $(HEADER)
	$(MAKE) -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) -L$(LIBFT_PATH) -lft $(B_SRCS) -o $(NAME)	

%.o			:	%.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean		:
	$(MAKE) clean -C $(LIBFT_PATH)
	$(RM) $(OBJS) $(B_OBJS)

fclean		:	clean
	$(MAKE) fclean -C $(LIBFT_PATH)
	$(RM) $(NAME) 

re			:	fclean all