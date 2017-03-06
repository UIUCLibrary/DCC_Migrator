from distutils.util import get_platform

from setuptools import setup
from distutils.command.build import build as _build
from distutils.command.build_ext import build_ext as _build_ext
from subprocess import check_call
import os



class build_ext(_build_ext):
    def run(self):
        root = os.path.dirname(os.path.abspath(__file__))
        build_path = os.path.join(root, self.build_lib)

        if not os.path.exists(build_path):
            os.makedirs(build_path)

        library_path = os.path.join(root if self.inplace else build_path, "DCC_pyMigrator/ext")
        check_call(["cmake", "../..", "-DLIBRARY_OUTPUT_PATH={}".format(library_path)], cwd=build_path)
        check_call(["cmake", "--build", ".", "--config", "Release", "--target", "PythonExtensions"], cwd=build_path)
        _build_ext.run(self)


class build(_build):
    sub_commands = [("build_ext", None)]

cmdclass = {"build": build,
            "build_ext": build_ext
            }
try:
    from wheel.bdist_wheel import bdist_wheel as _bdist_wheel


    class bdist_wheel(_bdist_wheel):

        def get_tag(self):
            tag = _bdist_wheel.get_tag(self)
            tag = (tag[0], tag[1], get_platform())
            return tag

    cmdclass["bdist_wheel"] = bdist_wheel

except ImportError:
    # Wheel library isn't installed
    pass

setup(
    name="DCC_pyMigrator",
    version="0.0.1a0",
    packages=["DCC_pyMigrator",
              "DCC_pyMigrator.ext",
              ],
    cmdclass=cmdclass,
    package_data={"DCC_pyMigrator.ext": ["*.so", "*.pyd"]},
    url="",
    license="",
    author="hborcher",
)
