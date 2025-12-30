#!/usr/bin/env python3

import sys
import subprocess
import shutil
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

# Invokes a subprocces to run commands via CLI
def run(cmd: list[str]) -> None:
    print(">", " ".join(cmd))
    subprocess.check_call(cmd)

def generate_c_source(dbc: Path):
    can_id = dbc.stem 
    CAN_SOURCE = BUILD / str(can_id)
    run(["cantools", "generate_c_source", str(dbc), "-o", str(CAN_SOURCE)])
    print(f"[canbuild] Generated {CAN_SOURCE}...")

# Generates build files
def build():
    print("[canbuild] Starting build process...")
    clean()
    BUILD.mkdir(exist_ok=True) 

    for dbc in INPUTS:
        can_id = dbc.stem
        print(f"[canbuild] Building: `{dbc}`...")
        run(["cantools", "list", str(dbc)] )
        generate_c_source(dbc)

# Verifies .dbc files, does not generate build files
def lint():
    print("[canbuild] Starting lint process...")

# Deletes the build folder, and removes build artifacts
def clean():
    shutil.rmtree(BUILD, ignore_errors=True)
    print("[canbuild] Deleted build folder...")

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
    print("[cantools] Done.")

if __name__ == "__main__":
    debug_info()
    main()

