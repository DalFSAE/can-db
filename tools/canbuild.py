#!/usr/bin/env python3

import sys
import subprocess
import shutil
import cantools
from pathlib import Path
from collections.abc import Iterable


SCRIPT_DIR = Path(__file__).resolve().parent
ROOT = SCRIPT_DIR.parent
BUILD = ROOT / "build"
DIST = ROOT / "dist"

INPUTS = [
    ROOT / "networks" / "can0_powertrain.dbc",
    ROOT / "networks" / "can1_data.dbc",
]


def debug_info():
    print(SCRIPT_DIR)
    print(ROOT)


# Invokes a subprocces to run commands via CLI
def run(cmd: list[str], *, stdout=None) -> None:
    print(">", " ".join(cmd))
    subprocess.check_call(cmd, stdout=stdout)


def generate_c_source(dbc: Path, out_dir: Path) -> Path:
    can_id = dbc.stem
    out = out_dir / str(can_id)
    run(["cantools", "generate_c_source", str(dbc), "-o", str(out)])
    return out


# Create a log file, with CAN outputs.
def generate_log(dbc: Path, out_dir: Path) -> Path:
    can_id = dbc.stem
    out = out_dir / can_id / f"{can_id}.txt"
    out.parent.mkdir(parents=True, exist_ok=True)

    with out.open("w") as f:
        run(["cantools", "dump", str(dbc)], stdout=f)

    return out


# check if any CAN frames share the same ID
def assert_no_duplicate_frame_ids(dbc: Path) -> None:
    db = cantools.database.load_file(dbc)

    seen: dict[int, str] = {}
    duplicates: list[tuple[int, str, str]] = []

    for msg in db.messages:
        fid = msg.frame_id
        if fid in seen:
            duplicates.append((fid, seen[fid], msg.name))
        else:
            seen[fid] = msg.name

    if duplicates:
        details = ", ".join([f"0x{fid:X} ({a} vs {b})" for fid, a, b in duplicates])
        raise ValueError(f"Duplicate CAN frame IDs in {dbc}: {details}")


# Generates build files
def build(inputs, out_dir: Path):
    print("[canbuild] Starting build process...")
    clean(out_dir)
    out_dir.mkdir(exist_ok=True)

    # check if input is a single path -> set to iterable instance
    if isinstance(inputs, (str, Path)):
        inputs = [Path(inputs)]

    for dbc in inputs:
        # List all messages, throws exception early if any errors occur
        print(f"[canbuild] Building: `{dbc}`...")
        run(["cantools", "list", str(dbc)])

        lint(dbc)

        out = generate_c_source(dbc, out_dir)
        print(f"[canbuild] Source files generated {out}...")

        out = generate_log(dbc, out_dir)
        print(f"[canbuild] Log generated: {out}...")


# Verifies .dbc files, does not generate build files
def lint(dbc: Path) -> None:
    if not dbc.exists():
        raise FileNotFoundError(dbc)

    try:
        assert_no_duplicate_frame_ids(dbc)
    except Exception:
        print(f"[canbuild] [FAIL]: {dbc.name}")
        raise

    print(f"[canbuild] [PASS]: {dbc.name}")


# Deletes the build folder, and removes build artifacts
def clean(out_dir: Path):
    shutil.rmtree(out_dir, ignore_errors=True)
    print("[canbuild] Deleted build folder...")


def main():
    if len(sys.argv) < 2:
        print("Usage: canbuild.py [build|lint|clean|deploy]")
        sys.exit(1)

    cmd = sys.argv[1]

    if cmd == "build":
        build(INPUTS, BUILD)

    elif cmd == "lint":
        if len(sys.argv) < 3:
            print("Usage: canbuild.py lint <dbc_path>")
        lint((ROOT / sys.argv[2]).resolve())

    elif cmd == "clean":
        clean(BUILD)
    elif cmd =="deploy":
        build(INPUTS, BUILD)
        package_build(BUILD, DIST)

    print("[cantools] Exiting.")


if __name__ == "__main__":
    debug_info()
    main()
