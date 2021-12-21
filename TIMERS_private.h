#ifndef _TIMERS_PRIVATE_H
#define _TIMERS_PRIVATE_H

/*GPTM0 registers definitions*/
#define GPTM0_CFG * ((u32*) 0x40030000)
#define GPTM0_TAMR * ((u32*) 0x40030004)
#define GPTM0_TBMR * ((u32*) 0x40030008)
#define GPTM0_CTL * ((u32*) 0x4003000C)
#define GPTM0_SYNC * ((u32*) 0x40030010)
#define GPTM0_IMR * ((u32*) 0x40030018)
#define GPTM0_RIS * ((u32*) 0x4003001C)
#define GPTM0_MIS * ((u32*) 0x40030020)
#define GPTM0_ICR * ((u32*) 0x40030024)
#define GPTM0_TAILR * ((u32*) 0x40030028)
#define GPTM0_TBILR * ((u32*) 0x4003002C)
#define GPTM0_TAMATCHR * ((u32*) 0x40030030)
#define GPTM0_TBMATCHR * ((u32*) 0x40030034)
#define GPTM0_TAPR * ((u32*) 0x40030038)
#define GPTM0_TBPR * ((u32*) 0x4003003C)
#define GPTM0_TAPMR * ((u32*) 0x40030040)
#define GPTM0_TBPMR * ((u32*) 0x40030044)
#define GPTM0_TAR * ((u32*) 0x40030048)
#define GPTM0_TBR * ((u32*) 0x4003004C)
#define GPTM0_TAV * ((u32*) 0x40030050)
#define GPTM0_TBV * ((u32*) 0x40030054)
#define GPTM0_RTCPD * ((u32*) 0x40030058)
#define GPTM0_TAPS * ((u32*) 0x4003005C)
#define GPTM0_TBPS * ((u32*) 0x40030060)
#define GPTM0_TAPV * ((u32*) 0x40030064)
#define GPTM0_TBPV * ((u32*) 0x40030068)
#define GPTM0_PP * ((u32*) 0x40030FC0)

/*GPTM1*/
#define GPTM1_CFG * ((u32*) 0x40031000)
#define GPTM1_TAMR * ((u32*) 0x40031004)
#define GPTM1_TBMR * ((u32*) 0x40031008)
#define GPTM1_CTL * ((u32*) 0x4003100C)
#define GPTM1_SYNC * ((u32*) 0x40031010)
#define GPTM1_IMR * ((u32*) 0x40031018)
#define GPTM1_RIS * ((u32*) 0x4003101C)
#define GPTM1_MIS * ((u32*) 0x40031020)
#define GPTM1_ICR * ((u32*) 0x40031024)
#define GPTM1_TAILR * ((u32*) 0x40031028)
#define GPTM1_TBILR * ((u32*) 0x4003102C)
#define GPTM1_TAMATCHR * ((u32*) 0x40031030)
#define GPTM1_TBMATCHR * ((u32*) 0x40031034)
#define GPTM1_TAPR * ((u32*) 0x40031038)
#define GPTM1_TBPR * ((u32*) 0x4003103C)
#define GPTM1_TAPMR * ((u32*) 0x40031040)
#define GPTM1_TBPMR * ((u32*) 0x40031044)
#define GPTM1_TAR * ((u32*) 0x40031048)
#define GPTM1_TBR * ((u32*) 0x4003104C)
#define GPTM1_TAV * ((u32*) 0x40031050)
#define GPTM1_TBV * ((u32*) 0x40031054)
#define GPTM1_RTCPD * ((u32*) 0x40031058)
#define GPTM1_TAPS * ((u32*) 0x4003105C)
#define GPTM1_TBPS * ((u32*) 0x40031060)
#define GPTM1_TAPV * ((u32*) 0x40031064)
#define GPTM1_TBPV * ((u32*) 0x40031068)
#define GPTM1_PP * ((u32*) 0x40031FC0)

/*GPTM2*/
#define GPTM2_CFG * ((u32*) 0x40032000)
#define GPTM2_TAMR * ((u32*) 0x40032004)
#define GPTM2_TBMR * ((u32*) 0x40032008)
#define GPTM2_CTL * ((u32*) 0x4003200C)
#define GPTM2_SYNC * ((u32*) 0x40032010)
#define GPTM2_IMR * ((u32*) 0x40032018)
#define GPTM2_RIS * ((u32*) 0x4003201C)
#define GPTM2_MIS * ((u32*) 0x40032020)
#define GPTM2_ICR * ((u32*) 0x40032024)
#define GPTM2_TAILR * ((u32*) 0x40032028)
#define GPTM2_TBILR * ((u32*) 0x4003202C)
#define GPTM2_TAMATCHR * ((u32*) 0x40032030)
#define GPTM2_TBMATCHR * ((u32*) 0x40032034)
#define GPTM2_TAPR * ((u32*) 0x40032038)
#define GPTM2_TBPR * ((u32*) 0x4003203C)
#define GPTM2_TAPMR * ((u32*) 0x40032040)
#define GPTM2_TBPMR * ((u32*) 0x40032044)
#define GPTM2_TAR * ((u32*) 0x40032048)
#define GPTM2_TBR * ((u32*) 0x4003204C)
#define GPTM2_TAV * ((u32*) 0x40032050)
#define GPTM2_TBV * ((u32*) 0x40032054)
#define GPTM2_RTCPD * ((u32*) 0x40032058)
#define GPTM2_TAPS * ((u32*) 0x4003205C)
#define GPTM2_TBPS * ((u32*) 0x40032060)
#define GPTM2_TAPV * ((u32*) 0x40032064)
#define GPTM2_TBPV * ((u32*) 0x40032068)
#define GPTM2_PP * ((u32*) 0x40032FC0)

