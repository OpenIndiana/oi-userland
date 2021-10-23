from setuptools import setup

setup(
    name='isort',
    version='5.9.3',
    description='A Python utility / library to sort imports',
    url='https://github.com/PyCQA/isort',
    packages=['isort', 'isort._future', 'isort._vendored.toml', 'isort.deprecated', 'isort.stdlibs'],
)
