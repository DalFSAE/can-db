#!/usr/bin/env python3

import sys
import cantools
from pathlib import Path

SCRIPT_DIR = Path(__file__).resolve().parent
ROOT = SCRIPT_DIR.parent
BUILD = ROOT / "build"

INPUTS = [
    ROOT / "networks" / "can0_powertrain.dbc",
    ROOT / "networks" / "can1_data.dbc",
]

def debug_info():
    print(SCRIPT_DIR)
    print(ROOT)

def build():
    print("Starting build process...")
    BUILD.mkdir(exist_ok=True) 

def lint():
    print("Starting lint process...")

def clean():
    print("Starting clean process...")


def main():
    if len(sys.argv) < 2:
        print("Usage: canbuild.py [build|lint|clean]")
        sys.exit(1)

    cmd = sys.argv[1]

    if cmd == "build":
        build()
    elif cmd == "lint":
        lint()
    elif cmd == "clean":
        clean()

if __name__ == "__main__":
    debug_info()
    main()

