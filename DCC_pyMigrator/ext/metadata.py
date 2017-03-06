from collections import namedtuple
from . import exiv2_wrapper

Rational = namedtuple("Rational", ["numerator", "denominator"])

def convert_to_rational(data):
    numerator, denominator = data.split("/")
    return Rational(numerator=int(numerator), denominator=int(denominator))


exiv2_2_python = {
    "Short": int,
    "Long": int,
    "Rational": convert_to_rational,
    "SRational": convert_to_rational,
    "String": str,
    "Date": str,
    "LangAlt": str,
    "XmpSeq": str,
    "Time": str,
    "XmpText": str,
    "Ascii": lambda x: bytes(x, encoding="ascii"),
    "Byte": lambda x: bytes(x, encoding="ascii"),
    "Undefined": lambda x: bytes(x, encoding="ascii"),

}


def convert(type, text):
    try:
        return exiv2_2_python[type](text)
    except KeyError as e:
        print("Unsupported value {}".format(e), text)
        return text
    except ValueError as e:
        return text


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
