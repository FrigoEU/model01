{ fetchgit, json
}:

let
  pkg = builtins.fromJSON (builtins.readFile json);

in
fetchgit { inherit (pkg) url rev sha256; }
