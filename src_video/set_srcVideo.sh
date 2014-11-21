#!/bin/sh
########################################################
# resize argument video file to 640 x 480
# and create symbolic link from "src.avi"
########################################################
src=${1}
dst="resized_${src}"

# convert
ffmpeg -i ${src} -sameq -s 640x480 ${dst}

# create symbolic link
ln -snf ${dst} src.avi
