slimcat.out: src/cat.c
	$(CC) -Wall -Ofast -o slimcat.out src/cat.c

slimcat.1.gz: slimcat.1
	gzip -k slimcat.1

debug: src/cat.c
	$(CC) -Wall -O0 -g -o slimcat.debug.out src/cat.c

clean:
	rm slimcat.*out
	rm slimcat.1.gz

install: slimcat.out slimcat.1.gz
	# Moves compiled programs to their spots, might not work for BSD
	sudo cp slimcat.1.gz /usr/share/man/man1/
	sudo cp slimcat.out /usr/bin/slimcat
	# You may want to add an aliase to your shell to replace cat with slimcat

uninstall: 
	sudo rm -v /usr/share/man/man1/slimcat.1.gz
	sudo rm -v /usr/bin/slimcat

unsafe-install: 
	# Makes slimcat your default cat and makes a backup of cat
	sudo cp -n /usr/bin/cat /usr/bin/cat.bak
	sudo cp slimcat.out /usr/bin/cat
	sudo cp -n /usr/share/man/man1/cat.1.gz /usr/share/man/man1/cat.1.gz.bak
	sudo cp slimcat.1.gz /usr/share/man/man1/cat.1.gz


unsafe-uninstall: /usr/bin/cat.bak /usr/share/man/man1/cat.1.gz.bak
	sudo mv /usr/bin/cat.bak /usr/bin/cat
	sudo mv /usr/share/man/man1/cat.1.gz.bak /usr/share/man/man1/cat.1.gz

