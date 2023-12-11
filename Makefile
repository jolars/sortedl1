LIBSLOPE_API_URL := https://api.github.com/repos/jolars/libslope/releases/latest
LIBSLOPE_RELEASE := $(shell curl -s $(LIBSLOPE_API_URL) | grep "tarball_url" | cut -d '"' -f 4)

all: install

.PHONY: install
install:
	pip install -e .

.PHONY: build
build:
	rm -rf dist
	python -m build

.PHONY: test-pypi
test-pypi:
	python -m twine upload --repository testpypi dist/*

.PHONY: clean
clean:
	rm -rf src/*.o src/*.so

.PHONY: test
test:
	python -m unittest discover

.PHONY: docs
docs:
	sphinx-apidoc -o docs/source sortedl1 ;\
	cd docs ;\
	make html

.PHONY: autodoc
autodoc:
	sphinx-autobuild docs/source docs/build
	
.PHONY: update-libslope
update-libslope:
	@mkdir -p tmp
	@curl -L $(LIBSLOPE_RELEASE) | tar -xz --strip-components=1 -C tmp
	@rm -rf src/slope @cp -ri tmp/src/slope src/ @rm -rf tmp
