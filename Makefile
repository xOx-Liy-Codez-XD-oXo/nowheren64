BUILD_DIR=build
include $(N64_INST)/include/n64.mk

src = source/main.c

all: nowhere.z64

$(BUILD_DIR)/nowhere.dfs:
$(BUILD_DIR)/nowhere.elf: $(src:%.c=$(BUILD_DIR)/%.o)

nowhere.z64: N64_ROM_TITLE="nowhere to go"
nowhere.z64: $(BUILD_DIR)/nowhere.dfs

clean:
	rm -rf $(BUILD_DIR) nowhere.z64

-include $(wildcard $(BUILD_DIR)/*.d)

.PHONY: all clean
