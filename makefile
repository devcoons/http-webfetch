SRCDIR=src/
BINDIR=bin/
DESTDIR=/$(BINDIR)  
INSTALL_LOCATION=$(DESTDIR)usr/bin/
CC=gcc
NAME=webfetch
CFLAGS:=$(shell dpkg-buildflags --get CFLAGS)
LDFLAGS:=$(shell dpkg-buildflags --get LDFLAGS)
C_FILES := $(wildcard $(SRCDIR)*.c)
O_FILES := $(C_FILES:.c=.o)

all: $(NAME) clean
$(NAME): $(O_FILES)
	@mkdir -p $(BINDIR)
	$(CC) $(LDFLAGS) $(CFLAGS) -o $(BINDIR)$@ $^ -fno-inline -Wall -Werror -O0 -lextend
%.o: %.c
	$(CC) -c -o $@ $< -lextend
clean:
	rm -f $(SRCDIR)*.o
cleanall:
	rm -f $(SRCDIR)*.o
	rm -f $(BINDIR)*
install:
	cp bin/$(NAME) /usr/bin/$(NAME)
uninstall:
	rm /usr/bin/$(NAME)
