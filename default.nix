{ arduino, bash
, stdenv, fetchgit
}:

let
  keyboardio = import ./nix/git-from-json.nix {
    inherit fetchgit;
    json = ./nix/pkgs/bundle.json;
  };
  firmware = import ./nix/git-from-json.nix {
    inherit fetchgit;
    json = ./nix/pkgs/firmware.json;
  };

in
stdenv.mkDerivation {
  pname = "madkeys";
  version = "1.0";

  buildInputs = [ arduino bash ];
  src = [
    keyboardio
    firmware
  ];

  unpackPhase = ''
    mkdir -p ./madkeys/hardware
    cp -rL ${keyboardio} ./madkeys/hardware/keyboardio
    cp -rL ${firmware} ./madkeys/Model01-Firmware
  '';

  patchPhase = ''
    chmod u+w -R .
    patchShebangs .
  '';

  buildPhase = ''
    mkdir $out
    cd ./madkeys/Model01-Firmware
    export SKETCHBOOK_DIR="/build/madkeys"
    export ARDUINO_PATH=${arduino}/share/arduino
    export OUTPUT_PATH=$out
    make
  '';

  installPhase = ''
    true
  '';

  description = "Keymaps for Model 01 keyboard";
}
