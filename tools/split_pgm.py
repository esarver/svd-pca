#!/usr/bin/env python3
import sys, os

def split(input_file):
    output_header = "split/" + input_file + ".header"
    output_pgm = "split/" + input_file + ".txt"

    header = ""
    pgm = ""

    with open(input_file, "r") as fp:
        count = 0
        for line in fp:
            if count < 3: 
                header += line
                if "#" not in line:
                    count += 1
                continue
            pgm += line
    
    with open(output_header, "w") as header_file:
        header_file.write(header)
    
    with open(output_pgm, "w") as pgm_file:
        pgm_file.write(pgm)

def main(argv):
    input_file = ''

    for arg in argv:
        split(arg)

if __name__ == "__main__":
    main(sys.argv[1:])

