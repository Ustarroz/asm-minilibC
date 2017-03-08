##
## Makefile for malloc in /home/puilla_e/semestre4/psu/PSU_2016_malloc
## 
## Made by Edouard Puillandre
## Login   <puilla_e@epitech.net>
## 
## Started on  Mon Jan 30 13:49:30 2017 Edouard Puillandre
## Last update Wed Mar  8 11:38:44 2017 puilla_e
##

ASM	= nasm -f elf64 

LD	= ld

RM	= rm -f

LIBNAME	= libasm.so

LIBSRC	= minilib.asm

LIBOBJ	= $(LIBSRC:.asm=.o)

$(LIBNAME):
	$(ASM) $(LIBSRC);
	$(LD) -shared -o $(LIBNAME) $(LIBOBJ)

all: $(LIBNAME)

clean:
	$(RM) $(LIBOBJ)

fclean: clean
	$(RM) $(LIBNAME)

re: fclean all

.PHONY: all clean fclean re
