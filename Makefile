NAME = lem-in

LIBMLX = ./mlx/libmlx.a

SRCSDIR = ./srcs/


SRCS =	${SRCSDIR}lem-in.c \
		${SRCSDIR}utils.c 


HEADERDIR = includes/

HEADER = utils.h \
		lem-in 


OBJ = $(SRCS:.c=.o)

CC = clang

FLAGS =  -g3

IFLAG = -I$(HEADERDIR)  -Imlx/

.c.o:
	@$(CC) $(IFLAG) $(FLAGS) -c $< -o $(<:.c=.o)

all : $(NAME)


$(NAME) :  $(LIBMLX) $(OBJ)
	@$(CC)  $(OBJ) -o $(NAME) $(FLAGS) $(IFLAG) -L./mlx -lmlx -lXext -lX11   -lm

$(LIBMLX) :
	@${MAKE} -sC mlx/

clean :
	@rm -f $(OBJ)
	@rm -f $(OBJ_BONUS)
	@${MAKE} clean -sC mlx/

fclean : clean
	@rm -f $(NAME)
	@${MAKE} clean -sC mlx/

re : fclean all

.PHONY : all clean fclean re 
