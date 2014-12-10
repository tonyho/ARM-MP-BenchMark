/*
  ~/workspace/MemSpeed/jni$ ~/Eclipse/android-ndk-r7/ndk-build
*/

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <math.h>
 #include <time.h> 
 //#include "jni.h"

  #define version  "32 Bit Version 4"

  int n1;

  double  xd[4194304];  // 32 MB 
  double  yd[4194304];  // 32 MB
  float  * xs;
  float  * ys;

  int    * xi; 
  int    * yi;
 
double runSecs = 0.1;
double startSecs;
double  secs;
char resultchars[1000];

 double getTime()
 {
     struct timespec tp1;
     clock_gettime(CLOCK_REALTIME, &tp1);
     return (double)tp1.tv_sec + (double)tp1.tv_nsec / 1e9;
 }
 
 void start_time()
  {
      startSecs = getTime();
      return;
  }

  void end_time()
  {
      secs = getTime() - startSecs;
      return;
  }


  void checkTime()
  {
     if (secs < runSecs)
     {
          if (secs < runSecs / 8.0)
          {
                n1 = n1 * 10;
          }
          else
          {
                n1 = (int)(runSecs * 1.25 / secs * (double)n1+1);
          }
      }
  }


 //jstring
 //Java_com_memspeed_MemSpeedActivity_stringFromJNI( JNIEnv* env, jobject thiz, jint size)
