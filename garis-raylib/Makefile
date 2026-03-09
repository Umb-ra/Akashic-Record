CC     = gcc
CFLAGS = -Wall -O2 -I. $(shell pkg-config --cflags raylib)
LIBS   = $(shell pkg-config --libs raylib) -lm -ldl -lpthread

TARGET = grafika_dda

SRCS = main.c \
       coords.c \
       src/algo/dda.c \
       src/algo/bresenham.c \
       src/ui/primitives.c \
       src/ui/back_button.c \
       src/ui/cartesian.c \
       src/screens/program1.c \
       src/screens/program2.c \
       src/screens/program3.c \
       src/screens/program4.c \
       src/screens/about.c \
       src/screens/menu.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

run: all
	LIBGL_ALWAYS_SOFTWARE=1 ./$(TARGET)
