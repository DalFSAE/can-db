import pytest
import subprocess
from pathlib import Path
import tools.canbuild as canbuild

def test_build_generates_outputs(tmp_path: Path):
    # Test production dbc files
    inputs = [
        canbuild.ROOT / "networks" / "can0_powertrain.dbc",
        canbuild.ROOT / "networks" / "can1_data.dbc",
    ]

    out_dir = tmp_path / "build"
    canbuild.build(inputs, out_dir)

    for dbc in inputs:
        stem = dbc.stem
        gen_dir = out_dir / stem

        # Test if build files are generated
        assert (gen_dir / f"{stem}.c").is_file()
        assert (gen_dir / f"{stem}.h").is_file()

        log = gen_dir / f"{stem}.txt"
        assert log.is_file()
        assert log.stat().st_size > 0

def test_bad_syntax(tmp_path: Path):
    bad_dbc = canbuild.ROOT / "tests" / "data" /  "bad_syntax.dbc"

    out_dir = tmp_path / "build"
    with pytest.raises(subprocess.CalledProcessError):
        canbuild.build(str(bad_dbc), out_dir)

    # Check that no output directory exists
    assert not (out_dir / bad_dbc.stem).exists()

def test_duplicate_id(tmp_path: Path):
    ...

def test_good_minimal(tmp_path: Path):
    ...

