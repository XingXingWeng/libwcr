main:$(OBJ)
	$(MAKE) -C src

.PHONY:clean
clean:
	$(MAKE) clean -C src
