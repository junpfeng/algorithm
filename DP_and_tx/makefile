src = $(wildcard *.cpp)  # 外面包个$()类似与shell的命令代换
targets = $(patsubst %.cpp, %, $(src))

CPP = g++
CFLAGS = -Wall -g

all : $(targets)

$(targets):%:%.cpp
	$(CPP) $< -o $@ $(CFLAGS)

.PHONY :clean all

clean:
	rm -rf $(targets) 
