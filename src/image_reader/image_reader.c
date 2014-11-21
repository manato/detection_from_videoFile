/* 
   server program 
   which get image from avi file 
*/
#include <stdio.h>
#include <cv.h>
#include <highgui.h>
#include <sys/time.h>
#include "data_for_shm.h"
#include "deal_image.h"

/* /\* color macro definition *\/ */
/* //#define RED  CV_RGB(255, 0, 0) */
/* #define RED  CV_RGB(204, 0, 0) */
/* //#define BLUE CV_RGB(0, 0, 255) */
/* #define GREEN CV_RGB(40, 175, 12) */

/* /\* global variables for get frame per second *\/ */
/* static int car_fps; */
/* static int pds_fps; */
/* static int sgn_fps; */
/* typedef struct { */
/*     int semaphore_id; */
/*     int *ptr_shared_car_fps; */
/*     int *ptr_shared_pds_fps; */
/*     int *ptr_shared_sgn_fps; */
/* } getFPS_args; */

/************************************************************************/
/* Get Frame Per Second */
/* void *getFPS(void* arg) */
/* { */
/*     /\* get arguments *\/ */
/*     getFPS_args *this_args = (getFPS_args *)arg; */
/*     int semid = this_args->semaphore_id; */
/*     int *ptr_shrd_car_fps = this_args->ptr_shared_car_fps; */
/*     int *ptr_shrd_pds_fps = this_args->ptr_shared_pds_fps; */
/*     int *ptr_shrd_sgn_fps = this_args->ptr_shared_sgn_fps; */

/*     while(1) { */
/*         sleep(1);               /\* wait 1 second *\/ */

/*         /\* get frame per second of car detection program *\/ */
/*         My_sem_operation(semid, LOCK); /\* lock semaphore *\/ */
/*         car_fps = *ptr_shrd_car_fps; */
/*         *ptr_shrd_car_fps = 0; */
/*         My_sem_operation(semid, UNLOCK); /\* unlock semaphore *\/ */

/*         /\* get frame per second of pedestrian detection program *\/ */
/*         My_sem_operation(semid, LOCK); /\* lock semaphore *\/ */
/*         pds_fps = *ptr_shrd_pds_fps; */
/*         *ptr_shrd_pds_fps = 0; */
/*         My_sem_operation(semid, UNLOCK); /\* unlock semaphore *\/ */

/*         /\* get frame per second of sign detection program *\/ */
/*         My_sem_operation(semid, LOCK); /\* lock semaphore *\/ */
/*         sgn_fps = *ptr_shrd_sgn_fps; */
/*         *ptr_shrd_sgn_fps = 0; */
/*         My_sem_operation(semid, UNLOCK); /\* unlock semaphore *\/ */
/*     } */


/* } */
/************************************************************************/

/************************************************************************/
/* Writes Frame Per Seconds on the image */
/* void writeFPS(IplImage *image) */
/* { */
/*     CvFont dfont; */
/*     char text_car[256]; */
/*     char text_pds[256]; */
/*     char text_sgn[256]; */
/*     CvScalar color_car, color_pds, color_sgn; */

/*     /\* displayed text parameter *\/ */
/* //    const float hscale      = 1.0f; */
/*     const float hscale      = 0.5f; */
/* //    const float vscale      = 1.0f; */
/*     const float vscale      = 0.5f; */
/*     const float italicscale = 0.0f; */
/*     const int   thickness   = 1; */

/*     /\* create text *\/ */
/*     sprintf(text_car, "Speed of Processing(car): %d[FPS]", car_fps); */
/*     sprintf(text_pds, "Speed of Processing(pds): %d[FPS]", pds_fps); */
/*     sprintf(text_sgn, "Speed of Processing(sgn): %d[FPS]", sgn_fps); */


/*     /\* initialize text font information *\/ */
/*     cvInitFont( */
/*         &dfont,                 /\* font information structure *\/ */
/* //        CV_FONT_HERSHEY_COMPLEX_SMALL, /\* font name *\/ */
/*         CV_FONT_HERSHEY_SIMPLEX, /\* font name *\/ */
/*         hscale,                        /\* rate of horizontal width *\/ */
/*         vscale,                        /\* rage of vertical height *\/ */
/*         italicscale,                   /\* italic relative angle *\/ */
/*         thickness,                     /\* thickness of letters *\/ */
/*         CV_AA                          /\* line type *\/ */
/*         ); */

