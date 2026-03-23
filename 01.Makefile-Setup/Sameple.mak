# =============================================================================
# Cross-Platform Makefile (Windows / macOS / Linux)
# =============================================================================

# --- OS 감지 ----------------------------------------------------------------

# 변수 참조 | $(cc) | 변수 CC 의 값
# 함수 호출 | $(shell uname -s) | shell 명령어 실행

# debug: $(OBJS)	<- 타겟
# 	gcc -g -o app	<- 레시피

# Windows XP 이후 모든 Windows => Windows_NT
# OS 라는 건 Windows 에서 만든 환경변수임
# 그래서 macOS / Linux 는 해당 값이 항상 비어있음 (Empty String)
# 때문에 uname -s 를 써야함 (-s 는 system name)
# macOS 의 uname -s => Darwin
# Linux 의 uname -s => Linux

ifeq ($(OS), Windows_NT)
	PLATFORM := Windows
	EXE_EXT := .exe
else
	UNAME := $(shell uname -s)
	ifeq ($(UNAME), Darwin)
		PLATFORM := macOS
	else
		PLATFORM := Linux
	endif
	EXE_EXT := 
endif

# Windows / macOS / Linux 모두 bash(sh) 환경이므로 Unix 명령어로 통일
# RM | rm -f | 파일 삭제 (없어도 에러 안 냄)
# RMDIR | rm -rf | 폴더 통쨰로 삭제 (recursive)
# MKDIR | mkdir -p | 폴더 생성 (중간 폴더도 같이 생성 a/b/c 경로 한번에 생성)
RM		:= rm -f
RMDIR	:= rm -rf
MKDIR	:= mkdir -p

# 프로젝트 설정
TARGET		:= app$(EXE_EXT)
CXX			:= g++				#C++ 컴파일러
# 항상 적용되는 컴파일 옵션
CXXFLAGS	:= -std=c++20 -Wall -Wextra -Wpedantic #C++20 / 경고 전부 표시 / 추가 경고 표시 / 표준 엄격히 준수
# 디버그 빌드 옵션
DBGFLAGS	:= -g -O0 -DDEBUG	#디버그 정보 포함 (중단점 등) / 최적화 없음 (디버깅 쉽게) / #define DEBUG 활성화
# 릴리즈 빌드 옵션
RELFLAGS	:= -O2 -DNDEBUG		#최적화 레벨2 (빠르게) / #define NDEBUG -> assert 비활성화

# 디렉토리
SRC_DIR := src
INC_DIR := include
OBJ_DIR := obj
BIN_DIR := bin

# 소스 / 오브젝트 파일 자동 수집
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS)) # 무엇을(패턴), 어떻게(결과), 어디에서 (대상목록)

# 최종 실행 파일 경로
BIN_TARGET := $(BIN_DIR)/$(TARGET)

# 기본 타겟 : Debug 빌드
.PHONY: all debug release clean rebuild info # 이 타겟은 파일이 아님 선언 (항상 실행하도록 선언)

all: debug # make -> all 실행 / make debug -> debug 실행

debug: CXXFLAGS += $(DBGFLAGS)
debug: $(BIN_TARGET)
	@echo ">>> [$(PLATFORM)] Debug build complete: $(BIN_TARGET)"

release: CXXFLAGS += $(RELFLAGS)
release: $(BIN_TARGET)
	@echo ">>> [$(PLATFORM)] Release build complete: $(BIN_TARGET)"

# 링크
# .o 파일들을 링크해서 실행파일을 만드는 단계
# $@ : 자동 변수 -> 자동으로 bin/app.exe 채움
# $^ : 자동 변수 -> 자동으로 모든 의존성 채움
$(BIN_TARGET): $(OBJS) | $(BIN_DIR) #<- 준비 조건을 모두 충족했는지 확인 (없으면 먼저 컴파일 및 생성)
	$(CXX) $(CXXFLAGS) -o $@ $^

# 컴파일
# $< : 자동 변수 -> 첫 번째 의존성
# 1 : 1 이라서 $< 이든 $^ 이든 상관없음
# 
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

# 디렉토리 생성
$(BIN_DIR):
	@$(MKDIR) $(BIN_DIR)

$(OBJ_DIR):
	@$(MKDIR) $(OBJ_DIR)

# 청소
clean:
	@$(RMDIR) $(OBJ_DIR) $(BIN_DIR)
	@echo ">>> Clean done."

rebuild: clean all # make 에게 clean 이랑 all 실행해 라고 지시

# 정보 출력 (mingw32-make info 치면 정보 출력)
info:
	@echo "Platform : $(PLATFORM)"
	@echo "Compiler : $(CXX)"
	@echo "Target : $(BIN_TARGET)"
	@echo "Sources : $(SRCS)"
	@echo "Objects : $(OBJS)"
	@echo "CXXFLAGS : $(CXXFLAGS)"