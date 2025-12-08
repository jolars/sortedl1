# Copilot Instructions for sortedl1

## Repository Overview

**sortedl1** is a Python package for Sorted L-One Penalized Estimation (SLOPE), providing scikit-learn compatible estimators. The project is a hybrid Python/C++ codebase with Python bindings using pybind11.

- **Languages**: Python 3.10+, C++17
- **Size**: Small-to-medium (core Python code in `sortedl1/`, C++ implementation in `src/`)
- **Framework**: scikit-learn compatible, uses scikit-build-core for building
- **Dependencies**: numpy, scipy, scikit-learn, pybind11, Eigen (C++ linear algebra library)

## Key Architecture

### Project Structure
```
sortedl1/
├── sortedl1/              # Python package source
│   ├── __init__.py        # Package initialization
│   ├── estimators.py      # Main Slope estimator class
│   └── results.py         # PathResults and CvResults classes
├── src/                   # C++ source files
│   ├── main.cpp           # pybind11 bindings
│   ├── setup_model.cpp    # Model setup code
│   └── slope/             # Core C++ implementation (from libslope)
├── include/               # C++ headers
│   └── slope/             # C++ header files
├── external/              # Third-party libraries
│   └── Eigen/             # Eigen linear algebra library
├── tests/                 # pytest test suite
├── docs/                  # Sphinx documentation
├── CMakeLists.txt         # CMake build configuration
├── pyproject.toml         # Python project metadata and build config
└── Taskfile.yml           # Task automation (requires go-task, not standard)
```

### Important Notes
- The C++ code in `src/slope/` is automatically synced from https://github.com/jolars/libslope - DO NOT modify these files directly
- Core algorithm issues should be reported at the libslope repository
- Changes should focus on the Python interface or build configuration

## Build, Test, and Validation

### Prerequisites
**ALWAYS** install these dependencies before building:
```bash
python -m pip install --upgrade pip
python -m pip install pybind11 setuptools
```

### Installation
To install the package with dependencies for development (build time: ~90-120 seconds):
```bash
pip install .[tests,plots]
```

For documentation development:
```bash
pip install .[docs,plots]
```

**Note**: The package requires a C++17 compatible compiler. The build process compiles C++ extensions, which takes significant time.

### Running Tests
**ALWAYS** run tests after code changes:
```bash
pytest
```

For verbose output:
```bash
pytest -v
```

For coverage reporting (used in CI):
```bash
coverage run -m pytest
```

**Expected test results**: 11 tests should pass in ~5 seconds. Some warnings about sparse matrices are expected and can be ignored.

### Linting
The project uses `ruff` for Python linting (configured in `pyproject.toml`):
```bash
ruff check sortedl1/
```

**Known lint issues** (non-blocking):
- Some implicit `Optional` types in function signatures
- Mutable default arguments in function definitions
- Import placement in try/except blocks for optional dependencies

### Building Documentation
From the `docs/` directory:
```bash
cd docs
make html
```

**Expected warnings**: 
- Network-related warnings about intersphinx inventories (numpy, scipy, scikit-learn) are normal in isolated environments
- ~7 warnings are expected and do not indicate build failure
- Documentation uses Sphinx with MyST-NB for Jupyter notebook support

**Build time**: ~30-60 seconds. Output is in `docs/build/html/`.

For live documentation development (requires additional setup):
```bash
sphinx-autobuild docs/source docs/build --watch sortedl1
```

## Continuous Integration

### GitHub Workflows

The repository has three main workflows in `.github/workflows/`:

1. **test.yml** (runs on PRs and main branch pushes):
   - Tests across Python 3.10 and 3.13.5 on Windows, macOS, and Ubuntu
   - Builds source distribution (sdist) and wheels for multiple platforms
   - Runs documentation build and pytest with coverage
   - **Key install sequence**:
     ```bash
     python -m pip install --upgrade pip
     python -m pip install pybind11 setuptools coverage  # for testing
     python -m pip install .[tests,plots]
     coverage run -m pytest
     ```

