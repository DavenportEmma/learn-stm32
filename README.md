# learn-stm32
This is a repository I'm logging all of my work with my STM32F722ZE Nucleo
board.

## Getting started
### Requirements
- Python 3.8 or later

### Initialisation

Install the python requirements from requirements.txt.

`python -m pip install -r scripts/requirements.txt`

Run the initialisation script from the base directory.

`python scripts/init.py`

Run the env script to set up your environment.

`./scripts/env.ps1`

## Building a project

Run the build script to build a project.

`python scripts/build.py -a path/to/your/project -d path/to/you/build/directory`

## Running a project

Download the stlink tool from here: 
https://www.st.com/en/development-tools/stsw-link004.html#st-get-software

Run the following command to program the board.

`ST-LINK_CLI.exe -c -P ./path/to/your/build/dir/project_name.hex -V -Run`