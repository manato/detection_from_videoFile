# detction_from_videoFile

utility program which create from source video file to video file cantaining detection result
##  how to install 
1. run `$ src/init/init.sh`

2. modify GPU architecture number written in `src/geye_car/CAR_TRACKING/CAR_TRACKING.makefile` and `src/geye_pds/CAR_TRACKING/CAR_TRACKING.makefile`

3. rewrite shared memory path written in `src/autonomous_driving_system/data_for_shm.h` (replace all `/home/hirabayashi/` to `YOUR_INSTALL_PATH`)

4. run `$ make and $ make install under src/ sub directory`

## how to use 
run 
    $ cd shell/ 
    $ ./run.sh [--nocar, --nopds, --nosgn, --noline]

The file named "src.avi" will be processed 
and "dst_video/detection_result.avi" will be created.

If you want to terminate program halfway, run `$ shell/run.sh --terminate`