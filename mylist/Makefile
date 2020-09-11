LIB=./lib/mylist.c

TEST1=func_test1
TEST2=func_test2
TEST3=func_test3
TEST4=func_test4
TEST5=func_test5

TEST1_EXE=$(TEST1).out
TEST1_SRC=./tests/$(TEST1).c
TEST2_EXE=func_test2.out
TEST2_SRC=./tests/func_test2.c
TEST3_EXE=func_test3.out
TEST3_SRC=./tests/func_test3.c
TEST4_EXE=func_test4.out
TEST4_SRC=./tests/func_test4.c
TEST5_EXE=func_test5.out
TEST5_SRC=./tests/func_test5.c

all:
	gcc -std=c99 -o $(TEST1_EXE) $(TEST1_SRC) $(LIB) -I./include/
	gcc -std=c99 -o $(TEST2_EXE) $(TEST2_SRC) $(LIB) -I./include/
	gcc -std=c99 -o $(TEST3_EXE) $(TEST3_SRC) $(LIB) -I./include/
	gcc -std=c99 -o $(TEST4_EXE) $(TEST4_SRC) $(LIB) -I./include/
	gcc -std=c99 -o $(TEST5_EXE) $(TEST5_SRC) $(LIB) -I./include/

test:
	./$(TEST1_EXE) > $(TEST1).youranswer
	diff $(TEST1).youranswer $(TEST1).answer >> scoring_result
	./$(TEST2_EXE) > $(TEST2).youranswer
	diff $(TEST2).youranswer $(TEST2).answer >> scoring_result
	./$(TEST3_EXE) > $(TEST3).youranswer
	diff $(TEST3).youranswer $(TEST3).answer >> scoring_result
	./$(TEST4_EXE) > $(TEST4).youranswer
	diff $(TEST4).youranswer $(TEST4).answer >> scoring_result
	./$(TEST5_EXE) > $(TEST5).youranswer
	diff $(TEST5).youranswer $(TEST5).answer >> scoring_result
