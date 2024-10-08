{
  stdenv,
  lib,
  cmake,
  libsecret,
  pkg-config,
  glib,
  pcre2,
  util-linux,
  libselinux,
  libsepol,
  libgcrypt,
  libgpg-error,
  json_c,
  curl,
  libxml2,
}:

stdenv.mkDerivation(finalAttrs:{
  pname = "luogu-cli";
  version = "1.0.0";

  src = ../.;

  nativeBuildInputs = [
    cmake
    pkg-config
  ];

  buildInputs = [
    libsecret
    glib
    libgcrypt
    util-linux
    libselinux
    libgpg-error
    pcre2
    libsepol
    libxml2
    json_c
    curl
  ];
})