/*     /\* write text on the image *\/ */
/*     color_car = (car_fps == 0) ? RED : GREEN;  */
/*     cvPutText( */
/*         image,                  /\* image written text on *\/ */
/*         text_car,               /\* text written on the image *\/ */
/* //        cvPoint(0, 470),        /\* start coordinates(left bottom) of text *\/ */
/*         cvPoint(0, 435),        /\* start coordinates(left bottom) of text *\/ */
/*         &dfont,                 /\* font information *\/ */
/*         color_car */
/*         ); */
    
/*     color_pds = (pds_fps == 0) ? RED : GREEN; */
/*     cvPutText( */
/*         image,                  /\* image written text on *\/ */
/*         text_pds,               /\* text written on the image *\/ */
/*         cvPoint(0, 455),        /\* start coordinates(left bottom) of text *\/ */
/*         &dfont,                 /\* font information *\/ */
/*         color_pds */
/*         ); */
    
/*     color_sgn = (sgn_fps == 0) ? RED : GREEN; */
/*     cvPutText( */
/*         image,                  /\* image written text on *\/ */
/*         text_sgn,               /\* text written on the image *\/ */
/*         cvPoint(0, 475),        /\* start coordinates(left bottom) of text *\/ */
/*         &dfont,                 /\* font information *\/ */
/*         color_sgn */
/*         ); */
/* } */
/************************************************************************/


