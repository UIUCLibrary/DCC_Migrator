from setuptools import setup

setup(
    name="DCC_pyMigrator",
    version="0.0.1a0",
    packages=["DCC_pyMigrator",
              "DCC_pyMigrator.ext",
              "DCC_pyMigrator.ext.Exiv2Wrapper",
              ],
    package_data={"DCC_pyMigrator.ext.Exiv2Wrapper": ["*.so", "*.dll"]},
    url="",
    license="",
    author="hborcher",
)