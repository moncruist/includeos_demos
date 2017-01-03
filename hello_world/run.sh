#! /bin/bash
set -
INCLUDEOS_PREFIX=${INCLUDEOS_PREFIX-/usr/local}
sudo $INCLUDEOS_PREFIX/includeos/scripts/create_bridge.sh

export CMDLINE="-append ${1}"
if [ $# -eq 0 ]
then
  export CMDLINE=""
fi
export GRAPHICS="-display gtk"
source ${INCLUDEOS_PREFIX-/usr/local}/includeos/scripts/run.sh IncludeOS_helloworld
