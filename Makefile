all: build

build:
  @echo "Building"
  gcc shell.c

clean:
  @echo "Cleaning"
  rm shell
