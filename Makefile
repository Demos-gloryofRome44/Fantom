CXX = g++
CXXFLAGS = -std=c++20 -I/opt/homebrew/Cellar/sfml/2.6.1/include
LDFLAGS = -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system

TARGET = prog

SRCS = main.cpp Entity.cpp Map.cpp Menu.cpp Game.cpp Enemy.cpp Bullet.cpp

OBJDIR = obj

OBJS = $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean