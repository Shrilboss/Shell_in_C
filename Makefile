all: build

build: binaries
  @echo "Building"
  gcc shell.c

clean:
  @echo "Cleaning"
  rm shell
