import os
from glob import glob

from pybind11.setup_helpers import Pybind11Extension, build_ext
from setuptools import setup

# Setup boilerplate below this line.

# Set version from version.py
package_root = os.path.abspath(os.path.dirname(__file__))
version = {}
with open(os.path.join(package_root, "sortedl1/version.py")) as fp:
    exec(fp.read(), version)
__version__ = version["__version__"]

ext_modules = [
    Pybind11Extension(
        "_sortedl1",
        sorted(glob("src/**/*.cpp", recursive=True)),
        define_macros=[("VERSION_INFO", __version__)],
        include_dirs=["external/"],
    ),
]

setup(
    name="sortedl1",
    version=__version__,
    author="Johan Larsson",
    author_email="johanlarsson@outlook.com",
    url="https://github.com/jolars/sortedl1",
    description="Sorted L-One Penalized Estimation (SLOPE)",
    long_description="",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
    zip_safe=False,
)