int main(int argc, char *argv[]) {
    
    //  DLimgdescriptor  imgdes, imgdes_shm; /* image descriptor */
    DLimgdescriptor  imgdes_shm, imgdes_shm_output; /* image descriptor */
    unsigned char   *buf;                /* buffer for image from camera */
    unsigned char   *buf_output; /* buffer for image of detection result */
    int              image_size;         /* size of image */

    CvMat    *tmpbuf;             /* buffer for show image */
    IplImage *image_res;          /* for show image */

    /* for shared memory */
    key_t shm_key_size;
    key_t shm_key_rbuf, shm_key_rbuf_head, shm_key_rbuf_tail;

    int shrd_id_size;
    int shrd_id_rbuf, shrd_id_rbuf_head, shrd_id_rbuf_tail;

    int *shrd_ptr_size;
    int *shrd_ptr_rbuf_head, *shrd_ptr_rbuf_tail;
    obj_coordinate *shrd_ptr_rbuf;

    /* for semaphore control */
    key_t sem_key;
    int   semid;

    /* for reader-writer lock */
    key_t shm_key_rwlock;
    int   shrd_id_rwlock;
    pthread_rwlock_t *shrd_ptr_rwlock;

    /* for image update checker */
    key_t  shm_key_imgupd;
    int    shrd_id_imgupd;
    char  *shrd_ptr_imgupd;

    /* /\* for fps calculate *\/ */
    /* key_t  shm_key_car_fps, shm_key_pds_fps, shm_key_sgn_fps; */
    /* int    shrd_id_car_fps, shrd_id_pds_fps, shrd_id_sgn_fps; */
    /* int   *shrd_ptr_car_fps, *shrd_ptr_pds_fps, *shrd_ptr_sgn_fps; */

    /* for process checker */
    key_t shm_key_process_check;
    int shrd_id_process_check;
    int *shrd_ptr_process_check;

    /* part of storing image to shared memory */
    int rtn;
    struct timeval tv;
    struct tm *tmptr = NULL;	

    /* part of display detection results */
    int      i   = 0;	
    int      num = 0;
    CvScalar rects_color;
    CvPoint  p1;
    CvPoint  p2;
    
    /* part of get FPS */
    /* pthread_t th_getFPS; */
    /* getFPS_args thread_arg; */

    /* to get frame from avi video file */
    CvCapture *capture = NULL;
    double video_fps;
    CvSize video_size;
    CvVideoWriter *writer;
    char *src_videoName = argv[1];
    char *dst_videoName = argv[2];
    int frame_count = 0;
    int process_check = 0;
    
    IplImage *cv_image, *vga_image;

    /****************************************************************/
    /* key generation */
    /****************************************************************/
    shm_key_size = ftok(SIZE_SHM_PATH, 1);  // key for size file
    if(shm_key_size == -1) {   // error semantics
        printf("generate key for size failed\n");
        return -1;
    }

    shm_key_rbuf = ftok(RBUF_PATH, 1);  // key for ring buffer
    if(shm_key_rbuf == -1) {  // error semantics
        printf("generate key for rbuf failed\n");
        return -1;
    }          

    shm_key_rbuf_head = ftok(RBUF_HEAD_PATH, 1);  // key for ring buffer head
    if(shm_key_rbuf_head == -1) {  // error semantics
        printf("generate key for rbuf_head failed\n");
        return -1;
    }          

    shm_key_rbuf_tail = ftok(RBUF_TAIL_PATH, 1);  // key for ring buffer tail
    if(shm_key_rbuf_tail == -1) {  // error semantics
        printf("generate key for rbuf_tail failed\n");
        return -1;
    }          


    /* key generation for semaphore */
    sem_key = ftok(SEM_PATH, 1);  // key for semaphore
    if(sem_key == -1) {   // error semantics
        printf("generate key for semaphore failed\n");
        return -1;
    }

    /* key generation for reader-writer lock */
    shm_key_rwlock = ftok(RWLOCK_SHM_PATH, 1);  // key for reader-writer lock 
    if(shm_key_rwlock == -1) {  // error semantics
        printf("generation key for reader-writer lock failed\n");
        return -1;
    }



    /* key generation for image update checker */
    shm_key_imgupd = ftok(IMGUPD_SHM_PATH, 1); // key for image update checker
    if(shm_key_imgupd == -1) {  // error semantics
        printf("generation key for image update checker failed\n");
        return -1;
    }

    /* /\* key generation for fps keeper *\/ */
    /* shm_key_car_fps = ftok(CAR_FPS_SHM_PATH, 1); // key for image update checker */
    /* if(shm_key_car_fps == -1) {  // error semantics */
    /*     printf("generation key for car_fps failed\n"); */
    /*     return -1; */
    /* } */

    /* shm_key_pds_fps = ftok(PDS_FPS_SHM_PATH, 1); // key for image update checker */
    /* if(shm_key_pds_fps == -1) {  // error semantics */
    /*     printf("generation key for pds_fps failed\n"); */
    /*     return -1; */
    /* } */

    /* shm_key_sgn_fps = ftok(SGN_FPS_SHM_PATH, 1); // key for image update checker */
    /* if(shm_key_sgn_fps == -1) {  // error semantics */
    /*     printf("generation key for sgn_fps failed\n"); */
    /*     return -1; */
    /* } */

    /* key generation for process checker */
    shm_key_process_check = ftok(PROCESS_CHECK_SHM_PATH, 1);
    if (shm_key_process_check == -1) {  // error semantics
        printf("generation key for process checker failed\n");
        return -1;
    }

    /****************************************************************/
    /* open shared memory */
    /****************************************************************/
    shrd_id_size = shmget(shm_key_size, sizeof(int), 0666);
    if(shrd_id_size < 0) {  // error semantics
        printf("Can't Access to the Shared memory for size...\n");
        return -1;
    }


    shrd_id_rbuf = shmget(shm_key_rbuf, MAX_OBJECT_NUM*sizeof(obj_coordinate), 0666);
    if(shrd_id_rbuf < 0) {
        printf("Can't Access to the Shared memory for rbuf...\n");
        return -1;
    }

    shrd_id_rbuf_head = shmget(shm_key_rbuf_head, sizeof(int), 0666);
    if(shrd_id_rbuf_head < 0) {
        printf("Can't Access to the Shared memory for rbuf_head...\n");
        return -1;
    }

    shrd_id_rbuf_tail = shmget(shm_key_rbuf_tail, sizeof(int), 0666);
    if(shrd_id_rbuf_tail < 0) {
        printf("Can't Access to the Shared memory for rbuf_tail...\n");
        return -1;
    }


    /* open semaphore */
    semid = semget(sem_key, 1, 0666);
    if(semid == -1) {
        printf("Can't Access to the semaphore\n");
        return -1;
    }

    /* open reader-writer lock */
    shrd_id_rwlock = shmget(shm_key_rwlock, sizeof(pthread_rwlock_t), 0666);
    if(shrd_id_rwlock < 0) {
        printf("Can't Access to the Shared memory for reader-writer lock...\n");
        return -1;
    }


    /* create shared image update checker */
    shrd_id_imgupd = shmget(shm_key_imgupd, sizeof(char)*256, 0666);
    if(shrd_id_imgupd < 0) {  // error semantics
        printf("Can't Access Shared memory for image update checker...\n");
        return -1;
    }

    /* /\* open shared fps keeper *\/ */
    /* shrd_id_car_fps = shmget(shm_key_car_fps, sizeof(int), 0666); */
    /* if(shrd_id_car_fps < 0) {  // error semantics */
    /*     printf("Can't Access Shared memory for car_fps...\n"); */
    /*     return -1; */
    /* } */

    /* shrd_id_pds_fps = shmget(shm_key_pds_fps, sizeof(int), 0666); */
    /* if(shrd_id_pds_fps < 0) {  // error semantics */
    /*     printf("Can't Access Shared memory for pds_fps...\n"); */
    /*     return -1; */
    /* } */

    /* shrd_id_sgn_fps = shmget(shm_key_sgn_fps, sizeof(int), 0666); */
    /* if(shrd_id_sgn_fps < 0) {  // error semantics */
    /*     printf("Can't Access Shared memory for sgn_fps...\n"); */
    /*     return -1; */
    /* } */

    /* open shared process checker */
    shrd_id_process_check = shmget(shm_key_process_check, sizeof(int), 0666);
    if (shrd_id_process_check < 0) {  // error semantics
         printf("Can't Access Shared memory for process_checker...\n");
         return -1;
    }


    /****************************************************************/
    /* get address of shared memory */
    /****************************************************************/
    shrd_ptr_size = (int*)shmat(shrd_id_size, NULL, 0);

    shrd_ptr_rbuf = (obj_coordinate *)shmat(shrd_id_rbuf, NULL, 0);
    shrd_ptr_rbuf_head = (int *)shmat(shrd_id_rbuf_head, NULL, 0);
    shrd_ptr_rbuf_tail = (int *)shmat(shrd_id_rbuf_tail, NULL, 0);

    shrd_ptr_rwlock = (pthread_rwlock_t *)shmat(shrd_id_rwlock, NULL, 0);

    shrd_ptr_imgupd = (char*)shmat(shrd_id_imgupd, NULL, 0);

    /* shrd_ptr_car_fps = (int*)shmat(shrd_id_car_fps, NULL, 0); */
    /* shrd_ptr_pds_fps = (int*)shmat(shrd_id_pds_fps, NULL, 0); */
    /* shrd_ptr_sgn_fps = (int*)shmat(shrd_id_sgn_fps, NULL, 0); */

    shrd_ptr_process_check = (int*)shmat(shrd_id_process_check, NULL, 0);

    /*************************************************************************/
    // prepare for using shared memory and semaphoer
    /*************************************************************************/
    /*************************************************************************/




    /* call initialize function */
    //  dlibImageInit(&imgdes, NULL, 0, FROM_CAM);
    dlibImageInit(&imgdes_shm, INPUT_SHM_PATH, IMAGE_SIZE, FROM_SHM);
    dlibImageInit(&imgdes_shm_output, OUTPUT_SHM_PATH, IMAGE_SIZE, FROM_SHM);

    /*************************************************************************/
    /* initialize grasshopper camera */
    /*************************************************************************/
    /* fc2Context context; */
    /* fc2Error err; */
    /* fc2PGRGuid guid; */
    /* fc2Image  raw_image, bgr_image;  */
    /* IplImage *cv_image, *vga_image;  */

    /* err = fc2CreateContext(&context); // create camera context */
    /* MY_FC2_CHECK(err, "fc2CreateContext()"); */

    /* unsigned int numCameras = 0; */
    /* err = fc2GetNumOfCameras(context, &numCameras); */
    /* MY_FC2_CHECK(err, "fc2GetNumOfCameras()");  */

    /* if (numCameras == 0) {        // No cameras detected */
    /*     fprintf(stderr, "No PGR grasshopper camera detected.\n"); */
    /*     fprintf(stderr, "program exit.\n"); */
    /*     exit(0); */
    /* } */

    /* /\* get the 0th camera *\/ */
    /* err = fc2GetCameraFromIndex(context, 0, &guid);  */
    /* MY_FC2_CHECK(err, "fc2GetCameraFromIndex()"); */
  
    /* err = fc2Connect(context, &guid); // make connection to camera */
    /* MY_FC2_CHECK(err, "fc2Connect()"); */

    /* /\* start capturing *\/ */
    /* err = fc2StartCapture(context);  */
    /* MY_FC2_CHECK(err, "fc2StartCapture()"); */

    /* err = fc2CreateImage(&raw_image); */
    /* MY_FC2_CHECK(err, "fc2CreateImage(raw_image)"); */
  
    /* err = fc2CreateImage(&bgr_image); */
    /* MY_FC2_CHECK(err, "fc2CreateImage(rgb_image)"); */
    /* bgr_image.format = FC2_PIXEL_FORMAT_BGR; // set the format to standard BGR */

    /* /\* capture image once *\/ */
    /* err = fc2RetrieveBuffer(context, &raw_image); */
    /* MY_FC2_CHECK(err, "fc2RetrieveBuffer() first"); */

    /* /\* create OpenCV image descriptor for raw image *\/ */
    /* cv_image = cvCreateImage( cvSize(raw_image.cols, raw_image.rows), IPL_DEPTH_8U, 3);  */

    /* /\* create OpenCV image descriptor for VGA size image *\/ */
    /* vga_image = cvCreateImage( cvSize(RESIZED_IMG_WIDTH, RESIZED_IMG_HEIGHT), IPL_DEPTH_8U, 3);  */


    /*************************************************************************/

    /* initialize static Frame Per Second values */
    /* car_fps = 0; */
    /* pds_fps = 0; */
    /* sgn_fps = 0; */

    /* create thread for get frame per second */
    /* thread_arg.semaphore_id = semid; */
    /* thread_arg.ptr_shared_car_fps = shrd_ptr_car_fps; */
    /* thread_arg.ptr_shared_pds_fps = shrd_ptr_pds_fps; */
    /* thread_arg.ptr_shared_sgn_fps = shrd_ptr_sgn_fps; */

    /* pthread_create(&th_getFPS, NULL, getFPS, (void *)&thread_arg); */

    /* prepare for read and write avi video file */
    capture = cvCaptureFromAVI(src_videoName);
    video_fps = cvGetCaptureProperty(capture, CV_CAP_PROP_FPS);
    video_size = cvSize(
        (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH),
        (int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT)
        );
    writer = cvCreateVideoWriter(dst_videoName, CV_FOURCC('X', 'V', 'I', 'D'), video_fps, video_size, 1);
    vga_image = cvCreateImage( cvSize(RESIZED_IMG_WIDTH, RESIZED_IMG_HEIGHT), IPL_DEPTH_8U, 3);  

    printf("\ndetection start\n");

    while(1) { 

        // /* get image from camera */
        // image_size = dlibImageGet(&buf, &imgdes);
        // if(image_size < 0) {
        //   printf("dlibImageGet error. image_size = %d\n", image_size);
        //   exit(1);
        // }

        /*************************************************************************/
        /* capture image and convert to VGA size */
        /*************************************************************************/
        /* /\* capture image from camera *\/ */
        /* err = fc2RetrieveBuffer(context, &raw_image); */
        /* MY_FC2_CHECK(err, "fc2RetrieveBuffer() in loop"); */
    
        /* /\* convert raw image to standerd BGA format image *\/ */
        /* err = fc2ConvertImageTo(FC2_PIXEL_FORMAT_BGR, &raw_image, &bgr_image); */
        /* MY_FC2_CHECK(err, "fc2ConvertImageTo()"); */

        /* /\* copy data to OpenCV image descriptor *\/ */
        /* memcpy(cv_image->imageData, bgr_image.pData, bgr_image.rows * bgr_image.stride);  */
        
        /* /\* resize image to VGA size *\/ */
        /* cvResize(cv_image, vga_image, CV_INTER_LINEAR); */

        /* /\* encode image to jpeg format *\/ */
        /* CvMat *encoded_img = cvEncodeImage(".jpg", vga_image, 0); */

        /* /\* allocate buffer and copy image data *\/ */
        /* int image_size = encoded_img->cols * encoded_img->rows; */
        /* buf = (unsigned char *)calloc(image_size, sizeof(unsigned char)); */
        /* memcpy(buf, encoded_img->data.ptr, image_size); */

        /* cvReleaseMat(&encoded_img); */

        /*************************************************************************/

        /*************************************************************************/
        /* get one frame from video file */
        /*************************************************************************/
        if ((cv_image = cvQueryFrame(capture)) == NULL) /* Do not release cv_image in manual */
        {
            break;
        }

        frame_count++;
        switch (frame_count%3) {
        case 0:
            printf("processing.  %d\r", frame_count);
            break;
        case 1:
            printf("processing.. %d\r", frame_count);
            break;
        case 2:
            printf("processing...%d\r", frame_count);
            break;
        }
 

        /* resize image to VGA size */
        cvResize(cv_image, vga_image, CV_INTER_LINEAR);

        /* encode image to jpeg format */
        CvMat *encoded_img = cvEncodeImage(".jpg", vga_image, 0);

        /* allocate buffer and copy image data */
        int image_size = encoded_img->cols * encoded_img->rows;
        buf = (unsigned char *)calloc(image_size, sizeof(unsigned char));
        memcpy(buf, encoded_img->data.ptr, image_size);

        cvReleaseMat(&encoded_img);
        /*************************************************************************/

        /* set image to shared memory */
        rtn = pthread_rwlock_wrlock(shrd_ptr_rwlock); /* lock reader-writer lock as a writer */
        if(rtn != 0) {
            printf("pthread_rwlock_wrlock failed.\nerror no.%d\n", rtn);
        }
        
        dlibImageSet(buf, image_size, &imgdes_shm);
        
        rtn = pthread_rwlock_unlock(shrd_ptr_rwlock); /* unlock reader-writer lock */
        if(rtn != 0) {
            printf("pthread_rwlock_unlock failed\n");
        }
        

        //get current time
        gettimeofday(&tv, NULL);
        tmptr = localtime(&tv.tv_sec);

        /* write image update checker */
        My_sem_operation(semid, LOCK); /* lock semaphore */
//        sprintf(shrd_ptr_imgupd,"%02d%02d%02d%3d", tmptr->tm_hour, tmptr->tm_min, tmptr->tm_sec, tv.tv_usec/1000);
        sprintf(shrd_ptr_imgupd,"%d", frame_count);
        My_sem_operation(semid, UNLOCK); /* unlock semaphore */
        
//        cvWaitKey(2);         /* wait 2ms */

        /* wait until all detection program complete its work */
        while(1) {
            My_sem_operation(semid, LOCK); /* lock semaphore */
            process_check = *shrd_ptr_process_check;
            My_sem_operation(semid, UNLOCK); /* unlock semaphore */
            
            if (process_check == 4) { /* if car, pedestrian, sign, line detection is completed */
                My_sem_operation(semid, LOCK); /* lock semaphore */
                *shrd_ptr_process_check = 0;
                My_sem_operation(semid, UNLOCK); /* unlock semaphore */
                break;
            }
        }

        /* conver image data(unsigned char) to IplImage*/
        int shm_image_size = IMAGE_SIZE;
        tmpbuf = cvCreateMat(1, shm_image_size, CV_8UC3); 

        rtn = pthread_rwlock_rdlock(shrd_ptr_rwlock); /* lock reader-writer lock as a reader */
        if(rtn != 0) {
            printf("pthread_rwlock_rdlock failed.\nerror no.%d\n", rtn);
        }

        dlibImageGet(&buf_output, &imgdes_shm_output);

        rtn = pthread_rwlock_unlock(shrd_ptr_rwlock); /* unlock reader-writer lock as a reader */
        if(rtn != 0) {
            printf("pthread_rwlock_unlock failed.\nerror no.%d\n", rtn);
        }


#ifdef NO_LINE_DETECTION
        memcpy(tmpbuf->data.ptr, buf, image_size);
#else
        memcpy(tmpbuf->data.ptr, buf_output, shm_image_size);
#endif

        image_res = cvDecodeImage(tmpbuf, CV_LOAD_IMAGE_COLOR);

        /* get objects coordinates */
        My_sem_operation(semid, LOCK); /* lock semaphore */

        num = *shrd_ptr_rbuf_tail - *shrd_ptr_rbuf_head; /* the number of detected object */
        if(num==0) num++;
        if(num < 0) num += MAX_OBJECT_NUM;
        
        //data of detection result
        int *data = (int *)malloc((4 + num*6)*sizeof(int)); 
        if(data == NULL) {
            printf("memory allocation error!!\n");
            printf("num %d\n", num);
            return -1;
        }
        
        
        /* header
           number of object
           resolution
           Reserverd
           Reserverd
        */
        data[0] = num;
        data[1] = VGA;
        data[2] = 0;
        data[3] = 0;

        i = 0;        
        while(i < num) {
            apGetCoordinate(shrd_ptr_rbuf, /* obj_coordinate *queue */
                            shrd_ptr_rbuf_head, /* int *head */
                            shrd_ptr_rbuf_tail, /* int *tail */
                            &data[4+i*6],       /* int *left */
                            &data[4+i*6+1],     /* int *upper */
                            &data[4+i*6+2],     /* int *right */
                            &data[4+i*6+3],     /* int *bottom */
                            &data[4+i*6+4]      /* int *type */
                );
            
            data[4+i*6+5] = 0;     /* reserved value(currently 0) */

            i++;
        }
        My_sem_operation(semid, UNLOCK); /* unlock semaphore */
        
        
        /* draw detection results */
        i = 0;
        while(i < num) {
            switch(data[4+i*6+4]) {
            case CAR:
                rects_color = CV_RGB(0, 0, 255); /* blue */
                break;
            case SIGN:
                rects_color = CV_RGB(255, 255, 0); /* yellow */
                break;
            case PEDESTRIAN:
                rects_color = CV_RGB(0, 255, 0); /* green */
                break;
            default:
                rects_color = CV_RGB(0, 0, 0); /* black */
                break;   
            }

            p1 = cvPoint(data[4+i*6], data[4+i*6+1]); /* p1(left, upper) */
            p2 = cvPoint(data[4+i*6+2], data[4+i*6+3]); /* p2(right, bottom) */

            cvRectangle(image_res, p1, p2, rects_color, 5, 8, 0);

            i++;
        }

        /* write Frame Per Second on image */
//        writeFPS(image_res);
        
        /* show image */
//        cvShowImage("detection result", image_res);
  
        /* write to video file */
        cvWriteFrame(writer, image_res);
      
        //        if(cvWaitKey(2) != -1) break; /* wait 2ms */

        /* release resources */
        //    dlibImageFree(buf);
        free(buf);
        dlibImageFree(buf_output);
        cvReleaseMat(&tmpbuf);
        cvReleaseImage(&image_res);
        free(data);
    }
    
    
    /* call clean up function */
    //  dlibImageExit(&imgdes);
    dlibImageExit(&imgdes_shm);
    dlibImageExit(&imgdes_shm_output);

    /* /\* stop capture *\/ */
    /* err = fc2StopCapture(context);  */
    /* MY_FC2_CHECK(err, "fc2StopCapture()"); */
  
  
    /* /\* release image descriptor *\/ */
    /* err = fc2DestroyImage(&raw_image); */
    /* MY_FC2_CHECK(err, "fc2DestroyImage(raw_image)"); */
  
    /* err = fc2DestroyImage(&bgr_image); */
    /* MY_FC2_CHECK(err, "fc2DestroyImage(bgr_image)"); */

    /* /\* destroy context *\/ */
    /* err = fc2DestroyContext(context); */
    /* MY_FC2_CHECK(err, "fc2DestroyContext()"); */
  
    /* release OpenCV image descriptor */
    /* cvReleaseImage(&cv_image);  */
    cvReleaseImage(&vga_image);

    cvReleaseVideoWriter(&writer);
    cvReleaseCapture(&capture);

    printf("\ndetection complete!\n");

}

