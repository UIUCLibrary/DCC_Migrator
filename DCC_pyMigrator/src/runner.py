# from pprint import pprint
#
from pprint import pprint

import dcc_migrator
# from datetime import datetime
#
def main():
    print("Hello from python")
    # print(dcc_migrator.greet())
    w = dcc_migrator.Metadata("/Users/hborcher/Documents/00000003.tif")
    res = w.get()
    pprint(res)
    # print(w.foo())
#     print(migrate.hello())
#     print(migrate.version())
#
#     print("Doing the magick thing")
#     version = migrate.version()
#     print(version)
#     print(migrate.hello())
#     # gmagickpy.convert(input="/Users/hborcher/Documents/00000003.tif", output="dummy.jp2")
#     res = migrate.read_metadata("/Users/hborcher/Documents/00000003.tif")
#     print(type(res))
#     pprint(res)
#     # dtime = datetime.strptime(res['Iptc.Application2.DateCreated'], "%Y-%m-%d")
#     # print(dtime)
#
#
if __name__ == '__main__':
    main()