import os
import sys

from sortedl1 import __version__

sys.path.insert(0, os.path.abspath("../.."))

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = "sortedl1"
copyright = "2023, Johan Larsson, Mathurin Massias, Quentin Klopfenstein, Jonas Wallin, Malgorzata Bogdan, Ewout van den Berg, Chiarai Sabatti, Emmanuel Candes, Evan Patterson, Weijie Su"
author = "Johan Larsson, Mathurin Massias, Quentin Klopfenstein, Jonas Wallin, Malgorzata Bogdan, Ewout van den Berg, Chiarai Sabatti, Emmanuel Candes, Evan Patterson, Weijie Su"

release = __version__

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = [
    "sphinx.ext.autosummary",
    "sphinx.ext.autodoc",
    "sphinx.ext.doctest",
    "sphinx.ext.intersphinx",
    "sphinx.ext.napoleon",
    "sphinx_copybutton",
    "myst_parser",
]
templates_path = ["_templates"]
exclude_patterns = [
    "_build",
    "Thumbs.db",
    ".DS_Store",
]

master_doc = "index"
exclude_patterns = ["_build"]

# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = "furo"
html_static_path = ["_static"]
html_logo = "_static/slope-horizontal.svg"

# - Intersphinx
intersphinx_mapping = {
    # 'numpy': ('https://docs.scipy.org/doc/numpy/', None),
    # 'scipy': ('https://docs.scipy.org/doc/scipy/reference', None),
    # 'matplotlib': ('https://matplotlib.org/', None),
    "sklearn": ("http://scikit-learn.org/stable", None),
}

# Myst
myst_enable_extensions = ["colon_fence", "deflist", "fieldlist"]
