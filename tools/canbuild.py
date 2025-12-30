#!/usr/bin/env python3

import sys
from pathlib import Path


def build():
    print("Starting build process...")

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
    main()
