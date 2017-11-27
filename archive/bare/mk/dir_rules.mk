all:
	for d in $(dirs); do make -C $$d; done

clean:
	for d in $(dirs); do make -C $$d $@; done
