.PHONY: install coverage test docs help
.DEFAULT_GOAL := help

define BROWSER_PYSCRIPT
import os, webbrowser, sys

try:
	from urllib import pathname2url
except:
	from urllib.request import pathname2url

webbrowser.open("file://" + pathname2url(os.path.abspath(sys.argv[1])))
endef
export BROWSER_PYSCRIPT

define PRINT_HELP_PYSCRIPT
import re, sys

for line in sys.stdin:
	match = re.match(r'^([a-zA-Z_-]+):.*?## (.*)$$', line)
	if match:
		target, help = match.groups()
		print("%-20s %s" % (target, help))
endef
export PRINT_HELP_PYSCRIPT

BROWSER := python -c "$$BROWSER_PYSCRIPT"
PROJECT_NAME := modern_cpp_project
INSTALL_LOCATION = "/tmp/$(PROJECT_NAME)"
PROJECT_NAME_UPPERCASE = $(shell echo $(PROJECT_NAME) | tr  '[:lower:]' '[:upper:]')

help:
	@python -c "$$PRINT_HELP_PYSCRIPT" < $(MAKEFILE_LIST)

clean:
	rm -rf build

# update CPM.cmake
update:
	wget -q -O cmake/CPM.cmake https://github.com/cpm-cmake/CPM.cmake/releases/latest/download/get_cpm.cmake

test: ## run tests quickly with ctest
	rm -rf build/ 
	cmake -Bbuild -DCMAKE_INSTALL_PREFIX=$(INSTALL_LOCATION) -D${PROJECT_NAME_UPPERCASE}_ENABLE_TESTING=1 -DCMAKE_BUILD_TYPE="Release"
	cmake --build build --config Release
	cd build/ && ctest -C Release -VV

coverage: ## check code coverage quickly GCC
	cmake -Bbuild -DCMAKE_INSTALL_PREFIX=$(INSTALL_LOCATION) -DENABLE_CODE_COVERAGE=1
	cmake --build build --config Release
	cd build/ && ctest -C Release -VV
	cd .. && (bash -c "find . -type f -name '*.gcno' -exec gcov -pb {} +" || true)

docs: ## generate Doxygen HTML documentation, including API docs
	rm -rf docs/
	rm -rf build/
	cmake -Bbuild -DCMAKE_INSTALL_PREFIX=$(INSTALL_LOCATION) -DENABLE_DOXYGEN=1
	cmake --build build --config Release
	cmake --build build --target doxygen-docs
	$(BROWSER) docs/html/index.html

install: ## install the package to the `INSTALL_LOCATION`
	rm -rf build/
	cmake -Bbuild -DCMAKE_INSTALL_PREFIX=$(INSTALL_LOCATION)
	cmake --build build --config Release
	cmake --build build --target install --config Release

format: ## view changes the project sources
	cmake -Bbuild -DCMAKE_INSTALL_PREFIX=$(INSTALL_LOCATION)
	cmake --build build --target format

fix-format: ## format the project sources
	cmake -Bbuild -DCMAKE_INSTALL_PREFIX=$(INSTALL_LOCATION)
	cmake --build build --target fix-format

uninstall: ## uninstall the package to the `INSTALL_LOCATION`
	cmake --build build --target uninstall

check:
	cppcheck --std=c++20 \
		--suppress=noExplicitConstructor \
		--inline-suppr --enable=all \
		--suppress=missingIncludeSystem \
		--template='[{file}:{line}]:({severity}),[{id}],{message}' \
		--force -q \
		-I ./include ./src 2>&1 | tee cppcheck.txt
	python ./ci/colorize_cppcheck_results.py

