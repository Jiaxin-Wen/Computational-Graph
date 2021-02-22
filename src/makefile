CPPLIST = $(wildcard *.cpp)
TARGET = $(patsubst %.cpp, %.o, $(CPPLIST))
SRC_FILES += $(filter-out main1.o main2.o main3.o main4.o, $(TARGET))

all: $(TARGET) main1 main2 main3 main4

%.o:%.cpp
	g++ -c $< -o $@ -std=c++11
main1: main1.o $(SRC_FILES)
	g++ main1.o $(SRC_FILES) -o main1 -std=c++11
main2: main2.o $(SRC_FILES)
	g++ main2.o $(SRC_FILES) -o main2 -std=c++11
main3: main3.o $(SRC_FILES)
	g++ main3.o $(SRC_FILES) -o main3 -std=c++11
main4: main4.o $(SRC_FILES)
	g++ main4.o $(SRC_FILES) -o main4 -std=c++11

.PHONY: clean cleanall
clean:
	rm -f $(TARGET)
cleanall:
	rm -f $(TARGET)
	rm -f main1 main2 main3 main4
