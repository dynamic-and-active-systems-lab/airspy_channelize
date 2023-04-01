all:
	rm -f airspy_channelize
	rm -f *.o
	rm -f codegen/exe/airspy_channelize/*.o
	make -f matlab-coder-utils/Makefile PRODUCT_NAME=airspy_channelize -j4
