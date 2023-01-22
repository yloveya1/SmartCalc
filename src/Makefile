CC = g++ -std=c++17 -Wall -Wextra -Werror -pedantic
QMAKE_PATH = qmake
LIN_FLAGS := -lgtest -lgmock -pthread
ifeq ($(shell uname), Linux)
LIN_FLAGS += -lpthread -pthread -lrt -lm -lsubunit
endif
GCOVFLAGS := -fprofile-arcs -ftest-coverage
TEST_SOURCE = source/tests.cpp source/model.cpp
D_FILES = ../objs/$(patsubst %.cpp, %.d, $(TEST_SOURCE))

TEST_OBJ = $(TEST_SOURCE:.cpp=.o)
	
%.o: %.cpp
	@mkdir -p objs
	$(CC) $(LIN_FLAGS) -c $< -o $(addprefix objs/, $(notdir $@)) -MD

include $(wildcard objs/*.d)

all: run

install: clean
	mkdir ../install
	qmake source/New_calculator.pro -o ../install/Makefile
	make -C ../install

run:
ifeq ("$(shell test -e ../install/New_calculator.app && echo yes)", "yes")
	open ../install/./New_calculator*
else
	make install
	open ../install/./New_calculator*
endif

uninstall:
	rm -rf ../install

clean:
	rm -rf ../install build report.info \
	rm -rf *.tgz build/*bak \
	rm -rf objs finish
	rm -rf test check_res *.user
	rm -rf build-New_calculator-Desktop_x86_darwin_generic_mach_o_64bit-Debug

dvi:
	open doc/doc.pdf

dist:
	rm -rf Calculator.1.0
	mkdir Calculator.1.0
	cp -r Makefile source Calculator.1.0/
	tar cvzf ./Calculator.tgz Calculator.1.0/
	rm -rf Calculator.1.0/


tests: $(TEST_OBJ)
	$(CC)  $(addprefix objs/, $(notdir $(TEST_OBJ))) -o test $(LIN_FLAGS)
	./test

gcov_report: LIN_FLAGS += $(GCOVFLAGS) 
gcov_report: tests
	lcov -t report -o report.info -c -d . --no-external
	genhtml report.info -o finish
	open finish/index.html

clang:
	clang-format -i source/*.cpp source/*.h


.PHONY: all install run uninstall clean dvi dist gcov_report clean_tests
