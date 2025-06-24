"""Main module for the sortedl1 package."""

from .estimators import Slope
from .results import CvResults, PathResults

__all__ = ["Slope", "CvResults", "PathResults"]

__version__ = "1.6.0"
