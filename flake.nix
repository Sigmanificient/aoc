{
  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs = { self, nixpkgs }:
    let
      inherit (nixpkgs) lib;

      genSystems = lib.genAttrs ["x86_64-linux"];

      eachSystem = f:
        genSystems
        (system: f nixpkgs.legacyPackages.${system});
    in {
        formatter = eachSystem (pkgs: pkgs.alejandra);
        devShells = eachSystem (pkgs: {
          default = pkgs.mkShell {
            packages = with pkgs; [ gcc gnumake ];
          };
        });
    };
}
