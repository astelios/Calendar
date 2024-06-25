all: compile

run: compile
	./calendar

compile:
	gcc calendar.c -o calendar

clean:
	rm calendar