import migrate
import pygmagick


def main():
    print("Hello from python")
    print(migrate.hello())
    print(migrate.version())

    print("Doing the magick thing")
    version = pygmagick.version()
    print(version)
    print(pygmagick.hello())
    pygmagick.convert(input="/Users/hborcher/Documents/00000003.tif", output="dummy.jp2")
    print(version)
    print(type(version))


if __name__ == '__main__':
    main()