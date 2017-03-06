import sys
from fractions import Fraction

from datetime import datetime, timezone

from . import exiv2_wrapper


def convert(type, text):
    numarical_types = ["Short", "Long"]
    rational_types = ['Rational', 'SRational']
    string_types = ["String", "XmpText"]
    byte_types = ["Ascii", "Byte"]
    try:
        if type in string_types:
            return str(text)

        elif type in byte_types:
            return bytes(text.encode("ascii"))

        elif type in rational_types:
            nom, dem = text.split("/")
            return Fraction(int(nom), int(dem))

        elif type in numarical_types:
            return int(text)

        # elif type == "Time":
        #     time, timezone = text.split("+")
        #     dt = datetime.strptime(time, "%H:%M:%S")
        #     tz = timezone(0)

            # print(dt.timetz())
            # return dt
        elif type == "Undefined":
            return text

        else:
            print(type, text, file=sys.stderr)
            return text

    except ValueError:
        return str(text)


class Metadata:
    def __init__(self, file):
        self._file = file
        self._data = exiv2_wrapper.Metadata(file)

    def read(self):
        iptc = self._data.iptc()
        exif = self._data.exif()
        xmp = self._data.xmp()
        updated = {}
        for k, v in {**iptc, **exif, **xmp}.items():
            updated[k] = convert(v[0], v[1])

        return updated
