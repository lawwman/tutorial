## Requirement
- python and pip installed
- Pipenv for python env management


## Installing pipenv

### For Ubuntu
`pip install pipenv`
`pip install --upgrade pipenv` -> to upgrade current version
### For MacOS
`brew install pipenv`

## Initial setup
`cd learn_python`\
`pipenv --python 3.8` -> set up Pipfile and virtual env for python version 3.8\
`pipenv shell` -> enter virtual env

## Setting up
`cd learn_python`\
`pipenv shell`\
`pipenv install` -> installs the packages from `pipfile.lock`

## Installing new packages
`pipenv install pandas` -> You can verify with `pipenv run pip list`


## Removing environment

Before deleting `Pipfile`, run `pipenv --rm` to remove the virtual environment.
