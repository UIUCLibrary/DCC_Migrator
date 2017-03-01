from setuptools import setup, Extension

migrate = Extension("migrate", sources=["src/migrate.cpp",
                                        "src/convert.cpp",
                                        "src/PyObject_builder.cpp",
                                        "src/PyObjectProcessor.cpp",
                                        "src/pyobjects/TimePyObject.cpp",
                                        "src/pyobjects/SimplePyObject.cpp",
                                        "src/metadata.cpp"
                                        ],
                    include_dirs=["src", "/usr/local/Cellar/graphicsmagick/1.3.25/include/GraphicsMagick",
                                  "/usr/local/Cellar/exiv2/0.25/include"],
                    library_dirs=["/usr/local/lib/"],
                    libraries=["GraphicsMagick++", "exiv2"],
                    extra_compile_args=['-std=c++14']
                    )
setup(
    name="DCC_pyMigrator",
    version="0.0.1a0",
    url="",
    license="",
    author="hborcher",
    ext_modules=[migrate]
)
