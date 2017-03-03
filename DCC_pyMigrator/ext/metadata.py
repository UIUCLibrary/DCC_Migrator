from . import exiv2_wrapper

class Metadata:
    def __init__(self, file):
        self._file = file
        self._data = exiv2_wrapper.Metadata(file)

    def read(self):
        md = self._data.iptc()
        return md