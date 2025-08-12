CC       := gcc
CPPFLAGS := -Iinclude
CFLAGS   := -std=c11 -Wall -Wextra -Werror -pedantic -O2 -MMD -MP -Iinclude

SRC_DIR   := src
BUILD_DIR := build
TEST_DIR := test

UNITY_PATH := lib/Unity/src
INSTALL_INC_PATH := /usr/local/include/arena
INSTALL_LIB_PATH := /usr/local/lib

SOURCES   := $(wildcard $(SRC_DIR)/*.c)
TEST_SOURCES := $(wildcard $(TEST_DIR)/*.c)
UNITY_SOURCES := $(wildcard $(UNITY_PATH)/*.c)
OBJECTS   := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))
TEST_OBJECTS := $(patsubst $(TEST_DIR)/%.c,$(BUILD_DIR)/test_%.o,$(TEST_SOURCES))
UNITY_OBJECTS := $(patsubst $(UNITY_PATH)/%.c,$(BUILD_DIR)/unity_%.o,$(UNITY_SOURCES))
DEPS      := $(OBJECTS:.o=.d)

LIB_NAME := libarena.a
TARGET   := $(BUILD_DIR)/$(LIB_NAME)
TEST_TARGET := $(BUILD_DIR)/tests

TEST_RESULTS := $(BUILD_DIR)/test_results.txt
TEST_PASSE := `grep -s PASS $(TEST_RESULTS)`
TEST_FAIL := `grep -s FAIL $(TEST_RESULTS)`
TEST_IGNORE := `grep -s IGNORE $(TEST_RESULTS)` 

GREEN  := \033[1;32m
RED    := \033[1;31m
YELLOW := \033[1;33m
BLUE   := \033[1;34m
RESET  := \033[0m

.PHONY: all test clean install uninstall help

all: $(TARGET)

$(BUILD_DIR):
	@mkdir -p $@

$(TARGET): $(OBJECTS)
	ar rcs $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/test_%.o: $(TEST_DIR)/%.c | $(BUILD_DIR)
	$(CC) -I$(UNITY_PATH) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/unity_%.o: $(UNITY_PATH)/%.c | $(BUILD_DIR)
	$(CC) -I$(UNITY_PATH) $(CFLAGS) -c -o $@ $<

$(TEST_TARGET): $(TARGET) $(UNITY_OBJECTS) $(TEST_OBJECTS)
	$(CC) -I$(UNITY_PATH) $(CFLAGS) -o $(TEST_TARGET) $(UNITY_OBJECTS) $(TEST_OBJECTS) $(TARGET)

$(TEST_RESULTS): $(TEST_TARGET)
	@-./$< > $@ 2>&1

test: $(TEST_TARGET)
	@echo "$(BLUE)>>>$(RESET) Running unit tests..."
	@mkdir -p $(BUILD_DIR)
	@./$(TEST_TARGET) > $(TEST_RESULTS) 2>&1 || true

	@echo "$(YELLOW)--- IGNORED ---$(RESET)"
	@grep -s IGNORE $(TEST_RESULTS) || echo "None"
	@echo

	@echo "$(RED)--- FAILURES ---$(RESET)"
	@grep -s FAIL $(TEST_RESULTS) || echo "None"
	@echo

	@echo "$(GREEN)--- PASSED ---$(RESET)"
	@grep -s PASS $(TEST_RESULTS) || echo "None"
	@echo

	@PASSED=$$(grep -c PASS $(TEST_RESULTS) 2>/dev/null); \
	FAILED=$$(grep -c FAIL $(TEST_RESULTS) 2>/dev/null); \
	IGNORED=$$(grep -c IGNORE $(TEST_RESULTS) 2>/dev/null); \
	TOTAL=$$((PASSED + FAILED + IGNORED)); \
	echo "$(BLUE)Summary:$(RESET) $$TOTAL total | $(GREEN)$$PASSED passed$(RESET), $(RED)$$FAILED failed$(RESET), $(YELLOW)$$IGNORED ignored$(RESET)"; \
	[ $$FAILED -eq 0 ]

-include $(DEPS)

clean:
	rm -rf $(BUILD_DIR)

install: $(TARGET)
	@echo "Installing $(LIB_NAME) to $(INSTALL_LIB_PATH)"
	install -d $(INSTALL_LIB_PATH)
	install -m 0755 $(TARGET) $(INSTALL_LIB_PATH)/$(LIB_NAME)
	@echo "Installing headers to $(INSTALL_INC_PATH)"
	install -d $(INSTALL_INC_PATH)
	install -m 0644 include/*.h $(INSTALL_INC_PATH)

uninstall:
	@echo "Removing $(LIB_NAME) from $(INSTALL_LIB_PATH)"
	rm -f $(INSTALL_LIB_PATH)/$(LIB_NAME)
	@echo "Removing headers from $(INSTALL_INC_PATH)"
	rm -f $(INSTALL_INC_PATH)/*.h
	rmdir --ignore-fail-on-non-empty $(INSTALL_INC_PATH)

help:
	@echo ""
	@echo "$(YELLOW)Available targets:$(RESET)"
	@echo "  $(GREEN)make$(RESET)           - Build the library"
	@echo "  $(GREEN)make install$(RESET)   - Install library and headers system-wide"
	@echo "  $(GREEN)make uninstall$(RESET) - Remove installed files"
	@echo "  $(GREEN)make clean$(RESET)     - Remove build artifacts"
	@echo "  $(GREEN)make test$(RESET)      - Run unit tests"
	@echo "  $(GREEN)make help$(RESET)      - Show this help message"
	@echo ""
