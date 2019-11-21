#!/usr/bin/env python3
import sys, os


def calc_error(original_file, svd_file):
    original_numbers = list()
    svd_numbers = list()
    with open(original_file, "r") as fp:
        count = 0
        for line in fp:
            if count < 3: 
                if "#" not in line:
                    count += 1
                continue
            else:
                for number in line.strip().split():
                    original_numbers.append(int(number))
    with open(svd_file, "r") as fp:
        count = 0
        for line in fp:
            if count < 3: 
                if "#" not in line:
                    count += 1
                continue
            else:
                for number in line.strip().split():
                    svd_numbers.append(int(number))
    
    differences = list()

    for orig, svd in zip(original_numbers, svd_numbers):
       differences.append(abs(orig-svd))

    total_diff = 0

    for diff in differences:
        total_diff += diff

    average_diff = total_diff / len(differences)

    print(str(average_diff))


def main(argv):
    original_file = argv[0]

    svd_file = argv[1]

    calc_error(original_file, svd_file)

if __name__ == "__main__":
    main(sys.argv[1:])
