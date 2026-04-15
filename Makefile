CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -I include
BUILD    := build
BIN      := bin
OUTPUT   := images/output

FFTW_CFLAGS := $(shell pkg-config --cflags fftw3)
FFTW_LIBS   := $(shell pkg-config --libs fftw3)

SHARED_SRCS := src/core/Image.cpp \
               src/io/ImageIO.cpp \
               src/io/PGM.cpp \
               src/io/PNG.cpp

Q2_SRCS := src/processing/Convolution.cpp \
           src/processing/Filters.cpp \
           assignments/q2-convolution.cpp

Q3_SRCS := src/processing/HistogramEq.cpp \
           assignments/q3-histogram.cpp

Q4_SRCS := src/processing/Median.cpp \
           assignments/q4-median_s_and_p.cpp

Q5_SRCS := assignments/q5.cpp

SHARED_OBJS := $(patsubst %.cpp, $(BUILD)/%.o, $(SHARED_SRCS))
Q2_OBJS     := $(patsubst %.cpp, $(BUILD)/%.o, $(Q2_SRCS))
Q3_OBJS     := $(patsubst %.cpp, $(BUILD)/%.o, $(Q3_SRCS))
Q4_OBJS     := $(patsubst %.cpp, $(BUILD)/%.o, $(Q4_SRCS))
Q5_OBJS     := $(patsubst %.cpp, $(BUILD)/%.o, $(Q5_SRCS))

.PHONY: all q2 q3 q4 q5 clean

all: q2 q3 q4 q5

q2: $(BIN)/q2-convolution

q3: $(BIN)/q3-histogram

q4: $(BIN)/q4-median_s_and_p

q5: $(BIN)/q5

$(BIN)/q2-convolution: $(SHARED_OBJS) $(Q2_OBJS) | $(BIN) $(OUTPUT)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BIN)/q3-histogram: $(SHARED_OBJS) $(Q3_OBJS) | $(BIN) $(OUTPUT)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BIN)/q4-median_s_and_p: $(SHARED_OBJS) $(Q4_OBJS) | $(BIN) $(OUTPUT)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BIN)/q5: $(SHARED_OBJS) $(Q5_OBJS) | $(BIN) $(OUTPUT)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(FFTW_LIBS)



$(BUILD)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(FFTW_CFLAGS) -c $< -o $@

$(BIN):
	@mkdir -p $(BIN)

$(OUTPUT):
	@mkdir -p $(OUTPUT)

clean:
	rm -rf $(BUILD) $(BIN)
