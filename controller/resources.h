// Copyright 2009 Emilie Gillet.
//
// Author: Emilie Gillet (emilie.o.gillet@gmail.com)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// -----------------------------------------------------------------------------
//
// Resources definitions.
//
// Automatically generated with:
// make resources


#ifndef CONTROLLER_RESOURCES_H_
#define CONTROLLER_RESOURCES_H_


#include "avrlib/base.h"

#include <avr/pgmspace.h>


#include "avrlib/resources_manager.h"

namespace ambika {

typedef uint16_t ResourceId;

extern const prog_char* const string_table[];

extern const prog_uint16_t* const lookup_table_table[];

extern const prog_uint8_t* const character_table[];

extern const prog_uint8_t* const waveform_table[];

extern const prog_uint16_t lut_res_lfo_increments[] PROGMEM;
extern const prog_uint16_t lut_res_scale_just[] PROGMEM;
extern const prog_uint16_t lut_res_scale_pythagorean[] PROGMEM;
extern const prog_uint16_t lut_res_scale_1_4_eb[] PROGMEM;
extern const prog_uint16_t lut_res_scale_1_4_e[] PROGMEM;
extern const prog_uint16_t lut_res_scale_1_4_ea[] PROGMEM;
extern const prog_uint16_t lut_res_scale_bhairav[] PROGMEM;
extern const prog_uint16_t lut_res_scale_gunakri[] PROGMEM;
extern const prog_uint16_t lut_res_scale_marwa[] PROGMEM;
extern const prog_uint16_t lut_res_scale_shree[] PROGMEM;
extern const prog_uint16_t lut_res_scale_purvi[] PROGMEM;
extern const prog_uint16_t lut_res_scale_bilawal[] PROGMEM;
extern const prog_uint16_t lut_res_scale_yaman[] PROGMEM;
extern const prog_uint16_t lut_res_scale_kafi[] PROGMEM;
extern const prog_uint16_t lut_res_scale_bhimpalasree[] PROGMEM;
extern const prog_uint16_t lut_res_scale_darbari[] PROGMEM;
extern const prog_uint16_t lut_res_scale_rageshree[] PROGMEM;
extern const prog_uint16_t lut_res_scale_khamaj[] PROGMEM;
extern const prog_uint16_t lut_res_scale_mimal[] PROGMEM;
extern const prog_uint16_t lut_res_scale_parameshwari[] PROGMEM;
extern const prog_uint16_t lut_res_scale_rangeshwari[] PROGMEM;
extern const prog_uint16_t lut_res_scale_gangeshwari[] PROGMEM;
extern const prog_uint16_t lut_res_scale_kameshwari[] PROGMEM;
extern const prog_uint16_t lut_res_scale_pa__kafi[] PROGMEM;
extern const prog_uint16_t lut_res_scale_natbhairav[] PROGMEM;
extern const prog_uint16_t lut_res_scale_m_kauns[] PROGMEM;
extern const prog_uint16_t lut_res_scale_bairagi[] PROGMEM;
extern const prog_uint16_t lut_res_scale_b_todi[] PROGMEM;
extern const prog_uint16_t lut_res_scale_chandradeep[] PROGMEM;
extern const prog_uint16_t lut_res_scale_kaushik_todi[] PROGMEM;
extern const prog_uint16_t lut_res_scale_jogeshwari[] PROGMEM;
extern const prog_uint16_t lut_res_arpeggiator_patterns[] PROGMEM;
extern const prog_uint16_t lut_res_groove_swing[] PROGMEM;
extern const prog_uint16_t lut_res_groove_shuffle[] PROGMEM;
extern const prog_uint16_t lut_res_groove_push[] PROGMEM;
extern const prog_uint16_t lut_res_groove_lag[] PROGMEM;
extern const prog_uint16_t lut_res_groove_human[] PROGMEM;
extern const prog_uint16_t lut_res_groove_monkey[] PROGMEM;
extern const prog_uint8_t chr_res_special_characters[] PROGMEM;
extern const prog_uint8_t wav_res_lfo_waveforms[] PROGMEM;
#define STR_RES_WAVEFORM 0  // waveform
#define STR_RES_PARAMETER 1  // parameter
#define STR_RES_RANGE 2  // range
#define STR_RES_TUNE 3  // tune
#define STR_RES_OSC_MIX 4  // osc mix
#define STR_RES_SUB_OSC_ 5  // sub osc.
#define STR_RES_CROSSMOD_ 6  // crossmod.
#define STR_RES_OPERATOR 7  // operator
#define STR_RES_AMOUNT 8  // amount
#define STR_RES_RESONANCE 9  // resonance
#define STR_RES_MODE 10  // mode
#define STR_RES_ENV2TVCF 11  // env2~vcf
#define STR_RES_LFO2TVCF 12  // lfo2~vcf
#define STR_RES_VELOTVCF 13  // velo~vcf
#define STR_RES_KEYBTVCF 14  // keyb~vcf
#define STR_RES_CRV1 15  // crv1
#define STR_RES_CRV2 16  // crv2
#define STR_RES_CRV3 17  // crv3
#define STR_RES_ENV1_CURVE 18  // env1 curve
#define STR_RES_ENV2_CURVE 19  // env2 curve
#define STR_RES_ENV3_CURVE 20  // env3 curve
#define STR_RES_VINT 21  // vint
#define STR_RES_VINTAGE 22  // vintage
#define STR_RES_VOICE 23  // voice
#define STR_RES_ATTACK 24  // attack
#define STR_RES_DECAY 25  // decay
#define STR_RES_SUSTAIN 26  // sustain
#define STR_RES_RELEASE 27  // release
#define STR_RES_TRIGGER 28  // trigger
#define STR_RES_RATE 29  // rate
#define STR_RES_LFO_EG 30  // lfo/eg
#define STR_RES_VOICE_LFO 31  // voice lfo
#define STR_RES_SOURCE 32  // source
#define STR_RES_DESTINATION 33  // destination
#define STR_RES_IN1 34  // in1
#define STR_RES_IN2 35  // in2
#define STR_RES_MODULATION 36  // modulation
#define STR_RES_MODUL_ 37  // modul.
#define STR_RES__MODULATION 38  // modulation
#define STR_RES_MODIFIER 39  // modifier
#define STR_RES_MODIF_ 40  // modif.
#define STR_RES_VOLUME 41  // volume
#define STR_RES_OCTAVE 42  // octave
#define STR_RES_SPREAD 43  // spread
#define STR_RES_LEGATO 44  // legato
#define STR_RES_PORTAMENTO 45  // portamento
#define STR_RES_ARP_SEQ 46  // arp/seq
#define STR_RES_RAGA 47  // raga
#define STR_RES_DIRECTION 48  // direction
#define STR_RES_PATTERN 49  // pattern
#define STR_RES_CHANNEL 50  // channel
#define STR_RES_PART 51  // part
#define STR_RES_BPM 52  // bpm
#define STR_RES_LTCH 53  // ltch
#define STR_RES_LATCH 54  // latch
#define STR_RES_LOW 55  // low
#define STR_RES_HIGH 56  // high
#define STR_RES_GRID 57  // grid
#define STR_RES_SEQ1_LEN 58  // seq1 len
#define STR_RES_SEQ2_LEN 59  // seq2 len
#define STR_RES_PATT_LEN 60  // patt len
#define STR_RES_LEN1 61  // len1
#define STR_RES_LEN2 62  // len2
#define STR_RES_LENP 63  // lenp
#define STR_RES_GROOVE 64  // groove
#define STR_RES_MIDI 65  // midi
#define STR_RES_SNAP 66  // snap
#define STR_RES_HELP 67  // help
#define STR_RES_AUTO_BACKUP 68  // auto backup
#define STR_RES_LEDS 69  // leds
#define STR_RES_CARD_LEDS 70  // card leds
#define STR_RES_SWAP_COLORS 71  // swap colors
#define STR_RES_INPT_FILTER 72  // inpt filter
#define STR_RES_OUTP_MODE 73  // outp mode
#define STR_RES_EXT 74  // ext
#define STR_RES_OMNI 75  // omni
#define STR_RES_AMNT 76  // amnt
#define STR_RES_SRCE 77  // srce
#define STR_RES_OCT 78  // oct
#define STR_RES_SPRD 79  // sprd
#define STR_RES_A_SQ 80  // a/sq
#define STR_RES_OCTV 81  // octv
#define STR_RES_OFF 82  // off
#define STR_RES_ON 83  // on
#define STR_RES_NONE 84  // none
#define STR_RES_SAW 85  // saw
#define STR_RES_SQUARE 86  // square
#define STR_RES_TRIANGLE 87  // triangle
#define STR_RES_SINE 88  // sine
#define STR_RES_ZSAW 89  // zsaw
#define STR_RES_LPZSAW 90  // lpzsaw
#define STR_RES_PKZSAW 91  // pkzsaw
#define STR_RES_BPZSAW 92  // bpzsaw
#define STR_RES_HPZSAW 93  // hpzsaw
#define STR_RES_LPZPULSE 94  // lpzpulse
#define STR_RES_PKZPULSE 95  // pkzpulse
#define STR_RES_BPZPULSE 96  // bpzpulse
#define STR_RES_HPZPULSE 97  // hpzpulse
#define STR_RES_ZTRIANGLE 98  // ztriangle
#define STR_RES_PAD 99  // pad
#define STR_RES_FM 100  // fm
#define STR_RES_8BITS 101  // 8bits
#define STR_RES_PWM 102  // pwm
#define STR_RES_NOISE 103  // noise
#define STR_RES_VOWEL 104  // vowel
#define STR_RES_MALE 105  // male
#define STR_RES_FEMALE 106  // female
#define STR_RES_CHOIR 107  // choir
#define STR_RES_TAMPURA 108  // tampura
#define STR_RES_BOWED 109  // bowed
#define STR_RES_CELLO 110  // cello
#define STR_RES_VIBES 111  // vibes
#define STR_RES_SLAP 112  // slap
#define STR_RES_EPIANO 113  // epiano
#define STR_RES_ORGAN 114  // organ
#define STR_RES_WAVES 115  // waves
#define STR_RES_DIGITAL 116  // digital
#define STR_RES_DRONE_1 117  // drone 1
#define STR_RES_DRONE_2 118  // drone 2
#define STR_RES_METALLIC 119  // metallic
#define STR_RES_BELL 120  // bell
#define STR_RES_WAVQUENCE 121  // wavquence
#define STR_RES_OLDSAW 122  // oldsaw
#define STR_RES_QPWM 123  // qpwm
#define STR_RES_FMFB 124  // fmfb
#define STR_RES_CSAW 125  // csaw
#define STR_RES_VOWEL_2 126  // vowel 2
#define STR_RES_TRI 127  // tri
#define STR_RES_SQR 128  // sqr
#define STR_RES_S_H 129  // s&h
#define STR_RES_RAMP 130  // ramp
#define STR_RES__SINE 131  // sine
#define STR_RES_HRM2 132  // hrm2
#define STR_RES_HRM3 133  // hrm3
#define STR_RES_HRM5 134  // hrm5
#define STR_RES_GRG1 135  // grg1
#define STR_RES_GRG2 136  // grg2
#define STR_RES_BAT1 137  // bat1
#define STR_RES_BAT2 138  // bat2
#define STR_RES_SPK1 139  // spk1
#define STR_RES_SPK2 140  // spk2
#define STR_RES_LSAW 141  // lsaw
#define STR_RES_LSQR 142  // lsqr
#define STR_RES_RSAW 143  // rsaw
#define STR_RES_RSQR 144  // rsqr
#define STR_RES_STP1 145  // stp1
#define STR_RES_STP2 146  // stp2
#define STR_RES___OFF 147  // off
#define STR_RES_SYNC 148  // sync
#define STR_RES_RINGMOD 149  // ringmod
#define STR_RES_XOR 150  // xor
#define STR_RES_FOLD 151  // fold
#define STR_RES_BITS 152  // bits
#define STR_RES_SQU1 153  // squ1
#define STR_RES_TRI1 154  // tri1
#define STR_RES_PUL1 155  // pul1
#define STR_RES_SQU2 156  // squ2
#define STR_RES_TRI2 157  // tri2
#define STR_RES_PUL2 158  // pul2
#define STR_RES_CLICK 159  // click
#define STR_RES_GLITCH 160  // glitch
#define STR_RES_BLOW 161  // blow
#define STR_RES_METAL 162  // metal
#define STR_RES_POP 163  // pop
#define STR_RES_ENV1 164  // env1
#define STR_RES_ENV2 165  // env2
#define STR_RES_ENV3 166  // env3
#define STR_RES_LFO1 167  // lfo1
#define STR_RES_LFO2 168  // lfo2
#define STR_RES_LFO3 169  // lfo3
#define STR_RES_LFO4 170  // lfo4
#define STR_RES_MOD1 171  // mod1
#define STR_RES_MOD2 172  // mod2
#define STR_RES_MOD3 173  // mod3
#define STR_RES_MOD4 174  // mod4
#define STR_RES_SEQ1 175  // seq1
#define STR_RES_SEQ2 176  // seq2
#define STR_RES_ARP 177  // arp
#define STR_RES_VELO 178  // velo
#define STR_RES_AFTR 179  // aftr
#define STR_RES_BEND 180  // bend
#define STR_RES_MWHL 181  // mwhl
#define STR_RES_WHL2 182  // whl2
#define STR_RES_PDAL 183  // pdal
#define STR_RES_NOTE 184  // note
#define STR_RES_GATE 185  // gate
#define STR_RES_NOIS 186  // nois
#define STR_RES_RAND 187  // rand
#define STR_RES_E256 188  // =256
#define STR_RES_E128 189  // =128
#define STR_RES_E64 190  // =64
#define STR_RES_E32 191  // =32
#define STR_RES_E16 192  // =16
#define STR_RES_E8 193  // =8
#define STR_RES_E4 194  // =4
#define STR_RES_PRM1 195  // prm1
#define STR_RES_PRM2 196  // prm2
#define STR_RES_OSC1 197  // osc1
#define STR_RES_OSC2 198  // osc2
#define STR_RES_31S2 199  // 1+2
#define STR_RES_VIBR 200  // vibr
#define STR_RES_MIX 201  // mix
#define STR_RES_XMOD 202  // xmod
#define STR_RES__NOIS 203  // nois
#define STR_RES_SUB 204  // sub
#define STR_RES_FUZZ 205  // fuzz
#define STR_RES_CRSH 206  // crsh
#define STR_RES_FREQ 207  // freq
#define STR_RES_RESO 208  // reso
#define STR_RES_ATTK 209  // attk
#define STR_RES_DECA 210  // deca
#define STR_RES_RELE 211  // rele
#define STR_RES__LFO4 212  // lfo4
#define STR_RES_VCA 213  // vca
#define STR_RES_ENV_1 214  // env 1
#define STR_RES_ENV_2 215  // env 2
#define STR_RES_ENV_3 216  // env 3
#define STR_RES_LFO_1 217  // lfo 1
#define STR_RES_LFO_2 218  // lfo 2
#define STR_RES_LFO_3 219  // lfo 3
#define STR_RES_LFO_4 220  // lfo 4
#define STR_RES_MOD__1 221  // mod. 1
#define STR_RES_MOD__2 222  // mod. 2
#define STR_RES_MOD__3 223  // mod. 3
#define STR_RES_MOD__4 224  // mod. 4
#define STR_RES_SEQ__1 225  // seq. 1
#define STR_RES_SEQ__2 226  // seq. 2
#define STR_RES__ARP 227  // arp
#define STR_RES__VELO 228  // velo
#define STR_RES_AFTTCH 229  // afttch
#define STR_RES_BENDER 230  // bender
#define STR_RES_MWHEEL 231  // mwheel
#define STR_RES_WHEEL2 232  // wheel2
#define STR_RES_PEDAL 233  // pedal
#define STR_RES__NOTE 234  // note
#define STR_RES__GATE 235  // gate
#define STR_RES__NOISE 236  // noise
#define STR_RES_RANDOM 237  // random
#define STR_RES_E_256 238  // = 256
#define STR_RES_E_32 239  // = 32
#define STR_RES_E_16 240  // = 16
#define STR_RES_E_8 241  // = 8
#define STR_RES_E_4 242  // = 4
#define STR_RES_PARAM_1 243  // param 1
#define STR_RES_PARAM_2 244  // param 2
#define STR_RES_OSC_1 245  // osc 1
#define STR_RES_OSC_2 246  // osc 2
#define STR_RES_OSC_1S2 247  // osc 1+2
#define STR_RES_VIBRATO 248  // vibrato
#define STR_RES__MIX 249  // mix
#define STR_RES__XMOD 250  // xmod
#define STR_RES___NOISE 251  // noise
#define STR_RES_SUBOSC 252  // subosc
#define STR_RES__FUZZ 253  // fuzz
#define STR_RES_CRUSH 254  // crush
#define STR_RES_FREQUENCY 255  // frequency
#define STR_RES__RESO 256  // reso
#define STR_RES__ATTACK 257  // attack
#define STR_RES__DECAY 258  // decay
#define STR_RES__RELEASE 259  // release
#define STR_RES__LFO_4 260  // lfo 4
#define STR_RES__VCA 261  // vca
#define STR_RES_LP 262  // lp
#define STR_RES_BP 263  // bp
#define STR_RES_HP 264  // hp
#define STR_RES_NT 265  // nt
#define STR_RES_FREE 266  // free
#define STR_RES_ENVTLFO 267  // env~lfo
#define STR_RES_LFOTENV 268  // lfo~env
#define STR_RES_STEP_SEQ 269  // step seq
#define STR_RES_ARPEGGIO 270  // arpeggio
#define STR_RES__PATTERN 271  // pattern
#define STR_RES__OFF 272  // off
#define STR_RES_ADD 273  // add
#define STR_RES_PROD 274  // prod
#define STR_RES_ATTN 275  // attn
#define STR_RES_MAX 276  // max
#define STR_RES_MIN 277  // min
#define STR_RES__XOR 278  // xor
#define STR_RES_GE 279  // >=
#define STR_RES_LE 280  // <=
#define STR_RES_QTZ 281  // qtz
#define STR_RES_LAG 282  // lag
#define STR_RES_MONO 283  // mono
#define STR_RES_POLY 284  // poly
#define STR_RES_2X_UNISON 285  // 2x unison
#define STR_RES_CYCLIC 286  // cyclic
#define STR_RES_CHAIN 287  // chain
#define STR_RES_UP 288  // up
#define STR_RES_DOWN 289  // down
#define STR_RES_UP_DOWN 290  // up&down
#define STR_RES_PLAYED 291  // played
#define STR_RES__RANDOM 292  // random
#define STR_RES_CHORD 293  // chord
#define STR_RES_1_1 294  // 1/1
#define STR_RES_3_4 295  // 3/4
#define STR_RES_2_3 296  // 2/3
#define STR_RES_1_2 297  // 1/2
#define STR_RES_3_8 298  // 3/8
#define STR_RES_1_3 299  // 1/3
#define STR_RES_1_4 300  // 1/4
#define STR_RES_1_6 301  // 1/6
#define STR_RES_1_8 302  // 1/8
#define STR_RES_1_12 303  // 1/12
#define STR_RES_1_16 304  // 1/16
#define STR_RES_1_24 305  // 1/24
#define STR_RES_1_32 306  // 1/32
#define STR_RES_1_48 307  // 1/48
#define STR_RES_1_96 308  // 1/96
#define STR_RES_THRU 309  // thru
#define STR_RES_SEQUENCER 310  // sequencer
#define STR_RES_CONTROLLR 311  // controllr
#define STR_RES__CHAIN 312  // chain
#define STR_RES_FULL 313  // full
#define STR_RES_____ 314  // ....
#define STR_RES____S 315  // ...s
#define STR_RES___P_ 316  // ..p.
#define STR_RES___PS 317  // ..ps
#define STR_RES__N__ 318  // .n..
#define STR_RES__N_S 319  // .n.s
#define STR_RES__NP_ 320  // .np.
#define STR_RES__NPS 321  // .nps
#define STR_RES_C___ 322  // c...
#define STR_RES_C__S 323  // c..s
#define STR_RES_C_P_ 324  // c.p.
#define STR_RES_C_PS 325  // c.ps
#define STR_RES_CN__ 326  // cn..
#define STR_RES_CN_S 327  // cn.s
#define STR_RES_CNP_ 328  // cnp.
#define STR_RES_CNPS 329  // cnps
#define STR_RES_SWING 330  // swing
#define STR_RES_SHUFFLE 331  // shuffle
#define STR_RES_PUSH 332  // push
#define STR_RES__LAG 333  // lag
#define STR_RES_HUMAN 334  // human
#define STR_RES_MONKEY 335  // monkey
#define STR_RES_OSCILLATOR_1 336  // oscillator 1
#define STR_RES_OSCILLATOR_2 337  // oscillator 2
#define STR_RES_MIXER 338  // mixer
#define STR_RES_LFO 339  // lfo
#define STR_RES_FILTER_1 340  // filter 1
#define STR_RES_FILTER_2 341  // filter 2
#define STR_RES_ENVELOPE 342  // envelope
#define STR_RES_ARPEGGIATOR 343  // arpeggiator
#define STR_RES_MULTI 344  // multi
#define STR_RES_CLOCK 345  // clock
#define STR_RES_PERFORMANCE 346  // performance
#define STR_RES_SYSTEM 347  // system
#define STR_RES_PT_X_PATCH 348  // pt X patch
#define STR_RES_PT_X_SEQUENCE 349  // pt X sequence
#define STR_RES_PT_X_PROGRAM 350  // pt X program
#define STR_RES_RANDOMIZE 351  // randomize
#define STR_RES_INIT 352  // init
#define STR_RES_PATCH 353  // PATCH
#define STR_RES_SEQUENCE 354  // SEQUENCE
#define STR_RES_PROGRAM 355  // PROGRAM
#define STR_RES__MULTI 356  // MULTI
#define STR_RES____ 357  // ___
#define STR_RES_EQUAL 358  // equal
#define STR_RES_JUST 359  // just
#define STR_RES_PYTHAGOREAN 360  // pythagorean
#define STR_RES_1_4_EB 361  // 1/4 eb
#define STR_RES_1_4_E 362  // 1/4 e
#define STR_RES_1_4_EA 363  // 1/4 ea
#define STR_RES_BHAIRAV 364  // bhairav
#define STR_RES_GUNAKRI 365  // gunakri
#define STR_RES_MARWA 366  // marwa
#define STR_RES_SHREE 367  // shree
#define STR_RES_PURVI 368  // purvi
#define STR_RES_BILAWAL 369  // bilawal
#define STR_RES_YAMAN 370  // yaman
#define STR_RES_KAFI 371  // kafi
#define STR_RES_BHIMPALASREE 372  // bhimpalasree
#define STR_RES_DARBARI 373  // darbari
#define STR_RES_BAGESHREE 374  // bageshree
#define STR_RES_RAGESHREE 375  // rageshree
#define STR_RES_KHAMAJ 376  // khamaj
#define STR_RES_MIMAL 377  // mi'mal
#define STR_RES_PARAMESHWARI 378  // parameshwari
#define STR_RES_RANGESHWARI 379  // rangeshwari
#define STR_RES_GANGESHWARI 380  // gangeshwari
#define STR_RES_KAMESHWARI 381  // kameshwari
#define STR_RES_PA__KAFI 382  // pa. kafi
#define STR_RES_NATBHAIRAV 383  // natbhairav
#define STR_RES_M_KAUNS 384  // m.kauns
#define STR_RES_BAIRAGI 385  // bairagi
#define STR_RES_B_TODI 386  // b.todi
#define STR_RES_CHANDRADEEP 387  // chandradeep
#define STR_RES_KAUSHIK_TODI 388  // kaushik todi
#define STR_RES_JOGESHWARI 389  // jogeshwari
#define STR_RES_RASIA 390  // rasia
#define LUT_RES_LFO_INCREMENTS 0
#define LUT_RES_LFO_INCREMENTS_SIZE 128
#define LUT_RES_SCALE_JUST 1
#define LUT_RES_SCALE_JUST_SIZE 12
#define LUT_RES_SCALE_PYTHAGOREAN 2
#define LUT_RES_SCALE_PYTHAGOREAN_SIZE 12
#define LUT_RES_SCALE_1_4_EB 3
#define LUT_RES_SCALE_1_4_EB_SIZE 12
#define LUT_RES_SCALE_1_4_E 4
#define LUT_RES_SCALE_1_4_E_SIZE 12
#define LUT_RES_SCALE_1_4_EA 5
#define LUT_RES_SCALE_1_4_EA_SIZE 12
#define LUT_RES_SCALE_BHAIRAV 6
#define LUT_RES_SCALE_BHAIRAV_SIZE 12
#define LUT_RES_SCALE_GUNAKRI 7
#define LUT_RES_SCALE_GUNAKRI_SIZE 12
#define LUT_RES_SCALE_MARWA 8
#define LUT_RES_SCALE_MARWA_SIZE 12
#define LUT_RES_SCALE_SHREE 9
#define LUT_RES_SCALE_SHREE_SIZE 12
#define LUT_RES_SCALE_PURVI 10
#define LUT_RES_SCALE_PURVI_SIZE 12
#define LUT_RES_SCALE_BILAWAL 11
#define LUT_RES_SCALE_BILAWAL_SIZE 12
#define LUT_RES_SCALE_YAMAN 12
#define LUT_RES_SCALE_YAMAN_SIZE 12
#define LUT_RES_SCALE_KAFI 13
#define LUT_RES_SCALE_KAFI_SIZE 12
#define LUT_RES_SCALE_BHIMPALASREE 14
#define LUT_RES_SCALE_BHIMPALASREE_SIZE 12
#define LUT_RES_SCALE_DARBARI 15
#define LUT_RES_SCALE_DARBARI_SIZE 12
#define LUT_RES_SCALE_BAGESHREE 16
#define LUT_RES_SCALE_BAGESHREE_SIZE 12
#define LUT_RES_SCALE_RAGESHREE 17
#define LUT_RES_SCALE_RAGESHREE_SIZE 12
#define LUT_RES_SCALE_KHAMAJ 18
#define LUT_RES_SCALE_KHAMAJ_SIZE 12
#define LUT_RES_SCALE_MIMAL 19
#define LUT_RES_SCALE_MIMAL_SIZE 12
#define LUT_RES_SCALE_PARAMESHWARI 20
#define LUT_RES_SCALE_PARAMESHWARI_SIZE 12
#define LUT_RES_SCALE_RANGESHWARI 21
#define LUT_RES_SCALE_RANGESHWARI_SIZE 12
#define LUT_RES_SCALE_GANGESHWARI 22
#define LUT_RES_SCALE_GANGESHWARI_SIZE 12
#define LUT_RES_SCALE_KAMESHWARI 23
#define LUT_RES_SCALE_KAMESHWARI_SIZE 12
#define LUT_RES_SCALE_PA__KAFI 24
#define LUT_RES_SCALE_PA__KAFI_SIZE 12
#define LUT_RES_SCALE_NATBHAIRAV 25
#define LUT_RES_SCALE_NATBHAIRAV_SIZE 12
#define LUT_RES_SCALE_M_KAUNS 26
#define LUT_RES_SCALE_M_KAUNS_SIZE 12
#define LUT_RES_SCALE_BAIRAGI 27
#define LUT_RES_SCALE_BAIRAGI_SIZE 12
#define LUT_RES_SCALE_B_TODI 28
#define LUT_RES_SCALE_B_TODI_SIZE 12
#define LUT_RES_SCALE_CHANDRADEEP 29
#define LUT_RES_SCALE_CHANDRADEEP_SIZE 12
#define LUT_RES_SCALE_KAUSHIK_TODI 30
#define LUT_RES_SCALE_KAUSHIK_TODI_SIZE 12
#define LUT_RES_SCALE_JOGESHWARI 31
#define LUT_RES_SCALE_JOGESHWARI_SIZE 12
#define LUT_RES_SCALE_RASIA 32
#define LUT_RES_SCALE_RASIA_SIZE 12
#define LUT_RES_ARPEGGIATOR_PATTERNS 33
#define LUT_RES_ARPEGGIATOR_PATTERNS_SIZE 22
#define LUT_RES_GROOVE_SWING 34
#define LUT_RES_GROOVE_SWING_SIZE 16
#define LUT_RES_GROOVE_SHUFFLE 35
#define LUT_RES_GROOVE_SHUFFLE_SIZE 16
#define LUT_RES_GROOVE_PUSH 36
#define LUT_RES_GROOVE_PUSH_SIZE 16
#define LUT_RES_GROOVE_LAG 37
#define LUT_RES_GROOVE_LAG_SIZE 16
#define LUT_RES_GROOVE_HUMAN 38
#define LUT_RES_GROOVE_HUMAN_SIZE 16
#define LUT_RES_GROOVE_MONKEY 39
#define LUT_RES_GROOVE_MONKEY_SIZE 16
#define CHR_RES_SPECIAL_CHARACTERS 0
#define CHR_RES_SPECIAL_CHARACTERS_SIZE 56
#define WAV_RES_LFO_WAVEFORMS 0
#define WAV_RES_LFO_WAVEFORMS_SIZE 2064
typedef avrlib::ResourcesManager<
    ResourceId,
    avrlib::ResourcesTables<
        string_table,
        lookup_table_table> > ResourcesManager; 

}  // namespace ambika

#endif  // CONTROLLER_RESOURCES_H_
