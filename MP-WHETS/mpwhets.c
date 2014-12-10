/*
  ~/workspace/MemSpeed/jni$ ~/Eclipse/android-ndk-r7/ndk-build
*/



 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <math.h>
 #include <time.h> 
 //#include "jni.h"
 #include <pthread.h> 

 #define SPDP float
 SPDP Check;
 SPDP results[65][9];
 
 double  secs;
 double  startSecs;
 double score[66][10];
 double timec[66][10];


 int  test;
 int  x100 = 100;
 int  n1;
 int  n2;
 int  n3;
 int  n4;
 int  n5;
 int  n6;
 int  n7;
 int  n8;
 int  n1mult = 10;
 int  n3mult = 5;
 int  n7mult = 10;
 int  repeatPasses = 1;
    
 char resultchars[1000];

 pthread_t tid[100]; 
 pthread_attr_t * attrt = NULL; 
 pthread_mutex_t mutext = PTHREAD_MUTEX_INITIALIZER;

void MFLOPS1(SPDP e11[4], SPDP ta0, long thrd)
{
    int i;
    
    for(i=0; i<n1*n1mult; i++)
    {
          e11[0] = (e11[0] + e11[1] + e11[2] - e11[3]) * ta0;
          e11[1] = (e11[0] + e11[1] - e11[2] + e11[3]) * ta0;
          e11[2] = (e11[0] - e11[1] + e11[2] + e11[3]) * ta0;
          e11[3] = (-e11[0] + e11[1] + e11[2] + e11[3]) * ta0;
    }
    Check = Check + e11[3];
    results[thrd][1] = e11[3];
    return;
}

void MFLOPS2(SPDP e12[4], SPDP t02, long thrd)
{
    int jj;
    
    for(jj=0;jj<6*n2;jj++)
    {
       e12[0] = (e12[0]+e12[1]+e12[2]-e12[3])*t02;
       e12[1] = (e12[0]+e12[1]-e12[2]+e12[3])*t02;
       e12[2] = (e12[0]-e12[1]+e12[2]+e12[3])*t02;
       e12[3] = (-e12[0]+e12[1]+e12[2]+e12[3])/(SPDP)2.0;
    }
    Check = Check + e12[3];
    results[thrd][2] = e12[3];
    return;
}
  

__inline void MIPSInt(int j, int k, int l, SPDP e14[4], long thrd)
{
    int i;
     
    for(i=0; i<n4; i++)
    {
         j = j *(k-j)*(l-k);
         k = l * k - (l-j) * k;
         l = (l-k) * (k+j);
         e14[l-2] = (SPDP)(j + k + l);
         e14[k-2] = (SPDP)(j * k * l);
    }
    Check = Check + e14[k-2];
    results[thrd][4] = e14[0] + e14[1];
    return;
}

SPDP MOPSCOS(SPDP t5, SPDP t25, SPDP x[1], SPDP y[1], long thrd)
{
    int i;
    for(i=1; i<n5; i++)
    {
         x[0] = (SPDP)(t5*atan(t25*sin(x[0])*cos(x[0])/(cos(x[0]+y[0])+cos(x[0]-y[0])-1.0)));
         y[0] = (SPDP)(t5*atan(t25*sin(y[0])*cos(y[0])/(cos(x[0]+y[0])+cos(x[0]-y[0])-1.0)));
    }        
    Check = Check + y[0];
    results[thrd][5] = y[0];
    return y[0];
}

__inline void MFLOPS3(SPDP *x, SPDP *y, SPDP *z, SPDP t, SPDP t1, SPDP t2, long thrd)
{
     int i;
     
     for(i=0; i<n6; i++)
     {
         *x = *y;
         *y = *z;
         *x = t * (*x + *y);
         *y = t1 * (*x + *y);
         *z = (*x + *y)/t2;
     }
     Check = Check + *z;
     results[thrd][6] = *z;
     return;
}


