## Requirement
- python and pip installed

## Managing virtual envs
I'm using [venv](https://docs.python.org/3/library/venv.html) for managing my envs. Guide can be found [here](https://packaging.python.org/guides/installing-using-pip-and-virtual-environments/#creating-a-virtual-environment)

### Why?
Out of the box. Easier. Cons of venv is that the version of Python itself is fixed to the installed version. It is only good for managing 3rd party python packages. But good enough for me. I want it easy.

## Initial Setup
`cd python` \
`python -m venv env`  <- Creates the env folder

## How to activate the venv
`cd python` \
(windows) `.\env\Scripts\activate` (mac) `source env/bin/activate`


## How to deactivate the venv
`deactivate` <- How easy

## Install from requirements
`python -m pip install -r requirements.txt`

## How to install new packages
`python -m pip install pandas`
`python -m pip list` <- Check on python packages
`python -m pip freeze > requirements.txt` <- Update requirements.txt

## Gotchas
I don't think the `env` folder will be valid if you change the location of `python`. we gotta delete `env` and run `Initial Setup` again if location is changed.
