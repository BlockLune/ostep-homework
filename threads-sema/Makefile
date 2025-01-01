TARGETS = fork-join

CFLAGS = -Wall -pthread

.PHONY: all clean

all: $(TARGETS)

clean:
	rm -f $(TARGETS)

%: %.c
	gcc $(CFLAGS) -o $@ $<
