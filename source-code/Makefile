# executable names, for our own makefile we only use EXE no rule for TEST (yet atleast)
EXE = project
TEST = test

# our own makefile uses only TEST_OBJS, the makefile from the mps use the other 2
TEST_OBJS = project.o recommendation_generator.o graph.o actor_graph.o genre_graph.o test.o PNG.o HSLAPixel.o lodepng.o

# these are not used in our own test functions its for the catch makefile 
# when we finally compile our code, and if we use our own makefile, we will make use of the OBJS macro
EXE_OBJS = main.o project.o recommendation_generator.o graph.o actor_graph.o genre_graph.o PNG.o HSLAPixel.o lodepng.o
#OBJS = main.o test.o project.o recommendation_generator.o graph.o actor_graph.o genre_graph.o

#this is for catch testing stuff
#include cs225/make/cs225.mk

# for all non catch based testing

# all flags used and compiler name and stuff
CXX = clang++
CXXFLAGS = $(CS225) -std=c++1y -stdlib=libstdc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libstdc++ -lc++abi -lm

# Custom Clang version enforcement Makefile rule:
ccred=$(shell echo -e "\033[0;31m")
ccyellow=$(shell echo -e "\033[0;33m")
ccend=$(shell echo -e "\033[0m")

IS_EWS=$(shell hostname | grep "ews.illinois.edu")
IS_CORRECT_CLANG=$(shell clang -v 2>&1 | grep "version 6")
ifneq ($(strip $(IS_EWS)),)
ifeq ($(strip $(IS_CORRECT_CLANG)),)
CLANG_VERSION_MSG = $(error $(ccred) On EWS, please run 'module load llvm/6.0.1' first when running CS225 assignments. $(ccend))
endif
else
CLANG_VERSION_MSG = $(warning $(ccyellow) Looks like you are not on EWS. Be sure to test on EWS before the deadline. $(ccend))
endif

.PHONY: all test clean

# rule for only "make"
all: $(EXE)

# this file is made when we type only make, its name will be "project"
# the object files used in the copilation of this executable are in the TEST_OBJS macro
# so update it if you want ot change which files will be used for testing
# this rule links all object files to make the executable
$(EXE) : $(EXE_OBJS)
	$(LD) $(EXE_OBJS) $(LDFLAGS) -o $(EXE)

# for the test
$(TEST) : $(TEST_OBJS)
	$(LD) $(TEST_OBJS) $(LDFLAGS) -o $(TEST)

# rules for the object files start here
# add new rules according to test and files being used
# this is not linking so for example if we want graph.o, we will have graph.h and graph.cpp and structures.h in the rule
# also keep in mind the order of files is very important
# compiler starts compiliing files from right to left, so header files come on the right and cpp on the left
# for example i want to make graph.o, so i will order the files like this:
# graph.cpp graph.h structures.h
# we need structures.h for struct definitions used in graph class
# we need graph.h for all declarations in graph.cpp hence the order

# project.h recommendation_generator.h graph.h genre_graph.h actor_graph.h structures.h
main.o: main.cpp project.o
	$(CXX) $(CXXFLAGS) main.cpp

# test.h project.h recommendation_generator.h graph.h genre_graph.h actor_graph.h structures.h
test.o: test.cpp project.o
	$(CXX) $(CXXFLAGS) test.cpp

# project.h recommendation_generator.h graph.h structures.h
project.o: project.cpp recommendation_generator.o
	$(CXX) $(CXXFLAGS) project.cpp
# recommendation_generator.o

# recommendation_generator.h graph.h genre_graph.h actor_graph.h structures.h
recommendation_generator.o: recommendation_generator.cpp graph.o genre_graph.o actor_graph.o
	$(CXX) $(CXXFLAGS) recommendation_generator.cpp

# graph.h structures.h cs225/PNG.h cs225/HSLAPixel.h
graph.o: graph.cpp PNG.o
	$(CXX) $(CXXFLAGS) graph.cpp

# actor_graph.h graph.h structures.h
actor_graph.o: actor_graph.cpp
	$(CXX) $(CXXFLAGS) actor_graph.cpp

# genre_graph.h graph.h structures.h
genre_graph.o: genre_graph.cpp
	$(CXX) $(CXXFLAGS) genre_graph.cpp

# cs225/PNG.h cs225/HSLAPixel.h cs225/lodepng/lodepng.h cs225/RGB_HSL.h
PNG.o: cs225/PNG.cpp HSLAPixel.o lodepng.o
	$(CXX) $(CXXFLAGS) cs225/PNG.cpp

# cs225/HSLAPixel.h
HSLAPixel.o: cs225/HSLAPixel.cpp
	$(CXX) $(CXXFLAGS) cs225/HSLAPixel.cpp

# cs225/lodepng/lodepng.h
lodepng.o: cs225/lodepng/lodepng.cpp
	$(CXX) $(CXXFLAGS) cs225/lodepng/lodepng.cpp

# this is the generic clean rule works no matter how many rules you add above
# deletes all .o files or executables
# if in the future we add and .png file and use our own makefile, we will have to update this
clean :
	-rm -f *.o *.gch *.png $(EXE) $(TEST)
