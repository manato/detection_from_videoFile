#!/bin/sh
#########################
# preparation to use geye
#########################

######################################################
# if following commands exit with error code, 
# then display strings and exit this shell program 
######################################################
#set -e
#trap 'echo -e "\n init_geye.sh failed...\n"' ERR

######################################################
# base path definition
######################################################
base_path="../.."

######################################################
# make directory for geye
######################################################
echo "### start making directory... ###"

mkdir -p ${base_path}
mkdir -p ${base_path}/bin
mkdir -p ${base_path}/bin/shm_creater
mkdir -p ${base_path}/bin/car_detecter
mkdir -p ${base_path}/bin/pedestrian_detecter
mkdir -p ${base_path}/bin/sign_detecter
mkdir -p ${base_path}/bin/image_receiver
mkdir -p ${base_path}/bin/shm_deleter
mkdir -p ${base_path}/bin/line_detecter

mkdir -p ${base_path}/doc

mkdir -p ${base_path}/log

mkdir -p ${base_path}/shared_memory

mkdir -p ${base_path}/shell

mkdir -p ${base_path}/lib

mkdir -p ${base_path}/dst_video

echo "### complete making directory... ###"

######################################################
# make empty files for geye shared memory
######################################################
echo "### start making files for shared memory... ###"

shm_path="${base_path}/shared_memory"

touch ${shm_path}/height_file
touch ${shm_path}/imgupd_checker
touch ${shm_path}/input_file
touch ${shm_path}/output_file
touch ${shm_path}/rbuf
touch ${shm_path}/rbuf_head
touch ${shm_path}/rbuf_tail
touch ${shm_path}/rwlock
touch ${shm_path}/semaphore
touch ${shm_path}/size_file
touch ${shm_path}/width_file
touch ${shm_path}/car_fps
touch ${shm_path}/pds_fps
touch ${shm_path}/sgn_fps
touch ${shm_path}/process_check



echo "### complete making files for shared memory... ###"

######################################################
# copy some documents to proper directory
######################################################
echo "### copying documents... ###"

cp run.sh ${base_path}/shell/
cp usage.txt ${base_path}/doc/

echo "### complete copying documents... ###"
echo "### init_geye complete!! ###"
