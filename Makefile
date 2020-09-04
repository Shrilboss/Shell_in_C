all: build

build:
  @echo "Building"
  gcc shell.c -o shell -Wall -Werror

clean:
  @echo "Cleaning"
  rm shell
