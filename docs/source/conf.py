import os
import sys

sys.path.insert(0, os.path.abspath("../.."))
sys.path.insert(0, os.path.abspath("sphinxext"))

from github_link import make_linkcode_resolve

from sortedl1 import __version__

# Project information
project = "sortedl1"
copyright = "2023, Johan Larsson, Mathurin Massias, Quentin Klopfenstein, Jonas Wallin, Malgorzata Bogdan, Ewout van den Berg, Chiarai Sabatti, Emmanuel Candes, Evan Patterson, Weijie Su"
author = "Johan Larsson, Mathurin Massias, Quentin Klopfenstein, Jonas Wallin, Malgorzata Bogdan, Ewout van den Berg, Chiarai Sabatti, Emmanuel Candes, Evan Patterson, Weijie Su"
release = __version__

# General configuration
extensions = [
    "sphinx.ext.autosummary",
    "sphinx.ext.autodoc",
    "sphinx.ext.doctest",
    "sphinx.ext.intersphinx",
    "sphinx.ext.napoleon",
    "sphinx.ext.mathjax",
    "sphinx_copybutton",
    "myst_parser",
    "sphinx.ext.linkcode",
]
templates_path = ["_templates"]
exclude_patterns = [
    "_build",
    "_templates",
    "Thumbs.db",
    ".DS_Store",
]
master_doc = "index"
exclude_patterns = ["_build"]

templates_path = ["_templates"]

# Autodoc
autodoc_type_aliases = {
    "ArrayLike": "ArrayLike",
}

# Autosummary
autosummary_generate = True
autosummary_imported_members = True

# Options for HTML output
html_theme = "furo"
html_static_path = ["_static"]
html_logo = "_static/slope-horizontal.svg"

# Intersphinx
intersphinx_mapping = {
    "sklearn": ("https://scikit-learn.org/stable", None),
    "numpy": ("https://numpy.org/doc/stable/", None),
    "scipy": ("https://docs.scipy.org/doc/scipy/", None),
}

# Myst
myst_enable_extensions = [
    "colon_fence",
    "deflist",
    "fieldlist",
    "dollarmath",
    "amsmath",
]

# Linkcode
linkcode_resolve = make_linkcode_resolve(
    "sortedl1",
    (
        "https://github.com/jolars/"
        "sortedl1/blob/{revision}/"
        "{package}/{path}#L{lineno}"
    ),
)

# Napoleon
napoleon_google_docstring = False
napoleon_use_ivar = True
