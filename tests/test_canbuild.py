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

