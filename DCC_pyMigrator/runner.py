from pprint import pprint
from ext import Metadata

def main():
    print("Hello")
    image = Metadata("tests/data/00000003.tif")
    md =image.read()
    print(md)
    # w = exiv2_wrapper.ImageMetadata()
    # res = w.get()
    # pprint(res)



if __name__ == '__main__':
    main()
