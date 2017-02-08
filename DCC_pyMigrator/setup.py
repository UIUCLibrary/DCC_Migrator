from setuptools import setup, Extension

exiv2 = Extension("migrate", sources=["src/migrate.cpp"], extra_compile_args=['-std=c++11'])
pymagick = Extension("pygmagick", sources=["src/py_gmagick.cpp", "src/glue.cpp"],
                     include_dirs=["/usr/local/Cellar/graphicsmagick/1.3.25/include/GraphicsMagick"],
                     library_dirs=["/usr/local/lib/"],
                     libraries=["GraphicsMagick++"],
                     extra_compile_args=['-std=c++11']

                     )
setup(
    name="DCC_pyMigrator",
    version="0.0.1a0",
    url="",
    license="",
    author="hborcher",
    ext_modules=[exiv2, pymagick]
)
