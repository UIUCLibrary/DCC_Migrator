import pytest

TEST_FILE = "/Users/hborcher/Documents/00000003.tif"
from DCC_pyMigrator import Metadata


@pytest.fixture()
def test_metadata():
    return Metadata(TEST_FILE)


def test_foo(test_metadata: Metadata):
    for k, pair in test_metadata.read().items():
        print(k, pair)
        # m_type, m_value = pair
        # print("{}: {}: {}".format(k, m_type, m_value))
    assert 1 == 1

