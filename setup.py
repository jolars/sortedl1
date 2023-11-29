from glob import glob

from pybind11.setup_helpers import Pybind11Extension, build_ext
from setuptools import setup

__version__ = "0.1.0"

# The main interface is through Pybind11Extension.
# * You can add cxx_std=11/14/17, and then build_ext can be removed.
# * You can set include_pybind11=false to add the include directory yourself,
#   say from a submodule.
#
# Note:
#   Sort input source files if you glob sources to ensure bit-for-bit
#   reproducible builds (https://github.com/pybind/python_example/pull/53)

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
    description="Sorted L1 Penalized Estimation",
    long_description="",
    ext_modules=ext_modules,
    # Currently, build_ext only provides an optional "highest supported C++
    # level" feature, but in the future it may provide more features.
    cmdclass={"build_ext": build_ext},
    zip_safe=False,
)
