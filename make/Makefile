BONUS_NAME		=	philo_bonus

MANDATORY_NAME	=	philo

LIBFT_PATH		=	../libft/

SRCS_PATH		=	../philo/

BONUS_PATH		=	../philo_bonus/

HEADER_PATH		=	../includes/

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

ifdef BONUS
		OBJECTS = $(B_OBJS)
else
		OBJECTS = $(OBJS)
endif

ifdef NAME_DEFINE
		NAME 	= $(BONUS_NAME)
else
		NAME	= $(MANDATORY_NAME)
endif

.PHONY		:	all clean fclean re bonus

all			:	$(NAME)
	
$(NAME)		:	$(OBJECTS) $(HEADER)
	$(MAKE) -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) -L$(LIBFT_PATH) -lft $(OBJECTS) -o $(NAME)

bonus		:
	@make BONUS=1 NAME_DEFINE=2 all

%.o			:	%.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean		:
	$(MAKE) clean -C $(LIBFT_PATH)
	$(RM) $(OBJS) $(B_OBJS)

fclean		:	clean
	$(MAKE) fclean -C $(LIBFT_PATH)
	$(RM) $(MANDATORY_NAME) $(BONUS_NAME) 

re			:	fclean all