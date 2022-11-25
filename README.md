# Visualization.goom add-on for Kodi

This is a [Kodi](http://kodi.tv) visualization add-on.

[![License: GPL-2.0-or-later](https://img.shields.io/badge/License-GPL%20v2+-blue.svg)](LICENSE.md)
[![Build Status](https://dev.azure.com/teamkodi/binary-addons/_apis/build/status/xbmc.visualization.goom?branchName=Nexus)](https://dev.azure.com/teamkodi/binary-addons/_build/latest?definitionId=38&branchName=Nexus)
[![Build Status](https://jenkins.kodi.tv/view/Addons/job/xbmc/job/visualization.goom/job/Nexus/badge/icon)](https://jenkins.kodi.tv/blue/organizations/jenkins/xbmc%2Fvisualization.goom/branches/)

## Build instructions

When building the add-on you have to use the correct branch depending on which version of Kodi you're
building against. If you want to build the add-on to be compatible with the latest kodi `'master'` commit,
then you need to checkout the add-on branch with the current Kodi codename. For example, if the latest
Kodi codename is `'Nexus'`, then your current add-on branch must be `'Nexus'`. Also make sure you follow
the README from the branch in question.

Note: For goom++ development, Docker toolchains are used to make sure the right compiler and tool versions
are available. (Currently 'clang-15' and 'g++-12'.)

### Linux Builds

The following instructions assume, as an example, the `'Nexus'` branch, and that your current local
directory is `'xbmc'`

1. `git clone --branch master https://github.com/xbmc/xbmc.git`
1. `git clone --branch Nexus https://github.com/xbmc/visualization.goom.git`
1. `cd visualization.goom`
1. `cd docker-toolchains`
1. `./build-all.sh`
1. `cd ..`
1. `./goom-configure-with-docker-toolchain.sh -c clang-15 --build-type RelWithDebInfo --suffix nexus`
1. `./goom-build-with-docker-toolchain.sh -c clang-15 --build-type RelWithDebInfo --suffix nexus`
1. `./goom-docker-install-to.sh && ./goom-docker-build.sh`
1. `cd ..`

The build add-on files will be placed in `'./xbmc/kodi-build/addons/lib/addons/visualization.goom'` and
`'./xbmc/kodi-build/addons/share/kodi/addons/visualization.goom'`. So if you build Kodi from source and
run it directly, then the add-on will be available as a system add-on.

Alternatively, the `goom-docker-...` scripts create a Docker image from the nightly Kodi build and the
latest goom++ build files. This allows you to run a current nightly Kodi build with a freshly built goom++
add-on using the `goom-docker-run.sh` script. See below.

### Running Kodi in a Docker Container

You can run the latest Kodi nightly build in a Docker container with a fresh goom++ build. To run
the container with X11 you need to install `'x11docker'`. This is fairly straightforward: See
`https://github.com/mviereck/x11docker#installation`

Once you've installed `'x11docker'` you can install the required goom++ files, build the Kodi Docker images,
then run Kodi Docker. Here are the steps:

First set up a symlink, '/mnt/Music', pointing to your music directory.
Then run the following scripts:

1. `./goom-docker-install-to.sh`
1. `./goom-docker-build.sh`
1. `./goom-docker-run.sh`

Kodi should now start in full-screen mode. To enable the Goom visualisation do the following:

1. For the first run of Kodi, it should pop up a 'Disabled add-ons' dialog box. Say 'yes' to enable the 'Goom'
add-on.
1. Set the Goom options to whatever you want.
1. Go to the Kodi system settings for 'Player' and change the 'Music/Visualisation' setting to 'Goom'.
1. Go back to the Kodi main menu and choose 'Music/Files'. You can add the 'Music' folder using 'Add music'.<br>
   (The Docker container has mounted a 'Music' folder to the host directory '/mnt/Music'.)
1. Now you can play a music track and the Goom visualisation should run with it.

Note: The Kodi Docker container uses `'${HOME}/docker/kodi-nightly'` as it's home directory. Kodi will install
the files it requires under `'${HOME}/docker/kodi-nightly/.kodi'`.
