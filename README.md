# OpenMoHAA

[![Build](https://github.com/openmoh/openmohaa/actions/workflows/branches-build.yml/badge.svg?branch=main)](https://github.com/openmoh/openmohaa/actions/workflows/branches-build.yml) [![Release](https://img.shields.io/github/v/release/openmoh/openmohaa)](https://github.com/openmoh/openmohaa/releases) [![Downloads](https://img.shields.io/github/downloads/openmoh/openmohaa/total)](https://github.com/openmoh/openmohaa/releases)

![License](https://img.shields.io/github/license/openmoh/openmohaa) ![Commits](https://img.shields.io/github/commit-activity/t/openmoh/openmohaa)

![Discord](https://img.shields.io/discord/596049712579215361?logo=discord&logoColor=white&color=5865F2)

![logo](misc/openmohaa-text-sm.png)

## What is OpenMoHAA?

OpenMoHAA is an open-source project aimed at preserving and enhancing **Medal of Honor: Allied Assault** (including Spearhead and Breakthrough expansions) by providing more features and bugfixes, across modern platforms and architectures.

Powered by [ioquake3](https://github.com/ioquake/ioq3) and the [F.A.K.K SDK](https://code.idtech.space/ritual/fakk2-sdk), OpenMoHAA provides:
- Full compatibility with the original game: assets, scripts and multiplayer
- Better support for modern systems
- Cross-platform support (Linux, Windows, macOS)
- Support for both single-player and multiplayer modes
- All fixes and features from the latest version of MOH:AAB (Allied Assault Breakthrough 2.40b)

## Getting started

- 📦 [Installation Guide](docs/getting_started_installation.md)
- ▶️ [Running & Expansions](docs/getting_started_running.md)
- ⚙️ [Game configuration](docs/configuration.md)
- 🌐 [Hosting a server](docs/getting_started_running_server.md)
- ❓ [FAQ & Troubleshooting](docs/faq.md)

## Current features

### Single-player

The entire single-player campaign should work (Allied Assault, Spearhead and Breakthrough). If you encounter any bug, please create a new [GitHub issue](https://github.com/openmoh/openmohaa/issues) describing them.

### Multiplayer

- Almost fully stable
- All official game modes are supported, including those from Spearhead and Breakthrough:
  - Free-For-All
  - Team-Deathmatch
  - Round-based match
  - Objective match
  - Tug-of-War (Spearhead)
  - Liberation (Breakthrough)
- Popular mods like **Freeze-Tag** are supported
- Built-in bots for offline practice and for testing
  - 🔧 [Setting up bots](docs/getting_started_running.md#Playing-with-bots)

You can host your own [OpenMoHAA server](docs/getting_started_running_server.md) or join others using OpenMoHAA.

## Reporting Issues

If you encounter a bug or a problem, you can do one of the following:
- Submit an [issue](https://github.com/openmoh/openmohaa/issues) on GitHub (use the template).
- Join the [OpenMoHAA Discord](https://discord.gg/NYtH58R) for a quick help.

## Features

- 🧰 [Feature list](docs/features.md)
- 📝 [Scripting documentation](docs/scripting.md)

## Screenshots

|                                                                                   |                                                                            |
|-----------------------------------------------------------------------------------|----------------------------------------------------------------------------|
| ![](docs/images/v0.60.0-x86_64/mohdm1_1.png)                                      | ![](docs/images/v0.60.0-x86_64/training_1.png)                               |
| ![](docs/images/v0.60.0-x86_64/flughafen_1.png)                                   | ![](docs/images/v0.60.0-x86_64/flughafen_2.png)                            |
| ![](docs/images/v0.60.0-x86_64/mohdm2_1.png "Playing Freeze-Tag mode with bots")  | ![](docs/images/v0.60.0-x86_64/training_3.png "Single-Player training")    |

*More screenshots [here](docs/images)*

## Development & Compiling

- 💻 [Compiling instructions](docs/compiling.md)

## Third party librairies

The following third party tools and libraries are used by the project

- [Flex](https://github.com/westes/flex)
- [Bison](https://savannah.gnu.org/projects/bison/)
- [SDL](http://www.libsdl.org/)
- [OpenAL](https://www.openal.org/)
- [LibMAD](http://www.underbit.com/products/mad/)
- [cURL](https://curl.se/)
- [Libogg](https://github.com/gcp/libogg)
- [Libvorbis](https://xiph.org/vorbis/)
- [Libopus](https://opus-codec.org/)

## Community & Links

- 🔗 [GitHub Repository](https://github.com/openmoh/openmohaa/)
- 🌐 [MOHAAAA Amalgamated Allied Assault Alliance](https://mohaaaa.co.uk/AAAAMOHAA/index.php)
- 🕹️ [333networks](https://333networks.com/)
- 🛠 [X-NULL](https://x-null.net/)
- 💬 [Join us on Discord](https://discord.gg/NYtH58R)
