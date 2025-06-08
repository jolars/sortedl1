{
  description = "A basic flake with a shell";
  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
  inputs.systems.url = "github:nix-systems/default";
  inputs.flake-utils = {
    url = "github:numtide/flake-utils";
    inputs.systems.follows = "systems";
  };

  outputs =
    { nixpkgs, flake-utils, ... }:
    flake-utils.lib.eachDefaultSystem (
      system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
      in
      {
        devShells.default = pkgs.mkShell {
          packages =
            let
              sortedl1 = (
                pkgs.python3.pkgs.buildPythonPackage {
                  name = "sortedl1";
                  src = ./.;
                  version = "1.2.0";
                  pyproject = true;

                  dontUseCmakeConfigure = true;

                  build-system = [
                    pkgs.python3.pkgs.scikit-build-core
                    pkgs.python3.pkgs.pybind11
                    pkgs.cmake
                    pkgs.ninja
                  ];
                  dependencies = with pkgs.python3.pkgs; [
                    numpy
                    scikit-learn
                    scipy
                    furo
                    sphinx-copybutton
                    myst-parser
                    pytest
                  ];
                  disabledTests = [
                    "test_cdist"
                  ];
                  pythonImportsCheck = [
                    "sortedl1"
                  ];
                }
              );
            in
            [
              pkgs.bashInteractive
              pkgs.mypy
              pkgs.ruff
              pkgs.jq
              pkgs.go-task
              pkgs.cmake
              pkgs.eigen
              (pkgs.python3.withPackages (ps: [
                sortedl1
                ps.pytest
                ps.twine
                ps.build
                ps.pandas
                ps.ipython
                ps.notebook
                ps.jupyter
              ]))
            ];
        };
      }
    );
}
