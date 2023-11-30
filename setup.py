from glob import glob

from pybind11.setup_helpers import Pybind11Extension
from setuptools import setup

setup(
    ext_modules=[
        Pybind11Extension(
            "_sortedl1",
            sorted(glob("src/**/*.cpp", recursive=True)),
            include_dirs=["external/"],
            cxx_std=14,
        )
    ]
)
