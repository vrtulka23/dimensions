#!/bin/bash
set -e

rm -r build
python3 setup.py build
pytest