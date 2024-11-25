#!/bin/bash
swipl-ld -o matrices.so -shared matricesLogic.c matricesProlog.c -I/include 

