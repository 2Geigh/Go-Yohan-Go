{
  description = "Development Dependencies for Go Yohan Go!";

  inputs = {
    nixpkgs.url = "https://channels.nixos.org/nixpkgs-unstable/nixexprs.tar.zst";
  };

  outputs = {nixpkgs, ...}: let
    systems = ["aarch64-darwin" "x86_64-linux"];
  in {
    # nixpkgs.lib.genAttrs -> Define devShells as an attribute set whos attributes are each `system` in `systems`
    devShells = nixpkgs.lib.genAttrs systems (system: {
      default = nixpkgs.legacyPackages.${system}.mkShell {
        packages = with nixpkgs.legacyPackages.${system}; [
          clang
          sdl3
          # docker
          # docker-compose
        ];

        shellHook = ''
          echo "Welcome to the Go Yohan Go development environment!"
        '';
      };
    });
  };
}
