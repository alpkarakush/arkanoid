
CXX=g++
CXXFLAGS=-std=c++11 -Wall -pedantic -Wno-long-long -O0 -ggdb
LIB=-lncurses
SRCDIR = src

all: compile doc

run:
	./khudabek

compile: $(SRCDIR)/main.o $(SRCDIR)/name.o $(SRCDIR)/play.o $(SRCDIR)/game.o $(SRCDIR)/object.o $(SRCDIR)/attacker.o $(SRCDIR)/friend.o $(SRCDIR)/rock.o $(SRCDIR)/asteroid.o 
	$(CXX) $(CXXFLAGS)  $^ -o khudabek $(LIB)


$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(SRCDIR)/asteroid.o: $(SRCDIR)/asteroid.cpp $(SRCDIR)/object.h $(SRCDIR)/rect.h $(SRCDIR)/asteroid.h
$(SRCDIR)/attacker.o: $(SRCDIR)/attacker.cpp $(SRCDIR)/object.h $(SRCDIR)/rect.h $(SRCDIR)/attacker.h
$(SRCDIR)/friend.o: $(SRCDIR)/friend.cpp $(SRCDIR)/object.h $(SRCDIR)/rect.h $(SRCDIR)/friend.h
$(SRCDIR)/game.o: $(SRCDIR)/game.cpp $(SRCDIR)/game.h $(SRCDIR)/player.h $(SRCDIR)/clock.h $(SRCDIR)/map.h $(SRCDIR)/object.h $(SRCDIR)/rect.h $(SRCDIR)/friend.h \
 $(SRCDIR)/attacker.h $(SRCDIR)/rock.h $(SRCDIR)/asteroid.h
$(SRCDIR)/main.o: $(SRCDIR)/main.cpp $(SRCDIR)/name.h $(SRCDIR)/player.h $(SRCDIR)/play.h $(SRCDIR)/game.h $(SRCDIR)/clock.h $(SRCDIR)/map.h $(SRCDIR)/object.h \
 $(SRCDIR)/rect.h $(SRCDIR)/friend.h $(SRCDIR)/attacker.h $(SRCDIR)/rock.h $(SRCDIR)/asteroid.h
$(SRCDIR)/name.o: $(SRCDIR)/name.cpp $(SRCDIR)/name.h $(SRCDIR)/player.h $(SRCDIR)/play.h $(SRCDIR)/game.h $(SRCDIR)/clock.h $(SRCDIR)/map.h $(SRCDIR)/object.h \
 $(SRCDIR)/rect.h $(SRCDIR)/friend.h $(SRCDIR)/attacker.h $(SRCDIR)/rock.h $(SRCDIR)/asteroid.h
$(SRCDIR)/object.o: $(SRCDIR)/object.cpp $(SRCDIR)/rect.h $(SRCDIR)/object.h
$(SRCDIR)/play.o: $(SRCDIR)/play.cpp $(SRCDIR)/play.h $(SRCDIR)/game.h $(SRCDIR)/player.h $(SRCDIR)/clock.h $(SRCDIR)/map.h $(SRCDIR)/object.h $(SRCDIR)/rect.h \
 $(SRCDIR)/friend.h $(SRCDIR)/attacker.h $(SRCDIR)/rock.h $(SRCDIR)/asteroid.h
$(SRCDIR)/rock.o: $(SRCDIR)/rock.cpp $(SRCDIR)/object.h $(SRCDIR)/rect.h $(SRCDIR)/rock.h

clean: 
	rm -f khudabek $(SRCDIR)/*.o
	rm -r ./doc 

doc:
	doxygen ./src/conf
	rm -rf ./doc/latex
	cp -r ./doc/html/* ./doc
	rm -rf ./doc/html