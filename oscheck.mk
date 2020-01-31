ACCEPTED_OS = Darwin

ifeq ($(OS),Windows_NT)
    DETECTED_OS := Windows
else
    DETECTED_OS := $(shell sh -c 'uname 2>/dev/null || echo Unknown')
endif

ifeq ($(ACCEPTED_OS),$(DETECTED_OS))

else
	exit(-1)
endif