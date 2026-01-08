"""Main module for the sortedl1 package."""

from .estimators import Slope
from .results import CvResults, PathResults

__all__ = ["CvResults", "PathResults", "Slope"]

__version__ = "1.7.0"
