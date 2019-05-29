EXE = graph_example

SRC_DIR = src
OBJ_DIR = obj

SRC = $(wildcard $(SRC_DIR)/*.cc)
OBJ = $(SRC:$(SRC_DIR)/%.cc=$(OBJ_DIR)/%.o)

CPPFLAGS += -Iinclude
CFLAGS += -Wall

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	$(CXX) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)