
#ifndef STEP_MOTOR_DRV
#define STEP_MOTOR_DRV

#include  "MEPCIOINI.H"
#include  "MEPCIODEV.H"

/* -------------------- initMotionCard ------------------------- *
 * 1. cycleTime��form timer�]�w���ɶ��A�����MintpInit�]�w���ۦP  *
 * ------------------------------------------------------------- */
int initMotionCard( double U , double V , double W , int cycleTime , LIOISR TimerFunction );
;
/* ---------- �����b�d -------------- *
 * 1. �����Ѽ�
 * ---------------------------------- */
int closeMotionCard( void );

// -------------------------------------------------- //
//    putAxisValue
// -------------------------------------------------- //
int putAxisValue(int axis, int increment);

/* ---------- �}�� timer ------------- *
 * 1. interval �����Oms
 * ----------------------------------- */
int enableHDTimer(int interval);

/* ---------- ���� timer -------------- *
 * 1. �����Ѽ�
 * ------------------------------------ */
int disableHDTimer(void);


#endif