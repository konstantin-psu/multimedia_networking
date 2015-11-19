########################################
#
# Makefile for Programming Assignment 2
#
########################################
CC=g++

CFLAGS=-Wall

COMMON=block.cpp block.h macroblock.cpp macroblock.h macroblockManager.cpp macroblockManager.h rawInput.cpp rawInput.h
DCT=myDCT.cpp
IDCT=myIDCT.cpp

default: myDCT myIDCT



myDCT: $(DCT) $(COMMON)
	$(CC) $(CFLAGS) $(COMMON) $(DCT) -o myDCT

myIDCT:  $(DCT) $(COMMON)
	$(CC) $(CFLAGS) $(COMMON) $(IDCT) -o myIDCT

clean:
	rm myDCT myIDCT