__inline void MIPSEqu(SPDP e1a[4], int j, int k, int l, long thrd)
{
     int i;
      
     for(i=0;i<n7*n7mult;i++)
     {
         e1a[j] = e1a[k];
         e1a[k] = e1a[l];
         e1a[l] = e1a[j];
     }
     Check = Check + e1a[l];
     results[thrd][7] = e1a[l];
     return;
}

 SPDP MOPSExp(SPDP x8, SPDP t18, long thrd)
 {
     int i;
     
     for(i=0; i<n8; i++)
     {
          x8 = (SPDP)(sqrt(exp(log(x8)/t18)));
     }
     Check = Check + x8;
     results[thrd][8] = x8;
     return x8;
}

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

void *whetstones(void *arg)
{
    SPDP x;              
    int i,j,k,l;
    long thread;
    SPDP e1[4];
    double timeb;
    
    volatile int  mainCount = 0;
                    
    SPDP t =  (SPDP)0.49999975;
    SPDP t0 = t;        
    SPDP ta = t;        
    SPDP tb = t;        
    SPDP t1 = (SPDP)0.50000025;
    SPDP t2 = 2.0;
    
    Check=0.0;

    thread = (long)arg;

    // Section 1, Array elements
    
    if (test==1)
    {
        e1[0] = 1.0;
        e1[1] = -1.0;
        e1[2] = -1.0;
        e1[3] = -1.0;
        
        mainCount = 0;

        do
        {
            MFLOPS1(e1, ta, thread);
            mainCount = mainCount + 1;
            ta = (SPDP)1.0 - ta;
        }
        while (mainCount < repeatPasses);
                          
        pthread_mutex_lock( &mutext);      
        end_time();
        timeb = secs/(double)(n1mult);
        secs = timeb;
        timec[thread][test] = timeb;
        timec[thread][9] = timeb;
        score[thread][test] = (double)(n1*16)*(double)(mainCount)/(1000000.0*timeb);
        pthread_mutex_unlock( &mutext);
    }

    // Section 2, Array as parameter
       
    if (test==2)
    {
        e1[0] = 1.0;
        e1[1] = -1.0;
        e1[2] = -1.0;
        e1[3] = -1.0;

        mainCount = 0;

        do
        {
            MFLOPS2(e1,tb,thread);
            mainCount = mainCount + 1;
            tb = (SPDP)1.0 - tb;
        }
        while (mainCount < repeatPasses);
        
        pthread_mutex_lock( &mutext);      
        end_time();
        timeb = secs;
        timec[thread][test] = timeb;
        timec[thread][9] = timec[thread][9] + timeb;
        score[thread][test] = (double)(n2*96)*(double)(mainCount)/(1000000.0*timeb);
        pthread_mutex_unlock( &mutext);
    }

    // Section 3, Conditional jumps 

    if (test==3)
    {
        int  j = 1;
        int  j3 = 1;
 
        mainCount = 0;
        
        do
        {
            for(i=0; i<n3*n3mult; i++)
            {
                 if(j==1)       j = 2;
                 else           j = 3;
                 if(j>2)        j = 0;
                 else           j = 1;
                 if(j<1)        j = 1;
                 else           j = 0;
            }
            mainCount = mainCount + 1;
        }
        while (mainCount < repeatPasses);
        Check = Check + (SPDP)j;
        results[thread][3] = (SPDP)j;

        pthread_mutex_lock( &mutext);      
        end_time();
        timeb = secs/(double)n3mult;
        secs = timeb;
        timec[thread][test] = timeb;
        timec[thread][9] = timec[thread][9] + timeb;
        score[thread][test] = (double)(n3*3)*(double)(mainCount)/(1000000.0*timeb);
        pthread_mutex_unlock( &mutext);
    }

    // Section 4, Integer arithmetic

    if (test==4)
    {
        int j4 = 1;
        int k4 = 2;
        int l4 = 3;

        mainCount = 0;

        do
        {
            MIPSInt(j4, k4, l4, e1, thread); 
            mainCount = mainCount + 1;
        }
        while (mainCount < repeatPasses);
        pthread_mutex_lock( &mutext);      
        end_time();
        timeb = secs;
        x = e1[0]+e1[1];
        timec[thread][test] = timeb;
        timec[thread][9] = timec[thread][9] + timeb;
        score[thread][test] = (double)(n4*15)*(double)(mainCount)/(1000000.0*timeb);
        pthread_mutex_unlock( &mutext);
    }
     
    // Section 5, Trig functions

    if (test==5)
    {
        SPDP x5[1];
        SPDP y5[1];
        x5[0] = 0.5;
        y5[0] = 0.5;
        mainCount = 0;

        do
        {
            MOPSCOS(t, t2, x5, y5, thread);
            t = (SPDP)1.0 - t;
            mainCount = mainCount + 1;
         }
        while (mainCount < repeatPasses); 
        t = t0;
        pthread_mutex_lock( &mutext);      
        end_time();
        timeb = secs;
        timec[thread][test] = timeb;
        timec[thread][9] = timec[thread][9] + timeb;
        score[thread][test] = (double)(n5*26)*(double)(mainCount)/(1000000.0*timeb);
        pthread_mutex_unlock( &mutext);
    }
    
    // Section 6, Procedure calls

    if (test==6)
    {
        SPDP x6 = 1.0;
        SPDP y6 = 1.0;
        SPDP z6 = 1.0;
        SPDP t6  = t;
        SPDP t16 = t1;
        SPDP t26 = t2;
        mainCount = 0;

        do
        {
            mainCount = mainCount + 1;
            MFLOPS3(&x6,&y6,&z6,t6,t16,t26, thread);
        }
        while (mainCount < repeatPasses);
        pthread_mutex_lock( &mutext);      
        end_time();
        timeb = secs;
        timec[thread][test] = timeb;
        timec[thread][9] = timec[thread][9] + timeb;
        score[thread][test] = (double)(n6*6)*(double)(mainCount)/(1000000.0*timeb);
        pthread_mutex_unlock( &mutext);
    }
    
    // Section 7, Array refrences

    if (test==7)
    {
        j = 0;
        k = 1;
        l = 2;
        e1[0] = 1.0;
        e1[1] = 2.0;
        e1[2] = 3.0;
        mainCount = 0;
        
        do
        {
            MIPSEqu(e1,j,k,l, thread);
            mainCount = mainCount + 1;
            if (e1[0] + e1[1] == (SPDP)23.2) e1[2] = e1[2] + (SPDP)2.0;
        }
        while (mainCount < repeatPasses);        
        pthread_mutex_lock( &mutext);      
        end_time();
        timeb = secs/(double)(n7mult);
        secs = timeb;
        timec[thread][test] = timeb;
        timec[thread][9] = timec[thread][9] + timeb;
        score[thread][test] = (double)(n7*3)*(double)(mainCount)/(1000000.0*timeb);
        pthread_mutex_unlock( &mutext);
    }
    
    // Section 8, Standard functions

    if (test==8)
    {
        x = 0.75;
        mainCount = 0;

        do
        {
            x = MOPSExp(x, t1, thread);
            mainCount = mainCount + 1;
        }
        while (mainCount < repeatPasses);        
        pthread_mutex_lock( &mutext);      
        end_time();
        timeb = secs;
        timec[thread][test] = timeb;
        timec[thread][9] = timec[thread][9] + timeb;
        score[thread][test] = (double)(n8*4)*(double)(mainCount)/(1000000.0*timeb);
        pthread_mutex_unlock( &mutext);
    }
}

