from distutils.util import get_platform

from setuptools import setup
from setuptools.command.build_ext import build_ext as _build_ext
from distutils.command.build import build as _build
# from distutils.command.build_ext import build_ext as _build_ext
from subprocess import check_call
import os
import sysconfig
import sys


class build_ext(_build_ext):
    def run(self):
        _build_ext.run(self)
        root = os.path.dirname(os.path.abspath(__file__))

        # configure
        # print("Configuring cmake")
        if not os.path.exists(self.build_temp):
            os.makedirs(self.build_temp)

        configure_command = ["cmake", root,
                             "-DPYTHON_INCLUDE_DIR={}".format(sysconfig.get_config_vars()["INCLUDEPY"])]
        check_call(configure_command, cwd=self.build_temp)
        # build

        build_command = ["cmake", "--build", ".", "--config", "Release", "--target", "DCC_pyMigrator"]
        check_call(build_command, cwd=self.build_temp)


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
    tests_require={
        "pytest"
    },
    test_suite="DCC_pyMigrator.tests",
    url="",
    license="",
    author="hborcher",
)
