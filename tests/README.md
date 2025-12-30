# tests/

This directory contains automated tests for the CAN database and build tooling.

## Purpose:

- To verify CAN dbc files parse correctly
- To automate the build process via GitHub contains
- To automate the testing process, to ensure valid and stable output.

## Running the tests

To run the tests:

```bash
# setup python3 environment
python3 -m venv .venv
source .venv/bin/activate
pip install -r requirements.txt

# run tests
pytest
```

## Adding Tests

All source code files and functions should have a corresponding unit test.
For python files, see pystest documentation for info on how to add tests.
Feel free to add your own tests as needed.