//jstring
//Java_com_mpwhets_WhetsActivity_stringFromJNI( JNIEnv* env, jobject thiz, jint size)
int main(int argc, char *argv[])
{

    long  thisThread;

    double TimeUsed;
    double mwips;
    double total[4][10];
    double timeTot[4];

    int  answers[4][10];
    int  i, j, t;
    int  threads;
    int  passThreads[4];
    
    int  count = 10;
    int  duration = 5;

    char errorMsg[100];


    n1 = 12*x100;
    n2 = 14*x100;
    n3 = 345*x100;
    n4 = 210*x100;
    n5 = 32*x100;
    n6 = 899*x100;
    n7 = 616*x100;
    n8 = 93*x100;

    passThreads[0] = 1;
    passThreads[1] = 2;
    passThreads[2] = 4;
    passThreads[3] = 8;

    do
    {
        TimeUsed=0;

        thisThread = 0;
        start_time();
        for (test=1; test<9; test++)
        {
            pthread_create(&tid[thisThread], attrt, whetstones, (void *)thisThread);
            pthread_join(tid[thisThread], NULL);
        }
        TimeUsed = secs;
        count = count - 1;
        if (TimeUsed > 0.2)
           count = 0;
        else
           repeatPasses = repeatPasses * 5;
    }
    while (count > 0);
       
    if (TimeUsed > 0)
                     repeatPasses = (int)((SPDP)(duration * repeatPasses) / TimeUsed);
    if (repeatPasses < 1) repeatPasses = 1;

    for(t=0; t<4; t++)
    {
        threads = passThreads[t];
           
        timeTot[t] = 0;
        TimeUsed = 0;
    
        for (test=1; test<9; test++)
        {
            start_time();
            for (thisThread=1; thisThread<threads+1; thisThread++)
            {
                pthread_create(&tid[thisThread], attrt, whetstones, (void *)thisThread);
            }
            for (thisThread=1; thisThread<threads+1; thisThread++)
            {
                pthread_join(tid[thisThread], NULL);
            }
            end_time();
            TimeUsed = TimeUsed + secs;
        }
        
        timeTot[t] = TimeUsed;
        for (i=1; i<threads+1; i++)
        {
            score[i][9] = 0.0;
        }
    
        for (i=1; i<threads+1; i++)
        {
            mwips=(double)(repeatPasses) * (double)(x100) / (10 * timec[i][9]);
            score[i][9] = mwips;
        }
        results[t][9] = 0.0;    
        for (j=1; j<10; j++)
        {
            total[t][j] = 0.0;
            for (i=1; i<threads+1; i++)
            {
                total[t][j] = total[t][j] + score[i][j];
            }
        }
        sprintf(errorMsg, " All calculations produced consistent numeric results");
        for (j=1; j<10; j++)
        {
            for (i=1; i<threads+1; i++)
            {
               if (results[i][j] != results[1][j])
               {
                   sprintf(errorMsg, " Numeric results incorrect");
               }
            }
        }

    }
    sprintf(resultchars, "1T %7.1f%7.1f%7.1f%7.1f%6.1f%6.1f%7.1f%7.1f%7.1f\n"
                         "2T %7.1f%7.1f%7.1f%7.1f%6.1f%6.1f%7.1f%7.1f%7.1f\n"
                         "4T %7.1f%7.1f%7.1f%7.1f%6.1f%6.1f%7.1f%7.1f%7.1f\n"
                         "8T %7.1f%7.1f%7.1f%7.1f%6.1f%6.1f%7.1f%7.1f%7.1f\n"
                         "\n"
                         " Overall Seconds %6.2f 1T, %6.2f 2T, %6.2f 4T, %6.2f 8T\n"
                         "\n"
                         "%s\n"
                         "\n",
                          total[0][9], total[0][1], total[0][2], total[0][6], total[0][5],
                          total[0][8], total[0][4], total[0][3], total[0][7],
                          total[1][9], total[1][1], total[1][2], total[1][6], total[1][5],
                          total[1][8], total[1][4], total[1][3], total[1][7],
                          total[2][9], total[2][1], total[2][2], total[2][6], total[2][5],
                          total[2][8], total[2][4], total[2][3], total[2][7],
                          total[3][9], total[3][1], total[3][2], total[3][6], total[3][5],
                          total[3][8], total[3][4], total[3][3], total[3][7],
                          timeTot[0], timeTot[1], timeTot[2], timeTot[3],
                          errorMsg                          
                          );

    printf("%s",resultchars);
    return 0;
    // return (*env)->NewStringUTF(env, resultchars);
}






 

