NAME = lem-in
NAME_VISUALIZER = visu-hex

LIBMLX = ./mlx/libmlx.a

SRCSDIR = ./srcs/


SRCS =	${SRCSDIR}lem-in.c \
		${SRCSDIR}utils.c \
		${SRCSDIR}parsing.c 

SRCS_VISUALIZER =	${SRCSDIR}visu-hex.c \
					${SRCSDIR}utils.c \
					${SRCSDIR}parsing.c 


HEADERDIR = includes/

HEADER = utils.h \
		lem-in.h \
		parsing.h 


OBJ = $(SRCS:.c=.o)
OBJ_VISU = $(SRCS_VISUALIZER:.c=.o)

CC = clang

FLAGS =  -g3 -g

IFLAG = -I$(HEADERDIR)  -Imlx/

.c.o:
	@$(CC) $(IFLAG) $(FLAGS) -c $< -o $(<:.c=.o)

all : $(NAME) $(NAME_VISUALIZER)


$(NAME) :  $(LIBMLX) $(OBJ)
	@$(CC)  $(OBJ) -o $(NAME) $(FLAGS) $(IFLAG) -L./mlx -lmlx -lXext -lX11   -lm


$(NAME_VISUALIZER) :  $(LIBMLX) $(OBJ_VISU)
	@$(CC)  $(OBJ_VISU) -o $(NAME_VISUALIZER) $(FLAGS) $(IFLAG) -L./mlx -lmlx -lXext -lX11   -lm

$(LIBMLX) :
	@${MAKE} -sC mlx/

clean :
	@rm -f $(OBJ)
	@rm -f $(OBJ_VISU)
	@rm -f $(OBJ_BONUS)
	@${MAKE} clean -sC mlx/

fclean : clean
	@rm -f $(NAME)
	@rm -f $(NAME_VISUALIZER)
	@${MAKE} clean -sC mlx/

re : fclean all

.PHONY : all clean fclean re 
