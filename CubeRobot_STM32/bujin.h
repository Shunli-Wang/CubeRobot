#ifndef __BUJIN_H
#define __BUJIN_H
#include "sys.h"

#define kai1 62
#define kai2 46
#define kai3 62
#define kai4 70
#define he1 153
#define he2 150
#define he3 159
#define he4 163

void bujin1(u8 fangxiang,u8 jiaodu);
void bujin2(u8 fangxiang,u8 jiaodu);
void bujin3(u8 fangxiang,u8 jiaodu);
void bujin4(u8 fangxiang,u8 jiaodu);

void duoji1(double jiaodu);
void duoji2(double jiaodu);
void duoji3(double jiaodu);
void duoji4(double jiaodu);

void zhangkai(double jiaodu1,double jiaodu2,double jiaodu3,double jiaodu4);
void bihe(double jiaodu1,double jiaodu2,double jiaodu3,double jiaodu4);
void saomiao(void);
void jieshou(void);
void jiemofang(u8* result);

void F(u8 num);
void B(u8 num);
void U(u8 num);
void D(u8 num);
void L(u8 num);
void R(u8 num);
void X(void);
void S(void);

void zhuangdong1(void);
void zhuangdong2(void);
void zhuangdong3(void);
void zhuangdong4(void);
void zhuangdong5(void);
void zhuangdong6(void);
void weizhichushi(void);

void duoji13(double jiaodu2,double jiaodu4);
void duoji24(double jiaodu2,double jiaodu4);

void bujin13(u8 fangxiang1,u8 fangxiang3,u8 jiaodu);
void bujin24(u8 fangxiang2,u8 fangxiang4,u8 jiaodu);

void chuli(u8* result,u8 *f);

#endif
