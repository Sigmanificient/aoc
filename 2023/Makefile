.POSIX:
.SUFFIXES:

BUILD_DIR := .build
OUT := aoc

# ↓ `touch .fast` to force multi-threading
ifneq ($(shell find . -name ".fast"),)
    MAKEFLAGS += -j
endif

CC := gcc -std=gnu11

CFLAGS := -pedantic
CFLAGS += -U_FORTIFY_SOURCE
CFLAGS += -Wformat=2

CFLAGS += -MMD -MP
CFLAGS += -fanalyzer
CFLAGS += -pipe

CFLAGS += -O2 -g3 -march=native -mtune=native

CFLAGS += -Wall
CFLAGS += -Waggregate-return
CFLAGS += -Wcast-qual
CFLAGS += -Wconversion
CFLAGS += -Wdisabled-optimization
CFLAGS += -Wduplicated-branches
CFLAGS += -Wduplicated-cond
CFLAGS += -Werror=return-type
CFLAGS += -Wextra
CFLAGS += -Winit-self
CFLAGS += -Winline
CFLAGS += -Wlogical-op
CFLAGS += -Wmissing-prototypes
CFLAGS += -Wredundant-decls
CFLAGS += -Wshadow
CFLAGS += -Wstrict-prototypes
CFLAGS += -Wsuggest-attribute=pure
CFLAGS += -Wundef
CFLAGS += -Wunreachable-code
CFLAGS += -Wwrite-strings
CFLAGS += -iquote .

LDFLAGS += -fwhole-program -flto
LDFLAGS += -fsanitize=address,leak,undefined

VPATH += .
SRC += main.c
SRC += file_reader.c
SRC += strpnum.c

SRC += day_01.c
SRC += day_02.c
SRC += day_03.c
SRC += day_04.c
SRC += day_05.c
SRC += day_06.c
SRC += day_07.c
SRC += day_08.c
SRC += day_09.c
SRC += day_10.c

vpath %.c $(VPATH)

OBJ := $(SRC:%.c=$(BUILD_DIR)/%.o)
DEP := $(OBJ:.o=.d)

RM ?= rm -f
AR ?= ar

ifneq ($(shell command -v tput),)
    ifneq ($(shell tput colors),0)

C_RESET := \033[00m
C_BOLD := \e[1m
C_RED := \e[31m
C_GREEN := \e[32m
C_YELLOW := \e[33m
C_BLUE := \e[34m
C_PURPLE := \e[35m
C_CYAN := \e[36m

    endif
endif

NOW = $(shell date +%s%3N)
STIME := $(call NOW)

TIME_NS = $(shell expr $(call NOW) - $(STIME))
TIME_MS = $(shell expr $(call TIME_NS))
LOG_TIME = echo -e "[ $(C_BLUE)$(call TIME_MS)$(C_RESET) ]"

all: $(OUT)
.PHONY: all

$(BUILD_DIR):
	@ mkdir -p $@

$(OUT): $(BUILD_DIR) .WAIT $(OBJ)
	$(CC) -o $@ $(CFLAGS) $(OBJ) $(LDFLAGS)
	@ $(LOG_TIME) $@

$(BUILD_DIR)/%.o: %.c
	$(CC) -o $@ $(CFLAGS) -c $< || exit 1

clean:
	$(RM) $(SRC:.c=.gcda)
	$(RM) $(SRC:.c=.gcno)
	$(RM) $(OBJ)

fclean: clean
	$(RM) -r $(BUILD_DIR)
	$(RM) $(OUT)

.PHONY: clean fclean

re: fclean .WAIT all
.PHONY: re

-include $(DEP)