/*GPTM3*/
#define GPTM3_CFG * ((u32*) 0x40033000)
#define GPTM3_TAMR * ((u32*) 0x40033004)
#define GPTM3_TBMR * ((u32*) 0x40033008)
#define GPTM3_CTL * ((u32*) 0x4003300C)
#define GPTM3_SYNC * ((u32*) 0x40033010)
#define GPTM3_IMR * ((u32*) 0x40033018)
#define GPTM3_RIS * ((u32*) 0x4003301C)
#define GPTM3_MIS * ((u32*) 0x40033020)
#define GPTM3_ICR * ((u32*) 0x40033024)
#define GPTM3_TAILR * ((u32*) 0x40033028)
#define GPTM3_TBILR * ((u32*) 0x4003302C)
#define GPTM3_TAMATCHR * ((u32*) 0x40033030)
#define GPTM3_TBMATCHR * ((u32*) 0x40033034)
#define GPTM3_TAPR * ((u32*) 0x40033038)
#define GPTM3_TBPR * ((u32*) 0x4003303C)
#define GPTM3_TAPMR * ((u32*) 0x40033040)
#define GPTM3_TBPMR * ((u32*) 0x40033044)
#define GPTM3_TAR * ((u32*) 0x40033048)
#define GPTM3_TBR * ((u32*) 0x4003304C)
#define GPTM3_TAV * ((u32*) 0x40033050)
#define GPTM3_TBV * ((u32*) 0x40033054)
#define GPTM3_RTCPD * ((u32*) 0x40033058)
#define GPTM3_TAPS * ((u32*) 0x4003305C)
#define GPTM3_TBPS * ((u32*) 0x40033060)
#define GPTM3_TAPV * ((u32*) 0x40033064)
#define GPTM3_TBPV * ((u32*) 0x40033068)
#define GPTM3_PP * ((u32*) 0x40033FC0)

/*GPTM4*/
#define GPTM4_CFG * ((u32*) 0x40034000)
#define GPTM4_TAMR * ((u32*) 0x40034004)
#define GPTM4_TBMR * ((u32*) 0x40034008)
#define GPTM4_CTL * ((u32*) 0x4003400C)
#define GPTM4_SYNC * ((u32*) 0x40034010)
#define GPTM4_IMR * ((u32*) 0x40034018)
#define GPTM4_RIS * ((u32*) 0x4003401C)
#define GPTM4_MIS * ((u32*) 0x40034020)
#define GPTM4_ICR * ((u32*) 0x40034024)
#define GPTM4_TAILR * ((u32*) 0x40034028)
#define GPTM4_TBILR * ((u32*) 0x4003402C)
#define GPTM4_TAMATCHR * ((u32*) 0x40034030)
#define GPTM4_TBMATCHR * ((u32*) 0x40034034)
#define GPTM4_TAPR * ((u32*) 0x40034038)
#define GPTM4_TBPR * ((u32*) 0x4003403C)
#define GPTM4_TAPMR * ((u32*) 0x40034040)
#define GPTM4_TBPMR * ((u32*) 0x40034044)
#define GPTM4_TAR * ((u32*) 0x40034048)
#define GPTM4_TBR * ((u32*) 0x4003404C)
#define GPTM4_TAV * ((u32*) 0x40034050)
#define GPTM4_TBV * ((u32*) 0x40034054)
#define GPTM4_RTCPD * ((u32*) 0x40034058)
#define GPTM4_TAPS * ((u32*) 0x4003405C)
#define GPTM4_TBPS * ((u32*) 0x40034060)
#define GPTM4_TAPV * ((u32*) 0x40034064)
#define GPTM4_TBPV * ((u32*) 0x40034068)
#define GPTM4_PP * ((u32*) 0x40034FC0)

/*GPTM5*/
#define GPTM5_CFG * ((u32*) 0x40035000)
#define GPTM5_TAMR * ((u32*) 0x40035004)
#define GPTM5_TBMR * ((u32*) 0x40035008)
#define GPTM5_CTL * ((u32*) 0x4003500C)
#define GPTM5_SYNC * ((u32*) 0x40035010)
#define GPTM5_IMR * ((u32*) 0x40035018)
#define GPTM5_RIS * ((u32*) 0x4003501C)
#define GPTM5_MIS * ((u32*) 0x40035020)
#define GPTM5_ICR * ((u32*) 0x40035024)
#define GPTM5_TAILR * ((u32*) 0x40035028)
#define GPTM5_TBILR * ((u32*) 0x4003502C)
#define GPTM5_TAMATCHR * ((u32*) 0x40035030)
#define GPTM5_TBMATCHR * ((u32*) 0x40035034)
#define GPTM5_TAPR * ((u32*) 0x40035038)
#define GPTM5_TBPR * ((u32*) 0x4003503C)
#define GPTM5_TAPMR * ((u32*) 0x40035040)
#define GPTM5_TBPMR * ((u32*) 0x40035044)
#define GPTM5_TAR * ((u32*) 0x40035048)
#define GPTM5_TBR * ((u32*) 0x4003504C)
#define GPTM5_TAV * ((u32*) 0x40035050)
#define GPTM5_TBV * ((u32*) 0x40035054)
#define GPTM5_RTCPD * ((u32*) 0x40035058)
#define GPTM5_TAPS * ((u32*) 0x4003505C)
#define GPTM5_TBPS * ((u32*) 0x40035060)
#define GPTM5_TAPV * ((u32*) 0x40035064)
#define GPTM5_TBPV * ((u32*) 0x40035068)
#define GPTM5_PP * ((u32*) 0x40035FC0)

/*Wide timers*/
/*To be added below*/
#endif