SRCS = srcs/mainTime.cpp

OBJS_FT = $(addprefix ${OBJDIR_FT}/,${SRCS:.cpp=.o})
OBJS_STD = $(addprefix ${OBJDIR_STD}/,${SRCS:.cpp=.o})

NAME_FT = ft_containers
NAME_STD = std_containers

DEPF = -MMD -MP
DEP_FT = ${OBJS_FT:.o=.d}
DEP_STD = ${OBJS_STD:.o=.d}

OBJDIR_FT = helper_files_ft
OBJDIR_STD = helper_files_std

CC = c++
RM = rm -f
CFLAGS = -g3 -Wall -Wextra -Werror -std=c++98

all: ${NAME_FT} $(NAME_STD)

RED=\e[31m
GREEN=\e[32m
YELLOW=\e[33m
STOPCOLOR=\e[0m


$(NAME_FT)	: ${OBJS_FT}
	${CC} ${CFLAGS} ${DEPF} ${OBJS_FT} -o $@
	@echo -e "${GREEN}Created ft_containers results file${STOPCOLOR}"

$(NAME_STD)	: ${OBJS_STD}
	${CC} ${CFLAGS} ${DEPF} ${OBJS_STD} -o $@
	@echo -e "${GREEN}Created std_containers results file${STOPCOLOR}"

${OBJDIR_FT}/%.o:%.cpp
	@mkdir -p ${@D}
	${CC} ${CFLAGS} ${DEPF} -c $< -o $@
	@echo -e "${YELLOW}Created .o and .d files for version FT ${STOPCOLOR}"

${OBJDIR_STD}/%.o:%.cpp
	@mkdir -p ${@D}
	${CC} ${CFLAGS} ${DEPF} -c $< -D STD -o $@
	@echo -e "${YELLOW}Created .o and .d files for version STD${STOPCOLOR}"

clean:
	rm -rf ${OBJDIR_FT} ${OBJDIR_STD}

fclean: clean
	${RM} ${NAME_FT} ${NAME_STD}

re: fclean all

.PHONY: all clean fclean re

-include ${DEP_FT} ${DEP_STD}
