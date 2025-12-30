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

def generate_c_source(dbc: Path, out_dir: Path) -> Path:
    can_id = dbc.stem 
    out = out_dir / str(can_id)
    run(["cantools", "generate_c_source", str(dbc), "-o", str(out)])
    return out 

# Generates build files
def build(inputs, out_dir: Path):
    print("[canbuild] Starting build process...")
    clean()
    out_dir.mkdir(exist_ok=True) 

    for dbc in inputs:
        can_id = dbc.stem
        print(f"[canbuild] Building: `{dbc}`...")
        run(["cantools", "list", str(dbc)] )
        out = generate_c_source(dbc, out_dir)
        print(f"[canbuild] Generated {out}...")

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
        build(INPUTS, BUILD)
    elif cmd == "lint":
        lint()
    elif cmd == "clean":
        clean()
    print("[cantools] Done.")

if __name__ == "__main__":
    debug_info()
    main()

