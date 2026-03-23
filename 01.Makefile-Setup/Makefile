# =============================================================================
# Cross-Platform Makefile (Windows / macOS / Linux)
# =============================================================================

# --- OS 감지 ----------------------------------------------------------------
ifeq ($(OS), Windows_NT)
    PLATFORM := Windows
    EXE_EXT  := .exe
else
    UNAME := $(shell uname -s)
    ifeq ($(UNAME), Darwin)
        PLATFORM := macOS
    else
        PLATFORM := Linux
    endif
    EXE_EXT  :=
endif

# Windows / macOS / Linux 모두 bash(sh) 환경이므로 Unix 명령어로 통일
RM    := rm -f
RMDIR := rm -rf
MKDIR := mkdir -p

# --- 프로젝트 설정 -----------------------------------------------------------
TARGET   := app$(EXE_EXT)
CXX      := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic
DBGFLAGS := -g -O0 -DDEBUG
RELFLAGS := -O2 -DNDEBUG

# --- 디렉토리 ---------------------------------------------------------------
SRC_DIR := src
INC_DIR := include
OBJ_DIR := obj
BIN_DIR := bin

# --- 소스 / 오브젝트 파일 자동 수집 -----------------------------------------
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# --- 최종 실행 파일 경로 -----------------------------------------------------
BIN_TARGET := $(BIN_DIR)/$(TARGET)

# =============================================================================
# 기본 타겟 : Debug 빌드
# =============================================================================
.PHONY: all debug release clean rebuild info

all: debug

debug: CXXFLAGS += $(DBGFLAGS)
debug: $(BIN_TARGET)
	@echo ">>> [$(PLATFORM)] Debug build complete: $(BIN_TARGET)"

release: CXXFLAGS += $(RELFLAGS)
release: $(BIN_TARGET)
	@echo ">>> [$(PLATFORM)] Release build complete: $(BIN_TARGET)"

# --- 링크 -------------------------------------------------------------------
$(BIN_TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# --- 컴파일 -----------------------------------------------------------------
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

# --- 디렉토리 생성 -----------------------------------------------------------
$(BIN_DIR):
	@$(MKDIR) $(BIN_DIR)

$(OBJ_DIR):
	@$(MKDIR) $(OBJ_DIR)

# --- 청소 -------------------------------------------------------------------
clean:
	@$(RMDIR) $(OBJ_DIR) $(BIN_DIR)
	@echo ">>> Clean done."

rebuild: clean all

# --- 정보 출력 ---------------------------------------------------------------
info:
	@echo "Platform  : $(PLATFORM)"
	@echo "Compiler  : $(CXX)"
	@echo "Target    : $(BIN_TARGET)"
	@echo "Sources   : $(SRCS)"
	@echo "Objects   : $(OBJS)"
	@echo "CXXFLAGS  : $(CXXFLAGS)"
