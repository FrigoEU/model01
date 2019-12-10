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
stdenv.mkDerivation {
  pname = "madkeys";
  version = "1.0";

  buildInputs = [ arduino bash ];
  src = [
    keyboardio
    firmware
  ] ++ builtins.attrValues plugins;

  unpackPhase = ''
    mkdir -p ./madkeys/hardware
    cp -rL ${keyboardio} ./madkeys/hardware/keyboardio
    cp -rL ${firmware} ./madkeys/Model01-Firmware
    mkdir -p ./madkeys/libraries
  '' + (copyPlugins "./madkeys/libraries");

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
