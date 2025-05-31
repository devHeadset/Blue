{
  description = "Blue - a minimal GTK Bluetooth manager";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }: flake-utils.lib.eachDefaultSystem (system:
    let
      pkgs = import nixpkgs { inherit system; };
    in {
      packages.default = pkgs.stdenv.mkDerivation {
        pname = "blue";
        version = "0.1";

        src = ./.;

        buildInputs = [ pkgs.gtk3 pkgs.glib pkgs.pkg-config ];
        nativeBuildInputs = [ pkgs.pkg-config ];

        buildPhase = ''
          ${pkgs.gcc}/bin/gcc \
            main.c bluetooth.c gui.c \
            -o blue \
            `pkg-config --cflags --libs gtk+-3.0`
        '';

        installPhase = ''
          mkdir -p $out/bin
          cp blue $out/bin/
        '';
      };

      apps.default = {
        type = "app";
        program = "${self.packages.${system}.default}/bin/blue";
      };
    });
}
