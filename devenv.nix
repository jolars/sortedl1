{
  pkgs,
  ...
}:

{
  # https://devenv.sh/packages/
  packages = [
    pkgs.cmake
    pkgs.ninja
    pkgs.basedpyright
    pkgs.ruff
    pkgs.go-task
  ];

  # https://devenv.sh/languages/
  languages.python = {
    enable = true;

    uv = {
      enable = true;

      sync = {
        enable = true;
        allExtras = true;
        allGroups = true;
      };
    };

    venv = {
      enable = true;
    };
  };

  # https://devenv.sh/git-hooks/
  git-hooks.hooks = {
    ruff.enable = true;
    ruff-format.enable = true;
  };

  # See full reference at https://devenv.sh/reference/options/
}
