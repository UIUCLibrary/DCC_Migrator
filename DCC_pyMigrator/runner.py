from pprint import pprint
from ext import Metadata

def main():
    print("Hello")
    image = Metadata("/Users/hborcher/Documents/00000003.tif")
    print(image.read())
    # w = exiv2_wrapper.Metadata()
    # res = w.get()
    # pprint(res)



if __name__ == '__main__':
    main()
