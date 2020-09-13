#!/bin/bash -xe

# Make sure that we are in the home directory
cd

# Clone or update the repo
if [[ ! -d svxlink ]]; then
  git clone $GIT_URL svxlink
  cd svxlink
else
  cd svxlink
  git fetch
  git checkout master
  git reset --hard origin/master
fi

# Checkout the wanted branch
if [ -n "$GIT_BRANCH" ]; then
  git checkout $GIT_BRANCH
fi

# Create a build directory and build svxlink
cd
[[ -d build ]] && rm -rf build
mkdir build
cd build
cmake -DWITH_SYSTEMD=ON -DUSE_QT=OFF -DCMAKE_INSTALL_PREFIX=/usr \
      -DSYSCONF_INSTALL_DIR=/etc -DLOCAL_STATE_DIR=/var \
      -DCMAKE_BUILD_TYPE=Release ../svxlink/src
make -j$(nproc)
sudo make install
sudo ldconfig
