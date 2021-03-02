CXX =   g++
CXXFLAGS =	-O0 -g3 -Wall -fmessage-length=0
LINK =	$(CXX)

TARGET = bin/slothjson

TEMP_OBJS = bin/me_test_opt.i

OBJS = bin/main.o \
	bin/perf_test.o \
	bin/sample_test.o \
	bin/me_test_opt.o \
  bin/slothjson.o

INCS = -I include/rapidjson \
	-I include

DEPS = include/rapidjson/rapidjson.h include/mtjson.h

$(TARGET):	$(OBJS)

	$(LINK) -o $(TARGET) $(OBJS)

bin/main.o:	$(DEPS) src/main.cpp
	$(CXX) -c $(CXXFLAGS)  $(INCS) -o bin/main.o src/main.cpp

bin/perf_test.o:	$(DEPS) src/perf_test.cpp
	$(CXX) -c $(CXXFLAGS)  $(INCS) -o bin/perf_test.o src/perf_test.cpp

bin/sample_test.o:	$(DEPS) src/sample_test.cpp
	$(CXX) -c $(CXXFLAGS)  $(INCS) -o bin/sample_test.o src/sample_test.cpp

bin/me_test_opt.o:	$(DEPS) src/me_test_opt.cpp
	$(CXX) -E $(CXXFLAGS)  $(INCS) src/me_test_opt.cpp  -o  bin/me_test_opt.i
	$(CXX) -c $(CXXFLAGS)  $(INCS) -o bin/me_test_opt.o src/me_test_opt.cpp

SLOTHJSON_CPP = include/slothjson.cpp
bin/slothjson.o:	$(DEPS) $(SLOTHJSON_CPP)
	$(CXX) -c $(CXXFLAGS)  $(INCS) -o bin/slothjson.o $(SLOTHJSON_CPP)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) $(TEMP_OBJS)