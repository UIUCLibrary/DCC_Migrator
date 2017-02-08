import migrate

def main():
    print("Hello from python")
    print(migrate.hello())
    print(migrate.version())

    print("Doing the magick thing")
    version = migrate.version()
    print(version)
    print(migrate.hello())
    # gmagickpy.convert(input="/Users/hborcher/Documents/00000003.tif", output="dummy.jp2")
    print(version)
    print(type(version))
    migrate.read_metadata("/Users/hborcher/Documents/00000003.tif")


if __name__ == '__main__':
    main()