int main(int argc, char * argv[])
{
    
    int passes[25];

    int useMem;   

  
    float  sums;
    float  ones = 1.0;
    float  zeros = 0;
      
    int g, i, m, nn;
    int kd, ks, ki, mem;

    int  sumi;
   
    int  zeroi = 0;
    int onei = 1;
             
    int inc;
    double sumd;
    double mbpsd1, mbpss1, mbpsi1;
    double mbpsd2, mbpss2, mbpsi2;
    double oned = 1.0;
    double zerod = 0;
    double memMB;
    
    passes[0]  =      1000;   //     16 KB
    passes[1]  =      2000;   //     32 KB
    passes[2]  =      4000;   //     64 KB
    passes[3]  =      8000;   //    128 KB
    passes[4]  =     16000;   //    256 KB
    passes[5]  =     32000;   //    512 kB
    passes[6]  =     64000;   //      1 MB
    passes[7]  =    256000;   //      4 MB
    passes[8]  =   1024000;   //     16 MB
    passes[9]  =   4096000;   //     64 MB  - Max here runs = 10
    passes[10] =  16384000;   //    256 MB
    passes[11] =  65536000;   //   1024 MB


 
    float *xs = (float *) xd;
    float *ys = (float *) yd;

     int   *xi = (int *) xd;
     int   *yi = (int *) yd;     
  
    {
        kd = passes[size];
        
        nn = 6400000 / kd;
        if (nn < 1) nn = 1;
        
        ks = kd * 2;

        ki = kd * 2; 
        
        memMB = (double)kd * 16.0 / 1000000;
        mem = (int)((double)kd * 16.0 / 1000);

        inc = 4;
          
        n1 = nn;
        
        do
        {
            sumd = 1.00001;
            for (m=0; m<kd; m++)
            {
                  xd[m] = oned;
                  yd[m] = oned;
            }          
            start_time();
            for (i=0; i<n1; i++)
            {
                for (m=0; m<kd; m=m+inc)
                {
                   xd[m]   = xd[m]   + sumd * yd[m];
                   xd[m+1] = xd[m+1] + sumd * yd[m+1];
                   xd[m+2] = xd[m+2] + sumd * yd[m+2];
                   xd[m+3] = xd[m+3] + sumd * yd[m+3];
                 }
            }
            end_time();
            checkTime();
        }
        while (secs < runSecs);
        
        mbpsd1 = (double)n1 * memMB / secs;

                 
        n1 = nn;
        do
        {
            sums = 1.0001;
            for (m=0; m<ks; m++)
            {
                  xs[m] = ones;
                  ys[m] = ones;
            }          
            start_time();
            for (i=0; i<n1; i++)
            {
                for (m=0; m<ks; m=m+inc)
                {
                   xs[m]   = xs[m]   + sums * ys[m];
                   xs[m+1] = xs[m+1] + sums * ys[m+1];
                   xs[m+2] = xs[m+2] + sums * ys[m+2];
                   xs[m+3] = xs[m+3] + sums * ys[m+3];
                }
            }
            end_time();
            checkTime();
        }
        while (secs < runSecs);

        mbpss1 =  (double)n1 * memMB / secs;
         
        n1 = nn;
        do
        {
            sumi = nn;
            for (m=0; m<ki; m++)
            {
                  xi[m] = zeroi;
                  yi[m] = zeroi;
            }          
            yi[ki-1] = onei;
                    
            start_time();
            for (i=0; i<n1; i++)
            {
               for (m=0; m<ki; m=m+inc)
               {
                   xi[m]   = xi[m]   + sumi + yi[m];
                   xi[m+1] = xi[m+1] + sumi + yi[m+1];
                   xi[m+2] = xi[m+2] + sumi + yi[m+2];
                   xi[m+3] = xi[m+3] + sumi + yi[m+3];
                }
                sumi = -sumi;
            }
            end_time();
            checkTime();
        }
        while (secs < runSecs);
                  
        mbpsi1 = (double)n1 * memMB / secs;
            
        n1 = nn;
        do
        {
            for (m=0; m<kd; m++)
            {
                  xd[m] = zerod;
                  yd[m] = oned;
            }          
            start_time();
            for (i=0; i<n1; i++)
            {
                for (m=0; m<kd; m=m+inc)
                {
                      xd[m]   = xd[m] + yd[m];
                      xd[m+1] = xd[m+1] + yd[m+1];
                      xd[m+2] = xd[m+2] + yd[m+2];
                      xd[m+3] = xd[m+3] + yd[m+3];
                }
            }
            end_time();
            checkTime();
        }
        while (secs < runSecs);
    
        sumd = xd[1];

        mbpsd2 = (double)n1 * memMB / secs;

        n1 = nn;
        do
        {
            for (m=0; m<ks; m++)
            {
                  xs[m] = zeros;
                  ys[m] = ones;
            }          
            start_time();
            for (i=0; i<n1; i++)
            {
                for (m=0; m<ks; m=m+inc)
                {
                      xs[m] = xs[m] + ys[m];
                      xs[m+1] = xs[m+1] + ys[m+1];
                      xs[m+2] = xs[m+2] + ys[m+2];
                      xs[m+3] = xs[m+3] + ys[m+3];
                }
            }
            end_time();
            checkTime();
        }
        while (secs < runSecs);
            

        sums = xs[1];
        mbpss2 = (double)n1 * memMB / secs;

        n1 = nn;
        do
        {
            for (m=0; m<ki; m++)
            {
                  xi[m] = zeroi;
                  yi[m] = onei;
            }          
                    
            start_time();
            for (i=0; i<n1; i++)
            {
                for (m=0; m<ki; m=m+inc)
                {
                     xi[m] = xi[m] + yi[m];
                     xi[m+1] = xi[m+1] + yi[m+1];
                     xi[m+2] = xi[m+2] + yi[m+2]; 
                     xi[m+3] = xi[m+3] + yi[m+3]; 
                }
            }
            end_time();
            checkTime();
        }
        while (secs < runSecs);
     
        sumi = xi[1];
        mbpsi2 = (double)n1 * memMB / secs;
        

          sprintf(resultchars, "%8d%7d%7d%7d%7d%7d%7d\n",
                              mem, (int)mbpsd1, (int)mbpss1, (int)mbpsi1,
                                   (int)mbpsd2, (int)mbpss2, (int)mbpsi2);
     }
    printf("%s",resultchars);
    return 0;
    // return (*env)->NewStringUTF(env, resultchars);
}

int size
  16,
  32,
  64,
 128, 
 256,
 512,
   1,
   4,
  16,
  64,
 256,
1024,