2. **release.yml** (manual workflow):
   - Runs full test suite before release
   - Uses semantic-release for automated versioning
   - Requires conventional commit messages

3. **pypi.yml** (triggered on releases):
   - Publishes to PyPI
   - Deploys documentation to GitHub Pages

### Pre-commit Validation
Before committing, you should:
1. Run `pytest` to ensure tests pass
2. Run `ruff check sortedl1/` to check for linting issues
3. If modifying C++ code, ensure it builds successfully
4. If modifying documentation, build docs with `cd docs && make html`

## Code Style and Conventions

### Python
- Follow numpy-style docstrings (configured in pyproject.toml)
- Use type hints where possible
- Ruff linting configuration in `pyproject.toml` enables extensive checks (flake8-bugbear, isort, etc.)
- Use `.editorconfig` settings: LF line endings, black profile for Python

### C++
- C++17 standard required (CMAKE_CXX_STANDARD = "17")
- Mozilla-based clang-format style (see `.clang-format`)
- OpenMP support when available (optional)

### Commit Messages
**IMPORTANT**: Use conventional commits format (https://www.conventionalcommits.org/):
- `feat:` for new features
- `fix:` for bug fixes
- `docs:` for documentation changes
- `chore:` for maintenance tasks

This is required for semantic versioning and automated releases.

## Common Development Tasks

### Making a Code Change
1. Install dependencies: `pip install pybind11 setuptools`
2. Install package: `pip install .[tests,plots]`
3. Make your changes to Python files in `sortedl1/`
4. Run tests: `pytest`
5. Run linter: `ruff check sortedl1/`
6. If tests pass, commit with conventional commit message

### Modifying C++ Bindings
1. Edit files in `src/` (but NOT in `src/slope/` - those are auto-synced)
2. Reinstall: `pip install .[tests,plots]` (rebuilds C++ extensions)
3. Test: `pytest`

### Adding Dependencies
- Add to `dependencies` in `pyproject.toml` for runtime dependencies
- Add to `[project.optional-dependencies]` for development/test/docs dependencies
- Rebuild: `pip install .[tests,plots]`

## Key Files Reference

### Configuration Files
- `pyproject.toml` - Python project metadata, dependencies, build config, ruff linting rules
- `CMakeLists.txt` - C++ build configuration
- `codecov.yml` - Code coverage thresholds (1% for PR changes)
- `.editorconfig` - Editor settings for consistent formatting
- `.clang-format` - C++ code formatting (Mozilla style)
- `.gitignore` - Comprehensive ignore patterns including build/, dist/, *.so, etc.

### Build and Workflow Files
- `Taskfile.yml` - Task automation (requires go-task, NOT available in standard environment)
- `.github/workflows/test.yml` - Main CI pipeline
- `.releaserc.json` - Semantic release configuration

### Source Files
- `sortedl1/__init__.py` - Package exports: Slope, CvResults, PathResults
- `sortedl1/estimators.py` - Main Slope estimator implementing scikit-learn interface
- `sortedl1/results.py` - Result classes for cross-validation and regularization paths

## Environment Notes

- **Python version**: 3.10+ required, CI tests on 3.10 and 3.13.5
- **go-task**: The `Taskfile.yml` is present but `task` command is NOT available in standard environments. Use direct pip/pytest/make commands instead.
- **Nix**: `flake.nix` provides a Nix development environment but is optional

## Build Artifacts to Ignore
When committing, ensure these are in `.gitignore` and not committed:
- `build/` - CMake build artifacts
- `dist/` - Distribution packages
- `*.so` - Compiled C++ extensions
- `__pycache__/` - Python bytecode
- `.pytest_cache/` - Pytest cache
- `docs/build/` - Built documentation
- `.eggs/`, `*.egg-info/` - Egg metadata

## Trust These Instructions

These instructions have been validated by:
- Successfully installing the package with all dependencies
- Running the full test suite (11 tests passing)
- Building documentation successfully
- Running the linter to identify code style issues
- Examining the GitHub workflows and CI configuration

**Follow these instructions exactly** to minimize exploration and command failures. Only search for additional information if these instructions are incomplete or incorrect for your specific task.
