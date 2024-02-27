#CC := gcc
#CFLAGS := -Wall -Werror -Wextra

all: update_data preproc postproc

app.exe: main.c time_exp.c time_exp.h
	$(CC) $(CFLAGS) main.c time_exp.c -o app.exe

update_data: app.exe
	mkdir -p data
	./update_data.sh

.PHONY: preproc
preproc: make_preproc.py
	mkdir -p preproc
	python3 make_preproc.py

.PHONY: postproc
postproc: make_postproc.py
	mkdir -p graphs
	python3 make_postproc.py

clean:
	rm -rf ./data ./preproc app.exe