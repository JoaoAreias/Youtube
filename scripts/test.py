import subprocess
import argparse

from pathlib import Path
from enum import Enum


class BColors:
    HEADER = "\033[95m"
    OKBLUE = "\033[94m"
    OKCYAN = "\033[96m"
    OKGREEN = "\033[92m"
    WARNING = "\033[93m"
    FAIL = "\033[91m"
    ENDC = "\033[0m"
    BOLD = "\033[1m"
    UNDERLINE = "\033[4m"


class SupportedLanguages(Enum):
    CPP = "c++"
    PYTHON = "python"

    def __str__(self) -> str:
        return self.value

def main(args):
    inputs = Path("./input").glob("*")
    outputs = Path("./output").glob("*")

    failed = False
    for input_file, output_file in zip(inputs, outputs):
        assert (
            input_file.name[-2:] == output_file.name[-2:]
        ), "Input does not match output"

        cmd = {
            SupportedLanguages.CPP: ["./solution"],
            SupportedLanguages.PYTHON: ["python", "solution.py"]
        }[args.language]

        with open(input_file, "r") as file:
            result = subprocess.run(cmd, stdin=file, capture_output=True) \
                        .stdout.decode("utf-8")

        with open(output_file, "r") as file:
            expected = file.read()

        if result != expected:
            failed = True
            print(f"{BColors.FAIL}Input {input_file.name} failed {BColors.ENDC}")

    if not failed:
        print(f"{BColors.OKGREEN}All good!{BColors.ENDC}")


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "language",
        type=SupportedLanguages,
        choices=list(SupportedLanguages)
    )


    args = parser.parse_args()

    main(args)
