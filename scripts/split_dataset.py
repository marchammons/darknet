"""Script to split dataset into test and train sets."""
# Copyright 2017 Dell Inc.
# Shreya Gupta <shreya_gupta2@dell.com>
#
# ==============================================================================
import argparse
import glob
import math
import os
import random


def split(directory, percentage_test=10):
    """Splits dataset into test and train sets."""
    # Create and/or truncate train.txt and test.txt
    file_train = open(os.path.join(directory, 'train.txt'), 'wb')
    file_test = open(os.path.join(directory, 'test.txt'), 'wb')

    # Populate train.txt and test.txt
    files = glob.glob(os.path.join(directory, '*.jpg'))
    random.shuffle(files)
    counter = 1
    index_test = math.ceil(len(files) * percentage_test/100.0)
    for path in files:
        title, _ = os.path.splitext(os.path.basename(path))
        image_file = os.path.join(directory, title) + '.jpg'

        if counter <= index_test:
            counter += 1
            file_test.write(image_file + "\n")
        else:
            file_train.write(image_file + "\n")


def main():
    """Main function."""
    parser = argparse.ArgumentParser()
    parser.add_argument('-d', '--directory', type=str, required=True,
                        help='directory containing images')
    parser.add_argument('-p', '--percentage-test', type=float, required=False,
                        default=10, help='percentage of dataset to be used'
                        ' as test set')
    args = parser.parse_args()
    split(args.directory, args.percentage_test)


if __name__ == '__main__':
    main()
