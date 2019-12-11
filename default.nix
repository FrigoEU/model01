{ arduino, bash
, lib, stdenv, fetchgit
}:

let
  source = json: import ./nix/git-from-json.nix {
    inherit fetchgit json;
  };

  keyboardio = source ./nix/pkgs/bundle.json;
  firmware = source ./nix/pkgs/firmware.json;

  plugins = {
    "Kaleidoscope-ModifierLayers" = source ./nix/pkgs/modifierLayers.json;
  };

  copyPlugins = dest:
    builtins.concatStringsSep "\n" (lib.mapAttrsToList
      (name: path: "cp -rL ${path} ${dest}/${name}")
      plugins);

in
stdenv.mkDerivation rec {
  pname = "madkeys";
  version = "1.0";

  buildInputs = [ arduino bash ];
  src = [
    ./src
    keyboardio
    firmware
  ] ++ builtins.attrValues plugins;

  unpackPhase = ''
    mkdir -p ./madkeys/hardware
    cp -rL ${keyboardio} ./madkeys/hardware/keyboardio
    cp -rL ${firmware} ./madkeys/Model01-Firmware
    chmod u+w ./madkeys/Model01-Firmware/Model01-Firmware.ino
    cp -f ${builtins.head src}/Model01-Firmware.ino ./madkeys/Model01-Firmware/
    mkdir -p ./madkeys/libraries
  '' + (copyPlugins "./madkeys");

  patchPhase = ''
    chmod u+w -R .
    patchShebangs .
  '';

  buildPhase = ''
    mkdir -p $out/lib

    cd ./madkeys/Model01-Firmware
    export SKETCHBOOK_DIR="/build/madkeys"
    export ARDUINO_PATH=${arduino}/share/arduino
    export OUTPUT_PATH=$out/lib
    make
  '';

  installPhase = ''
    install -D -t $out/lib/udev/rules.d ../hardware/keyboardio/avr/libraries/Kaleidoscope/etc/99-kaleidoscope.rules
  '';

  description = "Keymaps for Model 01 keyboard";
}
