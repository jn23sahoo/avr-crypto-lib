# Makefile for BlueMidnightWish
ALGO_NAME := BMW_C

# comment out the following line for removement of BlueMidnightWish from the build process
HASHES += $(ALGO_NAME)


$(ALGO_NAME)_OBJ      := bmw_small.o bmw_large.o
$(ALGO_NAME)_TEST_BIN := main-bmw-test.o hfal_bmw_small.o hfal_bmw_large.o $(CLI_STD) $(HFAL_STD)
$(ALGO_NAME)_NESSIE_TEST      := test nessie
$(ALGO_NAME)_PERFORMANCE_TEST := performance
