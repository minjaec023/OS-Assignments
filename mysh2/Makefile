CC=gcc -std=c99
LIB=-lpthread

all:
	$(CC) -o mysh ./src/mysh.c ./src/commands.c \
		./lib/parser.c ./lib/fs.c -I./include \
		$(LIB)

unit_test:
	$(CC) -o unit_test ./lib/parser.c ./tests/parser_test.c\
		-I./include $(LIB)
	./unit_test

func_test:
	touch scoring.txt
	rm scoring.txt
	pwd > answer1.txt
	./mysh < sample1.input > your_answer1.txt
	diff your_answer1.txt answer1.txt >> scoring.txt
	./mysh < sample2.input > your_answer2.txt
	diff your_answer2.txt answer2.txt >> scoring.txt
	./mysh < sample3.input > your_answer3.txt
	diff your_answer3.txt answer3.txt >> scoring.txt
	./mysh < sample4.input > your_answer4.txt 2> your_answer4.err
	diff your_answer4.txt answer4.txt >> scoring.txt
	diff your_answer4.err answer4.err >> scoring.txt
	./mysh < sample5.input > your_answer5.txt
	diff your_answer5.txt answer5.txt >> scoring.txt
	./mysh < sample6.input > your_answer6.txt
	diff your_answer6.txt answer6.txt >> scoring.txt
	./mysh < sample7.input > your_answer7.txt 2> your_answer7.err
	diff your_answer7.txt answer7.txt >> scoring.txt
	diff your_answer7.err answer7.err >> scoring.txt
