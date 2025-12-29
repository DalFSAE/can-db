# DMS-27-CAN

This repo defines the CAN interface for the DMS-27 vehicle.

## Python Environment

Python tools in this repo use a local virtual environment.

```bash
python3 -m venv .venv
source .venv/bin/activate
pip install -r requirements.txt
```

## Build

To verify if a .dbc file is valid, the following commands may be used.

```bash
cantools dump networks/can0_powertrain.dbc      # lists all devices
```

